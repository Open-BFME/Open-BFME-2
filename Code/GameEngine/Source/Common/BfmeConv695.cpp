#include <new.h>

class BfmeThingDGD
{
public:
	BfmeThingDGD(void *a) throw();
};

#include "../../Include/GameNetwork/Gen007F0130.h"

BfmeThingDGD *bfmeGoDGD(void *a)
{
	void *p = Gen007F0130::operator new(0x6e0);
	if (p != 0)
		return new (p) BfmeThingDGD(a);
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Gen007F86A0@@YAPAURva007E9EF0Cached@@PAURva007E9EF0Owner@@@Z=?bfmeGoDGD@@YAPAVBfmeThingDGD@@PAX@Z")
