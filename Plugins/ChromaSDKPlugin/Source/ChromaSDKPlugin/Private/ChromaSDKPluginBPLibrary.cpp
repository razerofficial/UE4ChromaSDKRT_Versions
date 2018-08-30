// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

//#include "ChromaSDKPluginBPLibrary.h" //___HACK_UE4_VERSION_4_16_OR_GREATER
#include "ChromaSDKPluginPrivatePCH.h"
#include "ChromaSDKPluginBPLibrary.h" //___HACK_UE4_VERSION_4_15_OR_LESS
#include "ChromaSDKPluginAnimation1DObject.h"
#include "ChromaSDKPluginAnimation2DObject.h"

#if PLATFORM_WINDOWS

#include "AllowWindowsPlatformTypes.h" 

using namespace ChromaSDK;
using namespace std;

IChromaSDKPlugin UChromaSDKPluginBPLibrary::_sIChromaSDKPlugin;

// keyboard map
std::map<EChromaSDKKeyboardKey::Type, int> UChromaSDKPluginBPLibrary::_sKeyboardEnumMap =
std::map<EChromaSDKKeyboardKey::Type, int>();

// mouse map
std::map<EChromaSDKMouseLed::Type, ChromaSDK::Mouse::RZLED2> UChromaSDKPluginBPLibrary::_sMouseEnumMap =
std::map<EChromaSDKMouseLed::Type, ChromaSDK::Mouse::RZLED2>();

#endif

UChromaSDKPluginBPLibrary::UChromaSDKPluginBPLibrary(const FPostConstructInitializeProperties& PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
	: Super(PCIP) //___HACK_UE4_VERSION_4_8_OR_LESS
//UChromaSDKPluginBPLibrary::UChromaSDKPluginBPLibrary(const FObjectInitializer& ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
//	: Super(ObjectInitializer) //___HACK_UE4_VERSION_4_9_OR_GREATER
{
#if PLATFORM_WINDOWS
	// keyboard mapping
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ESC] = Keyboard::RZKEY::RZKEY_ESC;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F1] = Keyboard::RZKEY::RZKEY_F1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F2] = Keyboard::RZKEY::RZKEY_F2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F3] = Keyboard::RZKEY::RZKEY_F3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F4] = Keyboard::RZKEY::RZKEY_F4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F5] = Keyboard::RZKEY::RZKEY_F5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F6] = Keyboard::RZKEY::RZKEY_F6;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F7] = Keyboard::RZKEY::RZKEY_F7;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F8] = Keyboard::RZKEY::RZKEY_F8;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F9] = Keyboard::RZKEY::RZKEY_F9;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F10] = Keyboard::RZKEY::RZKEY_F10;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F11] = Keyboard::RZKEY::RZKEY_F11;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F12] = Keyboard::RZKEY::RZKEY_F12;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_1] = Keyboard::RZKEY::RZKEY_1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_2] = Keyboard::RZKEY::RZKEY_2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_3] = Keyboard::RZKEY::RZKEY_3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_4] = Keyboard::RZKEY::RZKEY_4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_5] = Keyboard::RZKEY::RZKEY_5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_6] = Keyboard::RZKEY::RZKEY_6;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_7] = Keyboard::RZKEY::RZKEY_7;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_8] = Keyboard::RZKEY::RZKEY_8;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_9] = Keyboard::RZKEY::RZKEY_9;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_0] = Keyboard::RZKEY::RZKEY_0;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_A] = Keyboard::RZKEY::RZKEY_A;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_B] = Keyboard::RZKEY::RZKEY_B;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_C] = Keyboard::RZKEY::RZKEY_C;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_D] = Keyboard::RZKEY::RZKEY_D;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_E] = Keyboard::RZKEY::RZKEY_E;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F] = Keyboard::RZKEY::RZKEY_F;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_G] = Keyboard::RZKEY::RZKEY_G;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_H] = Keyboard::RZKEY::RZKEY_H;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_I] = Keyboard::RZKEY::RZKEY_I;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_J] = Keyboard::RZKEY::RZKEY_J;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_K] = Keyboard::RZKEY::RZKEY_K;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_L] = Keyboard::RZKEY::RZKEY_L;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_M] = Keyboard::RZKEY::RZKEY_M;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_N] = Keyboard::RZKEY::RZKEY_N;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_O] = Keyboard::RZKEY::RZKEY_O;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_P] = Keyboard::RZKEY::RZKEY_P;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Q] = Keyboard::RZKEY::RZKEY_Q;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_R] = Keyboard::RZKEY::RZKEY_R;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_S] = Keyboard::RZKEY::RZKEY_S;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_T] = Keyboard::RZKEY::RZKEY_T;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_U] = Keyboard::RZKEY::RZKEY_U;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_V] = Keyboard::RZKEY::RZKEY_V;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_W] = Keyboard::RZKEY::RZKEY_W;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_X] = Keyboard::RZKEY::RZKEY_X;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Y] = Keyboard::RZKEY::RZKEY_Y;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Z] = Keyboard::RZKEY::RZKEY_Z;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMLOCK] = Keyboard::RZKEY::RZKEY_NUMLOCK;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD0] = Keyboard::RZKEY::RZKEY_NUMPAD0;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD1] = Keyboard::RZKEY::RZKEY_NUMPAD1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD2] = Keyboard::RZKEY::RZKEY_NUMPAD2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD3] = Keyboard::RZKEY::RZKEY_NUMPAD3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD4] = Keyboard::RZKEY::RZKEY_NUMPAD4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD5] = Keyboard::RZKEY::RZKEY_NUMPAD5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD6] = Keyboard::RZKEY::RZKEY_NUMPAD6;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD7] = Keyboard::RZKEY::RZKEY_NUMPAD7;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD8] = Keyboard::RZKEY::RZKEY_NUMPAD8;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD9] = Keyboard::RZKEY::RZKEY_NUMPAD9;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DIVIDE] = Keyboard::RZKEY::RZKEY_NUMPAD_DIVIDE;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_MULTIPLY] = Keyboard::RZKEY::RZKEY_NUMPAD_MULTIPLY;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_SUBTRACT] = Keyboard::RZKEY::RZKEY_NUMPAD_SUBTRACT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ADD] = Keyboard::RZKEY::RZKEY_NUMPAD_ADD;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ENTER] = Keyboard::RZKEY::RZKEY_NUMPAD_ENTER;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DECIMAL] = Keyboard::RZKEY::RZKEY_NUMPAD_DECIMAL;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PRINTSCREEN] = Keyboard::RZKEY::RZKEY_PRINTSCREEN;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SCROLL] = Keyboard::RZKEY::RZKEY_SCROLL;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAUSE] = Keyboard::RZKEY::RZKEY_PAUSE;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INSERT] = Keyboard::RZKEY::RZKEY_INSERT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_HOME] = Keyboard::RZKEY::RZKEY_HOME;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEUP] = Keyboard::RZKEY::RZKEY_PAGEUP;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DELETE] = Keyboard::RZKEY::RZKEY_DELETE;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_END] = Keyboard::RZKEY::RZKEY_END;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEDOWN] = Keyboard::RZKEY::RZKEY_PAGEDOWN;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_UP] = Keyboard::RZKEY::RZKEY_UP;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LEFT] = Keyboard::RZKEY::RZKEY_LEFT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DOWN] = Keyboard::RZKEY::RZKEY_DOWN;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RIGHT] = Keyboard::RZKEY::RZKEY_RIGHT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_TAB] = Keyboard::RZKEY::RZKEY_TAB;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_CAPSLOCK] = Keyboard::RZKEY::RZKEY_CAPSLOCK;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_BACKSPACE] = Keyboard::RZKEY::RZKEY_BACKSPACE;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ENTER] = Keyboard::RZKEY::RZKEY_ENTER;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LCTRL] = Keyboard::RZKEY::RZKEY_LCTRL;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LWIN] = Keyboard::RZKEY::RZKEY_LWIN;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LALT] = Keyboard::RZKEY::RZKEY_LALT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SPACE] = Keyboard::RZKEY::RZKEY_SPACE;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RALT] = Keyboard::RZKEY::RZKEY_RALT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_FN] = Keyboard::RZKEY::RZKEY_FN;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RMENU] = Keyboard::RZKEY::RZKEY_RMENU;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RCTRL] = Keyboard::RZKEY::RZKEY_RCTRL;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LSHIFT] = Keyboard::RZKEY::RZKEY_LSHIFT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RSHIFT] = Keyboard::RZKEY::RZKEY_RSHIFT;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO1] = Keyboard::RZKEY::RZKEY_MACRO1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO2] = Keyboard::RZKEY::RZKEY_MACRO2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO3] = Keyboard::RZKEY::RZKEY_MACRO3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO4] = Keyboard::RZKEY::RZKEY_MACRO4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO5] = Keyboard::RZKEY::RZKEY_MACRO5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_1] = Keyboard::RZKEY::RZKEY_OEM_1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_2] = Keyboard::RZKEY::RZKEY_OEM_2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_3] = Keyboard::RZKEY::RZKEY_OEM_3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_4] = Keyboard::RZKEY::RZKEY_OEM_4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_5] = Keyboard::RZKEY::RZKEY_OEM_5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_6] = Keyboard::RZKEY::RZKEY_OEM_6;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_7] = Keyboard::RZKEY::RZKEY_OEM_7;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_8] = Keyboard::RZKEY::RZKEY_OEM_8;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_9] = Keyboard::RZKEY::RZKEY_OEM_9;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_10] = Keyboard::RZKEY::RZKEY_OEM_10;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_11] = Keyboard::RZKEY::RZKEY_OEM_11;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_1] = Keyboard::RZKEY::RZKEY_EUR_1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_2] = Keyboard::RZKEY::RZKEY_EUR_2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_1] = Keyboard::RZKEY::RZKEY_JPN_1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_2] = Keyboard::RZKEY::RZKEY_JPN_2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_3] = Keyboard::RZKEY::RZKEY_JPN_3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_4] = Keyboard::RZKEY::RZKEY_JPN_4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_5] = Keyboard::RZKEY::RZKEY_JPN_5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_1] = Keyboard::RZKEY::RZKEY_KOR_1;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_2] = Keyboard::RZKEY::RZKEY_KOR_2;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_3] = Keyboard::RZKEY::RZKEY_KOR_3;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_4] = Keyboard::RZKEY::RZKEY_KOR_4;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_5] = Keyboard::RZKEY::RZKEY_KOR_5;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_6] = Keyboard::RZKEY::RZKEY_KOR_6;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_7] = Keyboard::RZKEY::RZKEY_KOR_7;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LOGO] = Keyboard::RZLED::RZLED_LOGO;
	_sKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INVALID] = Keyboard::RZKEY::RZKEY_INVALID;

	// mouse mapping
	_sMouseEnumMap[EChromaSDKMouseLed::ML_SCROLLWHEEL] = Mouse::RZLED2::RZLED2_SCROLLWHEEL;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LOGO] = Mouse::RZLED2::RZLED2_LOGO;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BACKLIGHT] = Mouse::RZLED2::RZLED2_BACKLIGHT;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE1] = Mouse::RZLED2::RZLED2_LEFT_SIDE1;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE2] = Mouse::RZLED2::RZLED2_LEFT_SIDE2;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE3] = Mouse::RZLED2::RZLED2_LEFT_SIDE3;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE4] = Mouse::RZLED2::RZLED2_LEFT_SIDE4;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE5] = Mouse::RZLED2::RZLED2_LEFT_SIDE5;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE6] = Mouse::RZLED2::RZLED2_LEFT_SIDE6;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE7] = Mouse::RZLED2::RZLED2_LEFT_SIDE7;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM1] = Mouse::RZLED2::RZLED2_BOTTOM1;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM2] = Mouse::RZLED2::RZLED2_BOTTOM2;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM3] = Mouse::RZLED2::RZLED2_BOTTOM3;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM4] = Mouse::RZLED2::RZLED2_BOTTOM4;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM5] = Mouse::RZLED2::RZLED2_BOTTOM5;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE1] = Mouse::RZLED2::RZLED2_RIGHT_SIDE1;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE2] = Mouse::RZLED2::RZLED2_RIGHT_SIDE2;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE3] = Mouse::RZLED2::RZLED2_RIGHT_SIDE3;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE4] = Mouse::RZLED2::RZLED2_RIGHT_SIDE4;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE5] = Mouse::RZLED2::RZLED2_RIGHT_SIDE5;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE6] = Mouse::RZLED2::RZLED2_RIGHT_SIDE6;
	_sMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE7] = Mouse::RZLED2::RZLED2_RIGHT_SIDE7;

	_sIChromaSDKPlugin = IChromaSDKPlugin::Get();
#endif
}

bool UChromaSDKPluginBPLibrary::IsPlatformWindows()
{
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

int32 UChromaSDKPluginBPLibrary::GetMaxLeds(EChromaSDKDevice1DEnum::Type device)
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

int UChromaSDKPluginBPLibrary::GetMaxRow(EChromaSDKDevice2DEnum::Type device)
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

int UChromaSDKPluginBPLibrary::GetMaxColumn(EChromaSDKDevice2DEnum::Type device)
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

FLinearColor UChromaSDKPluginBPLibrary::GetRGB(int32 red, int32 green, int32 blue)
{
	FLinearColor color = FLinearColor(red/255.0f, green/255.0f, blue/255.0f, 1.0f);
	return color;
}

int32 UChromaSDKPluginBPLibrary::ToBGR(const FLinearColor& colorParam)
{
	return IChromaSDKPlugin::ToBGR(colorParam);
}

FLinearColor UChromaSDKPluginBPLibrary::ToLinearColor(int32 colorParam)
{
	return IChromaSDKPlugin::ToLinearColor(colorParam);
}

float UChromaSDKPluginBPLibrary::Lerp(float start, float end, float amt)
{
	return (1 - amt)*start + amt * end;
}

int32 UChromaSDKPluginBPLibrary::LerpColorBGR(int from, int to, float t)
{
	int red = floor(Lerp((from & 0xFF), (to & 0xFF), t));
	int green = floor(Lerp((from & 0xFF00) >> 8, (to & 0xFF00) >> 8, t));
	int blue = floor(Lerp((from & 0xFF0000) >> 16, (to & 0xFF0000) >> 16, t));
	int color = red | (green << 8) | (blue << 16);
	return color;
}

FLinearColor UChromaSDKPluginBPLibrary::LerpColor(FLinearColor colorParam1, FLinearColor colorParam2, float t)
{
	int color1 = ToBGR(colorParam1);
	int color2 = ToBGR(colorParam2);
	int color = LerpColorBGR(color1, color2, t);
	return ToLinearColor(color);
}

TArray<FLinearColor> UChromaSDKPluginBPLibrary::CreateColors1D(EChromaSDKDevice1DEnum::Type device)
{
	TArray<FLinearColor> colors = TArray<FLinearColor>();
#if PLATFORM_WINDOWS
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		FLinearColor color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
		colors.Add(color);
	}
#endif
	return colors;
}

TArray<FChromaSDKColors> UChromaSDKPluginBPLibrary::CreateColors2D(EChromaSDKDevice2DEnum::Type device)
{
	TArray<FChromaSDKColors> result = TArray<FChromaSDKColors>();
#if PLATFORM_WINDOWS
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			FLinearColor color = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
			row.Colors.Add(color);
		}
		result.Add(row);
	}
#endif
	return result;
}

// RANDOM

TArray<FLinearColor> UChromaSDKPluginBPLibrary::CreateRandomColors1D(EChromaSDKDevice1DEnum::Type device)
{
	TArray<FLinearColor> colors = TArray<FLinearColor>();
#if PLATFORM_WINDOWS
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		float red = FMath::FRandRange(0.0f, 1.0f);
		float green = FMath::FRandRange(0.0f, 1.0f);
		float blue = FMath::FRandRange(0.0f, 1.0f);
		float alpha = 1.0f;
		FLinearColor color = FLinearColor(red, green, blue, alpha);
		colors.Add(color);
	}
#endif
	return colors;
}

TArray<FChromaSDKColors> UChromaSDKPluginBPLibrary::CreateRandomColors2D(EChromaSDKDevice2DEnum::Type device)
{
	TArray<FChromaSDKColors> result = TArray<FChromaSDKColors>();
#if PLATFORM_WINDOWS
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			float red = FMath::FRandRange(0.0f, 1.0f);
			float green = FMath::FRandRange(0.0f, 1.0f);
			float blue = FMath::FRandRange(0.0f, 1.0f);
			float alpha = 1.0f;
			FLinearColor color = FLinearColor(red, green, blue, alpha);
			row.Colors.Add(color);
		}
		result.Add(row);
	}
#endif
	return result;
}

// RANDOM BLACK AND WHITE

TArray<FLinearColor> UChromaSDKPluginBPLibrary::CreateRandomColorsBlackAndWhite1D(EChromaSDKDevice1DEnum::Type device)
{
	TArray<FLinearColor> colors = TArray<FLinearColor>();
#if PLATFORM_WINDOWS
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		float gray = FMath::FRandRange(0.0f, 1.0f);
		float alpha = 1.0f;
		FLinearColor color = FLinearColor(gray, gray, gray, alpha);
		colors.Add(color);
	}
#endif
	return colors;
}

TArray<FChromaSDKColors> UChromaSDKPluginBPLibrary::CreateRandomColorsBlackAndWhite2D(EChromaSDKDevice2DEnum::Type device)
{
	TArray<FChromaSDKColors> result = TArray<FChromaSDKColors>();
#if PLATFORM_WINDOWS
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			float gray = FMath::FRandRange(0.0f, 1.0f);
			float alpha = 1.0f;
			FLinearColor color = FLinearColor(gray, gray, gray, alpha);
			row.Colors.Add(color);
		}
		result.Add(row);
	}
#endif
	return result;
}

void UChromaSDKPluginBPLibrary::SetKeyboardKeyColor(EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam, TArray<FChromaSDKColors>& colors)
{
#if PLATFORM_WINDOWS
	int maxRow = ChromaSDK::Keyboard::MAX_ROW;
	int maxColumn = ChromaSDK::Keyboard::MAX_COLUMN;
	if (maxRow != colors.Num() ||
		colors.Num() == 0 ||
		maxColumn != colors[0].Colors.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::SetKeyboardKeyColor Array size mismatch row: %d==%d column: %d==%d!"),
			maxRow,
			colors.Num(),
			maxColumn,
			colors.Num() > 0 ? colors[0].Colors.Num() : 0);
		return;
	}

	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = colorParam;
	}
#endif
}

FLinearColor UChromaSDKPluginBPLibrary::GetKeyboardKeyColor(EChromaSDKKeyboardKey::Type key, TArray<FChromaSDKColors>& colors)
{
#if PLATFORM_WINDOWS
	int maxRow = ChromaSDK::Keyboard::MAX_ROW;
	int maxColumn = ChromaSDK::Keyboard::MAX_COLUMN;
	if (maxRow != colors.Num() ||
		colors.Num() == 0 ||
		maxColumn != colors[0].Colors.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::GetKeyboardKeyColor Array size mismatch row: %d==%d column: %d==%d!"),
			maxRow,
			colors.Num(),
			maxColumn,
			colors.Num() > 0 ? colors[0].Colors.Num() : 0);
		return FLinearColor(0, 0, 0, 0);
	}

	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		return colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
	}
#endif
	return FLinearColor(0, 0, 0, 0);
}

void UChromaSDKPluginBPLibrary::SetMouseLedColor(EChromaSDKMouseLed::Type led, const FLinearColor& colorParam, TArray<FChromaSDKColors>& colors)
{
#if PLATFORM_WINDOWS
	int maxRow = ChromaSDK::Mouse::MAX_ROW;
	int maxColumn = ChromaSDK::Mouse::MAX_COLUMN;
	if (maxRow != colors.Num() ||
		colors.Num() == 0 ||
		maxColumn != colors[0].Colors.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::SetMouseLedColor Array size mismatch row: %d==%d column: %d==%d!"),
			maxRow,
			colors.Num(),
			maxColumn,
			colors.Num() > 0 ? colors[0].Colors.Num() : 0);
		return;
	}

	ChromaSDK::Mouse::RZLED2 rzled = _sMouseEnumMap[led];
	colors[HIBYTE(rzled)].Colors[LOBYTE(rzled)] = colorParam;
#endif
}

FLinearColor UChromaSDKPluginBPLibrary::GetMouseLedColor(EChromaSDKMouseLed::Type led, TArray<FChromaSDKColors>& colors)
{
#if PLATFORM_WINDOWS
	int maxRow = ChromaSDK::Mouse::MAX_ROW;
	int maxColumn = ChromaSDK::Mouse::MAX_COLUMN;
	if (maxRow != colors.Num() ||
		colors.Num() == 0 ||
		maxColumn != colors[0].Colors.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::SetMouseLedColor Array size mismatch row: %d==%d column: %d==%d!"),
			maxRow,
			colors.Num(),
			maxColumn,
			colors.Num() > 0 ? colors[0].Colors.Num() : 0);
		return FLinearColor(0, 0, 0, 0);
	}

	ChromaSDK::Mouse::RZLED2 rzled = _sMouseEnumMap[led];
	return colors[HIBYTE(rzled)].Colors[LOBYTE(rzled)];
#endif
	return FLinearColor(0, 0, 0, 0);
}

bool UChromaSDKPluginBPLibrary::IsInitialized()
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.IsInitialized();
#else
	return false;
#endif
}

int32 UChromaSDKPluginBPLibrary::ChromaSDKInit()
{
#if PLATFORM_WINDOWS
	if (!_sIChromaSDKPlugin.IsInitialized())
	{
		// Init the SDK
		int result = _sIChromaSDKPlugin.ChromaSDKInit();
		return result;
	}
	else
	{
		return -1;
	}
#else
	return -1;
#endif
}

int32 UChromaSDKPluginBPLibrary::ChromaSDKUnInit()
{
#if PLATFORM_WINDOWS
	// unload any 1D animation effects
	for (TObjectIterator<UChromaSDKPluginAnimation1DObject> iterator; iterator; ++iterator)
	{
		UChromaSDKPluginAnimation1DObject* item = *iterator;
		if (item != nullptr &&
			item->IsLoaded())
		{
			item->Unload();
		}
	}

	// unload any 2D animation effects
	for (TObjectIterator<UChromaSDKPluginAnimation2DObject> iterator; iterator; ++iterator)
	{
		UChromaSDKPluginAnimation2DObject* item = *iterator;
		if (item != nullptr &&
			item->IsLoaded())
		{
			item->Unload();
		}
	}

	// UnInit the SDK
	UE_LOG(LogTemp, Log, TEXT("UChromaSDKPluginBPLibrary:: Uninit"));
	if (_sIChromaSDKPlugin.IsInitialized())
	{
		int result = _sIChromaSDKPlugin.ChromaSDKUnInit();
		return _sIChromaSDKPlugin.ChromaSDKUnInit();
	}
	else
	{
		return -1;
	}
#else
	return -1;
#endif
}

FChromaSDKEffectResult UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectNone(EChromaSDKDeviceEnum::Type device)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

#if PLATFORM_WINDOWS

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_ChromaLink:
		result = _sIChromaSDKPlugin.ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDeviceEnum::DE_Headset:
		result = _sIChromaSDKPlugin.ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDeviceEnum::DE_Keyboard:
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDeviceEnum::DE_Keypad:
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDeviceEnum::DE_Mouse:
		result = _sIChromaSDKPlugin.ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDeviceEnum::DE_Mousepad:
		result = _sIChromaSDKPlugin.ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, &effectId);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectNone Unsupported device used!"));
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

#endif

	return data;
}

FChromaSDKEffectResult UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic(EChromaSDKDeviceEnum::Type device, const FLinearColor& colorParam)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

#if PLATFORM_WINDOWS

	//UE_LOG(LogTemp, Log, TEXT("ChromaSDKPlugin:: Color R=%f G=%f B=%f"), color.R, color.G, color.B);	
	int red = colorParam.R * 255;
	int green = colorParam.G * 255;
	int blue = colorParam.B * 255;

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_ChromaLink:
	{
		ChromaSDK::ChromaLink::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		result = _sIChromaSDKPlugin.ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDeviceEnum::DE_Headset:
	{
		ChromaSDK::Headset::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		result = _sIChromaSDKPlugin.ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDeviceEnum::DE_Keyboard:
	{
		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDeviceEnum::DE_Keypad:
	{
		ChromaSDK::Keypad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDeviceEnum::DE_Mouse:
	{
		ChromaSDK::Mouse::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		pParam.LEDId = ChromaSDK::Mouse::RZLED_ALL;
		result = _sIChromaSDKPlugin.ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDeviceEnum::DE_Mousepad:
	{
		ChromaSDK::Mousepad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = RGB(red, green, blue);
		result = _sIChromaSDKPlugin.ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectStatic Unsupported device used!"));
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

#endif

	return data;
}

FChromaSDKEffectResult UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D(EChromaSDKDevice1DEnum::Type device, const TArray<FLinearColor>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

#if PLATFORM_WINDOWS

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxLeds = 0;
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
	{
		maxLeds = ChromaSDK::ChromaLink::MAX_LEDS;
		if (maxLeds != colors.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D Array size mismatch elements: %d==%d!"),
				maxLeds,
				colors.Num());
			break;
		}
		ChromaSDK::ChromaLink::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			const FLinearColor& color = colors[i];
			int red = color.R * 255;
			int green = color.G * 255;
			int blue = color.B * 255;
			pParam.Color[i] = RGB(red, green, blue);
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		maxLeds = ChromaSDK::Headset::MAX_LEDS;
		if (maxLeds != colors.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D Array size mismatch elements: %d==%d!"),
				maxLeds,
				colors.Num());
			break;
		}
		ChromaSDK::Headset::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			const FLinearColor& color = colors[i];
			int red = color.R * 255;
			int green = color.G * 255;
			int blue = color.B * 255;
			pParam.Color[i] = RGB(red, green, blue);
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		maxLeds = ChromaSDK::Mousepad::MAX_LEDS;
		if (maxLeds != colors.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D Array size mismatch elements: %d==%d!"),
				maxLeds,
				colors.Num());
			break;
		}
		ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			const FLinearColor& color = colors[i];
			int red = color.R * 255;
			int green = color.G * 255;
			int blue = color.B * 255;
			pParam.Color[i] = RGB(red, green, blue);
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom1D Unsupported device used!"));
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

#endif

	return data;
}

FChromaSDKEffectResult UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D(EChromaSDKDevice2DEnum::Type device, const TArray<FChromaSDKColors>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

#if PLATFORM_WINDOWS

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = 0;
	int maxColumn = 0;
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	{
		maxRow = ChromaSDK::Keyboard::MAX_ROW;
		maxColumn = ChromaSDK::Keyboard::MAX_COLUMN;
		if (maxRow != colors.Num() ||
			(colors.Num() > 0 &&
			maxColumn != colors[0].Colors.Num()))
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!"),
				maxRow,
				colors.Num(),
				maxColumn,
				colors.Num() > 0 ? colors[0].Colors.Num() : 0);
			break;
		}
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				const FLinearColor& color = row.Colors[j];
				int red = color.R * 255;
				int green = color.G * 255;
				int blue = color.B * 255;
				pParam.Color[i][j] = RGB(red, green, blue);
			}
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		maxRow = ChromaSDK::Keypad::MAX_ROW;
		maxColumn = ChromaSDK::Keypad::MAX_COLUMN;
		if (maxRow != colors.Num() ||
			(colors.Num() > 0 &&
			maxColumn != colors[0].Colors.Num()))
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!"),
				maxRow,
				colors.Num(),
				maxColumn,
				colors.Num() > 0 ? colors[0].Colors.Num() : 0);
			break;
		}
		ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				const FLinearColor& color = row.Colors[j];
				int red = color.R * 255;
				int green = color.G * 255;
				int blue = color.B * 255;
				pParam.Color[i][j] = RGB(red, green, blue);
			}
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		maxRow = ChromaSDK::Mouse::MAX_ROW;
		maxColumn = ChromaSDK::Mouse::MAX_COLUMN;
		if (maxRow != colors.Num() ||
			(colors.Num() > 0 &&
			maxColumn != colors[0].Colors.Num()))
		{
			UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!"),
				maxRow,
				colors.Num(),
				maxColumn,
				colors.Num() > 0 ? colors[0].Colors.Num() : 0);
			break;
		}
		ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				const FLinearColor& color = row.Colors[j];
				int red = color.R * 255;
				int green = color.G * 255;
				int blue = color.B * 255;
				pParam.Color[i][j] = RGB(red, green, blue);
			}
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &pParam, &effectId);
	}
	break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectCustom2D Unsupported device used!"));
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

#endif

	return data;
}

FChromaSDKEffectResult UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectKeyboardCustom2D(const TArray<FChromaSDKColors>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

#if PLATFORM_WINDOWS

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = ChromaSDK::Keyboard::MAX_ROW;
	int maxColumn = ChromaSDK::Keyboard::MAX_COLUMN;

	if (maxRow != colors.Num() ||
		(colors.Num() > 0 &&
		maxColumn != colors[0].Colors.Num()))
	{
		UE_LOG(LogTemp, Error, TEXT("UChromaSDKPluginBPLibrary::ChromaSDKCreateEffectKeyboardCustom2D Array size mismatch row: %d==%d column: %d==%d!"),
			maxRow,
			colors.Num(),
			maxColumn,
			colors.Num() > 0 ? colors[0].Colors.Num() : 0);
	}
	else
	{
		ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				const FLinearColor& color = row.Colors[j];
				pParam.Key[i][j] = ToBGR(color);
			}
		}
		result = _sIChromaSDKPlugin.ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY, &pParam, &effectId);
	}
	
	data.EffectId.Data = effectId;
	data.Result = result;

#endif

	return data;
}

int UChromaSDKPluginBPLibrary::ChromaSDKSetEffect(const FChromaSDKGuid& effectId)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.ChromaSDKSetEffect(effectId.Data);
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::ChromaSDKDeleteEffect(const FChromaSDKGuid& effectId)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.ChromaSDKDeleteEffect(effectId.Data);
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetAnimation(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	return _sIChromaSDKPlugin.GetAnimation(pathArg);
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetAnimationId(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	return _sIChromaSDKPlugin.GetAnimation(pathArg);
#else
	return -1;
#endif
}

FString UChromaSDKPluginBPLibrary::GetAnimationName(const int animationId)
{
#if PLATFORM_WINDOWS
	FString result = _sIChromaSDKPlugin.GetAnimationName(animationId);
	return result;
#else
	return TEXT("");
#endif
}

void UChromaSDKPluginBPLibrary::LoadAnimation(const int animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.LoadAnimation(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::LoadAnimationName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.LoadAnimationName(pathArg);
#endif
}

void UChromaSDKPluginBPLibrary::CloseAnimation(const int animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.CloseAnimation(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::CloseAnimationName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.CloseAnimationName(pathArg);
#endif
}

void UChromaSDKPluginBPLibrary::UnloadAnimation(const int animationId)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.UnloadAnimation(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::UnloadAnimationName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.UnloadAnimationName(pathArg);
#endif
}

void UChromaSDKPluginBPLibrary::PlayAnimation(const FString& animationName, bool loop)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("PlayAnimation: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.PlayAnimationName(pathArg, loop);
#endif
}

void UChromaSDKPluginBPLibrary::PlayAnimationName(const FString& animationName, bool loop)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("PlayAnimationName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.PlayAnimationName(pathArg, loop);
#endif
}

void UChromaSDKPluginBPLibrary::StopAnimation(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.StopAnimationName(pathArg);
#endif
}

void UChromaSDKPluginBPLibrary::StopAnimationType(EChromaSDKDeviceEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_ChromaLink:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
		break;
	case EChromaSDKDeviceEnum::DE_Headset:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset);
		break;
	case EChromaSDKDeviceEnum::DE_Keyboard:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
		break;
	case EChromaSDKDeviceEnum::DE_Keypad:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad);
		break;
	case EChromaSDKDeviceEnum::DE_Mouse:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse);
		break;
	case EChromaSDKDeviceEnum::DE_Mousepad:
		_sIChromaSDKPlugin.StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad);
		break;
	}
#endif
}

void UChromaSDKPluginBPLibrary::StopAll()
{
#if PLATFORM_WINDOWS
	StopAnimationType(EChromaSDKDeviceEnum::DE_ChromaLink);
	StopAnimationType(EChromaSDKDeviceEnum::DE_Headset);
	StopAnimationType(EChromaSDKDeviceEnum::DE_Keyboard);
	StopAnimationType(EChromaSDKDeviceEnum::DE_Keypad);
	StopAnimationType(EChromaSDKDeviceEnum::DE_Mouse);
	StopAnimationType(EChromaSDKDeviceEnum::DE_Mousepad);
#endif
}

void UChromaSDKPluginBPLibrary::ClearAnimationType(EChromaSDKDeviceEnum::Type device)
{
#if PLATFORM_WINDOWS
	StopAnimationType(device);

	FChromaSDKEffectResult result = ChromaSDKCreateEffectNone(device);
	if (result.Result == 0)
	{
		ChromaSDKSetEffect(result.EffectId);
		ChromaSDKDeleteEffect(result.EffectId);
	}
#endif
}

void UChromaSDKPluginBPLibrary::ClearAll()
{
#if PLATFORM_WINDOWS
	ClearAnimationType(EChromaSDKDeviceEnum::DE_ChromaLink);
	ClearAnimationType(EChromaSDKDeviceEnum::DE_Headset);
	ClearAnimationType(EChromaSDKDeviceEnum::DE_Keyboard);
	ClearAnimationType(EChromaSDKDeviceEnum::DE_Keypad);
	ClearAnimationType(EChromaSDKDeviceEnum::DE_Mouse);
	ClearAnimationType(EChromaSDKDeviceEnum::DE_Mousepad);
#endif
}

int UChromaSDKPluginBPLibrary::GetAnimationCount()
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.GetAnimationCount();
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetAnimationIdByIndex(int index)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.GetAnimationId(index);
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetPlayingAnimationCount()
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.GetPlayingAnimationCount();
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetPlayingAnimationId(int index)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.GetPlayingAnimationId(index);
#else
	return -1;
#endif
}

bool UChromaSDKPluginBPLibrary::IsAnimationPlaying(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("IsAnimationPlaying: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	return _sIChromaSDKPlugin.IsAnimationPlayingName(pathArg);
#else
	return false;
#endif
}

bool UChromaSDKPluginBPLibrary::IsAnimationTypePlaying(EChromaSDKDeviceEnum::Type device)
{
#if PLATFORM_WINDOWS
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_ChromaLink:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
	case EChromaSDKDeviceEnum::DE_Headset:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset);
	case EChromaSDKDeviceEnum::DE_Keyboard:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	case EChromaSDKDeviceEnum::DE_Keypad:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad);
	case EChromaSDKDeviceEnum::DE_Mouse:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse);
	case EChromaSDKDeviceEnum::DE_Mousepad:
		return _sIChromaSDKPlugin.IsAnimationPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad);
	}
#endif
	return false;
}

void UChromaSDKPluginBPLibrary::PlayAnimations(const TArray<FString>& animationNames, bool loop)
{
	for (int i = 0; i < animationNames.Num(); ++i)
	{
		PlayAnimation(animationNames[i], loop);
	}
}

void UChromaSDKPluginBPLibrary::StopAnimations(const TArray<FString>& animationNames)
{
	for (int i = 0; i < animationNames.Num(); ++i)
	{
		StopAnimation(animationNames[i]);
	}
}

void UChromaSDKPluginBPLibrary::PlayAnimationComposite(const FString& animationName, bool loop)
{
	PlayAnimation(animationName + "_ChromaLink", loop);
	PlayAnimation(animationName + "_Headset", loop);
	PlayAnimation(animationName + "_Keyboard", loop);
	PlayAnimation(animationName + "_Keypad", loop);
	PlayAnimation(animationName + "_Mouse", loop);
	PlayAnimation(animationName + "_Mousepad", loop);
}

void UChromaSDKPluginBPLibrary::StopAnimationComposite(const FString& animationName)
{
	StopAnimation(animationName + "_ChromaLink");
	StopAnimation(animationName + "_Headset");
	StopAnimation(animationName + "_Keyboard");
	StopAnimation(animationName + "_Keypad");
	StopAnimation(animationName + "_Mouse");
	StopAnimation(animationName + "_Mousepad");
}

FLinearColor UChromaSDKPluginBPLibrary::GetKeyColor(int animationId, int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int color = _sIChromaSDKPlugin.GetKeyColor(animationId, frameIndex, rzkey);
		return IChromaSDKPlugin::ToLinearColor(color);
	}
#endif
	return IChromaSDKPlugin::ToLinearColor(0);
}

FLinearColor UChromaSDKPluginBPLibrary::GetKeyColorName(const FString& animationName, const int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int color = _sIChromaSDKPlugin.GetKeyColorName(pathArg, frameIndex, rzkey);
		return IChromaSDKPlugin::ToLinearColor(color);
	}
#endif
	return IChromaSDKPlugin::ToLinearColor(0);
}


void UChromaSDKPluginBPLibrary::SetKeyColor(int animationId, int frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, IChromaSDKPlugin::ToBGR(colorParam));
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeyColorName(const FString& animationName, const int frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, IChromaSDKPlugin::ToBGR(colorParam));
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeyNonZeroColor(int animationId, int frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.SetKeyNonZeroColor(animationId, frameIndex, rzkey, IChromaSDKPlugin::ToBGR(colorParam));
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeyNonZeroColorName(const FString& animationName, const int frameIndex, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.SetKeyNonZeroColorName(pathArg, frameIndex, rzkey, IChromaSDKPlugin::ToBGR(colorParam));
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysColor(int animationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, colorArg);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysColorName(const FString& animationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, colorArg);
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysColorRGB(int animationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	int colorArg = IChromaSDKPlugin::GetRGB(red, green, blue);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, colorArg);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysColorRGBName(const FString& animationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int colorArg = IChromaSDKPlugin::GetRGB(red, green, blue);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, colorArg);
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysNonZeroColor(int animationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyNonZeroColor(animationId, frameIndex, rzkey, colorArg);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysNonZeroColorName(const FString& animationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.SetKeyNonZeroColorName(pathArg, frameIndex, rzkey, colorArg);
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeyColorAllFrames(int animationId, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
		int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
		for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
		{
			_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, colorArg);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeyColorAllFramesName(const FString& animationName, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
		int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
		for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
		{
			_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, colorArg);
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeyNonZeroColorAllFrames(int animationId, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
		int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
		for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
		{
			_sIChromaSDKPlugin.SetKeyNonZeroColor(animationId, frameIndex, rzkey, colorArg);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeyNonZeroColorAllFramesName(const FString& animationName, EChromaSDKKeyboardKey::Type key, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
		int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
		for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
		{
			_sIChromaSDKPlugin.SetKeyNonZeroColorName(pathArg, frameIndex, rzkey, colorArg);
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysColorAllFrames(int animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysColorAllFramesName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysColorAllFramesRGB(int animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
	int colorArg = IChromaSDKPlugin::GetRGB(red, green, blue);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyColor(animationId, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysColorAllFramesRGBName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
	int colorArg = IChromaSDKPlugin::GetRGB(red, green, blue);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyColorName(pathArg, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::SetKeysNonZeroColorAllFrames(int animationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyNonZeroColor(animationId, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::SetKeysNonZeroColorAllFramesName(const FString& animationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
	int colorArg = IChromaSDKPlugin::ToBGR(colorParam);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.SetKeyNonZeroColorName(pathArg, frameIndex, rzkey, colorArg);
			}
		}
	}
#endif
}


void UChromaSDKPluginBPLibrary::CopyKeyColor(int sourceAnimationId, int targetAnimationId, int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.CopyKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.CopyKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyKeysColor(int sourceAnimationId, int targetAnimationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.CopyKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.CopyKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyKeysColorAllFrames(int sourceAnimationId, int targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(targetAnimationId);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.CopyKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
			}
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.CopyKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
			}
		}
	}
#endif
}

// COPY ALL KEYS

void UChromaSDKPluginBPLibrary::CopyAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.CopyAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
#endif
}

void UChromaSDKPluginBPLibrary::CopyAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	_sIChromaSDKPlugin.CopyAllKeysName(sourcePathArg, targetPathArg, frameIndex);
#endif
}

// NONZERO

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.CopyNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	_sIChromaSDKPlugin.CopyNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
#endif
}

// NONZERO ADD

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.AddNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
#endif
}

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	_sIChromaSDKPlugin.AddNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
#endif
}

// NONZERO Subtract

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeys(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.SubtractNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
#endif
}

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeysName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameIndex)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	_sIChromaSDKPlugin.SubtractNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
#endif
}

// NONZERO OFFSET

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 frameIndex, int32 offset)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.CopyNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameIndex, offset);
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 frameIndex, int32 offset)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	_sIChromaSDKPlugin.CopyNonZeroAllKeysOffsetName(sourcePathArg, targetPathArg, frameIndex, offset);
#endif
}

// COPY ALL KEYS ALL FRAMES

void UChromaSDKPluginBPLibrary::CopyAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyAllKeysName(sourcePathArg, targetPathArg, frameIndex);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.CopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeyColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, EChromaSDKKeyboardKey::Type key)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int rzkey = _sKeyboardEnumMap[key];
	if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
	{
		_sIChromaSDKPlugin.CopyNonZeroKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeysColor(int sourceAnimationId, int targetAnimationId, int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.CopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeysColorName(const FString& sourceAnimationName, const FString& targetAnimationName, const int frameIndex, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			_sIChromaSDKPlugin.CopyNonZeroKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeysColorAllFrames(int sourceAnimationId, int targetAnimationId, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(targetAnimationId);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.CopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameIndex, rzkey);
			}
		}
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroKeysColorAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName, const TArray<TEnumAsByte<EChromaSDKKeyboardKey::Type>>& keys)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int k = 0; k < keys.Num(); ++k)
	{
		EChromaSDKKeyboardKey::Type key = keys[k];
		int rzkey = _sKeyboardEnumMap[key];
		if (rzkey != ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID)
		{
			for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
			{
				_sIChromaSDKPlugin.CopyNonZeroKeyColorName(sourcePathArg, targetPathArg, frameIndex, rzkey);
			}
		}
	}
#endif
}

// NONZERO

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
	}
#endif
}

// NONZERO ADD

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.AddNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
	}
#endif
}

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.AddNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
	}
#endif
}

// NONZERO SUBTRACT

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeysAllFrames(int32 sourceAnimationId, int32 targetAnimationId)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.SubtractNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameIndex);
	}
#endif
}

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeysAllFramesName(const FString& sourceAnimationName, const FString& targetAnimationName)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.SubtractNonZeroAllKeysName(sourcePathArg, targetPathArg, frameIndex);
	}
#endif
}

// NONZERO OFFSET

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameIndex, offset);
	}
#endif
}

void UChromaSDKPluginBPLibrary::CopyNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.CopyNonZeroAllKeysOffsetName(sourcePathArg, targetPathArg, frameIndex, offset);
	}
#endif
}

// NONZERO OFFSET ADD

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.AddNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameIndex, offset);
	}
#endif
}

void UChromaSDKPluginBPLibrary::AddNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.AddNonZeroAllKeysOffsetName(sourcePathArg, targetPathArg, frameIndex, offset);
	}
#endif
}

// NONZERO OFFSET SUBTRACT

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeysAllFramesOffset(int32 sourceAnimationId, int32 targetAnimationId, int32 offset)
{
#if PLATFORM_WINDOWS
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCount(sourceAnimationId);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.SubtractNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameIndex, offset);
	}
#endif
}

void UChromaSDKPluginBPLibrary::SubtractNonZeroAllKeysAllFramesOffsetName(const FString& sourceAnimationName, const FString& targetAnimationName, int32 offset)
{
#if PLATFORM_WINDOWS
	FString sourcePath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString sourcePath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (sourceAnimationName.EndsWith(".chroma"))
	{
		sourcePath += sourceAnimationName;
	}
	else
	{
		sourcePath += sourceAnimationName + ".chroma";
	}
	const char* sourcePathArg = TCHAR_TO_ANSI(*sourcePath);
	FString targetPath = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString targetPath = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (targetAnimationName.EndsWith(".chroma"))
	{
		targetPath += targetAnimationName;
	}
	else
	{
		targetPath += targetAnimationName + ".chroma";
	}
	const char* targetPathArg = TCHAR_TO_ANSI(*targetPath);
	int frameCount = _sIChromaSDKPlugin.GetAnimationFrameCountName(targetPathArg);
	for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
	{
		_sIChromaSDKPlugin.SubtractNonZeroAllKeysOffsetName(sourcePathArg, targetPathArg, frameIndex, offset);
	}
#endif
}

// FILL COLOR

void UChromaSDKPluginBPLibrary::FillColor(int animationId, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillColor(animationId, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillColorName(const FString& animationName, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillColorName(pathArg, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillColorRGB(int animationId, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillColorRGB(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillColorRGBName(const FString& animationName, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillColorRGBName(pathArg, frameId, red, green, blue);
#endif
}

// NONZERO COLOR

void UChromaSDKPluginBPLibrary::FillNonZeroColor(int animationId, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillNonZeroColor(animationId, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorName(const FString& animationName, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillNonZeroColorName(pathArg, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillNonZeroColorRGB(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorRGBName(const FString& animationName, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillNonZeroColorRGBName(pathArg, frameId, red, green, blue);
#endif
}

// ZERO COLOR

void UChromaSDKPluginBPLibrary::FillZeroColor(int animationId, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillZeroColor(animationId, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorName(const FString& animationName, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillZeroColorName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillZeroColorName(pathArg, frameId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillZeroColorRGB(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorRGBName(const FString& animationName, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillZeroColorName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillZeroColorRGBName(pathArg, frameId, red, green, blue);
#endif
}


// FILL THRESHOLD COLORS ALL FRAMES

void UChromaSDKPluginBPLibrary::FillThresholdColorsAllFrames(int animationId, int threshold, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillThresholdColorsAllFrames(animationId, threshold, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillThresholdColorsAllFramesName(const FString& animationName, int threshold, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillThresholdColorsAllFramesName(pathArg, threshold, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillThresholdColorsAllFramesRGB(int animationId, int threshold, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillThresholdColorsAllFramesRGB(animationId, threshold, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillThresholdColorsAllFramesRGBName(const FString& animationName, int threshold, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillThresholdColorsAllFramesRGBName(pathArg, threshold, red, green, blue);
#endif
}


// FILL COLOR ALL FRAMES

void UChromaSDKPluginBPLibrary::FillColorAllFrames(int animationId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillColorAllFrames(animationId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillColorAllFramesName(const FString& animationName, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillColorAllFramesName(pathArg, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillColorAllFramesRGB(int animationId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillColorAllFramesRGB(animationId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillColorAllFramesRGBName(const FString& animationName, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillColorAllFramesRGBName(pathArg, red, green, blue);
#endif
}

// NONZERO COLOR

void UChromaSDKPluginBPLibrary::FillNonZeroColorAllFrames(int animationId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillNonZeroColorAllFrames(animationId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorAllFramesName(const FString& animationName, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillNonZeroColorAllFramesName(pathArg, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillNonZeroColorAllFramesRGB(animationId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillNonZeroColorAllFramesRGBName(const FString& animationName, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillNonZeroColorAllFramesRGBName(pathArg, red, green, blue);
#endif
}

// ZERO COLOR

void UChromaSDKPluginBPLibrary::FillZeroColorAllFrames(int animationId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillZeroColorAllFrames(animationId, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorAllFramesName(const FString& animationName, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillZeroColorAllFramesName(pathArg, IChromaSDKPlugin::ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillZeroColorAllFramesRGB(animationId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::FillZeroColorAllFramesRGBName(const FString& animationName, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillNonZeroColorAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillZeroColorAllFramesRGBName(pathArg, red, green, blue);
#endif
}


// FILL RANDOM COLORS

void UChromaSDKPluginBPLibrary::FillRandomColors(int32 animationId, int32 frameId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillRandomColors(animationId, frameId);
#endif
}

void UChromaSDKPluginBPLibrary::FillRandomColorsName(const FString& animationName, int32 frameId)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillRandomColorsName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillRandomColorsName(pathArg, frameId);
#endif
}


void UChromaSDKPluginBPLibrary::FillRandomColorsAllFrames(int32 animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillRandomColorsAllFrames(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::FillRandomColorsAllFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillRandomColorsAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillRandomColorsAllFramesName(pathArg);
#endif
}


// FILL RANDOM BLACK AND WHITE


void UChromaSDKPluginBPLibrary::FillRandomColorsBlackAndWhite(int32 animationId, int32 frameId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillRandomColorsBlackAndWhite(animationId, frameId);
#endif
}

void UChromaSDKPluginBPLibrary::FillRandomColorsBlackAndWhiteName(const FString& animationName, int32 frameId)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillRandomColorsBlackAndWhiteName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillRandomColorsBlackAndWhiteName(pathArg, frameId);
#endif
}


void UChromaSDKPluginBPLibrary::FillRandomColorsBlackAndWhiteAllFrames(int32 animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FillRandomColorsBlackAndWhiteAllFrames(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::FillRandomColorsBlackAndWhiteAllFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("FillRandomColorsBlackAndWhiteAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FillRandomColorsBlackAndWhiteAllFramesName(pathArg);
#endif
}


// OFFSET COLORS

void UChromaSDKPluginBPLibrary::OffsetColors(int animationId, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.OffsetColors(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::OffsetColorsName(const FString& animationName, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("OffsetColorsName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.OffsetColorsName(pathArg, frameId, red, green, blue);
#endif
}


void UChromaSDKPluginBPLibrary::OffsetColorsAllFrames(int animationId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.OffsetColorsAllFrames(animationId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::OffsetColorsAllFramesName(const FString& animationName, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("OffsetColorsAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.OffsetColorsAllFramesName(pathArg, red, green, blue);
#endif
}


void UChromaSDKPluginBPLibrary::OffsetNonZeroColors(int animationId, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.OffsetNonZeroColors(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::OffsetNonZeroColorsName(const FString& animationName, int frameId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("OffsetNonZeroColorsName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.OffsetNonZeroColorsName(pathArg, frameId, red, green, blue);
#endif
}


void UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFrames(int animationId, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.OffsetNonZeroColorsAllFrames(animationId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::OffsetNonZeroColorsAllFramesName(const FString& animationName, int red, int green, int blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("OffsetNonZeroColorsAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.OffsetNonZeroColorsAllFramesName(pathArg, red, green, blue);
#endif
}


// MULTIPLY INTENSITY

void UChromaSDKPluginBPLibrary::MultiplyIntensity(int animationId, int frameId, float intensity)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MultiplyIntensity(animationId, frameId, intensity);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityName(const FString& animationName, int frameId, float intensity)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MultiplyIntensityName(pathArg, frameId, intensity);
#endif
}

// MULTIPLY INTENSITY RGB

void UChromaSDKPluginBPLibrary::MultiplyIntensityRGB(int32 animationId, int32 frameId, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MultiplyIntensityRGB(animationId, frameId, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityRGBName(const FString& animationName, int32 frameId, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MultiplyIntensityRGBName(pathArg, frameId, red, green, blue);
#endif
}


// MULTIPLY INTENSITY COLOR

void UChromaSDKPluginBPLibrary::MultiplyIntensityColor(int animationId, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int color = ToBGR(colorParam);
	_sIChromaSDKPlugin.MultiplyIntensityColor(animationId, frameId, color);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityColorName(const FString& animationName, int frameId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int color = ToBGR(colorParam);
	_sIChromaSDKPlugin.MultiplyIntensityColorName(pathArg, frameId, color);
#endif
}


// MULTIPLY INTENSITY ALL FRAMES

void UChromaSDKPluginBPLibrary::MultiplyIntensityAllFrames(int animationId, float intensity)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MultiplyIntensityAllFrames(animationId, intensity);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesName(const FString& animationName, float intensity)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MultiplyIntensityAllFramesName(pathArg, intensity);
#endif
}


// MULTIPLY INTENSITY COLOR ALL FRAMES

void UChromaSDKPluginBPLibrary::MultiplyIntensityColorAllFrames(int animationId, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	int color = ToBGR(colorParam);
	_sIChromaSDKPlugin.MultiplyIntensityColorAllFrames(animationId, color);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityColorAllFramesName(const FString& animationName, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityAllFramesName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	int color = ToBGR(colorParam);
	_sIChromaSDKPlugin.MultiplyIntensityColorAllFramesName(pathArg, color);
#endif
}

// RGB

void UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesRGB(int animationId, float redIntensity, float greenIntensity, float blueIntensity)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MultiplyIntensityAllFramesRGB(animationId, redIntensity, greenIntensity, blueIntensity);
#endif
}

void UChromaSDKPluginBPLibrary::MultiplyIntensityAllFramesRGBName(const FString& animationName, float redIntensity, float greenIntensity, float blueIntensity)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	//UE_LOG(LogTemp, Log, TEXT("MultiplyIntensityAllFramesRGBName: %s"), *path);
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MultiplyIntensityAllFramesRGBName(pathArg, redIntensity, greenIntensity, blueIntensity);
#endif
}


int UChromaSDKPluginBPLibrary::GetFrameCount(const int animationId)
{
#if PLATFORM_WINDOWS
	return _sIChromaSDKPlugin.GetAnimationFrameCount(animationId);
#else
	return -1;
#endif
}

int UChromaSDKPluginBPLibrary::GetFrameCountName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	return _sIChromaSDKPlugin.GetAnimationFrameCountName(pathArg);
#else
	return 0;
#endif
}

void UChromaSDKPluginBPLibrary::SetChromaCustomFlagName(const FString& animationName, bool flag)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.SetChromaCustomFlagName(pathArg, flag);
#endif
}

void UChromaSDKPluginBPLibrary::SetChromaCustomColorAllFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.SetChromaCustomColorAllFramesName(pathArg);
#endif
}

void UChromaSDKPluginBPLibrary::OverrideFrameDurationName(const FString& animationName, float duration)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.OverrideFrameDurationName(pathArg, duration);
#endif
}

// MAKE FRAMES

void UChromaSDKPluginBPLibrary::MakeBlankFrames(int32 animationId, int32 frameCount, float duration, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MakeBlankFrames(animationId, frameCount, duration, ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::MakeBlankFramesName(const FString& animationName, int32 frameCount, float duration, const FLinearColor& colorParam)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MakeBlankFramesName(pathArg, frameCount, duration, ToBGR(colorParam));
#endif
}

void UChromaSDKPluginBPLibrary::MakeBlankFramesRGB(int32 animationId, int32 frameCount, float duration, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MakeBlankFramesRGB(animationId, frameCount, duration, red, green, blue);
#endif
}

void UChromaSDKPluginBPLibrary::MakeBlankFramesRGBName(const FString& animationName, int32 frameCount, float duration, int32 red, int32 green, int32 blue)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MakeBlankFramesRGBName(pathArg, frameCount, duration, red, green, blue);
#endif
}

// RANDOM

void UChromaSDKPluginBPLibrary::MakeBlankFramesRandom(int32 animationId, int32 frameCount, float duration)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MakeBlankFramesRandom(animationId, frameCount, duration);
#endif
}

void UChromaSDKPluginBPLibrary::MakeBlankFramesRandomName(const FString& animationName, int32 frameCount, float duration)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MakeBlankFramesRandomName(pathArg, frameCount, duration);
#endif
}

// RANDOM BLACK AND WHITE

void UChromaSDKPluginBPLibrary::MakeBlankFramesRandomBlackAndWhite(int32 animationId, int32 frameCount, float duration)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.MakeBlankFramesRandomBlackAndWhite(animationId, frameCount, duration);
#endif
}

void UChromaSDKPluginBPLibrary::MakeBlankFramesRandomBlackAndWhiteName(const FString& animationName, int32 frameCount, float duration)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.MakeBlankFramesRandomBlackAndWhiteName(pathArg, frameCount, duration);
#endif
}


// REVERSE ALL FRAMES

void UChromaSDKPluginBPLibrary::ReverseAllFrames(int32 animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.ReverseAllFrames(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::ReverseAllFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.ReverseAllFramesName(pathArg);
#endif
}


// DUPLICATE FRAMES

void UChromaSDKPluginBPLibrary::DuplicateFrames(int32 animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.DuplicateFrames(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::DuplicateFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.DuplicateFramesName(pathArg);
#endif
}


// DUPLICATE FIRST FRAME

void UChromaSDKPluginBPLibrary::DuplicateFirstFrame(int32 animationId, int32 frameCount)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.DuplicateFirstFrame(animationId, frameCount);
#endif
}

void UChromaSDKPluginBPLibrary::DuplicateFirstFrameName(const FString& animationName, int32 frameCount)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.DuplicateFirstFrameName(pathArg, frameCount);
#endif
}


// DUPLICATE MIRROR FRAMES

void UChromaSDKPluginBPLibrary::DuplicateMirrorFrames(int32 animationId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.DuplicateMirrorFrames(animationId);
#endif
}

void UChromaSDKPluginBPLibrary::DuplicateMirrorFramesName(const FString& animationName)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.DuplicateMirrorFramesName(pathArg);
#endif
}


// INSERT FRAME

void UChromaSDKPluginBPLibrary::InsertFrame(int32 animationId, int32 sourceFrame, int32 targetFrame)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.InsertFrame(animationId, sourceFrame, targetFrame);
#endif
}

void UChromaSDKPluginBPLibrary::InsertFrameName(const FString& animationName, int32 sourceFrame, int32 targetFrame)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.InsertFrameName(pathArg, sourceFrame, targetFrame);
#endif
}


// INSERT DELAY

void UChromaSDKPluginBPLibrary::InsertDelay(int32 animationId, int32 frameId, int32 delay)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.InsertDelay(animationId, frameId, delay);
#endif
}

void UChromaSDKPluginBPLibrary::InsertDelayName(const FString& animationName, int32 frameId, int32 delay)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.InsertDelayName(pathArg, frameId, delay);
#endif
}


// REDUCE FRAMES

void UChromaSDKPluginBPLibrary::ReduceFrames(int32 animationId, int32 n)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.ReduceFrames(animationId, n);
#endif
}

void UChromaSDKPluginBPLibrary::ReduceFramesName(const FString& animationName, int32 n)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.ReduceFramesName(pathArg, n);
#endif
}


// TRIM FRAME

void UChromaSDKPluginBPLibrary::TrimFrame(int32 animationId, int32 frameId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.TrimFrame(animationId, frameId);
#endif
}

void UChromaSDKPluginBPLibrary::TrimFrameName(const FString& animationName, int32 frameId)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.TrimFrameName(pathArg, frameId);
#endif
}


// TRIM START FRAMES

void UChromaSDKPluginBPLibrary::TrimStartFrames(int32 animationId, int32 numberOfFrames)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.TrimStartFrames(animationId, numberOfFrames);
#endif
}

void UChromaSDKPluginBPLibrary::TrimStartFramesName(const FString& animationName, int32 numberOfFrames)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.TrimStartFramesName(pathArg, numberOfFrames);
#endif
}


// TRIM END FRAMES

void UChromaSDKPluginBPLibrary::TrimEndFrames(int32 animationId, int32 lastFrameId)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.TrimEndFrames(animationId, lastFrameId);
#endif
}

void UChromaSDKPluginBPLibrary::TrimEndFramesName(const FString& animationName, int32 lastFrameId)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.TrimEndFramesName(pathArg, lastFrameId);
#endif
}


// FADE START FRAMES

void UChromaSDKPluginBPLibrary::FadeStartFrames(int32 animationId, int32 fade)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FadeStartFrames(animationId, fade);
#endif
}

void UChromaSDKPluginBPLibrary::FadeStartFramesName(const FString& animationName, int32 fade)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FadeStartFramesName(pathArg, fade);
#endif
}


// FADE END FRAMES

void UChromaSDKPluginBPLibrary::FadeEndFrames(int32 animationId, int32 fade)
{
#if PLATFORM_WINDOWS
	_sIChromaSDKPlugin.FadeEndFrames(animationId, fade);
#endif
}

void UChromaSDKPluginBPLibrary::FadeEndFramesName(const FString& animationName, int32 fade)
{
#if PLATFORM_WINDOWS
	FString path = FPaths::GameContentDir(); //___HACK_UE4_VERSION_4_17_OR_LESS
//	FString path = FPaths::ProjectContentDir(); //___HACK_UE4_VERSION_4_18_OR_GREATER
	if (animationName.EndsWith(".chroma"))
	{
		path += animationName;
	}
	else
	{
		path += animationName + ".chroma";
	}
	const char* pathArg = TCHAR_TO_ANSI(*path);
	_sIChromaSDKPlugin.FadeEndFramesName(pathArg, fade);
#endif
}

#if PLATFORM_WINDOWS

#include "HideWindowsPlatformTypes.h"

#endif