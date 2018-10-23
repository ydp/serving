#ifndef TENSORFLOW_SERVING_MODEL_SERVERS_THRIFT_SERVICE_H_
#define TENSORFLOW_SERVING_MODEL_SERVERS_THRIFT_SERVICE_H_

#include <brpc/server.h>
#include <brpc/thrift_message.h>
#include <brpc/thrift_service.h>
#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface_types.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface_constants.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface_types.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface_constants.h"


using namespace ServiceCommonInterface;
using namespace ServiceClassifyInterface;

namespace tensorflow {

namespace serving {

class ThriftServiceImpl : public brpc::ThriftService {

 public:
  ThriftServiceImpl();
  virtual ~ThriftServiceImpl();
  void ProcessThriftFramedRequest(brpc::Controller* cntl,
                                  brpc::ThriftFramedMessage* req,
                                  brpc::ThriftFramedMessage* res,
                                  google::protobuf::Closure* done) override;

  void classifyGet(brpc::Controller* cntl,
                   ServiceResult*,
                   const ServiceClassifyGetParam*,
                   google::protobuf::Closure* done);
  void classifyGet2(brpc::Controller* cntl,
                    ServiceResult2*,
                    const ServiceClassifyGet2Param*,
                    google::protobuf::Closure* done);
  void classifyGet3(brpc::Controller* cntl,
                    ServiceResult3&,
                    const ServiceClassifyGet3Param&,
                    google::protobuf::Closure* done);

  void stat(brpc::Controller* cntl,
            ServiceResult& _return,
            const ServiceStatParam& param,
            google::protobuf::Closure* done);
  void control(brpc::Controller* cntl,
               ServiceResult& _return,
               const ServiceControlParam& param,
               google::protobuf::Closure* done);

};

} // namespace serving
} // namespace tensorflow

#endif // TENSORFLOW_SERVING_MODEL_SERVERS_THRIFT_SERVICE_H_
