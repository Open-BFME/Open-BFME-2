// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// BFME1 factory provenance retained from the original import. Native factory
// 35D0DC calls the existing 58-byte constructor 35D097, allocates 0x28 bytes,
// parses table C16428, then copies end frame +14 to frame length +4.
// The target constructor/destructor pair supplies the neutral Rva0035D0D1
// owner; the original derived-class name remains unresolved.

class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
#include "../../Include/Common/Gen_00489270.h"

class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    char m_padB;
    int m_C;
};

class Rva0035D0D1 : public Rva001DBAA4
{
public:
    Rva0035D0D1();
    virtual ~Rva0035D0D1();
    virtual void slot1(int);
    virtual void slot2(int);
    virtual void slot3();
    virtual void slot4();
    virtual void Rva0035D1C6();
    virtual void slot6();
    int m_10;
    int m_14;
    int m_18;
    bool m_1C;
    char m_pad1D[3];
    float m_20;
    bool m_24;
};

// Native DBA1F8..DBA208: complete null-terminated bit-name list, before
// the unrelated NONE/HOLD/KILL/SPAWN table. Its pointer is C16428+0x28.
const char *fadeViewBitNames[] = { "Tactical", "World", "Shell", 0 };

// Native C16428..C16478: four FieldParse records and the null record.
extern const FieldParse s5Table0059FB50[] = {
    { "StartFrame", &INI::parseInt, 0, 0x10 },
    { "EndFrame", &INI::parseInt, 0, 0x14 },
    { "ViewsToFade", &INI::parseBitString32, fadeViewBitNames, 0x18 },
    { "LeaveSilent", &INI::parseBool, 0, 0x1C },
    { 0, 0, 0, 0 }
};

void parseSoundFadeTransition(INI *ini, Gen_00489270 *sink)
{
    Rva0035D0D1 *transition = new Rva0035D0D1;
    ini->initFromINI(transition, s5Table0059FB50);
    transition->m_4 = transition->m_14;
    sink->m((int)transition);
}
