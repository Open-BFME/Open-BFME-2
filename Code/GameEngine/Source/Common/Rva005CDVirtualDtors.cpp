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
struct RvaSmallVtableZeroBase { void *m_04; };
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
    Rva0007DF07() { m_04 = 0; }
    virtual ~Rva0007DF07() {}
};
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
class Rva005E4B9D
{
public:
    Rva005E4B9D(Rva005E4AE2 *v) : value(v) {}
    ~Rva005E4B9D() { clear(); }
    void clear();
    Rva005E4AE2 *value;
};
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
class Rva005F64F5
{
public:
    virtual ~Rva005F64F5();
private:
    void *data4;
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

class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {
public:
    ArmyDetailsMovieClip(int, const AsciiString &, int, bool);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();
private:
    class Impl *m_impl;
};
}
class Rva005E54AE : public StrategicHUD::ArmyDetailsMovieClip {public:virtual ~Rva005E54AE(){}};
class Rva005E54F7 : public Rva005E54AE,public Rva005E4F6D {public:virtual ~Rva005E54F7();};
Rva005E54F7::~Rva005E54F7(){}
struct Rva005CD9C0Link {char prefix[0xc];void *owner;};
class Rva005CD9C0 : public Rva005E54F7 {public:virtual ~Rva005CD9C0();private:Rva005CD9C0Link *link1C;};
Rva005CD9C0::~Rva005CD9C0(){if(link1C)link1C->owner=0;}
