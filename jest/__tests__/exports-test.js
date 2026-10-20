/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import * as library from '../../index';
import TouchThroughView from '../../components/TouchThroughView';
import TouchThroughWrapper from '../../components/TouchThroughWrapper';

describe('library public exports', () => {
  it('exports the two documented components', () => {
    expect(Object.keys(library).sort()).toEqual([
      'TouchThroughView',
      'TouchThroughWrapper',
    ]);
  });

  it('exports the same component implementations as the component modules', () => {
    expect(library.TouchThroughView).toBe(TouchThroughView);
    expect(library.TouchThroughWrapper).toBe(TouchThroughWrapper);
  });
});
