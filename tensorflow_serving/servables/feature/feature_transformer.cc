#include "tensorflow_serving/servables/feature/feature_transformer.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/io/inputbuffer.h"
#include "tensorflow/core/lib/strings/str_util.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/types.h"
#include "rapidjson/error/en.h"
#include "tensorflow/core/example/example.pb.h"
#include "tensorflow/core/example/feature.pb.h"

namespace tensorflow {

namespace serving {

FeatureTransformer::~FeatureTransformer() {}

Status FeatureTransformer::LoadTfExampleConf(string path) {
  const string file = io::JoinPath(path, "features.conf");
  std::unique_ptr<RandomAccessFile> f;
  TF_RETURN_IF_ERROR(Env::Default()->NewRandomAccessFile(file, &f));
  const size_t kBufferSizeBytes = 262144;
  io::InputBuffer in(f.get(), kBufferSizeBytes);
  string line;
  while (in.ReadLine(&line).ok()) {
    if (line.size() > 2 &&
        line[0] == '#' &&
        line[1] != '#') {
      std::vector<string> cols = str_util::Split(line, '\t');
      if (cols.size() != 4) {
        return errors::InvalidArgument("features.conf not have 4 cols.");
      }
      const string& name = cols[0].substr(1);
      const string& opType = cols[1];
      const string& oper = cols[2];
      const string& args = cols[3];
      rapidjson::MemoryStream ms(args.data(), args.size());
      rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::MemoryStream>
          jsonstream(ms);
      rapidjson::Document doc;
      if (doc.ParseStream<rapidjson::kParseNanAndInfFlag>(jsonstream)
          .HasParseError()) {
        return errors::InvalidArgument(
          "JSON Parse error: ", rapidjson::GetParseError_En(doc.GetParseError()),
          " at offset: ", doc.GetErrorOffset());
      }
      if (!doc.IsObject()) {
        return errors::InvalidArgument("expected json to an object.");
      }
      FeatureNode node;
      node.name = name;
      node.opType = opType;
      if (oper == "tffeaturecolumn") {
        ParseFeatureColumn(doc, node);
      } else if (oper == "pickcats") {
        ParsePickcats(doc, node);
      }      
      feature_nodes_.emplace_back(node);
    }
  }
  return Status::OK();
}

Status FeatureTransformer::ParseFeatureColumn(const rapidjson::Document& doc,
                                                FeatureNode& node) {
  rapidjson::Value::ConstMemberIterator itor;
  itor = doc.FindMember("type");
  if (itor != doc.MemberEnd()) {
    node.dataType = itor->value.GetString();
  }
  itor = doc.FindMember("defaultin");
  if (itor != doc.MemberEnd()) {
    const string& v = itor->value.GetString();
    if (node.dataType == "float") {
      node.defaultVal.fval = atof(v.c_str());
    } else if (node.dataType == "int") {
      node.defaultVal.ival = atoi(v.c_str());
    } else if (node.dataType == "string") {
      node.defaultVal.sval = v;
    } else {
      return errors::InvalidArgument("unsupported data type.");
    }
  }
  return Status::OK();
}

Status FeatureTransformer::ParsePickcats(const rapidjson::Document& doc,
                                         FeatureNode& node) {
  rapidjson::Value::ConstMemberIterator itor;
  itor = doc.FindMember("rowdelimiter");
  if (itor != doc.MemberEnd()) {
    node.rowdelimiter = itor->value.GetString();
  } 
  itor = doc.FindMember("coldelimiter");
  if (itor != doc.MemberEnd()) {
    node.coldelimiter = itor->value.GetString();
  }
  itor = doc.FindMember("valuetype");
  if (itor != doc.MemberEnd()) {
    node.valuetype = itor->value.GetString();
  }
  itor = doc.FindMember("defaultin");
  if (itor != doc.MemberEnd()) {
    node.defaultVal.sval = itor->value.GetString();
  }
  return Status::OK();
}


Status FeatureTransformer::Transform(const rapidjson::Document& doc,
                                    Tensor& example_tensor) {
  rapidjson::Value::ConstMemberIterator it = doc.FindMember("input");
  if (it == doc.MemberEnd()) {
    return errors::InvalidArgument("did not find input field.");
  }
  if (!it->value.IsArray()) {
    return errors::InvalidArgument("input field is not an array.");
  }
  rapidjson::Value::ConstMemberIterator itor;
  for (rapidjson::SizeType i = 0; i < it->value.Size(); ++i) {
    const rapidjson::Value& sample = it->value[i];
    Example example;
    string str_example;
    auto features = example.mutable_features();
    for (auto& feature_def : feature_nodes_) {
      auto& fea = (*features->mutable_feature())[feature_def.name];
      itor = sample.FindMember(feature_def.name.c_str());
      if (itor != sample.MemberEnd()) {
        const string& v = itor->value.GetString();
        if (feature_def.opType == "tffeaturecolumn") {
          if (feature_def.dataType == "int") {
            fea.mutable_int64_list()->add_value(atoi(v.c_str()));
          } else if (feature_def.dataType == "float") {
            fea.mutable_float_list()->add_value(atof(v.c_str()));
          } else if (feature_def.dataType == "string") {
            fea.mutable_bytes_list()->add_value(v);
          }
        } else if (feature_def.opType == "pickcats") {
          // TODO
        }    
      } else {
        if (feature_def.dataType == "int") {
          fea.mutable_int64_list()->add_value(feature_def.defaultVal.ival);
        } else if (feature_def.dataType == "float") {
          fea.mutable_float_list()->add_value(feature_def.defaultVal.fval);
        } else if (feature_def.dataType == "string") {
          fea.mutable_bytes_list()->add_value(feature_def.defaultVal.sval);
        }
      }
    }    // for feature_nodes_  
    // LOG(INFO) << example.DebugString().c_str();
    example.SerializeToString(&str_example);
    example_tensor.flat<string>()(i) = str_example;
    example.Clear();
    str_example.clear();
  }      // for it->value
  return Status::OK();
}

} // namespace serving

} // namespace tensorflow

