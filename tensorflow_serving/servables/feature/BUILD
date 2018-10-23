
# Description: specialization for tensorflow with feature transformation

package(
    default_visibility = ["//tensorflow_serving:internal"],
    features = ["-layering_check"],
)

licenses(["notice"])  # Apache 2.0

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
            "g3doc/sitemap.md",
        ],
    ),
)

cc_library(
    name = "feature_transformer",
    hdrs = ["feature_transformer.h"],
    srcs = ["feature_transformer.cc"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@com_github_tencent_rapidjson//:rapidjson",
        "@org_tensorflow//tensorflow/core:framework",
        "@org_tensorflow//tensorflow/core:lib",
        "@org_tensorflow//tensorflow/core:tensorflow",
    ],
)


cc_library(
    name = "feature_source_adapter",
    hdrs = ["feature_source_adapter.h"],
    srcs = ["feature_source_adapter.cc"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":feature_source_adapter_proto",
        ":feature_transformer",
        "//tensorflow_serving/core:simple_loader",
        "//tensorflow_serving/core:source_adapter",
        "//tensorflow_serving/core:storage_path",
        "@org_tensorflow//tensorflow/core:lib",
        "@org_tensorflow//tensorflow/core:tensorflow",
    ],
)

load("//tensorflow_serving:serving.bzl", "serving_proto_library")

serving_proto_library(
    name = "feature_source_adapter_proto",
    srcs = ["feature_source_adapter.proto"],
    cc_api_version = 2,
)
