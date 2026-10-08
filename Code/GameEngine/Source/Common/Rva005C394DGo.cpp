// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"

// ?rva005C394D@Rva005C394D@@QAEXXZ @0x005C394D 40B
// AptCall Go with empty fallback: if string holder +4 null use
// g_Rva0107301CEmptyString else +8, then AptCall with manager
// TheRva00222A8BTarget, member +0 and literal "Go".
// Evidence: retail mov eax,[ecx+4] test je add 8 plus pushes, rowed
// 0x00524EF4 callee, caller jmp at 0x00567D90.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva005C394D
{
public:
    void rva005C394D();
private:
    void *m_p00;
    AsciiString m_s04;
};

void Rva005C394D::rva005C394D()
{
    char *t = *(char **)(void *)&m_s04;
    const char *s = t ? t + 8 : "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_p00, s, "Go");
}
