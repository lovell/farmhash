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

#include <napi.h>
#include "upstream/farmhash.h"

// Hash methods - platform dependent

Napi::Value Hash32Buffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint32_t hash = util::Hash32(buffer.Data(), buffer.ByteLength());
  return Napi::Number::New(env, hash);
}

Napi::Value Hash32String(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint32_t hash = util::Hash32(input);
  return Napi::Number::New(env, hash);
}

Napi::Value Hash32WithSeedBuffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint32_t seed = info[1].As<Napi::Number>().Uint32Value();
  uint32_t hash = util::Hash32WithSeed(buffer.Data(), buffer.ByteLength(), seed);
  return Napi::Number::New(env, hash);
}

Napi::Value Hash32WithSeedString(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint32_t seed = info[1].As<Napi::Number>().Uint32Value();
  uint32_t hash = util::Hash32WithSeed(input, seed);
  return Napi::Number::New(env, hash);
}

Napi::Value Hash64Buffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint64_t hash = util::Hash64(buffer.Data(), buffer.ByteLength());
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Hash64String(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint64_t hash = util::Hash64(input);
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Hash64WithSeedBuffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint64_t seed = static_cast<uint64_t>(info[1].As<Napi::Number>().Uint32Value());
  uint64_t hash = util::Hash64WithSeed(buffer.Data(), buffer.ByteLength(), seed);
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Hash64WithSeedString(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint64_t seed = static_cast<uint64_t>(info[1].As<Napi::Number>().Uint32Value());
  uint64_t hash = util::Hash64WithSeed(input, seed);
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Hash64WithSeedsBuffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint64_t seed1 = static_cast<uint64_t>(info[1].As<Napi::Number>().Uint32Value());
  uint64_t seed2 = static_cast<uint64_t>(info[2].As<Napi::Number>().Uint32Value());
  uint64_t hash = util::Hash64WithSeeds(buffer.Data(), buffer.ByteLength(), seed1, seed2);
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Hash64WithSeedsString(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint64_t seed1 = static_cast<uint64_t>(info[1].As<Napi::Number>().Uint32Value());
  uint64_t seed2 = static_cast<uint64_t>(info[2].As<Napi::Number>().Uint32Value());
  uint64_t hash = util::Hash64WithSeeds(input, seed1, seed2);
  return Napi::String::New(env, std::to_string(hash));
}

// Fingerprint methods - platform independent

Napi::Value Fingerprint32Buffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint32_t hash = util::Fingerprint32(buffer.Data(), buffer.ByteLength());
  return Napi::Number::New(env, hash);
}

Napi::Value Fingerprint32String(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint32_t hash = util::Fingerprint32(input);
  return Napi::Number::New(env, hash);
}

Napi::Value Fingerprint64Buffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  uint64_t hash = util::Fingerprint64(buffer.Data(), buffer.ByteLength());
  return Napi::String::New(env, std::to_string(hash));
}

Napi::Value Fingerprint64String(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string input = info[0].As<Napi::String>().Utf8Value();
  uint64_t hash = util::Fingerprint64(input);
  return Napi::String::New(env, std::to_string(hash));
}

// Init

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "Hash32Buffer"), Napi::Function::New(env, Hash32Buffer));
  exports.Set(Napi::String::New(env, "Hash32String"), Napi::Function::New(env, Hash32String));
  exports.Set(Napi::String::New(env, "Hash32WithSeedBuffer"), Napi::Function::New(env, Hash32WithSeedBuffer));
  exports.Set(Napi::String::New(env, "Hash32WithSeedString"), Napi::Function::New(env, Hash32WithSeedString));
  exports.Set(Napi::String::New(env, "Hash64Buffer"), Napi::Function::New(env, Hash64Buffer));
  exports.Set(Napi::String::New(env, "Hash64String"), Napi::Function::New(env, Hash64String));
  exports.Set(Napi::String::New(env, "Hash64WithSeedBuffer"), Napi::Function::New(env, Hash64WithSeedBuffer));
  exports.Set(Napi::String::New(env, "Hash64WithSeedString"), Napi::Function::New(env, Hash64WithSeedString));
  exports.Set(Napi::String::New(env, "Hash64WithSeedsBuffer"), Napi::Function::New(env, Hash64WithSeedsBuffer));
  exports.Set(Napi::String::New(env, "Hash64WithSeedsString"), Napi::Function::New(env, Hash64WithSeedsString));
  exports.Set(Napi::String::New(env, "Fingerprint32Buffer"), Napi::Function::New(env, Fingerprint32Buffer));
  exports.Set(Napi::String::New(env, "Fingerprint32String"), Napi::Function::New(env, Fingerprint32String));
  exports.Set(Napi::String::New(env, "Fingerprint64Buffer"), Napi::Function::New(env, Fingerprint64Buffer));
  exports.Set(Napi::String::New(env, "Fingerprint64String"), Napi::Function::New(env, Fingerprint64String));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
