#include "common.hpp"

static Napi::Value Initialize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString() || !info[1].IsString()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (const std::string databasePath = info[0].As<Napi::String>().Utf8Value(); !CardManager::getInstance()->initialize(databasePath)) {
        return Napi::Boolean::New(env, false);
    }

    const std::string scriptDirectory = info[1].As<Napi::String>().Utf8Value();
    Replay::setScriptDirectory(scriptDirectory);

    return Napi::Boolean::New(env, true);
}

static Napi::Value ParseReplayFile(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString() && !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    auto filePath = info[0].As<Napi::String>().Utf8Value();
    auto replay = Replay::fromFile(filePath);
    auto jsonValue = replay->parse()->toJSON();

    auto json = env.Global().Get("JSON").As<Napi::Object>();
    auto parse = json.Get("parse").As<Napi::Function>();

    return parse.Call(json, { Napi::String::New(env, jsonValue.dump()) }).As<Napi::Object>();
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "initialize"),Napi::Function::New(env, Initialize));
    exports.Set(Napi::String::New(env, "parse"),Napi::Function::New(env, ParseReplayFile));
    return exports;
}

NODE_API_MODULE(hello, Init)
