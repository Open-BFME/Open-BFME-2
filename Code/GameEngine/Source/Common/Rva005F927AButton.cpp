// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::BattlePromptMovieClip::Impl::SetRealTimeButtonEnabled @0x005F927A 91B (WorldBuilder name, StrategicHUDBattlePromptMovieClip.cpp; same SetButtonState RealTime _up/_disabled) twin of 0x005F921F SetButtonState RealTime _up/_disabled.
// Evidence: caller 0x005F93D3 jmp thunk; callee rowed AptCall 0x005F8EDA; strings _up _disabled SetButtonState RealTime; empty fallback g_Rva0107301CEmptyString; manager TheRva00222A8BTarget; flag at +0x61 vs twin +0x60.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005F927AHolder
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
	void SetRealTimeButtonEnabled(bool flag);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F927AHolder *m_team08;
	char m_pad0C[0x61 - 0x0C];
	bool m_flag61;
};

void StrategicHUD::BattlePromptMovieClip::Impl::SetRealTimeButtonEnabled(bool flag)
{
	if (m_flag61 == flag)
		return;
	const char *state = flag ? "_up" : "_disabled";
	const char *team = m_team08 ? (const char *)m_team08 + 8 : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetButtonState", "RealTime", (void **)&state);
	m_flag61 = flag;
}
