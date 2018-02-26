// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ChromaSDKDevice2DEnum.generated.h"

UENUM(BlueprintType)
namespace EChromaSDKDevice2DEnum
{
	enum Type
	{
		DE_Keyboard		UMETA(DisplayName = "Keyboard"),
		DE_Keypad		UMETA(DisplayName = "Keypad"),
		DE_Mouse		UMETA(DisplayName = "Mouse"),
	};
}
