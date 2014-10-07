#include <sstream>
#include <node.h>

#include "nan.h"
#include "upstream/farmhash.h"

using namespace std;
using namespace v8;
using namespace util;

// Convert uint64_t to string via stream
template <typename T>
string Uint64ToString(const T& t) {
  ostringstream ss;
  ss << t;
  return ss.str();
}

// Hash methods - platform dependent

NAN_METHOD(Hash32) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t hash = Hash32(input);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash32WithSeed) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = Hash32WithSeed(input, seed);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash64) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t hash = Hash64(input);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeed) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t seed = args[1]->IntegerValue();
  uint64_t hash = Hash64WithSeed(input, seed);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeeds) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t seed1 = args[1]->IntegerValue();
  uint64_t seed2 = args[2]->IntegerValue();
  uint64_t hash = Hash64WithSeeds(input, seed1, seed2);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

// Fingerprint methods - platform independent

NAN_METHOD(Fingerprint32) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t hash = Fingerprint32(input);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Fingerprint64) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t hash = Fingerprint64(input);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

// Init

extern "C" void init(Handle<Object> target) {
  NanScope();
  NODE_SET_METHOD(target, "Hash32", Hash32);
  NODE_SET_METHOD(target, "Hash32WithSeed", Hash32WithSeed);
  NODE_SET_METHOD(target, "Hash64", Hash64);
  NODE_SET_METHOD(target, "Hash64WithSeed", Hash64);
  NODE_SET_METHOD(target, "Hash64WithSeeds", Hash64);
  NODE_SET_METHOD(target, "Fingerprint32", Fingerprint32);
  NODE_SET_METHOD(target, "Fingerprint64", Fingerprint64);
}

NODE_MODULE(farmhash, init)
