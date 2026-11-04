// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// The native005E4202/005E426F cleanup bodies are implicit diamond destructors,
// not ordinary methods with stack-local cleanup guards. WB015FCEE0 and retail
// calls prove second-base cleanup then first-base cleanup; unwind actions at
// 007A3831/007A3846 adjust the incoming receiver by -0x10. Two 16B nonvirtual
// icon portions plus vtordisp put the shared12B Rva005F4179 base at0x24.
// Replacing the first portion with the existing28B ArmyUnitIcon puts it at0x30.
// The deleting wrappers005E41D7/005E4244 prove the complete pointer adjustments,
// shared virtual-base cleanup and conditional delete. Both full43B RET4 bodies
// occupy gaps between independently bounded neighbours; no suffix is claimed.
//
// Providers005F422C/40B and005E3A76/44B now have actual destructor names and
// real virtual inheritance. Their former address-derived method rows are
// renamed, not aliased. The compiler emits the two vbptr/vtordisp writes.
// WB015F7750 identifies the counted ArmyDetailsMemberIconSlot cleanup in the
// second provider. Snapshot its pointer before decrementing the pointee count,
// preserving native ECX and preventing an aliased member-pointer reload.
// Only inherited slot ownership and field extents are claimed; original class
// names and the unused fields remain unresolved. The ArmyUnitIcon declaration
// is the existing StrategicInGameUIArmyUnitIconLifetime.cpp layout, with the
// same real vector<int>, clip reference, interface and out-of-line destructor.
// Evidence and full-body/provider receipts: W7-R1 r2 build/w7r1r2/diamond.
#include <new>
#include <vector>
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C;
class AptMovieClipFrame;
class Rva005F4179 {
public:
 virtual ~Rva005F4179();
 virtual void slot01()=0;
 virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *)=0;
 virtual TreeHintRef00217D4C rva005F4710();
 virtual void DoUpdate();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
private: int count;void *leaf;
};
struct Rva005F422CClip {
 TargetRef00217D4C *p;
 ~Rva005F422CClip(){ if(p)ReleaseTreeHintRef00217D4C(p); }
};
class Rva005F422C:public virtual Rva005F4179 {
public:
 virtual ~Rva005F422C();
 virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *);
 virtual TreeHintRef00217D4C rva005F4710();
 virtual void DoUpdate();
private: char m_unrecovered[8];Rva005F422CClip clip;
};
class Rva005E3A76Ref {public:virtual void release();int m_refs;};
struct Rva005E3A76Clip {
 Rva005E3A76Ref *p;
 __forceinline ~Rva005E3A76Clip(){Rva005E3A76Ref *old=p;if(old&&--old->m_refs==0)old->release();}
};
class Rva005E3A76:public virtual Rva005F4179 {
public:
 virtual ~Rva005E3A76();
 virtual void slot01();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
private: char m_unrecovered[8];Rva005E3A76Clip clip;
};
Rva005F422C::~Rva005F422C(){}
Rva005E3A76::~Rva005E3A76(){}
class EmitHeroVtableTag;
class Rva005E4202:public Rva005F422C,public Rva005E3A76 {
public:
 Rva005E4202(EmitHeroVtableTag *);
};

struct ClipRef {
 ClipRef():ptr(0){}
 ~ClipRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
 TargetRef00217D4C *ptr;
};
struct UnitView;
namespace StrategicInGameUI {
class ArmyUnitIcon:public virtual Rva005F4179 {
public:
 ArmyUnitIcon(void *owner,void *clip,UnitView *unit);
 virtual ~ArmyUnitIcon();
 virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *);
 virtual TreeHintRef00217D4C rva005F4710();
 virtual void DoUpdate();
private:
 void *m_owner;
 UnitView *m_unit;
 ClipRef m_clip;
 _STL::vector<int> m_upgrades;
};
}

struct EmitVtableTag;
class Rva005E426F:public StrategicInGameUI::ArmyUnitIcon,public Rva005E3A76 {
public:
 Rva005E426F(EmitVtableTag *);
};
// Emits Rva005E426F's tables, whose virtual-base table 0x00877C9C reaches the
// three ArmyUnitIcon overrides through vtordisp thunks with a further -0x10
// (0x005E3D2A/35/40): ArmyUnitIcon expects its virtual base at +0x20, the
// composite places it at +0x30.
// ?<Rva005E426F::Rva005E426F> absent-from-retail
Rva005E426F::Rva005E426F(EmitVtableTag *):StrategicInGameUI::ArmyUnitIcon(0,0,0){}
// The composites' deleting destructors (0x005E41D7, 0x005E4244) are the
// compiler's own ??_G bodies, emitted with each composite's tables: subtract
// to the complete object, run the implicit diamond destructor and the shared
// virtual base's, delete on bit 0. Their vtordisp thunks (0x005E3C67,
// 0x005E3D22) are slot 0 of the virtual-base tables.
// ?<Rva005E4202::Rva005E4202> absent-from-retail
Rva005E4202::Rva005E4202(EmitHeroVtableTag *){}
// The hero icon's own deleting destructor (0x005F445D) and its slot-0
// vtordisp thunk (0x005F4224) are likewise the compiler's ??_G and ??_E
// thunk, emitted with Rva005F422C's tables.

typedef char FirstIconHas32Bytes[sizeof(Rva005F422C)==0x20?1:-1];
typedef char DetailsIconHas32Bytes[sizeof(Rva005E3A76)==0x20?1:-1];
typedef char CompositeHeroHas48Bytes[sizeof(Rva005E4202)==0x30?1:-1];
typedef char CompositeUnitHas60Bytes[sizeof(Rva005E426F)==0x3c?1:-1];
