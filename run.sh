#!/bin/bash 

tensorflow_model_server --port=8500 --model_config_file=./etc/models.conf &
