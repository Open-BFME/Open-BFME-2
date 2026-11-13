// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native destructor 5E5018..5E508F has two interfaces at 0 and 8,
// shared virtual counted base at 14 and owned child at 10. The hidden
// native teardown adjusts the virtual-base this bias and clears the child.
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
// First interface ctor5CC5E5 is independently verified57B of only stores;
// its nonthrowing declaration removes an otherwise redundant initial EH state.
Rva005E4F6D::Rva005E4F6D(_Rva005E4AE2In *info, int count)
    : child(new Rva005E4AE2(this, info, count)) {}
Rva005E4F6D::~Rva005E4F6D() {}

// The constructor 5E6ED6 calls the 12-byte polymorphic base at 0 and
// Rva005E4F6D at C. Its shared counted base moves to24; the second owned
// pointer at20 is independently cleared in the native102-byte teardown.
class AsciiString;
#include "../../Include/GameClient/ArmyDetailsMovieClip.h"
namespace StrategicHUD {
}
class Rva005F64F5 : public StrategicHUD::ArmyDetailsMovieClip
{
public:
    Rva005F64F5(int,const AsciiString &,bool);
    virtual ~Rva005F64F5();
private:
    void *owned8;
};
struct HeroDetailsInput { void *owner,*details,*container; bool backButton; };
class Rva005E6D0D {
public: Rva005E6D0D(void *,HeroDetailsInput *);
private: char storage[0x20];
};
#include "../../Include/Common/Rva005E68C0.h"
class Rva005E6D90
{
    friend class Rva005E6F9D;
public:
    // ?Rva005E6D90::Rva005E6D90 absent-from-retail - inline pointer holder
    Rva005E6D90(Rva005E6D0D *p) : value(p) {}
    ~Rva005E6D90() { clear(); }
    void clear();
private:
    void *value;
};
class Rva005E6F9D : public Rva005F64F5, public Rva005E4F6D
{
public:
    Rva005E6F9D(int,const AsciiString &,HeroDetailsInput *);
    virtual ~Rva005E6F9D();
    void rva005E69C8();
private:
    Rva005E6D90 child20;
};
Rva005E6F9D::~Rva005E6F9D() {}

// Native005E69C8..005E69D0 forwards the owned listener at+20 to the
// independently matched120B roster method5E68C0. WB1601CD0 reaches the
// same owned pointer and corroborates the parent/child relationship;
// its original wrapper name is unknown, so the method stays descriptive.
void Rva005E6F9D::rva005E69C8()
{
    ((Rva005E68C0 *)child20.value)->rva005E68C0();
}


// Native005E6ED6..005E6F95,191B RET16 (hidden virtual-base flag included).
// Constructor and destructor5E6F9D install the same C77E5C owner vtable.
// Calls establish primary12B movie clip, secondary interface atC, shared
// counted virtual base24, and owned20B listener stored at20. The named
// primary base80 proves the level/name/back-button argument contract;
// input+C supplies the bool. WB1601A80 corroborates all three initializers,
// but is unnamed, so the target owner and field labels remain descriptive.
Rva005E6F9D::Rva005E6F9D(int level,const AsciiString &name,HeroDetailsInput *input)
    : Rva005F64F5(level,name,input->backButton)
    , Rva005E4F6D((_Rva005E4AE2In *)input,(int)this)
    , child20(new Rva005E6D0D(this,input)) {}
