// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004F838CDestroy@@YAXPAURva004F691E@@0@Z retail 0x004F838C 25B
// Evidence: unlock lane; stride 12 via add esi 0xC plus rowed dtor 0x004F691E 13B; callers 0x004F887C 0x004F89A8 0x004F8A17 plus vector dtor next; prev Create same /O1.
//
// ??1Rva004F691E@@QAE@XZ retail 0x004F691E 13B: holder dtor releasing the
// TargetRef pointer at +8 via rowed fastcall 0x0007DEEF (tail jmp to
// ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z). Callers: this
// destroy loop, the deleting dtor 0x005677EB and Unwind funclets. Same 13B
// shape as ??1Rva0027EA49@@QAE@XZ (release at +4). It is an inline member:
// LivingWorldAutoResolveBattleLeadership.cpp expands it in line and emits the
// same select-any copy for its unwind funclet.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F691E
{
	inline __declspec(noinline) ~Rva004F691E()
	{
		if (m_08)
			ReleaseTreeHintRef00217D4C(m_08);
	}
	int m_00;
	int m_04;
	TargetRef00217D4C *m_08;
};

void __cdecl Rva004F838CDestroy(Rva004F691E *first, Rva004F691E *last)
{
	while (first != last) {
		first->~Rva004F691E();
		++first;
	}
}
