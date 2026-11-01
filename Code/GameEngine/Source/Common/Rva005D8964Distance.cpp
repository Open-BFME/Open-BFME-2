// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// Slot 7 and slot 8 of Rva005D8964 (plus slot 0x005D88AA of the sibling Rva005D8883 below) (vtable 0x008761C4; the ctor/dtor rows live in
// Rva005EE2A0Derived.cpp): two distance predicates over the AI victim of the
// object passed in.
//  - ?rva005D89F0@Rva005D8964@@UAE_NPAVObject@@@Z @0x005D89F0 115B: the victim
//    exists and is within 50 (squared 2500.0 at 0xC761BC) of the object.
//  - ?rva005D8A63@Rva005D8964@@UAE_NPAVObject@@@Z @0x005D8A63 111B: the same
//    test against 150 (squared 22500.0 at 0xC761C0) with the opposite sense.
// Retail keeps all six coordinates live in xmm0-5 before the three subtractions
// and has no frame. Both positions are read through retail's non-POD Coord3D
// (Lib/Coord3DCtorView.h, member-wise user copy constructor): the two by-value
// copies load every component into registers ahead of the arithmetic, where plain
// float reads fold into memory-operand subtractions.
// Evidence: native bytes (+0x258 AI interface, rowed getCurrentVictim 0x00268D71,
// positions at +0x38); names are address-derived, the class identity is unproven.
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Object;

class ThingTemplate
{
public:
	unsigned char m_pad[0x108];
	unsigned char m_flags108;
};

#include "../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
	const ThingTemplate *getTemplate() const { return *(const ThingTemplate *const *)((const char *)this + 4); }
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
};

class Rva005EE2A0
{
public:
	virtual ~Rva005EE2A0();
};

class Rva005D8964 : public Rva005EE2A0
{
public:
	virtual bool rva005D89F0(Object *other);
	virtual bool rva005D8A63(Object *other);
};

bool Rva005D8964::rva005D89F0(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		Coord3D a(*other->getPosition());
		Coord3D b(*victim->getPosition());
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		return dz * dz + dy * dy + dx * dx <= 2500.0f;
	}
	return false;
}

bool Rva005D8964::rva005D8A63(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		Coord3D a(*other->getPosition());
		Coord3D b(*victim->getPosition());
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		return dz * dz + dy * dy + dx * dx >= 22500.0f;
	}
	return false;
}

// Slot of the sibling class Rva005D8883 (vtable 0x00C76190): the same shape with
// the victim's template flag byte +0x108 bit 0x80 clearing the predicate and the
// 150 limit (squared 22500.0 at 0xC7618C) inclusive: ?Rva005D88AA@Rva005D8883@@UAE_NPAVObject@@@Z
// @0x005D88AA 127B.
class Rva005D8883 : public Rva005EE2A0
{
public:
	virtual bool Rva005D88AA(Object *other);
};

bool Rva005D8883::Rva005D88AA(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim && !(victim->getTemplate()->m_flags108 & 0x80)) {
		Coord3D a(*other->getPosition());
		Coord3D b(*victim->getPosition());
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		return dz * dz + dy * dy + dx * dx <= 22500.0f;
	}
	return false;
}
