// cl: /MD
// StrategicHUD::HeroArmyDetailsMovieClip::Impl::ShowLeaderRankProgress (WorldBuilder name, lines 201..208: SetLeaderRankProgress on change, SetLeaderRankProgressBarState _show once).
// was ?rva005F6439@Rva005F6439@@QAEXM@Z retail 0x005F6439 135B
// Evidence: gap between Rva005F6220Apt rows 0x005F63EC and 0x005F64C0; ucomiss float at +0x30 plus rowed Fire 0x00527925 SetLeaderRankProgress plus rowed AptCall 0x005FB5E6 SetLeaderRankProgressBarState _show once-flag +0x37; globals TheRva00222A8BTarget 0x009FE4CC g_Rva0107301CEmptyString 0x007BAC1C; caller 0x005F64D3; precedents Rva005D4B1F float-Fire plus Rva005F7670 show-once
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

struct Rva005F6439Team
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD
{
class HeroArmyDetailsMovieClip
{
public:
	class Impl;
};
}
class StrategicHUD::HeroArmyDetailsMovieClip::Impl
{
public:
	void ShowLeaderRankProgress(float v);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F6439Team *m_team08;
	char m_pad0C[0x30 - 0x0C];
	float m_progress30;
	char m_pad34[0x37 - 0x34];
	bool m_shown37;
};

void StrategicHUD::HeroArmyDetailsMovieClip::Impl::ShowLeaderRankProgress(float v)
{
	if (v != m_progress30) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetLeaderRankProgress", &v);
		m_progress30 = v;
	}
	if (!m_shown37) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetLeaderRankProgressBarState", "_show");
		m_shown37 = true;
	}
}
