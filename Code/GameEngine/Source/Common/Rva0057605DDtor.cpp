// cl: /MD /EHsc
// ??1Rva0057605D@@UAE@XZ retail 0x00575E9C 78B
// Two-base dtor: own vptrs C6E6A0 at +0 and C6E690 at +8; under EH state 1
// the body unregisters the +8 subobject from the list at +8 of the object
// held at +0xC through the rowed ?rva002B7250@Rva002B7250 0x002B7250; the
// inline base dtors then restore C77F44 (+8) and C6E60C (+0). Caller: rowed
// ??_GRva0057605D 0x005760B1. Names address-derived.

class CreateAHeroData;

#include "../../Include/Common/Rva002B7250.h"

struct Rva0057605DOwner
{
	unsigned char m_pad[8];
	Rva002B7250 m_list; // +0x08
};

class Rva0057605DBase
{
public:
	virtual ~Rva0057605DBase() {}
	// Retail table 0x00C6E60C holds __purecall at slot 1; the derived table
	// 0x00C6E6A0 holds 0x00575DE6 there.
	virtual void rva00575DE6() = 0;

private:
	int m_04;
};

#include <new.h>
#include "../../Include/Common/Rva0057605DSecond.h"
// ??0Rva0057605DSecond@@QAE@XZ @0x002B251A 9B: the default constructor, storing the
// class's own vtable (VA 0x00C77F44) and returning this.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0057605DSecond::Rva0057605DSecond()
{
}

// ?bfmeAnchorRva0057605DSecond absent-from-retail
void *bfmeAnchorRva0057605DSecond(void *where)
{
	return new (where) Rva0057605DSecond();
}

class Rva0057605D : public Rva0057605DBase, public Rva0057605DSecond
{
public:
	virtual ~Rva0057605D();
private:
	// Native+C pointer stays in the enclosing minimal view.
	Rva0057605DOwner *m_owner;
};

Rva0057605D::~Rva0057605D()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva0057605DSecond *>(this));
}
