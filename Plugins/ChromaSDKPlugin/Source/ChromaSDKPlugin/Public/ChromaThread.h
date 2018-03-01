#pragma once

#include "AnimationBase.h"
#include "AllowWindowsPlatformTypes.h" 
#include <mutex>
#include <thread>
#include <vector>
#include "HideWindowsPlatformTypes.h"

namespace ChromaSDK
{
	class ChromaThread
	{
	public:
		static ChromaThread* Instance();
		void Start();
		void Stop();
		void AddAnimation(AnimationBase* animation);
		void RemoveAnimation(AnimationBase* animation);
		int GetAnimationCount();
		int GetAnimationId(int index);
	private:
		ChromaThread();
		void ChromaWorker();
		static ChromaThread* _sInstance;
		std::vector<AnimationBase*> _mAnimations;
		std::thread* _mThread;
		std::mutex _mMutex;
		bool _mWaitForExit;
	};
}
