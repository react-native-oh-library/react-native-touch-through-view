/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

module.exports = {
  presets: [
    [
      require.resolve('@babel/preset-env'),
      { targets: { node: 'current' }, modules: 'commonjs' },
    ],
  ],
  plugins: [require.resolve('@babel/plugin-transform-react-jsx')],
  overrides: [
    {
      test: /\.jsx?$/,
      presets: [[require.resolve('@babel/preset-flow'), { all: true }]],
    },
    {
      test: /\.tsx?$/,
      presets: [require.resolve('@babel/preset-typescript')],
    },
  ],
};
