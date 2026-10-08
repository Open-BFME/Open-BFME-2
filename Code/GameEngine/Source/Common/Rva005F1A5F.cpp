// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Oy-
// StrategicHUD::GetBonusTypeFromParam @0x005F1A5F 150B (WorldBuilder name,
// StrategicHUDRegionDetailsTerritoryMovieClip.cpp lines 260..272): free cdecl bool const-char plus int-out with index GetParam plus empty plus isdigit plus atoi 0-5.
// Evidence: unlock lane; string index plus atoi plus releaseBuffer; pin Rva004128F0GetParam plus IAT isdigit atoi; extern g_Rva0107301CEmptyString; callers 0x005F1B02 0x005F1B25.
#include "ascii_string.h"

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

__forceinline const char *GetStr005F1A5F(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

namespace StrategicHUD
{
	bool GetBonusTypeFromParam(const char *params, int *out);
}

bool StrategicHUD::GetBonusTypeFromParam(const char *params, int *out)
{
	if (params == 0)
		return false;
	AsciiString tmp;
	if (!Rva004128F0GetParam(params, "index", tmp))
		return false;
	char *t = *(char * *)(void *)&tmp;
	if (t == 0 || *(unsigned short *)(t + 4) == 0)
		return false;
	if (!isdigit(t[8]))
		return false;
	int v = atoi(GetStr005F1A5F(tmp));
	if (v < 0 || v >= 6)
		return false;
	*out = v;
	return true;
}

// ?rva005F1AF5@Rva005F1AF5@@QAEXPBD@Z @0x005F1AF5 35B: thiscall setter parsing index via 0x005F1A5F into +0x44 reusing arg slot.
// Evidence: chain from 0x005F1A5F; rowed callee; no Ghidra entry beyond size.
class Rva005F1AF5
{
public:
	void rva005F1AF5(const char *p);
	void rva005F1B18(const char *p);
private:
	char m_pad[0x44];
	int m_44;
};

void Rva005F1AF5::rva005F1AF5(const char *p)
{
	if (StrategicHUD::GetBonusTypeFromParam(p, (int *)&p))
		m_44 = (int)p;
}

// ?rva005F1B18@Rva005F1AF5@@QAEXPBD@Z @0x005F1B18 41B: thiscall clearing +0x44 to -1 when parsed index equals stored value via 0x005F1A5F.
// Evidence: chain from 0x005F1A5F; same +0x44 layout as 0x005F1AF5; rowed callee; no Ghidra entry beyond size.
void Rva005F1AF5::rva005F1B18(const char *p)
{
	if (StrategicHUD::GetBonusTypeFromParam(p, (int *)&p)) {
		if ((int)p == m_44)
			m_44 = -1;
	}
}
