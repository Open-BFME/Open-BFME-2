// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??0ThreatFinderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003ECCA2, 46 bytes.
// ThreatFinderUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x20 and installs the primary vtable slot and the
// +0x0C/+0x10 secondary slots.
// The rowed pool key at 0x3ECCD6 and the rowed instance factory 0x24FBD0
// (sole caller, ModuleFactory registration literal) prove the class. Row
// supersedes the ctor pin.

enum NameKeyType { NK_UNKNOWN = 0 };
class Thing;
class ModuleData;
class Rva003ECD60Object;
class Xfer;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class UpdateModuleInterface
{
public:
    virtual void f2() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();
    void xfer(Xfer *xfer);

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class ThreatFinderUpdate : public UpdateModule
{
public:
    ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~ThreatFinderUpdate();
    virtual NameKeyType getModuleNameKey() const;

protected:
    virtual void xfer(Xfer *xfer);

private:
    Rva003ECD60Object *m_heap;
};

// ??0ThreatFinderUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x3ECCA2
ThreatFinderUpdate::ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_heap(0)
{
}
