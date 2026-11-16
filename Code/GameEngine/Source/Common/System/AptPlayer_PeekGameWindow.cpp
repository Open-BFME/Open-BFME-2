// flags: region default (reverse/retail_inventory/flag_regions.csv)
// AptPlayer::PeekGameWindow (WorldBuilder name, AptPlayer.cpp line 1515: bounds-checked level slot lookup).

// was ?rva0022252D@Rva0022252D@@QAEPAXH@Z, retail 0x0022252D, 26 bytes.
// Bounds-checked slot lookup: 14 records at this+0xCC stride 0x28 return
// the record's +8 pointer else null. Callers 0x004115CF 0x00412017 pass level from
// Rva004128BBGetLevel through global 0x009FE4CC.
#include "../../../../Libraries/Source/Apt/AptPlayerClass.h"

void *AptPlayer::PeekGameWindow(int index)
{
	if ((unsigned int)index >= 14)
		return 0;
	return field0CC[index].field08;
}
