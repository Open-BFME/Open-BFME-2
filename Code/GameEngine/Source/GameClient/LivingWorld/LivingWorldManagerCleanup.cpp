// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../Include/Common/Rva003FA62B.h"
#include "ascii_string.h"
// Native 21427A..2142EA RET0: same receiver forwarded through five
// independently identified cleanup calls, followed by two singleton calls.
// WB callgraph supplies LivingWorldManager; sibling CreateSound independently
// establishes the receiver's +204 table. Method semantics retain address name.
// Target fields: optional cleanup objects264/268 and cleared byte2C0.
class Rva002141D1 { public: void rva002141D1(); };
// LINK: calls bind the rowed owners at the same addresses (Rva0021237E::rva002126BB, Rva002115EC::rva002115EC).
class Rva002115EC { public: void rva002115EC(); };
#include "../../../Include/GameClient/Rva00211589.h"
#include "../../../Include/GameClient/Rva00213A85.h"
#include "../../../Include/GameClient/Rva0021237E.h"
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva002D3627Host {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    char unknown04[0x18-4];
    bool active18;
    __forceinline bool enabled() const { return active18; }
};
class LivingWorld; extern LivingWorld *TheLivingWorld;
#include "../../../Include/Common/Rva003EF14A.h"

// Additional target evidence for 2142EA..214407 RET0: the +48 AsciiString
// selects a template, a 12-byte tracking handle plus ID makes a 16-byte record,
// the +3C coordinate is passed to the existing particle setter, and the record
// is appended to the independently rowed +2A8 vector. The final 2115EC callee
// is a complete 726B RET0 same-receiver routine over +234/+240, inspected in
// full; its original method name is not asserted.
#include "../../../Include/GameLogic/Module/Rva001F3899Arg.h"
#include "../../../Include/GameLogic/Module/Rva001F3899Slot.h"
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva001F384AByteZeroSetter.h"
class ParticleSystem {
public:
    void rva001F465E(void *);
    char unknown00[0xA8];
    int id;
};
ParticleSystem *Make001FCBD7();
#include "../../../Include/Common/RvaSmartPtr12.h"
class BfmeParticleSystemHandle {
public:
    BfmeParticleSystemHandle() : system(0), previous(0), next(0) {}
    __forceinline ~BfmeParticleSystemHandle() {
        if (system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
    }
    __forceinline BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other) throw() {
        *reinterpret_cast<RvaSmartPtr12 *>(this) = *reinterpret_cast<const RvaSmartPtr12 *>(&other);
        return *this;
    }
    ParticleSystem *operator->() const {
        return system ? system : Make001FCBD7();
    }
    ParticleSystem *system;
    BfmeParticleSystemHandle *previous, *next;
};
class ParticleSystemTemplate;
#include "../../../Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;
struct Rva00214243Element { int a[4]; };
// push_back on this element is rowed in its overflow owner as vector<Rva002111C8>.
class Rva002111C8 { public: int a[4]; };
namespace _STL {
template <> void vector<Rva002111C8>::push_back(const Rva002111C8 &);
template <> __declspec(dllimport) __forceinline void vector<Rva00214243Element>::push_back(const Rva00214243Element &x)
{ ((vector<Rva002111C8> *)this)->push_back(*(const Rva002111C8 *)&x); }
}
struct LivingWorldParticleRecord {
    BfmeParticleSystemHandle handle;
    int id;
};
class LivingWorldManager {
public:
    void rva0021427A();
    void rva002142EA();
private:
    char unknown00[0x3C];
    Rva001F3899Arg m_position3C;
    AsciiString m_template48;
    char unknown4C[0x264-0x4C];
    Rva003FA62B *m_cleanup264;
    Rva003EF14A *m_cleanup268;
    char unknown26C[0x2A8-0x26C];
    _STL::vector<Rva00214243Element> m_systems2A8;
    char unknown2B4[0x2C0-0x2B4];
    bool m_active2C0;
};
void LivingWorldManager::rva0021427A()
{
    ((Rva002141D1 *)this)->rva002141D1();
    ((Rva0021237E *)this)->rva002126BB();
    ((Rva00211589 *)this)->rva002129B4();
    ((Rva00213A85 *)this)->rva00213A0E();
    ((Rva0021237E *)this)->rva0021237E();
    if (TheGameLogic) TheGameLogic->rva0023D033();
    if (((Rva002D3627Host *)TheLivingWorld)) ((Rva002D3627Host *)TheLivingWorld)->slot6();
    if (m_cleanup268) {
        m_cleanup268->rva003EF1B8();
        m_cleanup268=0;
    }
    m_active2C0=false;
    if (m_cleanup264) m_cleanup264->clear();
}

// ?rva002142EA@LivingWorldManager@@QAEXXZ
void LivingWorldManager::rva002142EA()
{
    if (((Rva002D3627Host *)TheLivingWorld)->enabled()) {
        ParticleSystemTemplate *particleSystemTemplate;
        {
            AsciiString name(m_template48.str());
            particleSystemTemplate=TheParticleSystemManager->findTemplate(name);
        }
        if (particleSystemTemplate) {
            LivingWorldParticleRecord record;
            record.handle=TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
            if (record.handle.system) {
                record.id=record.handle.system->id;
                reinterpret_cast<Rva001F3899Slot *>(record.handle.system)->set(m_position3C);
                record.handle->rva001F465E((void *)1);
                reinterpret_cast<Rva001F384AByteZeroSetter *>(record.handle.operator->())->disable();
            }
            m_systems2A8.push_back(*reinterpret_cast<Rva00214243Element *>(&record));
        }
        ((Rva002115EC *)this)->rva002115EC();
    }
}
