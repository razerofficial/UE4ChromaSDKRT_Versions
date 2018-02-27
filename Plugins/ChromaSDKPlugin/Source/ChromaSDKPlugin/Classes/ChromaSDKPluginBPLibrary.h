// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "ChromaSDKPluginBPLibrary.generated.h"

UENUM(BlueprintType)
namespace EChromaSDKDevice1DEnum
{
	enum Type
	{
		DE_ChromaLink		UMETA(DisplayName = "ChromaLink"),
		DE_Headset			UMETA(DisplayName = "Headset"),
		DE_Mousepad			UMETA(DisplayName = "Mousepad"),
	};
}

UENUM(BlueprintType)
namespace EChromaSDKDevice2DEnum
{
	enum Type
	{
		DE_Keyboard			UMETA(DisplayName = "Keyboard"),
		DE_Keypad			UMETA(DisplayName = "Keypad"),
		DE_Mouse			UMETA(DisplayName = "Mouse"),
	};
}

UCLASS()
class CHROMASDKPLUGIN_API UChromaSDKPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
};
