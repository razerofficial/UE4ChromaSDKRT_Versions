// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SampleBPButton.generated.h"

UCLASS()
class USampleBPButton : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	FString Name;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HandleClick", Keywords = "Dynamic function to handle button widget clicks"), Category = "Sample")
	void HandleClick();
};
