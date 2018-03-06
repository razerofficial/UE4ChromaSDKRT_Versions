// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "SampleBPLibrary.generated.h"

UCLASS()
class USampleBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStart", Keywords = "Init at the start of the application"), Category = "Sample")
	static void SampleStart();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleEnd", Keywords = "Uninit at the end of the application"), Category = "Sample")
	static void SampleEnd();

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

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationChromaLink", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationChromaLink();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationHeadset", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationHeadset();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationKeyboard", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationKeyboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationKeypad", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationKeypad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationMouse", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SamplePlayAnimationMousepad", Keywords = "Play the device animation"), Category = "Sample")
	static void SamplePlayAnimationMousepad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationChromaLink", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationChromaLink();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationHeadset", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationHeadset();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationKeyboard", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationKeyboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationKeypad", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationKeypad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationMouse", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleLoopAnimationMousepad", Keywords = "Loop the device animation"), Category = "Sample")
	static void SampleLoopAnimationMousepad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationChromaLink", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationChromaLink();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationHeadset", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationHeadset();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationKeyboard", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationKeyboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationKeypad", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationKeypad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationMouse", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStopAnimationMousepad", Keywords = "Stop the device animation"), Category = "Sample")
	static void SampleStopAnimationMousepad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorChromaLink", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorChromaLink();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorHeadset", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorHeadset();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorKeyboard", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorKeyboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorKeypad", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorKeypad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorMouse", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleStaticColorMousepad", Keywords = "Set a static color on the device"), Category = "Sample")
	static void SampleStaticColorMousepad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearChromaLink", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearChromaLink();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearHeadset", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearHeadset();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearKeyboard", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearKeyboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearKeypad", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearKeypad();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearMouse", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SampleClearMousepad", Keywords = "Clear the device"), Category = "Sample")
	static void SampleClearMousepad();
};
