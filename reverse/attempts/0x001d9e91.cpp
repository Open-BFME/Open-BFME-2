// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.98 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /EHs-c- /Oi-
// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z, retail 0x001D9E91, 208 bytes.
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/Common/INI/AudioEventInfoParseVolumeSliderMultiplier.cpp
// proves class AudioEventInfo and verb parseVolumeSliderMultiplier plus Slider/Multiplier token flow,
// 8-byte {int slider, float multiplier} entry with -1/1.0 defaults and vector push_back.
// BFME2 deltas retail-measured: INI sepsColon at +0x420, member scanIndexList/dup_002EE10 via ecx,
// _strcmpi through IAT, name list theArmorBlockParse+0x78. REF slot 0x007D9EFC neighbours
// VolumeSliderMultiplier; strings Slider/Multiplier plus both INIException formats.
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	float dup_002EE10(const char *token);

	char _pad[0x420];
	const char *m_sepsColon;
};

struct BlockParse
{
	char m_pad[0x78];
	const char *m_names[1];
};
extern BlockParse theArmorBlockParse;

struct BfmeE8
{
	int m_slider;
	float m_multiplier;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

class AudioEventInfo
{
public:
	static void parseVolumeSliderMultiplier(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseVolumeSliderMultiplier@AudioEventInfo@@SAXPAVINI@@PAX1PBX@Z
void AudioEventInfo::parseVolumeSliderMultiplier(INI *ini, void *, void *store, const void *)
{
	BfmeE8 entry;
	entry.m_slider = -1;
	entry.m_multiplier = 1.0f;
	const char *token = ini->getNextTokenOrNull(ini->m_sepsColon);
	if (token == 0)
		goto slider_error;
	if (_strcmpi(token, "Slider") == 0) {
		const char *slider = ini->getNextToken(ini->m_sepsColon);
		entry.m_slider = ini->scanIndexList(slider, theArmorBlockParse.m_names);
		token = ini->getNextTokenOrNull(ini->m_sepsColon);
		if (token != 0 && _strcmpi(token, "Multiplier") == 0) {
			entry.m_multiplier = ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
			((_STL::vector<BfmeE8> *)store)->push_back(entry);
			return;
		}
		goto multiplier_error;
	}
	goto slider_error;

slider_error:
	{
		throw INIException(3, "Slider:slidername expected after VolumeSliderMultiplier");
	}

multiplier_error:
	{
		throw INIException(3, "Multiplier:number expected after VolumeSliderMultiplier = Slider:slidername");
	}
}
