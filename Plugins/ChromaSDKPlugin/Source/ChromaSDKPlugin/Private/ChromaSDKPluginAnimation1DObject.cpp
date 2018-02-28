// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChromaSDKPluginPrivatePCH.h"
#include "ChromaSDKPluginBPLibrary.h"
#include "ChromaSDKPluginAnimation1DObject.h"

UChromaSDKPluginAnimation1DObject::UChromaSDKPluginAnimation1DObject(const FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

bool UChromaSDKPluginAnimation1DObject::IsLoaded()
{
#if PLATFORM_WINDOWS
	return _mIsLoaded;
#else
	return false;
#endif
}

void UChromaSDKPluginAnimation1DObject::Unload()
{
#if PLATFORM_WINDOWS
	if (!_mIsLoaded)
	{
		//ignore
		return;
	}

	for (int i = 0; i < _mEffects.Num(); ++i)
	{
		FChromaSDKEffectResult& effect = _mEffects[i];
		int result = UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(effect.EffectId);
		if (result != 0)
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginAnimation1DObject::Unload Failed to delete effect!"));
		}
	}
	_mEffects.Reset();
	_mIsLoaded = false;
#endif
}

void UChromaSDKPluginAnimation1DObject::Tick(float deltaTime)
{
#if PLATFORM_WINDOWS
	_mTime += deltaTime;
	float nextTime = GetTime(_mCurrentFrame);
	if (nextTime < _mTime)
	{
		++_mCurrentFrame;
		if (_mCurrentFrame < _mEffects.Num())
		{
			//UE_LOG(LogTemp, Log, TEXT("UChromaSDKPluginAnimation1DObject::Tick SetEffect."));
			FChromaSDKEffectResult& effect = _mEffects[_mCurrentFrame];
			int result = UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(effect.EffectId);
			if (result != 0)
			{
				UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginAnimation1DObject::Tick Failed to set effect!"));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Log, TEXT("UChromaSDKPluginAnimation1DObject::Tick Animation Complete."));
			_mIsPlaying = false;
			_mTime = 0.0f;
			_mCurrentFrame = 0;

			// execute the complete event if set
			_mOnComplete.ExecuteIfBound(this);
		}
	}
#endif
}

bool UChromaSDKPluginAnimation1DObject::IsTickable() const
{
#if PLATFORM_WINDOWS
	return _mIsPlaying;
#else
	return false;
#endif
}

bool UChromaSDKPluginAnimation1DObject::IsTickableInEditor() const
{
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

bool UChromaSDKPluginAnimation1DObject::IsTickableWhenPaused() const
{
	return false;
}

TStatId UChromaSDKPluginAnimation1DObject::GetStatId() const
{
	return TStatId();
}

float UChromaSDKPluginAnimation1DObject::GetTime(int index)
{
	if(index >= 0 &&
		index < Curve.EditorCurveData.GetNumKeys())
	{
		TMap<FKeyHandle, int32>::TConstIterator iter = Curve.EditorCurveData.GetKeyHandleIterator();
		for (int i = 0; i < index; ++i)
		{
			if (i == index)
			{
				return Curve.EditorCurveData.GetKeyTime(iter->Key);
			}
			++iter;
		}
	}
	return 0.033f;
}
