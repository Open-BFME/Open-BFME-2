// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0057BAC4@Rva0057BAC4@@QAEXXZ @0x0057BAC4 52B unlock lane Apt Close via rowed call.
// Evidence: same shape as Rva0057BAF8Toggle 86B; prefix +0x18 plus 8 else g_Rva0107301CEmptyString; level +0x14; function Close; sets +0x28 to 3; callers 0x0057BBCA 0x0057BC3D.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);

struct Rva0057BAC4Inner
{
    char m_pad8[8];
    char m_name[1];
};

class Rva0057BAC4
{
public:
    void rva0057BAC4();
private:
    char m_pad00[0x14];
    void *m_level14;
    Rva0057BAC4Inner *m_inner18;
    char m_pad1C[0x28 - 0x1C];
    int m_state28;
};

void Rva0057BAC4::rva0057BAC4()
{
    const char *prefix = m_inner18 ? m_inner18->m_name : "";
    Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level14, prefix, "Close");
    m_state28 = 3;
}
