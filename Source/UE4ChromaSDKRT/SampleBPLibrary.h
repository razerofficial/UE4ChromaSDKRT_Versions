// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "SampleBPLibrary.generated.h"

UCLASS()
class USampleBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayComposite", Keywords = "Play composite animations"), Category = "Sample")
	static void SamplePlayComposite();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayCompositeLoop", Keywords = "Play composite animations with loop on"), Category = "Sample")
	static void SamplePlayCompositeLoop();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopComposite", Keywords = "Stop composite animations from playing"), Category = "Sample")
	static void SampleStopComposite();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearComposite", Keywords = "Clear composite animations"), Category = "Sample")
	static void SampleClearComposite();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleShowHotkeysAnimated", Keywords = "Show animated hot keys"), Category = "Sample")
	static void SampleShowHotkeysAnimated();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleShowHotkeysStaticColor", Keywords = "Show hot keys with a static color"), Category = "Sample")
	static void SampleShowHotkeysStaticColor();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleHideHotkeys", Keywords = "Hide hot keys"), Category = "Sample")
	static void SampleHideHotkeys();
};
