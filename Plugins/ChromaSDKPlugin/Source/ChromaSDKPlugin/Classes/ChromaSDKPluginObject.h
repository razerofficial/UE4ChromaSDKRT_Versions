// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ChromaSDKPluginObject.generated.h"


/**
 * Example UStruct declared in a plugin module
 */
USTRUCT()
struct FChromaSDKPluginStruct
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY()
	FString TestString;
};
 

/**
 * Example of declaring a UObject in a plugin module
 */
UCLASS()
class UChromaSDKPluginObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:

private:

	UPROPERTY()
	FChromaPluginStruct MyStruct;

};


