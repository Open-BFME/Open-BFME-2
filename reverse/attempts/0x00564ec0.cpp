// ?rva00564EC0@LivingWorldCampaignAct@@QAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?rva00564EC0@LivingWorldCampaignAct@@QAEXXZ
// Retail 0x00564EC0..0x00565085 (453 bytes). BANKED DRAFT (score ~0.9):
// 445 vs 453 bytes. Remaining codegen differences: the entry pointer
// (offset IV + base) load shape at the loop top, and the 4-argument
// rva002B8767 call: retail pushes each argument as soon as it is evaluated
// (get08 result, then the 0x1C flag through a stack temp, then the get18
// call), this build evaluates both getter calls first and pushes afterwards.
// PINS: every callee here is ICF-folded or mis-typed in the ledger, so even an
// exact body needs new names: the entry getters 0x00564DF2 / 0x000AF1DD /
// 0x00564E0D / 0x00564E28 (AsciiString copies of +0x04 / +0x08 / +0x0C /
// +0x18; rowed under dup_ and CDDrive::getDiskName names), 0x00564BF6 (returns
// the +0x10 {float,int} pair by value; rowed as an out-parameter void),
// 0x002B8767 (row spells its strings AsciiStringWI) and the empty 3-argument
// stub 0x000D1407 (ret 0xC, rowed RenderObjClass::Set_Animation) that both
// fallback calls reach.
//
// LivingWorldCampaignAct step called from 0x0056696F between rowed
// 0x00564E43 and 0x005666C5: when TheLivingWorldLogic has its +0xB0 object,
// for each 0x28-byte entry of +0x14: with a +0x18 name, either the +0x08 name
// alone (0x1D set, rowed 0x002B778A) or (pair +0x10, name +0x18, flag 0x1C,
// name +0x08) through 0x002B8767; otherwise the empty stub with the +0x04 or
// pair +0x10 first argument, the +0x0C name and the +0x20 member.
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct BfmePairWI
{
	BfmePairWI(const BfmePairWI &o) : m_f(o.m_f), m_i(o.m_i) {}
	float m_f;
	int m_i;
};

// One 0x28-byte entry of the act's +0x14 list.
class LivingWorldCampaignActEntry
{
public:
	AsciiString get04() const;		// 0x00564DF2
	AsciiString get08() const;		// 0x000AF1DD
	AsciiString get0C() const;		// 0x00564E0D
	BfmePairWI get10() const;		// 0x00564BF6
	AsciiString get18() const;		// 0x00564E28

	unsigned char m_pad00[0x1c];
	Bool getFlag1C() const { return m_1c; }
	Bool getFlag1D() const { return m_1d; }
	Bool m_1c;				// +0x1C
	Bool m_1d;				// +0x1D
	unsigned char m_pad1e[2];
	unsigned char m_20[8];			// +0x20
};

class LivingWorldLogic
{
public:
	void rva002B778A(const AsciiString &name);					// 0x002B778A
	void rva002B8767(BfmePairWI pair, const AsciiString &a, Bool flag, const AsciiString &b);	// 0x002B8767
	void rva000D1407(const AsciiString &a, const AsciiString &b, const void *where);	// 0x000D1407, empty
	void rva000D1407(const BfmePairWI &a, const AsciiString &b, const void *where);	// 0x000D1407, empty
	unsigned char m_pad00[0xb0];
	void *getB0() const { return m_b0; }
	void *m_b0;					// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

template <class T> class ActVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

class LivingWorldCampaignAct
{
public:
	void rva00564EC0();
private:
	unsigned char m_pad00[0x14];
	ActVectorView<LivingWorldCampaignActEntry> m_entries;	// +0x14
};

void LivingWorldCampaignAct::rva00564EC0()
{
	if (TheLivingWorldLogic->getB0() == 0)
		return;
	for (UnsignedInt i = 0; i < m_entries.size(); ++i)
	{
		LivingWorldCampaignActEntry &entry = m_entries[i];
		if (entry.get18().getLength() != 0)
		{
			if (entry.getFlag1D())
				TheLivingWorldLogic->rva002B778A(entry.get08());
			else
				TheLivingWorldLogic->rva002B8767(entry.get10(), entry.get18(), entry.getFlag1C(), entry.get08());
		}
		else if (entry.get04().getLength() != 0)
		{
			TheLivingWorldLogic->rva000D1407(entry.get04(), entry.get0C(), entry.m_20);
		}
		else
		{
			TheLivingWorldLogic->rva000D1407(entry.get10(), entry.get0C(), entry.m_20);
		}
	}
}
