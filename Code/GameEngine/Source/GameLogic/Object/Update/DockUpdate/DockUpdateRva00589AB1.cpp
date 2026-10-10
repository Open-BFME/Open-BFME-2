// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/sweep
// stlport
// ?onApproachReached@DockUpdate@@UAEXPAVObject@@@Z @0x00589AB1 78B.
// Zero Hour DockUpdate::onApproachReached: finds the docker's ID (Object
// +0x74) among the approach-position owners and sets that index's bit in the
// approach-reached vector<bool>. DockUpdateInterface slot 8 of the docks'
// +0x20 interface vtables 0x00C51AC0 0x00C51C30 0x00C53740 (0x00C51D18 holds
// MonsterDockUpdate's override 0x004A159E), so `this` is the +0x20 subobject: owners at DockUpdate +0x60 (interface +0x40),
// reached bits at +0x6C (interface +0x4C). MonsterDockUpdate::onApproachReached
// 0x004A159E calls it first, as Zero Hour's overrides call the base.
// Evidence: offsets +0x40 +0x44 size sar2 plus vector bool call rowed 0x0006BE1F in DockUpdateCtor plus caller 0x004A159E passing object plus neighbour DockUpdateRemove layout.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
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

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	virtual void loadPostProcess();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
struct Coord3D;
class DockUpdateInterface
{
public:
	virtual bool isClearToApproach(const Object *docker) const = 0;
	virtual bool reserveApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool advanceApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool isClearToEnter(const Object *docker) const = 0;
	virtual bool isClearToAdvance(const Object *docker, int dockerIndex) const = 0;
	virtual void getEnterPosition(Object *docker, Coord3D *position) = 0;
	virtual void getDockPosition(Object *docker, Coord3D *position) = 0;
	virtual void getExitPosition(Object *docker, Coord3D *position) = 0;
	virtual void onApproachReached(Object *docker) = 0;
};
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	virtual void onApproachReached(Object *docker);
protected:
	unsigned char m_pad24[0x60 - 0x24];
	ObjectIDVector m_approachPositionOwners; // +0x60
	BoolVector m_approachPositionReached; // +0x6C
};

void DockUpdate::onApproachReached(Object *docker)
{
	int target = docker->getID();
	for (unsigned int i = 0; i < m_approachPositionOwners.size(); ++i)
	{
		if (m_approachPositionOwners[i] == target)
		{
			m_approachPositionReached[i] = true;
			break;
		}
	}
}
