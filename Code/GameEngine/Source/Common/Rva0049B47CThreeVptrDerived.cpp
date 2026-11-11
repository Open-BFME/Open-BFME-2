// cl: /MD /GX
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

class Rva00484EF4_B2
{
public:
  virtual void f2() {}
};

class Rva00484EF4 : public PrimaryP, public Rva00484EF4_B2
{
public:
	virtual ~Rva00484EF4();
};

Rva00484EF4::~Rva00484EF4()
{
}

// Anchor: forces emission of the scalar deleting destructor COMDAT (an
// out-of-class destructor no longer emits ??_G on its own, and `delete` on a
// pointer would only virtual-call it). Deleting a freshly-newed object lets
// the compiler devirtualize to a direct ??_G call, which emits the COMDAT;
// ??_G calls the dtor above plus the pinned operator delete. The anchor
// itself is unclaimed scratch. Operator new/delete resolve to their pins.
#include <new>

void Rva00484EF4_Anchor()
{
	Rva00484EF4 *p = new Rva00484EF4;
	delete p;
}

// BodyModule (ZH BodyModule.h: BehaviorModule plus BodyModuleInterface at
// +0x10). Target evidence: the BodyModule constructor 0x004BD7FD stores the
// vftable whose slot 0 is the deleting dtor 0x004BD841 (calls this dtor), and
// the InactiveBody constructor 0x004BD8BD's unwind map destroys its BodyModule
// base through 0x004BD763. PrimaryP stands for BehaviorModule (its +0/+0xC
// vftables 0x007EEA7C/0x007EE9C0 are BehaviorModule's). The +0x10 interface
// is the one-slot pure view BodyModuleCtor.cpp uses, so the shared
// ??_7BodyModule@@6B@ copies agree. The deleting dtor is emitted and rowed in
// BodyModuleCtor.cpp (slot 0 of its vftable).
#include "../../Include/GameLogic/Module/BodyModule.h"

class BodyModule : public PrimaryP, public BodyModuleInterface
{
public:
	virtual ~BodyModule();
};

BodyModule::~BodyModule()
{
}

class Rva004B96CC_B2
{
public:
  virtual void f2() {}
};

class Rva004B96CC : public PrimaryP, public Rva004B96CC_B2
{
public:
	virtual ~Rva004B96CC();
};

Rva004B96CC::~Rva004B96CC()
{
}

// Anchor: new/delete devirtualizes to a direct ??_G call (see above).
void Rva004B96CC_Anchor()
{
	Rva004B96CC *p = new Rva004B96CC;
	delete p;
}

class Rva004BB68E_B2
{
public:
  virtual void f2() {}
};

class Rva004BB68E : public PrimaryP, public Rva004BB68E_B2
{
public:
	virtual ~Rva004BB68E();
};

Rva004BB68E::~Rva004BB68E()
{
}

// Anchor: new/delete devirtualizes to a direct ??_G call (see above).
void Rva004BB68E_Anchor()
{
	Rva004BB68E *p = new Rva004BB68E;
	delete p;
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
