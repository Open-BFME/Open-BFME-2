// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// StrategicHUD::RegionDetailsArmiesMovieClip::Impl::HideArmyName retail
// 0x005EF283 59B (WorldBuilder name: SetArmyNameState _hide, the ShowArmyName pair)
// Evidence: rowed AptCall 0x005FB5E6 with SetArmyNameState _hide; globals TheRva00222A8BTarget 0x009FE4CC g_Rva0107301CEmptyString 0x007BAC1C; caller forwarder 0x005EF3DE; precedent Rva005EF557ArmyName.cpp show/hide pair.
class Rva00222A8BTarget
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005EF283Team
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005EF283Outer
{
	Rva005EF283Team *m_team;
};

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

#include "RegionDetailsArmiesClipImplView.h"

void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::HideArmyName()
{
	if (!m_armyNameShown) {
		return;
	}
	const char *team = m_name.str();
	Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level, team, "SetArmyNameState", "_hide");
	m_armyNameShown = false;
}
