#!/bin/bash

docker run -itd -p 8500:8500 -p 8501:8501 -v `pwd`:/data -w /data tensorflow/serving:nightly-devel bash
