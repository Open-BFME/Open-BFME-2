// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/sweep
// stlport
// ?update@DockUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00589F09 258B. DockUpdate::update via rowed vector bool operator[] 0x0006BE1F plus findObjectByID 0x00049DC5 plus overlap 0x00263546 plus bitset 0x0028F59A plus clear 0x001E42F2. Donor open-bfme-1 DockUpdateUpdateBfme.cpp plus ZH DockUpdate.cpp. Caller 0x004A111E.
#include <stl/_bvector.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include <stl/_bvector.h>

namespace _STL
{
template <>
class vector<ObjectID, allocator<ObjectID> > : public _Vector_base<ObjectID, allocator<ObjectID> >
{
public:
	__forceinline vector() : _Vector_base<ObjectID, allocator<ObjectID> >(allocator<ObjectID>()) {}
	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	ObjectID &operator[](unsigned int index)
	{
		return _M_start[index];
	}
};
}

typedef _STL::vector<ObjectID, _STL::allocator<ObjectID> > ObjectIDVector;
typedef _STL::vector<bool, _STL::allocator<bool> > BoolVector;

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	unsigned int m_kind0;
	unsigned char m_pad2[6];
	unsigned char m_supply;
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};

class Object
{
public:
	void *m_vft;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x10c - 8];
	Rva00263546 m_flags;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct Rva0028F59A
{
	Rva0028F59A(int unused, int bit);
	unsigned m_bits[19];
};

struct Rva001E42F2
{
	void rva001E42F2(const int *x);
};

class Thing;
class ModuleData;

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
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual UpdateSleepTime update();
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

struct Coord3D
{
	Coord3D() {}
	float x, y, z;
};

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	virtual UpdateSleepTime update();
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
	Object *getObject() const
	{
		return *(Object *const *)((const char *)this + 8);
	}
};

UpdateSleepTime DockUpdate::update()
{
	ObjectID positionIndex = m_activeDocker;
	if (positionIndex == INVALID_ID && !m_dockCrippled)
	{
		for (UnsignedInt i = 0; i < m_approachPositionReached.size(); ++i)
		{
			if (m_approachPositionReached[i])
			{
				m_activeDocker = m_approachPositionOwners[i];
				return UPDATE_SLEEP_NONE;
			}
		}
	}
	else
	{
		Object *object = getObject();
		if ((object->m_template->m_supply & 0x40) != 0)
		{
			Object *docker = TheGameLogic->findObjectByID(positionIndex);
			if (docker != 0 && (docker->m_template->m_kind0 & 0x4000) != 0 && (docker->m_template->m_kind0 & 0x10000) != 0)
			{
				Rva00263546 test;
				ji_006291ae(&test, 0, 0x4c);
				((unsigned char *)&test)[10] |= 4;
				if (test.rva00263546(&docker->m_flags))
				{
					((Rva001E42F2 *)docker)->rva001E42F2((const int *)&Rva0028F59A(0, 0x3d));
				}
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}
