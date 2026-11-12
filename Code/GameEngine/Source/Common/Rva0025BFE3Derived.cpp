// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva0025BFE3::~
// Rva0025BFE3 at 0x0025BFE3 (row in FreeMemberDeleters.cpp: null-checked
// free of its member at +0x04). Each class below stores its own vtable and
// tail-calls the base destructor; the base itself is only declared here
// (defined once in FreeMemberDeleters.cpp), because a same-TU definition
// would capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();

private:
	void *m_ptr04;
};

class Rva00596069 : public Rva0025BFE3
{
public:
	Rva00596069();
	virtual ~Rva00596069();
};

// ??0Rva00596069@@QAE@XZ, retail 0x00596057, 18 bytes. Derived default ctor
// abutting its dtor at 0x00596069: calls base Rva0025BFE3 ctor at 0x0025BFC7,
// stores derived vtable 0x00870A40, returns this. No extra members.
// Caller at 0x004E0387 constructs this.
Rva00596069::Rva00596069() : Rva0025BFE3()
{
}

Rva00596069::~Rva00596069()
{
}

class AIEconomyStats : public Rva0025BFE3
{
public:
	AIEconomyStats(int player);
	virtual ~AIEconomyStats();
	int getTotalMoney() const;
	void rva0059640C(void *holder);
	void withdrawSavedAmount(int amount);
	void rva005963A1(int amount);
private:
	char m_pad08[8];
	int m_arg10;
	int m_zero14;
	int m_minusOne18;
};

class Rva0039B7AD;
class Rva0039B795;
#include "../../Include/GameLogic/Module/Rva003B0D7C.h"

// ??0AIEconomyStats@@QAE@H@Z, retail 0x00596366, 35 bytes. Derived ctor taking int:
// calls base, clears +0x14 to 0 via and, sets +0x18 to -1 via or (/O1 idioms),
// stores arg at +0x10, installs derived vtable 0x00870A50. Abtus its dtor.
// Caller at 0x004E03D4 passes an int.
AIEconomyStats::AIEconomyStats(int player) : Rva0025BFE3()
{
	m_zero14 = 0;
	m_minusOne18 = -1;
	m_arg10 = player;
}

AIEconomyStats::~AIEconomyStats()
{
}

// ?getTotalMoney@AIEconomyStats@@QBEHXZ @0x00596394 13B
// Const chase-add getter of AIEconomyStats: return *(int*)(*(int*)(this+0x10)+0x94)
// plus *(this+0x14). Evidence: neighbours 0x00596389 dtor / 0x005963F0 deleting
// dtor prove AIEconomyStats owner (+0x10 arg ptr +0x14 zero per rowed ctor
// 0x00596366); single caller at 0x005AC092; no donor string vtable or export.
// WorldBuilder AIEconomyStats::getTotalMoney, WB VA 0x0148CFD0 (callgraph lead, score 1).
int AIEconomyStats::getTotalMoney() const
{
	int const *ptr = reinterpret_cast<int const *>(m_arg10);
	return *(int const *)((char const *)ptr + 0x94) + m_zero14;
}
// ?rva0059640C@AIEconomyStats@@QAEXPAX@Z @0x0059640C 58B
// __thiscall triple virtual dispatch over holder: builds TwoBytes{1,1} local
// and calls holder vtable+0x28 with it, then holder vtable+0x78 with this+0x14
// and vtable+0x7C with this+0x18. EBP frame with push ecx local.
// Evidence: push ebp mov ebp esp push ecx/esi/edi; mov esi[ebp+8] edi ecx;
// lea [ebp-4] push mov ecx esi mov [ebp-4]1 [ebp-3]1 call [eax+28];
// lea [edi+14] push call [eax+78]; add edi18 push call [eax+7c]; ret4.
// Caller at 0x004DFA38 passes [edi+0xC] as this and holder; prev deleting dtor
// and +0x14/+0x18 members prove AIEconomyStats owner.
class Holder
{
public:
	virtual void v00(void *);
	virtual void v01(void *);
	virtual void v02(void *);
	virtual void v03(void *);
	virtual void v04(void *);
	virtual void v05(void *);
	virtual void v06(void *);
	virtual void v07(void *);
	virtual void v08(void *);
	virtual void v09(void *);
	virtual void v10(void *);
	virtual void v11(void *);
	virtual void v12(void *);
	virtual void v13(void *);
	virtual void v14(void *);
	virtual void v15(void *);
	virtual void v16(void *);
	virtual void v17(void *);
	virtual void v18(void *);
	virtual void v19(void *);
	virtual void v20(void *);
	virtual void v21(void *);
	virtual void v22(void *);
	virtual void v23(void *);
	virtual void v24(void *);
	virtual void v25(void *);
	virtual void v26(void *);
	virtual void v27(void *);
	virtual void v28(void *);
	virtual void v29(void *);
	virtual void v30(void *);
	virtual void v31(void *);
};
struct TwoBytes
{
	unsigned char a;
	unsigned char b;
};

void AIEconomyStats::rva0059640C(void *holder)
{
	TwoBytes version;
	version.a = 1;
	version.b = 1;
	Holder *xfer = (Holder *)holder;
	xfer->v10(&version);
	xfer->v30(&m_zero14);
	xfer->v31(&m_minusOne18);
}

// ?withdrawSavedAmount@AIEconomyStats@@QAEXH@Z @0x005963C8 40B
// __thiscall spend-if-available: if (amount <= m_zero14 unsigned) route
// (amount,0,true) into Money at Player+0x90 via rowed Rva003B0D7C and deduct.
// Evidence: neighbours prove AIEconomyStats owner (+0x10 Player ptr +0x14 balance
// per rowed ctor 0x00596366 and getter 0x00596394); callee row
// Rva003B0D7C 0x003B0D7C takes (int,ptr,bool); caller 0x0055ADE2 passes
// this=[result+0xC] with unsigned avail check; chain lane from 0x003B0D7C.
void AIEconomyStats::withdrawSavedAmount(int amount)
{
	if ((unsigned int)amount <= (unsigned int)m_zero14) {
		Rva003B0D7C *money = (Rva003B0D7C *)((char *)m_arg10 + 0x90);
		money->rva003B0D7C(amount, 0, true);
		m_zero14 -= amount;
	}
}

// ?rva005963A1@AIEconomyStats@@QAEXH@Z @0x005963A1 39B
// __thiscall credit-if-nonzero: if (amount != 0) route (amount,0,true) into
// Money at Player+0x90 via rowed withdraw and add to balance. Gap between
// 0x00596394 and 0x005963C8 in same TU; mirrors spend sibling withdrawSavedAmount
// but adds. Evidence: neighbours prove AIEconomyStats owner (+0x10/+0x14);
// callee row withdraw 0x003B0CB3 takes (uint,ptr,bool); caller 0x004EC14A.
void AIEconomyStats::rva005963A1(int amount)
{
	if ((unsigned int)amount <= 0u)
		return;
	Rva003B0D7C *money = (Rva003B0D7C *)((char *)m_arg10 + 0x90);
	money->withdraw((unsigned int)amount, 0, true);
	m_zero14 += amount;
}
