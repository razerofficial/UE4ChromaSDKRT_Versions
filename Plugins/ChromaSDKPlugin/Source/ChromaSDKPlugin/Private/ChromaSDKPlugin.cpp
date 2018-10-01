// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ChromaSDKPluginPrivatePCH.h"
#include "AnimationBase.h"
#include "Animation1D.h"
#include "Animation2D.h"
#include "ChromaSDKPluginBPLibrary.h"
#include "ChromaThread.h"

#if PLATFORM_WINDOWS

#include "AllowWindowsPlatformTypes.h" 

typedef unsigned char byte;
#define ANIMATION_VERSION 1

using namespace ChromaSDK;
using namespace ChromaSDK::ChromaLink;
using namespace ChromaSDK::Headset;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Mousepad;
using namespace std;

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

#endif

int g_seed = 0;
inline int fastrand() {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

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

#if PLATFORM_WINDOWS
	_mInitialized = false;
	_mAnimationId = 0;
	_mAnimationMapID.clear();
	_mAnimations.clear();
	_mPlayMap1D.clear();
	_mPlayMap2D.clear();

	_mLibraryChroma = LoadLibrary(CHROMASDKDLL);
	if (_mLibraryChroma == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin failed to load!"));
		return;
	}
	//UE_LOG(LogTemp, Log, TEXT("ChromaSDKPlugin loaded."));

	// GetProcAddress will throw 4191 because it's an unsafe type cast
#pragma warning(disable: 4191)
	_mMethodInit = (CHROMA_SDK_INIT)GetProcAddress(_mLibraryChroma, "Init");
	if (ValidateGetProcAddress(_mMethodInit == nullptr, FString("Init")))
	{
		return;
	}
	_mMethodUnInit = (CHROMA_SDK_UNINIT)GetProcAddress(_mLibraryChroma, "UnInit");
	if (ValidateGetProcAddress(_mMethodUnInit == nullptr, FString("UnInit")))
	{
		return;
	}
	_mMethodQueryDevice = (CHROMA_SDK_QUERY_DEVICE)GetProcAddress(_mLibraryChroma, "QueryDevice");
	if (ValidateGetProcAddress(_mMethodQueryDevice == nullptr, FString("QueryDevice")))
	{
		return;
	}
	_mMethodUnInit = (CHROMA_SDK_UNINIT)GetProcAddress(_mLibraryChroma, "UnInit");
	if (ValidateGetProcAddress(_mMethodUnInit == nullptr, FString("UnInit")))
	{
		return;
	}

	_mMethodCreateChromaLinkEffect = (CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT)GetProcAddress(_mLibraryChroma, "CreateChromaLinkEffect");
	if (ValidateGetProcAddress(_mMethodCreateChromaLinkEffect == nullptr, FString("CreateChromaLinkEffect")))
	{
		return;
	}
	_mMethodCreateHeadsetEffect = (CHROMA_SDK_CREATE_HEADSET_EFFECT)GetProcAddress(_mLibraryChroma, "CreateHeadsetEffect");
	if (ValidateGetProcAddress(_mMethodCreateHeadsetEffect == nullptr, FString("CreateHeadsetEffect")))
	{
		return;
	}
	_mMethodCreateKeyboardEffect = (CHROMA_SDK_CREATE_KEYBOARD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateKeyboardEffect");
	if (ValidateGetProcAddress(_mMethodCreateKeyboardEffect == nullptr, FString("CreateKeyboardEffect")))
	{
		return;
	}
	_mMethodCreateMouseEffect = (CHROMA_SDK_CREATE_MOUSE_EFFECT)GetProcAddress(_mLibraryChroma, "CreateMouseEffect");
	if (ValidateGetProcAddress(_mMethodCreateMouseEffect == nullptr, FString("CreateMouseEffect")))
	{
		return;
	}
	_mMethodCreateMousepadEffect = (CHROMA_SDK_CREATE_MOUSEPAD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateMousepadEffect");
	if (ValidateGetProcAddress(_mMethodCreateMousepadEffect == nullptr, FString("CreateMousepadEffect")))
	{
		return;
	}
	_mMethodCreateKeypadEffect = (CHROMA_SDK_CREATE_KEYPAD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateKeypadEffect");
	if (ValidateGetProcAddress(_mMethodCreateKeypadEffect == nullptr, FString("CreateKeypadEffect")))
	{
		return;
	}

	_mMethodCreateEffect = (CHROMA_SDK_CREATE_EFFECT)GetProcAddress(_mLibraryChroma, "CreateEffect");
	if (ValidateGetProcAddress(_mMethodCreateEffect == nullptr, FString("CreateEffect")))
	{
		return;
	}
	_mMethodSetEffect = (CHROMA_SDK_SET_EFFECT)GetProcAddress(_mLibraryChroma, "SetEffect");
	if (ValidateGetProcAddress(_mMethodSetEffect == nullptr, FString("SetEffect")))
	{
		return;
	}
	_mMethodDeleteEffect = (CHROMA_SDK_DELETE_EFFECT)GetProcAddress(_mLibraryChroma, "DeleteEffect");
	if (ValidateGetProcAddress(_mMethodDeleteEffect == nullptr, FString("DeleteEffect")))
	{
		return;
	}

#pragma warning(default: 4191)

	if (!UChromaSDKPluginBPLibrary::IsInitialized())
	{
		UChromaSDKPluginBPLibrary::ChromaSDKInit();
	}

	ChromaThread::Instance()->Start();
#endif
}


void FChromaSDKPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if PLATFORM_WINDOWS
	ChromaThread::Instance()->Stop();

	if (UChromaSDKPluginBPLibrary::IsInitialized())
	{
		UChromaSDKPluginBPLibrary::ChromaSDKUnInit();
	}

	if (_mLibraryChroma)
	{
		FreeLibrary(_mLibraryChroma);
		_mLibraryChroma = nullptr;
	}
#endif
}

#if PLATFORM_WINDOWS

int IChromaSDKPlugin::ChromaSDKInit()
{
	if (_mInitialized)
	{
		//UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin is already initialized!"));
		return RZRESULT_INVALID;
	}

	if (_mMethodInit == nullptr)
	{
		return RZRESULT_INVALID;
	}

	int result = _mMethodInit();
	if (result == RZRESULT_SUCCESS)
	{
		_mInitialized = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin [Init] result=%d"), result);
	}
	return result;
}

int IChromaSDKPlugin::ChromaSDKUnInit()
{
	if (!_mInitialized)
	{
		//UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin is not initialized!"));
		return RZRESULT_INVALID;
	}

	if (_mMethodUnInit == nullptr)
	{
		return RZRESULT_INVALID;
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
	if (result != RZRESULT_SUCCESS)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin [Uninit] result=%d"), result);
	}
	return result;
}

bool IChromaSDKPlugin::IsInitialized()
{
	return _mInitialized;
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateEffect(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateEffect(deviceId, effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateChromaLinkEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateChromaLinkEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateHeadsetEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateHeadsetEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeyboardEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateKeyboardEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeypadEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateKeypadEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateMouseEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateMouseEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateMousepadEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodCreateMousepadEffect(effect, pParam, pEffectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKSetEffect(RZEFFECTID effectId)
{
	if (_mMethodSetEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodSetEffect(effectId);
}

RZRESULT IChromaSDKPlugin::ChromaSDKDeleteEffect(RZEFFECTID effectId)
{
	if (_mMethodDeleteEffect == nullptr)
	{
		return RZRESULT_INVALID;
	}

	return _mMethodDeleteEffect(effectId);
}

int IChromaSDKPlugin::GetRGB(int red, int green, int blue)
{
	return (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
}

int IChromaSDKPlugin::ToBGR(const FLinearColor& color)
{
	int red = max(0, min(255, color.R * 255));
	int green = max(0, min(255, color.G * 255));
	int blue = max(0, min(255, color.B * 255));
	int customFlag = max(0, min(255, color.A * 255));
	int bgrColor = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16) | (customFlag << 24);
	return bgrColor;
}

FLinearColor IChromaSDKPlugin::ToLinearColor(int color)
{
	float red = GetRValue(color) / 255.0f;
	float green = GetGValue(color) / 255.0f;
	float blue = GetBValue(color) / 255.0f;
	float alpha = ((color & 0xFF000000) >> 24) / 255.0f;
	return FLinearColor(red, green, blue, alpha);
}

int IChromaSDKPlugin::GetMaxLeds(EChromaSDKDevice1DEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		return ChromaSDK::ChromaLink::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Headset:
		return ChromaSDK::Headset::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		return ChromaSDK::Mousepad::MAX_LEDS;
	}
#endif
	return 0;
}

int IChromaSDKPlugin::GetMaxRow(EChromaSDKDevice2DEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return ChromaSDK::Keyboard::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return ChromaSDK::Keypad::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return ChromaSDK::Mouse::MAX_ROW;
	}
#endif
	return 0;
}

int IChromaSDKPlugin::GetMaxColumn(EChromaSDKDevice2DEnum::Type device)
{
	int result = 0;
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return ChromaSDK::Keyboard::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return ChromaSDK::Keypad::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return ChromaSDK::Mouse::MAX_COLUMN;
	}
#endif
	return result;
}

int IChromaSDKPlugin::OpenAnimation(const char* path)
{
	AnimationBase* animation = nullptr;

	//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: %s"), path);

	FILE* stream = nullptr;
	if (0 != fopen_s(&stream, path, "rb") ||
		stream == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Failed to open animation! %s"), *FString(UTF8_TO_TCHAR(path)));
		return -1;
	}

	long read = 0;
	long expectedRead = 1;
	long expectedSize = sizeof(byte);

	//version
	int version = 0;
	expectedSize = sizeof(int);
	read = fread(&version, expectedSize, 1, stream);
	if (read != expectedRead)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Failed to read version!"));
		std::fclose(stream);
		return -1;
	}
	if (version != ANIMATION_VERSION)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Unexpected Version!"));
		std::fclose(stream);
		return -1;
	}

	//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Version: %d"), version);

	//device
	byte device = 0;

	// device type
	byte deviceType = 0;
	expectedSize = sizeof(byte);
	read = fread(&deviceType, expectedSize, 1, stream);
	if (read != expectedRead)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Unexpected DeviceType!"));
		std::fclose(stream);
		return -1;
	}

	//device
	switch ((EChromaSDKDeviceTypeEnum::Type)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: DeviceType: 1D"));
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: DeviceType: 2D"));
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Unexpected DeviceType!"));
		std::fclose(stream);
		return -1;
	}

	switch ((EChromaSDKDeviceTypeEnum::Type)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		read = fread(&device, expectedSize, 1, stream);
		if (read != expectedRead)
		{
			UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Unexpected Device!"));
			std::fclose(stream);
			return -1;
		}
		else
		{
			switch ((EChromaSDKDevice1DEnum::Type)device)
			{
			case EChromaSDKDevice1DEnum::DE_ChromaLink:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_ChromaLink"));
				break;
			case EChromaSDKDevice1DEnum::DE_Headset:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_Headset"));
				break;
			case EChromaSDKDevice1DEnum::DE_Mousepad:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_Mousepad"));
				break;
			}

			Animation1D* animation1D = new Animation1D();
			animation = animation1D;

			// device
			animation1D->SetDevice((EChromaSDKDevice1DEnum::Type)device);

			//frame count
			int frameCount;

			expectedSize = sizeof(int);
			read = fread(&frameCount, expectedSize, 1, stream);
			if (read != expectedRead)
			{
				UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading frame count!"));
				delete animation1D;
				std::fclose(stream);
				return -1;
			}
			else
			{
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				for (int index = 0; index < frameCount; ++index)
				{
					FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
					int maxLeds = GetMaxLeds((EChromaSDKDevice1DEnum::Type)device);

					//duration
					float duration = 0.0f;
					expectedSize = sizeof(float);
					read = fread(&duration, expectedSize, 1, stream);
					if (read != expectedRead)
					{
						UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading duration!"));
						delete animation1D;
						std::fclose(stream);
						return -1;
					}
					else
					{
						if (duration < 0.033f)
						{
							duration = 0.033f;
						}
						frame.Duration = duration;

						// colors
						expectedSize = sizeof(int);
						for (int i = 0; i < maxLeds; ++i)
						{
							int color = 0;
							read = fread(&color, expectedSize, 1, stream);
							if (read != expectedRead)
							{
								UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading color!"));
								delete animation1D;
								std::fclose(stream);
								return -1;
							}
							else
							{
								frame.Colors.Add(ToLinearColor(color));
							}
						}
						if (index == 0)
						{
							frames[0] = frame;
						}
						else
						{
							frames.push_back(frame);
						}
					}
				}
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		read = fread(&device, expectedSize, 1, stream);
		if (read != expectedRead)
		{
			UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Unexpected Device!"));
			std::fclose(stream);
			return -1;
		}
		else
		{
			switch ((EChromaSDKDevice2DEnum::Type)device)
			{
			case EChromaSDKDevice2DEnum::DE_Keyboard:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_Keyboard"));
				break;
			case EChromaSDKDevice2DEnum::DE_Keypad:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_Keypad"));
				break;
			case EChromaSDKDevice2DEnum::DE_Mouse:
				//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Device: DE_Mouse"));
				break;
			}

			Animation2D* animation2D = new Animation2D();
			animation = animation2D;

			//device
			animation2D->SetDevice((EChromaSDKDevice2DEnum::Type)device);

			//frame count
			int frameCount;

			expectedSize = sizeof(int);
			read = fread(&frameCount, expectedSize, 1, stream);
			if (read != expectedRead)
			{
				UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading frame count!"));
				delete animation2D;
				std::fclose(stream);
				return -1;
			}
			else
			{
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				for (int index = 0; index < frameCount; ++index)
				{
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
					int maxRow = GetMaxRow((EChromaSDKDevice2DEnum::Type)device);
					int maxColumn = GetMaxColumn((EChromaSDKDevice2DEnum::Type)device);

					//duration
					float duration = 0.0f;
					expectedSize = sizeof(float);
					read = fread(&duration, expectedSize, 1, stream);
					if (read != expectedRead)
					{
						UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading duration!"));
						delete animation2D;
						std::fclose(stream);
						return -1;
					}
					else
					{
						if (duration < 0.033f)
						{
							duration = 0.033f;
						}
						frame.Duration = duration;

						// colors
						expectedSize = sizeof(int);
						for (int i = 0; i < maxRow; ++i)
						{
							FChromaSDKColors row = FChromaSDKColors();
							for (int j = 0; j < maxColumn; ++j)
							{
								int color = 0;
								read = fread(&color, expectedSize, 1, stream);
								if (read != expectedRead)
								{
									UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Error detected reading color!"));
									delete animation2D;
									std::fclose(stream);
									return -1;
								}
								else
								{
									row.Colors.Add(ToLinearColor(color));
								}
							}
							frame.Colors.Add(row);
						}
						if (index == 0)
						{
							frames[0] = frame;
						}
						else
						{
							frames.push_back(frame);
						}
					}
				}
			}
		}
		break;
	}

	std::fclose(stream);

	if (animation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenAnimation: Animation is null! name=%s"), *FString(UTF8_TO_TCHAR(path)));
		return -1;
	}

	//UE_LOG(LogTemp, Log, TEXT("OpenAnimation: Loaded %s"), *FString(UTF8_TO_TCHAR(path)));
	animation->SetName(path);
	int id = _mAnimationId;
	_mAnimations[id] = animation;
	++_mAnimationId;
	_mAnimationMapID[path] = id;
	return id;
}

int IChromaSDKPlugin::CloseAnimation(int animationId)
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
		animation->Unload();
		string animationName = animation->GetName();
		if (_mAnimationMapID.find(animationName) != _mAnimationMapID.end())
		{
			_mAnimationMapID.erase(animationName);
		}
		delete _mAnimations[animationId];
		_mAnimations.erase(animationId);
		return animationId;
	}
	return -1;
}

int IChromaSDKPlugin::CloseAnimationName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CloseAnimationName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return -1;
	}
	return CloseAnimation(animationId);
}

int IChromaSDKPlugin::GetAnimation(const char* path)
{
	for (std::map<string, int>::iterator it = _mAnimationMapID.begin(); it != _mAnimationMapID.end(); ++it)
	{
		const string& item = (*it).first;
		if (item.compare(path) == 0) {
			return (*it).second;
		}
	}
	return OpenAnimation(path);
}

int IChromaSDKPlugin::GetAnimationIdFromInstance(AnimationBase* animation)
{
	if (animation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetAnimationIdFromInstance: Invalid animation!"));
		return -1;
	}
	for (int index = 0; index < _mAnimations.size(); ++index)
	{
		if (_mAnimations[index] == animation)
		{
			return index;
		}
	}
	return -1;
}

AnimationBase* IChromaSDKPlugin::GetAnimationInstance(int animationId)
{
	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		return _mAnimations[animationId];
	}
	return nullptr;
}

const char* IChromaSDKPlugin::GetAnimationName(int animationId)
{
	if (animationId < 0)
	{
		return "";
	}
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (animation == nullptr)
	{
		return "";
	}
	return animation->GetName().c_str();
}

int IChromaSDKPlugin::GetAnimationCount()
{
	return _mAnimationMapID.size();
}

int IChromaSDKPlugin::GetAnimationId(int index)
{
	int i = 0;
	for (std::map<string, int>::iterator it = _mAnimationMapID.begin(); it != _mAnimationMapID.end(); ++it)
	{
		if (index == i)
		{
			return (*it).second;
		}
		++i;
	}
	return -1;
}

int IChromaSDKPlugin::GetPlayingAnimationCount()
{
	if (ChromaThread::Instance() == nullptr)
	{
		return 0;
	}
	return ChromaThread::Instance()->GetAnimationCount();
}

int IChromaSDKPlugin::GetPlayingAnimationId(int index)
{
	if (ChromaThread::Instance() == nullptr)
	{
		return -1;
	}
	return ChromaThread::Instance()->GetAnimationId(index);
}

void IChromaSDKPlugin::PlayAnimation(int animationId, bool loop)
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
			UE_LOG(LogTemp, Error, TEXT("PlayAnimation: Animation is null! id=%d"), animationId);
			return;
		}
		StopAnimationType(animation->GetDeviceTypeId(), animation->GetDeviceId());
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			_mPlayMap1D[(EChromaSDKDevice1DEnum::Type)animation->GetDeviceId()] = animationId;
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			_mPlayMap2D[(EChromaSDKDevice2DEnum::Type)animation->GetDeviceId()] = animationId;
			break;
		}
		//UE_LOG(LogTemp, Log, TEXT("PlayAnimation: %s"), *FString(UTF8_TO_TCHAR(animation->GetName().c_str())));
		animation->Play(loop);
	}
}

void IChromaSDKPlugin::PlayAnimationName(const char* path, bool loop)
{
	if (!IsInitialized())
	{
		ChromaSDKInit();
	}
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayAnimationName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	PlayAnimation(animationId, loop);
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

void IChromaSDKPlugin::StopAnimationName(const char* path)
{
	if (!IsInitialized())
	{
		ChromaSDKInit();
	}
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("StopAnimationName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	StopAnimation(animationId);
}

void IChromaSDKPlugin::StopAnimationType(int deviceType, int device)
{
	switch ((EChromaSDKDeviceTypeEnum::Type)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		if (_mPlayMap1D.find((EChromaSDKDevice1DEnum::Type)device) != _mPlayMap1D.end())
		{
			int prevAnimation = _mPlayMap1D[(EChromaSDKDevice1DEnum::Type)device];
			if (prevAnimation != -1)
			{
				StopAnimation(prevAnimation);
				_mPlayMap1D[(EChromaSDKDevice1DEnum::Type)device] = -1;
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		if (_mPlayMap2D.find((EChromaSDKDevice2DEnum::Type)device) != _mPlayMap2D.end())
		{
			int prevAnimation = _mPlayMap2D[(EChromaSDKDevice2DEnum::Type)device];
			if (prevAnimation != -1)
			{
				StopAnimation(prevAnimation);
				_mPlayMap2D[(EChromaSDKDevice2DEnum::Type)device] = -1;
			}
		}
	}
	break;
	}
}

bool IChromaSDKPlugin::IsAnimationPlaying(int animationId)
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
			UE_LOG(LogTemp, Error, TEXT("IsAnimationPlaying: Animation is null! id=%d"), animationId);
			return false;
		}
		return animation->IsPlaying();
	}
	return false;
}

bool IChromaSDKPlugin::IsAnimationPlayingName(const char* path)
{
	if (!IsInitialized())
	{
		ChromaSDKInit();
	}
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("IsAnimationPlayingName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return false;
	}
	return IsAnimationPlaying(animationId);
}

bool IChromaSDKPlugin::IsAnimationPlayingType(int deviceType, int device)
{
	switch ((EChromaSDKDeviceTypeEnum::Type)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		if (_mPlayMap1D.find((EChromaSDKDevice1DEnum::Type)device) != _mPlayMap1D.end())
		{
			int prevAnimation = _mPlayMap1D[(EChromaSDKDevice1DEnum::Type)device];
			if (prevAnimation != -1)
			{
				return IsAnimationPlaying(prevAnimation);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		if (_mPlayMap2D.find((EChromaSDKDevice2DEnum::Type)device) != _mPlayMap2D.end())
		{
			int prevAnimation = _mPlayMap2D[(EChromaSDKDevice2DEnum::Type)device];
			if (prevAnimation != -1)
			{
				return IsAnimationPlaying(prevAnimation);
			}
		}
	}
	break;
	}
	return false;
}

int IChromaSDKPlugin::GetAnimationFrameCount(int animationId)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return -1;
	}
	return animation->GetFrameCount();
}

int IChromaSDKPlugin::GetAnimationFrameCountName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GetFrameCountName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return -1;
	}
	return GetAnimationFrameCount(animationId);
}


void IChromaSDKPlugin::SetKeyColor(int animationId, int frameId, int rzkey, COLORREF color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
		animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = ToLinearColor(color);
		}
	}
}

void IChromaSDKPlugin::SetKeyColorName(const char* path, int frameId, int rzkey, COLORREF color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SetKeyColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	SetKeyColor(animationId, frameId, rzkey, color);
}


void IChromaSDKPlugin::SetKeyNonZeroColor(int animationId, int frameId, int rzkey, COLORREF color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
		animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			if (frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] != ToLinearColor(RGB(0,0,0)))
			{
				frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = ToLinearColor(color);
			}
		}
	}
}

void IChromaSDKPlugin::SetKeyNonZeroColorName(const char* path, int frameId, int rzkey, COLORREF color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SetKeyNonZeroColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	SetKeyNonZeroColor(animationId, frameId, rzkey, color);
}


COLORREF IChromaSDKPlugin::GetKeyColor(int animationId, int frameId, int rzkey)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return 0;
	}
	if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
		animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			FLinearColor& color = frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
			return ToBGR(color);
		}
	}
	return 0;
}

COLORREF IChromaSDKPlugin::GetKeyColorName(const char* path, int frameId, int rzkey)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GetKeyColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return 0;
	}
	return GetKeyColor(animationId, frameId, rzkey);
}

void IChromaSDKPlugin::CopyKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
	}
}

void IChromaSDKPlugin::CopyKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyKeyColorName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyKeyColorName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
}


void IChromaSDKPlugin::CopyNonZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		FLinearColor& color = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		if (ToBGR(color) != 0)
		{
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
		}
	}
}

void IChromaSDKPlugin::CopyNonZeroKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroKeyColorName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroKeyColorName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
}


void IChromaSDKPlugin::CopyAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& color = sourceFrame.Colors[i].Colors[j];
				targetFrame.Colors[i].Colors[j] = color;
			}
		}
	}
}

void IChromaSDKPlugin::CopyAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyAllKeysName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyAllKeysName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyAllKeys(sourceAnimationId, targetAnimationId, frameId);
}


// NONZERO

void IChromaSDKPlugin::CopyNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& color = sourceFrame.Colors[i].Colors[j];
				if (ToBGR(color) != 0)
				{
					targetFrame.Colors[i].Colors[j] = color;
				}
			}
		}
	}
}

void IChromaSDKPlugin::CopyNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
}

// NONZERO ADD

void IChromaSDKPlugin::AddNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& linearColor = sourceFrame.Colors[i].Colors[j];
				int color = ToBGR(linearColor);
				if (color != 0)
				{
					int sourceRed = color & 0xFF;
					int sourceGreen = (color & 0xFF00) >> 8;
					int sourceBlue = (color & 0xFF0000) >> 16;

					int oldColor = ToBGR(targetFrame.Colors[i].Colors[j]);
					int oldRed = oldColor & 0xFF;
					int oldGreen = (oldColor & 0xFF00) >> 8;
					int oldBlue = (oldColor & 0xFF0000) >> 16;

					int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
					int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
					int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
					int newColor = red | (green << 8) | (blue << 16);

					targetFrame.Colors[i].Colors[j] = ToLinearColor(newColor);
				}
			}
		}
	}
}

void IChromaSDKPlugin::AddNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroAllKeysName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroAllKeysName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	AddNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
}

// NONZERO SUBTRACT

void IChromaSDKPlugin::SubtractNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& linearColor = sourceFrame.Colors[i].Colors[j];
				int color = ToBGR(linearColor);
				if (color != 0)
				{
					int sourceRed = color & 0xFF;
					int sourceGreen = (color & 0xFF00) >> 8;
					int sourceBlue = (color & 0xFF0000) >> 16;

					int oldColor = ToBGR(targetFrame.Colors[i].Colors[j]);
					int oldRed = oldColor & 0xFF;
					int oldGreen = (oldColor & 0xFF00) >> 8;
					int oldBlue = (oldColor & 0xFF0000) >> 16;

					int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
					int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
					int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
					int newColor = red | (green << 8) | (blue << 16);

					targetFrame.Colors[i].Colors[j] = ToLinearColor(newColor);
				}
			}
		}
	}
}

void IChromaSDKPlugin::SubtractNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroAllKeysName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroAllKeysName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	SubtractNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
}


// NONZERO OFFSET

void IChromaSDKPlugin::CopyNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < sourceFrames.size() && (frameId + offset) < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId+offset];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& color = sourceFrame.Colors[i].Colors[j];
				if (ToBGR(color) != 0)
				{
					targetFrame.Colors[i].Colors[j] = color;
				}
			}
		}
	}
}

void IChromaSDKPlugin::CopyNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
}


// NONZERO OFFSET ADD

void IChromaSDKPlugin::AddNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < sourceFrames.size() && (frameId + offset) < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId + offset];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& linearColor = sourceFrame.Colors[i].Colors[j];
				int color = ToBGR(linearColor);
				if (color != 0)
				{
					int sourceRed = color & 0xFF;
					int sourceGreen = (color & 0xFF00) >> 8;
					int sourceBlue = (color & 0xFF0000) >> 16;

					int oldColor = ToBGR(targetFrame.Colors[i].Colors[j]);
					int oldRed = oldColor & 0xFF;
					int oldGreen = (oldColor & 0xFF00) >> 8;
					int oldBlue = (oldColor & 0xFF0000) >> 16;

					int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
					int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
					int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
					int newColor = red | (green << 8) | (blue << 16);

					targetFrame.Colors[i].Colors[j] = ToLinearColor(newColor);
				}
			}
		}
	}
}

void IChromaSDKPlugin::AddNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroAllKeysOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroAllKeysOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	AddNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
}


// NONZERO OFFSET SUBTRACT

void IChromaSDKPlugin::SubtractNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
{
	StopAnimation(targetAnimationId);
	AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
	if (nullptr == sourceAnimation)
	{
		return;
	}
	AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
	if (nullptr == targetAnimation)
	{
		return;
	}
	if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
		targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	if (frameId < 0)
	{
		return;
	}
	Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
	Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
	vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
	vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
	if (sourceFrames.size() == 0)
	{
		return;
	}
	if (targetFrames.size() == 0)
	{
		return;
	}
	if (frameId < sourceFrames.size() && (frameId + offset) < targetFrames.size())
	{
		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId + offset];
		for (int i = 0; i < sourceFrame.Colors.Num(); ++i)
		{
			for (int j = 0; j < sourceFrame.Colors[i].Colors.Num(); ++j)
			{
				FLinearColor& linearColor = sourceFrame.Colors[i].Colors[j];
				int color = ToBGR(linearColor);
				if (color != 0)
				{
					int sourceRed = color & 0xFF;
					int sourceGreen = (color & 0xFF00) >> 8;
					int sourceBlue = (color & 0xFF0000) >> 16;

					int oldColor = ToBGR(targetFrame.Colors[i].Colors[j]);
					int oldRed = oldColor & 0xFF;
					int oldGreen = (oldColor & 0xFF00) >> 8;
					int oldBlue = (oldColor & 0xFF0000) >> 16;

					int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
					int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
					int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
					int newColor = red | (green << 8) | (blue << 16);

					targetFrame.Colors[i].Colors[j] = ToLinearColor(newColor);
				}
			}
		}
	}
}

void IChromaSDKPlugin::SubtractNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroAllKeysOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroAllKeysOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	SubtractNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
}


int IChromaSDKPlugin::min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
int IChromaSDKPlugin::max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}


// FILL COLOR


void IChromaSDKPlugin::FillColor(int animationId, int frameId, int color)
{
	//clamp values
	color = color & 0xFFFFFFFF;

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillColorName(const char* path, int frameId, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColor(animationId, frameId, color);
}


void IChromaSDKPlugin::FillColorRGB(int animationId, int frameId, int red, int green, int blue)
{
	int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillColorRGBName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColorRGB(animationId, frameId, red, green, blue);
}


// NONZERO COLOR

void IChromaSDKPlugin::FillNonZeroColor(int animationId, int frameId, int color)
{
	color = color & 0xFFFFFFFF;

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				if (ToBGR(colors[i]) != 0)
				{
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					if (ToBGR(row.Colors[j]) != 0)
					{
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillNonZeroColorName(const char* path, int frameId, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColor(animationId, frameId, color);
}


void IChromaSDKPlugin::FillNonZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
{
	int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				if (ToBGR(colors[i]) != 0)
				{
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					if (ToBGR(row.Colors[j]) != 0)
					{
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillNonZeroColorRGBName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColorRGB(animationId, frameId, red, green, blue);
}


// ZERO COLOR

void IChromaSDKPlugin::FillZeroColor(int animationId, int frameId, int color)
{
	//clamp values
	color = color & 0xFFFFFFFF;

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				if (ToBGR(colors[i]) == 0)
				{
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					if (ToBGR(row.Colors[j]) == 0)
					{
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillZeroColorName(const char* path, int frameId, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillZeroColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillZeroColor(animationId, frameId, color);
}


void IChromaSDKPlugin::FillZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
{
	//clamp values
	red = max(0, min(255, red));
	green = max(0, min(255, green));
	blue = max(0, min(255, blue));
	int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				if (ToBGR(colors[i]) == 0)
				{
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					if (ToBGR(row.Colors[j]) == 0)
					{
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillZeroColorRGBName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillZeroColorRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillZeroColorRGB(animationId, frameId, red, green, blue);
}


// FILL THRESHOLD COLORS

void IChromaSDKPlugin::FillThresholdColors(int animationId, int frameId, int threshold, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				FLinearColor& linearColor = colors[i];
				int oldColor = ToBGR(linearColor);
				int red = oldColor & 0xFF;
				int green = (oldColor & 0xFF00) >> 8;
				int blue = (oldColor & 0xFF0000) >> 16;
				if (red != 0 &&
					green != 0 &&
					blue != 0 &&
					red <= threshold &&
					green <= threshold &&
					blue <= threshold) {
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = GetMaxRow(animation2D->GetDevice());
			int maxColumn = GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					FLinearColor& linearColor = row.Colors[j];
					int oldColor = ToBGR(linearColor);
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if (red != 0 &&
						green != 0 &&
						blue != 0 &&
						red <= threshold &&
						green <= threshold &&
						blue <= threshold) {
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillThresholdColorsName(const char* path, int frameId, int threshold, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillThresholdColorsName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillThresholdColors(animationId, frameId, threshold, color);
}

void IChromaSDKPlugin::FillThresholdColorsRGB(int animationId, int frameId, int threshold, int red, int green, int blue)
{
	StopAnimation(animationId);
	int color = GetRGB(red, green, blue);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				FLinearColor& linearColor = colors[i];
				int oldColor = ToBGR(linearColor);
				int red = oldColor & 0xFF;
				int green = (oldColor & 0xFF00) >> 8;
				int blue = (oldColor & 0xFF0000) >> 16;
				if (red != 0 &&
					green != 0 &&
					blue != 0 &&
					red <= threshold &&
					green <= threshold &&
					blue <= threshold) {
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = GetMaxRow(animation2D->GetDevice());
			int maxColumn = GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					FLinearColor& linearColor = row.Colors[j];
					int oldColor = ToBGR(linearColor);
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if (red != 0 &&
						green != 0 &&
						blue != 0 &&
						red <= threshold &&
						green <= threshold &&
						blue <= threshold) {
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::FillThresholdColorsRGBName(const char* path, int frameId, int threshold, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillThresholdColorsRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillThresholdColorsRGB(animationId, frameId, threshold, red, green, blue);
}


// FILL THRESHOLD COLORS ALL FRAMES

void IChromaSDKPlugin::FillThresholdColorsAllFrames(int animationId, int threshold, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillThresholdColors(animationId, frameId, threshold, color);
	}
}

void IChromaSDKPlugin::FillThresholdColorsAllFramesName(const char* path, int threshold, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillThresholdColorsAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillThresholdColorsAllFrames(animationId, threshold, color);
}

void IChromaSDKPlugin::FillThresholdColorsAllFramesRGB(int animationId, int threshold, int red, int green, int blue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillThresholdColorsRGB(animationId, frameId, threshold, red, green, blue);
	}
}

void IChromaSDKPlugin::FillThresholdColorsAllFramesRGBName(const char* path, int threshold, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillThresholdColorsAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillThresholdColorsAllFramesRGB(animationId, threshold, red, green, blue);
}


// FILL COLOR ALL FRAMES


void IChromaSDKPlugin::FillColorAllFrames(int animationId, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillColor(animationId, frameId, color);
	}
}

void IChromaSDKPlugin::FillColorAllFramesName(const char* path, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColorAllFrames(animationId, color);
}


void IChromaSDKPlugin::FillColorAllFramesRGB(int animationId, int red, int green, int blue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillColorRGB(animationId, frameId, red, green, blue);
	}
}

void IChromaSDKPlugin::FillColorAllFramesRGBName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColorAllFramesRGB(animationId, red, green, blue);
}


// NONZERO COLOR


void IChromaSDKPlugin::FillNonZeroColorAllFrames(int animationId, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillNonZeroColor(animationId, frameId, color);
	}
}

void IChromaSDKPlugin::FillNonZeroColorAllFramesName(const char* path, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColorAllFrames(animationId, color);
}


void IChromaSDKPlugin::FillNonZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillNonZeroColorRGB(animationId, frameId, red, green, blue);
	}
}

void IChromaSDKPlugin::FillNonZeroColorAllFramesRGBName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColorAllFramesRGB(animationId, red, green, blue);
}


// ZERO COLOR


void IChromaSDKPlugin::FillZeroColorAllFrames(int animationId, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillZeroColor(animationId, frameId, color);
	}
}

void IChromaSDKPlugin::FillZeroColorAllFramesName(const char* path, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillZeroColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillZeroColorAllFrames(animationId, color);
}


void IChromaSDKPlugin::FillZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillZeroColorRGB(animationId, frameId, red, green, blue);
	}
}

void IChromaSDKPlugin::FillZeroColorAllFramesRGBName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillZeroColorAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillZeroColorAllFramesRGB(animationId, red, green, blue);
}


// FILL RANDOM COLORS


void IChromaSDKPlugin::FillRandomColors(int animationId, int frameId)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	if (frameId >= 0 && frameId < frameCount)
	{
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				frame.Colors = UChromaSDKPluginBPLibrary::CreateRandomColors1D(animation1D->GetDevice());
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				frame.Colors = UChromaSDKPluginBPLibrary::CreateRandomColors2D(animation2D->GetDevice());
			}
		}
		break;
		}
	}
}

void IChromaSDKPlugin::FillRandomColorsName(const char* path, int frameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillRandomColorsName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FillRandomColors(animationId, frameId);
}


void IChromaSDKPlugin::FillRandomColorsAllFrames(int animationId)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillRandomColors(animationId, frameId);
	}
}

void IChromaSDKPlugin::FillRandomColorsAllFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillRandomColorsAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FillRandomColorsAllFrames(animationId);
}


// FILL RANDOM BLACK AND WHITE


void IChromaSDKPlugin::FillRandomColorsBlackAndWhite(int animationId, int frameId)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	if (frameId >= 0 && frameId < frameCount)
	{
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				frame.Colors = UChromaSDKPluginBPLibrary::CreateRandomColorsBlackAndWhite1D(animation1D->GetDevice());
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				frame.Colors = UChromaSDKPluginBPLibrary::CreateRandomColorsBlackAndWhite2D(animation2D->GetDevice());
			}
		}
		break;
		}
	}
}

void IChromaSDKPlugin::FillRandomColorsBlackAndWhiteName(const char* path, int frameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillRandomColorsBlackAndWhiteName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FillRandomColorsBlackAndWhite(animationId, frameId);
}


void IChromaSDKPlugin::FillRandomColorsBlackAndWhiteAllFrames(int animationId)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = animation->GetFrameCount();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FillRandomColorsBlackAndWhite(animationId, frameId);
	}
}

void IChromaSDKPlugin::FillRandomColorsBlackAndWhiteAllFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillRandomColorsBlackAndWhiteAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FillRandomColorsBlackAndWhiteAllFrames(animationId);
}


// OFFSET COLORS

void IChromaSDKPlugin::OffsetColors(int animationId, int frameId, int offsetRed, int offsetGreen, int offsetBlue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				int color = ToBGR(colors[i]);
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = max(0, min(255, red + offsetRed));
				green = max(0, min(255, green + offsetGreen));
				blue = max(0, min(255, blue + offsetBlue));
				color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = ToBGR(row.Colors[j]);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red + offsetRed));
					green = max(0, min(255, green + offsetGreen));
					blue = max(0, min(255, blue + offsetBlue));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}
void IChromaSDKPlugin::OffsetColorsName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OffsetColorsName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return OffsetColors(animationId, frameId, red, green, blue);
}


void IChromaSDKPlugin::OffsetColorsAllFrames(int animationId, int offsetRed, int offsetGreen, int offsetBlue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		OffsetColors(animationId, frameId, offsetRed, offsetGreen, offsetBlue);
	}
}
void IChromaSDKPlugin::OffsetColorsAllFramesName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OffsetColorsAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return OffsetColorsAllFrames(animationId, red, green, blue);
}


void IChromaSDKPlugin::OffsetNonZeroColors(int animationId, int frameId, int offsetRed, int offsetGreen, int offsetBlue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				int color = ToBGR(colors[i]);
				if (color != 0)
				{
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red + offsetRed));
					green = max(0, min(255, green + offsetGreen));
					blue = max(0, min(255, blue + offsetBlue));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = ToBGR(row.Colors[j]);
					if (color != 0)
					{
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, red + offsetRed));
						green = max(0, min(255, green + offsetGreen));
						blue = max(0, min(255, blue + offsetBlue));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
	}
	break;
	}
}
void IChromaSDKPlugin::OffsetNonZeroColorsName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OffsetNonZeroColorsName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return OffsetNonZeroColors(animationId, frameId, red, green, blue);
}


void IChromaSDKPlugin::OffsetNonZeroColorsAllFrames(int animationId, int offsetRed, int offsetGreen, int offsetBlue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		OffsetNonZeroColors(animationId, frameId, offsetRed, offsetGreen, offsetBlue);
	}
}
void IChromaSDKPlugin::OffsetNonZeroColorsAllFramesName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OffsetNonZeroColorsAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return OffsetNonZeroColorsAllFrames(animationId, red, green, blue);
}


// MULTIPLY INTENSITY

void IChromaSDKPlugin::MultiplyIntensity(int animationId, int frameId, float intensity)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				int color = ToBGR(colors[i]);
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = max(0, min(255, red * intensity));
				green = max(0, min(255, green * intensity));
				blue = max(0, min(255, blue * intensity));
				color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = ToBGR(row.Colors[j]);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red * intensity));
					green = max(0, min(255, green * intensity));
					blue = max(0, min(255, blue * intensity));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::MultiplyIntensityName(const char* path, int frameId, float intensity)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensity(animationId, frameId, intensity);
}

// MULTIPLY INTENSITY COLOR

void IChromaSDKPlugin::MultiplyIntensityColor(int animationId, int frameId, int color)
{
	StopAnimation(animationId);
	int red = (color & 0xFF);
	int green = (color & 0xFF00) >> 8;
	int blue = (color & 0xFF0000) >> 16;
	float redIntensity = red / 255.0f;
	float greenIntensity = green / 255.0f;
	float blueIntensity = blue / 255.0f;
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = IChromaSDKPlugin::Get().GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				int color = ToBGR(colors[i]);
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = max(0, min(255, red * redIntensity));
				green = max(0, min(255, green * greenIntensity));
				blue = max(0, min(255, blue * blueIntensity));
				color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = IChromaSDKPlugin::Get().GetMaxRow(animation2D->GetDevice());
			int maxColumn = IChromaSDKPlugin::Get().GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = ToBGR(row.Colors[j]);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red * redIntensity));
					green = max(0, min(255, green * greenIntensity));
					blue = max(0, min(255, blue * blueIntensity));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::MultiplyIntensityColorName(const char* path, int frameId, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensityColor(animationId, frameId, color);
}


// MULTIPLY INTENSITY RGB

void IChromaSDKPlugin::MultiplyIntensityRGB(int animationId, int frameId, int red, int green, int blue)
{
	float redIntensity = red / 255.0f;
	float greenIntensity = green / 255.0f;
	float blueIntensity = blue / 255.0f;

	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[frameId];
			int maxLeds = GetMaxLeds(animation1D->GetDevice());
			TArray<FLinearColor>& colors = frame.Colors;
			for (int i = 0; i < maxLeds; ++i)
			{
				FLinearColor& linearColor = colors[i];
				int color = ToBGR(linearColor);
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = max(0, min(255, red * redIntensity));
				green = max(0, min(255, green * greenIntensity));
				blue = max(0, min(255, blue * blueIntensity));
				color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
				colors[i] = ToLinearColor(color);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = GetMaxRow(animation2D->GetDevice());
			int maxColumn = GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					FLinearColor& linearColor = row.Colors[j];
					int color = ToBGR(linearColor);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red * redIntensity));
					green = max(0, min(255, green * greenIntensity));
					blue = max(0, min(255, blue * blueIntensity));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					row.Colors[j] = ToLinearColor(color);
				}
			}
		}
	}
	break;
	}
}

void IChromaSDKPlugin::MultiplyIntensityRGBName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensityRGB(animationId, frameId, red, green, blue);
}


// MULTIPLY INTENSITY ALL FRAMES

void IChromaSDKPlugin::MultiplyIntensityAllFrames(int animationId, float intensity)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		MultiplyIntensity(animationId, frameId, intensity);
	}
}

void IChromaSDKPlugin::MultiplyIntensityAllFramesName(const char* path, float intensity)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensityAllFrames(animationId, intensity);
}


// MULTIPLY INTENSITY COLOR ALL FRAMES

void IChromaSDKPlugin::MultiplyIntensityColorAllFrames(int animationId, int color)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		MultiplyIntensityColor(animationId, frameId, color);
	}
}

void IChromaSDKPlugin::MultiplyIntensityColorAllFramesName(const char* path, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensityColorAllFrames(animationId, color);
}


// MULTIPLY INTENSITY ALL FRAMES RGB

void IChromaSDKPlugin::MultiplyIntensityAllFramesRGB(int animationId, int red, int green, int blue)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	int frameCount = GetAnimationFrameCount(animationId);
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		MultiplyIntensityRGB(animationId, frameId, red, green, blue);
	}
}

void IChromaSDKPlugin::MultiplyIntensityAllFramesRGBName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyIntensityAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return MultiplyIntensityAllFramesRGB(animationId, red, green, blue);
}


void IChromaSDKPlugin::LoadAnimation(int animationId)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	animation->Load();
}

void IChromaSDKPlugin::LoadAnimationName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	LoadAnimation(animationId);
}

void IChromaSDKPlugin::UnloadAnimation(int animationId)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	animation->Stop();
	animation->Unload();
}

void IChromaSDKPlugin::UnloadAnimationName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UnloadAnimationName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	UnloadAnimation(animationId);
}

void IChromaSDKPlugin::SetChromaCustomFlag(int animationId, bool flag)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	Animation2D* animation2D = (Animation2D*)(animation);
	animation2D->SetChromaCustom(flag);
}

void IChromaSDKPlugin::SetChromaCustomFlagName(const char* path, bool flag)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SetChromaCustomFlagName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	SetChromaCustomFlag(animationId, flag);
}

void IChromaSDKPlugin::SetChromaCustomColorAllFrames(int animationId)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	Animation2D* animation2D = (Animation2D*)(animation);
	vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
	for (int frameId = 0; frameId < int(frames.size()); ++frameId)
	{
		FChromaSDKColorFrame2D& frame = frames[frameId];
		int maxRow = GetMaxRow(animation2D->GetDevice());
		int maxColumn = GetMaxColumn(animation2D->GetDevice());
		for (int i = 0; i < maxRow; ++i)
		{
			FChromaSDKColors& row = frame.Colors[i];
			for (int j = 0; j < maxColumn; ++j)
			{
				int color = ToBGR(row.Colors[j]);
				int customFlag = 0x1;
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16) | (customFlag << 24);
				row.Colors[j] = ToLinearColor(color);
			}
		}
	}
}

void IChromaSDKPlugin::SetChromaCustomColorAllFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SetChromaCustomColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	SetChromaCustomColorAllFrames(animationId);
}


int IChromaSDKPlugin::PreviewFrame(int animationId, int frameId)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			return -1;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 && frameId < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				TArray<FLinearColor>& colors = frame.Colors;
				FChromaSDKEffectResult result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D(animation1D->GetDevice(), colors);
				if (result.Result == 0)
				{
					UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
					UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 && frameId < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				TArray<FChromaSDKColors>& colors = frame.Colors;
				FChromaSDKEffectResult result;
				if (animation2D->UseChromaCustom())
				{
					result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectKeyboardCustom2D(colors);
				}
				else
				{
					result = UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D(animation2D->GetDevice(), colors);
				}
				if (result.Result == 0)
				{
					UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(result.EffectId);
					UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(result.EffectId);
				}
			}
		}
		break;
		}
		return animationId;
	}

	return -1;
}

void IChromaSDKPlugin::PreviewFrameName(const char* path, int frameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("PreviewFrameName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	PreviewFrame(animationId, frameId);
}


int IChromaSDKPlugin::OverrideFrameDuration(int animationId, float duration)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			return -1;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			for (int i = 0; i < int(frames.size()); ++i)
			{
				FChromaSDKColorFrame1D& frame = frames[i];
				if (duration < 0.033f)
				{
					duration = 0.033f;
				}
				frame.Duration = duration;
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int i = 0; i < int(frames.size()); ++i)
			{
				FChromaSDKColorFrame2D& frame = frames[i];
				if (duration < 0.033f)
				{
					duration = 0.033f;
				}
				frame.Duration = duration;
			}
		}
		break;
		}
		return animationId;
	}

	return -1;
}

void IChromaSDKPlugin::OverrideFrameDurationName(const char* path, float duration)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("OverrideFrameDurationName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	OverrideFrameDuration(animationId, duration);
}


// MAKE FRAMES


void IChromaSDKPlugin::MakeBlankFrames(int animationId, int frameCount, float duration, int color)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	StopAnimation(animationId);
	Animation2D* animation2D = (Animation2D*)animation;
	vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
	frames.clear();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
		frame.Duration = duration;
		frame.Colors = UChromaSDKPluginBPLibrary::CreateColors2D(animation2D->GetDevice());
		int maxRow = UChromaSDKPluginBPLibrary::GetMaxRow(animation2D->GetDevice());
		int maxColumn = UChromaSDKPluginBPLibrary::GetMaxColumn(animation2D->GetDevice());
		for (int i = 0; i < maxRow; ++i)
		{
			FChromaSDKColors& row = frame.Colors[i];
			for (int j = 0; j < maxColumn; ++j)
			{
				row.Colors[j] = ToLinearColor(color);
			}
		}
		frames.push_back(frame);
	}
}

void IChromaSDKPlugin::MakeBlankFramesName(const char* path, int frameCount, float duration, int color)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MakeBlankFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MakeBlankFrames(animationId, frameCount, duration, color);
}


void IChromaSDKPlugin::MakeBlankFramesRGB(int animationId, int frameCount, float duration, int red, int green, int blue)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	StopAnimation(animationId);
	int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
	Animation2D* animation2D = (Animation2D*)(animation);
	vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
	frames.clear();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
		frame.Duration = duration;
		frame.Colors = UChromaSDKPluginBPLibrary::CreateColors2D(animation2D->GetDevice());
		int maxRow = UChromaSDKPluginBPLibrary::GetMaxRow(animation2D->GetDevice());
		int maxColumn = UChromaSDKPluginBPLibrary::GetMaxColumn(animation2D->GetDevice());
		for (int i = 0; i < maxRow; ++i)
		{
			FChromaSDKColors& row = frame.Colors[i];
			for (int j = 0; j < maxColumn; ++j)
			{
				row.Colors[j] = ToLinearColor(color);
			}
		}
		frames.push_back(frame);
	}
}

void IChromaSDKPlugin::MakeBlankFramesRGBName(const char* path, int frameCount, float duration, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MakeBlankFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MakeBlankFramesRGB(animationId, frameCount, duration, red, green, blue);
}


// RANDOM


void IChromaSDKPlugin::MakeBlankFramesRandom(int animationId, int frameCount, float duration)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	StopAnimation(animationId);
	Animation2D* animation2D = (Animation2D*)(animation);
	vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
	frames.clear();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
		frame.Duration = duration;
		frame.Colors = UChromaSDKPluginBPLibrary::CreateColors2D(animation2D->GetDevice());
		int maxRow = UChromaSDKPluginBPLibrary::GetMaxRow(animation2D->GetDevice());
		int maxColumn = UChromaSDKPluginBPLibrary::GetMaxColumn(animation2D->GetDevice());
		for (int i = 0; i < maxRow; ++i)
		{
			FChromaSDKColors& row = frame.Colors[i];
			for (int j = 0; j < maxColumn; ++j)
			{
				int red = fastrand() % 256;
				int green = fastrand() % 256;
				int blue = fastrand() % 256;
				COLORREF color = GetRGB(red, green, blue);
				row.Colors[j] = ToLinearColor(color);
			}
		}
		frames.push_back(frame);
	}
}

void IChromaSDKPlugin::MakeBlankFramesRandomName(const char* path, int frameCount, float duration)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MakeBlankFramesRandomName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MakeBlankFramesRandom(animationId, frameCount, duration);
}


// RANDOM BLACK AND WHITE


void IChromaSDKPlugin::MakeBlankFramesRandomBlackAndWhite(int animationId, int frameCount, float duration)
{
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
	{
		return;
	}
	if (animation->GetDeviceId() != EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		return;
	}
	StopAnimation(animationId);
	Animation2D* animation2D = (Animation2D*)(animation);
	vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
	frames.clear();
	for (int frameId = 0; frameId < frameCount; ++frameId)
	{
		FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
		frame.Duration = duration;
		frame.Colors = UChromaSDKPluginBPLibrary::CreateColors2D(animation2D->GetDevice());
		int maxRow = UChromaSDKPluginBPLibrary::GetMaxRow(animation2D->GetDevice());
		int maxColumn = UChromaSDKPluginBPLibrary::GetMaxColumn(animation2D->GetDevice());
		for (int i = 0; i < maxRow; ++i)
		{
			FChromaSDKColors& row = frame.Colors[i];
			for (int j = 0; j < maxColumn; ++j)
			{
				int gray = fastrand() % 256;
				COLORREF color = RGB(gray, gray, gray);
				row.Colors[j] = ToLinearColor(color);
			}
		}
		frames.push_back(frame);
	}
}

void IChromaSDKPlugin::MakeBlankFramesRandomBlackAndWhiteName(const char* path, int frameCount, float duration)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MakeBlankFramesRandomBlackAndWhiteName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MakeBlankFramesRandomBlackAndWhite(animationId, frameCount, duration);
}


// REVERSE ALL FRAMES
void IChromaSDKPlugin::ReverseAllFrames(int animationId)
{
	StopAnimation(animationId);
	AnimationBase* animation = GetAnimationInstance(animationId);
	if (nullptr == animation)
	{
		return;
	}
	switch (animation->GetDeviceType())
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		Animation1D* animation1D = (Animation1D*)(animation);
		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		reverse(frames.begin(), frames.end());
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		reverse(frames.begin(), frames.end());
	}
	break;
	}
}
void IChromaSDKPlugin::ReverseAllFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ReverseAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	ReverseAllFrames(animationId);
}


// DUPLICATE FRAMES
void IChromaSDKPlugin::DuplicateFrames(int animationId)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("DuplicateFrames: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				newFrames.push_back(frame);
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				newFrames.push_back(frame);
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::DuplicateFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("DuplicateFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	DuplicateFrames(animationId);
}

// DUPLICATE FIRST FRAME
void IChromaSDKPlugin::DuplicateFirstFrame(int animationId, int frameCount)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("DuplicateFirstFrame: Animation is null! id=%d"), animationId);
			return;
		}
		if (animation->GetFrameCount() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("PluginDuplicateFirstFrame: Animation has no frames! id=%d"), animationId);
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			FChromaSDKColorFrame1D firstFrame = frames[0];
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				frames.push_back(firstFrame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			FChromaSDKColorFrame2D firstFrame = frames[0]; //copy
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				frames.push_back(firstFrame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::DuplicateFirstFrameName(const char* path, int frameCount)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("DuplicateFirstFrameName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	DuplicateFirstFrame(animationId, frameCount);
}

// DUPLICATE MIRROR FRAMES
void IChromaSDKPlugin::DuplicateMirrorFrames(int animationId)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("DuplicateMirrorFrames: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		if (frameCount == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("DuplicateMirrorFrames: Animation has no frames! id=%d"), animationId);
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			for (int frameId = frameCount - 1; frameId >= 0; --frameId)
			{
				FChromaSDKColorFrame1D frame = frames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = frameCount - 1; frameId >= 0; --frameId)
			{
				FChromaSDKColorFrame2D frame = frames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::DuplicateMirrorFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("DuplicateMirrorFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	DuplicateMirrorFrames(animationId);
}

// INSERT FRAME
void IChromaSDKPlugin::InsertFrame(int animationId, int sourceFrame, int targetFrame)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("InsertFrame: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		if (sourceFrame < 0 ||
			sourceFrame >= frameCount)
		{
			return;
		}
		if (targetFrame < 0 ||
			targetFrame >= frameCount)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				if (targetFrame == frameId)
				{
					FChromaSDKColorFrame1D frame = frames[sourceFrame];
					newFrames.push_back(frame);
				}

				FChromaSDKColorFrame1D frame = frames[frameId];
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				if (targetFrame == frameId)
				{
					FChromaSDKColorFrame2D frame = frames[sourceFrame];
					newFrames.push_back(frame);
				}

				FChromaSDKColorFrame2D frame = frames[frameId];
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::InsertFrameName(const char* path, int sourceFrame, int targetFrame)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("InsertFrameName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	InsertFrame(animationId, sourceFrame, targetFrame);
}

// INSERT DELAY
void IChromaSDKPlugin::InsertDelay(int animationId, int frameId, int delay)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("InsertDelay: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		if (frameId < 0 ||
			frameId >= frameCount)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int index = 0; index < frameCount; ++index)
			{
				FChromaSDKColorFrame1D frame = frames[index];
				if (index == frameId)
				{
					for (int d = 0; d < delay; ++d)
					{
						newFrames.push_back(frame);
					}
				}
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int index = 0; index < frameCount; ++index)
			{
				FChromaSDKColorFrame2D frame = frames[index];
				if (index == frameId)
				{
					for (int d = 0; d < delay; ++d)
					{
						newFrames.push_back(frame);
					}
				}
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::InsertDelayName(const char* path, int frameId, int delay)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("InsertDelayName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	InsertDelay(animationId, frameId, delay);
}

// REDUCE FRAMES
void IChromaSDKPlugin::ReduceFrames(int animationId, int n)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ReduceFrames: Animation is null! id=%d"), animationId);
			return;
		}
		if (n <= 0)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				if (frameId % n == 0)
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				if (frameId % n == 0)
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::ReduceFramesName(const char* path, int n)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ReduceFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	ReduceFrames(animationId, n);
}

// TRIM FRAME
void IChromaSDKPlugin::TrimFrame(int animationId, int frameId)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("TrimFrame: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int index = 0; index < frameCount; ++index)
			{
				if (index != frameId)
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int index = 0; index < frameCount; ++index)
			{
				if (index != frameId)
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::TrimFrameName(const char* path, int frameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("TrimFrameName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	TrimFrame(animationId, frameId);
}

// TRIM START FRAMES
void IChromaSDKPlugin::TrimStartFrames(int animationId, int numberOfFrames)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("TrimStartFrames: Animation is null! id=%d"), animationId);
			return;
		}
		if (numberOfFrames < 0)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
			for (int frameId = numberOfFrames; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
			for (int frameId = numberOfFrames; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				newFrames.push_back(frame);
			}
			frames.clear();
			for (int frameId = 0; frameId < newFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D& frame = newFrames[frameId];
				frames.push_back(frame);
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::TrimStartFramesName(const char* path, int numberOfFrames)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("TrimStartFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	TrimStartFrames(animationId, numberOfFrames);
}

// TRIM END FRAMES
void IChromaSDKPlugin::TrimEndFrames(int animationId, int lastFrameId)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("TrimEndFrames: Animation is null! id=%d"), animationId);
			return;
		}
		if (lastFrameId <= 0)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			while (lastFrameId > frames.size())
			{
				frames.pop_back();
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			while (lastFrameId > frames.size())
			{
				frames.pop_back();
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::TrimEndFramesName(const char* path, int lastFrameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("TrimEndFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	TrimEndFrames(animationId, lastFrameId);
}

// FADE START FRAMES
void IChromaSDKPlugin::FadeStartFrames(int animationId, int fade)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("FadeStartFrames: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		if (fade <= 0 ||
			fade >= frameCount)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			int maxLeds = GetMaxLeds(animation1D->GetDevice());
			for (int frameId = 0; frameId < fade; ++frameId)
			{
				float intensity = (frameId + 1) / (float)fade;
				FChromaSDKColorFrame1D& frame = frames[frameId];
				TArray<FLinearColor>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					FLinearColor& linearColor = colors[i];
					int color = ToBGR(linearColor);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red * intensity));
					green = max(0, min(255, green * intensity));
					blue = max(0, min(255, blue * intensity));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = ToLinearColor(color);
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			int maxRow = GetMaxRow(animation2D->GetDevice());
			int maxColumn = GetMaxColumn(animation2D->GetDevice());
			for (int frameId = 0; frameId < fade; ++frameId)
			{
				float intensity = (frameId + 1) / (float)fade;
				FChromaSDKColorFrame2D& frame = frames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						FLinearColor& linearColor = row.Colors[j];
						int color = ToBGR(linearColor);
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, red * intensity));
						green = max(0, min(255, green * intensity));
						blue = max(0, min(255, blue * intensity));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::FadeStartFramesName(const char* path, int fade)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FadeStartFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FadeStartFrames(animationId, fade);
}

// FADE END FRAMES
void IChromaSDKPlugin::FadeEndFrames(int animationId, int fade)
{
	StopAnimation(animationId);

	if (_mAnimations.find(animationId) != _mAnimations.end())
	{
		AnimationBase* animation = _mAnimations[animationId];
		if (animation == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("FadeEndFrames: Animation is null! id=%d"), animationId);
			return;
		}
		int frameCount = animation->GetFrameCount();
		if (fade <= 0 ||
			fade >= frameCount)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			int maxLeds = GetMaxLeds(animation1D->GetDevice());
			for (int offset = 0; offset < fade; ++offset)
			{
				int frameId = frameCount - 1 - offset;
				float intensity = (frameId + 1) / (float)fade;
				FChromaSDKColorFrame1D& frame = frames[frameId];
				TArray<FLinearColor>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					FLinearColor& linearColor = colors[i];
					int color = ToBGR(linearColor);
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red * intensity));
					green = max(0, min(255, green * intensity));
					blue = max(0, min(255, blue * intensity));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = ToLinearColor(color);
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			int maxRow = GetMaxRow(animation2D->GetDevice());
			int maxColumn = GetMaxColumn(animation2D->GetDevice());
			for (int frameId = 0; frameId < fade; ++frameId)
			{
				float intensity = (frameId + 1) / (float)fade;
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = GetMaxRow(animation2D->GetDevice());
				int maxColumn = GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						FLinearColor& linearColor = row.Colors[j];
						int color = ToBGR(linearColor);
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, red * intensity));
						green = max(0, min(255, green * intensity));
						blue = max(0, min(255, blue * intensity));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = ToLinearColor(color);
					}
				}
			}
		}
		break;
		}
	}
}
void IChromaSDKPlugin::FadeEndFramesName(const char* path, int fade)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FadeEndFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FadeEndFrames(animationId, fade);
}


// COPY ANIMATION
int IChromaSDKPlugin::CopyAnimation(int sourceAnimationId, const char* targetAnimation)
{
	return 0;
}
void IChromaSDKPlugin::CopyAnimationName(const char* sourceAnimation, const char* targetAnimation)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyAnimationName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	CopyAnimation(sourceAnimationId, targetAnimation);
}


// APPEND ALL FRAMES
void IChromaSDKPlugin::AppendAllFrames(int sourceAnimationId, int targetAnimationId)
{

}
void IChromaSDKPlugin::AppendAllFramesName(const char* sourceAnimation, const char* targetAnimation)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AppendAllFramesName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AppendAllFramesName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	AppendAllFrames(sourceAnimationId, targetAnimationId);
}


// INVERT ALL COLORS
void IChromaSDKPlugin::InvertColors(int animationId, int frameId)
{

}
void IChromaSDKPlugin::InvertColorsName(const char* path, int frameId)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("InvertColorsName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	InvertColors(animationId, frameId);
}

// ALL FRAMES
void IChromaSDKPlugin::InvertColorsAllFrames(int animationId)
{

}
void IChromaSDKPlugin::InvertColorsAllFramesName(const char* path)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("InvertColorsAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	InvertColorsAllFrames(animationId);
}


// COPY NONZERO TARGET
void IChromaSDKPlugin::CopyNonZeroTargetAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
{

}
void IChromaSDKPlugin::CopyNonZeroTargetAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroTargetAllKeys(sourceAnimationId, targetAnimationId, frameId);
}


// ALL FRAMES
void IChromaSDKPlugin::CopyNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
{

}
void IChromaSDKPlugin::CopyNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
}


// ADD NONZERO TARGET
void IChromaSDKPlugin::AddNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
{

}
void IChromaSDKPlugin::AddNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	AddNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
}


// SUBTRACT NONZERO TARGET ALL FRAMES
void IChromaSDKPlugin::SubtractNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
{

}
void IChromaSDKPlugin::SubtractNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	SubtractNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
}


// COPY NONZERO TARGET ALL FRAMES
void IChromaSDKPlugin::CopyNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
{

}
void IChromaSDKPlugin::CopyNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
}


// ADD NONZERO TARGET ALL FRAMES OFFSET
void IChromaSDKPlugin::AddNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
{

}
void IChromaSDKPlugin::AddNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AddNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	AddNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
}


// SUBTRACT NONZERO TARGET ALL FRAMES OFFSET
void IChromaSDKPlugin::SubtractNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
{

}
void IChromaSDKPlugin::SubtractNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SubtractNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	SubtractNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
}


// MULTIPLY COLOR LERP ALL FRAMES
void IChromaSDKPlugin::MultiplyColorLerpAllFrames(int animationId, int color1, int color2)
{

}
void IChromaSDKPlugin::MultiplyColorLerpAllFramesName(const char* path, int color1, int color2)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyColorLerpAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MultiplyColorLerpAllFrames(animationId, color1, color2);
}


// MULTIPLY TARGET COLOR LERP ALL FRAMES
void IChromaSDKPlugin::MultiplyTargetColorLerpAllFrames(int animationId, int color1, int color2)
{

}
void IChromaSDKPlugin::MultiplyTargetColorLerpAllFramesName(const char* path, int color1, int color2)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyTargetColorLerpAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MultiplyTargetColorLerpAllFrames(animationId, color1, color2);
}


// FILL THRESHOLD RGB COLORS ALL FRAMES RGB
void IChromaSDKPlugin::FillThresholdRGBColorsAllFramesRGB(int animationId, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
{

}
void IChromaSDKPlugin::FillThresholdRGBColorsAllFramesRGBName(const char* path, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillThresholdRGBColorsAllFramesRGBName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	FillThresholdRGBColorsAllFramesRGB(animationId, redThreshold, greenThreshold, blueThreshold, red, green, blue);
}


// MULTIPLY NONZERO TARGET COLOR LERP ALL FRAMES
void IChromaSDKPlugin::MultiplyNonZeroTargetColorLerpAllFrames(int animationId, int color1, int color2)
{

}
void IChromaSDKPlugin::MultiplyNonZeroTargetColorLerpAllFramesName(const char* path, int color1, int color2)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("MultiplyNonZeroTargetColorLerpAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	MultiplyNonZeroTargetColorLerpAllFrames(animationId, color1, color2);
}


// VALIDATE DLL METHODS

bool IChromaSDKPlugin::ValidateGetProcAddress(bool condition, FString methodName)
{
	if (condition)
	{
		UE_LOG(LogTemp, Error, TEXT("ChromaSDKPlugin failed to load %s!"), *methodName);
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("ChromaSDKPlugin loaded %s."), *methodName);
	}
	return condition;
}

#include "HideWindowsPlatformTypes.h"

#endif
