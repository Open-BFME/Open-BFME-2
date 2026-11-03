// cl: /O1 /MD /EHsc /DNDEBUG
//
// ??1AttackNugget@@UAE@XZ, retail 0x001F0622, 48 bytes.
// Target evidence: the audited scalar deleting dtor 0x001F0606 (vtable
// 0x00BE0FF4 slot 0) calls this body. It destroys the two-string record at
// +0x04 (0x000B6CF1), then the inlined trivial base stores vtable 0x00BE09D0.
// No derived vptr store (novtable). AttackNugget spelling is donor-carried
// per the audited pin; the base and member types are unrecovered.

extern "C" const void *const __identifier("??_7ObjectCreationNugget@@6B@")[];  // vftable 0x00BE09D0

class Rva001F0622Base
{
public:
	virtual ~Rva001F0622Base();
};

// ?Rva001F0622Base::~Rva001F0622Base present-unmatched
inline Rva001F0622Base::~Rva001F0622Base()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)__identifier("??_7ObjectCreationNugget@@6B@")));
}

#include "../../../Include/Common/BfmeStringRecord000B94D2.h"

class __declspec(novtable) AttackNugget : public Rva001F0622Base
{
public:
	virtual ~AttackNugget();

private:
	BfmeStringRecord000B94D2 m_record;	// +0x04
};

inline AttackNugget::~AttackNugget()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeAttackNuggetDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeAttackNuggetDtorInlineAnchor()
{
    static_cast<AttackNugget *>(0)->AttackNugget::~AttackNugget();
}
#pragma inline_depth()
