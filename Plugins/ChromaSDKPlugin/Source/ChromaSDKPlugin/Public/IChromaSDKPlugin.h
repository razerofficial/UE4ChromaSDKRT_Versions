// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

#if PLATFORM_WINDOWS

//expose HMODULE
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"
#include <map>
#include <string>
#include "ChromaSDKPluginTypes.h"

typedef RZRESULT(*CHROMA_SDK_INIT)(void);
typedef RZRESULT(*CHROMA_SDK_UNINIT)(void);
typedef RZRESULT(*CHROMA_SDK_CREATE_EFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT)(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_KEYBOARD_EFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_KEYPAD_EFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_HEADSET_EFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_MOUSE_EFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_MOUSEPAD_EFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_SET_EFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*CHROMA_SDK_DELETE_EFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*CHROMA_SDK_REGISTER_EVENT_NOTIFICATION)(HWND hWnd);
typedef RZRESULT(*CHROMA_SDK_UNREGISTER_EVENT_NOTIFICATION)(void);
typedef RZRESULT(*CHROMA_SDK_QUERY_DEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

namespace ChromaSDK
{
	class AnimationBase;
}

#endif

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class IChromaSDKPlugin : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IChromaSDKPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< IChromaSDKPlugin >( "ChromaSDKPlugin" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "ChromaSDKPlugin" );
	}

#if PLATFORM_WINDOWS
	// SDK Methods
	int ChromaSDKInit();
	int ChromaSDKUnInit();
	bool IsInitialized();
	RZRESULT ChromaSDKCreateEffect(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKSetEffect(RZEFFECTID effectId);
	RZRESULT ChromaSDKDeleteEffect(RZEFFECTID effectId);

	static int GetRGB(int red, int green, int blue);
	static int ToBGR(const FLinearColor& color);
	static FLinearColor ToLinearColor(int color);
	static int GetMaxLeds(EChromaSDKDevice1DEnum::Type device);
	static int GetMaxRow(EChromaSDKDevice2DEnum::Type device);
	static int GetMaxColumn(EChromaSDKDevice2DEnum::Type device);
	int OpenAnimation(const char* path);
	int CloseAnimation(int animationId);
	int CloseAnimationName(const char* path);
	int GetAnimation(const char* path);
	int GetAnimationIdFromInstance(ChromaSDK::AnimationBase* animation);
	ChromaSDK::AnimationBase* GetAnimationInstance(int animationId);
	const char* GetAnimationName(int animationId);
	int GetAnimationCount();
	int GetAnimationId(int index);
	int GetPlayingAnimationCount();
	int GetPlayingAnimationId(int index);
	void PlayAnimation(int animationId, bool loop);
	void PlayAnimationName(const char* path, bool loop);
	void StopAnimation(int animationId);
	void StopAnimationName(const char* path);
	void StopAnimationType(int deviceType, int device);
	bool IsAnimationPlaying(int animationId);
	bool IsAnimationPlayingName(const char* path);
	bool IsAnimationPlayingType(int deviceType, int device);
	int GetAnimationFrameCount(int animationId);
	int GetAnimationFrameCountName(const char* path);
	void SetKeyColor(int animationId, int frameId, int rzkey, COLORREF color);
	void SetKeyColorName(const char* path, int frameId, int rzkey, COLORREF color);
	void SetKeyNonZeroColor(int animationId, int frameId, int rzkey, COLORREF color);
	void SetKeyNonZeroColorName(const char* path, int frameId, int rzkey, COLORREF color);
	COLORREF GetKeyColor(int animationId, int frameId, int rzkey);
	COLORREF GetKeyColorName(const char* path, int frameId, int rzkey);
	void CopyKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
	void CopyKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
	void CopyNonZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
	void CopyNonZeroKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
	void CopyAllKeysColor(int sourceAnimationId, int targetAnimationId, int frameId);
	void CopyAllKeysColorName(const char* sourceAnimation, const char* targetAnimation, int frameId);
	void CopyNonZeroAllKeysColor(int sourceAnimationId, int targetAnimationId, int frameId);
	void CopyNonZeroAllKeysColorName(const char* sourceAnimation, const char* targetAnimation, int frameId);

	// FILL COLOR
	
	void FillColor(int animationId, int frameId, int color);
	void FillColorName(const char* path, int frameId, int color);

	void FillColorRGB(int animationId, int frameId, int red, int green, int blue);
	void FillColorRGBName(const char* path, int frameId, int red, int green, int blue);

	// NONZERO COLOR

	void FillNonZeroColor(int animationId, int frameId, int color);
	void FillNonZeroColorName(const char* path, int frameId, int color);

	void FillNonZeroColorRGB(int animationId, int frameId, int red, int green, int blue);
	void FillNonZeroColorRGBName(const char* path, int frameId, int red, int green, int blue);

	// ZERO COLOR

	void FillZeroColor(int animationId, int frameId, int color);
	void FillZeroColorName(const char* path, int frameId, int color);

	void FillZeroColorRGB(int animationId, int frameId, int red, int green, int blue);
	void FillZeroColorRGBName(const char* path, int frameId, int red, int green, int blue);

	// FILL COLOR ALL FRAMES

	void FillColorAllFrames(int animationId, int color);
	void FillColorAllFramesName(const char* path, int color);

	void FillColorAllFramesRGB(int animationId, int red, int green, int blue);
	void FillColorAllFramesRGBName(const char* path, int red, int green, int blue);

	// NONZERO COLOR

	void FillNonZeroColorAllFrames(int animationId, int color);
	void FillNonZeroColorAllFramesName(const char* path, int color);

	void FillNonZeroColorAllFramesRGB(int animationId, int red, int green, int blue);
	void FillNonZeroColorAllFramesRGBName(const char* path, int red, int green, int blue);

	// ZERO COLOR

	void FillZeroColorAllFrames(int animationId, int color);
	void FillZeroColorAllFramesName(const char* path, int color);

	void FillZeroColorAllFramesRGB(int animationId, int red, int green, int blue);
	void FillZeroColorAllFramesRGBName(const char* path, int red, int green, int blue);

	// FILL RANDOM COLORS
	void FillRandomColors(int animationId, int frameId);
	void FillRandomColorsName(const char* path, int frameId);

	void FillRandomColorsAllFrames(int animationId);
	void FillRandomColorsAllFramesName(const char* path);

	// FILL RANDOM BLACK AND WHITE
	void FillRandomColorsBlackAndWhite(int animationId, int frameId);
	void FillRandomColorsBlackAndWhiteName(const char* path, int frameId);

	void FillRandomColorsBlackAndWhiteAllFrames(int animationId);
	void FillRandomColorsBlackAndWhiteAllFramesName(const char* path);

	// OFFSET COLORS

	void OffsetColors(int animationId, int frameId, int red, int green, int blue);
	void OffsetColorsName(const char* path, int frameId, int red, int green, int blue);

	void OffsetColorsAllFrames(int animationId, int red, int green, int blue);
	void OffsetColorsAllFramesName(const char* path, int red, int green, int blue);

	void OffsetNonZeroColors(int animationId, int frameId, int red, int green, int blue);
	void OffsetNonZeroColorsName(const char* path, int frameId, int red, int green, int blue);

	void OffsetNonZeroColorsAllFrames(int animationId, int red, int green, int blue);
	void OffsetNonZeroColorsAllFramesName(const char* path, int red, int green, int blue);

	void MultiplyIntensity(int animationId, int frameId, float intensity);
	void MultiplyIntensityName(const char* path, int frameId, float intensity);

	void MultiplyIntensityRGB(int animationId, int frameId, float redIntensity, float greenIntensity, float blueIntensity);
	void MultiplyIntensityRGBName(const char* path, int frameId, float redIntensity, float greenIntensity, float blueIntensity);

	void MultiplyIntensityAllFrames(int animationId, float intensity);
	void MultiplyIntensityAllFramesName(const char* path, float intensity);

	void MultiplyIntensityAllFramesRGB(int animationId, float redIntensity, float greenIntensity, float blueIntensity);
	void MultiplyIntensityAllFramesRGBName(const char* path, float redIntensity, float greenIntensity, float blueIntensity);

	void LoadAnimation(int animationId);
	void LoadAnimationName(const char* path);
	void UnloadAnimation(int animationId);
	void UnloadAnimationName(const char* path);

	void SetChromaCustomFlag(int animationId, bool flag);
	void SetChromaCustomFlagName(const char* path, bool flag);

	void SetChromaCustomColorAllFrames(int animationId);
	void SetChromaCustomColorAllFramesName(const char* path);

	int OverrideFrameDuration(int animationId, float duration);
	void OverrideFrameDurationName(const char* path, float duration);

	// MAKE FRAMES
	void MakeBlankFrames(int animationId, int frameCount, float duration, int color);
	void MakeBlankFramesName(const char* path, int frameCount, float duration, int color);

	void MakeBlankFramesRGB(int animationId, int frameCount, float duration, int red, int green, int blue);
	void MakeBlankFramesRGBName(const char* path, int frameCount, float duration, int red, int green, int blue);

	// RANDOM
	void MakeBlankFramesRandom(int animationId, int frameCount, float duration);
	void MakeBlankFramesRandomName(const char* path, int frameCount, float duration);

	// RANDOM BLACK AND WHITE
	void MakeBlankFramesRandomBlackAndWhite(int animationId, int frameCount, float duration);
	void MakeBlankFramesRandomBlackAndWhiteName(const char* path, int frameCount, float duration);

protected:
	static int min(int a, int b);
	static int max(int a, int b);

	bool ValidateGetProcAddress(bool condition, FString methodName);

	bool _mInitialized;

	HMODULE _mLibraryChroma;

	CHROMA_SDK_INIT _mMethodInit;
	CHROMA_SDK_UNINIT _mMethodUnInit;
	CHROMA_SDK_CREATE_EFFECT _mMethodCreateEffect;
	CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT _mMethodCreateChromaLinkEffect;
	CHROMA_SDK_CREATE_HEADSET_EFFECT _mMethodCreateHeadsetEffect;
	CHROMA_SDK_CREATE_KEYBOARD_EFFECT _mMethodCreateKeyboardEffect;
	CHROMA_SDK_CREATE_KEYPAD_EFFECT _mMethodCreateKeypadEffect;
	CHROMA_SDK_CREATE_MOUSE_EFFECT _mMethodCreateMouseEffect;
	CHROMA_SDK_CREATE_MOUSEPAD_EFFECT _mMethodCreateMousepadEffect;
	CHROMA_SDK_SET_EFFECT _mMethodSetEffect;
	CHROMA_SDK_DELETE_EFFECT _mMethodDeleteEffect;
	CHROMA_SDK_QUERY_DEVICE _mMethodQueryDevice;

	int _mAnimationId;
	std::map<std::string, int> _mAnimationMapID;
	std::map<int, ChromaSDK::AnimationBase*> _mAnimations;
	std::map<EChromaSDKDevice1DEnum::Type, int> _mPlayMap1D;
	std::map<EChromaSDKDevice2DEnum::Type, int> _mPlayMap2D;
#endif
};
