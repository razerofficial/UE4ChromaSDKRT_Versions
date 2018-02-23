## Table of contents

* [See Also](#see-also)
* [Overview](#overview)
* [Supported versions](#supported-versions)
* [Dependencies](#dependencies)

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

* Duplicated the blank plugin sample found at:
```
C:\Program Files\Epic Games\UE_4.5\Engine\Plugins\Developer\BlankPlugin
```

## New Plugin Structure

```
Plugins
Plugins/ChromaSDKPlugin
Plugins/ChromaSDKPlugin/ChromaSDKPlugin.uplugin
Plugins/ChromaSDKPlugin/Resources
Plugins/ChromaSDKPlugin/Resources/Icon128.png
Plugins/ChromaSDKPlugin/Source
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/ChromaSDKPlugin.Build.cs
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Classes
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Classes/ChromaSDKPluginObject.h
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public
Plugins/ChromaSDKPlugin/Source/ChromaSDKPlugin/Public/IChromaSDKPlugin.h
```
