// cl: /DNDEBUG /MD /GX
//
// ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00477F06,
// 278 bytes. Zero Hour's GarrisonContain::GarrisonContain (GeneralsMD
// GameLogic/Object/Contain/GarrisonContain.cpp). Target evidence: the body
// runs the rowed OpenContain ctor 0x004649F8 and stores the nine vtables the
// rowed dtor 0x00478067 restores (0x008461F8 primary, the table of the
// deleting dtor 0x0047860D and the GarrisonContain pool key 0x0047801C),
// then builds the 3x40 garrison point array at +0x424 through
// __ehvec_ctor with an empty out-of-line element ctor/dtor (ICF-folded
// 0x0047A6A9/0x000B3FD0; the +0x9D0 rally point is a plain Coord3D). As in
// ZH it clears the original team (an id at +0xFC in BFME 2, per the rowed
// xfer 0x00478844), the hide flag, the
// in-use count and the initialized flag, zeroes the 40 point records
// (+0x100, 0x14 each) and every condition's point, then clears the rally
// flag and point. BFME 2 drops ZH's station-point list and evacuation
// disposition and zeroes the 12-byte block at +0x9C4 the xfer skips.
#include <string.h>
#pragma intrinsic(memset)
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

#define FALSE false

class Thing;
class ModuleData;
class Object;

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The garrison point element: a Coord3D with an out-of-line empty ctor and
// dtor (retail's __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and
// 0x000B3FD0), unlike the plain Coord3D rally point.
struct Rva00477F06GarrisonPoint : public Coord3D
{
	Rva00477F06GarrisonPoint();
	~Rva00477F06GarrisonPoint();
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class UpdateModuleInterface
{
public:
	virtual void update();
private:
	unsigned char m_pad14[0x0C]; // +0x14
};

// OpenContain's six interfaces at +0x20..+0x34 (positional stand-ins).
class OpenContainInterface0 { public: virtual void i0(); };
class OpenContainInterface1 { public: virtual void i1(); };
class OpenContainInterface2 { public: virtual void i2(); };
class OpenContainInterface3 { public: virtual void i3(); };
class OpenContainInterface4 { public: virtual void i4(); };
class OpenContainInterface5 { public: virtual void i5(); private: unsigned char m_pad38[0xFC - 0x38]; };

class OpenContain : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface,
	public OpenContainInterface0, public OpenContainInterface1, public OpenContainInterface2,
	public OpenContainInterface3, public OpenContainInterface4, public OpenContainInterface5
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
};

class GarrisonContain : public OpenContain
{
public:
	GarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~GarrisonContain();
private:
	enum { MAX_GARRISON_POINTS = 40 };
	enum { MAX_GARRISON_POINT_CONDITIONS = 3 };

	struct GarrisonPointData
	{
		ObjectID object;
		ObjectID targetID;
		UnsignedInt placeFrame;
		UnsignedInt lastEffectFrame;
		Int effect;
	};

	UnsignedInt m_originalTeamID; // +0xFC
	GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
	Int m_garrisonPointsInUse; // +0x420
	Rva00477F06GarrisonPoint m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
	UnsignedInt m_unknown9C4[3]; // +0x9C4
	Coord3D m_exitRallyPoint; // +0x9D0
	Bool m_garrisonPointsInitialized; // +0x9DC
	Bool m_hideGarrisonedStateFromNonallies; // +0x9DD
	Bool m_rallyValid; // +0x9DE
};

GarrisonContain::GarrisonContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
{
	Int i, j;

	m_originalTeamID = 0;
	m_hideGarrisonedStateFromNonallies = FALSE;
	m_garrisonPointsInUse = 0;
	m_garrisonPointsInitialized = FALSE;

	for (i = 0; i < MAX_GARRISON_POINTS; i++)
	{
		m_garrisonPointData[i].object = 0;
		m_garrisonPointData[i].targetID = 0;
		m_garrisonPointData[i].placeFrame = 0;
		m_garrisonPointData[i].lastEffectFrame = 0;
		m_garrisonPointData[i].effect = 0;

		for (j = 0; j < MAX_GARRISON_POINT_CONDITIONS; ++j)
			zeroCoord(m_garrisonPoint[j][i]);
	}

	memset(m_unknown9C4, 0, sizeof(m_unknown9C4));

	m_rallyValid = FALSE;
	zeroCoord(m_exitRallyPoint);
}
