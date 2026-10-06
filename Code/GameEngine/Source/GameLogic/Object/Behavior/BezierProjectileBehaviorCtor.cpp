// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0045C850, 265 bytes. Donor: BFME 1's matched
// BezierProjectileBehaviorConstructor.cpp (BFME 1 retail 0x001F1470); member
// names below are carried from it. Target evidence: the body runs the rowed
// UpdateModule ctor 0x00253390, the implicit ctors of the two abstract
// interfaces at +0x20/+0x24 (both vtable 0x00840818), then stores the five
// vtables the rowed dtor 0x0045BF6E restores (0x00841E04 primary, whose
// slot 0 is the rowed ??_GBezierProjectileBehavior 0x0045C959 and slot 3
// the rowed xfer 0x0045CA8E). As in BFME 1 the +0x44 Coord3D vector is
// built and cleared (STLport's out-of-line vector<Coord3D> base ctor and
// erase, both pinned: ICF-folded 0x00211E58 and 0x002A133B),
// the +0x7C list is built through the rowed list-base ctor 0x0029FB3B with
// a stack allocator, the remaining members are zeroed, +0x84 is 1.0 and
// the module sleeps forever. Offsets agree with the rowed xfer.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <vector>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

class Thing;
class ModuleData;
class Object;
class WeaponTemplate;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

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

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

// The two abstract interfaces at +0x20 and +0x24.
class BezierProjectileInterface0
{
public:
	virtual void slot00() = 0;
};

class BezierProjectileInterface1
{
public:
	virtual void slot00() = 0;
};

class PoolMember
{
public:
	void Rva00268902() throw();
};

struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
	~Rva0029FB3BAlloc() {}
};

// The ID list's base; its allocator-taking ctor is rowed at 0x0029FB3B.
class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc);
	~Rva0029FB3BMember() { ((PoolMember *)this)->Rva00268902(); }
private:
	void *m_node;
};

class ObjectIDList : public Rva0029FB3BMember
{
public:
	explicit ObjectIDList(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc()) : Rva0029FB3BMember(alloc) {}
};

class BezierProjectileBehavior : public UpdateModule, public BezierProjectileInterface0, public BezierProjectileInterface1
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~BezierProjectileBehavior();
	virtual void slot00();
private:
	ObjectID m_launcherID; // +0x28
	Coord3D m_at2C; // +0x2C
	ObjectID m_victimID; // +0x38
	const WeaponTemplate *m_at3C; // +0x3C
	const WeaponTemplate *m_at40; // +0x40
	_STL::vector<Coord3D> m_flightPath; // +0x44
	Coord3D m_flightPathStart; // +0x50
	Coord3D m_flightPathEnd; // +0x5C
	Real m_flightPathSpeed; // +0x68
	Int m_flightPathSegments; // +0x6C
	Int m_currentFlightPathStep; // +0x70
	UnsignedInt m_extraBonusFlags; // +0x74
	Int m_altCurve; // +0x78
	ObjectIDList m_at7C; // +0x7C
	Bool m_hasDetonated; // +0x80
	Real m_heightScale; // +0x84
};

BezierProjectileBehavior::BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_launcherID = 0;
	zeroCoord(m_at2C);
	m_victimID = 0;
	m_at3C = 0;
	m_at40 = 0;
	m_flightPath.clear();
	m_flightPathSegments = 0;
	m_flightPathSpeed = 0;
	zeroCoord(m_flightPathStart);
	zeroCoord(m_flightPathEnd);
	m_currentFlightPathStep = 0;
	m_extraBonusFlags = 0;
	m_hasDetonated = false;
	m_altCurve = 0;
	m_heightScale = 1.0f;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
