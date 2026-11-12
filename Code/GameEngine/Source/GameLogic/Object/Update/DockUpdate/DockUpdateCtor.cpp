// cl: /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /arch:SSE /Ireference/shims/sweep
// platformsdk
// stlport
//
// DockUpdate base constructor (retail 0x0058A290, 384 bytes) plus the STL
// instantiation bodies it calls. Ported from the Open-BFME-1 DockUpdate.cpp
// donor (same class, same member order, same resize-if/else-zero loop); BFME 2
// carries the extra UpdateModule dword the dockupdate shim proves, which keeps
// DockUpdateInterface at +0x20 exactly as here.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <limits.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define NOMINMAX
#include <windows.h>

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_INLINE
#include "../../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<bool,allocator<bool> >::~vector(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<ObjectID,allocator<ObjectID> >::~_Vector_base(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<Coord3D,allocator<Coord3D> >::~_Vector_base(); }
// bfme link decl-only begin
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iterator, unsigned int, bool); }
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *, unsigned int) const; }
namespace _STL { template <> void allocator<ObjectID>::deallocate(ObjectID *, unsigned int) const; }
namespace _STL { template <> void _Bvector_base<allocator<bool> >::_M_deallocate(); }
namespace _STL { template <> _Bvector_base<allocator<bool> >::~_Bvector_base(); }
// bfme link decl-only end
// Retail keeps the 16-byte /O2 copy of the default _Bit_iter constructor
// (0x00672310, stlport_vector_bool.cpp); this /O1 unit inlines every use, so
// it must not emit its own 10-byte copy.
namespace _STL { template <> __declspec(dllimport) __forceinline _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter() {} }

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
	// Both dtors bind to retail's inlined 14-byte copy (0x0007FAB3).
	~vector();

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
	~vector();

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
class BehaviorModuleOther
{
	virtual void unused();
};

#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"

// Native secondary table 0x00851D68: DockUpdate::update, followed by
// UpdateModule's disabled-mask getter and wake-delay slot.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
template<int NumBits> class BitFlags;

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"


class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
	// Retail table 0x00C52EE8: 19 __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
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
	virtual ~DockUpdate();
	virtual UpdateSleepTime update();

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor() = 0;
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
inline __declspec(noinline) void _Construct<Coord3D, Coord3D>(Coord3D *destination, const Coord3D &value)
{
	if (destination != NULL)
	{
		destination->x = value.x;
		destination->y = value.y;
		destination->z = value.z;
	}
}
_STLP_END_NAMESPACE

// ?ObjectIDVector::resize present-unmatched
void ObjectIDVector::resize(unsigned int newSize, ObjectID value)
{
	if (newSize < size())
		erase(_M_start + newSize, _M_finish);
	else
		insert(_M_finish, newSize - size(), value);
}

// ?ObjectIDVector::erase present-unmatched
inline ObjectID *ObjectIDVector::erase(ObjectID *first, ObjectID *last)
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
		m_approachPositions.resize(DEFAULT_APPROACH_VECTOR_SIZE, Coord3D());
		m_approachPositionOwners.resize(DEFAULT_APPROACH_VECTOR_SIZE, INVALID_ID);
		m_approachPositionReached.resize(DEFAULT_APPROACH_VECTOR_SIZE, FALSE);
	}

	for (UnsignedInt vectorIndex = 0;
		vectorIndex < m_approachPositions.size(); ++vectorIndex)
	{
		m_approachPositions[vectorIndex].zero();
		m_approachPositionOwners[vectorIndex] = INVALID_ID;
		m_approachPositionReached[vectorIndex] = FALSE;
	}
}

#pragma inline_depth(0)
// ?bfmeEmitDockUpdateCtor@@YAXPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitDockUpdateCtor(ObjectIDVector *objectIDVector)
{
	objectIDVector->erase((ObjectID *)0, (ObjectID *)0);
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0SupplyCenterDockUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z=??0DockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// _M_fill_insert binds to the kept retail copy (declared above), so its two
// rowed callees are no longer pulled in by it; emit them explicitly.
namespace _STL {
template _Bit_iterator __copy_backward(_Bit_iterator, _Bit_iterator, _Bit_iterator,
	const random_access_iterator_tag &, int *);
}

// ?bfmeAnchorDockBitIterNe absent-from-retail
void *bfmeAnchorDockBitIterNe()
{
	bool (*ne)(const _STL::_Bit_iterator_base &, const _STL::_Bit_iterator_base &) = &_STL::operator!=;
	return (void *)ne;
}
