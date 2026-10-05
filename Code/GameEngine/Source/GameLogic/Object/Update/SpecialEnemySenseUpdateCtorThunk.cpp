// cl: /O1 /DNDEBUG /MD /EHsc
// The named ModuleFactory entry reaches this constructor through its unique
// 0x20-byte allocation, leaving no derived state beyond UpdateModule.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class SESU_DeepBase
{
public:
    SESU_DeepBase(Thing *, const ModuleData *);
    virtual ~SESU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class SESU_Iface1 { public: virtual void slot(); };
class SESU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public SESU_DeepBase, public SESU_Iface1, public SESU_Iface2
{
public:
    // Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
    // ctors call it, and a copy here would offer the link a second, non-retail body.
    UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class SpecialEnemySenseUpdate : public UpdateModule
{
public:
    SpecialEnemySenseUpdate(Thing *, const ModuleData *);
};

// ??0SpecialEnemySenseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpecialEnemySenseUpdate::SpecialEnemySenseUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
