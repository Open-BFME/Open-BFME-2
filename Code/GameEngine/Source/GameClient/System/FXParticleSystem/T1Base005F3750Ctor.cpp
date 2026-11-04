// Native constructor at RVA 0x005F3750, 227 bytes.
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/System/FXParticleSystem/T1Base005F3750Ctor.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: T1Base_005F3750::T1Base_005F3750 0x0055C903 (157B),
// AssetList::AssetList 0x0006D577 (20B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// The matched T1Derived_005E24B0 constructor forwards to this existing
// address-derived identity. It is not DefaultModule<6> (whose constructor
// is at 0x005E5840). The matched copy constructor at 0x005EB730 installs
// the same vtables: 0x01112E78 at +0, 0x01112E74 at +0x14,
// and 0x01112E60 at +0x18. The inlined info base installs 0x01110920.
// Native base and local AssetList lifetimes generate the retail unwind states.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include "ascii_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::_Rb_tree_base(const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> void _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_erase(_Rb_tree_node<Rva001408C0Target *> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;

namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }

class Xfer;

namespace FXParticleSystem {
class DefaultDrawModuleInfo {
public:
    DefaultDrawModuleInfo() {}
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess() = 0;
    virtual void DoXfer(Xfer &xfer) = 0;
};

}

class T1A1_005DD290 {
public:
    T1A1_005DD290(void *first, void *second);
    virtual void primarySlot() = 0;
    virtual ~T1A1_005DD290();

    unsigned int m_storage[4];
};

class ParticleModuleInterface005F2CA0 {
public:
    virtual void interfaceSlot() = 0;
};

class ParticleModule005F2CA0
    : public T1A1_005DD290,
      public ParticleModuleInterface005F2CA0 {
public:
    ParticleModule005F2CA0(void *first, void *second);
    virtual ~ParticleModule005F2CA0();
    virtual void moduleSlot() = 0;
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

class ParticleSystem;
extern ParticleSystem *Make001FCBD7();
extern void bfmeMergeReceiverKeys(int value);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
#define Rva0134FAA0 ((void *)::Rva0134FAA0)

// Retail's tables, each slot the ledger row at the native address. The class's
// own destructor is still filed under the folded placeholder Rva003ABA36
// (vtable slot 0 is ??_GRva003ABA36 0x003AE8D5), so the class is novtable and
// the constructor stores the tables itself: the compiler's table would name a
// T1Base_005F3750 destructor no unit defines.
extern "C" {
void __identifier("??_GRva003ABA36@@UAEPAXI@Z")();
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
void __identifier("??_ERva003ABA36@@WBI@AEPAXI@Z")();
void __identifier("?GetSnapshotName@Rva003AD273@@UAEPBDXZ")();
void __identifier("?DoXfer@Rva003AD273@@WBI@AEXAAVXfer@@@Z")();
}

// Retail table at VA 0x00C1D3F4 (+0x00).
extern "C" const void *const __identifier("g_t1Base005F3750PrimaryTable")[11] = {
    (const void *)&__identifier("??_GRva003ABA36@@UAEPAXI@Z"),
    (const void *)&__identifier("??1Region2D@@QAE@XZ"),
    (const void *)&_purecall,
    (const void *)&__identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z"),
    (const void *)&__identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"),
    (const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"),
    (const void *)&__identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ"),
    (const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"),
    (const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"),
    (const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"),
    (const void *)&__identifier("?Rva004647D1Get@@YAMXZ"),
};

// Retail table at VA 0x00C1C780 (+0x14).
extern "C" const void *const __identifier("g_t1Base005F3750InterfaceTable")[1] = {
    (const void *)&_purecall,
};

// Retail table at VA 0x00C1D3E4 (+0x18, the DefaultDrawModuleInfo base).
extern "C" const void *const __identifier("g_t1Base005F3750DrawInfoTable")[4] = {
    (const void *)&__identifier("??_ERva003ABA36@@WBI@AEPAXI@Z"),
    (const void *)&__identifier("??1Region2D@@QAE@XZ"),
    (const void *)&__identifier("?GetSnapshotName@Rva003AD273@@UAEPBDXZ"),
    (const void *)&__identifier("?DoXfer@Rva003AD273@@WBI@AEXAAVXfer@@@Z"),
};

class __declspec(novtable) T1Base_005F3750
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
    *(const void *const **)this = g_t1Base005F3750PrimaryTable;
    *(const void *const **)((char *)this + 0x14) = g_t1Base005F3750InterfaceTable;
    *(const void *const **)((char *)this + 0x18) = g_t1Base005F3750DrawInfoTable;
    if (Rva0134FAA0 != 0) {
        AssetList assets;
        ParticleSystem *systemObject =
            *(ParticleSystem **)((unsigned char *)this + 4);
        if (systemObject == 0)
            systemObject = Make001FCBD7();
        assets << *(const AsciiString *)((unsigned char *)systemObject + 0x10);
        bfmeMergeReceiverKeys((int)&assets);
    }
}
