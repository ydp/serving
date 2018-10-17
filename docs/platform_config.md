# how to generate platform config file

[Is there an example of platform_config_file](https://github.com/tensorflow/serving/issues/342) 

https://gist.github.com/cutewalker/58e1c4f71b5af4822bc732fd619ebda3 

```
platform_configs {
  key: "tensorflow"
  value {
    source_adapter_config {
      [type.googleapis.com/tensorflow.serving.SavedModelBundleSourceAdapterConfig] {
        legacy_config {
          session_config {
            gpu_options {
              per_process_gpu_memory_fraction: 0.4
              allow_growth: true
            }
          }
        }
      }
    }
  }
}
```

generate pb

```
apt-get install python-pip
pip install grpcio
pip install grpcio-tools
bash gen-tf-serving-proto-py.sh ./
```

