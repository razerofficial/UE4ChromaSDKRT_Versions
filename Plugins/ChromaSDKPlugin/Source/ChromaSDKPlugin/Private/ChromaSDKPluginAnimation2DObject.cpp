// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

//#include "ChromaSDKPluginAnimation2DObject.h" //___HACK_UE4_VERSION_4_16_OR_GREATER
#include "ChromaSDKPluginPrivatePCH.h"
#include "ChromaSDKPluginBPLibrary.h"
#include "ChromaSDKPluginAnimation2DObject.h" //___HACK_UE4_VERSION_4_15_OR_LESS

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h" 
#endif

UChromaSDKPluginAnimation2DObject::UChromaSDKPluginAnimation2DObject(const FPostConstructInitializeProperties& PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
	: Super(PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
//UChromaSDKPluginAnimation2DObject::UChromaSDKPluginAnimation2DObject(const FObjectInitializer& ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
//	: Super(ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
{
}

bool UChromaSDKPluginAnimation2DObject::IsLoaded()
{
#if PLATFORM_WINDOWS
	return _mIsLoaded;
#else
	return false;
#endif
}

void UChromaSDKPluginAnimation2DObject::Unload()
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
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginAnimation2DObject::Unload Failed to delete effect!"));
		}
	}
	_mEffects.Reset();
	_mIsLoaded = false;
#endif
}

void UChromaSDKPluginAnimation2DObject::Tick(float deltaTime)
{
#if PLATFORM_WINDOWS
	_mTime += deltaTime;
	float nextTime = GetDuration(_mCurrentFrame);
	if (nextTime < _mTime)
	{
		_mTime = 0.0f;
		++_mCurrentFrame;
		if (_mCurrentFrame < _mEffects.Num())
		{
			//UE_LOG(LogTemp, Log, TEXT("UChromaSDKPluginAnimation2DObject::Tick SetEffect."));
			FChromaSDKEffectResult& effect = _mEffects[_mCurrentFrame];
			int result = UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(effect.EffectId);
			if (result != 0)
			{
				UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginAnimation2DObject::Tick Failed to set effect!"));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Log, TEXT("UChromaSDKPluginAnimation2DObject::Tick Animation Complete."));
			_mIsPlaying = false;
			_mTime = 0.0f;
			_mCurrentFrame = 0;

			// execute the complete event if set
			_mOnComplete.ExecuteIfBound(this);
		}
	}
#endif
}

bool UChromaSDKPluginAnimation2DObject::IsTickable() const
{
#if PLATFORM_WINDOWS
	return _mIsPlaying;
#else
	return false;
#endif
}

bool UChromaSDKPluginAnimation2DObject::IsTickableInEditor() const
{
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

bool UChromaSDKPluginAnimation2DObject::IsTickableWhenPaused() const
{
	return false;
}

TStatId UChromaSDKPluginAnimation2DObject::GetStatId() const
{
	return TStatId();
}

float UChromaSDKPluginAnimation2DObject::GetDuration(int index)
{
	if (index < Frames.Num())
	{
		FChromaSDKColorFrame2D& frame = Frames[index];
		return frame.Duration;
	}
	return 0.0f;
}

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h" 
#endif
