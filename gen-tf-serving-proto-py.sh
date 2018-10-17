#!/bin/bash
# run at root of tensorflow_serving repo
TARGET_DIR="$1"

python -m grpc_tools.protoc \
    -I . -I ./tensorflow \
    --python_out "$TARGET_DIR" \
    tensorflow_serving/servables/tensorflow/saved_model_bundle_source_adapter.proto \
    tensorflow_serving/servables/hashmap/hashmap_source_adapter.proto \
    tensorflow_serving/servables/tensorflow/session_bundle_config.proto \
    tensorflow_serving/config/platform_config.proto

pushd $TARGET_DIR

touch tensorflow_serving/__init__.py
touch tensorflow_serving/config/__init__.py
touch tensorflow_serving/servables/__init__.py
touch tensorflow_serving/servables/tensorflow/__init__.py
touch tensorflow_serving/servables/hashmap/__init__.py

popd
