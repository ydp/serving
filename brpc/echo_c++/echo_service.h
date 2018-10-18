// Copyright (c) 2014 Baidu, Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// A server to receive EchoRequest and send back EchoResponse.

#ifndef BRPC_EXAMPLE_ECHO_CPP_SERVER_H_
#define BRPC_EXAMPLE_ECHO_CPP_SERVER_H_

//#include <butil/logging.h>
#include <brpc/server.h>
#include "brpc/echo_c++/echo.pb.h"
#include <brpc/thrift_message.h>
#include <brpc/thrift_service.h>
#include "brpc/echo_c++/gen-cpp/echo_types.h"

// Your implementation of example::EchoService
// Notice that implementing brpc::Describable grants the ability to put
// additional information in /status.
namespace example {
class EchoServiceImpl : public ::example::EchoService {
public:
    EchoServiceImpl();
    virtual ~EchoServiceImpl();
    virtual void Echo(::google::protobuf::RpcController* cntl_base,
                      const ::example::EchoRequest* request,
                      ::example::EchoResponse* response,
                      ::google::protobuf::Closure* done);

};

class Echo2ServiceImpl : public brpc::ThriftService {
public:
    Echo2ServiceImpl();
    virtual ~Echo2ServiceImpl();
    void ProcessThriftFramedRequest(brpc::Controller* cntl,
                                    brpc::ThriftFramedMessage* req,
                                    brpc::ThriftFramedMessage* res,
                                    google::protobuf::Closure* done);

    void Echo2(brpc::Controller* cntl,
              const example::Echo2Request* req,
              example::Echo2Response* res,
              google::protobuf::Closure* done);
};

}  // namespace example

#endif // BRPC_EXAMPLE_ECHO_CPP_SERVER_H_
