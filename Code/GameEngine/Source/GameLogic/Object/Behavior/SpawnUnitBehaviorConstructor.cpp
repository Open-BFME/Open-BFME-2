// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: SpawnUnitBehavior constructor.
// Retail shape: grandbase ctor call with both args, interface-base vtable
// stores at +0x0C/+0x10, field inits (+0x18/+0x1C = -1, +0x14 = 0), vtable
// store for this class's own interface base at +0x20, then the four
// most-derived vtable stores and a byte copied from the object at this+4.
// /EHs- because retail has no unwind frame.

class Thing;
class ModuleData;

class SpawnUnitBehaviorGrandBase
{
public:
    SpawnUnitBehaviorGrandBase(Thing *, const ModuleData *);
    virtual ~SpawnUnitBehaviorGrandBase();

protected:
    // ObjectModule constructor 0x00113C60 receives the same ModuleData
    // second argument and stores it at +4 (0x00113C83), as in Module.h.
    const ModuleData *m_moduleData;

private:
    unsigned char m_pad[4];
};

class SpawnUnitBehaviorIface1
{
public:
    virtual ~SpawnUnitBehaviorIface1();
};

class SpawnUnitBehaviorIface2
{
public:
    virtual ~SpawnUnitBehaviorIface2();
};

// Retail's base vftable 0x00C1C780 (stored at +0x20 before the derived one) starts with
// a __purecall slot, overridden at 0x00C59120 by the AsciiString getter 0x004B8851; the
// derived table there holds that one slot, so the interface has no virtual destructor.
class SpawnUnitBehaviorIface3
{
public:
    virtual void slot0() const = 0;
};

// The base is retail's UpdateModule: its constructor (0x00253390) and
// destructor are rowed elsewhere, so they are declared, never defined here.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class SpawnUnitBehavior : public UpdateModule, public SpawnUnitBehaviorIface3
{
public:
    SpawnUnitBehavior(Thing *, const ModuleData *);

private:
    // Factory 0x00125D70 -> callback 0x0020D260 binds SpawnOnce at
    // ModuleData+0x1c to parseBool (table RVA 0x00CA7008). Retail
    // 0x0020D147/0x0020D14A copies that byte into this+0x24.
    unsigned char m_spawnOnce;
public:
	// retail slot 4: the rowed ?getModuleNameKey@SpawnUnitBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0SpawnUnitBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
SpawnUnitBehavior::SpawnUnitBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_spawnOnce = *(reinterpret_cast<const unsigned char *>(m_moduleData) + 0x1C);
}
