// Eight helper-then-member steps (17B each): push esi, mov esi, ecx,
// call <helper>, mov ecx, [esi+off], pop esi, jmp <run>. Each runs a
// no-argument helper on this, then tail-jumps the run method of the owned
// pointer at its offset:
// 0x005D1516 (+0x08, fold-nop helper, -> 0x005D13C2),
// 0x005E1906 (+0x0C, rowed Overridable::markAsOverride, -> 0x005E18D0),
// 0x005E1917 (+0x0C, rowed Rva00420B2AZeroSetter::disable, -> 0x005E18DC),
// 0x005E1BC4 (+0x0C, fold-nop helper, -> 0x005E1B9A),
// 0x005E25DE (+0x0C, fold-nop helper, -> 0x005E254C),
// 0x005E590F (+0x08, fold-nop helper, -> 0x005E589E),
// 0x005E6BA3 (+0x20, fold-nop helper, -> 0x005E6A9D),
// 0x005E6BB4 (+0x20, fold-nop helper, -> 0x005E6AD8).
// The fold-nop helper shares one opaque alias pin at 0x000B3FD0 (the known
// folded empty body); run/member/owner identities unproven (opaque run
// pins); names are address-derived. One ledger row per step.

#include "../../Include/Common/Overridable.h"

class Rva005E549E
{
public:
	virtual void rva005E549E();
};

#include "../../Include/Common/Rva005F327ARun.h"

class Rva005E5554
{
public:
	// virtual: also reached through the this-8 thunk 0x005CDA53.
	virtual void step();
};

void Rva005E5554::step()
{
	((Rva005E549E *)this)->Rva005E549E::rva005E549E();
	((Rva005F327ARun *)((char *)this - 8))->run();
}
