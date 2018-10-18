COPTS = [
    "-D__STDC_FORMAT_MACROS",
    "-DBTHREAD_USE_FAST_PTHREAD_MUTEX",
    "-D__const__=",
    "-D_GNU_SOURCE",
    "-DUSE_SYMBOLIZE",
    "-DNO_TCMALLOC",
    "-D__STDC_LIMIT_MACROS",
    "-D__STDC_CONSTANT_MACROS",
    "-fPIC",
    "-Wno-unused-parameter",
    "-fno-omit-frame-pointer",
    "-DGFLAGS_NS=google",
] + select({
    "@com_github_brpc_brpc//:with_glog": ["-DBRPC_WITH_GLOG=1"],
    "//conditions:default": ["-DBRPC_WITH_GLOG=0"],
})

proto_library(
    name = "echo_c++_proto",
    srcs = [
        "echo_c++/echo.proto",
    ],
)

cc_proto_library(
    name = "cc_echo_c++_proto",
    deps = [
        ":echo_c++_proto",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "echo_c++_service",
    hdrs = [
        "echo_c++/echo_service.h",
        "echo_c++/gen-cpp/echo_types.h",
    ],
    srcs = [
        "echo_c++/echo_service.cpp",
        "echo_c++/gen-cpp/echo_types.cpp",
    ],
    includes = [
        "echo_c++",
    ],
    deps = [
        ":cc_echo_c++_proto",
        "@com_github_brpc_brpc//:brpc",
    ],
    visibility = [
        "//visibility:public",
    ],
    copts = COPTS,
    linkopts = [
      "-lthriftnb",
      "-lthrift",
    ],
)

cc_binary(
    name = "echo_c++_server",
    srcs = [
        "echo_c++/server.cpp",
    ],
    includes = [
        "echo_c++",
    ],
    deps = [
        #":cc_echo_c++_proto",
        ":echo_c++_service",
        "@com_github_brpc_brpc//:brpc",
    ],
    copts = COPTS,
)

cc_binary(
    name = "echo_c++_client",
    srcs = [
        "echo_c++/client.cpp",
    ],
    includes = [
        "echo_c++",
    ],
    deps = [
        ":cc_echo_c++_proto",
        "@com_github_brpc_brpc//:brpc",
    ],
    copts = COPTS,
)
