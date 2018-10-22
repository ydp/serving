#include "tensorflow_serving/servables/tf_feature/tf_feature_source_adapter.h"


namespace tensorflow {

namespace serving {




TfFeatureSourceAdapter::TfFeatureSourceAdapter(
    const TfFeatureSourceAdapterConfig& config)
    : SimpleLoaderSourceAdapter<StoragePath, Hashmap>(
        [config](const StoragePath& path, std::unique_ptr<Hashmap>* hashmap) {
          return ;
        },
        SimpleLoaderSourceAdapter<StoragePath,
                                  Hashmap>::EstimateNoResources()) {}

TfFeatureSourceAdapter::~TfFeatureSourceAdapter() { Detach(); }

} // serving

} // namespace tensorflow
