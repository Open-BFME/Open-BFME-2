// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor body through ILT 0x0004773F. The
// registration string and 0x24-byte allocation independently identify the
// retail-only DetachableRiderUpdate class.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };

class DRU_DeepBase
{
public:
    DRU_DeepBase(Thing *, const ModuleData *);
    virtual ~DRU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DRU_Iface1 { public: virtual void slot(); };
class DRU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class DetachableRiderUpdate : public UpdateModule
{
public:
    DetachableRiderUpdate(Thing *, const ModuleData *);
    void rva004AE8FA();

private:
    bool m_flag20;
    bool m_flag21;
public:
	// retail slot 4: the rowed ?getModuleNameKey@DetachableRiderUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual const char *GetSnapshotName() const;
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

// ??0DetachableRiderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DetachableRiderUpdate::DetachableRiderUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_flag20(false), m_flag21(false)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

// ?rva004AE8FA@DetachableRiderUpdate@@QAEXXZ @0x004AE8FA 15B: clear +0x20 then
// wake (none) via rowed UpdateModule::setWakeFrame 0x0044DF71; caller
// ReplenishUnitsBehavior::rva004842DD casts to DetachableRiderUpdate and calls it.
void DetachableRiderUpdate::rva004AE8FA()
{
    m_flag20 = false;
    setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
