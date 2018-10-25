#include "tensorflow_serving/model_servers/thrift_service.h"
#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/core/framework/tensor.h"
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

void ThriftServiceImpl::classifyGet(brpc::Controller* cntl,
                   ServiceResult* _return,
                   const ServiceClassifyGetParam* param,
                   google::protobuf::Closure* done) {
  brpc::ClosureGuard done_guard(done);
  // LOG(INFO) << "type: " << param->type;
  // LOG(INFO) << "key: " << param->key;
  // LOG(INFO) << "keyType: " << param->keyType;
  // LOG(INFO) << "value: " << param->value;
  // LOG(INFO) << "valueType: " << param->valueType;
  _return->valueType = 1;

  rapidjson::MemoryStream ms(param->key.data(), param->key.size());
  rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::MemoryStream>
      jsonstream(ms);
  rapidjson::Document doc;
  if (doc.ParseStream<rapidjson::kParseStopWhenDoneFlag>(jsonstream)
          .HasParseError()) {
    _return->status = -1;
    _return->value = "JSON Parse error at offset: ";
    LOG(ERROR) << "JSON Parse error at offset: " <<  doc.GetErrorOffset() << ", " << param->key.size()
               << ", " << rapidjson::GetParseError_En(doc.GetParseError());
    return;
  }
  if (!doc.IsObject()) {
    _return->status = -1;
    _return->value = "input JSON is not object.";
    LOG(ERROR) << "input JSON is not object.";
    return;
  }

  rapidjson::Value::ConstMemberIterator it = doc.FindMember("model");
  if (it != doc.MemberEnd()) {
    ModelSpec model_spec;
    model_spec.set_name(it->value.GetString());
    ServableHandle<FeatureTransformer> bundle;
    core_->GetServableHandle(model_spec, &bundle);
    rapidjson::Value::ConstMemberIterator input_field = doc.FindMember("input");
    if (input_field == doc.MemberEnd()) {
      _return->status = -1;
      _return->value = "cannot find input field.";
      LOG(ERROR) << "cannot find input field.";
      return;
    }
    Tensor in_tensor(tensorflow::DT_STRING,
                     tensorflow::TensorShape({(int)input_field->value.Size()}));
    bundle->Transform(doc, in_tensor);

    model_spec.set_name("feed");
    ServableHandle<SavedModelBundle> bundle2;
    Status status = core_->GetServableHandle(model_spec, &bundle2);
    if (!status.ok()) {
      _return->status = -1;
      _return->value = "cannot get servable handle.";
      LOG(ERROR) << "cannot get servable handle.";
      return;
    }

    tensorflow::RunOptions run_options = tensorflow::RunOptions();
    std::vector<std::pair<string, Tensor>> input_tensors;
    input_tensors.push_back(std::make_pair("input_example_tensor:0", in_tensor));
    std::vector<string> output_tensor_names;
    output_tensor_names.push_back("head/predictions/probabilities:0");
    // std::vector<string> output_tensor_aliases;
    std::vector<Tensor> outputs;
    RunMetadata run_metadata;
    bundle2->session->Run(run_options, input_tensors,
                          output_tensor_names, {}, &outputs,
                          &run_metadata);
    for(Tensor& t : outputs) {
      // LOG(INFO) << t.DebugString();
    }
    _return->status = 0;
    _return->value = "{}";
  } else {
    _return->status = -1;
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
