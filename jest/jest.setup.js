/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

jest.mock(
  'react-native',
  () => jest.requireActual('./__mocks__/react-native'),
  {
    virtual: true,
  },
);

jest.mock(
  'react-native/Libraries/Utilities/codegenNativeComponent',
  () => ({
    __esModule: true,
    default: jest.requireActual('./__mocks__/react-native')
      .requireNativeComponent,
  }),
  { virtual: true },
);
