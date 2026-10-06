// cl: /MD
// ?rva00532165@Rva00532165@@QAEXGG@Z @ 0x00532165 108B.
// Union-by-rank: order by counts at +8, parent map via +4,
// remap via +0xC/+0x10, rank inc via +8 with 0xFE cap.
// Callees none. Same TU default flags as neighbours. Caller 0x0053244C.
class Rva00531A44
{
public:
    unsigned short rva00531AEE(unsigned short idx);
};
class Rva00532165
{
public:
    void rva00532165(unsigned short a, unsigned short b);
    void rva00532431(unsigned short a, unsigned short b);
private:
    int m_00;
    unsigned short *m_map;
    unsigned char *m_counts;
    unsigned short *m_aux;
    unsigned short *m_remap;
};

void Rva00532165::rva00532165(unsigned short a, unsigned short b)
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
    unsigned short t2 = m_remap[b];
    m_aux[t2] = a;
    m_remap[b] = m_remap[a];
    {
        unsigned char c = m_counts[a];
        if (c != m_counts[b])
            return;
    }
    if (m_counts[b] >= 0xFE)
        return;
    m_counts[b]++;
}
// ?rva00532431@Rva00532165@@QAEXGG@Z @ 0x00532431 (36B): __thiscall unite via Find on both args then Union.
// Evidence: same this calls rowed Find 0x531AEE twice plus rowed Union 0x532165 plus callers in 0x5324D8 0x532708 0x533BEC.
void Rva00532165::rva00532431(unsigned short a, unsigned short b)
{
    Rva00531A44 *self = (Rva00531A44 *)this;
    rva00532165(self->rva00531AEE(a), self->rva00531AEE(b));
}
