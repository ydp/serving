#ifndef TENSORFLOW_SERVING_SERVABLES_FEATURE_TRANSFORMER_
#define TENSORFLOW_SERVING_SERVABLES_FEATURE_TRANSFORMER_

#include <string>
#include "tensorflow/core/lib/core/status.h"
#include "tensorflow/core/framework/tensor.h"
#include "rapidjson/document.h"

namespace tensorflow {

namespace serving {

struct DefaultValue {
  float fval;
  int ival;
  string sval;
  DefaultValue() {
    sval = "";
  }
};

struct FeatureNode {
  // basic fields
  string name;
  string opType;
  string oper;
  string dataType;
  DefaultValue defaultVal; 

  // fields for operation computing
  //
  // pickcats
  string rowdelimiter;
  string coldelimiter;
  string valuetype;
};

class FeatureTransformer {
 public:
  explicit FeatureTransformer();
  ~FeatureTransformer();

  Status LoadTfExampleConf(string path);
  Status Transorm(const rapidjson::Document& doc,
                  Tensor& example_tensor);
 private:
  Status ParseFeatureColumn(const rapidjson::Document& doc, FeatureNode& node);
  Status ParsePickcats(const rapidjson::Document& doc, FeatureNode& node);

 private:
  std::vector<FeatureNode> feature_nodes_;  
};

} // namespace serving
} // namespace tensorflow

#endif // TENSORFLOW_SERVING_SERVABLES_FEATURE_TRANSFORMER_

