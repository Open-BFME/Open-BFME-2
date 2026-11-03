// cl: /DNDEBUG /MD
// ??0Rva004FAC6B@@QAE@XZ @0x004FAC6B 21B: honest ctor with member at +4.
// Evidence: calls rowed Rva00330757Member ctor 0x00330757 for member at +4; installs vtable 0x008633C0; called by derived ctor 0x004FADF4 which overrides vtable to 0x008633FC; prev row is dtor in same subsystem.

#include "../../../../Include/Common/Rva00330757Member.h"

class __declspec(novtable) Rva004FAC6BBase0
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
};

class Rva004FAC6B : public Rva004FAC6BBase0, public Rva00330757Member
{
public:
	Rva004FAC6B();
	~Rva004FAC6B();
};

Rva004FAC6B::Rva004FAC6B()
{
}

// The sibling stores 0x00BE2B78, whose three slots are pure virtual.
// Its nonvirtual destructor is owned by FreeMemberDeleters.cpp.
class Rva00578C2E : public Rva00330757Member
{
public:
	Rva00578C2E();
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	~Rva00578C2E();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00578C2E::Rva00578C2E()
{
}

// ?bfmeAnchorRva00578C2ECtor absent-from-retail
void *bfmeAnchorRva00578C2ECtor(void *where)
{
	((Rva00578C2E *)where)->Rva00578C2E::Rva00578C2E();
	return where;
}
