// cl: /O1 /DNDEBUG /MD /Oy- /arch:SSE
// Native 45EA66..45EB02 RET 4; WorldBuilder ShipSlowDeathBehavior.cpp
// lines 64 and 70 and the secondary SlowDeathBehaviorInterface slot prove
// beginSlowDeath. The interface receiver is complete-object +24: native
// module data at receiver-20 and the three angles at receiver+2C/+30/+34.
// The old no-boundary verdict confused instruction addresses; the native
// body starts with 55 8B EC and ends with 5F 5E 5D C2 04 00.
class DamageInfo;
struct ModuleData
{
    char pad[0x4C];
    unsigned int sinkDuration;
};
class ObjectModule
{
public:
    virtual ~ObjectModule();
protected:
    const ModuleData *m_moduleData;
    void *m_object;
};
class BehaviorModuleInterface
{
public:
    virtual void slot0();
};
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface {};
class UpdateModuleInterface
{
public:
    virtual int update() = 0;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
    char pad14[0xC];
};
class DieModuleInterface
{
public:
    virtual void onDie(const DamageInfo *) = 0;
};
class SlowDeathBehaviorInterface
{
public:
    virtual void beginSlowDeath(const DamageInfo *) = 0;
};
class SlowDeathBehavior : public UpdateModule, public DieModuleInterface,
                          public SlowDeathBehaviorInterface
{
public:
    virtual void beginSlowDeath(const DamageInfo *);
private:
    char pad28[0x28];
};
class ShipSlowDeathBehavior : public SlowDeathBehavior
{
public:
    virtual void beginSlowDeath(const DamageInfo *);
private:
    float m_pitchRate;
    float m_rollRate;
    float m_rotation;
};
int GetGameLogicRandomValue(int, int, char *, int);

void ShipSlowDeathBehavior::beginSlowDeath(const DamageInfo *damage)
{
    SlowDeathBehavior::beginSlowDeath(damage);
    float duration = (float)m_moduleData->sinkDuration;
    m_pitchRate = 3.1415927f / duration / 2.0f;
    m_rollRate = 3.1415927f / duration / 2.0f;
    m_rotation = 0.0f;
    char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\ShipSlowDeathBehavior.cpp";
    if (GetGameLogicRandomValue(0, 1, source, 64) == 1)
        m_pitchRate = -m_pitchRate;
    if (GetGameLogicRandomValue(0, 1, source, 70) == 1)
        m_rollRate = -m_rollRate;
}
