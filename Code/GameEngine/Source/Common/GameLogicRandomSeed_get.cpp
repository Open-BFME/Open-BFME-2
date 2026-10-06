// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomSeed@@YAIXZ @ 0x00233F6A (6B) trial port from
// Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomSeed). Dedicated TU; the base seed global is
// TU-local here and patched to retail's data address.
typedef unsigned int UnsignedInt;

static UnsignedInt theGameLogicBaseSeed;

// ?GetGameLogicRandomSeed@@YAIXZ
UnsignedInt GetGameLogicRandomSeed(void)
{
	return theGameLogicBaseSeed;
}
