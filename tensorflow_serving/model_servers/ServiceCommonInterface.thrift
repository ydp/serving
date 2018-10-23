namespace cpp ServiceCommonInterface
namespace java common.service.classify.thrift
namespace perl ServiceCommonInterface
namespace php ServiceCommonInterface

//return value type
const i32 MYSERVICEVALUETYPEARRAY 	= 0
const i32 MYSERVICEVALUETYPEJSON 	= 1
const i32 MYSERVICEVALUETYPEDICT 	= 2
const i32 MYSERVICEVALUETYPEVALUE 	= 3

typedef list<string> MySequenceString
typedef list<list<string>> MyMatrixString
typedef map<string, string> MyDictionaryString

struct ServiceStatParam {
    1: string cmd
}

struct ServiceControlParam {
    1: string cmd
    11: MyDictionaryString valueDict
}

struct ServiceResult {
    1: i32 status           //0: ok; <0: error;
    11: i32 valueType       //0: array; 1: json; 2: dict
    12: string value		//column name->column value
    13: MyMatrixString valueMatrix	//inner: don't include column names; outside: the first row is column name
    14: MyDictionaryString valueDict
}

service ServiceCommonInterface {
    ServiceResult stat(1: ServiceStatParam param)

    ServiceResult control(1: ServiceControlParam param)
}
