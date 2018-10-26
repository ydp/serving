#include "tensorflow_serving/model_servers/thrift_service.h"
#include "rapidjson/error/en.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/writer.h>
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow_serving/core/servable_handle.h"
#include "tensorflow_serving/servables/feature/feature_transformer.h"

namespace tensorflow {
namespace serving {


ThriftServiceImpl::~ThriftServiceImpl() {}

void ThriftServiceImpl::ProcessThriftFramedRequest(brpc::Controller* cntl,
                                  brpc::ThriftFramedMessage* req,
                                  brpc::ThriftFramedMessage* res,
                                  google::protobuf::Closure* done) {
  // Dispatch calls to different methods
  if (cntl->thrift_method_name() == "classifyGet") {
    classifyGet(cntl, res->Cast<ServiceResult>(),
                req->Cast<ServiceClassifyGetParam>(),  done);
  } else if (cntl->thrift_method_name() == "classifyGet2") {
    classifyGet2(cntl, res->Cast<ServiceResult2>(),
                 req->Cast<ServiceClassifyGet2Param>(),  done);
  } else if (cntl->thrift_method_name() == "classifyGet3") {
    //classifyGet3(cntl, req->Cast<ServiceClassifyGet3Param>(),
    //             res->Cast<ServiceResult3>(), done);
  } else if (cntl->thrift_method_name() == "stat") {
    //stat(cntl, req->Cast<ServiceStatParam>(),
    //     res->Cast<ServiceResult>(), done);
  } else if (cntl->thrift_method_name() == "control") {
    //control(cntl, req->Cast<ServiceControlParam>(),
    //       res->Cast<ServiceResult>(), done);
  } else {
    cntl->SetFailed(brpc::ENOMETHOD, "Fail to find method=%s",
                  cntl->thrift_method_name().c_str());
    done->Run();
  }
}

Status ThriftServiceImpl::ExampleFeature(const ModelSpec& model_spec,
                                  const rapidjson::Document& in_doc,
                                  Tensor& out_tensor) {
    ServableHandle<FeatureTransformer> bundle;
    core_->GetServableHandle(model_spec, &bundle);
    return bundle->Transform(in_doc, out_tensor);
}

Status ThriftServiceImpl::Tensorflow(const ModelSpec& model_spec,
                                     const Tensor& in_tensor,
                                     std::vector<Tensor>& out_tenors) {
    ServableHandle<SavedModelBundle> bundle;
    Status status = core_->GetServableHandle(model_spec, &bundle);
    if (!status.ok()) {
      LOG(ERROR) << "cannot get servable handle.";
      return status;
    }

    std::vector<std::pair<string, Tensor>> input_tensors;
    input_tensors.push_back(std::make_pair("input_example_tensor:0", in_tensor));
    std::vector<string> output_tensor_names{"head/predictions/probabilities:0"};
    RunMetadata run_metadata;
    return bundle->session->Run(tensorflow::RunOptions(), input_tensors,
                                output_tensor_names, {}, &out_tenors,
                                &run_metadata);
}

Status ThriftServiceImpl::ExampleFeature2Tensorflow(
           const string& featureModelName,
           const string& tensorflowModelName, int type, int num,
           const rapidjson::Document& in_doc, string& out_json) {
  // ExampleFeature
  ModelSpec model_spec;
  model_spec.set_name(featureModelName);
  Tensor tmp_tensor(tensorflow::DT_STRING, tensorflow::TensorShape({num}));
  ExampleFeature(model_spec, in_doc, tmp_tensor);

  // Tensorflow
  model_spec.set_name(tensorflowModelName);
  std::vector<Tensor> out_tensors;
  Tensorflow(model_spec, tmp_tensor, out_tensors);
    
  rapidjson::Document document;
  document.SetObject();
  char buf[64];
  memset(buf, 0, 64);
  int len = snprintf(buf, 64, "%d", type);
  rapidjson::Value typeValue;
  typeValue.SetString(buf, len, document.GetAllocator());
  document.AddMember("type", typeValue, document.GetAllocator());
  memset(buf, 0, 64);
  len = snprintf(buf, 64, "%d", num);
  rapidjson::Value numValue;
  numValue.SetString(buf, len, document.GetAllocator());
  document.AddMember("num", numValue, document.GetAllocator());
  rapidjson::Value outputValue(rapidjson::kArrayType);
  for(Tensor& out_tensor : out_tensors) {
    const float& score = out_tensor.flat<float>()(1);
    // LOG(INFO) << out_tensor.DebugString();
    rapidjson::Value val(rapidjson::kArrayType);
    memset(buf, 0, 64);
    len = snprintf(buf, 64, "%.16f", score);
    val.PushBack(rapidjson::Value(buf, len, document.GetAllocator()),
                 document.GetAllocator());
    outputValue.PushBack(val, document.GetAllocator());
  }
  document.AddMember("output", outputValue, document.GetAllocator());
  rapidjson::StringBuffer buffer;
  buffer.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  document.Accept(writer);
  out_json = string(buffer.GetString());
  return Status::OK();  
}

void ThriftServiceImpl::classifyGet(brpc::Controller* cntl,
                   ServiceResult* _return,
                   const ServiceClassifyGetParam* param,
                   google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
  _return->valueType = 1;
  _return->status = -1;

  rapidjson::MemoryStream ms(param->key.data(), param->key.size());
  rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::MemoryStream>
      jsonstream(ms);
  rapidjson::Document doc;
  if (doc.ParseStream<rapidjson::kParseStopWhenDoneFlag>(jsonstream)
          .HasParseError()) {
    _return->value = "JSON Parse error at offset: ";
    LOG(ERROR) << "JSON Parse error at offset: " <<  doc.GetErrorOffset() << ", " << param->key.size()
               << ", " << rapidjson::GetParseError_En(doc.GetParseError());
    return;
  }
  if (!doc.IsObject()) {
    _return->value = "input JSON is not object.";
    LOG(ERROR) << "input JSON is not object.";
    return;
  }

  rapidjson::Value::ConstMemberIterator numItr = doc.FindMember("num");
  if (numItr == doc.MemberEnd()) {
    _return->value = "cannot find num field.";
    LOG(ERROR) << "cannot find num field.";
    return;
  }
  int num = atoi(numItr->value.GetString());
  rapidjson::Value::ConstMemberIterator it = doc.FindMember("model");
  if (it != doc.MemberEnd()) {
    const string& model_name = it->value.GetString();
    if (model_name == "feature") {
      ExampleFeature2Tensorflow(model_name, "tensorflow", param->type, num,
                                doc, _return->value);
      _return->status = 0;
    } else {
      _return->value = "not implemented.";
    }
  } else {
    _return->value = "input JSON cannot find model field.";
  }
}

void ThriftServiceImpl::classifyGet2(brpc::Controller* cntl,
                    ServiceResult2*,
                    const ServiceClassifyGet2Param*,
                    google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
}

void ThriftServiceImpl::classifyGet3(brpc::Controller* cntl,
                    ServiceResult3&,
                    const ServiceClassifyGet3Param&,
                    google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
  // TODO
}

void ThriftServiceImpl::stat(brpc::Controller* cntl,
            ServiceResult& _return,
            const ServiceStatParam& param,
            google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
  // TODO
}


void ThriftServiceImpl::control(brpc::Controller* cntl,
               ServiceResult& _return,
               const ServiceControlParam& param,
               google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
  // TODO
}

} // namespace serving
} // namespace tensorflow
