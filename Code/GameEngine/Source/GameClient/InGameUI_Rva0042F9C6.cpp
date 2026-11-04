// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Address-derived query wrapper at retail 0x0042F9C6 (20B).
// Retail loads TheInGameUI from VA 0x00DFEDF0 and dispatches slot 48
// at vtable offset +0xC0. The BFME1 ICF donor used slot 47, so its
// method name is not carried over; only the target-observed dispatch is.

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

int Rva0042F9C6InGameUISlot48Zero()
{
	return !TheInGameUI->getGUICommand();
}

// Native 0x0030F099..0x0030F0E2, cdecl with one byte-valued argument.
// Slot 48 returns a pointer here; retail reads its flags at +0x1C.
// The original value type and operation names remain unknown.
struct Rva0030F099Value
{
	char pad00[0x1C];
	unsigned int flags1C;
};

// The 117-byte callee at 0x0030EFD5 returns a flag mask. Its argument is
// forwarded by this caller, although that callee does not inspect it.
unsigned int Rva0030EFD5(bool alternate);

unsigned int Rva0030F099(bool alternate)
{
	unsigned int result = 0x44;
	if (alternate)
		result = 0x64;
	Rva0030F099Value *value = (Rva0030F099Value *)TheInGameUI->getGUICommand();
	if (value)
	{
		if (value->flags1C & 0x10)
			result |= 8;
		if (value->flags1C & 0x200000)
			result |= 0x200;
	}
	else
		result |= Rva0030EFD5(alternate);
	return result;
}
