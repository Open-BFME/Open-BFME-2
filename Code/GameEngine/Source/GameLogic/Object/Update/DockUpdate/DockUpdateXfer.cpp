// cl: /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /arch:SSE /Ireference/shims/sweep
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
#include <limits.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	Coord3D() {}
	Coord3D(const Coord3D &);
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

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
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
	virtual void update();
};

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
	*xfer == m_enterPosition;
	*xfer == m_dockPosition;
	*xfer == m_exitPosition;
	*xfer == m_numberApproachPositions;
	*xfer == m_positionsLoaded;
	Int vectorSize = (Int)m_approachPositions.size();
	*xfer == vectorSize;
	m_approachPositions.resize(vectorSize);
	for (Int vectorIndex = 0; vectorIndex < vectorSize; ++vectorIndex)
		*xfer == m_approachPositions[vectorIndex];
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
