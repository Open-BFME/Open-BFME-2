// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Retail RVA 0x00001720, 19 bytes. Free cdecl wrapper that forwards its one
// dword argument to Debug vtable slot 0xB0 on the singleton at 0x00DE0880.
// initializeAppWindows at 0x0000275D is the only call site: it pushes
// runWindowed before the call. Slot 0xB0 is the canonical header's
// unnamed vslot44(unsigned char); the wrapper name is reconstruction.

#include "../Common/debug.h"

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

void bfmeNotifyDebugWindowed(unsigned runWindowed)
{
	theDebug->vslot44(runWindowed);
}
