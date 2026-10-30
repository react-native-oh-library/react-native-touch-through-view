/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RNOH/arkui/StackNode.h"
#include "RNOH/generated/components/BaseR2RTouchThroughViewComponentInstance.h"

namespace rnoh {

class TouchThroughViewComponentInstance
    : public BaseR2RTouchThroughViewComponentInstance {
 public:
  explicit TouchThroughViewComponentInstance(Context context);
  void onCreate() override;

  void onChildInserted(
      ComponentInstance::Shared const& childComponentInstance,
      std::size_t index) override;
  void onChildRemoved(
      ComponentInstance::Shared const& childComponentInstance) override;
  StackNode& getLocalRootArkUINode() override;

 protected:
  void onPropsChanged(SharedConcreteProps const& props) override;

 private:
  StackNode m_stackNode;
};

} // namespace rnoh
