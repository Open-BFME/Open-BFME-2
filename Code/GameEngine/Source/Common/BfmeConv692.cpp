#include <new.h>

class BfmeThingDGF;

#include "../../Include/GameNetwork/Gen007F0130.h"

class Rva007EAServiceList;

class BfmeThingTWA
{
public:
	BfmeThingTWA(Rva007EAServiceList *service) throw();
};

BfmeThingDGF *bfmeGoDGF(void *a)
{
	void *p = Gen007F0130::operator new(0x30);
	if (p != 0)
		return (BfmeThingDGF *)new (p) BfmeThingTWA((Rva007EAServiceList *)a);
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Gen007F89D0@@YAPAURva007E9F30Cached@@PAURva007E9F30Owner@@@Z=?bfmeGoDGF@@YAPAVBfmeThingDGF@@PAX@Z")
