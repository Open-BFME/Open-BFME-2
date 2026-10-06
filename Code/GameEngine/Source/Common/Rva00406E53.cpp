// cl: /MD
// ?rva00406E53@Rva00406E53@@QAEHXZ @0x00406E53 18B
// Unlock lane: forwards this+0xC and this+0x10 to rowed
// Rva00219B9E::rva00219E74 on g_00DFE344; callers 0x0040891A 0x0040899F
// 0x005B5F6D 0x005B6028. Honest-address method.
class Rva00219B9E
{
public:
    int rva00219E74(unsigned int a, unsigned int b);
};
extern Rva00219B9E *g_00DFE344;

class Rva00406E53
{
    char m_pad[0x0C];
    unsigned int m_0C;
    unsigned int m_10;
public:
    int rva00406E53();
};
int Rva00406E53::rva00406E53()
{
    return g_00DFE344->rva00219E74(m_0C, m_10);
}
