/*
 * Copyright (c) 2026 Huawei Device Co., Ltd. All rights reserved
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import type { HostComponent, ViewProps } from 'react-native';
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';

export interface NativeProps extends ViewProps {}

export default codegenNativeComponent<NativeProps>(
  'R2RTouchThroughWrapper',
) as HostComponent<NativeProps>;
