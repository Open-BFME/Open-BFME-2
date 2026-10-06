// cl: /MD
// ?rva00406E65@Rva00406E65@@QAEHI@Z @0x00406E65 24B
// Forward to rowed 0x00219E9F via global TheCreateAHeroManager.
// Retail: push esp+4 push ecx+10 push ecx+0c mov ecx global call.
// Callers 0x0040892E/0x005B5F7F. Honest-address method.
class CreateAHeroManager
{
public:
    int GetStatNameKey(unsigned int o, unsigned int o2, unsigned int i);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva00406E65
{
    char m_pad[0x0C];
    unsigned int m_0C;
    unsigned int m_10;
public:
    int rva00406E65(unsigned int i);
};

int Rva00406E65::rva00406E65(unsigned int i)
{
    return TheCreateAHeroManager->GetStatNameKey(m_0C, m_10, i);
}
