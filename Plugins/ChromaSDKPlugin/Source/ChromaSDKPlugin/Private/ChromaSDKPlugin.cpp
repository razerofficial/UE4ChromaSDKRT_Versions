// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ChromaSDKPluginPrivatePCH.h"
#include "AnimationBase.h"

#if PLATFORM_WINDOWS

using namespace ChromaSDK;
using namespace std;

#endif

class FChromaSDKPlugin : public IChromaSDKPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FChromaSDKPlugin, ChromaSDKPlugin )



void FChromaSDKPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FChromaSDKPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#if PLATFORM_WINDOWS

int IChromaSDKPlugin::ChromaSDKInit()
{
	if (_mMethodInit == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin Init method is not set!"));
		return -1;
	}

	int result = _mMethodInit();
	if (result == 0)
	{
		_mInitialized = true;
	}
	UE_LOG(LogTemp, Log, TEXT("ChromaSDKPlugin [INITIALIZED] result=%d"), result);
	return result;
}

int IChromaSDKPlugin::ChromaSDKUnInit()
{
	if (_mMethodUnInit == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin UnInit method is not set!"));
		return -1;
	}

	while (_mAnimations.size() > 0)
	{
		int animationId = _mAnimations.begin()->first;
		StopAnimation(animationId);
		CloseAnimation(animationId);
	}

	int result = _mMethodUnInit();
	_mInitialized = false;
	_mAnimationId = 0;
	_mAnimationMapID.clear();
	_mAnimations.clear();
	_mPlayMap1D.clear();
	_mPlayMap2D.clear();
	//UE_LOG(LogTemp, Log, TEXT("ChromaSDKPlugin [UNINITIALIZED] result=%d"), result);
	return result;
}

bool IChromaSDKPlugin::IsInitialized()
{
	return _mInitialized;
}

RZRESULT IChromaSDKPlugin::ChromaSDKSetEffect(RZEFFECTID effectId)
{
	if (_mMethodSetEffect == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin SetEffect method is not set!"));
		return -1;
	}

	return _mMethodSetEffect(effectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKDeleteEffect(RZEFFECTID effectId)
{
	if (_mMethodDeleteEffect == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin DeleteEffect method is not set!"));
		return -1;
	}

	return _mMethodDeleteEffect(effectId);
}

int IChromaSDKPlugin::CloseAnimation(int animationId)
{
	try
	{
		if (_mAnimations.find(animationId) != _mAnimations.end())
		{
			AnimationBase* animation = _mAnimations[animationId];
			if (animation == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("CloseAnimation: Animation is null! id=%d"), animationId);
				return -1;
			}
			animation->Stop();
			string animationName = animation->GetName();
			if (_mAnimationMapID.find(animationName) != _mAnimationMapID.end())
			{
				_mAnimationMapID.erase(animationName);
			}
			delete _mAnimations[animationId];
			_mAnimations.erase(animationId);
			return animationId;
		}
	}
	catch (exception)
	{
		UE_LOG(LogTemp, Error, TEXT("CloseAnimation: Exception animationId=%d"), (int)animationId);
	}
	return -1;
}

void IChromaSDKPlugin::StopAnimation(int animationId)
{
	if (!IsInitialized())
	{
		ChromaSDKInit();
	}
	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("StopAnimation: Animation is null! id=%d"), animationId);
			return;
		}
		//UE_LOG(LogTemp, Log, TEXT("StopAnimation: %s"), *FString(UTF8_TO_TCHAR(animation->GetName().c_str())));
		animation->Stop();
	}
}

#endif
