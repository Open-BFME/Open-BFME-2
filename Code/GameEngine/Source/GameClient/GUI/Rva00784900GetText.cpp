// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /I. /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
#include "unicode_string.h"

class Rva00784900TextSource
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual UnicodeString getText();
};

class Rva00784900
{
public:
    UnicodeString getText();
private:
    unsigned char m_prefix[8];
    Rva00784900TextSource *m_source;
};

UnicodeString Rva00784900::getText()
{
    UnicodeString text;
    if (m_source)
        text = m_source->getText();
    return text;
}
