#include <gflags/gflags.h>

#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface_types.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceCommonInterface_constants.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface_types.h"
#include "tensorflow_serving/model_servers/gen-cpp/ServiceClassifyInterface_constants.h"

#include <butil/logging.h>
#include <butil/time.h>
#include <brpc/channel.h>
#include <brpc/thrift_message.h>
#include <bvar/bvar.h>

bvar::LatencyRecorder g_latency_recorder("client");

DEFINE_string(server, "0.0.0.0:8501", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)"); 

using namespace ServiceCommonInterface;
using namespace ServiceClassifyInterface;

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    // A Channel represents a communication line to a Server. Notice that 
    // Channel is thread-safe and can be shared by all threads in your program.
    brpc::Channel channel;
    
    // Initialize the channel, NULL means using default options. 
    brpc::ChannelOptions options;
    options.protocol = brpc::PROTOCOL_THRIFT;
    options.timeout_ms = FLAGS_timeout_ms/*milliseconds*/;
    options.max_retry = FLAGS_max_retry;
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    brpc::ThriftStub stub(&channel);

    // Send a request and wait for the response every 1 second.
    while (!brpc::IsAskedToQuit()) {
        brpc::Controller cntl;
        ServiceClassifyGetParam req;
        ServiceResult res;

        req.__set_type(0);
        req.__set_key("####Aaasdfasdfaef");
        req.__set_keyType(1);
        req.__set_value("test value !!!!!!");
        req.__set_valueType(1);

        stub.CallMethod("classifyGet", &cntl, &req, &res, NULL);

        if (cntl.Failed()) {
            LOG(ERROR) << "Fail to send thrift request, " << cntl.ErrorText();
            sleep(1); // Remove this sleep in production code.
        } else {
            g_latency_recorder << cntl.latency_us();
            LOG(INFO) << "Thrift Response: " << res;
        }

        LOG_EVERY_SECOND(INFO)
            << "Sending thrift requests at qps=" << g_latency_recorder.qps(1)
            << " latency=" << g_latency_recorder.latency(1);

        sleep(1);

    }

    LOG(INFO) << "ThriftServiceClient is going to quit";
    return 0;
}

