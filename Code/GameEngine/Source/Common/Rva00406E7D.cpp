// cl: /MD
// ?rva00406E7D@Rva00406E7D@@QAEHXZ @0x00406E7D 18B
// Unlock lane: forwards this+0xC and this+0x10 to rowed
// CreateAHeroManager::GetAwardCount on TheCreateAHeroManager; sibling of 0x00406E53.
// Callers 0x00407E9F 0x00407F2E 0x00409B1E 0x00409C20 0x005B0362 0x005B608A.
// Honest-address method.
class CreateAHeroManager
{
public:
    int GetAwardCount(unsigned int a, unsigned int b);
};
extern CreateAHeroManager *TheCreateAHeroManager;

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
    return TheCreateAHeroManager->GetAwardCount(m_0C, m_10);
}
