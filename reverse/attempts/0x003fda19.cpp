// ?rva003FDA19@Rva003FDA19@@QAEXPBUCoord3D@@@Z
// partial score=0.72 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 003FDA19..003FDA90, 119B, RET4. The primary position worker
// updates render transforms. When slot +1C exists, the input plus the
// measured vector +AC is forwarded to the established particle-position
// worker. Original receiver and field names remain unknown.
#include "Coord3D.h"

class Rva003FB6C5 { public: void rva003FB6C5(const Coord3D *); };
struct Rva001F3899Arg { int m_00, m_04, m_08; };
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class Rva003FDA19 {
public:
	void rva003FDA19(const Coord3D *position);
private:
	char unknown00[0x1C];
	Rva001F3899Slot *slot;
	char unknown20[0xAC - 0x20];
	Coord3D offset;
};

static __forceinline void SumPosition003FDA19(Coord3D *result, const Coord3D *translation, const Coord3D *input)
{
	float x = input->x;
	float y = input->y;
	float z = input->z;
	result->x = translation->x + x;
	result->y = translation->y + y;
	result->z = translation->z + z;
}

void Rva003FDA19::rva003FDA19(const Coord3D *position)
{
	reinterpret_cast<Rva003FB6C5 *>(this)->rva003FB6C5(position);
	if (slot) {
		Coord3D point;
		SumPosition003FDA19(&point, &offset, position);
		(slot ? slot : reinterpret_cast<Rva001F3899Slot *>(Make001FCBD7()))->set(
			*reinterpret_cast<const Rva001F3899Arg *>(&point));
	}
}
