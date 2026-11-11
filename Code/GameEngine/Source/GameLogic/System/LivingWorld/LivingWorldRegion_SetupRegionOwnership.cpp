// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii
// Address-derived target body 0x003F300A (74 bytes); Ghidra supplies the
// boundary. The original member name is unknown. Retail checks an AsciiString
// at +0xE0, looks up a player by that string, updates ownership through the
// direct callee at 0x003F2A8C, then calls the rowed scheduler at 0x002B388D.

#include "../../../../Include/GameLogic/LivingWorldRegion.h"

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

typedef unsigned int UnsignedInt;

class Rva002E2903Player
{
public:
	unsigned char m_pad00[0x14];
	int m_playerID;
};

#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../../../Include/GameLogic/Rva003F2A8C.h"

class Refresh0023FA80AI;
class Refresh0023FA80Object;
class Refresh0023FA80Primary
{
public:
	void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *object);
};

static __forceinline int rva003F300ANameLength(const AsciiString *key)
{
	const char *text = *(const char **)key;
	return text ? *(const unsigned short *)(text + 4) : 0;
}

void LivingWorldRegion::SetupRegionOwnership()
{
	LivingWorldRegion *region = this;
	AsciiString *key = &region->m_fieldE0;
	if (rva003F300ANameLength(key) <= 0)
		return;
	Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(*key, 0);
	if (player != 0)
	{
		((Rva003F2A8C *)region)->rva003F2A8C(player->m_playerID);
		((Refresh0023FA80Primary *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->scheduleNullable(
			(Refresh0023FA80AI *)region, (Refresh0023FA80Object *)player);
	}
}
