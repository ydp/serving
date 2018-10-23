#include "tensorflow_serving/servables/feature/feature_source_adapter.h"

namespace tensorflow {

namespace serving {

namespace {
Status LoadFeaturesConf(const string& path,
                        const FeatureSourceAdapterConfig::OutputType& outputtype,
                        std::unique_ptr<FeatureTransformer>* transformer) {
  switch (outputtype) {
    case FeatureSourceAdapterConfig::TF_EXAMPLE: {
        (*transformer)->LoadTfExampleConf(path);
      break;
    }
    default: 
      return errors::InvalidArgument("Unrecognized outputtype: ", outputtype);
  }
  return Status::OK();
}
} // namespace


void loadFeatureServable() {
  LOG(INFO) << "load feature servable...";
}

FeatureSourceAdapter::FeatureSourceAdapter(
    const FeatureSourceAdapterConfig& config)
    : SimpleLoaderSourceAdapter<StoragePath, FeatureTransformer>(
        [config](const StoragePath& path,
                 std::unique_ptr<FeatureTransformer>* featureTransformer) {
          return LoadFeaturesConf(path, config.outputtype(), featureTransformer);
        },
        SimpleLoaderSourceAdapter<StoragePath,
                                  FeatureTransformer>::EstimateNoResources()) {}

FeatureSourceAdapter::~FeatureSourceAdapter() { Detach(); }

// register
class FeatureSourceAdapterCreator {
  public:
    static Status Create(
        const FeatureSourceAdapterConfig& config,
        std::unique_ptr<SourceAdapter<StoragePath, std::unique_ptr<Loader>>>*
            adapter) {
      adapter->reset(new FeatureSourceAdapter(config));
      return Status::OK();
    }
};

REGISTER_STORAGE_PATH_SOURCE_ADAPTER(FeatureSourceAdapterCreator,
                                     FeatureSourceAdapterConfig);



} // serving

} // namespace tensorflow

