// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PropagandaTowerBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp

// The retail BFME UpdateModule prefix has three interface vptrs before the
// PropagandaTowerBehavior interface.  Keep that verified view local to this
// constructor; the shared ZH declaration has a different base layout.
class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// BitFlags<11> by value, as FireWeaponWhenDeadBehavior.cpp spells it: retail's DISABLEDMASK_ALL
// getter 0x004DF396 copies the mask with a memcpy call.
#pragma function(memcpy)
#include <string.h>
template <int NUM_BITS> class BitFlags
{
public:
    __forceinline BitFlags(const BitFlags &other) { memcpy(m_bits, other.m_bits, sizeof(m_bits)); }
private:
    unsigned int m_bits[(NUM_BITS + 31) / 32];
};
extern DisabledMaskType DISABLEDMASK_ALL;

class PropagandaTowerBehaviorIface
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h
class PropagandaTowerBehavior : public UpdateModule,
    public PropagandaTowerBehaviorIface
{
public:
    PropagandaTowerBehavior(Thing *, const ModuleData *);
    // Update-interface slot 1 (retail table 0x00C4917C): Zero Hour's inline override,
    // ICF-folded at 0x004DF396.
    virtual DisabledMaskType getDisabledTypesToProcess() const { return DISABLEDMASK_ALL; }

private:
    unsigned int m_lastScanFrame;
    void *m_insideList;
    const void *m_upgradeRequired;
public:
	// retail slot 4: the rowed ?getModuleNameKey@PropagandaTowerBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
public:
	// BehaviorModuleInterface table 0x00C49188 (+0x0C): the receiver converted to the
	// class's own interface, the null-preserving casts retail folds across the module family.
	virtual DieModuleInterface *getDie();			// slot 7: retail 0x004543A9, the +0x20 die interface
};

// ??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PropagandaTowerBehavior::PropagandaTowerBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      m_lastScanFrame(0),
      m_insideList(0),
      m_upgradeRequired(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot@PropagandaTowerBehaviorIface@@UAEXXZ=?rva00481837@Rva00481837@@UAEXH@Z")

// Slot 7 of PropagandaTowerBehavior's BehaviorModuleInterface table 0x00C49188: retail 0x004543A9, the +0x20 die interface.
DieModuleInterface *PropagandaTowerBehavior::getDie()
{
	return reinterpret_cast<DieModuleInterface *>(static_cast<PropagandaTowerBehaviorIface *>(this));
}
