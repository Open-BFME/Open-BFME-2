// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::BattlePromptMovieClip::Impl::SetRetreatButtonEnabled @0x005F92D5 91B (WorldBuilder name, StrategicHUDBattlePromptMovieClip.cpp; same SetButtonState Retreat _up/_disabled) twin of 0x005F927A SetButtonState Retreat _up/_disabled.
// Evidence: rowed AptCall 0x005F8EDA; strings _up _disabled SetButtonState Retreat; empty fallback g_Rva0107301CEmptyString; manager TheRva00222A8BTarget; flag at +0x62 vs twin +0x61.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005F92D5Holder
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
	void SetRetreatButtonEnabled(bool flag);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F92D5Holder *m_team08;
	char m_pad0C[0x62 - 0x0C];
	bool m_flag62;
};

void StrategicHUD::BattlePromptMovieClip::Impl::SetRetreatButtonEnabled(bool flag)
{
	if (m_flag62 == flag)
		return;
	const char *state = flag ? "_up" : "_disabled";
	const char *team = m_team08 ? (const char *)m_team08 + 8 : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetButtonState", "Retreat", (void **)&state);
	m_flag62 = flag;
}
