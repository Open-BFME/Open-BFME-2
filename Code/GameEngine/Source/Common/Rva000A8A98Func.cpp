// cl: /MD
// ?rva000A8A98@Rva000A8A98@@QAEHXZ @0x000A8A98 14B unlock.
// Null-guarded +0x20 deref else +0x04 fallback; callers 0x0005AB19 0x0005AADD.
// Evidence: mov eax [ecx] test je mov eax [eax+0x20] ret mov eax [ecx+4] ret.
// Honest address name; owner unknown so class Rva000A8A98.
class Rva000A8A98Target
{
public:
    char m_pad[0x20];
    int m_val20;
};

class Rva000A8A98
{
public:
    int rva000A8A98();
private:
    Rva000A8A98Target *m_ptr;
    int m_fallback04;
};

int Rva000A8A98::rva000A8A98()
{
    if (m_ptr != 0)
        return m_ptr->m_val20;
    return m_fallback04;
}
