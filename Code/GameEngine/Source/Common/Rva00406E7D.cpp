// cl: /MD
// ?rva00406E7D@Rva00406E7D@@QAEHXZ @0x00406E7D 18B
// Unlock lane: forwards this+0xC and this+0x10 to rowed
// Rva00219B9E::rva00219ED5 on g_00DFE344; sibling of 0x00406E53.
// Callers 0x00407E9F 0x00407F2E 0x00409B1E 0x00409C20 0x005B0362 0x005B608A.
// Honest-address method.
class Rva00219B9E
{
public:
    int rva00219ED5(unsigned int a, unsigned int b);
};
extern Rva00219B9E *g_00DFE344;

class Rva00406E7D
{
    char m_pad[0x0C];
    unsigned int m_0C;
    unsigned int m_10;
public:
    int rva00406E7D();
};
int Rva00406E7D::rva00406E7D()
{
    return g_00DFE344->rva00219ED5(m_0C, m_10);
}
