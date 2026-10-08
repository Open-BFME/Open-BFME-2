// cl: /Oy- /MD
// StrategicHUD::HeroArmyDetailsMovieClip::Impl::HideLeaderRankProgress (WorldBuilder name, line 219: SetLeaderRankProgressBarState _hide when shown).
// was ?rva005F61E4@Rva005F61E4@@QAEXXZ @ 0x005F61E4 60B chain via rowed AptCall 0x005FB5E6.
// Flag clearer with _hide literal, flag byte at +0x37, team +8 level +4.
// Evidence: EBP frame, rowed AptCall, literals _hide and SetLeaderRankProgressBarState,
// empty g_Rva0107301CEmptyString, manager TheRva00222A8BTarget, caller jmp 0x005F6309.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);
struct Rva005F61E4Team
{
    char m_pad[8];
    const char *m_name;
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
    void HideLeaderRankProgress();
private:
    char m_pad0[4];
    unsigned int m_level;
    Rva005F61E4Team *m_team;
    char m_pad0C[0x37 - 0x0C];
    unsigned char m_flag;
};
void StrategicHUD::HeroArmyDetailsMovieClip::Impl::HideLeaderRankProgress()
{
    if (!m_flag)
        return;
    const char *team;
    if (m_team)
        team = (const char *)((char *)m_team + 8);
    else
        team = "";
    Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level, team, "SetLeaderRankProgressBarState", "_hide");
    m_flag = 0;
}
