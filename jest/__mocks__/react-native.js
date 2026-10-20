/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

function View() {
  return null;
}

// Also support the unchanged upstream wrappers that use View.propTypes.
View.propTypes = {};

module.exports = {
  View,
  requireNativeComponent: name => name,
};
