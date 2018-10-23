#ifndef TENSORFLOW_SERVING_SERVABLES_FEATURE_SOURCE_ADAPTER_H_
#define TENSORFLOW_SERVING_SERVABLES_FEATURE_SOURCE_ADAPTER_H_

#include <string>

#include "tensorflow_serving/core/simple_loader.h"
#include "tensorflow_serving/core/source_adapter.h"
#include "tensorflow_serving/core/storage_path.h"
#include "tensorflow_serving/servables/feature/feature_source_adapter.pb.h"
#include "tensorflow_serving/servables/feature/feature_transformer.h"

namespace tensorflow {

namespace serving {

void loadFeatureServable();

class FeatureSourceAdapter final
    : public SimpleLoaderSourceAdapter<StoragePath, 
                                       FeatureTransformer> {
 public:
  explicit FeatureSourceAdapter(const FeatureSourceAdapterConfig& config);
  ~FeatureSourceAdapter() override;

 private:
  friend class FeatureSourceAdapterCreator;

  TF_DISALLOW_COPY_AND_ASSIGN(FeatureSourceAdapter);
};

}  // namespace serving

}  // namespace tensorflow


#endif  // TENSORFLOW_SERVING_SERVABLES_FEATURE_SOURCE_ADAPTER_H_

