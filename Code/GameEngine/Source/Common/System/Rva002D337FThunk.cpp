// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D337F@RadarWindowOverrideSource@@QAEXXZ @ 0x002D337F 10B: call
// setHideScroll then tail-jmp hideSpellBook (was the free Rva002D337FHide).
// Evidence: leaf packet calls rowed 0x003FE8EB and 0x003FE99C; its one caller
// 0x002BF462 (LivingWorld::rva002BF391) loads theRadarWindowOverrideSource
// into ECX first, so it is a member that does not use this.
void __cdecl setHideScroll();
void __cdecl hideSpellBook();
#include "../../../Include/Common/RadarWindowOverrideSource.h"
void RadarWindowOverrideSource::rva002D337F()
{
	setHideScroll();
	hideSpellBook();
}
