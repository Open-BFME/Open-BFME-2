// cl: /GX /DNDEBUG /MD /Ireference/shims/moduledata /DBFME_STRINGBASE_PUBLIC_DTOR
//
// ??1SpellRechargeModifierUpgradeModuleData@@UAE@XZ, retail 0x004B608A,
// 75 bytes. ModuleData dtor: destroys the AsciiString at +0x128 through the
// folded StringBase<char> teardown at 0x00036410 (state 1) then frees the
// +0x118 vector buffer through the rowed _free at 0x00030830 (state 0) then
// restores the canonical Snapshot base vtable 0x00BBB554. No out-of-line
// base call; the inherited 0x118-byte state has no cleanup here.
// Layout from the rowed ctor 0x004B6011 (base
// 0x118 via OpenContain 0x253487, vector at +0x118, flag at +0x124, string
// at +0x128, size 0x12C via factory 0x002503A2) and table 0x00C58460.
// Caller is the slot-0 ??_G at 0x004B606E (vtable 0x008583E0). Shape follows
// RemoveUpgradeUpgradeModuleDataDtor (inline Snapshot teardown, novtable
// derived, empty body) plus OilSpillUpdateDtor
// (void* buffer modeled as inline-free vector since trivial destruction only
// frees) plus EmotionTrackerUpdateModuleDataDtor (custom EntryVec with
// null-checked free carrying the unwind state).

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "Common/Snapshot.h"

#include "../../../../../../reference/shims/bfme2_ascii/string_base.h"

struct Vec118
{
	~Vec118()
	{
		if (m_start != 0)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class __declspec(novtable) SpellRechargeModifierUpgradeModuleData : public Snapshot
{
public:
	virtual ~SpellRechargeModifierUpgradeModuleData();

private:
	// The inherited ModuleData state is opaque here; members still start at +0x118.
	unsigned char m_moduleDataState[0x118 - sizeof(Snapshot)];
	Vec118 m_vec118; // +0x118
	bool m_flag124; // +0x124
	unsigned char m_pad125[3];
	StringBase<char> m_str128; // +0x128
};

SpellRechargeModifierUpgradeModuleData::~SpellRechargeModifierUpgradeModuleData()
{
}
