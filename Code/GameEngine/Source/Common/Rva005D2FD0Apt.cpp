// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// StrategicHUD::SetString retail 0x005D2FD0 106B
// Evidence: format APT:_level%u.%s_%s via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C 0x008758A8; callers 0x005D3128 0x005D318D 0x005D31F2
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// StrategicHUD::SetString (0x005D2FD0) and StrategicHUD::SetRegionNameString
// (0x005D366A): WorldBuilder names both (StrategicHUDRegionStatsTrayMovieClip.cpp
// line 35, StrategicHUDRegionUIMovieClip.cpp line 27) with the same
// "APT:_level%u.%s_..." keys and SetText call. The movie clip name is an
// AsciiString passed by reference.
namespace StrategicHUD
{
	void SetString(unsigned int level, const AsciiString &clipName, const char *suffix, const UnicodeString &text);
	void SetRegionNameString(unsigned int level, const AsciiString &clipName, const UnicodeString &text);
}

void StrategicHUD::SetString(unsigned int level, const AsciiString &clipName, const char *suffix, const UnicodeString &text)
{
	AsciiString key;
	key.format("APT:_level%u.%s_%s", level, clipName.str(), suffix);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

void StrategicHUD::SetRegionNameString(unsigned int level, const AsciiString &clipName, const UnicodeString &text)
{
	AsciiString key;
	key.format("APT:_level%u.%s_RegionName", level, clipName.str());
	g_bfmeAptWindowManager->bfmeSetText(key, text, false);
}

// ?rva005D3846@Rva005D3846@@QAEXABVUnicodeString@@@Z retail 0x005D3846 53B
// Evidence: chain from 0x005D366A; compare 0x00006A7A; set pin 0x00037150; caller jmp 0x00578611
class Rva005D3846
{
public:
	void rva005D3846(const UnicodeString &text);
private:
	unsigned int m_level;
	AsciiString m_clipName;
	char m_pad[0x18 - 8];
	UnicodeString m_cached;
};

void Rva005D3846::rva005D3846(const UnicodeString &text)
{
	if (((const StringBase<unsigned short> *)(const void *)&text)->compare(*(const StringBase<unsigned short> *)(const void *)&m_cached) != 0) {
		StrategicHUD::SetRegionNameString(m_level, m_clipName, text);
		((StringBase<unsigned short> *)(void *)&m_cached)->set(*(const StringBase<unsigned short> *)(const void *)&text);
	}
}

// ??1Rva005D3731@@QAE@XZ @0x005D3731 69B
// Evidence: chain via rowed 0x005242D7 and releaseBuffers 0x00036E70 0x00036410;
// members +0x04 ansi +0x08 vector-wrapper +0x18 wide; callers 0x0057856D 0x005786F3 0x00578714
class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva005D3731
{
public:
	~Rva005D3731();
private:
	int m_00;
	AsciiString m_04;
	Rva005242D7 m_08;
	int m_14;
	UnicodeString m_18;
};

Rva005D3731::~Rva005D3731()
{
}

// ?rva005D37F1@Rva005D37F1@@QAEX_N@Z retail 0x005D37F1 85B
// Evidence: guard bool at +0x1c; _show else _hide reusing arg slot; prefix from +4 else g_Rva0107301CEmptyString; level at +0; SetState via rowed 0x0050E9FE; global TheRva00222A8BTarget; chain from 0x005D321D
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
class Rva005D37F1
{
public:
	void rva005D37F1(bool flag);
private:
	void *m_level00;
	Rva005D2FD0Inner *m_inner04;
	char m_pad08[0x1c - 0x08];
	bool m_flag1c;
};
void Rva005D37F1::rva005D37F1(bool flag)
{
	if (flag == m_flag1c)
		return;
	const char *state = flag ? "_show" : "_hide";
	const char *prefix = m_inner04 ? m_inner04->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level00, prefix, "SetState", &state);
	m_flag1c = flag;
}
