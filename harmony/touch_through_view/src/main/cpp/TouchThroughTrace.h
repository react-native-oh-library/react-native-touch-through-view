/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <arkui/ui_input_event.h>
#include <glog/logging.h>
#include <sstream>
#include <string>

namespace rnoh::touchthroughtrace {

inline constexpr const char* TRACE_TAG = "[TTV_TRACE]";

inline const char* actionName(int32_t action) {
  switch (action) {
    case UI_TOUCH_EVENT_ACTION_DOWN:
      return "DOWN";
    case UI_TOUCH_EVENT_ACTION_UP:
      return "UP";
    case UI_TOUCH_EVENT_ACTION_MOVE:
      return "MOVE";
    case UI_TOUCH_EVENT_ACTION_CANCEL:
      return "CANCEL";
    default:
      return "UNKNOWN";
  }
}

inline const char* boolName(bool value) {
  return value ? "true" : "false";
}

inline std::string pointToString(float x, float y) {
  std::ostringstream ss;
  ss << "(" << x << "," << y << ")";
  return ss.str();
}

inline void logLifecycle(
    const char* phase,
    int64_t seq,
    int tag,
    const std::string& component,
    const void* nodeHandle = nullptr,
    const void* delegate = nullptr) {
  LOG(INFO) << TRACE_TAG << " phase=" << phase << " seq=" << seq
            << " tag=" << tag << " component=" << component
            << " nodeHandle=" << nodeHandle << " delegate=" << delegate;
}

inline void logInterceptProbe(
    int64_t seq,
    int tag,
    const std::string& component,
    int32_t action,
    float localX,
    float localY,
    float windowX,
    float windowY,
    bool localHit,
    bool sequenceActive) {
  LOG(INFO) << TRACE_TAG << " phase=probe"
            << " seq=" << seq
            << " tag=" << tag
            << " component=" << component
            << " action=" << actionName(action)
            << " local=" << pointToString(localX, localY)
            << " window=" << pointToString(windowX, windowY)
            << " localHit=" << boolName(localHit)
            << " active=" << boolName(sequenceActive);
}

inline void logSequenceTransition(
    const char* phase,
    int64_t seq,
    int tag,
    const std::string& component,
    int32_t action,
    float windowX,
    float windowY) {
  LOG(INFO) << TRACE_TAG << " phase=" << phase
            << " seq=" << seq
            << " tag=" << tag
            << " component=" << component
            << " action=" << actionName(action)
            << " window=" << pointToString(windowX, windowY);
}

inline void logScrollBlock(
    const char* phase,
    int64_t seq,
    int ownerTag,
    int targetTag,
    const std::string& targetComponent,
    bool blocked) {
  LOG(INFO) << TRACE_TAG << " phase=" << phase
            << " seq=" << seq
            << " ownerTag=" << ownerTag
            << " targetTag=" << targetTag
            << " targetComponent=" << targetComponent
            << " blocked=" << boolName(blocked);
}

inline void logMarkerState(
    const char* phase,
    int tag,
    const std::string& component,
    const char* hitTestMode) {
  LOG(INFO) << TRACE_TAG << " phase=" << phase
            << " tag=" << tag
            << " component=" << component
            << " hitTestMode=" << hitTestMode;
}

} // namespace rnoh::touchthroughtrace
