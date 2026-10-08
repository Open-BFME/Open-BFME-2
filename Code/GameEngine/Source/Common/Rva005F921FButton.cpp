// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::BattlePromptMovieClip::Impl::SetAutoResolveButtonEnabled @0x005F921F 91B (WorldBuilder name, StrategicHUDBattlePromptMovieClip.cpp; same SetButtonState AutoResolve _up/_disabled) slot Apt SetButtonState AutoResolve _up/_disabled.
// Evidence: callers 0x005F93CB jmp thunk; callees rowed AptCall 0x005F8EDA; strings _up _disabled SetButtonState AutoResolve; empty fallback g_Rva0107301CEmptyString; manager TheRva00222A8BTarget; vtables none free method via ecx.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005F921FHolder
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
	void SetAutoResolveButtonEnabled(bool flag);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F921FHolder *m_team08;
	char m_pad0C[0x60 - 0x0C];
	bool m_flag60;
};

void StrategicHUD::BattlePromptMovieClip::Impl::SetAutoResolveButtonEnabled(bool flag)
{
	if (m_flag60 == flag)
		return;
	const char *state = flag ? "_up" : "_disabled";
	const char *team = m_team08 ? (const char *)m_team08 + 8 : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetButtonState", "AutoResolve", (void **)&state);
	m_flag60 = flag;
}
