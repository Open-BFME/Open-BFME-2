// cl: /MD
// Scalar deleting destructors that retail reaches only through vtable slots,
// so caller-based discovery never served them. All thirteen share the 28B
// shape (dtor call, flags byte test, conditional scalar delete through pinned
// ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// FamilyDeletingDtors11.cpp and RvaDeletingDtorBatch04.cpp. Each dtor is
// generally declared here and resolves through an address-derived pin
// in reverse/symbols.csv read from the wrapper's own REL32 at +4; every
// retail site calls it directly, so the dtors are non-virtual here. Emitted
// via delete anchors that are never called. Owner identities and layouts are
// not recovered; class names are the dtor addresses.
//  0x005CBAEE via dtor 0x002BEDA4   0x00419B71 via dtor 0x00419B8D
//  0x00431A64 via dtor 0x004318D8   0x00575700 via dtor 0x0057571C
//  0x005CFCD1 via dtor 0x005CF86B   0x005E57AD via dtor 0x005E57C9
//  0x005EA28F via dtor 0x005EA2AB   0x00604A6F via dtor 0x00604A68
//  0x005FAA31 via dtor 0x004E84A4
//  0x004AF161 via dtor 0x004AF17D
//  0x004BAF11 via dtor 0x004BAEC8
// (0x0040FD1C and 0x00558F6E belong to the virtual dtors rowed in Rva0040FB4ADtor.cpp
// and Rva00557CCCDtor.cpp, which emit them with their vtables.)
//  0x006022AE via dtor 0x006022CA

// ABI-only declaration: no UpdateModule layout or local provider is emitted.
#include "../../Include/GameLogic/Module/UpdateModule.h"

// Each dtor is rowed at its address under another name (a virtual dtor, or an
// ICF-folded setter/cleanup); forward to it so ??_G calls the rowed symbol.
class Rva002BED74 { public: virtual ~Rva002BED74(); };
class Rva004318C6 { public: virtual ~Rva004318C6(); };
class EvacuateDamage { protected: virtual ~EvacuateDamage(); friend class Rva004BAEC8; };
class Rva000419B8DDwordImmSetter { public: void apply(); };
class Rva0004E84A4DwordImmSetter { public: void apply(); };
class Rva00057571CDwordImmSetter { public: void apply(); };
class Rva0005CF86BDwordImmSetter { public: void apply(); };
class Rva0005E57C9DwordImmSetter { public: void apply(); };
class Rva0005EA2ABDwordImmSetter { public: void apply(); };
class Rva000604A68DwordImmSetter { public: void apply(); };
class Rva006022CAFileCleanupForward { public: void cleanup(); };

class Rva002BEDA4 { public: __declspec(dllimport) __forceinline ~Rva002BEDA4() { reinterpret_cast<Rva002BED74 *>(this)->Rva002BED74::~Rva002BED74(); } };
class Rva00419B8D { public: __declspec(dllimport) __forceinline ~Rva00419B8D() { reinterpret_cast<Rva000419B8DDwordImmSetter *>(this)->apply(); } };
class Rva004318D8 { public: __declspec(dllimport) __forceinline ~Rva004318D8() { reinterpret_cast<Rva004318C6 *>(this)->Rva004318C6::~Rva004318C6(); } };
class Rva0057571C { public: __declspec(dllimport) __forceinline ~Rva0057571C() { reinterpret_cast<Rva00057571CDwordImmSetter *>(this)->apply(); } };
class Rva005CF86B { public: __declspec(dllimport) __forceinline ~Rva005CF86B() { reinterpret_cast<Rva0005CF86BDwordImmSetter *>(this)->apply(); } };
class Rva005E57C9 { public: __declspec(dllimport) __forceinline ~Rva005E57C9() { reinterpret_cast<Rva0005E57C9DwordImmSetter *>(this)->apply(); } };
class Rva005EA2AB { public: __declspec(dllimport) __forceinline ~Rva005EA2AB() { reinterpret_cast<Rva0005EA2ABDwordImmSetter *>(this)->apply(); } };
class Rva00604A68 { public: __declspec(dllimport) __forceinline ~Rva00604A68() { reinterpret_cast<Rva000604A68DwordImmSetter *>(this)->apply(); } };
class Rva004E84A4 { public: __declspec(dllimport) __forceinline ~Rva004E84A4() { reinterpret_cast<Rva0004E84A4DwordImmSetter *>(this)->apply(); } };
class Rva004AF17D { public: __declspec(noinline) ~Rva004AF17D(); };
class Rva004BAEC8 { public: __declspec(dllimport) __forceinline ~Rva004BAEC8() { reinterpret_cast<EvacuateDamage *>(this)->EvacuateDamage::~EvacuateDamage(); } };
class Rva006022CA { public: __declspec(dllimport) __forceinline ~Rva006022CA() { reinterpret_cast<Rva006022CAFileCleanupForward *>(this)->cleanup(); } };

#include <new>

void Rva002BEDA4_DeleteAnchor(Rva002BEDA4 *p) { delete p; }
void Rva00419B8D_DeleteAnchor(Rva00419B8D *p) { delete p; }
void Rva004318D8_DeleteAnchor(Rva004318D8 *p) { delete p; }
void Rva0057571C_DeleteAnchor(Rva0057571C *p) { delete p; }
void Rva005CF86B_DeleteAnchor(Rva005CF86B *p) { delete p; }
void Rva005E57C9_DeleteAnchor(Rva005E57C9 *p) { delete p; }
void Rva005EA2AB_DeleteAnchor(Rva005EA2AB *p) { delete p; }
void Rva00604A68_DeleteAnchor(Rva00604A68 *p) { delete p; }
void Rva004E84A4_DeleteAnchor(Rva004E84A4 *p) { delete p; }
void Rva004AF17D_DeleteAnchor(Rva004AF17D *p) { delete p; }
void Rva004BAEC8_DeleteAnchor(Rva004BAEC8 *p) { delete p; }
void Rva006022CA_DeleteAnchor(Rva006022CA *p) { delete p; }

// Native 4AF17D..4AF182 is one complete JMP to the matched UpdateModule dtor.
// The existing deleting wrapper at4AF161 calls this entry with unchanged ECX.
// Keep the address-derived receiver name: its original class is unresolved.
// noinline preserves the wrapper's observed call boundary when this is visible.
Rva004AF17D::~Rva004AF17D()
{
    reinterpret_cast<UpdateModule *>(this)->UpdateModule::~UpdateModule();
}

// EnragedBehavior (ctor unit EnragedBehaviorCtor.cpp): its vtable 0x00C40FBC
// slot 0 is the deleting dtor 0x004AF161, which calls 0x004AF17D above -- the
// one JMP to ~UpdateModule. With no vptr store (novtable) its empty virtual
// dtor emits those same 5 bytes and relocation.
class __declspec(novtable) EnragedBehavior : public UpdateModule
{
public:
	virtual ~EnragedBehavior();
};

EnragedBehavior::~EnragedBehavior()
{
}
