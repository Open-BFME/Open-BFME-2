// cl: /MD
//
// Opaque three-vptr destructors tail-calling Rva0049B47C::~Rva0049B47C at
// 0x0049B47C (pinned opaque fold-point dtor; identity unproven). These bodies
// store a tertiary vptr at +0x10 and retail orders that store FIRST (+0x10,
// +0, +0xC). That order falls out of a shared PrimaryP intermediate
// (Rva0049B47C padded to 0xC plus the shared MiBase1 at +0xC) with a user
// empty destructor: each middle derives from PrimaryP plus its own B2 at
// +0x10, shares PrimaryP's +0/+0xC vptrs (patched once for the whole family)
// and keeps a per-middle B2-part vtable, then tail-calls the pinned base.
// Rva0049B47C is declared throw() (truthful: the 7B fold body cannot throw;
// mangling unchanged) so the middles stay SEH-free like retail. This
// supersedes the 0.8 partial bank (which used the direct model emitting
// (+0, +0xC, +0x10)). The scalar deleting destructor needs no vptr stores and
// is claimed from the emitted COMDAT. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

#include "../../Include/Common/MiBase1.h"

// Shared intermediate: Rva0049B47C (padded to 0xC) plus the shared MiBase1 at
// +0xC. The user empty destructor is load-bearing: it makes each middle share
// PrimaryP's +0/+0xC vptrs (instead of storing its own first), producing
// retail's (+0x10, +0, +0xC) order, and inlines to nothing so the middle still
// tail-calls the pinned fold base.
class PrimaryP : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP() {}
};

// BodyModule (ZH BodyModule.h: BehaviorModule plus BodyModuleInterface at
// +0x10). Target evidence: the BodyModule constructor 0x004BD7FD stores the
// vftable whose slot 0 is the deleting dtor 0x004BD841 (calls this dtor), and
// the InactiveBody constructor 0x004BD8BD's unwind map destroys its BodyModule
// base through 0x004BD763. Defining ~BehaviorModule inline reproduces retail's
// (+0x10, +0, +0x0C) store order and tail-jump to ~ObjectModule (0x0049B47C),
// and gives Rva004BD78F (InactiveBody) and Rva00484F5D (PillageModule) their
// full 47-slot BehaviorModuleInterface vtables (0x0085AD78 and 0x00870008).
// The deleting dtor is emitted and rowed in BodyModuleCtor.cpp (slot 0 of its
// vftable).
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#include "../../Include/GameLogic/Module/BodyModuleClass.h"

inline BehaviorModule::~BehaviorModule()
{
}

BodyModule::~BodyModule()
{
}

class Rva00484EF4_B2
{
public:
	virtual void slot0() = 0;
	virtual void slot1(int v) { m_14 = v; }

protected:
	int m_14;
};

class Rva00484EF4 : public BehaviorModule, public Rva00484EF4_B2
{
public:
	Rva00484EF4(Thing *thing, const ModuleData *data) : BehaviorModule(thing, data) {}
	virtual ~Rva00484EF4();
	virtual void *slot05() { return (Rva00484EF4_B2 *)this; }
};

Rva00484EF4::~Rva00484EF4()
{
}

// Anchor: abstract class cannot be new'd directly, so call the inline ctor
// which references the primary vtable and forces emission of the ??_G COMDAT.
#include <new>

void Rva00484EF4_Anchor(Rva00484EF4 *p, Thing *thing, const ModuleData *data)
{
	p->Rva00484EF4::Rva00484EF4(thing, data);
}

#include "../../Include/GameLogic/Module/DamageModuleInterface.h"

class Rva004B96CC : public PrimaryP, public DamageModuleInterface
{
public:
	Rva004B96CC() {}
	virtual ~Rva004B96CC();
};

Rva004B96CC::~Rva004B96CC()
{
}

// Anchor: abstract class cannot be new'd directly, so call the inline ctor
// which references the primary vtable and forces emission of the ??_G COMDAT.
void Rva004B96CC_Anchor(Rva004B96CC *p)
{
	p->Rva004B96CC::Rva004B96CC();
}

#include "../../Include/Common/CollideModuleInterface.h"

class Rva004BB68E : public PrimaryP, public CollideModuleInterface
{
public:
	Rva004BB68E() {}
	virtual ~Rva004BB68E();
	virtual bool wouldLikeToCollideWith(const Object *other) const { return false; }
	virtual bool slot02() const { return false; }
	virtual bool slot03() const { return false; }
	virtual bool slot04() const { return false; }
	virtual bool isSalvageCrateCollide() const { return false; }
};

Rva004BB68E::~Rva004BB68E()
{
}

// Anchor: abstract class cannot be new'd directly, so call the inline ctor
// which references the primary vtable and forces emission of the ??_G COMDAT.
void Rva004BB68E_Anchor(Rva004BB68E *p)
{
	p->Rva004BB68E::Rva004BB68E();
}

class Rva00462151_B2
{
public:
  virtual void f2() {}
};

class Rva00462151 : public PrimaryP, public Rva00462151_B2
{
public:
	virtual ~Rva00462151();
};

Rva00462151::~Rva00462151()
{
}

// Anchor: new/delete devirtualizes to a direct ??_G call (see above).
void Rva00462151_Anchor()
{
	Rva00462151 *p = new Rva00462151;
	delete p;
}

class Rva00484F5D : public Rva00484EF4
{
public:
	virtual ~Rva00484F5D();
};

Rva00484F5D::~Rva00484F5D()
{
}

class Rva004BD78F : public BodyModule
{
public:
	virtual ~Rva004BD78F();
};

Rva004BD78F::~Rva004BD78F()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1CollideModule@@UAE@XZ=??1Rva004BB68E@@UAE@XZ")
