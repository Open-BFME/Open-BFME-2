// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native005CDE89..005CDF2D,164B RET16, includes hidden virtual-base flag.
// Calls published191B root5E6ED6 with the same level/name/input contract.
// Retail stores primary/secondary vtables at0/C/14 and shared Count at28;
// link24 comes from input+10 and registers this at owner+20. The byte
// getter5E687F controls a call to published wrapper5E69C8. Native layout
// and callees are target facts. WB15C0550 corroborates initialization and
// PlanningPhase DetailsPanel identity, but that name remains a lead.
// Native vtableC750A0 slot0 is the existing35B scalar destructor5CDF49,
// which calls rowed50B Rva005CDCEE destructor5CDCEE. This independently
// establishes the existing owner; do not introduce a second panel class.
// Keep providers out of this TU: retail calls the8B wrapper out of line.
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
// The constructor 5E6ED6 calls the 12-byte polymorphic base at 0 and
// Rva005E4F6D at C. Its shared counted base moves to24; the second owned
// pointer at20 is independently cleared in the native102-byte teardown.
class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {public:
    ArmyDetailsMovieClip(int,const AsciiString &,int,bool);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();
private: class Impl *m_impl;
}; }
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
class Rva005F6037ByteChaseField;
struct Rva005E68C0Owner;
class Rva005E68C0
{
public:
	void rva005E68C0();
	void rva005E69AC();
	char m_pad00[0x4];
private:
	Rva005F6037ByteChaseField *guard; // +0x04
	char m_pad08[0x4];
	Rva005E68C0Owner *owner; // +0x0C
	char m_pad10[0x4];
	int selected; // +0x14
};
class Rva005E6D90
{
private:
	friend class Rva005E6F9D;
public:
	~Rva005E6D90() { clear(); }
	void clear();
	Rva005E6D90(Rva005E6D0D *p);
private:
	void *value; // +0x00
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



class Rva005CDCEE;
struct Rva005CDCEELink {
    char pad00[0x20];
    void *owner;
};
struct PlanningHeroDetailsInput : HeroDetailsInput {
    Rva005CDCEELink *planningOwner;
};
class Rva005E687F { public: unsigned char get() const; };
class Rva005CDCEE : public Rva005E6F9D {
public:
    Rva005CDCEE(int,const AsciiString &,PlanningHeroDetailsInput *);
    virtual ~Rva005CDCEE();
private:
    Rva005CDCEELink *link24;
};
Rva005CDCEE::Rva005CDCEE(int level,const AsciiString &name,PlanningHeroDetailsInput *input)
    : Rva005E6F9D(level,name,input),link24(input->planningOwner)
{
    link24->owner=this;
    if (!((const Rva005E687F *)this)->get()) rva005E69C8();
}
