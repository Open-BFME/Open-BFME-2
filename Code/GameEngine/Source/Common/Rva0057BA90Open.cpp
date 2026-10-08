// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0057BA90@Rva0057BA90@@QAEXXZ @0x0057BA90 52B leaf lane Apt Open via rowed call.
// Evidence: same shape as Rva0057BAC4Close 52B; prefix +0x18 plus 8 else g_Rva0107301CEmptyString; level +0x14; function Open; sets +0x28 to 1; callers 0x0057BC31 0x0057BC20.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);

struct Rva0057BA90Inner
{
    char m_pad8[8];
    char m_name[1];
};

class Rva0057BA90
{
public:
    void rva0057BA90();
private:
    char m_pad00[0x14];
    void *m_level14;
    Rva0057BA90Inner *m_inner18;
    char m_pad1C[0x28 - 0x1C];
    int m_state28;
};

void Rva0057BA90::rva0057BA90()
{
    const char *prefix = m_inner18 ? m_inner18->m_name : "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level14, prefix, "Open");
    m_state28 = 1;
}
