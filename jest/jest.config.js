/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

const path = require('path');

module.exports = {
  rootDir: path.resolve(__dirname, '..'),
  roots: ['<rootDir>/jest', '<rootDir>/components', '<rootDir>/specs'],
  testEnvironment: 'node',
  testMatch: ['<rootDir>/jest/__tests__/*-test.js'],
  testPathIgnorePatterns: [
    '/node_modules/',
    '<rootDir>/example/',
    '<rootDir>/harmony/',
    '-itest\\.js$',
  ],
  transform: {
    '^.+\\.[jt]sx?$': [
      require.resolve('babel-jest'),
      {
        babelrc: false,
        configFile: path.join(__dirname, 'babel.config.js'),
      },
    ],
  },
  moduleDirectories: ['<rootDir>/jest/node_modules', 'node_modules'],
  moduleNameMapper: {
    '^react$': require.resolve('react'),
    '^prop-types$': require.resolve('prop-types'),
  },
  setupFiles: ['<rootDir>/jest/jest.setup.js'],
  globals: { __DEV__: true },
  clearMocks: true,
  collectCoverageFrom: ['index.js', 'components/*.js'],
  coverageDirectory: '<rootDir>/jest/coverage',
  coverageReporters: ['text', 'lcov', 'json-summary'],
  coverageThreshold: {
    global: {
      branches: 60,
      functions: 80,
      lines: 80,
      statements: 80,
    },
  },
};
