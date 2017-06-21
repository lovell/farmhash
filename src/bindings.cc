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
#include <nan.h>
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

NAN_METHOD(Hash32Buffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint32_t hash = util::Hash32(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Hash32String) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t hash = util::Hash32(input);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Hash32WithSeedBuffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
  uint32_t hash = util::Hash32WithSeed(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Hash32WithSeedString) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t seed = Nan::To<uint32_t>(info[1]).FromJust();
  uint32_t hash = util::Hash32WithSeed(input, seed);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Hash64Buffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t hash = util::Hash64(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Hash64String) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t hash = util::Hash64(input);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Hash64WithSeedBuffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t seed = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t hash = util::Hash64WithSeed(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Hash64WithSeedString) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t seed = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t hash = util::Hash64WithSeed(input, seed);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Hash64WithSeedsBuffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t seed1 = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t seed2 = static_cast<uint64_t>(Nan::To<uint32_t>(info[2]).FromJust());
  uint64_t hash = util::Hash64WithSeeds(node::Buffer::Data(buffer), node::Buffer::Length(buffer), seed1, seed2);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Hash64WithSeedsString) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t seed1 = static_cast<uint64_t>(Nan::To<uint32_t>(info[1]).FromJust());
  uint64_t seed2 = static_cast<uint64_t>(Nan::To<uint32_t>(info[2]).FromJust());
  uint64_t hash = util::Hash64WithSeeds(input, seed1, seed2);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

// Fingerprint methods - platform independent

NAN_METHOD(Fingerprint32Buffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint32_t hash = util::Fingerprint32(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Fingerprint32String) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint32_t hash = util::Fingerprint32(input);
  info.GetReturnValue().Set(Nan::New<v8::Uint32>(hash));
}

NAN_METHOD(Fingerprint64Buffer) {
  Nan::HandleScope();
  v8::Local<v8::Object> buffer = info[0].As<v8::Object>();
  uint64_t hash = util::Fingerprint64(node::Buffer::Data(buffer), node::Buffer::Length(buffer));
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

NAN_METHOD(Fingerprint64String) {
  Nan::HandleScope();
  std::string input = *Nan::Utf8String(info[0]);
  uint64_t hash = util::Fingerprint64(input);
  info.GetReturnValue().Set(Nan::New(Uint64ToString(hash)).ToLocalChecked());
}

// Init

NAN_MODULE_INIT(init) {
  Nan::Set(target, Nan::New("Hash32Buffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash32Buffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash32String").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash32String)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash32WithSeedBuffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash32WithSeedBuffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash32WithSeedString").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash32WithSeedString)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64Buffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64Buffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64String").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64String)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64WithSeedBuffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64WithSeedBuffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64WithSeedString").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64WithSeedString)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64WithSeedsBuffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64WithSeedsBuffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Hash64WithSeedsString").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Hash64WithSeedsString)).ToLocalChecked());
  Nan::Set(target, Nan::New("Fingerprint32Buffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Fingerprint32Buffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Fingerprint32String").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Fingerprint32String)).ToLocalChecked());
  Nan::Set(target, Nan::New("Fingerprint64Buffer").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Fingerprint64Buffer)).ToLocalChecked());
  Nan::Set(target, Nan::New("Fingerprint64String").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Fingerprint64String)).ToLocalChecked());
}

#ifdef FARMHASH_LEGACY
NODE_MODULE(farmhash_legacy, init)
#else
NODE_MODULE(farmhash, init)
#endif
