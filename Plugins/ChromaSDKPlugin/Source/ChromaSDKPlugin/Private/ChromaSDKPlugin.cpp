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


void IChromaSDKPlugin::CopyAllKeysColor(int sourceAnimationId, int targetAnimationId, int frameId)
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

void IChromaSDKPlugin::CopyAllKeysColorName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyAllKeysColorName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyAllKeysColorName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyAllKeysColor(sourceAnimationId, targetAnimationId, frameId);
}


void IChromaSDKPlugin::CopyNonZeroAllKeysColor(int sourceAnimationId, int targetAnimationId, int frameId)
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

void IChromaSDKPlugin::CopyNonZeroAllKeysColorName(const char* sourceAnimation, const char* targetAnimation, int frameId)
{
	int sourceAnimationId = GetAnimation(sourceAnimation);
	if (sourceAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysColorName: Source Animation not found! %s"), *FString(UTF8_TO_TCHAR(sourceAnimation)));
		return;
	}
	int targetAnimationId = GetAnimation(targetAnimation);
	if (targetAnimationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("CopyNonZeroAllKeysColorName: Target Animation not found! %s"), *FString(UTF8_TO_TCHAR(targetAnimation)));
		return;
	}
	CopyNonZeroAllKeysColor(sourceAnimationId, targetAnimationId, frameId);
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


void IChromaSDKPlugin::FillColor(int animationId, int frameId, int red, int green, int blue)
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
void IChromaSDKPlugin::FillColorName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColor(animationId, frameId, red, green, blue);
}

void IChromaSDKPlugin::FillColorAllFrames(int animationId, int red, int green, int blue)
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
		FillColor(animationId, frameId, red, green, blue);
	}
}
void IChromaSDKPlugin::FillColorAllFramesName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillColorAllFrames(animationId, red, green, blue);
}


void IChromaSDKPlugin::FillNonZeroColor(int animationId, int frameId, int red, int green, int blue)
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
void IChromaSDKPlugin::FillNonZeroColorName(const char* path, int frameId, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColor(animationId, frameId, red, green, blue);
}


void IChromaSDKPlugin::FillNonZeroColorAllFrames(int animationId, int red, int green, int blue)
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
		FillNonZeroColor(animationId, frameId, red, green, blue);
	}
}
void IChromaSDKPlugin::FillNonZeroColorAllFramesName(const char* path, int red, int green, int blue)
{
	int animationId = GetAnimation(path);
	if (animationId < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FillNonZeroColorAllFramesName: Animation not found! %s"), *FString(UTF8_TO_TCHAR(path)));
		return;
	}
	return FillNonZeroColorAllFrames(animationId, red, green, blue);
}


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
