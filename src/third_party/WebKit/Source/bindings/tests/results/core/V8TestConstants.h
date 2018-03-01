// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.h.tmpl

// clang-format off
#ifndef V8TestConstants_h
#define V8TestConstants_h

#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/NativeValueTraits.h"
#include "bindings/core/v8/ToV8ForCore.h"
#include "bindings/core/v8/V8BindingForCore.h"
#include "bindings/tests/idls/core/TestConstants.h"
#include "core/CoreExport.h"
#include "platform/bindings/ScriptWrappable.h"
#include "platform/bindings/V8DOMWrapper.h"
#include "platform/bindings/WrapperTypeInfo.h"
#include "platform/heap/Handle.h"

namespace blink {

class ScriptState;
class V8TestConstants {
  STATIC_ONLY(V8TestConstants);
 public:
  CORE_EXPORT static bool hasInstance(v8::Local<v8::Value>, v8::Isolate*);
  static v8::Local<v8::Object> findInstanceInPrototypeChain(v8::Local<v8::Value>, v8::Isolate*);
  CORE_EXPORT static v8::Local<v8::FunctionTemplate> domTemplate(v8::Isolate*, const DOMWrapperWorld&);
  static TestConstants* toImpl(v8::Local<v8::Object> object) {
    return ToScriptWrappable(object)->ToImpl<TestConstants>();
  }
  CORE_EXPORT static TestConstants* toImplWithTypeCheck(v8::Isolate*, v8::Local<v8::Value>);
  CORE_EXPORT static const WrapperTypeInfo wrapperTypeInfo;
  static void Trace(Visitor* visitor, ScriptWrappable* scriptWrappable) {
    visitor->Trace(scriptWrappable->ToImpl<TestConstants>());
  }
  static void TraceWrappers(WrapperVisitor* visitor, ScriptWrappable* scriptWrappable) {
    visitor->TraceWrappers(scriptWrappable->ToImpl<TestConstants>());
  }
  static const int internalFieldCount = kV8DefaultWrapperInternalFieldCount + 0;

  static void installFeatureName1(v8::Isolate*, const DOMWrapperWorld&, v8::Local<v8::Object> instance, v8::Local<v8::Object> prototype, v8::Local<v8::Function> interface);
  static void installFeatureName1(ScriptState*, v8::Local<v8::Object> instance);
  static void installFeatureName1(ScriptState*);

  static void installFeatureName2(v8::Isolate*, const DOMWrapperWorld&, v8::Local<v8::Object> instance, v8::Local<v8::Object> prototype, v8::Local<v8::Function> interface);
  static void installFeatureName2(ScriptState*, v8::Local<v8::Object> instance);
  static void installFeatureName2(ScriptState*);

  // Callback functions
  CORE_EXPORT static void DEPRECATED_CONSTANTConstantGetterCallback(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>&);
  CORE_EXPORT static void MEASURED_CONSTANTConstantGetterCallback(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value>&);
};

template <>
struct NativeValueTraits<TestConstants> : public NativeValueTraitsBase<TestConstants> {
  CORE_EXPORT static TestConstants* NativeValue(v8::Isolate*, v8::Local<v8::Value>, ExceptionState&);
};

template <>
struct V8TypeOf<TestConstants> {
  typedef V8TestConstants Type;
};

}  // namespace blink

#endif  // V8TestConstants_h