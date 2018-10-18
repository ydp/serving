# brpc


```
apt-get install libssl-dev
```

add `build --copt -DHAVE_ZLIB=1` in tools/bazel.rc in serving project, see issue [275](https://github.com/brpc/brpc/issues/275)

```
bazel build //brpc:echo_c++_server
bazel build //brpc:echo_c++_client
```
