#include "tensorflow_serving/servables/tf_feature/tf_feature_transform.h"
#include <vector>
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/io/inputbuffer.h"
#include "tensorflow/core/lib/strings/str_util.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/types.h"
#include "rapidjson/error/en.h"

TfFeatureTransform::TfFeatureTransform() {}

TfFeatureTransform::~TfFeatureTransform() {}

Status TfFeatureTransform::Load(string path) {
  const string file = io.JoinPath(path, "features.conf");
  std::unique_ptr<RandomAccessFile> f;
  TF_RETURN_IF_ERROR(Env::Default()->NewRandomAccessFile(file, &f));
  const size_t kBufferSizeBytes = 262144;
  io::InputBuffer in(file.get(), kBufferSizeBytes);
  string line;
  while (in.ReadLine(line).ok()) {
    if (line.size() > 2 &&
        line[0] == '#' &&
        line[1] != '#') {
      std::vector<string> cols = str_util::Split(line, '\t');
      if (cols.size() != 4) {
        return errors::InvalidArgument("features.conf not have 4 cols.");
      }
      const string& name = cols[0];
      const string& opType = cols[1];
      const string& oper = cols[2];
      const string& args = cols[3];
      rapidjson::MemoryStream ms(args.data(), args.size());
      rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::MemoryStream>
          jsonstream(ms);
      rapidjson::Document doc;
      if (doc->ParseStream<rapidjson::kParseNanAndInfFlag>(jsonstream)
          .HasParseError()) {
        return errors::InvalidArgument(
          "JSON Parse error: ", rapidjson::GetParseError_En(doc->GetParseError()),
          " at offset: ", doc->GetErrorOffset());
      }
      if (!doc->IsObject()) {
        return errors::InvalidArgument("expected json to an object.");
      }
      FeatureNode node;
      if (oper == "tffeaturecolumn") {
        ParseTfFeatureColumn(doc, node);
      } else if (oper == "pickcats") {
        ParsePickcats(doc, node);
      }      
    }
  }
  return Status::OK();
}

Status TfFeatureTransform::ParseTfFeatureColumn(const rapidjson::Document& doc,
                                                FeatureNode& node) {
  if (doc.HasMember("type")) {
    node.dataType = doc["type"].GetString();
  }
  if (doc.HasMember("defaultin")) {
    if (node.dataType == "float") {
      node.defaultVal.fval = doc["defaultin"].GetFloat();
    } else if (node.dataType == "int") {
      node.defaultVal.ival = doc["defaultin"].GetInt();
    } else if (node.dataType == "string") {
      node.defaultVal.sval = doc["defaultin"].GetString();
    } else {
      return errors::InvalidArgument("unsupported data type.");
    }
  }
  return Status::OK();
}

Status TfFeatureTransform::ParsePickcats(const rapidjson::Document& doc,
                                         FeatureNode& node) {
  if (doc.HasMember("rowdelimiter")) {
    node.rowdelimiter = doc["rowdelimiter"].GetString();
  } 
  if (doc.HasMember("coldelimiter")) {
    node.coldelimiter = doc["coldelimiter"].GetString();
  }
  if (doc.HasMember("valuetype")) {
    node.valuetype = doc["valuetype"].GetString();
  }
  if (doc.HasMember("defaultin")) {
    node.defaultVal.sval = doc["defaultin"].GetString();
  }
  return Status::OK();
}


