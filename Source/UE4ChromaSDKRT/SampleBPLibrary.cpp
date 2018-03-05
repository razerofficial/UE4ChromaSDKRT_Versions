// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UE4ChromaSDKRT.h"
#include "SampleBPLibrary.h"
#include "ChromaSDKPluginBPLibrary.h"

USampleBPLibrary::USampleBPLibrary(const FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
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

void USampleBPLibrary::SampleShowHotkeys()
{

}

void USampleBPLibrary::SampleHideHotkeys()
{

}
