// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREDICTORS_LOADING_PREDICTOR_ANDROID_H_
#define CHROME_BROWSER_PREDICTORS_LOADING_PREDICTOR_ANDROID_H_

#include <jni.h>

namespace predictors {

bool RegisterLoadingPredictor(JNIEnv* env);

}  // namespace predictors

#endif  // CHROME_BROWSER_PREDICTORS_LOADING_PREDICTOR_ANDROID_H_
