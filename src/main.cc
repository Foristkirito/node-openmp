#include <napi.h>
#include "module.hpp"

Napi::String Method(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world");
}

Napi::Number getThreads2( const Napi::CallbackInfo& info ) {
    Napi::Env env = info.Env();
    int threads = getThreads();
    Napi::Number num = Napi::Number::New(env, threads);
    return num;
}

Napi::Value calculatePi(const Napi::CallbackInfo& info ){
    Napi::Env env = info.Env();
    // check for no. of arguments
    if(info.Length()<2){
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    double numThreads = info[0].As<Napi::Number>().DoubleValue();
    double numSteps = info[1].As<Napi::Number>().DoubleValue();
    
    double pi = GetPi(numThreads, numSteps);

    Napi::Number PI = Napi::Number::New(env, pi);

    return PI;
}

Napi::Object Init(Napi::Env env, Napi::Object exports){
    // register the functions that are to be exported    
    exports.Set(Napi::String::New(env, "getThreads"), Napi::Function::New(env, getThreads2));
    exports.Set(Napi::String::New(env, "pi"), Napi::Function::New(env, calculatePi));
    return exports;
}


NODE_API_MODULE(nodeOpenMP, Init);