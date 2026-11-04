// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?enumerateCurrentUnits@LivingWorldAutoResolveBattle@@QAEXHPAUPred004F6234@@@Z, retail 0x004F6234, 52 bytes.
// Thiscall predicate loop over slot vectors: slot = m_slots[idx], iterate begin..end step 4 calling pred virtual.
// Evidence: stride 0xC imul; offsets +0xC/+0x10 begin/end; virtual call via [edx] with ecx=pred; callers 0x005EAA9C 0x005EAB20 0x005EABD9.
#include "../../Include/GameLogic/LivingWorldAutoResolveBattle.h"

struct Pred004F6234
{
	virtual bool Check(int val);
};

void LivingWorldAutoResolveBattle::enumerateCurrentUnits(int idx, Pred004F6234 *pred)
{
	int *first = (int *)field0C[idx].m_start;
	int *last = (int *)field0C[idx].m_finish;
	for (; first != last; ++first)
	{
		int v = *first;
		if (!pred->Check(v))
			break;
	}
}
