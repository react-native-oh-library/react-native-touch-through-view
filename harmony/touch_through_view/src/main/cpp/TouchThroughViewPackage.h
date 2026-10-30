/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "RNOH/generated/BaseReactNativeTouchThroughViewPackage.h"
#include "TouchThroughViewComponentInstance.h"
#include "TouchThroughWrapperComponentInstance.h"

namespace rnoh {

class TouchThroughViewComponentInstanceFactoryDelegate
    : public ComponentInstanceFactoryDelegate {
 public:
  using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

  ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
    if (ctx.componentName == "R2RTouchThroughView") {
      return std::make_shared<TouchThroughViewComponentInstance>(
          std::move(ctx));
    }
    if (ctx.componentName == "R2RTouchThroughWrapper") {
      return std::make_shared<TouchThroughWrapperComponentInstance>(
          std::move(ctx));
    }
    return nullptr;
  }
};

class TouchThroughViewPackage : public BaseReactNativeTouchThroughViewPackage {
 public:
  using BaseReactNativeTouchThroughViewPackage::
      BaseReactNativeTouchThroughViewPackage;

  ComponentInstanceFactoryDelegate::Shared
  createComponentInstanceFactoryDelegate() override {
    return std::make_shared<TouchThroughViewComponentInstanceFactoryDelegate>();
  }
};

} // namespace rnoh
