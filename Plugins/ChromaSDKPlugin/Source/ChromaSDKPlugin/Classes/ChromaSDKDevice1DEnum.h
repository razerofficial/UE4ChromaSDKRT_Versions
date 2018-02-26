// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ChromaSDKDevice1DEnum.generated.h"

UENUM(BlueprintType)
namespace EChromaSDKDevice1DEnum
{
	enum Type
	{
		DE_ChromaLink	UMETA(DisplayName = "ChromaLink"),
		DE_Headset		UMETA(DisplayName = "Headset"),
		DE_Mousepad		UMETA(DisplayName = "Mousepad"),
	};
}
