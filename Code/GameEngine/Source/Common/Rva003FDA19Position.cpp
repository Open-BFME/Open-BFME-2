// ?rva003FDA19@Rva003FDA19@@QAEXPBUCoord3D@@@Z
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 003FDA19..003FDA90, 119B, RET4. The primary position worker
// updates render transforms. When slot +1C exists, the input plus the
// measured vector +AC is forwarded to the established particle-position
// worker. The volatile pointer view preserves the independently observed
// two reads of +1C; its original source qualifier is unknown. The nontrivial
// sum value models native temporary construction, not a named retail type.
// Original receiver and field names remain unknown.
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
	Rva001F3899Slot *volatile slot;
	char unknown20[0xAC - 0x20];
	Coord3D offset;
};

struct Rva003FDA19Sum
{
    float x, y, z;
    Rva003FDA19Sum(float a, float b, float c) : x(a), y(b), z(c) {}
    Rva003FDA19Sum(const Rva003FDA19Sum &other)
    { x = other.x; y = other.y; z = other.z; }
};
static __forceinline Rva003FDA19Sum SumPosition003FDA19(const Coord3D *translation, Rva003FDA19Sum input)
{
    return Rva003FDA19Sum(translation->x + input.x,
                         translation->y + input.y,
                         translation->z + input.z);
}

static __forceinline Rva001F3899Slot *ResolveParticle003FDA19(Rva001F3899Slot *target)
{
    if (target == 0)
        return reinterpret_cast<Rva001F3899Slot *>(Make001FCBD7());
    return target;
}

void Rva003FDA19::rva003FDA19(const Coord3D *position)
{
	reinterpret_cast<Rva003FB6C5 *>(this)->rva003FB6C5(position);
	if (slot) {
		Rva003FDA19Sum point = SumPosition003FDA19(&offset, Rva003FDA19Sum(position->x, position->y, position->z));
		Rva001F3899Slot *target = slot;
		ResolveParticle003FDA19(target)->set(
			*reinterpret_cast<const Rva001F3899Arg *>(&point));
	}
}
