#!/bin/bash

docker run -p 8500:8500 -v $(pwd)/models/mnist:/models/mnist -e MODEL_NAME=mnist -t tensorflow/serving &
