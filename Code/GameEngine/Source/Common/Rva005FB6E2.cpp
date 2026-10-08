// cl: /Oy- /MD
// ?ShowEliminated@Impl@DynamicAutoResolvePlayerPanelMovieClip@StrategicHUD@@QAEXXZ @0x005FB6E2 71B: __thiscall Apt eliminated-state setter via rowed AptCall 0x005FB5E6 with team+8 or empty string plus SetState plus _eliminated. Evidence: call-site mov ecx at 0x005FB846 plus TheRva00222A8BTarget plus level at +4 plus team at +8.
class Rva00222A8BTarget;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva005FB6E2Team
{
    char m_pad[8];
    char m_name[1];
};
namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl
{
public:
    void ShowEliminated();
    void ShowSurvived();
private:
    char m_pad0[4];
    void *m_level;
    Rva005FB6E2Team *m_team;
    char m_pad0C[0x24 - 0x0C];
    int m_done;
    char m_pad28[0x4C - 0x28];
    bool m_b4C;
    bool m_b4D;
};
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::ShowEliminated()
{
    if (m_done != 0)
        return;
    const char *teamName;
    if (m_team)
        teamName = m_team->m_name;
    else
        teamName = "";
    Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, teamName, "SetState", "_eliminated");
    m_b4C = false;
    m_b4D = false;
    m_done = 1;
}
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::ShowSurvived()
{
    if (m_done != 0)
        return;
    const char *teamName;
    if (m_team)
        teamName = m_team->m_name;
    else
        teamName = "";
    Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, teamName, "SetState", "_survived");
    m_b4C = false;
    m_b4D = false;
    m_done = 2;
}
