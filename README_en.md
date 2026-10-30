> Document Template: v0.4.2

<p align="center">
  <h1 align="center"> <code>react-native-touch-through-view</code> </h1>
</p>

This project is developed based on [react-native-touch-through-view](https://github.com/simonhoss/react-native-touch-through-view).

The version correspondence is as follows:

| Name | Version(Npm Address) | Release Information | Supported RN Version | Supported Autolink | Compile API Version | Community Baseline Version | Source code address |
| ------------ | ------------ | ------------------------------ | ------------- | ------------- | ------------------------ | ------------- | ------------- |
| @react-native-ohos/react-native-touch-through-view | [1.2.1 (in development)](https://www.npmjs.com/package/@react-native-ohos/react-native-touch-through-view) | [GitHub Releases](https://github.com/react-native-oh-library/react-native-touch-through-view/releases) | `0.72.*` / `0.77.*` / `0.82.*` / `0.84.*` / `0.86.*` | Yes | API12+ | 1.2.0-beta.1 | [master](https://github.com/react-native-oh-library/react-native-touch-through-view/tree/master) |

## Introduction

Touch pass-through components for React Native.<br/>
Wrap the upper scroll container with TouchThroughWrapper and use TouchThroughView to mark pass-through areas, allowing touch events in those areas to reach the interactive content underneath.

## Installation

Go to your project directory and run the following commands:

**npm**

```bash
npm install @react-native-ohos/react-native-touch-through-view
```

**yarn**

```bash
yarn add @react-native-ohos/react-native-touch-through-view
```

## Link

|                                      | Supported Autolink | Supported RN Version |
|--------------------------------------|----------------|-----------|
| 1.2.1 | Yes | 0.72 / 0.77 / 0.82 / 0.84 / 0.86 |

Projects using AutoLink must follow the configuration instructions in the Autolinking guide: https://gitcode.com/CPF-RN/ohos_react_native/blob/master/docs/zh-cn/Autolinking.md

If your library version supports Autolink and your project has enabled it, you can skip the ManualLink configuration.

<details>
  <summary>ManualLink: Instructions for manually configuring native dependencies</summary>

Open the `harmony` directory of the OpenHarmony project in DevEco Studio.

### 1. Overrides RN SDK

To ensure that the project uses the same RN SDK version across its dependencies, add an `overrides` field to `oh-package.json5` in the HarmonyOS project root, pointing to the required RN SDK version. The value can be an exact version, a version range, a local HAR package, or a source directory.

For details about this field, see the [official documentation](https://developer.huawei.com/consumer/en/doc/harmonyos-guides-V5/ide-oh-package-json5-V5#en-us_topic_0000001792256137_overrides).

```json
{
  "overrides": {
    "@rnoh/react-native-openharmony": "./react_native_openharmony" // Path to the RN SDK source used by the project
    // "@rnoh/react-native-openharmony" : "./react_native_openharmony.har" // Path to a local HAR package
  }
}
```

### 2. Introducing Native Code

Currently, two methods are available:

- Use the HAR file.
- Directly link to the source code.

Method 1 (recommended): Use the HAR file.

> [!TIP] The HAR package is located in the `harmony` folder of the installed library.

Open `entry/oh-package.json5` and add the following dependency:

```json
"dependencies": {
    "@react-native-ohos/react-native-touch-through-view": "file:../../node_modules/@react-native-ohos/react-native-touch-through-view/harmony/touch_through_view.har"
  }
```

Click the `sync` button in the upper-right corner.

Alternatively, run the following commands in the terminal:

```bash
cd entry
ohpm install
```

Method 2: Directly link to the source code.

> [!TIP] To link the source code directly, see the [source linking instructions](https://gitcode.com/CPF-RN/usage-docs/blob/master/en/link-source-code.md).

### 3. Configuring CMakeLists and Introducing TouchThroughViewPackage

Open `entry/src/main/cpp/CMakeLists.txt` and add:

```diff
project(rnapp)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(RNOH_APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(NODE_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../node_modules")
+ set(OH_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../oh_modules")
set(RNOH_CPP_DIR "${OH_MODULES}/@rnoh/react-native-openharmony/src/main/cpp")
set(LOG_VERBOSITY_LEVEL 1)
set(CMAKE_ASM_FLAGS "-Wno-error=unused-command-line-argument -Qunused-arguments")
set(CMAKE_CXX_FLAGS "-fstack-protector-strong -Wl,-z,relro,-z,now,-z,noexecstack -s -fPIE -pie")
set(WITH_HITRACE_SYSTRACE 1) # for other CMakeLists.txt files to use
add_compile_definitions(WITH_HITRACE_SYSTRACE)

add_subdirectory("${RNOH_CPP_DIR}" ./rn)

# RNOH_BEGIN: manual_package_linking_1
add_subdirectory("../../../../sample_package/src/main/cpp" ./sample-package)
+ add_subdirectory("${OH_MODULES}/@react-native-ohos/react-native-touch-through-view/src/main/cpp" ./touch_through_view)
# RNOH_END: manual_package_linking_1

file(GLOB GENERATED_CPP_FILES "./generated/*.cpp")

add_library(rnoh_app SHARED
    ${GENERATED_CPP_FILES}
    "./PackageProvider.cpp"
    "${RNOH_CPP_DIR}/RNOHAppNapiBridge.cpp"
)
target_link_libraries(rnoh_app PUBLIC rnoh)

# RNOH_BEGIN: manual_package_linking_2
target_link_libraries(rnoh_app PUBLIC rnoh_sample_package)
+ target_link_libraries(rnoh_app PUBLIC rnoh_touch_through_view)
# RNOH_END: manual_package_linking_2
```

Open `entry/src/main/cpp/PackageProvider.cpp` and add:

```diff
#include "RNOH/PackageProvider.h"
#include "SamplePackage.h"
+ #include "TouchThroughViewPackage.h"

using namespace rnoh;

std::vector<std::shared_ptr<Package>> PackageProvider::getPackages(Package::Context ctx) {
    return {
      std::make_shared<SamplePackage>(ctx),
+     std::make_shared<TouchThroughViewPackage>(ctx)
    };
}
```

### 4. Introducing TouchThroughViewPackage to ArkTS

Open `entry/src/main/ets/RNPackagesFactory.ets` and add:

```diff
  ...
+ import TouchThroughViewPackage from '@react-native-ohos/react-native-touch-through-view';

export function createRNPackages(ctx: RNPackageContext): RNPackage[] {
  return [
+    new TouchThroughViewPackage(ctx)
  ];
}
```

</details>

## Running

Click the `sync` button in the upper-right corner.

Alternatively, run the following commands in the terminal:

```bash
cd entry
ohpm install
```

Then build and run the project.

## Constraints

### Compatibility

The content of this document has been verified in the following environments:

1. RNOH: 0.84.1; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;
2. RNOH: 0.82.1; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;
3. RNOH: 0.77.18; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;
4. RNOH: 0.72.96; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;

### Permission Requirements

None.

### API requirements

> [!TIP] This library requires `API12+` for compilation and execution.

## Example

The following code demonstrates a basic usage scenario:

> [!WARNING] The library name used in import statements stays unchanged.

```javascript
import React from "react";
import { Button, ScrollView, StyleSheet, Text, View } from "react-native";
import {
  TouchThroughView,
  TouchThroughWrapper,
} from "react-native-touch-through-view";

const App = () => {
  return (
    <View style={{ flex: 1 }}>
      <View style={{ height: 200, justifyContent: "center" }}>
        <Button title="Bottom button" onPress={() => console.log("Bottom button clicked")} />
      </View>
      <TouchThroughWrapper style={StyleSheet.absoluteFill}>
        <ScrollView>
          <TouchThroughView style={{ height: 200 }} />
          <View style={{ height: 1000, backgroundColor: "white" }}>
            <Text>Upper scroll content</Text>
          </View>
        </ScrollView>
      </TouchThroughWrapper>
    </View>
  );
};

export default App;
```

## How to Use

**Configuring pass-through areas**

Wrap a ScrollView or list with TouchThroughWrapper, place TouchThroughView where touches should pass through, and set the area size with style.

```javascript
<TouchThroughWrapper style={StyleSheet.absoluteFill}>
  <ScrollView>
    <TouchThroughView style={{ height: 200 }} />
    <View style={{ height: 1000 }} />
  </ScrollView>
</TouchThroughWrapper>
```

Gestures starting in a pass-through area are delivered to the underlying components first; gestures starting in normal areas are handled by the upper scroll container.

## Available APIs

> [!TIP] The **Platform** column indicates the platforms supported by the property in the original third-party library.

> [!TIP] In the **OpenHarmony Platform Support** column, **yes** means the property is supported on OpenHarmony, **no** means it is unsupported, and **partially** means it is partially supported. Usage is consistent across platforms, with behavior aligned with iOS or Android.

### Components

| Name | Parameter Type | Required | Platform | OpenHarmony Platform Support | Description |
| ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
| TouchThroughView | ViewProps | yes | iOS, Android | yes | Marks a touch pass-through area. |
| TouchThroughWrapper | ViewProps | yes | iOS, Android | yes | Wraps the upper scroll container and works with TouchThroughView to pass touches to the underlying components. |

### Properties

`ViewProps`

Both components inherit ViewProps and have no custom properties.

### API

None

## Known Issues

None

## Other

None

## Directory Structure

````
/react-native-touch-through-view  # Project root
├── harmony                      # HarmonyOS adaptation code
│   ├── touch_through_view.har    # Native HAR package
│   └── touch_through_view        # Core adaptation code
│       └── src/main
│           ├── ets/Index.ets     # ArkTS package entry
│           └── cpp              # Native component implementations
│               ├── TouchThroughTrace.h
│               ├── TouchThroughViewPackage.h
│               ├── TouchThroughViewComponentInstance.h
│               ├── TouchThroughViewComponentInstance.cpp
│               ├── TouchThroughWrapperComponentInstance.h
│               └── TouchThroughWrapperComponentInstance.cpp
├── components                   # RN components
│   ├── TouchThroughView.js
│   └── TouchThroughWrapper.js
├── specs                        # Codegen definitions
│   ├── TouchThroughViewNativeComponent.ts
│   └── TouchThroughWrapperNativeComponent.ts
├── example                      # Example project
│   ├── src/rnt/TouchThroughViewTest.tsx  # Test page
│   ├── package.json
│   └── package_*.json            # Dependencies for RN 0.72, 0.77, 0.82, 0.84, and 0.86
├── index.js                     # RN entry
├── index.d.ts                   # Type declarations
├── README.md                    # Chinese installation and usage
└── README_en.md                 # English installation and usage
````

## How to Contribute

If you encounter any problems, submit an [Issue](https://github.com/react-native-oh-library/react-native-touch-through-view/issues). Contributions through [PRs](https://github.com/react-native-oh-library/react-native-touch-through-view/pulls) are also welcome.

## License

This project is licensed under the [MIT License](https://github.com/simonhoss/react-native-touch-through-view/blob/master/package.json#L24). Feel free to use and contribute to this open-source project.
