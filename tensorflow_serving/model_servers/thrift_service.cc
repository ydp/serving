#include "tensorflow_serving/model_servers/thrift_service.h"


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
  LOG(INFO) << "type: " << param->type;
  LOG(INFO) << "key: " << param->key;
  LOG(INFO) << "keyType: " << param->keyType;
  LOG(INFO) << "value: " << param->value;
  LOG(INFO) << "valueType: " << param->valueType;
  
  _return->status = 0;
  _return->valueType = 1;
  _return->value = "{\"key\": \"value\"}";
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
