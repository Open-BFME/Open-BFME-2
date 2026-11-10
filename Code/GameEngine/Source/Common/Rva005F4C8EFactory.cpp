// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005F4C8E@Rva005F4C52@@UAE?AV?$Rva005F4C8ERef@VRva005E6ED6Third@@@@HH@Z,
// retail 0x005F4C8E..0x005F4CF8 (106 bytes, EH, RET 12): slot 1 of
// Rva005F4C52's vtable. It returns a counted reference to the third
// interface (+0x14) of a new 0x2C-byte Rva005E6F9D built from both arguments
// and the +0x08 member (0x005E6ED6, now rowed with its true two-base layout; it takes the
// hidden construct-virtual-bases flag 1). The count lives in a virtual base,
// so the reference reaches it through the interface's vbptr. No WorldBuilder
// name is matched.

class AsciiString;
#include "../../Include/Common/Rva0007DF07.h"
class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
    __declspec(nothrow) Rva005CC5E5();
    virtual void slot0();
    virtual ~Rva005CC5E5();
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
#include "../../Include/GameClient/ArmyDetailsMovieClip.h"
namespace StrategicHUD {
}

class Rva005F64F5 : public StrategicHUD::ArmyDetailsMovieClip {
public:
    Rva005F64F5(int,const AsciiString &,bool);
    virtual ~Rva005F64F5();
private: void *owned8;
};
struct HeroDetailsInput;
class Rva005E6D90 { private: void *value; };
class Rva005E6F9D : public Rva005F64F5,public Rva005E4F6D {
public:
    Rva005E6F9D(int,const AsciiString &,HeroDetailsInput *);
    virtual ~Rva005E6F9D();
private: Rva005E6D90 child20;
};

class Rva005E6ED6Counted
{
public:
	virtual ~Rva005E6ED6Counted();
	void addRef() { ++m_refs; }
	int m_refs;
};

class Rva005E6ED6Second : public virtual Rva005E6ED6Counted
{
public:
	virtual void second0();
};

class Rva005E6ED6Third : public virtual Rva005E6ED6Counted
{
public:
	virtual void third0();
	int m_08;
};

template <class T>
class Rva005F4C8ERef
{
public:
	__forceinline Rva005F4C8ERef(T *pointer) : m_p(pointer) { if (pointer) pointer->addRef(); }
	Rva005F4C8ERef(const Rva005F4C8ERef &other);
	~Rva005F4C8ERef();
private:
	T *m_p;
};

class Rva005E5590Iface;

class Rva005F4C52
{
public:
	virtual Rva005F4C8ERef<Rva005E6ED6Third> rva005F4C8E(int level, int name);
	Rva005F4C8ERef<Rva005E5590Iface> createArmyDetailsPanel(int level, int name);
private:
	unsigned char m_pad04[0x08 - 4];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Third> Rva005F4C52::rva005F4C8E(int level, int name)
{
	Rva005E6F9D *panel = new Rva005E6F9D(level, *reinterpret_cast<const AsciiString *>(name), reinterpret_cast<HeroDetailsInput *>(&m_08));
	return Rva005F4C8ERef<Rva005E6ED6Third>(reinterpret_cast<Rva005E6ED6Third *>(static_cast<Rva005E3AE1 *>(panel)));
}

// ?rva005FAB34@Rva005FAAA1@@QAE?AV?$Rva005F4C8ERef@VRva005E6ED6Second@@@@HH@Z,
// retail 0x005FAB34..0x005FAB9E (106 bytes, EH, RET 12): slot 5 of
// Rva005FAAA1's vtable, the same factory returning the second interface
// (+0x0C) of the new object. The legacy return types are layout-only views;
// the provider owns Rva005CC5E5 at+C and Rva005E3AE1 at+14.
class Rva005FAAA1
{
public:
	Rva005F4C8ERef<Rva005E6ED6Second> rva005FAB34(int level, int name);
private:
	unsigned char m_pad00[0x08];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Second> Rva005FAAA1::rva005FAB34(int level, int name)
{
	Rva005E6F9D *panel = new Rva005E6F9D(level, *reinterpret_cast<const AsciiString *>(name), reinterpret_cast<HeroDetailsInput *>(&m_08));
	return Rva005F4C8ERef<Rva005E6ED6Second>(reinterpret_cast<Rva005E6ED6Second *>(static_cast<Rva005CC5E5 *>(panel)));
}

// The same factory over two other counted classes:
//   ?rva005F4CF8@Rva005F4C52@@... @0x005F4CF8 106B, slot 3 of Rva005F4C52:
//     a new 0x24-byte Rva005E54F7 (constructor 0x005E5590), interface at +0x10;
//   ?rva005CDF8B@Rva005CDF6C@@... @0x005CDF8B 106B, slot 2 of Rva005CDF6C:
//     a new 0x30-byte Rva005CDCEE (rowed164B ctor0x005CDE89), interface at +0x0C;
//     inherited Rva005CC5E5 interface, with the shared counted base at28.
//     Legacy return view only; constructor uses the real level/name/input ABI.
class AsciiString;
class Rva005E54AE:public StrategicHUD::ArmyDetailsMovieClip {public:Rva005E54AE(int,const AsciiString &,bool);virtual ~Rva005E54AE();};
class Rva005E54F7:public Rva005E54AE,public Rva005E4F6D {public:Rva005E54F7(int,const AsciiString &,void*);virtual ~Rva005E54F7();};
class Rva005E5590Iface : public virtual Rva005E6ED6Counted
{
public:
    virtual void iface0();
};

class Rva005CDE89Iface : public virtual Rva005E6ED6Counted
{
public:
	virtual void iface0();
};

struct PlanningHeroDetailsInput;
struct Rva005CDCEELink;
class Rva005CDCEE : public Rva005E6F9D
{
public:
	Rva005CDCEE(int,const AsciiString &,PlanningHeroDetailsInput *);
	virtual ~Rva005CDCEE();
private:
	Rva005CDCEELink *link24;
};

Rva005F4C8ERef<Rva005E5590Iface> Rva005F4C52::createArmyDetailsPanel(int level, int name)
{
	// The existing return view reaches the same counted base through its
    // vbptr; the provider's real third interface is Rva005E3AE1 at +10.
    Rva005E54F7 *panel = new Rva005E54F7(level, *reinterpret_cast<const AsciiString *>(name), &m_08);
    return Rva005F4C8ERef<Rva005E5590Iface>(reinterpret_cast<Rva005E5590Iface *>(static_cast<Rva005E3AE1 *>(panel)));
}

class Rva005CDF6C
{
public:
	virtual Rva005F4C8ERef<Rva005CDE89Iface> rva005CDF8B(int level, int name);
private:
	unsigned char m_pad04[0x08 - 4];
	int m_08;
};

Rva005F4C8ERef<Rva005CDE89Iface> Rva005CDF6C::rva005CDF8B(int level, int name)
{
	Rva005CDCEE *panel = new Rva005CDCEE(level, *reinterpret_cast<const AsciiString *>(name), reinterpret_cast<PlanningHeroDetailsInput *>(&m_08));
	return Rva005F4C8ERef<Rva005CDE89Iface>(reinterpret_cast<Rva005CDE89Iface *>(static_cast<Rva005CC5E5 *>(panel)));
}

// ?rva005CDBAE@Rva005CDB8F@@UAE?AV?$Rva005F4C8ERef@VRva005CD9C0Iface@@@@HH@Z,
// retail 0x005CDBAE..0x005CDC18 (106 bytes, EH, RET 12): slot 4 of
// Rva005CDB8F's vtable (after its clone 0x005CDC4A), the same factory over
// the garrison-selection details panel: a new 0x28-byte Rva005CD9C0 (rowed
// constructor 0x005CDA63, int / AsciiString / owner), interface at +0x08.
class Rva005CD9C0First : public virtual Rva005E6ED6Counted
{
public:
	virtual void first0();
};

class Rva005CD9C0Iface : public virtual Rva005E6ED6Counted
{
public:
	virtual void iface0();
};

class Rva005CD9C0 : public Rva005CD9C0First, public Rva005CD9C0Iface
{
public:
	Rva005CD9C0(int a, const AsciiString &name, void *owner);
private:
	int m_10[4];
};

class Rva005CDB8F
{
public:
	virtual Rva005F4C8ERef<Rva005CD9C0Iface> rva005CDBAE(int level, int name);
private:
	unsigned char m_pad04[0x08 - 4];
	int m_08;
};

Rva005F4C8ERef<Rva005CD9C0Iface> Rva005CDB8F::rva005CDBAE(int level, int name)
{
	return Rva005F4C8ERef<Rva005CD9C0Iface>(new Rva005CD9C0(level, *reinterpret_cast<const AsciiString *>(name), &m_08));
}
