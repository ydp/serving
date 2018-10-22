#ifndef TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_SOURCE_ADAPTER_H_
#define TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_SOURCE_ADAPTER_H_

#include <string>
#include <unordered_map>

#include "tensorflow_serving/core/simple_loader.h"
#include "tensorflow_serving/core/source_adapter.h"
#include "tensorflow_serving/core/storage_path.h"
#include "tensorflow_serving/servables/tf_feature/tf_feature_source_adapter.pb.h"

namespace tensorflow {

namespace serving {

class TfFeatureSourceAdapter final
    : public SimpleLoaderSourceAdapter<StoragePath, 
                                       std::unordered_map<string, string>> {
 public:
  explicit TfFeatureSourceAdapter(const TfFeatureSourceAdapterConfig& config);
  ~TfFeatureSourceAdapter() override;

 private:
  TF_DISALLOW_COPY_AND_ASSIGN(TfFeatureSourceAdapter);
};

}  // namespace serving

}  // namespace tensorflow


#endif  // TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_SOURCE_ADAPTER_H_
