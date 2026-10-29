// cl: /MD
// ?rva005321D1@Rva005321D1@@QAEXGG@Z @ 0x005321D1 94B.
// Union-style with indirection: order two words, parent map via +4,
// remap via +0xC/+0x10 tables, rank bytes via +8 with 0xFE cap.
// Callees none. Same TU default flags as neighbours. Caller 0x00532470.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva00531C5A
{
public:
    unsigned short rva00531C5A(unsigned short idx);
};
class Rva005321D1
{
public:
    void rva005321D1(unsigned short firstRoot, unsigned short secondRoot);
    void LinkSets(unsigned short a, unsigned short b);
private:
    int m_00;
    unsigned short *m_map;
    unsigned char *m_counts;
    unsigned short *m_aux;
    unsigned short *m_remap;
};

void Rva005321D1::rva005321D1(unsigned short firstRoot, unsigned short secondRoot)
{
    if (firstRoot == secondRoot)
        return;
    if (firstRoot > secondRoot)
    {
        unsigned short savedRoot = firstRoot;
        firstRoot = secondRoot;
        secondRoot = savedRoot;
    }
    m_map[firstRoot] = secondRoot;
    unsigned short remappedIndex = m_remap[secondRoot];
    m_aux[remappedIndex] = firstRoot;
    m_remap[secondRoot] = m_remap[firstRoot];
    unsigned char c = m_counts[firstRoot];
    if (c != m_counts[secondRoot])
        return;
    _ReadWriteBarrier();
    if (m_counts[secondRoot] >= 0xFE)
        return;
    m_counts[secondRoot]++;
}
// ?LinkSets@Rva005321D1@@QAEXGG@Z @ 0x00532455 (36B): __thiscall unite via Find on both args then Union.
// Evidence: same this calls rowed Find 0x531C5A twice plus rowed Union 0x5321D1 plus callers in 0x5324D8 0x533BEC.
void Rva005321D1::LinkSets(unsigned short a, unsigned short b)
{
    Rva00531C5A *self = (Rva00531C5A *)this;
    rva005321D1(self->rva00531C5A(a), self->rva00531C5A(b));
}
