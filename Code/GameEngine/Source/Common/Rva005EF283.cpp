// cl: /MD /EHsc
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
	void HideArmyName();
private:
	int m_level00;
	Rva005EF283Outer m_outer04;
	char m_pad08[0x3C - 0x08];
	bool m_shown3C;
};

void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::HideArmyName()
{
	if (!m_shown3C) {
		return;
	}
	const char *team = m_outer04.m_team ? m_outer04.m_team->m_name : "";
	Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level00, team, "SetArmyNameState", "_hide");
	m_shown3C = false;
}
