// cl: /MD
// ??Rva002229E3Build@@YA?AURva002229E3S12@@ABDPBD@Z @0x002229E3 54B
// Free 12B struct builder: char at +0 plus Rva000B3F84Pair at +4 from string.
// Evidence: init 0x000B3F84 row WinMainPairUnicode; callers 0x005E3187 95B '_' 0x5f hide and 0x002250EF 633B; 3x movsd 12B return; prev FunctorRef next stlport.
// Donor: WinMainPairUnicode PairWithChar operator+ 0x002342F7 pattern reversed (char first).
class Rva000B3F84Pair
{
public:
    Rva000B3F84Pair *init(const char *src);
    const char *m_ptr;
    int m_len;
};
struct Rva002229E3S12
{
    char m_c;
    const char *m_ptr;
    int m_len;
};
Rva002229E3S12 __cdecl Rva002229E3Build(const char &c, const char *s)
{
    Rva000B3F84Pair p;
    p.init(s);
    Rva002229E3S12 r;
    r.m_c = c;
    r.m_ptr = p.m_ptr;
    r.m_len = p.m_len;
    return r;
}
