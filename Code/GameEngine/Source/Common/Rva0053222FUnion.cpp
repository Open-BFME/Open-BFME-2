// cl: /MD
// ?rva0053222F@Rva0053222F@@QAEXGG@Z @0x0053222F 84B.
// Union-by-rank: early out when words equal rank table at +0x200 decides
// swap parent map at +0 then rank increment when ranks equal below 0xFE.
// Flags /O1 /MD like prev Rva005321D1Union. Caller 0x00532494.
class Rva00531ED3
{
public:
    unsigned short rva00531ED3(unsigned short idx);
};
class Rva0053222F
{
public:
    void rva0053222F(unsigned short a, unsigned short b);
    void rva00532479(unsigned short a, unsigned short b);
private:
    unsigned short m_map[256];
    unsigned char m_counts[256];
};

void Rva0053222F::rva0053222F(unsigned short a, unsigned short b)
{
    if (a == b)
        return;
    if (m_counts[a] > m_counts[b])
    {
        unsigned short t = a;
        a = b;
        b = t;
    }
    m_map[a] = b;
    unsigned char c = m_counts[b];
    if (m_counts[a] != c)
        return;
    if (c >= 0xFE)
        return;
    m_counts[b] = (unsigned char)(c + 1);
}

// ?rva00532479@Rva0053222F@@QAEXGG@Z @0x00532479 36B. Unite via Find 0x00531ED3 twice plus Union 0x0053222F same this. Caller 0x00532A82.
void Rva0053222F::rva00532479(unsigned short a, unsigned short b)
{
    Rva00531ED3 *self = (Rva00531ED3 *)this;
    rva0053222F(self->rva00531ED3(a), self->rva00531ED3(b));
}
