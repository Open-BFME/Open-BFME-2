// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva004626CA@OpenContain@@UAEPBUCoord3D@@XZ, retail 0x004626CA, 107 bytes.
// Slot 86 of OpenContain's +0x20 interface vftable 0x00C433B0, compiled on
// that subobject (the owner Thing at +0x08 is read at -0x18): the position
// the contain reports for its owner. An owner whose template has bit 0x80 at
// +0x11F set is snapped to the nearest land point (Pathfinder
// getClosestPointOnLand 0x002EE7EE on TheAI's pathfinder) kept in a function
// static; otherwise, or when no land point is found, the owner's own
// position (+0x38). The static's type has an empty destructor (its atexit
// thunk is a bare RET); /EHsc keeps the guarded initialization free of an
// unwind frame, as retail. Address name: class and slot proven, method identity
// not.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

class Pathfinder
{
public:
	bool getClosestPointOnLand(const Coord3D *pos, Object *obj, Coord3D *dest);
};

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

struct Rva004626CATemplateView
{
	unsigned char m_pad000[0x11F];
	unsigned char m_flags11F;	// +0x11F
};

struct Rva004626CAOwnerView
{
	void *m_vtable;
	Rva004626CATemplateView *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;			// +0x38
};

struct LandPoint : public Coord3D
{
	LandPoint() { x = 0.0f; y = 0.0f; z = 0.0f; }
	~LandPoint() {}
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class OpenContainPrimaryView
{
public:
	virtual void p0();
	const void *m_moduleData;		// +0x04
	Rva004626CAOwnerView *m_thing;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class ContainIface20
{
public:
	SLOT16(a) SLOT16(b) SLOT16(c) SLOT16(d) SLOT16(e)
	SLOT08(f0,f1,f2,f3,f4,f5,g0,g1)
	virtual const Coord3D *rva004626CA() = 0;	// slot 86
};

class OpenContain : public OpenContainPrimaryView, public ContainIface20
{
public:
	virtual const Coord3D *rva004626CA();
};

const Coord3D *OpenContain::rva004626CA()
{
	Rva004626CAOwnerView *owner = m_thing;
	if (owner->m_template->m_flags11F & 0x80)
	{
		static LandPoint s_landPoint;
		if (TheAI->pathfinder()->getClosestPointOnLand(&owner->m_position, (Object *)owner, &s_landPoint))
			return &s_landPoint;
	}
	return &owner->m_position;
}
