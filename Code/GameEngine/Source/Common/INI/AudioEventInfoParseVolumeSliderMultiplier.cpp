// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z
// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/iniexception -Ireference/open-bfme-1/game/GameEngine/Source/Common /I. /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z, retail 0x001D9E91, 209 bytes (complete epilogue; prior queue extent 208 truncated final RET byte).
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/Common/INI/AudioEventInfoParseVolumeSliderMultiplier.cpp
// proves class AudioEventInfo and verb parseVolumeSliderMultiplier plus Slider/Multiplier token flow,
// 8-byte {int slider, float multiplier} entry with -1/1.0 defaults and vector push_back.
// BFME2 deltas retail-measured: INI sepsColon at +0x420, member scanIndexList/dup_002EE10 via ecx,
// _strcmpi through IAT, name list 0x00DB8AEC (theSubmixSliderNames, the
// SubmixSlider list AudioEventInfoParseDefinition.cpp defines; it was spelled theArmorBlockParse+0x78). REF slot 0x007D9EFC neighbours
// VolumeSliderMultiplier; strings Slider/Multiplier plus both INIException formats.
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

#include "../../../Include/Common/INI/INI.h"

extern const char *theSubmixSliderNames[];

struct BfmeE8
{
	int m_slider;
	float m_multiplier;
};

#include <vector>

namespace _STL
{
// Bind the append to the rowed 8-byte-element worker.
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &value);
}

#include "../../../Include/Common/INI/FieldParse.h"

// The seed TU builds with _CRTIMP= empty; retail calls _strcmpi through the IAT.
namespace VolumeSliderCRT {
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);
}

class AudioEventInfo
{
public:
	static void parseVolumeSliderMultiplier(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z
void AudioEventInfo::parseVolumeSliderMultiplier(INI *ini, void *, void *store, const void *)
{
	{
	BfmeE8 entry;
	entry.m_slider = -1;
	entry.m_multiplier = 1.0f;
	const char *token = ini->getNextTokenOrNull(ini->m_sepsColon);
	if (token == 0)
		goto slider_error;
	if (VolumeSliderCRT::_strcmpi(token, "Slider") == 0) {
		const char *slider = ini->getNextToken(ini->m_sepsColon);
		entry.m_slider = ini->scanIndexList(slider, theSubmixSliderNames);
		token = ini->getNextTokenOrNull(ini->m_sepsColon);
		if (token != 0 && VolumeSliderCRT::_strcmpi(token, "Multiplier") == 0) {
			entry.m_multiplier = ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
			((_STL::vector<BfmeE8> *)store)->push_back(entry);
			return;
		}
		goto multiplier_error;
	}
	goto slider_error;
	}

slider_error:
	{
		throw INIException(3, "Slider:slidername expected after VolumeSliderMultiplier");
	}

multiplier_error:
	{
		throw INIException(3, "Multiplier:number expected after VolumeSliderMultiplier = Slider:slidername");
	}
}
