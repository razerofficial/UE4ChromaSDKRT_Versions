// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UE4ChromaSDKRT.h"
#include "SampleBPLibrary.h"
#include "ChromaSDKPluginBPLibrary.h"

USampleBPLibrary::USampleBPLibrary(const FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void USampleBPLibrary::SampleStart()
{
	UChromaSDKPluginBPLibrary::ChromaSDKInit();
}

void USampleBPLibrary::SampleEnd()
{
	UChromaSDKPluginBPLibrary::ChromaSDKUnInit();
}

void USampleBPLibrary::SamplePlayComposite()
{
	UChromaSDKPluginBPLibrary::PlayAnimationComposite("Random", false);
}

void USampleBPLibrary::SamplePlayCompositeLoop()
{
	UChromaSDKPluginBPLibrary::PlayAnimationComposite("Random", true);
}

void USampleBPLibrary::SampleStopComposite()
{
	UChromaSDKPluginBPLibrary::StopAnimationComposite("Random");
}

void USampleBPLibrary::SampleClearComposite()
{
	UChromaSDKPluginBPLibrary::ClearAll();
}

void USampleBPLibrary::SampleShowHotkeysAnimated()
{
	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);

	FString target = "Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(target);

	FString source = "Fire_Keyboard";
	UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(source, target, keys);

	UChromaSDKPluginBPLibrary::PlayAnimation(target, true);
}

void USampleBPLibrary::SampleShowHotkeysStaticColor()
{
	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);

	FString target = "Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(target);

	FLinearColor color = FLinearColor(1, 0, 0, 0);
	UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(target, keys, color);

	UChromaSDKPluginBPLibrary::PlayAnimation(target, true);
}

void USampleBPLibrary::SampleHideHotkeys()
{
	FString target = "Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(target);

	UChromaSDKPluginBPLibrary::PlayAnimation(target, true);
}
