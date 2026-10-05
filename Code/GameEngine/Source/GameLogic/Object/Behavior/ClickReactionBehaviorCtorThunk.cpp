// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1
};

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_f04;
    Object *m_object;
};

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    // Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
    // ctors call it, and a copy here would offer the link a second, non-retail body.
    UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class ClickReactionBehaviorIface
{
public:
    virtual void slot();
};

class ClickReactionBehavior : public UpdateModule,
    public ClickReactionBehaviorIface
{
public:
    ClickReactionBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_f24;
    unsigned int m_f28;
};

// ??0ClickReactionBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ClickReactionBehavior::ClickReactionBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_f24(0), m_f28(0)
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
