// cl: /DNDEBUG /MD /EHsc
// ?rva005FB872@Rva005FB770@@QAEXH@Z @ 0x005FB872 66B
// Apt SetPlayerColor setter with the colour cache at +0x2c; team name at +8 else
// the default-team constant at VA 0xBBAC1C; level at +4. Evidence: "SetPlayerColor"
// at VA 0x878610, default-team constant VA 0xBBAC1C, manager VA 0xDFE4CC, wrapper
// jmp at 0x005FBB4D, same class as the matched neighbours 0x005FB7D7 0x005FB903 in
// AptPlayerNameSet.cpp.
// Target evidence for the callee shape: retail copies the colour into edi and then
// pushes `lea ecx,[esp+0xc]` -- the colour parameter's own stack slot -- so the
// callee takes `int const *` while the cache comparison uses the value copy. The
// separate `c` local is what keeps edi live across the call.
// The callee is the rowed ?Rva0052519DFire@@YAHPAX0PBD1PAH@Z at 0x0052519D:
// (int *, void *, char const *, char const *, int const *).
extern void *g_bfmeAptManager;
extern const char g_bfmeAptDefaultTeamName[1];
struct Rva005FB872Team
{
    char m_pad[8];
    const char *m_name;
};

class Rva005FB770
{
public:
    void rva005FB872(int color);
private:
    char m_pad[4];
    unsigned int m_level;
    Rva005FB872Team *m_team;
    char m_pad0C[0x2C - 0x0C];
    int m_cachedColor;
    char m_pad30[0x34 - 0x30];
    float m_cachedValue;
};

extern int __cdecl Rva0052519DFire(void *, void *, const char *, const char *,
                                   int *);

void Rva005FB770::rva005FB872(int color)
{
    int c;
    if (color == m_cachedColor)
        return;
    c = color;
    const char *team;
    if (m_team)
        team = (const char *)((char *)m_team + 8);
    else
        team = g_bfmeAptDefaultTeamName;
    Rva0052519DFire(g_bfmeAptManager, (void *)m_level, team,
                    "SetPlayerColor", &color);
    m_cachedColor = c;
}