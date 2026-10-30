/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <arkui/native_type.h>
#include <memory>
#include "RNOH/arkui/UIInputEventHandler.h"
#include "RNOH/arkui/StackNode.h"
#include "RNOH/generated/components/BaseR2RTouchThroughWrapperComponentInstance.h"
#include <cstdint>
#include <string>

namespace rnoh {

class TouchThroughWrapperComponentInstance
    : public BaseR2RTouchThroughWrapperComponentInstance {
 public:
  explicit TouchThroughWrapperComponentInstance(Context context);

  bool canHandleTouch() const override;
  bool containsPoint(facebook::react::Point const& point) const override;
  bool containsPointInBoundingBox(
      facebook::react::Point const& point) override;
  void onChildInserted(
      ComponentInstance::Shared const& childComponentInstance,
      std::size_t index) override;
  void onChildRemoved(
      ComponentInstance::Shared const& childComponentInstance) override;
  StackNode& getLocalRootArkUINode() override;
  void onCreate() override;
  void releaseTouchThroughSequence(
      int32_t action,
      float windowX,
      float windowY);

 protected:
  void onArkUINodeTouchIntercept(const ArkUI_UIInputEvent* event) override;

 private:
  bool isTouchThroughHitAtPoint(
      TouchTarget::Shared const& target,
      facebook::react::Point const& point) const;
  bool isMarkerTarget(TouchTarget::Shared const& target) const;
  bool isTouchThroughHit(
      ComponentInstance::Shared const& componentInstance,
      float windowX,
      float windowY) const;
  bool isPointInsideMarker(
      ComponentInstance::Shared const& componentInstance,
      float windowX,
      float windowY) const;
  void setAncestorNativeScrollBlocked(
      ComponentInstance::Shared const& componentInstance,
      bool blocked);
  void setDescendantNativeScrollBlocked(
      ComponentInstance::Shared const& componentInstance,
      bool blocked);

  StackNode m_stackNode;
  bool m_isTouchThroughSequenceActive = false;
  int64_t m_traceSequenceId = 0;
  std::shared_ptr<UIInputEventHandler> m_touchHandler;
  static constexpr const char* NATIVE_RESPONDER_BLOCK_ORIGIN =
      "TOUCH_THROUGH";
};

} // namespace rnoh
