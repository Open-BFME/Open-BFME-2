// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// Identity: ModuleFactory registers this behavior class under "FloodUpdate"
// (addModule pairs the name with the instance factory at 0x24D142, the sole
// raw caller of this ctor); poolkey rowed at 0x48E0FA, ModuleData proc rowed
// at 0x48E15B, ModuleData factory rowed at 0x24D17A, ModuleData ctor rowed at
// 0x48DF7A.
// stlport
//
// ??0FloodUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048E09F,
// 85 bytes. UpdateModule is 0x20 (BehaviorModule pair plus
// UpdateModuleInterface plus three ints, per UpdateModuleCtor.cpp); the
// derived re-installs its three vtables at +0/+0xC/+0x10, builds an empty
// list at +0x20 through the rowed int-spelled List_base 0x4EC36C (1-byte
// stack allocator temp idiom) and clears its flag byte at +0x24. Zero new
// pins (all callees rowed). List element type is unproven (int matches the
// rowed List_base spelling; AsciiString/UnicodeString twins fold identically).

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

class Thing;
class ModuleData;
class Object;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class Xfer;

class FloodUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	FloodUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FloodUpdate();
private:
	_STL::list<int> m_records; // +0x20
	bool m_membersCreated; // +0x24
};

// ??0FloodUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048E09F
FloodUpdate::FloodUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_membersCreated = false;
}
