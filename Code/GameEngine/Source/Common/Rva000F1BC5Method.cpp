// cl: /MD /EHsc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// ?rva000F1BC5@Rva000F1BC5@@QAEXPBD@Z 0x000F1BC5 72B new Rva000F1B8F from arg plus Add to table at +4; caller none; callees new plus ctor 0x000F1B37 plus Add
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
class Rva000F1B8F {
public:
    Rva000F1B8F(const char *s);
private:
    char _s[0xC];
};
class Rva000F1BC5 {
public:
    void rva000F1BC5(const char *s);
private:
    int _p0;
    HashTableClass *m_4;
};
void Rva000F1BC5::rva000F1BC5(const char *s)
{
    Rva000F1B8F *p = new Rva000F1B8F(s);
    m_4->Add(reinterpret_cast<HashableClass *>(p));
}
