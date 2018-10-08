// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

//#include "ChromaSDKPluginBPLibrary.h" //___HACK_UE4_VERSION_4_16_OR_GREATER
#include "UE4ChromaSDKRT.h"
#include "ChromaSDKPluginBPLibrary.h" //___HACK_UE4_VERSION_4_15_OR_LESS
#include "SampleBPButton.h"
#include "SampleBPLibrary.h"

float USampleBPLibrary::_sBaseIntensity = 1.0f;
float USampleBPLibrary::_sEffectIntensity = 1.0f;
float USampleBPLibrary::_sHotkeyIntensity = 1.0f;
int USampleBPLibrary::_sSelectedLayerExample = 0;

USampleBPLibrary::USampleBPLibrary(const FPostConstructInitializeProperties& PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
	: Super(PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
//USampleBPLibrary::USampleBPLibrary(const FObjectInitializer& ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
//	: Super(ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
{
}

void USampleBPLibrary::SampleSetupButtonsEffects(const TArray<UButton*>& buttons)
{
	for (int i = 0; i < buttons.Num(); ++i)
	{
		UButton* button = buttons[i];
		if (button)
		{
			USampleBPButton* dynamicButton = NewObject<USampleBPButton>();
			dynamicButton->AddToRoot(); //avoid GC collection
			dynamicButton->Name = button->GetName();
			button->OnClicked.AddDynamic(dynamicButton, &USampleBPButton::HandleClick);
		}
	}
}


void USampleBPLibrary::SampleStart()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		UChromaSDKPluginBPLibrary::ChromaSDKInit();
	}
}

void USampleBPLibrary::SampleEnd()
{
	if (UChromaSDKPluginBPLibrary::IsInitialized())
	{
		UChromaSDKPluginBPLibrary::ChromaSDKUnInit();
	}
}

void USampleBPLibrary::SamplePlayComposite()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}
	UChromaSDKPluginBPLibrary::PlayAnimationComposite("Animations/Random", false);
}

void USampleBPLibrary::SamplePlayCompositeLoop()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}
	UChromaSDKPluginBPLibrary::PlayAnimationComposite("Animations/Random", true);
}

void USampleBPLibrary::SampleStopComposite()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}
	UChromaSDKPluginBPLibrary::StopAnimationComposite("Animations/Random");
}

void USampleBPLibrary::SampleClearComposite()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}
	UChromaSDKPluginBPLibrary::ClearAll();
}

void USampleBPLibrary::SampleShowHotkeysAnimated()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);

	FString target = "Animations/Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(target);

	FString source = "Animations/Fire_Keyboard";
	UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(source, target, keys);

	UChromaSDKPluginBPLibrary::PlayAnimation(target, true);
}

void USampleBPLibrary::SampleShowHotkeysStaticColor()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);

	FString target = "Animations/Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(target);

	FLinearColor color = FLinearColor(1, 0, 0, 0);
	UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(target, keys, color);

	UChromaSDKPluginBPLibrary::PlayAnimation(target, true);
}

void USampleBPLibrary::SampleHideHotkeys()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Random_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(animation);
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SamplePlayAnimationChromaLink()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationHeadset()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Headset";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationKeyboard()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keyboard";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationKeypad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keypad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationMouse()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mouse";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SamplePlayAnimationMousepad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mousepad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, false);
}

void USampleBPLibrary::SampleLoopAnimationChromaLink()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationHeadset()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Headset";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationKeyboard()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keyboard";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationKeypad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keypad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationMouse()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mouse";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleLoopAnimationMousepad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mousepad";
	UChromaSDKPluginBPLibrary::PlayAnimation(animation, true);
}

void USampleBPLibrary::SampleStopAnimationChromaLink()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_ChromaLink";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationHeadset()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Headset";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationKeyboard()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keyboard";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationKeypad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Keypad";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationMouse()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mouse";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStopAnimationMousepad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString animation = "Animations/Fire_Mousepad";
	UChromaSDKPluginBPLibrary::StopAnimation(animation);
}

void USampleBPLibrary::SampleStaticColorChromaLink()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_ChromaLink);
	FLinearColor color = FLinearColor(1, 0, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_ChromaLink, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorHeadset()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_Headset);
	FLinearColor color = FLinearColor(1, 1, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Headset, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorKeyboard()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_Keyboard);
	FLinearColor color = FLinearColor(1, 0, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Keyboard, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorKeypad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_Keypad);
	FLinearColor color = FLinearColor(0, 1, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Keypad, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorMouse()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_Mouse);
	FLinearColor color = FLinearColor(1, 1, 1);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Mouse, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleStaticColorMousepad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::DE_Mousepad);
	FLinearColor color = FLinearColor(1, 0.5f, 0);
	FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::DE_Mousepad, color);
	UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
	UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
}

void USampleBPLibrary::SampleClearChromaLink()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_ChromaLink);
}

void USampleBPLibrary::SampleClearHeadset()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Headset);
}

void USampleBPLibrary::SampleClearKeyboard()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Keyboard);
}

void USampleBPLibrary::SampleClearKeypad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Keypad);
}

void USampleBPLibrary::SampleClearMouse()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Mouse);
}

void USampleBPLibrary::SampleClearMousepad()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::DE_Mousepad);
}

void USampleBPLibrary::SampleLayeredHeal()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sSelectedLayerExample = 0;

	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);
	keys.Add(EChromaSDKKeyboardKey::KK_Q);
	keys.Add(EChromaSDKKeyboardKey::KK_E);

	FString baseLayer = "Animations/EnvironmentSnow_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(baseLayer);
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(baseLayer, 1.0f + 64.0f * _sBaseIntensity);

	FString layer2 = "Animations/RingGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer2);
	// turn animation green
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer2, -127, 127, -127); //animation starts with 127,127,127 so adding -127,127,-127 results in 0,255,0 or green
	// set intensity
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(layer2, _sEffectIntensity);
	UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesName(layer2, baseLayer);

	FString layer3 = "Animations/FadeInOutGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer3);
	// change color
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer3, 173-127, 255-127, 47-127);
	// set intensity
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(layer3, _sHotkeyIntensity);
	UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(layer3, baseLayer, keys);

	keys.Reset();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);

	FLinearColor color = FLinearColor(_sHotkeyIntensity * 1, _sHotkeyIntensity * 0.5f, 0, 0);
	UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(baseLayer, keys, color);

	UChromaSDKPluginBPLibrary::PlayAnimation(baseLayer, true);
}

void USampleBPLibrary::SampleLayeredDamage()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sSelectedLayerExample = 1;

	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);
	keys.Add(EChromaSDKKeyboardKey::KK_Q);
	keys.Add(EChromaSDKKeyboardKey::KK_E);

	FString baseLayer = "Animations/EnvironmentSnow_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(baseLayer);
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(baseLayer, 1.0f + 64.0f * _sBaseIntensity);

	FString layer2 = "Animations/RingGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer2);
	// turn animation red
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer2, 127, -127, -127); //animation starts with 127,127,127 so adding 127,-127,-127 results in 255,0,0 or red
	// set intensity
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(layer2, _sEffectIntensity);
	UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesName(layer2, baseLayer);

	FString layer3 = "Animations/FadeInOutGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer3);
	// change color
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer3, 220-127, 20-127, 60-127);
	// set intensity
	UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(layer3, baseLayer, keys);

	keys.Reset();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);

	FLinearColor color = FLinearColor(_sHotkeyIntensity * 1, _sHotkeyIntensity * 0.5f, 0, 0);
	UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(baseLayer, keys, color);

	UChromaSDKPluginBPLibrary::PlayAnimation(baseLayer, true);
}

void USampleBPLibrary::SampleLayeredItemPickup()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sSelectedLayerExample = 2;

	TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>> keys = TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>();
	keys.Add(EChromaSDKKeyboardKey::KK_LOGO);
	keys.Add(EChromaSDKKeyboardKey::KK_ESC);
	keys.Add(EChromaSDKKeyboardKey::KK_Q);
	keys.Add(EChromaSDKKeyboardKey::KK_E);

	FString baseLayer = "Animations/EnvironmentSnow_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(baseLayer);
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(baseLayer, 1.0f + 64.0f * _sBaseIntensity);

	FString layer2 = "Animations/RingGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer2);
	// turn animation blue
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer2, -127, -127, 127); //animation starts with 127,127,127 so adding -127,-127,127 results in 0,0,255 or blue
	// set intensity
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(layer2, _sEffectIntensity);
	UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesName(layer2, baseLayer);

	FString layer3 = "Animations/FadeInOutGray_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(layer3);
	// change color
	UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(layer3, 64-127, 224-127, 208-127);
	// set intensity
	UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(layer3, _sHotkeyIntensity);
	UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(layer3, baseLayer, keys);

	keys.Reset();
	keys.Add(EChromaSDKKeyboardKey::KK_W);
	keys.Add(EChromaSDKKeyboardKey::KK_A);
	keys.Add(EChromaSDKKeyboardKey::KK_S);
	keys.Add(EChromaSDKKeyboardKey::KK_D);

	FLinearColor color = FLinearColor(_sHotkeyIntensity * 1, _sHotkeyIntensity * 0.5f, 0, 0);
	UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(baseLayer, keys, color);

	UChromaSDKPluginBPLibrary::PlayAnimation(baseLayer, true);
}

void USampleBPLibrary::SampleLayeredOff()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	FString baseLayer = "Animations/EnvironmentSnow_Keyboard";
	UChromaSDKPluginBPLibrary::CloseAnimationName(baseLayer);

	UChromaSDKPluginBPLibrary::ClearAll();
}

void USampleBPLibrary::SetupLastLayeredExample()
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	switch (_sSelectedLayerExample)
	{
	case 0:
		SampleLayeredHeal();
		return;
	case 1:
		SampleLayeredDamage();
		return;
	case 2:
		SampleLayeredItemPickup();
		return;
	}
}

void USampleBPLibrary::SampleChangeBaseIntensity(float intensity)
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sBaseIntensity = intensity;
	SetupLastLayeredExample();
}

void USampleBPLibrary::SampleChangeEffectIntensity(float intensity)
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sEffectIntensity = intensity;
	SetupLastLayeredExample();
}

void USampleBPLibrary::SampleChangeHotkeyIntensity(float intensity)
{
	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		//Chroma is not available
		return;
	}

	_sHotkeyIntensity = intensity;
	SetupLastLayeredExample();
}
