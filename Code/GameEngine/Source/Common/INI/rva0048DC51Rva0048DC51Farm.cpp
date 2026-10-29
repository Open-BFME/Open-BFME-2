// ?rva0048DC51@FloodUpdate@@QAEXPBUFloodMember@@PAVRva0048E16C@@@Z
// ?rva0048DC51@FloodUpdate@@QAEXPBUFloodMember@@PAVRva0048E16C@@@Z
// ?rva0048DC51@FloodUpdate@@QAEXPBUFloodMember@@PAVRva0048E16C@@@Z
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
//
// FloodUpdate (BFME 2): member creation, path building and the update.
//
// Target facts. FloodUpdate's primary vftable is 0x00C4C948 (installed by the
// rowed ctor 0x0048E09F); its UpdateModuleInterface vftable at 0x00C4C93C
// holds update 0x0048E32E in slot 0. The object keeps a list of 0x14-byte
// records at +0x20 (record ctor row 0x0048E16C: ObjectID +0, coord vector
// +4, path index +0x10; the rowed xfer 0x0048E4E2 transfers the same three)
// and a members-created flag at +0x24. The module data (table 0x00C4C9A8)
// holds the member list at +8, AngleOfFlow +0xC and DirectionIsRelative
// +0x10; each member (parser 0x0048E022, table 0x00C4C850) holds
// MemberTemplateName +0, ControlPointOffsetOne..Four (Coord3D) at
// +4/+0x10/+0x1C/+0x28 and MemberSpeed +0x34.
//
// The control points are an array of BFME 2's Coord3D, whose empty ctor and
// dtor fold to the rowed 0x0047A6A9 / 0x000B3FD0 and drive the eh vector
// iterators; the Bezier segment is the rowed Rva0055A246 view (copy ctor
// 0x0055A3C5, length 0x0055A627, tessellation 0x0055A7DB).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <string.h>
// The float overloads of <math.h> inline here; dllimport keeps them from
// emitting out-of-line copies that differ from retail's fsin/fcos ones
// (0x2FBB0/0x2FBC0). Same wrap as wwmath.cpp.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")
#include <list>
#include <vector>
#include "ascii_string.h"
// The segment count's max(2, count) is inlined; a file-static int overload
// takes the call so this TU emits no external max<int> COMDAT.
namespace _STL {
static inline const int &max(const int &a, const int &b)
{
    return a < b ? b : a;
}
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData;
class Team;
class ThingTemplate;

// BFME 2's Coord3D with the empty ctor/dtor (rowed folds 0x0047A6A9 / 0x000B3FD0) that the
// control-point array's eh vector iterators take.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline float Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	float X;
	float Y;
	float Z;
};

class Matrix3D
{
public:
	Matrix3D();
	void buildTransformMatrix(const Vector3 &pos, const Vector3 &dir);
private:
	float m_row[3][4];
};

// Bezier segment over four control points (see Rva0055A246Ctor.cpp).
class Rva0055A246
{
public:
	Rva0055A246(const Rva0055A246 &other);
	float rva0055A627(float tolerance) const;
	void rva0055A7DB(int numSegments, void *points);
	Coord3D m_arr[4];
};

Real normalizeAngle(Real angle);

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../GameLogicObjectLookupView.h"

enum DamageType
{
	DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

struct CreateMask
{
	unsigned int m_bits[4];
};

#include "../Thing/thing.h"

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	Team *getTeam() const { return m_team; }
	void kill(DamageType damageType, DeathType deathType);
	Real GetRelativeAngle(const Coord3D *pos) const;
	void setTransformMatrix(const Matrix3D *mtx);
private:
	char m_unknown48[0x74 - 0x48];
	ObjectID m_id; // +0x74
	char m_unknown78[0x304 - 0x78];
	Team *m_team; // +0x304
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02();
	virtual void t03(); virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

extern TerrainLogic *TheTerrainLogic;

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b);
};

extern ThingFactory *TheThingFactory;

struct FloodMember
{
	AsciiString m_templateName; // +0
	Coord3D m_controlPointOffset[4]; // +4
	Real m_speed; // +0x34
};

class FloodUpdateModuleData
{
public:
	char m_unknown00[8];
	_STL::list<FloodMember *> m_members; // +8
	Real m_angleOfFlow; // +0xC
	Bool m_directionIsRelative; // +0x10
};

// One flood member in flight: its object, the tessellated path and the
// index of the path point it stands on.
class Rva0048E16C
{
public:
	Rva0048E16C() throw();

	ObjectID m_id; // +0
	_STL::vector<Coord3D> m_path; // +4
	Int m_index; // +0x10
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class FloodUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva0048DC51(const FloodMember *member, Rva0048E16C *record);
	void rva0048E189();

protected:
	const FloodUpdateModuleData *getFloodUpdateModuleData() const
	{
		return (const FloodUpdateModuleData *)m_moduleData;
	}

private:
	_STL::list<Rva0048E16C *> m_records; // +0x20
	Bool m_membersCreated; // +0x24
};

// A control-point offset rotated by angle about the origin, then moved to
// pos on the ground plane.
__forceinline void placeControlPoint(Coord3D &out, const Coord3D &offset, Real angle, const Coord3D &pos)
{
	Real y = offset.y;
	Coord3D pt;
	pt.x = offset.x;
	Real s = (Real)sin((double)angle);
	Real c = (Real)cos(angle);
	Real x = pt.x;
	Real rx = c * x;
	rx = rx - s * y;
	pt.x = rx + pos.x;
	pt.y = x * s + c * y + pos.y;
	pt.z = 0.0f;
	out = pt;
}

// ?rva0048DC51@FloodUpdate@@QAEXPBUFloodMember@@PAVRva0048E16C@@@Z @0x0048DC51 809B
// Builds a member's path: its four control-point offsets rotated by the flow
// angle (relative to the object's orientation when DirectionIsRelative) and
// moved to the object's position on the ground plane, a Bezier segment
// through them, tessellated into at least two points spaced MemberSpeed apart.
void FloodUpdate::rva0048DC51(const FloodMember *member, Rva0048E16C *record)
{
	const FloodUpdateModuleData *data = getFloodUpdateModuleData();
	Real angle = data->m_angleOfFlow;
	if (data->m_directionIsRelative)
	{
		angle = (1 ? normalizeAngle(getObject()->getOrientation() + angle) : normalizeAngle(0.0f));
		_ReadWriteBarrier();
		_ReadWriteBarrier();
	}

	Coord3D points[4];
	Coord3D pos = *getObject()->getPosition();
	placeControlPoint(points[0], member->m_controlPointOffset[0], angle, pos);
	placeControlPoint(points[1], member->m_controlPointOffset[1], angle, pos);
	placeControlPoint(points[2], member->m_controlPointOffset[2], angle, pos);
	placeControlPoint(points[3], member->m_controlPointOffset[3], angle, pos);
	_ReadWriteBarrier();

	Rva0055A246 segment(*(const Rva0055A246 *)points);
	Real speed = member->m_speed;
	Int count = (Int)ceil(segment.rva0055A627(1.0f) / speed);
	Int segments = _STL::max(2, count);
	segment.rva0055A7DB(segments, &record->m_path);
}

// rva0048E189 (0x0048E189) and update (0x0048E32E) are rowed in
// GameLogic/Object/Update/FloodUpdate.cpp; this unit only declares them.
