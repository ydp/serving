#include "brpc/echo_c++/echo_service.h"

namespace example {

EchoServiceImpl::EchoServiceImpl() {
}

EchoServiceImpl::~EchoServiceImpl() {
}
void EchoServiceImpl::Echo(::google::protobuf::RpcController* cntl_base,
                         const ::example::EchoRequest* request,
                         ::example::EchoResponse* response,
                         ::google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
              << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side()
              << ": " << request->message();
    response->set_message(request->message());
    cntl->response_attachment().append(cntl->request_attachment());
}


Echo2ServiceImpl::Echo2ServiceImpl() {
}

Echo2ServiceImpl::~Echo2ServiceImpl(){
}

void Echo2ServiceImpl::ProcessThriftFramedRequest(brpc::Controller* cntl,
                                    brpc::ThriftFramedMessage* req,
                                    brpc::ThriftFramedMessage* res,
                                    google::protobuf::Closure* done) {
        // Dispatch calls to different methods
        if (cntl->thrift_method_name() == "Echo2") {
            return Echo2(cntl, req->Cast<example::Echo2Request>(),
                        res->Cast<example::Echo2Response>(), done);
        } else {
            cntl->SetFailed(brpc::ENOMETHOD, "Fail to find method=%s",
                            cntl->thrift_method_name().c_str());
            done->Run();
        }
}

void Echo2ServiceImpl::Echo2(brpc::Controller* cntl,
              const example::Echo2Request* req,
              example::Echo2Response* res,
              google::protobuf::Closure* done) {
        // This object helps you to call done->Run() in RAII style. If you need
        // to process the request asynchronously, pass done_guard.release().
        brpc::ClosureGuard done_guard(done);
        LOG(INFO) << req->data;
        res->data = req->data + " (processed)";
}

}

