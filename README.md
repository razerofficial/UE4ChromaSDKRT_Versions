## Table of contents

* [See Also](#see-also)
* [Overview](#overview)
* [Supported versions](#supported-versions)
* [Dependencies](#dependencies)
* [Status](#status)
* [Plugin Structure](#plugin-structure)
* [Samples](#samples)
* [API](#api)

## See Also

* [ChromaDiscordApp](https://github.com/tgraupmann/ChromaDiscordApp) - Enable Chroma lighting in the Discord App for Windows

* [CChromaEditor](https://github.com/RazerOfficial/CChromaEditor) - Editor for editing Chroma animations

* [ChromaTwitchExtension](https://github.com/tgraupmann/ChromaTwitchExtension) - Adds Chroma lighting to the Twitch streaming experience

* [UE4ChromaSDK](https://github.com/RazerOfficial/UE4ChromaSDK) - UE4 Runtime and Editor modules for the ChromaSDK (requires UE 4.12 or better)

## Overview

`UE4ChromaSDKRT` provides a runtime module for using the `ChromaSDK` (requires UE 4.5.1 or better). The runtime module provides a blueprint library and C++ methods for playing Chroma animations.

## Supported versions

The plugin supports the following UE4 versions:

**UE 4.5.1**

## Dependencies

### UE 4.5.1

UE 4.5.1 requires [Visual Studio 2013](https://www.visualstudio.com/vs/older-downloads/)

![image_1](images/image_1.png)

## Status

* Duplicated the blank plugin sample found at [Engine/Plugins/Developer/BlankPlugin](https://github.com/EpicGames/UnrealEngine/tree/4.5/Engine/Plugins/Developer/BlankPlugin)

## Plugin Structure

```
Plugins/
Plugins/ChromaSDKPlugin/ChromaSDKPlugin.uplugin
Plugins/ChromaSDKPlugin/Resources
Plugins/ChromaSDKPlugin/Resources/Icon128.png
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/ChromaSDKPlugin.Build.cs
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/Animation1D.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/Animation2D.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/AnimationBase.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPlugin.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPluginAnimation1DObject.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPluginAnimation2DObject.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPluginBPLibrary.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPluginPrivatePCH.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaSDKPluginTypes.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Private/ChromaThread.cpp
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/Animation1D.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/Animation2D.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/AnimationBase.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/ChromaSDKPluginAnimation1DObject.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/ChromaSDKPluginAnimation2DObject.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/ChromaSDKPluginBPLibrary.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/ChromaSDKPluginTypes.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/ChromaThread.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/IChromaSDKPlugin.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/RzChromaSDKDefines.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/RzChromaSDKTypes.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/RzErrors.h
```

## Plugin appears in Window->Plugins
![image_1](images/image_2.png)


## Samples

**Animation Sample**

* The animation sample showcases invoking the ChromaSDK `Blueprint Library` from the C++ [Sample BP Library](Source/UE4ChromaSDKRT/SampleBPLibrary.cpp).

![image_3](images/image_3.png)

* Event `BeginPlay` invokes the setup for UI and buttons, and finishes invoking the `SampleStart` BP function.

![image_4](images/image_4.png)

* Event `EndPlay` ends the application by invoking the `SampleEnd` BP function.

![image_5](images/image_5.png)

* The `SetupUI` custom event loads the sample BP Widget and adds the stored widget var to the viewport.

![image_6](images/image_6.png)

* The `AnimationWidget_BP` UI Widget defines the all the button variable names.

![image_8](images/image_8.png)

* The `SetupButtons` custom event manually uses the `Widget` variable to add a click handler for each UI Widget button accessor which invokes the corresponding BP sample function.

![image_7](images/image_7.png)

* The animation sample `Chroma` files are found in the project's content folder. There's a set of `Blank`, `Fire`, and `Random` Chroma animation files. After building the Windows standalone application, the `Chroma` files should be copied to the compiled application content folder.

## API

`UE4ChromaSDKRT` has the same Blueprint API library as [UE4ChromaSDK](https://github.com/RazerOfficial/UE4ChromaSDK#api) with some exceptions to be compatible with earlier versions of UE4.

* Enum syntax - Enums are namespaced and types use the `EChromaSDKKeyboardKey::Type` syntax to avoid collisions.

* No const enum types or passing enums by reference in function parameters - Avoid use of const enum types because that seems to crash in UE 4.5.
