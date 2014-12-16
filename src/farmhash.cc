#include <sstream>
#include <node.h>

#include "nan.h"
#include "upstream/farmhash.h"

using namespace std;
using namespace v8;
using namespace node;
using namespace util;

// Convert uint64_t to string via stream
template <typename T>
string Uint64ToString(const T& t) {
  ostringstream ss;
  ss << t;
  return ss.str();
}

// Hash methods - platform dependent

NAN_METHOD(Hash32Buffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint32_t hash = Hash32(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj));
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash32String) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t hash = Hash32(input);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash32WithSeedBuffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = Hash32WithSeed(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj), seed);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash32WithSeedString) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = Hash32WithSeed(input, seed);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Hash64Buffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint64_t hash = Hash64(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj));
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64String) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t hash = Hash64(input);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeedBuffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint64_t seed = args[1]->IntegerValue();
  uint64_t hash = Hash64WithSeed(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj), seed);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeedString) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t seed = args[1]->IntegerValue();
  uint64_t hash = Hash64WithSeed(input, seed);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeedsBuffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint64_t seed1 = args[1]->IntegerValue();
  uint64_t seed2 = args[2]->IntegerValue();
  uint64_t hash = Hash64WithSeeds(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj), seed1, seed2);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Hash64WithSeedsString) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t seed1 = args[1]->IntegerValue();
  uint64_t seed2 = args[2]->IntegerValue();
  uint64_t hash = Hash64WithSeeds(input, seed1, seed2);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

// Fingerprint methods - platform independent

NAN_METHOD(Fingerprint32Buffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint32_t hash = Fingerprint32(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj));
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Fingerprint32String) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint32_t hash = Fingerprint32(input);
  NanReturnValue(NanNew<Uint32>(hash));
}

NAN_METHOD(Fingerprint64Buffer) {
  NanScope();
  Local<Object> buffer_obj = args[0]->ToObject();
  uint64_t hash = Fingerprint64(Buffer::Data(buffer_obj), Buffer::Length(buffer_obj));
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

NAN_METHOD(Fingerprint64String) {
  NanScope();
  string input = *String::Utf8Value(args[0]->ToString());
  uint64_t hash = Fingerprint64(input);
  NanReturnValue(NanNew<String>(Uint64ToString(hash)));
}

// Init

extern "C" void init(Handle<Object> target) {
  NanScope();
  NODE_SET_METHOD(target, "Hash32Buffer", Hash32Buffer);
  NODE_SET_METHOD(target, "Hash32String", Hash32String);
  NODE_SET_METHOD(target, "Hash32WithSeedBuffer", Hash32WithSeedBuffer);
  NODE_SET_METHOD(target, "Hash32WithSeedString", Hash32WithSeedString);
  NODE_SET_METHOD(target, "Hash64Buffer", Hash64Buffer);
  NODE_SET_METHOD(target, "Hash64String", Hash64String);
  NODE_SET_METHOD(target, "Hash64WithSeedBuffer", Hash64WithSeedBuffer);
  NODE_SET_METHOD(target, "Hash64WithSeedString", Hash64WithSeedString);
  NODE_SET_METHOD(target, "Hash64WithSeedsBuffer", Hash64WithSeedsBuffer);
  NODE_SET_METHOD(target, "Hash64WithSeedsString", Hash64WithSeedsString);
  NODE_SET_METHOD(target, "Fingerprint32Buffer", Fingerprint32Buffer);
  NODE_SET_METHOD(target, "Fingerprint32String", Fingerprint32String);
  NODE_SET_METHOD(target, "Fingerprint64Buffer", Fingerprint64Buffer);
  NODE_SET_METHOD(target, "Fingerprint64String", Fingerprint64String);
}

NODE_MODULE(farmhash, init)
