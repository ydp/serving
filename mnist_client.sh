#!/bin/bash

# apt-get install python-gevent
python tensorflow_serving/example/mnist_client.py --num_tests=1000 --server=127.0.0.1:8500
