// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F9330@Rva005F9330@@QAEXXZ @0x005F9330 52B
// Honest address name: __thiscall FadeOut AptCall with team-name fallback, twin of 0x005C394D Go.
// Target evidence: retail mov eax,[ecx+8] test je add 8 plus pushes, rowed 0x00524EF4 callee, literal FadeOut, manager TheRva00222A8BTarget, empty fallback g_Rva0107301CEmptyString, state 2 at +0x18, caller jmp at 0x005FD8C4.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

struct Rva005F9330Holder
{
    char m_pad[8];
    char m_name[1];
};

class Rva005F9330
{
public:
    void rva005F9330();
private:
    char m_pad00[4];
    void *m_level04;
    Rva005F9330Holder *m_team08;
    char m_pad0C[0x18 - 0x0C];
    int m_state18;
};

void Rva005F9330::rva005F9330()
{
    const char *team = m_team08 ? (const char *)m_team08 + 8 : "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "FadeOut");
    m_state18 = 2;
}
