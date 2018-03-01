#pragma once

#include "AnimationBase.h"

#if PLATFORM_WINDOWS

namespace ChromaSDK
{
	class Animation1D : public AnimationBase
	{
	public:
		Animation1D();
		void Reset();
		EChromaSDKDeviceTypeEnum::Type GetDeviceType();
		EChromaSDKDevice1DEnum::Type GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum::Type device);
		int GetDeviceId();
		std::vector<FChromaSDKColorFrame1D>& GetFrames();
		int GetFrameCount();
		float GetDuration(unsigned int index);
		void Load();
		void Unload();
		void Play(bool loop);
		void Stop();
		void Update(float deltaTime);
		void ResetFrames();
		int Save(const char* path);
	private:
		EChromaSDKDevice1DEnum::Type _mDevice;
		std::vector<FChromaSDKColorFrame1D> _mFrames;
		bool _mLoop;
	};
}

#endif
