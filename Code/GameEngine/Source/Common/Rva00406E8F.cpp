// cl: /MD
// ?rva00406E8F@Rva00406E8F@@QAEHI@Z @0x00406E8F 24B
// Forward to rowed 0x00219F00 via global g_00DFE344.
// Retail: push esp+4 push ecx+10 push ecx+0c mov ecx global call.
// Callers 0x00407EC6/0x00407F56/0x00409B30/0x005B5E64/0x005B60A7/0x005B0373. Honest-address method.
class Rva00219B9E
{
public:
    int rva00219F00(unsigned int o, unsigned int o2, unsigned int i);
};
extern Rva00219B9E *g_00DFE344;
class Rva00406E8F
{
    char m_pad[0x0C];
    unsigned int m_0C;
    unsigned int m_10;
public:
    int rva00406E8F(unsigned int i);
};
int Rva00406E8F::rva00406E8F(unsigned int i)
{
    return g_00DFE344->rva00219F00(m_0C, m_10, i);
}
