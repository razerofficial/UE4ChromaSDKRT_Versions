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

int UChromaSDKPluginBPLibrary::GetMaxRow(EChromaSDKDevice2DEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return ChromaSDK::Keyboard::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return ChromaSDK::Keypad::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return ChromaSDK::Mouse::MAX_ROW;
	}
#endif
	return 0;
}

int UChromaSDKPluginBPLibrary::GetMaxColumn(EChromaSDKDevice2DEnum::Type device)
{
	int result = 0;
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return ChromaSDK::Keyboard::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return ChromaSDK::Keypad::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return ChromaSDK::Mouse::MAX_COLUMN;
	}
#endif
	return result;
}

TArray<FLinearColor> UChromaSDKPluginBPLibrary::CreateColors1D(EChromaSDKDevice1DEnum::Type device)
{
	TArray<FLinearColor> colors = TArray<FLinearColor>();
#if PLATFORM_WINDOWS
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		FLinearColor color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
		colors.Add(color);
	}
#endif
	return colors;
}

TArray<FChromaSDKColors> UChromaSDKPluginBPLibrary::CreateColors2D(EChromaSDKDevice2DEnum::Type device)
{
	TArray<FChromaSDKColors> result = TArray<FChromaSDKColors>();
#if PLATFORM_WINDOWS
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			FLinearColor color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
			row.Colors.Add(color);
		}
		result.Add(row);
	}
#endif
	return result;
}
