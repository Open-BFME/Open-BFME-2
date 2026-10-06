// cl: /MD
// ?rva00406E8F@Rva00406E8F@@QAEHI@Z @0x00406E8F 24B
// Forward to rowed 0x00219F00 via global TheCreateAHeroManager.
// Retail: push esp+4 push ecx+10 push ecx+0c mov ecx global call.
// Callers 0x00407EC6/0x00407F56/0x00409B30/0x005B5E64/0x005B60A7/0x005B0373. Honest-address method.
class CreateAHeroManager
{
public:
    int GetAwardNameKey(unsigned int o, unsigned int o2, unsigned int i);
};
extern CreateAHeroManager *TheCreateAHeroManager;
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
    return TheCreateAHeroManager->GetAwardNameKey(m_0C, m_10, i);
}
