// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling DieModule::~DieModule
// at 0x0045CE54. Each class below derives (in order) from DieModule, a shared
// empty polymorphic base, and its own empty polymorphic base, giving vptrs at
// +0x00/+0x0C/+0x10; the empty bases have implicit trivial destructors (no
// code, no calls), so the derived destructor stores all three vptrs and
// tail-calls the DieModule destructor. The +0x0C secondary is shared across
// the family (none of them override the shared base), the other two are
// per-class. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class DieModule
{
protected:
	virtual ~DieModule();

private:
	char m_pad04[8];
};

#include "../../../../Include/Common/MiBase1.h"

class Rva004C227A_B2
{
public:
	virtual void f2();
};

class Rva004C227A : public DieModule, public MiBase1, public Rva004C227A_B2
{
public:
	virtual ~Rva004C227A();
};

Rva004C227A::~Rva004C227A()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva004C227A_B2@@UAEXXZ=?onDie@HeroDie@@UAEXPBVDamageInfo@@@Z")
