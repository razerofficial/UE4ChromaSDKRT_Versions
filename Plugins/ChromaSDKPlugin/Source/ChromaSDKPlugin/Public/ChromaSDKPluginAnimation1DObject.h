// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IChromaSDKPlugin.h"
#include "ChromaSDKPluginTypes.h"
#include "ChromaSDKPluginAnimation1DObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateChomaSDKOnComplete1D, UChromaSDKPluginAnimation1DObject*, animation);

UCLASS(Blueprintable, BlueprintType, Category = "Animation")
class CHROMASDKPLUGIN_API UChromaSDKPluginAnimation1DObject : public UObject, public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Data")
	TEnumAsByte<EChromaSDKDevice1DEnum::Type> Device;

	UPROPERTY(EditAnywhere, Category = "Data")
	TArray<FChromaSDKColorFrame1D> Frames;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsLoaded", Keywords = "Check if the animation has loaded"), Category = "ChromaSDK")
	bool IsLoaded();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Unload", Keywords = "Unload the effects"), Category = "ChromaSDK")
	void Unload();

	/* Implements FTickableGameObject */
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	/* Implements FTickableGameObject */

private:
	float GetDuration(int index);

	// Callback when animation completes
	FDelegateChomaSDKOnComplete1D _mOnComplete;

	// Effects needs to be loaded before the animation can be played
	bool _mIsLoaded;

	bool _mIsPlaying;
	float _mTime;
	int _mCurrentFrame;
	TArray<FChromaSDKEffectResult> _mEffects;
};
