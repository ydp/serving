#!/bin/bash

bazel build -c opt tensorflow_serving/model_servers/tensorflow_model_server
\cp -f bazel-bin/tensorflow_serving/model_servers/tensorflow_model_server /usr/local/bin/tensorflow_model_server
