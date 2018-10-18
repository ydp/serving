# build caffe2


## CPU

ubuntu 16.04

### install from source

```
apt-get update
apt-get install -y --no-install-recommends \
      build-essential \
      git \
      libgoogle-glog-dev \
      libgtest-dev \
      libiomp-dev \
      libleveldb-dev \
      liblmdb-dev \
      libopencv-dev \
      libopenmpi-dev \
      libsnappy-dev \
      libprotobuf-dev \
      openmpi-bin \
      openmpi-doc \
      protobuf-compiler \
      python-dev \
      python-pip 

pip install --user \
      future \
      numpy \
      protobuf \
      typing \
      hypothesis


apt-get install -y --no-install-recommends \
      libgflags-dev \
      cmake

git clone https://github.com/pytorch/pytorch.git && cd pytorch
git submodule update --init --recursive
python setup.py install

```

### test installation

```
cd ~ && python -c 'from caffe2.python import core' 2>/dev/null && echo "Success" || echo "Failure" && cd -

```

## GPU

https://caffe2.ai/docs/getting-started.html?platform=mac&configuration=compile


