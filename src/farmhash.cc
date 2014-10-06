#include <sstream>
#include <node.h>

#include "nan.h"
#include "upstream/farmhash.h"

using namespace std;
using namespace v8;
using namespace util;

template <typename T>
string ToString(const T& t) {
  ostringstream ss;
  ss << t;
  return ss.str();
}

NAN_METHOD(Hash64) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t hash = Hash64(input);
  NanReturnValue(NanNew<String>(ToString(hash)));
}

extern "C" void init(Handle<Object> target) {
  NanScope();
  NODE_SET_METHOD(target, "Hash64", Hash64);
}

NODE_MODULE(farmhash, init)
