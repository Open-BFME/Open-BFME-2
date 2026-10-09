// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva00344EB2@@YA_NPAVObject@@PAVThing@@@Z @0x00344EB2 165B.
// Native 00344EB2..00344F57 is a cdecl predicate with two object pointers.
// No donor name is asserted: this address-derived name preserves uncertainty.
// Cdecl range-gate predicate (bool): rejects a null candidate, a flagged
// (+0x438 bit) candidate, or a failed status/flag-resolution pair (rowed
// testStatus plus double rowed rva002931F5 whose second result replaces the
// candidate), then dots the candidate-to-anchor delta against the rowed
// getUnitDirectionVector2D and requires a non-negative projection plus the
// rowed holder-entry ratio check.
#include "Coord3D.h"

struct Rva0028AC4EEntry;
class Rva001E46E1;

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Object *rva002931F5(bool flag);
	const struct Rva0028AC4EEntry *rva0028AC4E() const;

	char m_pad00[0x38];
	Coord3D position;
	char m_pad44[0x438 - 0x44];
	unsigned char m_438;
};

class Thing : public Object
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class Rva001E46E1
{
public:
	bool rva001E543F(Object *obj);
};

// Preserve the established PAV ABI while the local parameter view sequences
// its read ahead of the two ordered position reads.
bool rva00344EB2Gate(Object *, Thing *);
bool rva00344EB2Gate(Object *volatile a, Thing *b)
{
	if (b == 0)
		return false;
	if ((b->m_438 & 1) != 0)
		return false;
	if (b->testStatus(OBJECT_STATUS_26)) {
		if (b->rva002931F5(false) != 0)
			b = (Thing *)b->rva002931F5(false);
	}
	Object *anchor=a;
const volatile Coord3D& point=b->position;
float x=point.x;float y=point.y;
Coord3D delta;delta.x=x-anchor->position.x;delta.y=y-anchor->position.y;
	const Coord3D *dir = b->getUnitDirectionVector2D();
	const volatile Coord3D& direction=*dir;
float vx=direction.x;float vy=direction.y;
float dot = vx * delta.x + vy * delta.y;
	if (0.0f > dot)
		return false;
	const Rva0028AC4EEntry *entry = b->rva0028AC4E();
	if (entry != 0)
		return ((Rva001E46E1 *)entry)->rva001E543F(b);
	else
		return false;
}
