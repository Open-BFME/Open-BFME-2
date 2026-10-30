// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The registration-named ModuleFactory entry allocates the 0x18-byte BFME
// EvacuateDamage and reaches this constructor through ILT 0x0003BD40.

#include <list>

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

private:
    const ModuleData *m_moduleData;
    void *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class EvacuateDamageInterface { public: virtual void slot() = 0; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModule : public PB_DeepBase,
                     public PB_Iface1,
                     public EvacuateDamageInterface
{
public:
    // Retail 0x004BAE1D calls the one linked base ctor, DamageModule's row at
    // 0x004B9704; an inline body here emitted a second, wrong copy first in
    // link order.
    DamageModule(Thing *thing, const ModuleData *moduleData);
};

struct EvacuationRecord
{
    unsigned int m_data[2];
};

class EvacuateDamage : public DamageModule
{
public:
    EvacuateDamage(Thing *, const ModuleData *);

private:
    std::list<EvacuationRecord> m_pendingEvacuations;
};

// ??0EvacuateDamage@@QAE@PAVThing@@PBVModuleData@@@Z
EvacuateDamage::EvacuateDamage(Thing *thing, const ModuleData *moduleData)
    : DamageModule(thing, moduleData)
{
    m_pendingEvacuations.clear();
}
