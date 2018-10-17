#!/bin/bash 

tensorflow_model_server --port=8500 --platform_config_file=./etc/platform.conf --model_config_file=./etc/models.conf &
