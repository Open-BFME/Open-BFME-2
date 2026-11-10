// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native CD9C0/CDCEE complete50B destructors clear their derived link
// owners at C/20 and tail to parents54F7(93B)/6F9D(102B). Both use the
// ctor/dtor-proven shared E4F6D(119B) graph: primary interfaces0/8, vbptrs4/C,
// holder10 and shared counted virtual base14. E6F9D adds a primary12B
// base and holder20; the54F7 primary8B base destroys owned38CA(14B).
// The derived fields move the shared counted base to20/28 respectively.
// 54F7 is independently entered by CD9C0's E9 and deleting wrapper5628's
// E8; its real EH prolog and terminal RET5553 prove93B. The older false
// boundary verdict decoded a different mapping and is superseded here.
// Three existing35B scalar wrappers are rehomed from the old opaque
// virtual-base/delete-anchor views to these actual virtual destructors;
// the three incorrect nonvirtual dtor pins are retired. No new pins.
// Only destructor-visible ABI is recovered; original class names and
// unobserved virtual interface surfaces remain unresolved.
#include "../../Include/Common/Rva0007DF07.h"
class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
    __declspec(nothrow) Rva005CC5E5();
    virtual void slot0();
    virtual ~Rva005CC5E5() {}
};
class Rva005E3AE1 : public virtual Rva0007DF07
{
public:
    Rva005E3AE1();
    virtual void slot0() = 0;
    virtual ~Rva005E3AE1();
};
struct _Rva005E4AE2In;
class Rva005E4AE2
{
public:
    Rva005E4AE2(void *, _Rva005E4AE2In *, int);
private:
    char storage[0x30];
};
#include "../../Include/Common/Rva005E4B9D.h"
class Rva005E4F6D : public Rva005CC5E5, public Rva005E3AE1
{
public:
    Rva005E4F6D(_Rva005E4AE2In *, int);
    virtual ~Rva005E4F6D();
    virtual void slot0();
    virtual void slot1();
private:
    Rva005E4B9D child;
};
// The constructor 5E6ED6 calls the 12-byte polymorphic base at 0 and
// Rva005E4F6D at C. Its shared counted base moves to24; the second owned
// pointer at20 is independently cleared in the native102-byte teardown.
class AsciiString;
#include "../../Include/GameClient/ArmyDetailsMovieClip.h"
namespace StrategicHUD {
}
// Match the constructor-proven ArmyDetailsMovieClip interface and +8 owned member.
class Rva005F64F5 : public StrategicHUD::ArmyDetailsMovieClip
{
public:
    virtual ~Rva005F64F5();
private:
    void *owned8;
};
class Rva005E6D90
{
public:
    ~Rva005E6D90() { clear(); }
    void clear();
private:
    void *value;
};
class Rva005E6F9D : public Rva005F64F5, public Rva005E4F6D
{
public:
    virtual ~Rva005E6F9D();
private:
    Rva005E6D90 child20;
};



struct Rva005CDCEELink {char prefix[0x20];void *owner;};
class Rva005CDCEE : public Rva005E6F9D {public:virtual ~Rva005CDCEE();private:Rva005CDCEELink *link24;};
Rva005CDCEE::~Rva005CDCEE(){if(link24)link24->owner=0;}

class Rva005E54AE : public StrategicHUD::ArmyDetailsMovieClip {public:Rva005E54AE(int,const AsciiString &,bool);virtual ~Rva005E54AE(){}};
class Rva005E54F7 : public Rva005E54AE,public Rva005E4F6D {public:Rva005E54F7(int,const AsciiString &,void *);virtual ~Rva005E54F7();};
Rva005E54F7::~Rva005E54F7(){}
struct Rva005CD9C0Link {char prefix[0xc];void *owner;};
class Rva005CD9C0 : public Rva005E54F7 {public:virtual ~Rva005CD9C0();private:Rva005CD9C0Link *link1C;};
Rva005CD9C0::~Rva005CD9C0(){if(link1C)link1C->owner=0;}

// Native 5E5590..5E5628 (152B): primary ArmyDetailsMovieClip-derived
// constructor 5E54D5, shared E4F6D constructor at +8, and the counted
// virtual base at +1C. The third input's Boolean at +C is read as a byte.
Rva005E54F7::Rva005E54F7(int level, const AsciiString &name, void *owner)
    : Rva005E54AE(level, name, *reinterpret_cast<bool *>(static_cast<char *>(owner) + 0xC)),
      Rva005E4F6D(static_cast<_Rva005E4AE2In *>(owner), reinterpret_cast<int>(this))
{
}

// Native 5FABC1..5FAC2B (106B, RET C): a factory slot (the vtable after
// clone@Rva005FAB9E) building a 0x24-byte Rva005E54F7 (level, name, owner
// +8, most-derived) and returning a counted handle to its shared E4F6D base
// at +8 (null-checked conversion) whose virtual counted base takes the
// reference. Receiver and handle names are address-derived.
struct Rva005FABC1Handle
{
    Rva005E4F6D *m_p;
    __forceinline Rva005FABC1Handle(Rva005E4F6D *p) : m_p(p)
    {
        if (p)
            ++static_cast<Rva0007DF07 *>(p)->m_04;
    }
    ~Rva005FABC1Handle();
};

class Rva005FABC1
{
public:
    Rva005FABC1Handle rva005FABC1(int level, const AsciiString &name);
private:
    char m_prefix[8];
    char m_owner[4];
};

Rva005FABC1Handle Rva005FABC1::rva005FABC1(int level, const AsciiString &name)
{
    return Rva005FABC1Handle(new Rva005E54F7(level, name, m_owner));
}
