// Copyright 2014, 2015, 2016, 2017 Lovell Fuller and contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <node.h>
//#include <nan.h>
#include<napi.h>
#include <sstream>

#include "upstream/farmhash.h"

// Convert uint64_t to string via stream
template <typename T>
std::string Uint64ToString(const T& t) {
  std::ostringstream ss;
  ss << t;
  return ss.str();
}

// Hash methods - platform dependent

Napi::Value Hash32Buffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>(); 
  uint32_t hash = util::Hash32(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  return Napi::Number::New(hash);
}

Napi::Value Hash32String(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t hash = util::Hash32(input);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

Napi::Value Hash32WithSeedBuffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
  uint32_t hash = util::Hash32WithSeed(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

Napi::Value Hash32WithSeedString(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
  uint32_t hash = util::Hash32WithSeed(input, seed);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

Napi::Value Hash64Buffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t hash = util::Hash64(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::Value Hash64String(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t hash = util::Hash64(input);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::Value Hash64WithSeedBuffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t seed = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t hash = util::Hash64WithSeed(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::Value Hash64WithSeedString(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t seed = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t hash = util::Hash64WithSeed(input, seed);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::Value Hash64WithSeedsBuffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t seed1 = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t seed2 = static_cast<uint64_t>(Nan::To<uint32_t>(info[2]).FromJust());
  uint64_t hash = util::Hash64WithSeeds(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed1, seed2);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::value Hash64WithSeedsString(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t seed1 = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t seed2 = static_cast<uint64_t>(Nan::To<uint32_t>(info[2]).FromJust());
  uint64_t hash = util::Hash64WithSeeds(input, seed1, seed2);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

// Fingerprint methods - platform independent

Napi::Value Fingerprint32Buffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint32_t hash = util::Fingerprint32(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

Napi::Value Fingerprint32String(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t hash = util::Fingerprint32(input);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

Napi::Value Fingerprint64Buffer(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t hash = util::Fingerprint64(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

Napi::Value Fingerprint64String(const Napi::CallbackInfo& info) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t hash = util::Fingerprint64(input);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

// Init

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "Hash32Buffer"), Napi::Function::New(env, "Hash32Buffer"));
  exports.Set(Napi::String::New(env, "Hash32String"), Napi::Function::New(env, "Hash32String"));
  exports.Set(Napi::String::New(env, "Hash32WithSeedBuffer"), Napi::Function::New(env, "Hash32WithSeedBuffer"));
  exports.Set(Napi::String::New(env, "Hash32WithSeedString"), Napi::Function::New(env, "Hash32WithSeedString"));
  exports.Set(Napi::String::New(env, "Hash64Buffer"), Napi::Function::New(env, "Hash64Buffer"));
  exports.Set(Napi::String::New(env, "Hash64String"), Napi::Function::New(env, "Hash64String"));
  exports.Set(Napi::String::New(env, "Hash64WithSeedBuffer"), Napi::Function::New(env, "Hash64WithSeedBuffer"));
  exports.Set(Napi::String::New(env, "Hash64WithSeedString"), Napi::Function::New(env, "Hash64WithSeedString"));
  exports.Set(Napi::String::New(env, "Hash64WithSeedsBuffer"), Napi::Function::New(env, "Hash64WithSeedsBuffer"));
  exports.Set(Napi::String::New(env, "Hash64WithSeedsString"), Napi::Function::New(env, "Hash64WithSeedsString"));
  exports.Set(Napi::String::New(env, "Fingerprint32Buffer"), Napi::Function::New(env, "Fingerprint32Buffer"));
  exports.Set(Napi::String::New(env, "Fingerprint32String"), Napi::Function::New(env, "Fingerprint32String"));
  exports.Set(Napi::String::New(env, "Fingerprint64Buffer"), Napi::Function::New(env, "Fingerprint64Buffer"));
  exports.Set(Napi::String::New(env, "Fingerprint64String"), Napi::Function::New(env, "Fingerprint64String"));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)