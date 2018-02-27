// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ChromaSDKPluginPrivatePCH.h"
#include "ChromaSDKPluginBPLibrary.h"


UChromaSDKPluginBPLibrary::UChromaSDKPluginBPLibrary(const FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

bool UChromaSDKPluginBPLibrary::IsPlatformWindows()
{
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

int32 UChromaSDKPluginBPLibrary::GetMaxLeds(EChromaSDKDevice1DEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		return ChromaSDK::ChromaLink::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Headset:
		return ChromaSDK::Headset::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		return ChromaSDK::Mousepad::MAX_LEDS;
	}
#endif
	return 0;
}
