// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//#include "SampleBPButton.h" //___HACK_UE4_VERSION_4_16_OR_GREATER
#include "UE4ChromaSDKRT.h"
#include "SampleBPButton.h" //___HACK_UE4_VERSION_4_15_OR_LESS
#include "SampleBPLibrary.h"

USampleBPButton::USampleBPButton(const class FPostConstructInitializeProperties& PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
	: Super(PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
//USampleBPButton::USampleBPButton(const FObjectInitializer& ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
//	: Super(ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
{
}

void USampleBPButton::HandleClick()
{
	if (Name.Compare("ButtonPlayComposite") == 0)
	{
		USampleBPLibrary::SamplePlayComposite();
	}
	else if (Name.Compare("ButtonLoopComposite") == 0)
	{
		USampleBPLibrary::SamplePlayCompositeLoop();
	}
	else if (Name.Compare("ButtonStopComposite") == 0)
	{
		USampleBPLibrary::SampleStopComposite();
	}
	else if (Name.Compare("ButtonClearComposite") == 0)
	{
		USampleBPLibrary::SampleClearComposite();
	}
	else if (Name.Compare("ButtonShowHotKeysAnimated") == 0)
	{
		USampleBPLibrary::SampleShowHotkeysAnimated();
	}
	else if (Name.Compare("ButtonShowHotKeysStaticColor") == 0)
	{
		USampleBPLibrary::SampleShowHotkeysStaticColor();
	}
	else if (Name.Compare("ButtonHideHotKeys") == 0)
	{
		USampleBPLibrary::SampleHideHotkeys();
	}
	else if (Name.Compare("ButtonLayeredHeal") == 0)
	{
		USampleBPLibrary::SampleLayeredHeal();
	}
	else if (Name.Compare("ButtonLayeredDamage") == 0)
	{
		USampleBPLibrary::SampleLayeredDamage();
	}
	else if (Name.Compare("ButtonLayeredItemPickup") == 0)
	{
		USampleBPLibrary::SampleLayeredItemPickup();
	}
	else if (Name.Compare("ButtonLayeredOff") == 0)
	{
		USampleBPLibrary::SampleLayeredOff();
	}
	else if (Name.Compare("ButtonPlayChromaLink") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationChromaLink();
	}
	else if (Name.Compare("ButtonLoopChromaLink") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationChromaLink();
	}
	else if (Name.Compare("ButtonStopChromaLink") == 0)
	{
		USampleBPLibrary::SampleStopAnimationChromaLink();
	}
	else if (Name.Compare("ButtonStaticColorChromaLink") == 0)
	{
		USampleBPLibrary::SampleStaticColorChromaLink();
	}
	else if (Name.Compare("ButtonClearChromaLink") == 0)
	{
		USampleBPLibrary::SampleClearChromaLink();
	}
	else if (Name.Compare("ButtonPlayHeadset") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationHeadset();
	}
	else if (Name.Compare("ButtonLoopHeadset") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationHeadset();
	}
	else if (Name.Compare("ButtonStopHeadset") == 0)
	{
		USampleBPLibrary::SampleStopAnimationHeadset();
	}
	else if (Name.Compare("ButtonStaticColorHeadset") == 0)
	{
		USampleBPLibrary::SampleStaticColorHeadset();
	}
	else if (Name.Compare("ButtonClearHeadset") == 0)
	{
		USampleBPLibrary::SampleClearHeadset();
	}
	else if (Name.Compare("ButtonPlayKeyboard") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationKeyboard();
	}
	else if (Name.Compare("ButtonLoopKeyboard") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationKeyboard();
	}
	else if (Name.Compare("ButtonStopKeyboard") == 0)
	{
		USampleBPLibrary::SampleStopAnimationKeyboard();
	}
	else if (Name.Compare("ButtonStaticColorKeyboard") == 0)
	{
		USampleBPLibrary::SampleStaticColorKeyboard();
	}
	else if (Name.Compare("ButtonClearKeyboard") == 0)
	{
		USampleBPLibrary::SampleClearKeyboard();
	}
	else if (Name.Compare("ButtonPlayKeypad") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationKeypad();
	}
	else if (Name.Compare("ButtonLoopKeypad") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationKeypad();
	}
	else if (Name.Compare("ButtonStopKeypad") == 0)
	{
		USampleBPLibrary::SampleStopAnimationKeypad();
	}
	else if (Name.Compare("ButtonStaticColorKeypad") == 0)
	{
		USampleBPLibrary::SampleStaticColorKeypad();
	}
	else if (Name.Compare("ButtonClearKeypad") == 0)
	{
		USampleBPLibrary::SampleClearKeypad();
	}
	else if (Name.Compare("ButtonPlayMouse") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationMouse();
	}
	else if (Name.Compare("ButtonLoopMouse") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationMouse();
	}
	else if (Name.Compare("ButtonStopMouse") == 0)
	{
		USampleBPLibrary::SampleStopAnimationMouse();
	}
	else if (Name.Compare("ButtonStaticColorMouse") == 0)
	{
		USampleBPLibrary::SampleStaticColorMouse();
	}
	else if (Name.Compare("ButtonClearMouse") == 0)
	{
		USampleBPLibrary::SampleClearMouse();
	}
	else if (Name.Compare("ButtonPlayMousepad") == 0)
	{
		USampleBPLibrary::SamplePlayAnimationMousepad();
	}
	else if (Name.Compare("ButtonLoopMousepad") == 0)
	{
		USampleBPLibrary::SampleLoopAnimationMousepad();
	}
	else if (Name.Compare("ButtonStopMousepad") == 0)
	{
		USampleBPLibrary::SampleStopAnimationMousepad();
	}
	else if (Name.Compare("ButtonStaticColorMousepad") == 0)
	{
		USampleBPLibrary::SampleStaticColorMousepad();
	}
	else if (Name.Compare("ButtonClearMousepad") == 0)
	{
		USampleBPLibrary::SampleClearMousepad();
	}
}
