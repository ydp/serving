namespace cpp example

struct Echo2Request {
    1: optional string data;
    2: optional i32 need_by_proxy;
}

struct ProxyRequest {
    2: optional i32 need_by_proxy;
}

struct Echo2Response {
    1: required string data;
}

service Echo2Service {
    Echo2Response Echo2(1:Echo2Request request);
}
