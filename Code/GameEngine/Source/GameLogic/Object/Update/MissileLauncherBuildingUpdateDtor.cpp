// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??_GMissileLauncherBuildingUpdate@@UAEPAXI@Z at retail 0x004CDA19 (28B).
// Emitted scalar deleting destructor (flag plus pinned operator delete at
// 0x0002FD60), and ??1MissileLauncherBuildingUpdate@@UAE@XZ at 0x004CD9C0
// (89B): compiler vptr restores, implicit destruction of the trailing
// vector (null-checked 0x30830 free), then the base call. The vector is a
// real member so the implicit destruction and SEH states fall out.
#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// Storage deallocation cannot throw; keep the STLport cleanup inline.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline _Vector_base<BfmeE16, allocator<BfmeE16> >::~_Vector_base()
{ if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); }
template <> __declspec(dllimport) __forceinline vector<BfmeE16, allocator<BfmeE16> >::~vector()
{ _Destroy(this->_M_start, this->_M_finish); }
}

class Thing;
class ModuleData;

class Object;

// Four-vptr module hierarchy (+0 +0x0C +0x10 +0x20), as in the matched
// GiveOrRestoreUpgradeSpecialPowerDtor.cpp; the dtor's vptr restores are
// compiler-generated, which puts them ahead of the EH state store.
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
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

// Opaque UpdateModule-derived intermediate.
class Rva0044EF5E : public BehaviorModule, public UpdateModuleInterface
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class SpecialPowerTemplate;
class Waypoint;
struct Coord3D;

class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);
};

// The dtor tail-calls the rowed ??1SpecialAbilityUpdate (0x00451F45), and
// retail's +0x10 and +0x20 tables (0x0084DEE8, 0x008552A4) keep
// SpecialAbilityUpdate::update (0x00451FA2) and
// SpecialAbilityUpdate::initiateIntentToDoSpecialPower (0x004500A3) in slot 0.
class SpecialAbilityUpdate : public Rva0044EF5E, public SpecialPowerUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();
	virtual void triggerAbilityEffect();	// slot 17 (0x0045108D)
	virtual UpdateSleepTime update();
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);
};

class MissileLauncherBuildingUpdate : public SpecialAbilityUpdate
{
public:
	virtual ~MissileLauncherBuildingUpdate();

private:
	unsigned char m_pad24[0x88 - 0x24];
	_STL::vector<BfmeE16> m_tail;		// +0x88
};

MissileLauncherBuildingUpdate::~MissileLauncherBuildingUpdate()
{
}
