# build thrift for brpc

## build thrift in ubuntu 16.04

```
wget http://www.us.apache.org/dist/thrift/0.11.0/thrift-0.11.0.tar.gz
tar -xf thrift-0.11.0.tar.gz
cd thrift-0.11.0/

./configure --prefix=/usr --with-ruby=no --with-python=no --with-java=no --with-go=no --with-perl=no --with-php=no --with-csharp=no --with-erlang=no --with-lua=no --with-nodejs=no

# automake and boost dependency
apt-get install automake bison flex g++ git libboost-all-dev libevent-dev libssl-dev libtool make pkg-config

make CPPFLAGS=-DFORCE_BOOST_SMART_PTR -j 4 -s
make install

```


add `build --define=with_thrift=true` in tools/bazel.rc


