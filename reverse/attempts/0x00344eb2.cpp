// ?rva00344EB2@@YA_NPAVObject@@PAVThing@@@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva00344EB2@@YA_NPAVObject@@PAVThing@@@Z @0x00344EB2 165B.
// Cdecl range-gate predicate (bool): rejects a null candidate, a flagged
// (+0x438 bit) candidate, or a failed status/flag-resolution pair (rowed
// testStatus plus double rowed rva002931F5 whose second result replaces the
// candidate), then dots the candidate-to-anchor delta against the rowed
// getUnitDirectionVector2D and requires a non-negative projection plus the
// rowed holder-entry ratio check.
struct Coord3D
{
	float x;
	float y;
	float z;
};

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
	float m_38;
	float m_3C;
	char m_pad40[0x438 - 0x40];
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

bool rva00344EB2(Object *a, Thing *b)
{
	volatile char framePad[4];
	(void)framePad;
	if (b == 0)
		return false;
	if ((b->m_438 & 1) != 0)
		return false;
	if (b->testStatus(OBJECT_STATUS_26)) {
		if (b->rva002931F5(false) != 0)
			b = (Thing *)b->rva002931F5(false);
	}
	float dx = b->m_38 - a->m_38;
	float dy = b->m_3C - a->m_3C;
	const Coord3D *dir = b->getUnitDirectionVector2D();
	float dot = dir->x * dx + dir->y * dy;
	if (0.0f > dot)
		return false;
	const Rva0028AC4EEntry *entry = b->rva0028AC4E();
	if (entry != 0)
		return ((Rva001E46E1 *)entry)->rva001E543F(b);
	else
		return false;
}
