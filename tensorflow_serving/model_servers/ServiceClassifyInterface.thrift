include "ServiceCommonInterface.thrift"

namespace cpp ServiceClassifyInterface
namespace java common.service.classify.thrift
namespace perl ServiceClassifyInterface
namespace php ServiceClassifyInterface

struct ServiceResult2 {
    1:  i32 status          //0: ok; <0: error;
    2:  i32 type
    3:  i32 num             // feautrevector count
    10: string model
    11: list<double> result
}

//for multi models
struct ServiceResult3 {
    1:  i32 status          //0: ok; <0: error;
    2:  i32 type
    3:  i32 num
    10: list<string> modellist
    11: list<map<string,double>> resultlist //string:modelname, double:predicted result
}

struct ServiceClassifyGetParam {
    1: i32 type
    10: string key
    11: i32 keyType       //0: array; 1: json; 2: dict
    20: string value
    21: i32 valueType       //0: array; 1: json; 2: dict
}

struct ServiceClassifyGet2Param {
     1: i32  version
     2: i32  type
     3: bool isdebug
     4: i32  num
     5: string model
     6: list<double>scorelist
     11: list<map<string,string>> featurelist
}
struct ServiceClassifyGet3Param {
     1: i32  version
     2: i32  type
     3: bool isdebug
     4: i32  num
     5: list<string> modellist
     6: list<double> scorelist
     11: list<map<string,string>> featurelist
}

service ServiceClassifyInterface extends ServiceCommonInterface.ServiceCommonInterface{
    ServiceCommonInterface.ServiceResult classifyGet(1: ServiceClassifyGetParam param)
    ServiceResult2                 classifyGet2(1: ServiceClassifyGet2Param param)
    ServiceResult3                 classifyGet3(1: ServiceClassifyGet3Param param)
}

