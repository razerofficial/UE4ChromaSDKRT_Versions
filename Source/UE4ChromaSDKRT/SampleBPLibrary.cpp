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
	FString animation = "Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(animation);
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SamplePlayAnimationChromaLink()
{
	FString animation = "Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationHeadset()
{
	FString animation = "Fire_Headset";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationKeyboard()
{
	FString animation = "Fire_Keyboard";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationKeypad()
{
	FString animation = "Fire_Keypad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationMouse()
{
	FString animation = "Fire_Mouse";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationMousepad()
{
	FString animation = "Fire_Mousepad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SampleLoopAnimationChromaLink()
{
	FString animation = "Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationHeadset()
{
	FString animation = "Fire_Headset";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationKeyboard()
{
	FString animation = "Fire_Keyboard";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationKeypad()
{
	FString animation = "Fire_Keypad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationMouse()
{
	FString animation = "Fire_Mouse";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationMousepad()
{
	FString animation = "Fire_Mousepad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleStopAnimationChromaLink()
{
	FString animation = "Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationHeadset()
{
	FString animation = "Fire_Headset";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationKeyboard()
{
	FString animation = "Fire_Keyboard";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationKeypad()
{
	FString animation = "Fire_Keypad";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationMouse()
{
	FString animation = "Fire_Mouse";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationMousepad()
{
	FString animation = "Fire_Mousepad";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStaticColorChromaLink()
{
	FLinearColor color = FLinearColor(1, 0, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_ChromaLink, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorHeadset()
{
	FLinearColor color = FLinearColor(1, 1, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Headset, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorKeyboard()
{
	FLinearColor color = FLinearColor(1, 0, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Keyboard, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorKeypad()
{
	FLinearColor color = FLinearColor(0, 1, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Keypad, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorMouse()
{
	FLinearColor color = FLinearColor(1, 1, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Mouse, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorMousepad()
{
	FLinearColor color = FLinearColor(1, 0.5f, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Mousepad, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleClearChromaLink()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_ChromaLink);
}

void USampleBPLibrary::SampleClearHeadset()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Headset);
}

void USampleBPLibrary::SampleClearKeyboard()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Keyboard);
}

void USampleBPLibrary::SampleClearKeypad()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Keypad);
}

void USampleBPLibrary::SampleClearMouse()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Mouse);
}

void USampleBPLibrary::SampleClearMousepad()
{
	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Mousepad);
}
