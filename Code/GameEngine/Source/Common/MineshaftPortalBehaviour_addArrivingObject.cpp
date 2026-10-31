// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// MineshaftPortalBehaviour::addArrivingObject (WorldBuilder name, MineshaftPortalBehaviour.cpp line 164: push_back onto the arriving list).
// stlport
//
// was ?rva003734A4@Rva003734A4@@QAEXPAX@Z @0x003734A4 (28B).
// Vector push_back of ScienceType field at +0x74 of arg into vector at +0x28
// via rowed push_back 0x002E01C6. EBP frame from /O1. Between 0x0037341F and
// 0x003734C0. Flags from Rva00373357 neighbour.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

enum ScienceType
{
	SCIENCE_Dummy0
};

// Retail's push_back overflow path (0x00148D00) calls the shared four-byte
// allocate at 0x00068E15; this unit's malloc-wired copy differed from it.
namespace _STL {
template <> ScienceType *allocator<ScienceType>::allocate(size_t, const void *) const;
}

enum NameKeyType
{
	NK_UNKNOWN = 0
};
#include "GameLogicObjectLookupView.h"
class Thing;
class ModuleData;
class BehaviorModuleBase
{
private:
	virtual void unused();
public:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
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
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
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
	virtual UpdateSleepTime update();
 virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};
class MineshaftPortalInterfaceA
{
public:
	virtual void ifaceA() = 0;
};
class MineshaftPortalInterfaceB
{
public:
	virtual void ifaceB() = 0;
};
struct Coord3D;
class Waypoint;
class MineshaftPortalBehaviour : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void DoXfer(Xfer *xfer);
	void addArrivingObject(void *p);
	Waypoint *rva00372DFA(const Coord3D *pos);
	void createWaypoint();

private:
	_STL::vector<ObjectID> m_pending; // +0x28
	Waypoint *m_waypoint; // +0x34
	bool m_registered; // +0x38
	bool m_mode39; // +0x39
};

void MineshaftPortalBehaviour::addArrivingObject(void *p)
{
	ScienceType tmp = *(ScienceType *)((char *)p + 0x74);
	((_STL::vector<ScienceType> *)&m_pending)->push_back(tmp);
}
