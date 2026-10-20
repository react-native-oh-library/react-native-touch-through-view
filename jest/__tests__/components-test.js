/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import React from 'react';
import { TouchThroughView, TouchThroughWrapper } from '../../index';

function renderComponent(Component, props) {
  const element = React.createElement(Component, props);
  // Exercise either the upstream class wrapper or the Codegen function wrapper.
  if (Component.prototype?.isReactComponent) {
    return new Component(element.props).render();
  }
  return Component(element.props);
}

describe.each([
  ['TouchThroughView', TouchThroughView, 'R2RTouchThroughView'],
  ['TouchThroughWrapper', TouchThroughWrapper, 'R2RTouchThroughWrapper'],
])('%s JS wrapper', (_name, Component, nativeName) => {
  it('renders the expected native component with no optional props', () => {
    const element = renderComponent(Component);

    expect(React.isValidElement(element)).toBe(true);
    expect(element.type).toBe(nativeName);
    expect(element.props).toEqual({});
  });

  it('forwards ViewProps and preserves style array identity', () => {
    const style = [{ width: 120 }, { height: 80, opacity: 0.5 }];
    const element = renderComponent(Component, {
      style,
      testID: 'touch-through-target',
      pointerEvents: 'box-none',
      accessible: true,
      accessibilityLabel: 'Touch through target',
    });

    expect(element.props.style).toBe(style);
    expect(element.props.testID).toBe('touch-through-target');
    expect(element.props.pointerEvents).toBe('box-none');
    expect(element.props.accessible).toBe(true);
    expect(element.props.accessibilityLabel).toBe('Touch through target');
  });

  it('preserves explicit false and null property values', () => {
    const element = renderComponent(Component, {
      accessible: false,
      style: null,
      children: null,
      pointerEvents: 'none',
    });

    expect(element.props.accessible).toBe(false);
    expect(element.props.style).toBeNull();
    expect(element.props.children).toBeNull();
    expect(element.props.pointerEvents).toBe('none');
  });

  it('preserves the identity and order of nested children', () => {
    const children = [
      React.createElement('View', { key: 'first', testID: 'first' }),
      React.createElement('View', { key: 'second', testID: 'second' }),
    ];
    const element = renderComponent(Component, { children });

    expect(element.props.children).toBe(children);
    expect(element.props.children[0]).toBe(children[0]);
    expect(element.props.children[1]).toBe(children[1]);
  });

  it('forwards event callbacks without invoking them during render', () => {
    const onLayout = jest.fn();
    const onTouchStart = jest.fn();
    const element = renderComponent(Component, { onLayout, onTouchStart });

    expect(element.props.onLayout).toBe(onLayout);
    expect(element.props.onTouchStart).toBe(onTouchStart);
    expect(onLayout).not.toHaveBeenCalled();
    expect(onTouchStart).not.toHaveBeenCalled();
  });

  it('does not mutate the supplied props or style object', () => {
    const style = Object.freeze({ width: 120, height: 80 });
    const props = Object.freeze({ style, testID: 'immutable-target' });

    const element = renderComponent(Component, props);

    expect(props).toEqual({
      style: { width: 120, height: 80 },
      testID: 'immutable-target',
    });
    expect(element.props.style).toBe(style);
    expect(element.props.testID).toBe('immutable-target');
  });
});
