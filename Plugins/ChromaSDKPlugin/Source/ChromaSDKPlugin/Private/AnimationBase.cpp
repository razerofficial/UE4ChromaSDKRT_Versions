#//include "AnimationBase.h" //___HACK_UE4_VERSION_4_16_OR_GREATER
#include "ChromaSDKPluginPrivatePCH.h"
#include "AnimationBase.h" //___HACK_UE4_VERSION_4_15_OR_LESS

using namespace ChromaSDK;
using namespace std;

AnimationBase::AnimationBase()
{
	_mCurrentFrame = 0;
	_mIsPlaying = false;
	_mTime = 0.0f;
}

AnimationBase::~AnimationBase()
{

}

const string& AnimationBase::GetName()
{
	return _mName;
}

void AnimationBase::SetName(const std::string& name)
{
	_mName = name;
}

int AnimationBase::GetDeviceTypeId()
{
	return (int)GetDeviceType();
}

int AnimationBase::GetCurrentFrame()
{
	return _mCurrentFrame;
}

void AnimationBase::SetCurrentFrame(int index)
{
	if (index < 0 ||
		index >= GetFrameCount())
	{
		index = 0;
	}
	_mCurrentFrame = index;
}

bool AnimationBase::IsPlaying()
{
	return _mIsPlaying;
}