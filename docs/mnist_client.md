# 

prepare
```
pip install grpcio==1.13.0
pip install grpcio-tools==1.13.0
```

download mnist data
```
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz

mv *.gz /tmp/
```

run 
```
python tensorflow_serving/example/mnist_client.py --num_tests=1000 --server=127.0.0.1:8500
```
