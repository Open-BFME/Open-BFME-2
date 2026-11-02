// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/sweep
// platformsdk
// stlport
//
// ?xfer@DockUpdate@@MAEXPAVXfer@@@Z, retail 0x0058A410, 439 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00870378 (class of rowed ctor
// ??0DockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x0058A290). Base
// UpdateModule xfer via rowed 0x44DF9F then IsLightCRC early-out via Xfer
// slot 0x10 then Version1 via rowed 0x53EE then 3 Coords at +0x24/+0x30/+0x3C
// via Xfer slot 0x60 plus int at +0x48 via Xfer slot 0x7C plus bool at +0x50
// via Xfer slot 0x90 plus Coord vector at +0x54 via rowed resize 0xCA33C plus
// ObjectID vector at +0x60 via rowed resize 0x5839A7 plus bool vector at +0x6C
// via rowed resize 0x6DB1C plus ObjectID at +0x80 via rowed XferObjectID
// 0x3060B2 plus bools at +0x84/+0x85/+0x86 via Xfer slot 0x90 last. Layout is
// the rowed 0x87-byte class from DockUpdateCtor.cpp (UpdateModule base 0x20
// plus DockUpdateInterface vptr at +0x20 giving +0x24 start). Donor is ZH
// DockUpdate::xfer (same member order skipping +0x4C bones) plus BFME2
// IsLightCRC and Version1 order. Recipe is QueueProductionExitUpdateXfer
// slot-3 pattern with vectors.
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


// Transfer coordinates through the canonical Coord3DBase view.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../Libraries/Include/Lib/Coord3DBase.h"


enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>
// bfme link decl-only begin
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iterator, unsigned int, bool); }
// bfme link decl-only end

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

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../../Include/Common/BfmeXfer.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"


class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DockUpdate();

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

protected:
	virtual void xfer(Xfer *xfer);

private:
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

void DockUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == asBase(m_enterPosition);
	*xfer == asBase(m_dockPosition);
	*xfer == asBase(m_exitPosition);
	*xfer == m_numberApproachPositions;
	*xfer == m_positionsLoaded;
	Int vectorSize = (Int)m_approachPositions.size();
	*xfer == vectorSize;
	m_approachPositions.resize(vectorSize);
	for (Int vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex)
		*xfer == asBase(m_approachPositions[vectorIndex]);
	vectorSize = (Int)m_approachPositionOwners.size();
	*xfer == vectorSize;
	m_approachPositionOwners.resize(vectorSize, INVALID_ID);
	for (vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex)
		XferObjectID(xfer, &m_approachPositionOwners[vectorIndex]);
	vectorSize = (Int)m_approachPositionReached.size();
	*xfer == vectorSize;
	m_approachPositionReached.resize(vectorSize, FALSE);
	for (vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex)
	{
		Bool unpack = m_approachPositionReached[vectorIndex];
		*xfer == unpack;
	}
	XferObjectID(xfer, &m_activeDocker);
	*xfer == m_dockerInside;
	*xfer == m_dockCrippled;
	*xfer == m_dockOpen;
}
