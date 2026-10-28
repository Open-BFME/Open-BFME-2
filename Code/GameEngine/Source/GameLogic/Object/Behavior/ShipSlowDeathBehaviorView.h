#pragma once

// Shared accessed prefixes from the matched beginSlowDeath/update bodies.
class Matrix3D;
enum UpdateSleepTime { FOREVER=0x3fffffff };
class Thing {public:void setTransformMatrix(const Matrix3D*);const Matrix3D*getTransformMatrix()const{return(const Matrix3D*)((const char*)this+8);}};
class DamageInfo;
class Xfer;
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
protected:
    virtual void xfer(Xfer *xfer);
private:
    char pad28[0x28];
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class ShipSlowDeathBehavior : public SlowDeathBehavior
{
public:
    virtual void beginSlowDeath(const DamageInfo *);
    virtual UpdateSleepTime update();
protected:
    virtual void xfer(Xfer *xfer);
private:
    float m_pitchRate;
    float m_rollRate;
    float m_rotation;
public:
	virtual NameKeyType getModuleNameKey() const;
};
