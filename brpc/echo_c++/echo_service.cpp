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

}
