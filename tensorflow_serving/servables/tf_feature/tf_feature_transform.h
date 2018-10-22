#ifndef TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_TRANSFORM_
#define TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_TRANSFORM_

#include <string>
#include <unordered_map>
#include "tensorflow/core/lib/core/status.h"
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

class TfFeatureTransform {
 public:
  explicit TfFeatureTransform();
  ~TfFeatureTransform();

  Status Load(string path);
  Status ParseTfFeatureColumn(const rapidjson::Document& doc, FeatureNode& node);
  Status ParsePickcats(const rapidjson::Document& doc, FeatureNode& node);

 private:
  std::unordered_map<string, FeatureNode> feature_nodes_;  
};

} // namespace serving
} // namespace tensorflow

#endif // TENSORFLOW_SERVING_SERVABLES_TF_FEATURE_TRANSFORM_

