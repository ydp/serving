/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "echo_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace example {


Echo2Request::~Echo2Request() throw() {
}


void Echo2Request::__set_data(const std::string& val) {
  this->data = val;
__isset.data = true;
}

void Echo2Request::__set_need_by_proxy(const int32_t val) {
  this->need_by_proxy = val;
__isset.need_by_proxy = true;
}
std::ostream& operator<<(std::ostream& out, const Echo2Request& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Echo2Request::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->data);
          this->__isset.data = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->need_by_proxy);
          this->__isset.need_by_proxy = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Echo2Request::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Echo2Request");

  if (this->__isset.data) {
    xfer += oprot->writeFieldBegin("data", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->data);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.need_by_proxy) {
    xfer += oprot->writeFieldBegin("need_by_proxy", ::apache::thrift::protocol::T_I32, 2);
    xfer += oprot->writeI32(this->need_by_proxy);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Echo2Request &a, Echo2Request &b) {
  using ::std::swap;
  swap(a.data, b.data);
  swap(a.need_by_proxy, b.need_by_proxy);
  swap(a.__isset, b.__isset);
}

Echo2Request::Echo2Request(const Echo2Request& other0) {
  data = other0.data;
  need_by_proxy = other0.need_by_proxy;
  __isset = other0.__isset;
}
Echo2Request& Echo2Request::operator=(const Echo2Request& other1) {
  data = other1.data;
  need_by_proxy = other1.need_by_proxy;
  __isset = other1.__isset;
  return *this;
}
void Echo2Request::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Echo2Request(";
  out << "data="; (__isset.data ? (out << to_string(data)) : (out << "<null>"));
  out << ", " << "need_by_proxy="; (__isset.need_by_proxy ? (out << to_string(need_by_proxy)) : (out << "<null>"));
  out << ")";
}


ProxyRequest::~ProxyRequest() throw() {
}


void ProxyRequest::__set_need_by_proxy(const int32_t val) {
  this->need_by_proxy = val;
__isset.need_by_proxy = true;
}
std::ostream& operator<<(std::ostream& out, const ProxyRequest& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ProxyRequest::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->need_by_proxy);
          this->__isset.need_by_proxy = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ProxyRequest::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ProxyRequest");

  if (this->__isset.need_by_proxy) {
    xfer += oprot->writeFieldBegin("need_by_proxy", ::apache::thrift::protocol::T_I32, 2);
    xfer += oprot->writeI32(this->need_by_proxy);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ProxyRequest &a, ProxyRequest &b) {
  using ::std::swap;
  swap(a.need_by_proxy, b.need_by_proxy);
  swap(a.__isset, b.__isset);
}

ProxyRequest::ProxyRequest(const ProxyRequest& other2) {
  need_by_proxy = other2.need_by_proxy;
  __isset = other2.__isset;
}
ProxyRequest& ProxyRequest::operator=(const ProxyRequest& other3) {
  need_by_proxy = other3.need_by_proxy;
  __isset = other3.__isset;
  return *this;
}
void ProxyRequest::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ProxyRequest(";
  out << "need_by_proxy="; (__isset.need_by_proxy ? (out << to_string(need_by_proxy)) : (out << "<null>"));
  out << ")";
}


Echo2Response::~Echo2Response() throw() {
}


void Echo2Response::__set_data(const std::string& val) {
  this->data = val;
}
std::ostream& operator<<(std::ostream& out, const Echo2Response& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Echo2Response::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_data = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->data);
          isset_data = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_data)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t Echo2Response::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Echo2Response");

  xfer += oprot->writeFieldBegin("data", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->data);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Echo2Response &a, Echo2Response &b) {
  using ::std::swap;
  swap(a.data, b.data);
}

Echo2Response::Echo2Response(const Echo2Response& other4) {
  data = other4.data;
}
Echo2Response& Echo2Response::operator=(const Echo2Response& other5) {
  data = other5.data;
  return *this;
}
void Echo2Response::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Echo2Response(";
  out << "data=" << to_string(data);
  out << ")";
}

} // namespace