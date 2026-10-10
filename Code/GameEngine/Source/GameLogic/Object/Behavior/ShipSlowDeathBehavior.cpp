// cl: /D_CRTIMP= /O1 /G7 /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native 45EA66..45EB02 RET 4; WorldBuilder ShipSlowDeathBehavior.cpp
// lines 64 and 70 and the secondary SlowDeathBehaviorInterface slot prove
// beginSlowDeath. The interface receiver is complete-object +24: native
// module data at receiver-20 and the three angles at receiver+2C/+30/+34.
// The old no-boundary verdict confused instruction addresses; the native
// body starts with 55 8B EC and ends with 5F 5E 5D C2 04 00.
#include "matrix3d.h"
enum UpdateSleepTime { FOREVER=0x3fffffff };
class Thing {public:void setTransformMatrix(const Matrix3D*);const Matrix3D*getTransformMatrix()const{return(const Matrix3D*)((const char*)this+8);}};
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
    virtual UpdateSleepTime update() = 0;
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
    virtual UpdateSleepTime update();
private:
    char pad28[0x28];
};
class ShipSlowDeathBehavior : public SlowDeathBehavior
{
public:
    virtual void beginSlowDeath(const DamageInfo *);
    virtual UpdateSleepTime update();
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

// Native45EB02..45ED0E524B RET0; ctor45E9AA installsC423F0 at+10,
// whose slot0 is85EB02. The named module factory/pool key establishes Ship.
// Compiler applies the UpdateModuleInterface secondary receiver: owner at-8
// and primary50/54 angular rates at+40/+44. The existing MI class view is
// shared with beginSlowDeath, rather than adding a second flattened view.
// BFME1 pointer575ba2b04 WWMath Matrix3D supplies copy and In_Place_Pre_Rotate
// semantics. Native keeps translation while pre-rotating the three axes.
// Normal /O1 /G7 SSE inlines the CRT float adapters into native doublecos/sin;
// /Oy- retains their out-of-line copies and loses this body. Both home rows
// match without /Oy-. The old no-boundary note confused RVA and VA.
UpdateSleepTime ShipSlowDeathBehavior::update(){
 UpdateSleepTime sleep=SlowDeathBehavior::update();
 Thing*object=(Thing*)m_object;
 if(object){Matrix3D transform(*object->getTransformMatrix());transform.In_Place_Pre_Rotate_X(m_pitchRate);transform.In_Place_Pre_Rotate_Y(m_rollRate);object->setTransformMatrix(&transform);}
 return sleep;
}
