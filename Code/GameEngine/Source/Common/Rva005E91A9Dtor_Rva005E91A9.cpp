// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /EHsc /MD
// Split from Rva005E91A9Dtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#include "ascii_string.h"
class Image;
class Rva005E12D1
{
public:
    Rva005E12D1(void *, const AsciiString &, void *);
    virtual ~Rva005E12D1();
private:
    char holderStorage[0x10];
};
#include "../../Include/Common/Rva005E1158.h"
#include "../../Include/Common/Rva005E16B9.h"
class Rva005E16DA;
extern Rva005E16DA g_cancelArmyMoveButton;
class Rva005E91A9Base
{
public:
    __declspec(dllimport) __forceinline Rva005E91A9Base() : m_04(0) {}
    virtual ~Rva005E91A9Base() {}
protected:
    int m_04;
};
class Rva005F5C77Base0 : public Rva005E91A9Base
{
public:
    virtual ~Rva005F5C77Base0() {}
    // Retail's table 0x00C7A630 holds the shared empty body 0x000B3FD0 here.
    virtual void rva005E9163() {}
};
class Rva005E91A9 : public Rva005F5C77Base0, public Rva005E12D1
{
public:
    Rva005E91A9(unsigned int owner, void *record);
    virtual ~Rva005E91A9();
    virtual void rva005E9163();
private:
    unsigned int m_state;
};
Rva005E91A9::Rva005E91A9(unsigned int owner, void *record)
    : Rva005E12D1((void *)owner, AsciiString("button"), *(void **)record)
{
    m_state = ((unsigned int *)record)[1];
    reinterpret_cast<Rva005E1158 *>(static_cast<Rva005E12D1 *>(this))->rva005E1158(((Rva005E16B9 *)&g_cancelArmyMoveButton)->GetImage());
}

