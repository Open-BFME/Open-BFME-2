// cl: /MD
// AptLoadMovieFrame::Impl::UnloadContent (WorldBuilder name, AptLoadMovieFrame.cpp line 84: UnloadContent when loaded, then clear +0x18); 0x0057C2CC forwards to it.
// was ?rva0057C236@Rva0057C236@@QAEXXZ @0x0057C236 54B
// UnloadContent Apt setter via rowed AptCall 0x00524EF4 with team+8 or empty string.
// Evidence: retail pushes TheRva00222A8BTarget plus [esi] plus team+8-or-empty plus UnloadContent,
// clears byte at +0x18; sibling Rva005FB6E2 same Apt plus team-plus-8 or empty pattern.
class Rva00222A8BTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva0057C236Team
{
    char m_pad[8];
    char m_name[1];
};
class AptLoadMovieFrame
{
public:
	class Impl;
};
class AptLoadMovieFrame::Impl
{
public:
    void UnloadContent();
private:
    void *m_level;
    Rva0057C236Team *m_team;
    char m_pad08[0x18 - 8];
    bool m_flag;
};
void AptLoadMovieFrame::Impl::UnloadContent()
{
    if (!m_flag)
        return;
    const char *name;
    if (m_team)
        name = m_team->m_name;
    else
        name = "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, name, "UnloadContent");
    m_flag = false;
}
// ?rva0057C2CC@Rva0057C2CC@@QAEXXZ @0x0057C2CC 8B
// UnloadContent forwarder via member at +4 tail-jmp to rowed 0x0057C236.
// Evidence: retail mov ecx [ecx+4] jmp 0x0057C236; caller 0x005D1857 loads ecx from [esi+4] then calls.
class Rva0057C2CC
{
public:
    void rva0057C2CC();
private:
    char m_pad00[4];
    AptLoadMovieFrame::Impl *m_p;
};
void Rva0057C2CC::rva0057C2CC()
{
    m_p->UnloadContent();
}
