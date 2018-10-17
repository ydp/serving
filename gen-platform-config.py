# -*- coding: utf-8 -*-


import tensorflow as tf

from tensorflow_serving.config import platform_config_pb2
from tensorflow_serving.servables.tensorflow import session_bundle_config_pb2
from tensorflow_serving.servables.tensorflow import saved_model_bundle_source_adapter_pb2
from tensorflow_serving.servables.hashmap import hashmap_source_adapter_pb2



session_config = tf.ConfigProto()
# config whatever you want
#session_config.gpu_options.allow_growth = True
#session_config.gpu_options.per_process_gpu_memory_fraction = 0.4

legacy_config=session_bundle_config_pb2.SessionBundleConfig(session_config=session_config)
tensorflowAdapter = saved_model_bundle_source_adapter_pb2.SavedModelBundleSourceAdapterConfig(legacy_config=legacy_config)
hashmapAdapter = hashmap_source_adapter_pb2.HashmapSourceAdapterConfig(format=hashmap_source_adapter_pb2.HashmapSourceAdapterConfig.SIMPLE_CSV)

config_map = platform_config_pb2.PlatformConfigMap()
config_map.platform_configs['tensorflow'].source_adapter_config.Pack(tensorflowAdapter)
config_map.platform_configs['hashmap'].source_adapter_config.Pack(hashmapAdapter)

print(config_map)
