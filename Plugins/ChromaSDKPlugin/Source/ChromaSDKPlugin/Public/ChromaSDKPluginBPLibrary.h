// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include <map>
#include "IChromaSDKPlugin.h"
#include "ChromaSDKPluginTypes.h"
#include "ChromaSDKPluginBPLibrary.generated.h"

UCLASS()
class CHROMASDKPLUGIN_API UChromaSDKPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsPlatformWindows", Keywords = "Returns true on the Windows Platform"), Category = "ChromaSDK")
	static bool IsPlatformWindows();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMaxLeds", Keywords = "Get the max led size for the device"), Category = "ChromaSDK")
	static int32 GetMaxLeds(EChromaSDKDevice1DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMaxRow", Keywords = "Get the max row size for the device"), Category = "ChromaSDK")
	static int32 GetMaxRow(EChromaSDKDevice2DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMaxColumn", Keywords = "Get the max column size for the device"), Category = "ChromaSDK")
	static int32 GetMaxColumn(EChromaSDKDevice2DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetRGB", Keywords = "Convert RGB to LinearColor"), Category = "ChromaSDK")
	static FLinearColor GetRGB(int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ToBGR", Keywords = "Convert LinearColor to BGR int"), Category = "ChromaSDK")
	static int32 ToBGR(const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ToLinearColor", Keywords = "Convert BGR int to LinearColor"), Category = "ChromaSDK")
	static FLinearColor ToLinearColor(int32 colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Lerp", Keywords = "Lerp floating point over 0 to 1"), Category = "ChromaSDK")
	static float Lerp(float start, float end, float amt);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LerpColorBGR", Keywords = "Lerp from one color to another over 0 to 1"), Category = "ChromaSDK")
	static int32 LerpColorBGR(int32 from, int32 to, float t);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LerpColor", Keywords = "Lerp from one color to another over 0 to 1"), Category = "ChromaSDK")
	static FLinearColor LerpColor(FLinearColor colorParam1, FLinearColor colorParam2, float t);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateColors1D", Keywords = "Create a blank one-dimensional color array"), Category = "ChromaSDK")
	static TArray<FLinearColor> CreateColors1D(EChromaSDKDevice1DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateColors2D", Keywords = "Create a blank two-dimensional color array"), Category = "ChromaSDK")
	static TArray<FChromaSDKColors> CreateColors2D(EChromaSDKDevice2DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColors1D", Keywords = "Create a random one-dimensional color array"), Category = "ChromaSDK")
	static TArray<FLinearColor> CreateRandomColors1D(EChromaSDKDevice1DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColors2D", Keywords = "Create a random two-dimensional color array"), Category = "ChromaSDK")
	static TArray<FChromaSDKColors> CreateRandomColors2D(EChromaSDKDevice2DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColorsBlackAndWhite1D", Keywords = "Create a random one-dimensional black and white color array"), Category = "ChromaSDK")
	static TArray<FLinearColor> CreateRandomColorsBlackAndWhite1D(EChromaSDKDevice1DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColorsBlackAndWhite2D", Keywords = "Create a random two-dimensional black and white color array"), Category = "ChromaSDK")
	static TArray<FChromaSDKColors> CreateRandomColorsBlackAndWhite2D(EChromaSDKDevice2DEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyboardKeyColor", Keywords = "Set the key to the supplied color"), Category = "ChromaSDK")
	static void SetKeyboardKeyColor(EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyboardKeyColor", Keywords = "Get the key to the supplied color"), Category = "ChromaSDK")
	static FLinearColor GetKeyboardKeyColor(EChromaSDKKeyboardKey::Type key, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetMouseLedColor", Keywords = "Set the led to the supplied color"), Category = "ChromaSDK")
	static void SetMouseLedColor(EChromaSDKMouseLed::Type led, const FLinearColor& colorParam, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMouseLedColor", Keywords = "Get the led to the supplied color"), Category = "ChromaSDK")
	static FLinearColor GetMouseLedColor(EChromaSDKMouseLed::Type led, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsInitialized", Keywords = "Return true if the blueprint library is initialized"), Category = "ChromaSDK")
	static bool IsInitialized();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init", Keywords = "Initialize the ChromaSDK"), Category = "ChromaSDK")
	static int32 ChromaSDKInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnInit", Keywords = "Uninitialize the ChromaSDK"), Category = "ChromaSDK")
	static int32 ChromaSDKUnInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectNone", Keywords = "Clear the color effect"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectNone(EChromaSDKDeviceEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectStatic", Keywords = "Create a static color effect"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::Type device, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectCustom1D", Keywords = "Create a custom color effect using one-dimensional array"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectCustom1D(EChromaSDKDevice1DEnum::Type device, const TArray<FLinearColor>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectCustom2D", Keywords = "Create a custom color effect using two-dimensional array"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectCustom2D(EChromaSDKDevice2DEnum::Type device, const TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectKeyboardCustom2D", Keywords = "Create a custom color keyboard effect using two-dimensional array"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectKeyboardCustom2D(const TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetEffect", Keywords = "Set Effect with Effect Id"), Category = "ChromaSDK")
	static int32 ChromaSDKSetEffect(const FChromaSDKGuid& effectId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DeleteEffect", Keywords = "Delete Effect with Effect Id"), Category = "ChromaSDK")
	static int32 ChromaSDKDeleteEffect(const FChromaSDKGuid& effectId);


	// library methods

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAnimation", Keywords = "Get the animation by name from disk or cache"), Category = "ChromaSDK")
	static int32 GetAnimation(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAnimationId", Keywords = "Get the animation id"), Category = "ChromaSDK")
	static int32 GetAnimationId(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAnimationName", Keywords = "Get the animation name"), Category = "ChromaSDK")
	static FString GetAnimationName(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadAnimation", Keywords = "Load the *.chroma Animation"), Category = "ChromaSDK")
	static void LoadAnimation(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadAnimationName", Keywords = "Load the *.chroma Animation"), Category = "ChromaSDK")
	static void LoadAnimationName(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CloseAnimation", Keywords = "Close the *.chroma Animation"), Category = "ChromaSDK")
	static void CloseAnimation(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CloseAnimationName", Keywords = "Close the *.chroma Animation"), Category = "ChromaSDK")
	static void CloseAnimationName(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnloadAnimation", Keywords = "Unload the *.chroma Animation"), Category = "ChromaSDK")
	static void UnloadAnimation(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnloadAnimationName", Keywords = "Unload the *.chroma Animation"), Category = "ChromaSDK")
	static void UnloadAnimationName(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimation", Keywords = "Play the *.chroma Animation"), Category = "ChromaSDK")
	static void PlayAnimation(const FString& animationName, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimationName", Keywords = "Play the *.chroma Animation"), Category = "ChromaSDK")
	static void PlayAnimationName(const FString& animationName, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimation", Keywords = "Stop the *.chroma Animation"), Category = "ChromaSDK")
	static void StopAnimation(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimationType", Keywords = "Stop playing the Animation type"), Category = "ChromaSDK")
	static void StopAnimationType(EChromaSDKDeviceEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAll", Keywords = "Stop playing all animations"), Category = "ChromaSDK")
	static void StopAll();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ClearAnimationType", Keywords = "Clear the device"), Category = "ChromaSDK")
	static void ClearAnimationType(EChromaSDKDeviceEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ClearAll", Keywords = "Clear all devices"), Category = "ChromaSDK")
	static void ClearAll();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAnimationCount", Keywords = "Get the number of open animations"), Category = "ChromaSDK")
	static int32 GetAnimationCount();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAnimationIdByIndex", Keywords = "Get the animationId for the open animation index"), Category = "ChromaSDK")
	static int32 GetAnimationIdByIndex(int32 index);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetPlayingAnimationCount", Keywords = "Get the number of playing animations"), Category = "ChromaSDK")
	static int32 GetPlayingAnimationCount();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetPlayingAnimationId", Keywords = "Get the animationId for the playing animation index"), Category = "ChromaSDK")
	static int32 GetPlayingAnimationId(int32 index);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsAnimationPlaying", Keywords = "Is the *.chroma Animation playing?"), Category = "ChromaSDK")
	static bool IsAnimationPlaying(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsAnimationTypePlaying", Keywords = "Is the Animation type playing?"), Category = "ChromaSDK")
	static bool IsAnimationTypePlaying(EChromaSDKDeviceEnum::Type device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimations", Keywords = "Play an array of *.chroma Animations"), Category = "ChromaSDK")
	static void PlayAnimations(const TArray<FString>& animationNames, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimations", Keywords = "Stop an array *.chroma Animations"), Category = "ChromaSDK")
	static void StopAnimations(const TArray<FString>& animationNames);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimationComposite", Keywords = "Play a set of *_Device.chroma Animations"), Category = "ChromaSDK")
	static void PlayAnimationComposite(const FString& animationName, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimationComposite", Keywords = "Stop a set of *_Device.chroma Animations"), Category = "ChromaSDK")
	static void StopAnimationComposite(const FString& animationName);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyColor", Keywords = "Get the color from the animation frame's key"), Category = "ChromaSDK")
	static FLinearColor GetKeyColor(int32 animationId, int32 frameIndex, EChromaSDKKeyboardKey::Type key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyColorName", Keywords = "Get the color from the animation frame's key"), Category = "ChromaSDK")
	static FLinearColor GetKeyColorName(const FString& animationName, const int32 frameIndex, EChromaSDKKeyboardKey::Type key);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColor", Keywords = "Set the animation frame's key to the supplied color"), Category = "ChromaSDK")
	static void SetKeyColor(int32 animationId, int32 frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorName", Keywords = "Set the animation frame's key to the supplied color"), Category = "ChromaSDK")
	static void SetKeyColorName(const FString& animationName, const int32 frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyNonZeroColor", Keywords = "Set the animation frame's key to the supplied color if the key is not already black"), Category = "ChromaSDK")
	static void SetKeyNonZeroColor(int32 animationId, int32 frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyNonZeroColorName", Keywords = "Set the animation frame's key to the supplied color if the key is not already black"), Category = "ChromaSDK")
	static void SetKeyNonZeroColorName(const FString& animationName, const int32 frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColor", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
	static void SetKeysColor(int32 animationId, int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorName", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
	static void SetKeysColorName(const FString& animationName, const int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorRGB", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
	static void SetKeysColorRGB(int32 animationId, int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorRGBName", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
	static void SetKeysColorRGBName(const FString& animationName, const int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysNonZeroColor", Keywords = "Set the animation frame to the supplied color for a set of keys if the key is not already black"), Category = "ChromaSDK")
	static void SetKeysNonZeroColor(int32 animationId, int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysNonZeroColorName", Keywords = "Set the animation frame to the supplied color for a set of keys if the key is not already black"), Category = "ChromaSDK")
	static void SetKeysNonZeroColorName(const FString& animationName, const int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);
	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorAllFrames", Keywords = "Set the key to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeyColorAllFrames(int32 animationId, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorAllFramesName", Keywords = "Set the key to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeyColorAllFramesName(const FString& animationName, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyNonZeroColorAllFrames", Keywords = "Set the key to the supplied color for all animation frames if the key is not already black"), Category = "ChromaSDK")
	static void SetKeyNonZeroColorAllFrames(int32 animationId, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyNonZeroColorAllFramesName", Keywords = "Set the key to the supplied color for all animation frames if the key is not already black"), Category = "ChromaSDK")
	static void SetKeyNonZeroColorAllFramesName(const FString& animationName, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFrames", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeysColorAllFrames(int32 animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFramesName", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeysColorAllFramesName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFramesRGB", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeysColorAllFramesRGB(int32 animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFramesRGBName", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeysColorAllFramesRGBName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysNonZeroColorAllFrames", Keywords = "Set the keys to the supplied color for all animation frames if the key is not already black"), Category = "ChromaSDK")
	static void SetKeysNonZeroColorAllFrames(int32 animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysNonZeroColorAllFramesName", Keywords = "Set the keys to the supplied color for all animation frames if the key is not already black"), Category = "ChromaSDK")
	static void SetKeysNonZeroColorAllFramesName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam);


	// COPY ANIMATION

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAnimation", Keywords = "Copy animation to the named animation"), Category = "ChromaSDK")
	static void CopyAnimation(int32 sourceAnimationId, const FString& targetAnimationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAnimationName", Keywords = "Copy animation to the named animation"), Category = "ChromaSDK")
	static void CopyAnimationName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// APPEND

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AppendAllFrames", Keywords = "Append animation frames to another animation"), Category = "ChromaSDK")
	static void AppendAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AppendAllFramesName", Keywords = "Append animation frames to another animation"), Category = "ChromaSDK")
	static void AppendAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// INVERT COLORS

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InvertColorsAllFrames", Keywords = "Invert animation colors"), Category = "ChromaSDK")
	static void InvertColorsAllFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InvertColorsAllFramesName", Keywords = "Invert animation colors"), Category = "ChromaSDK")
	static void InvertColorsAllFramesName(const FString& animationName);


	// COPY KEY COLOR

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeyColor", Keywords = "Copy color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyKeyColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, EChromaSDKKeyboardKey::Type key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeyColorName", Keywords = "Copy color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, EChromaSDKKeyboardKey::Type key);

	
	// NONZERO

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeyColor", Keywords = "Copy nonzero color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyNonZeroKeyColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, EChromaSDKKeyboardKey::Type key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeyColorName", Keywords = "Copy nonzero color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyNonZeroKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, EChromaSDKKeyboardKey::Type key);


	// COPY KEYS COLOR

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColor", Keywords = "Copy color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
	static void CopyKeysColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorName", Keywords = "Copy color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
	static void CopyKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);

	// NONZERO

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColor", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
	static void CopyNonZeroKeysColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorName", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
	static void CopyNonZeroKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);


	// COPY KEYS COLOR ALL FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorAllFrames", Keywords = "Copy color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
	static void CopyKeysColorAllFrames(int32 sourceAnimationId, int32 targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorAllFramesName", Keywords = "Copy color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
	static void CopyKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);

	
	// NONZERO	

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorAllFrames", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroKeysColorAllFrames(int32 sourceAnimationId, int32 targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorAllFramesName", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys);


	// COPY ALL KEYS

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAllKeys", Keywords = "Copy color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAllKeysName", Keywords = "Copy color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId);


	// NONZERO

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeys", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysName", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId);


	// NONZERO ADD

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeys", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void AddNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeysName", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void AddNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId);


	// NONZERO SUBTRACT

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeys", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeysName", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId);


	// NONZERO TARGET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeys", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysName", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId);


	// NONZERO OFFSET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysOffset", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 frameId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysOffsetName", Keywords = "Copy nonzero color from a source animation to a target animation for a frame"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameId, int32 offset);


	// COPY ALL KEYS ALL FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAllKeysAllFrames", Keywords = "Copy color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyAllKeysAllFramesName", Keywords = "Copy color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// NONZERO

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysAllFrames", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysAllFramesName", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);

	
	// NONZERO ADD

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeysAllFrames", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeysAllFramesName", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);

	
	// NONZERO SUBTRACT

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeysAllFrames", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeysAllFramesName", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// NONZERO TARGET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroTargetAllKeysAllFrames", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroTargetAllKeysAllFramesName", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// ADD NONZERO TARGET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroTargetAllKeysAllFrames", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroTargetAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroTargetAllKeysAllFramesName", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroTargetAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// SUBTRACT NONZERO TARGET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroTargetAllKeysAllFrames", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroTargetAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroTargetAllKeysAllFramesName", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroTargetAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName);


	// NONZERO TARGET OFFSET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroTargetAllKeysAllFramesOffset", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroTargetAllKeysAllFramesOffsetName", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroTargetAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// ADD NONZERO TARGET OFFSET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroTargetAllKeysAllFramesOffset", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroTargetAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroTargetAllKeysAllFramesOffsetName", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroTargetAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// SUBTRACT NONZERO TARGET OFFSET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroTargetAllKeysAllFramesOffset", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroTargetAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroTargetAllKeysAllFramesOffsetName", Keywords = "Subtract nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroTargetAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// NONZERO OFFSET

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysAllFramesOffset", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroAllKeysAllFramesOffsetName", Keywords = "Copy nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void CopyNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// NONZERO OFFSET ADD

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeysAllFramesOffset", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddNonZeroAllKeysAllFramesOffsetName", Keywords = "Add nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void AddNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// NONZERO OFFSET SUBTRACT

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeysAllFramesOffset", Keywords = "Remove nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SubtractNonZeroAllKeysAllFramesOffsetName", Keywords = "Remove nonzero color from a source animation to a target animation for all frames"), Category = "ChromaSDK")
	static void SubtractNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset);


	// FILL COLOR


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColor", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillColor(int32 animationId, int32 frameId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorName", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillColorName(const FString& animationName, int32 frameId, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorRGB", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillColorRGB(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorRGBName", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillColorRGBName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);

	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsRGB", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillThresholdColorsRGB(int32 animationId, int32 frameId, int32 threshold, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsRGBName", Keywords = "Set the RGB value for all colors in the specified frame"), Category = "ChromaSDK")
	static void FillThresholdColorsRGBName(const FString& animationName, int32 frameId, int32 threshold, int32 red, int32 green, int32 blue);


	// NONZERO COLOR


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColor", Keywords = "Set the RGB value for all nonzero colors in the specified frame"), Category = "ChromaSDK")
	static void FillNonZeroColor(int32 animationId, int32 frameId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorName", Keywords = "Set the RGB value for all nonzero colors in the specified frame"), Category = "ChromaSDK")
	static void FillNonZeroColorName(const FString& animationName, int32 frameId, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroNonColorRGB", Keywords = "Set the RGB value for all nonzero colors in the specified frame"), Category = "ChromaSDK")
	static void FillNonZeroColorRGB(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorRGBName", Keywords = "Set the RGB value for all nonzero colors in the specified frame"), Category = "ChromaSDK")
	static void FillNonZeroColorRGBName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);


	// ZERO COLOR


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColor", Keywords = "Set the RGB value for all zero colors in the specified frame"), Category = "ChromaSDK")
	static void FillZeroColor(int32 animationId, int32 frameId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorName", Keywords = "Set the RGB value for all zero colors in the specified frame"), Category = "ChromaSDK")
	static void FillZeroColorName(const FString& animationName, int32 frameId, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorRGB", Keywords = "Set the RGB value for all zero colors in the specified frame"), Category = "ChromaSDK")
	static void FillZeroColorRGB(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorRGBName", Keywords = "Set the RGB value for all zero colors in the specified frame"), Category = "ChromaSDK")
	static void FillZeroColorRGBName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);


	// FILL THRESHOLD COLORS ALL FRAMES


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsAllFrames", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsAllFrames(int32 animationId, int32 threshold, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsAllFramesName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsAllFramesName(const FString& animationName, int32 threshold, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsAllFramesRGB", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsAllFramesRGB(int32 animationId, int32 threshold, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsAllFramesRGBName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsAllFramesRGBName(const FString& animationName, int32 threshold, int32 red, int32 green, int32 blue);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdRGBColorsAllFramesRGB", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdRGBColorsAllFramesRGB(int32 animationId, int32 redThreshold, int32 greenThreshold, int32 blueThreshold, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdRGBColorsAllFramesRGBName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdRGBColorsAllFramesRGBName(const FString& animationName, int32 redThreshold, int32 greenThreshold, int32 blueThreshold, int32 red, int32 green, int32 blue);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsMinMaxAllFramesRGB", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsMinMaxAllFramesRGB(int32 animationId, int32 minThreshold, int32 minRed, int32 minGreen, int32 minBlue, int32 maxThreshold, int32 maxRed, int32 maxGreen, int32 maxBlue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillThresholdColorsMinMaxAllFramesRGBName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillThresholdColorsMinMaxAllFramesRGBName(const FString& animationName, int32 minThreshold, int32 minRed, int32 minGreen, int32 minBlue, int32 maxThreshold, int32 maxRed, int32 maxGreen, int32 maxBlue);


	// FILL COLOR ALL FRAMES


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorAllFrames", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillColorAllFrames(int32 animationId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorAllFramesName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillColorAllFramesName(const FString& animationName, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorAllFramesRGB", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillColorAllFramesRGB(int32 animationId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillColorAllFramesRGBName", Keywords = "Set the RGB value for all colors for all frames"), Category = "ChromaSDK")
	static void FillColorAllFramesRGBName(const FString& animationName, int32 red, int32 green, int32 blue);


	// NONZERO COLOR


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorAllFrames", Keywords = "Set the RGB value for all colors for all frames if the destination color is not black"), Category = "ChromaSDK")
	static void FillNonZeroColorAllFrames(int32 animationId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorAllFramesName", Keywords = "Set the RGB value for all colors for all frames if the destination color is not black"), Category = "ChromaSDK")
	static void FillNonZeroColorAllFramesName(const FString& animationName, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorAllFramesRGB", Keywords = "Set the RGB value for all colors for all frames if the destination color is not black"), Category = "ChromaSDK")
	static void FillNonZeroColorAllFramesRGB(int32 animationId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillNonZeroColorAllFramesRGBName", Keywords = "Set the RGB value for all colors for all frames if the destination color is not black"), Category = "ChromaSDK")
	static void FillNonZeroColorAllFramesRGBName(const FString& animationName, int32 red, int32 green, int32 blue);


	// ZERO COLORS


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorAllFrames", Keywords = "Set the RGB value for all zero colors in all frames"), Category = "ChromaSDK")
	static void FillZeroColorAllFrames(int32 animationId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorAllFramesName", Keywords = "Set the RGB value for all zero colors in all frames"), Category = "ChromaSDK")
	static void FillZeroColorAllFramesName(const FString& animationName, const FLinearColor& colorParam);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorAllFramesRGB", Keywords = "Set the RGB value for all zero colors in all frames"), Category = "ChromaSDK")
	static void FillZeroColorAllFramesRGB(int32 animationId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillZeroColorAllFramesRGBName", Keywords = "Set the RGB value for all zero colors in all frames"), Category = "ChromaSDK")
	static void FillZeroColorAllFramesRGBName(const FString& animationName, int32 red, int32 green, int32 blue);


	// FILL RANDOM COLORS

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColors", Keywords = "Fill the frame with random colors"), Category = "ChromaSDK")
	static void FillRandomColors(int32 animationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsName", Keywords = "Fill the frame with random colors"), Category = "ChromaSDK")
	static void FillRandomColorsName(const FString& animationName, int32 frameId);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsAllFrames", Keywords = "Fill all frames with random colors"), Category = "ChromaSDK")
	static void FillRandomColorsAllFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsAllFramesName", Keywords = "Fill all frames with random colors"), Category = "ChromaSDK")
	static void FillRandomColorsAllFramesName(const FString& animationName);


	// FILL RANDOM BLACK AND WHITE


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsBlackAndWhite", Keywords = "Fill the frame with random black and white colors"), Category = "ChromaSDK")
	static void FillRandomColorsBlackAndWhite(int32 animationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsBlackAndWhiteName", Keywords = "Fill the frame with random black and white colors"), Category = "ChromaSDK")
	static void FillRandomColorsBlackAndWhiteName(const FString& animationName, int32 frameId);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsBlackAndWhiteAllFrames", Keywords = "Fill all frames with random black and white colors"), Category = "ChromaSDK")
	static void FillRandomColorsBlackAndWhiteAllFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FillRandomColorsBlackAndWhiteAllFramesName", Keywords = "Fill all frames with random black and white colors"), Category = "ChromaSDK")
	static void FillRandomColorsBlackAndWhiteAllFramesName(const FString& animationName);


	// OFFSET COLORS


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetColors", Keywords = "Offset all colors in the frame using the RGB offset"), Category = "ChromaSDK")
	static void OffsetColors(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetColorsName", Keywords = "Offset all colors in the frame using the RGB offset"), Category = "ChromaSDK")
	static void OffsetColorsName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetColorsAllFrames", Keywords = "Offset all colors for all frames using the RGB offset"), Category = "ChromaSDK")
	static void OffsetColorsAllFrames(int32 animationId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetColorsAllFramesName", Keywords = "Offset all colors for all frames using the RGB offset"), Category = "ChromaSDK")
	static void OffsetColorsAllFramesName(const FString& animationName, int32 red, int32 green, int32 blue);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetNonZeroColors", Keywords = "Offset all colors in the frame using the RGB offset if the destination color is not black"), Category = "ChromaSDK")
	static void OffsetNonZeroColors(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetNonZeroColorsName", Keywords = "Offset all colors in the frame using the RGB offset if the destination color is not black"), Category = "ChromaSDK")
	static void OffsetNonZeroColorsName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetNonZeroColorsAllFrames", Keywords = "Offset all colors for all frames using the RGB offset if the destination color is not black"), Category = "ChromaSDK")
	static void OffsetNonZeroColorsAllFrames(int32 animationId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OffsetNonZeroColorsAllFramesName", Keywords = "Offset all colors for all frames using the RGB offset if the destination color is not black"), Category = "ChromaSDK")
	static void OffsetNonZeroColorsAllFramesName(const FString& animationName, int32 red, int32 green, int32 blue);


	// MULTIPLY INTENSITY

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensity", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensity(int32 animationId, int32 frameId, float intensity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityName", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityName(const FString& animationName, int32 frameId, float intensity);


	// MULTIPLY INTENSITY RGB

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensity", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityRGB(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityName", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityRGBName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue);


	// MULTIPLY INTENSITY COLOR

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityColor", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityColor(int32 animationId, int32 frameId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityColorName", Keywords = "Multiply all the colors in the frame by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityColorName(const FString& animationName, int32 frameId, const FLinearColor& colorParam);


	// MULTIPLY INTENSITY ALL FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityAllFrames", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityAllFrames(int32 animationId, float intensity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityAllFramesName", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityAllFramesName(const FString& animationName, float intensity);


	// MULTIPLY INTENSITY COLOR ALL FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityColorAllFrames", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityColorAllFrames(int32 animationId, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityColorAllFramesName", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityColorAllFramesName(const FString& animationName, const FLinearColor& colorParam);


	// RGB

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityAllFramesRGB", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityAllFramesRGB(int32 animationId, float redIntensity, float greenIntensity, float blueIntensity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyIntensityAllFramesRGBName", Keywords = "Multiply all the colors for all frames by the intensity value"), Category = "ChromaSDK")
	static void MultiplyIntensityAllFramesRGBName(const FString& animationName, float redIntensity, float greenIntensity, float blueIntensity);


	// LERP

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyColorLerpAllFrames", Keywords = "Lerp between colors using the frame ratio as the intensity"), Category = "ChromaSDK")
	static void MultiplyColorLerpAllFrames(int32 animationId, const FLinearColor& colorParam1, const FLinearColor& colorParam2);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyColorLerpAllFramesName", Keywords = "Lerp between colors using the frame ratio as the intensity"), Category = "ChromaSDK")
	static void MultiplyColorLerpAllFramesName(const FString& animationName, const FLinearColor& colorParam1, const FLinearColor& colorParam2);


	// TARGET LERP

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyTargetColorLerpAllFrames", Keywords = "Lerp between colors using the target colors as the intensity"), Category = "ChromaSDK")
	static void MultiplyTargetColorLerpAllFrames(int32 animationId, const FLinearColor& colorParam1, const FLinearColor& colorParam2);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyTargetColorLerpAllFramesName", Keywords = "Lerp between colors using the target colors as the intensity"), Category = "ChromaSDK")
	static void MultiplyTargetColorLerpAllFramesName(const FString& animationName, const FLinearColor& colorParam1, const FLinearColor& colorParam2);


	// NON ZERO

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyNonZeroTargetColorLerpAllFrames", Keywords = "Lerp between colors using the nonzero target colors as the intensity"), Category = "ChromaSDK")
	static void MultiplyNonZeroTargetColorLerpAllFrames(int32 animationId, const FLinearColor& colorParam1, const FLinearColor& colorParam2);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MultiplyNonZeroTargetColorLerpAllFramesName", Keywords = "Lerp between colors using the nonzero target colors as the intensity"), Category = "ChromaSDK")
	static void MultiplyNonZeroTargetColorLerpAllFramesName(const FString& animationName, const FLinearColor& colorParam1, const FLinearColor& colorParam2);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetFrameCount", Keywords = "Get the .chroma animation frame count"), Category = "ChromaSDK")
	static int32 GetFrameCount(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetFrameCountName", Keywords = "Get the .chroma animation frame count"), Category = "ChromaSDK")
	static int32 GetFrameCountName(const FString& animationName);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetChromaCustomFlagName", Keywords = "Set the Chroma custom flag for keyboard"), Category = "ChromaSDK")
	static void SetChromaCustomFlagName(const FString& animationName, bool flag);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetChromaCustomColorAllFramesName", Keywords = "Set the custom color mask on all the colors"), Category = "ChromaSDK")
	static void SetChromaCustomColorAllFramesName(const FString& animationName);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PreviewFrame", Keywords = "Display a specific animation frame"), Category = "ChromaSDK")
	static int32 PreviewFrame(int32 animationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PreviewFrameName", Keywords = "Display a specific animation frame"), Category = "ChromaSDK")
	static void PreviewFrameName(const FString& animationName, int32 frameId);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OverrideFrameDurationName", Keywords = "Set the Chroma custom flag for keyboard"), Category = "ChromaSDK")
	static void OverrideFrameDurationName(const FString& animationName, float duration);

	// MAKE FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFrames", Keywords = "Make sure animation has the number of blank frames"), Category = "ChromaSDK")
	static void MakeBlankFrames(int32 animationId, int32 frameCount, float duration, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesName", Keywords = "Make sure animation has the number of blank frames"), Category = "ChromaSDK")
	static void MakeBlankFramesName(const FString& animationName, int32 frameCount, float duration, const FLinearColor& colorParam);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRGB", Keywords = "Make sure animation has the number of blank frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRGB(int32 animationId, int32 frameCount, float duration, int32 red, int32 green, int32 blue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRGBName", Keywords = "Make sure animation has the number of blank frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRGBName(const FString& animationName, int32 frameCount, float duration, int32 red, int32 green, int32 blue);

	// RANDOM

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRandom", Keywords = "Make sure animation has the number of random color frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRandom(int32 animationId, int32 frameCount, float duration);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRandomName", Keywords = "Make sure animation has the number of random color frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRandomName(const FString& animationName, int32 frameCount, float duration);

	// RANDOM BLACK AND WHITE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRandomBlackAndWhite", Keywords = "Make sure animation has the number of random black and white frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRandomBlackAndWhite(int32 animationId, int32 frameCount, float duration);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeBlankFramesRandomBlackAndWhiteName", Keywords = "Make sure animation has the number of random black and white frames"), Category = "ChromaSDK")
	static void MakeBlankFramesRandomBlackAndWhiteName(const FString& animationName, int32 frameCount, float duration);


	// REVERSE ALL FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ReverseAllFrames", Keywords = "Reverse the order of all frames"), Category = "ChromaSDK")
	static void ReverseAllFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ReverseAllFramesName", Keywords = "Reverse the order of all frames"), Category = "ChromaSDK")
	static void ReverseAllFramesName(const FString& animationName);


	// DUPLICATE FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateFrames", Keywords = "Double the number of frames"), Category = "ChromaSDK")
	static void DuplicateFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateFramesName", Keywords = "Double the number of frames"), Category = "ChromaSDK")
	static void DuplicateFramesName(const FString& animationName);


	// DUPLICATE FIRST FRAME

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateFirstFrame", Keywords = "Duplicate the first frame for total the number of frames"), Category = "ChromaSDK")
	static void DuplicateFirstFrame(int32 animationId, int32 frameCount);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateFirstFrameName", Keywords = "Duplicate the first frame for total the number of frames"), Category = "ChromaSDK")
	static void DuplicateFirstFrameName(const FString& animationName, int32 frameCount);


	// DUPLICATE MIRROR FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateMirrorFrames", Keywords = "Duplicate and mirror the animation"), Category = "ChromaSDK")
	static void DuplicateMirrorFrames(int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DuplicateMirrorFramesName", Keywords = "Duplicate and mirror the animation"), Category = "ChromaSDK")
	static void DuplicateMirrorFramesName(const FString& animationName);


	// INSERT FRAME

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InsertFrame", Keywords = "Insert a copy of the frame at the given target frame index"), Category = "ChromaSDK")
	static void InsertFrame(int32 animationId, int32 sourceFrame, int32 targetFrame);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InsertFrameName", Keywords = "Insert a copy of the frame at the given target frame index"), Category = "ChromaSDK")
	static void InsertFrameName(const FString& animationName, int32 sourceFrame, int32 targetFrame);


	// INSERT DELAY

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InsertDelay", Keywords = "Duplicate frames to create a delay at the frame index"), Category = "ChromaSDK")
	static void InsertDelay(int32 animationId, int32 frameId, int32 delay);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InsertDelayName", Keywords = "Duplicate frames to create a delay at the frame index"), Category = "ChromaSDK")
	static void InsertDelayName(const FString& animationName, int32 frameId, int32 delay);


	// REDUCE FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ReduceFrames", Keywords = "Reduce every nth frame"), Category = "ChromaSDK")
	static void ReduceFrames(int32 animationId, int32 n);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ReduceFramesName", Keywords = "Reduce every nth frame"), Category = "ChromaSDK")
	static void ReduceFramesName(const FString& animationName, int32 n);


	// TRIM FRAME

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimFrame", Keywords = "Remove the given frame"), Category = "ChromaSDK")
	static void TrimFrame(int32 animationId, int32 frameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimFrameName", Keywords = "Remove the given frame"), Category = "ChromaSDK")
	static void TrimFrameName(const FString& animationName, int32 frameId);


	// TRIM START FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimStartFrames", Keywords = "Trim the start of the animation"), Category = "ChromaSDK")
	static void TrimStartFrames(int32 animationId, int32 numberOfFrames);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimStartFramesName", Keywords = "Trim the start of the animation"), Category = "ChromaSDK")
	static void TrimStartFramesName(const FString& animationName, int32 numberOfFrames);


	// TRIM END FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimEndFrames", Keywords = "Trim the end of the animation"), Category = "ChromaSDK")
	static void TrimEndFrames(int32 animationId, int32 lastFrameId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TrimEndFramesName", Keywords = "Trim the end of the animation"), Category = "ChromaSDK")
	static void TrimEndFramesName(const FString& animationName, int32 lastFrameId);


	// FADE START FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FadeStartFrames", Keywords = "Fade the start of the animation"), Category = "ChromaSDK")
	static void FadeStartFrames(int32 animationId, int32 fade);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FadeStartFramesName", Keywords = "Fade the start of the animation"), Category = "ChromaSDK")
	static void FadeStartFramesName(const FString& animationName, int32 fade);


	// FADE END FRAMES

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FadeEndFrames", Keywords = "Fade the end of the animation"), Category = "ChromaSDK")
	static void FadeEndFrames(int32 animationId, int32 fade);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FadeEndFramesName", Keywords = "Fade the end of the animation"), Category = "ChromaSDK")
	static void FadeEndFramesName(const FString& animationName, int32 fade);


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyboardRazerKey", Keywords = "Convert FKey to RZKEY"), Category = "ChromaSDK")
	static EChromaSDKKeyboardKey::Type GetKeyboardRazerKey(FKey key);


#if PLATFORM_WINDOWS
private:
	static IChromaSDKPlugin _sIChromaSDKPlugin;

	static std::map<FKey, EChromaSDKKeyboardKey::Type> _sKeyboardFKeyMap;
	static std::map<EChromaSDKKeyboardKey::Type, int32> _sKeyboardEnumMap;
	static std::map<EChromaSDKMouseLed::Type, ChromaSDK::Mouse::RZLED2> _sMouseEnumMap;

#endif
};
