// cl: /Ireference/shims/bfme2_ascii /MD
// StrategicHUD::RegionDetailsArmiesMovieClip::Impl::ShowArmyName, retail
// 0x005EF557, 107 bytes (WorldBuilder name: same compare/SetArmyNameString/set
// sequence and SetArmyNameState _show, StrategicHUDRegionDetailsArmiesMovieClip.cpp:385).
// Evidence: rowed compare 0x00006A7A and wide set 0x00037150; StrategicHUD::SetArmyNameString 0x005EF02F;
// rowed AptCall 0x005FB5E6 with SetArmyNameState _show; globals TheRva00222A8BTarget
// 0x009FE4CC and g_Rva0107301CEmptyString; caller forwarder 0x005EF5C2;
// precedent Rva005F7670::rva005F7670 cached compare plus once flag.
#include "unicode_string.h"

class Rva00222A8BTarget
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005EF557Team
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005EF02FOuter
{
	Rva005EF557Team *m_team;
};

namespace StrategicHUD
{
	void SetArmyNameString(int level, struct Rva005EF02FOuter *outer, const class UnicodeString &text);
}
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

namespace StrategicHUD
{
class RegionDetailsArmiesMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsArmiesMovieClip::Impl
{
public:
	void ShowArmyName(const UnicodeString &text);
private:
	int m_00;
	Rva005EF02FOuter m_outer04;
	char m_pad08[0x30 - 0x08];
	UnicodeString m_cached30;
	char m_pad34[8];
	bool m_shown3C;
};

void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::ShowArmyName(const UnicodeString &text)
{
	if (text.compare(m_cached30) != 0) {
		StrategicHUD::SetArmyNameString(m_00, &m_outer04, text);
		m_cached30.set(text);
	}
	if (!m_shown3C) {
		const char *team = m_outer04.m_team ? m_outer04.m_team->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_00, team, "SetArmyNameState", "_show");
		m_shown3C = true;
	}
}

class Rva005EF5C2
{
public:
	void rva005EF5C2(const UnicodeString &text);
private:
	char m_pad00[4];
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_inner04;
};

void Rva005EF5C2::rva005EF5C2(const UnicodeString &text)
{
	m_inner04->ShowArmyName(text);
}
