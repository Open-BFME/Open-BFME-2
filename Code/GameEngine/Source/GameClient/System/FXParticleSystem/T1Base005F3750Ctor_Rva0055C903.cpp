// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/System/FXParticleSystem
//
// ??0T1Base_005F3750@@QAE@PAX0@Z
// retail 0x0055C903, 157 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/System/FXParticleSystem/T1Base005F3750Ctor.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// Native constructor at donor RVA 0x005F3750, 227 bytes.
// The matched T1Derived_005E24B0 constructor forwards to this existing
// address-derived identity. It is not DefaultModule<6> (whose constructor
// is at 0x005E5840). The matched copy constructor at 0x005EB730 installs
// the same vtables: 0x01112E78 at +0, 0x01112E74 at +0x14,
// and 0x01112E60 at +0x18. The inlined info base installs 0x01110920.
// Native base and local AssetList lifetimes generate the retail unwind states.
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include "ascii_string.h"

class Xfer;

namespace FXParticleSystem {
class DefaultDrawModuleInfo {
public:
    DefaultDrawModuleInfo() {}
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
};

}

class T1A1_005DD290 {
public:
    T1A1_005DD290(void *first, void *second);
    virtual void primarySlot();
    virtual ~T1A1_005DD290();

    unsigned int m_storage[4];
};

class ParticleModuleInterface005F2CA0 {
public:
    virtual void interfaceSlot();
};

class ParticleModule005F2CA0
    : public T1A1_005DD290,
      public ParticleModuleInterface005F2CA0 {
public:
    ParticleModule005F2CA0(void *first, void *second);
    virtual void moduleSlot();
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<
    Rva001408C0Key,
    _STL::less<Rva001408C0Key>,
    _STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class AssetList {
public:
    AssetList()
        : m_treeLayoutPad(0),
          m_changed(true) {
    }

    AssetList &operator<<(const AsciiString &name);

private:
    Rva001408C0Set m_prototypes;
    unsigned int m_treeLayoutPad;
    bool m_changed;
};

class ParticleSystemZA;
extern ParticleSystemZA *bfmeNullSystemZA();
extern void Rva009EBAC0(int value);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
#define Rva0134FAA0 ((void *)::Rva0134FAA0)

class T1Base_005F3750
    : public ::ParticleModule005F2CA0,
      public FXParticleSystem::DefaultDrawModuleInfo {
public:
    T1Base_005F3750(void *first, void *second);
    virtual ~T1Base_005F3750();
};

T1Base_005F3750::T1Base_005F3750(
    void *first,
    void *second)
    : ::ParticleModule005F2CA0(first, second)
    , FXParticleSystem::DefaultDrawModuleInfo() {
    if (Rva0134FAA0 != 0) {
        AssetList assets;
        ParticleSystemZA *systemObject =
            *(ParticleSystemZA **)((unsigned char *)this + 4);
        if (systemObject == 0)
            systemObject = bfmeNullSystemZA();
        assets << *(const AsciiString *)((unsigned char *)systemObject + 0x10);
        Rva009EBAC0((int)&assets);
    }
}
