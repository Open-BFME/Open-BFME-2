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
class UpdateModule : public DRU_DeepBase, public DRU_Iface1, public DRU_Iface2
{
public:
    // Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
    // ctors call it, and a copy here would offer the link a second, non-retail body.
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    // Declared only: retail's ~UpdateModule (0x0024A797, pin) restores the three vtables and
    // tail-jumps on; the implicit one here compiled to a 5-byte jmp the link could keep.
    virtual ~UpdateModule();

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DetachableRiderUpdate : public UpdateModule
{
public:
    DetachableRiderUpdate(Thing *, const ModuleData *);
    void rva004AE8FA();

private:
    bool m_flag20;
    bool m_flag21;
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
