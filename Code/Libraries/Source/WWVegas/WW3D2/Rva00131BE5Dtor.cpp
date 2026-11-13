// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1Rva00131BE5@@UAE@XZ @ 0x00131BE5 (91B), unlock lane: dtor stores vtable 0x007D25D8 then deletes m_14 via virtual slot1 then Free_String at +0x18 then base bfmeResetUB. Callers 0x00131D42 0x001320B7.

class __declspec(novtable) BfmeThingUB
{
public:
    virtual ~BfmeThingUB() { bfmeResetUB(); }
    void bfmeResetUB();
    unsigned char m_bfmeGap[8];
    void *m_bfmeWhat;
};

class Rva00131BE5;

#include "../WWLib/StringClassData.h"
__forceinline StringClass::~StringClass(void) { Free_String(); }

#include "../../../../GameEngine/Include/Common/Rva00131BE5M14.h"

#include <new>

class Rva00131BE5 : public BfmeThingUB
{
public:
    virtual ~Rva00131BE5();
    int m_10;
    Rva00131BE5M14 *m_14;
    StringClass m_str;
};

Rva00131BE5::~Rva00131BE5()
{
    void *p;
    if (m_14)
        p = m_14->v04(0);
    else
        p = 0;
    ::operator delete(p);
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
