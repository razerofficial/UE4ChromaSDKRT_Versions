// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
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

	/*

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMaxRow", Keywords = "Get the max row size for the device"), Category = "ChromaSDK")
	static int32 GetMaxRow(const EChromaSDKDevice2DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMaxColumn", Keywords = "Get the max column size for the device"), Category = "ChromaSDK")
	static int32 GetMaxColumn(const EChromaSDKDevice2DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateColors1D", Keywords = "Create a blank one-dimensional color array"), Category = "ChromaSDK")
	static TArray<FLinearColor> CreateColors1D(const EChromaSDKDevice1DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateColors2D", Keywords = "Create a blank two-dimensional color array"), Category = "ChromaSDK")
	static TArray<FChromaSDKColors> CreateColors2D(const EChromaSDKDevice2DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColors1D", Keywords = "Create a random one-dimensional color array"), Category = "ChromaSDK")
	static TArray<FLinearColor> CreateRandomColors1D(const EChromaSDKDevice1DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateRandomColors2D", Keywords = "Create a random two-dimensional color array"), Category = "ChromaSDK")
	static TArray<FChromaSDKColors> CreateRandomColors2D(const EChromaSDKDevice2DEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyboardKeyColor", Keywords = "Set the key to the supplied color"), Category = "ChromaSDK")
	static const TArray<FChromaSDKColors>& SetKeyboardKeyColor(const EChromaSDKKeyboardKey& key, const FLinearColor& myColor, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetMouseLedColor", Keywords = "Set the led to the supplied color"), Category = "ChromaSDK")
	static const TArray<FChromaSDKColors>& SetMouseLedColor(const EChromaSDKMouseLed& led, const FLinearColor& myColor, UPARAM(ref) TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsInitialized", Keywords = "Return true if the blueprint library is initialized"), Category = "ChromaSDK")
	static bool IsInitialized();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init", Keywords = "Initialize the ChromaSDK"), Category = "ChromaSDK")
	static int32 ChromaSDKInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UnInit", Keywords = "Uninitialize the ChromaSDK"), Category = "ChromaSDK")
	static int32 ChromaSDKUnInit();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectNone", Keywords = "Clear the color effect"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectNone(const EChromaSDKDeviceEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectStatic", Keywords = "Create a static color effect"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectStatic(const EChromaSDKDeviceEnum& device, const FLinearColor& myColor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectCustom1D", Keywords = "Create a custom color effect using one-dimensional array"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectCustom1D(const EChromaSDKDevice1DEnum& device, const TArray<FLinearColor>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateEffectCustom2D", Keywords = "Create a custom color effect using two-dimensional array"), Category = "ChromaSDK")
	static FChromaSDKEffectResult ChromaSDKCreateEffectCustom2D(const EChromaSDKDevice2DEnum& device, const TArray<FChromaSDKColors>& colors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetEffect", Keywords = "Set Effect with Effect Id"), Category = "ChromaSDK")
	static int32 ChromaSDKSetEffect(const FChromaSDKGuid& effectId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DeleteEffect", Keywords = "Delete Effect with Effect Id"), Category = "ChromaSDK")
	static int32 ChromaSDKDeleteEffect(const FChromaSDKGuid& effectId);

	// library methods

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

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimation", Keywords = "Stop the *.chroma Animation"), Category = "ChromaSDK")
	static void StopAnimation(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimationType", Keywords = "Stop playing the Animation type"), Category = "ChromaSDK")
	static void StopAnimationType(const EChromaSDKDeviceEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAll", Keywords = "Stop playing all animations"), Category = "ChromaSDK")
	static void StopAll();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ClearAnimationType", Keywords = "Clear the device"), Category = "ChromaSDK")
	static void ClearAnimationType(const EChromaSDKDeviceEnum& device);

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
	static bool IsAnimationTypePlaying(const EChromaSDKDeviceEnum& device);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimations", Keywords = "Play an array of *.chroma Animations"), Category = "ChromaSDK")
	static void PlayAnimations(const TArray<FString>& animationNames, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimations", Keywords = "Stop an array *.chroma Animations"), Category = "ChromaSDK")
	static void StopAnimations(const TArray<FString>& animationNames);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PlayAnimationComposite", Keywords = "Play a set of *_Device.chroma Animations"), Category = "ChromaSDK")
	static void PlayAnimationComposite(const FString& animationName, bool loop);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StopAnimationComposite", Keywords = "Stop a set of *_Device.chroma Animations"), Category = "ChromaSDK")
	static void StopAnimationComposite(const FString& animationName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyColor", Keywords = "Get the color from the animation frame's key"), Category = "ChromaSDK")
	static FLinearColor GetKeyColor(int32 animationId, int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetKeyColorName", Keywords = "Get the color from the animation frame's key"), Category = "ChromaSDK")
	static FLinearColor GetKeyColorName(const FString& animationName, const int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColor", Keywords = "Set the animation frame's key to the supplied color"), Category = "ChromaSDK")
	static void SetKeyColor(int32 animationId, int32 frameIndex, const EChromaSDKKeyboardKey& key, const FLinearColor& myColor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorName", Keywords = "Set the animation frame's key to the supplied color"), Category = "ChromaSDK")
	static void SetKeyColorName(const FString& animationName, const int32 frameIndex, const EChromaSDKKeyboardKey& key, const FLinearColor& myColor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColor", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
//	static void SetKeysColor(int animationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys, const FLinearColor& color); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void SetKeysColor(int32 animationId, int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys, const FLinearColor& myColor); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorName", Keywords = "Set the animation frame to the supplied color for a set of keys"), Category = "ChromaSDK")
//	static void SetKeysColorName(const FString& animationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys, const FLinearColor& color); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void SetKeysColorName(const FString& animationName, const int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys, const FLinearColor& myColor); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorAllFrames", Keywords = "Set the key to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeyColorAllFrames(int32 animationId, const EChromaSDKKeyboardKey& key, const FLinearColor& myColor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeyColorAllFramesName", Keywords = "Set the key to the supplied color for all animation frames"), Category = "ChromaSDK")
	static void SetKeyColorAllFramesName(const FString& animationName, const EChromaSDKKeyboardKey& key, const FLinearColor& myColor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFrames", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
//	static void SetKeysColorAllFrames(int animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys, const FLinearColor& color); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void SetKeysColorAllFrames(int32 animationId, const TArray<EChromaSDKKeyboardKey>& keys, const FLinearColor& myColor); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetKeysColorAllFramesName", Keywords = "Set the keys to the supplied color for all animation frames"), Category = "ChromaSDK")
//	static void SetKeysColorAllFramesName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys, const FLinearColor& color); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void SetKeysColorAllFramesName(const FString& animationName, const TArray<EChromaSDKKeyboardKey>& keys, const FLinearColor& myColor); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeyColor", Keywords = "Copy color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyKeyColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeyColorName", Keywords = "Copy color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColor", Keywords = "Copy color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
//	static void CopyKeysColor(int sourceAnimationId, int targetAnimationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyKeysColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorName", Keywords = "Copy color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
//	static void CopyKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorAllFrames", Keywords = "Copy color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
//	static void CopyKeysColorAllFrames(int sourceAnimationId, int targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyKeysColorAllFrames(int32 sourceAnimationId, int32 targetAnimationId, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyKeysColorAllFramesName", Keywords = "Copy color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
//	static void CopyKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeyColor", Keywords = "Copy nonzero color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyNonZeroKeyColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeyColorName", Keywords = "Copy nonzero color from a source animation to a target animation for a key"), Category = "ChromaSDK")
	static void CopyNonZeroKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const EChromaSDKKeyboardKey& key);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColor", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
//	static void CopyNonZeroKeysColor(int sourceAnimationId, int targetAnimationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyNonZeroKeysColor(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorName", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys"), Category = "ChromaSDK")
//	static void CopyNonZeroKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyNonZeroKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int32 frameIndex, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorAllFrames", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
//	static void CopyNonZeroKeysColorAllFrames(int sourceAnimationId, int targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyNonZeroKeysColorAllFrames(int32 sourceAnimationId, int32 targetAnimationId, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyNonZeroKeysColorAllFramesName", Keywords = "Copy nonzero color from a source animation to a target animation for a set of keys for all frames"), Category = "ChromaSDK")
//	static void CopyNonZeroKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey>>& keys); //(support 4.13 and below)___HACK_UE4_WANTS_GAME_MODE
	static void CopyNonZeroKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<EChromaSDKKeyboardKey>& keys); //(support above 4.13)___HACK_UE4_WANTS_BASE_GAME_MODE

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetFrameCount", Keywords = "Get the .chroma animation frame count"), Category = "ChromaSDK")
	static int32 GetFrameCount(const int32 animationId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetFrameCountName", Keywords = "Get the .chroma animation frame count"), Category = "ChromaSDK")
	static int32 GetFrameCountName(const FString& animationName);

#if PLATFORM_WINDOWS
private:
	static std::map<EChromaSDKKeyboardKey, int32> _sKeyboardEnumMap;
	static std::map<EChromaSDKMouseLed, ChromaSDK::Mouse::RZLED2> _sMouseEnumMap;

	static bool _sInitialized;

#endif

	*/
};
