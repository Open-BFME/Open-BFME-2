// cl: /MD /EHsc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// ??0Rva000F0AF7@@QAE@XZ 0x000F0AF7 110B ctor of 8-byte holder of two HashTableClass(0x800); caller 0x000F1A32 does new 8 + this ctor
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
class Rva000F0AF7 {
public:
    Rva000F0AF7();
private:
    HashTableClass *m_a;
    HashTableClass *m_b;
};
Rva000F0AF7::Rva000F0AF7()
{
    m_a = new HashTableClass(0x800);
    m_b = new HashTableClass(0x800);
}
