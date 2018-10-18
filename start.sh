#!/bin/bash 

tensorflow_model_server --port=8500 --brpc_port=8501  --platform_config_file=./etc/platform.conf --model_config_file=./etc/models.conf
#tensorflow_model_server --port=8500 --brpc_port=8502 --rest_api_port=8501 --platform_config_file=./etc/platform.conf --model_config_file=./etc/models.conf
