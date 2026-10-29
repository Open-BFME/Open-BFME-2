// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;
class Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#include "../../../../Include/Common/ObjectModule.h"

class CritterEmitterUpdateIface1
{
public:
    virtual ~CritterEmitterUpdateIface1();
};

class CritterEmitterUpdateIface2
{
public:
    virtual ~CritterEmitterUpdateIface2();
};

// The base is retail's UpdateModule: its constructor (0x00253390) and
// destructor are rowed elsewhere, so they are declared, never defined here.
class UpdateModule : public ObjectModule,
    public CritterEmitterUpdateIface1,
    public CritterEmitterUpdateIface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();

private:
    unsigned int m_14;
    int m_18;
    int m_1c;
};

class CritterEmitterUpdateIface3
{
public:
    virtual void onCollide(Object *, const Coord3D *, const Coord3D *) = 0;
};

class CritterEmitterUpdate : public UpdateModule,
    public CritterEmitterUpdateIface3
{
public:
    CritterEmitterUpdate(Thing *, const ModuleData *);
    virtual void onCollide(Object *, const Coord3D *, const Coord3D *);

protected:
    virtual ~CritterEmitterUpdate();

private:
    unsigned char m_24;
    unsigned char m_25;
};

// ??0CritterEmitterUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CritterEmitterUpdate::CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_24 = 0;
    m_25 = 1;
}
