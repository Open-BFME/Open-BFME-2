// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Native constructor ownership supplies the derived type and layout.
// The factory parses its field table, then copies end frame into frame length.

class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
#include "../../Include/Common/Gen_00489270.h"

class Rva001DBAA4
{
public:
    Rva001DBAA4();
    virtual ~Rva001DBAA4();
    int m_4;
    bool m_8, m_9, m_A;
    int m_C;
};

class Rva00360474 : public Rva001DBAA4
{
public:
    Rva00360474();
    virtual ~Rva00360474();
    int m_10;
    int m_14;
    char m_pad[16];
    float m_28;
    int m_2c;
    int m_30;
};

// Native C16828..C16868 contains three fields and the null terminator.
extern const FieldParse s5Table0059DE10[] = {
    { "FadeImage", &INI::parseMappedImage, 0, 0x30 },
    { "StartFrame", &INI::parseInt, 0, 0x10 },
    { "EndFrame", &INI::parseInt, 0, 0x14 },
    { 0, 0, 0, 0 }
};

void s5parse0059DE10(INI *ini, Gen_00489270 *sink)
{
    Rva00360474 *t = new Rva00360474;
    ini->initFromINI(t, s5Table0059DE10);
    t->m_4 = t->m_14;
    sink->m((int)t);
}
