// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /arch:SSE /Ireference/shims/sweep
// stlport
//
// DockUpdate base constructor (retail 0x0058A290, 384 bytes) plus the STL
// instantiation bodies it calls. Ported from the Open-BFME-1 DockUpdate.cpp
// donor (same class, same member order, same resize-if/else-zero loop); BFME 2
// carries the extra UpdateModule dword the dockupdate shim proves, which keeps
// DockUpdateInterface at +0x20 exactly as here.
#include <limits.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct Coord3D
{
	// Retail Coord3D has an empty default ctor and a nontrivial copy ctor;
	// this keeps resize fill values in place.
	Coord3D() {}
	Coord3D(const Coord3D &);
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>

// BFME's resize overload passes its fill value by value. The vendored STLport
// headers use const references, so only these two element types are shadowed
// in this TU; vector<bool> stays on the witnessed bit-vector class.
namespace _STL
{
template <>
class vector<Coord3D, allocator<Coord3D> > : public _Vector_base<Coord3D, allocator<Coord3D> >
{
public:
	__forceinline vector() : _Vector_base<Coord3D, allocator<Coord3D> >(allocator<Coord3D>()) {}

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	Coord3D &operator[](unsigned int index)
	{
		return _M_start[index];
	}

	void insert(Coord3D *position, unsigned int count, const Coord3D &value)
	{
		_M_fill_insert(position, count, value);
	}

	void resize(unsigned int newSize, Coord3D value);
	void resize(unsigned int newSize);
	void _M_fill_insert(Coord3D *position, unsigned int count, const Coord3D &value);
	Coord3D *erase(Coord3D *first, Coord3D *last);

};

template <>
class vector<ObjectID, allocator<ObjectID> > : public _Vector_base<ObjectID, allocator<ObjectID> >
{
public:
	__forceinline vector() : _Vector_base<ObjectID, allocator<ObjectID> >(allocator<ObjectID>()) {}

	typedef _STL::__type_traits<ObjectID>::has_trivial_assignment_operator _TrivialAss;

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	ObjectID &operator[](unsigned int index)
	{
		return _M_start[index];
	}

	void insert(ObjectID *position, unsigned int count, const ObjectID &value)
	{
		_M_fill_insert(position, count, value);
	}

	void resize(unsigned int newSize, ObjectID value);
	void resize(unsigned int newSize);
	void _M_fill_insert(ObjectID *position, unsigned int count, const ObjectID &value);
	ObjectID *erase(ObjectID *first, ObjectID *last);

};
}

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;
typedef _STL::vector<ObjectID, _STL::allocator<ObjectID> > ObjectIDVector;
typedef _STL::vector<bool, _STL::allocator<bool> > BoolVector;

class Thing;
class ModuleData;

// Base-class model mirrors the rowed UpdateModuleCtor TU exactly: merged
// one-vptr BehaviorModule plus the UpdateModuleInterface vptr, then the two
// counters and the BFME-only reserved dword. Declarations only; the rowed
// 0x00253390 / 0x00253330 bodies stay the callees.
class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void update();
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

class DockUpdateModuleData
{
public:
	void *m_vftable;
	UnsignedInt m_moduleTagNameKey;
	Int m_numberApproachPositionsData;
	Bool m_isAllowPassthrough;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

	Coord3D m_enterPosition;
	Coord3D m_dockPosition;
	Coord3D m_exitPosition;
	Int m_numberApproachPositions;
	Int m_numberApproachPositionBones;
	Bool m_positionsLoaded;
	VecCoord3D m_approachPositions;
	ObjectIDVector m_approachPositionOwners;
	BoolVector m_approachPositionReached;
	ObjectID m_activeDocker;
	Bool m_dockerInside;
	Bool m_dockCrippled;
	Bool m_dockOpen;
};

enum
{
	DEFAULT_APPROACH_VECTOR_SIZE = 10,
	DYNAMIC_APPROACH_VECTOR_FLAG = -1
};

_STLP_BEGIN_NAMESPACE
template<>
__declspec(noinline) void _Construct<Coord3D, Coord3D>(Coord3D *destination, const Coord3D &value)
{
	if (destination != NULL)
	{
		destination->x = value.x;
		destination->y = value.y;
		destination->z = value.z;
	}
}
_STLP_END_NAMESPACE

void ObjectIDVector::resize(unsigned int newSize, ObjectID value)
{
	if (newSize < size())
		erase(_M_start + newSize, _M_finish);
	else
		insert(_M_finish, newSize - size(), value);
}

ObjectID *ObjectIDVector::erase(ObjectID *first, ObjectID *last)
{
	ObjectID *pos = _STL::__copy_ptrs(last, _M_finish, first, _TrivialAss());
	_M_finish = pos;
	return first;
}

// ??0DockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DockUpdate::DockUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_dockOpen = TRUE;
	m_positionsLoaded = FALSE;
	m_numberApproachPositionBones = -1;
	m_activeDocker = INVALID_ID;
	m_dockerInside = FALSE;
	m_dockCrippled = FALSE;

	const DockUpdateModuleData *md =
		(const DockUpdateModuleData *)moduleData;
	m_exitPosition.zero();
	m_dockPosition.zero();
	m_enterPosition.zero();

	m_numberApproachPositions = md->m_numberApproachPositionsData;
	if (m_numberApproachPositions != DYNAMIC_APPROACH_VECTOR_FLAG)
	{
		m_approachPositions.resize(m_numberApproachPositions);
		m_approachPositionOwners.resize(m_numberApproachPositions, INVALID_ID);
		m_approachPositionReached.resize(m_numberApproachPositions, FALSE);
	}
	else
	{
		m_approachPositions.resize(DEFAULT_APPROACH_VECTOR_SIZE);
		m_approachPositionOwners.resize(DEFAULT_APPROACH_VECTOR_SIZE, INVALID_ID);
		m_approachPositionReached.resize(DEFAULT_APPROACH_VECTOR_SIZE, FALSE);
	}

	for (Int vectorIndex = 0;
		vectorIndex < (Int)m_approachPositions.size(); ++vectorIndex)
	{
		m_approachPositions[vectorIndex].zero();
		m_approachPositionOwners[vectorIndex] = INVALID_ID;
		m_approachPositionReached[vectorIndex] = FALSE;
	}
}
