// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small vtable-referenced GameEngine bodies from .text gaps no ledger row
// covers (seat-3 batch A). Each body is reached only through a retail table in
// .rdata; retail bytes establish every shape. Owning classes are not recovered,
// so each keeps an address-derived name and a view of only the members it
// touches. Callees and globals use the ledger's existing spellings.

// --- 0x0057548A..0x005754EB: three table slots (0x00C6E638 / 0x00C6E8C0 and
// neighbours) asking TheLivingWorldLogic's rowed predicates about their
// argument; 1 when the logic exists and agrees, else 0.
struct Parent00575E4E;
struct Parent0057605D;
struct Parent00575EEA;

#include "../../Include/GameLogic/LivingWorldLogic.h"

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0057548A
{
public:
	virtual int rva0057548A(Parent00575E4E *entry);
	virtual int rva005754AB(Parent0057605D *entry);
	virtual int rva005754CC(Parent00575EEA *entry);
};

int Rva0057548A::rva0057548A(Parent00575E4E *entry)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B5A5F(entry))
		return 1;
	return 0;
}

int Rva0057548A::rva005754AB(Parent0057605D *entry)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B3484(entry))
		return 1;
	return 0;
}

int Rva0057548A::rva005754CC(Parent00575EEA *entry)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B3416(entry))
		return 1;
	return 0;
}

// --- 0x0057557F..0x00575672: five slots of the +0x14 interface of one
// multiple-inheritance object (table 0x00C6E6C0). Each override hands the
// rowed Rva005CD3AA-family factory the object's +0x0C container base, its
// +0x1C word, its +0x08 base and both arguments.
class Rva005CD1A9
{
public:
	virtual ~Rva005CD1A9();
	virtual int rva0057556D() = 0;
private:
	int m_04;
};

void rva005CD3AA(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);	// 0x005CD3AA
void rva005CD43D(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);	// 0x005CD43D
void rva005CD4D0(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);	// 0x005CD4D0
void rva005CD563(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);	// 0x005CD563

class Rva0057557FBase0
{
public:
	virtual void b0();
	int m_04;
};

class Rva0057557FBase8
{
public:
	virtual void b8();
};

class Rva0057557FIface
{
public:
	virtual void rva0057557F(void *a, void *b);
	virtual void rva005755B0(void *a, void *b);
	virtual void rva005755E1(void *a, void *b);
	virtual void rva00575612(void *a, void *b);
	virtual void s4(void *a, void *b);
	virtual void s5(void *a, void *b);
	virtual void rva00575643(void *a, void *b);
};

class Rva0057557F : public Rva0057557FBase0, public Rva0057557FBase8, public Rva005CD1A9, public Rva0057557FIface
{
public:
	virtual void rva0057557F(void *a, void *b);
	virtual void rva005755B0(void *a, void *b);
	virtual void rva005755E1(void *a, void *b);
	virtual void rva00575612(void *a, void *b);
	virtual void rva00575643(void *a, void *b);
private:
	int m_18;
	void *m_1C;												// +0x1C
};

void Rva0057557F::rva0057557F(void *a, void *b)
{
	rva005CD3AA(this, m_1C, (Rva0057557FBase8 *)this, a, b);
}

void Rva0057557F::rva005755B0(void *a, void *b)
{
	rva005CD43D(this, m_1C, (Rva0057557FBase8 *)this, a, b);
}

void Rva0057557F::rva005755E1(void *a, void *b)
{
	rva005CD4D0(this, m_1C, (Rva0057557FBase8 *)this, a, b);
}

void Rva0057557F::rva00575612(void *a, void *b)
{
	rva005CD563(this, m_1C, (Rva0057557FBase8 *)this, a, b);
}

void Rva0057557F::rva00575643(void *a, void *b)
{
	rva005CD563(this, m_1C, (Rva0057557FBase8 *)this, a, b);
}

// --- 0x0057556D (18B): a slot shared by two tables (0x00C6E6E8, 0x00C6E7EC)
// chasing +0x0C -> +0x04 through the rowed 0x00328A83 and 0x0042D697 getters.
#include "../../Include/Common/Rva00328A83PtrChaseField.h"

#include "../../Include/Common/Rva0042D697PtrChaseField.h"

struct Rva0057556DHolder
{
	int m_00;
	Rva00328A83PtrChaseField *m_04;							// +0x04
};

enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessage;
#include "../../Include/GameClient/UserInputTranslator.h"
class Listener00576C4B
{
public:
	virtual void rva00576ACB(void *, void *) = 0;
};
namespace StrategicInGameUI { class ResolveBattlesBehavior { public: class Impl; }; }
class StrategicInGameUI::ResolveBattlesBehavior::Impl : public UserInputTranslator, public Rva005CD1A9, public Listener00576C4B
{
public:
	virtual int rva0057556D();
private:
	Rva0057556DHolder *m_owner;
};

int StrategicInGameUI::ResolveBattlesBehavior::Impl::rva0057556D()
{
	return ((const Rva0042D697PtrChaseField *)m_owner->m_04->get())->get();
}

// --- 0x00574345 (8B): forward to the +0x08 HUD's rowed palantir query.
namespace StrategicHUD
{
	class Palantir;
	class HUD
	{
	public:
		Palantir *rva0042D6EC();							// 0x0042D6EC
	};
}

class Rva00574345
{
public:
	virtual StrategicHUD::Palantir *rva00574345();
private:
	int m_04;
	StrategicHUD::HUD *m_hud;								// +0x08
};

StrategicHUD::Palantir *Rva00574345::rva00574345()
{
	return m_hud->rva0042D6EC();
}

// --- 0x0057439A (20B): hand the argument's +0x2C word, when set, to this
// object's own slot 11.
struct Rva0057439AArg
{
	char m_pad00[0x2C];
	void *m_2C;												// +0x2C
};

class Rva0057439A
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11(void *p);
	virtual void rva0057439A(Rva0057439AArg *arg);
};

void Rva0057439A::rva0057439A(Rva0057439AArg *arg)
{
	if (arg->m_2C)
		s11(arg->m_2C);
}

// --- 0x005743C0 (41B): TheLivingWorldLogic exists, passes the rowed
// 0x0004253A flag-pair test and the rowed 0x002B5F8A check.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;							// 0x0004253A
};

class Rva002B5F8A
{
public:
	bool rva002B5F8A();										// 0x002B5F8A
};

class Rva005743C0
{
public:
	virtual bool rva005743C0();
};

bool Rva005743C0::rva005743C0()
{
	LivingWorldLogic *logic = TheLivingWorldLogic;
	if (logic && ((BfmeSelectionState *)logic)->isSelectionLocked() && ((Rva002B5F8A *)logic)->rva002B5F8A())
		return true;
	return false;
}

// --- 0x005743E9 (58B): pass the second argument and the first argument's
// +0x1C word, each when set, to the rowed 0x003EEE8E / 0x003EEF13 members of
// TheLivingWorldManager's +0x268 object.
class Rva003EEE8E
{
public:
	void rva003EEE8E(int v);								// 0x003EEE8E
};

class Rva003EEF13
{
public:
	void rva003EEF13(int v);								// 0x003EEF13
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva005743E9ManagerView
{
	char m_pad000[0x268];
	void *m_268;											// +0x268
};

struct Rva005743E9Arg
{
	char m_pad00[0x1C];
	int m_1C;												// +0x1C
};

class Rva005743E9
{
public:
	virtual void rva005743E9(Rva005743E9Arg *arg, int v);
};

void Rva005743E9::rva005743E9(Rva005743E9Arg *arg, int v)
{
	if (v)
		((Rva003EEE8E *)((Rva005743E9ManagerView *)TheLivingWorldManager)->m_268)->rva003EEE8E(v);
	if (arg->m_1C)
		((Rva003EEF13 *)((Rva005743E9ManagerView *)TheLivingWorldManager)->m_268)->rva003EEF13(arg->m_1C);
}

// --- 0x00574423 / 0x0057444B (40B each): when TheLivingWorldLogic exists and
// its rowed 0x002B254F guard holds, poke the rowed 0x002B256E object's proxy
// forwarders 0x003F8374 / 0x003F8385; the argument is unused.
#include "../../Include/Common/Rva002B254F.h"

class Rva002B256E
{
public:
	void *rva002B256E();									// 0x002B256E
};

#include "../../Include/Common/Rva003F81FDProxy.h"

class Rva00574423
{
public:
	virtual void rva00574423(int unused);
	virtual void rva0057444B(int unused);
};

void Rva00574423::rva00574423(int)
{
	if (TheLivingWorldLogic && (char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
		((Rva003F81FDProxy *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->rva003F8374();
}

void Rva00574423::rva0057444B(int)
{
	if (TheLivingWorldLogic && (char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
		((Rva003F81FDProxy *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->rva003F8385();
}

// --- 0x0057A31B / 0x0057A330 / 0x0057A345 (21B each): slots of the +0x08
// interface of one object forwarding the whole object to slots 1, 2 and 3 of
// its +0x54 listener when one is set.
class Rva0057A31B;

class Rva0057A31BListener
{
public:
	virtual void s0();
	virtual void s1(Rva0057A31B *owner);
	virtual void s2(Rva0057A31B *owner);
	virtual void s3(Rva0057A31B *owner);
};

class Rva0057A31BBase0
{
public:
	virtual void b0();
	int m_04;
};

class Rva0057A31BIface
{
public:
	virtual void rva0057A31B();
	virtual void rva0057A330();
	virtual void rva0057A345();
};

class Rva0057A31B : public Rva0057A31BBase0, public Rva0057A31BIface
{
public:
	virtual void rva0057A31B();
	virtual void rva0057A330();
	virtual void rva0057A345();
private:
	char m_pad0C[0x54 - 0x0C];
	Rva0057A31BListener *m_listener;						// +0x54
};

void Rva0057A31B::rva0057A31B()
{
	if (m_listener)
		m_listener->s1(this);
}

void Rva0057A31B::rva0057A330()
{
	if (m_listener)
		m_listener->s2(this);
}

void Rva0057A31B::rva0057A345()
{
	if (m_listener)
		m_listener->s3(this);
}
