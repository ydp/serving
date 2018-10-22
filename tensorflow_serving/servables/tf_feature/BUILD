
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
    name = "tf_feature_transform",
    hdrs = ["tf_feature_transform.h"],
    srcs = ["tf_feature_transform.cc"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@com_github_tencent_rapidjson//:rapidjson",
        "@org_tensorflow//tensorflow/core:lib",
        "@org_tensorflow//tensorflow/core:tensorflow",
    ],
)

