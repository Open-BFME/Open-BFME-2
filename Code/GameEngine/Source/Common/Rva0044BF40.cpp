// cl: /EHsc /MD
// ??0Rva0044BF40@@QAE@VRva004C5DD0@@@Z @0x0044BF40 55B
// Ctor of the two-callback holder (YesNo kind): forward the by-value 8-byte
// ref pair at [ebp+8] as const Pair ref to the rowed ctor-like 0x0044BEB9
// (0x0044BEB9 45B), then destroy the pair via rowed dtor ??1Rva0044BA4E
// (0x0044BA4E 61B), return this. The by-value parameter is modeled as the
// pair root class Rva004C5DD0 (rowed copy ctor 0x0044BD00) whose callee-side
// dtor is the derived Rva0044BA4E dtor: callers see Rva004C5DD0 without a dtor
// (their temp of the derived class owns the release), so cl builds the outer
// holder in the argument slot. Model and flags mirror Rva0044BF77.cpp.
// Caller 0x0044C060; target evidence for the ctor identity is the call-site
// shape (receiver slot first, pair copied inline after it).
struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

#include "../../Include/Common/Rva004C5DD0Pair.h"

struct Rva0044BA4E
{
	~Rva0044BA4E();
	void *m_00;
	void *m_04;
};

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	~Rva004C5DD0() { ((Rva0044BA4E *)this)->~Rva0044BA4E(); }
};

struct Rva0044BD34;
struct Rva0044BEB9
{
	Rva0044BD34 *m_ptr;
	Rva0044BEB9 *rva0044BEB9(const Rva004C5DD0Pair &arg);
};

struct Rva0044BF40 : Rva0044BEB9
{
	Rva0044BF40(Rva004C5DD0 arg);
};

Rva0044BF40::Rva0044BF40(Rva004C5DD0 arg)
{
	rva0044BEB9((const Rva004C5DD0Pair &)arg);
}

// ??0Rva0044BFB2@@QAE@VRva004C5DD0@@@Z @0x0044BFB2 55B
// Ctor twin of rowed Rva0044BF40 above (OkCancel kind) over the rowed ctor-like
// rva0044BF13 (0x0044BF13 45B): same by-value pair, same Pair reinterpret,
// same rowed dtor 0x0044BA4E. Caller 0x0044C1BD.
struct Rva0044BDD8;
struct Rva0044BF13
{
	Rva0044BDD8 *m_ptr;
	Rva0044BF13 *rva0044BF13(const Rva004C5DD0Pair &arg);
};

struct Rva0044BFB2 : Rva0044BF13
{
	Rva0044BFB2(Rva004C5DD0 arg);
};

Rva0044BFB2::Rva0044BFB2(Rva004C5DD0 arg)
{
	rva0044BF13((const Rva004C5DD0Pair &)arg);
}
