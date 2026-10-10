// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// BFME1 575ba2b AptPalantirResourceImageSlotConstructor.cpp supplies the
// resource-bar registration sequence. Native2D5188..2D5333 supplies layout,
// six strings, four existing binding constructors and complete EH ownership.
// Keep an address-derived owner pending reconciliation with the Palantir class.
#include "ascii_string.h"
#include "Lib/Coord2D.h"
class Image;
class Display;
extern Display *TheDisplay;
class W3DDisplay { public: void rva0004D6B3(Image *,float,float,float,float,int,int); };
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget {public:void rva002239FA(const AsciiString &,const AsciiString &);};
class Rva00223A94 {public:int rva00223A94(const AsciiString *);};
class Rva002246B1 {public:int rva002246B1(const AsciiString *);};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __single_inheritance ResourceDrawTarget {};
typedef void (ResourceDrawTarget::*ResourceDrawMethod)(const Coord2D &,const Coord2D &,void *,void *);
struct DelegateDesc {DelegateDesc(ResourceDrawMethod m,void *o):object(o),method(m){} void *object; ResourceDrawMethod method;};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc &);void *ptr;};
class Rva002D4594 {public:Rva002D4594(const int *);void *ptr;};
class Rva002D45C9 {public:Rva002D45C9(const int *);void *ptr;};
class Rva002D45FE {public:Rva002D45FE(const int *);void *ptr;};
class AptCustomRender;
class AptOverButtonHandler;
template<class T>class AptRef {
public:
 // These four-byte callback arguments are constructed in the caller's stack
 // slot by the existing rowed wrapper constructors. Their int-pointer API
 // copies the descriptor's pointer bits; it does not dereference the bound
 // resource field. VC7.1's qualified constructor call preserves that ABI.
 __forceinline AptRef(const DelegateDesc *d){reinterpret_cast<Rva00579E47*>(this)->Rva00579E47::Rva00579E47(*d);}
 AptRef(const AptRef &a):ptr(a.ptr){if(ptr)++reinterpret_cast<int*>(ptr)[1];}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(ptr));}
 struct Resources {int *slot;};
 struct Multiplier {float *slot;};
 struct CommandPoints {int *slot;};
 __forceinline AptRef(Resources d){reinterpret_cast<Rva002D4594*>(this)->Rva002D4594::Rva002D4594(reinterpret_cast<const int*>(&d.slot));}
 __forceinline AptRef(Multiplier d){reinterpret_cast<Rva002D45C9*>(this)->Rva002D45C9::Rva002D45C9(reinterpret_cast<const int*>(&d.slot));}
 __forceinline AptRef(CommandPoints d){reinterpret_cast<Rva002D45FE*>(this)->Rva002D45FE::Rva002D45FE(reinterpret_cast<const int*>(&d.slot));}
 void *ptr;
};
class AptPlayer {public:void AddCustomRender(const AsciiString &,AptRef<AptCustomRender>);void AddOverButtonHandler(const AsciiString &,AptRef<AptOverButtonHandler>);void RemoveOverButtonHandler(const AsciiString &);};
__forceinline void AddResourceRender(const AsciiString &name,DelegateDesc desc) {
 reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddCustomRender(name,&desc);
}
class Rva002D3869OwnedPrefix {public:void release();};
class Rva0055076F {public:void rva0055076F();};
// The owned image records: their releases are rowed out of line
// (0x002D3869 checks for null, 0x0055076F does not); the destructor below
// inlines both.
void __cdecl operator delete(void *) throw();
struct ResourceOwnedRecord20 {};
struct ResourceOwned20 {ResourceOwned20():ptr(0){} ~ResourceOwned20(){ResourceOwnedRecord20 *p=ptr;ptr=0;if(p)delete p;} ResourceOwnedRecord20 *ptr;};
struct ResourceOwned24 {ResourceOwned24():ptr(0){} ~ResourceOwned24(){void *p=ptr;ptr=0;delete p;} void *ptr;};
class Rva002D5188ResourceBar {
public:
 Rva002D5188ResourceBar();
 ~Rva002D5188ResourceBar();
 void rva002D2D63(const Coord2D &,const Coord2D &,void *,void *);
private:
 int unknown00,unknown04;bool flag08;int resources,commandPoints,unknown14;
 float multiplier;Image *image;ResourceOwned20 owned20;ResourceOwned24 owned24;
};
void Rva002D5188ResourceBar::rva002D2D63(const Coord2D &position,const Coord2D &size,void *,void *) {
 // Complete79B RET16 leaf; constructor binds the receiver and method under
 // RenderFactionIcon. WB F409A0 confirms two point references; the unused
 // trailing argument types remain opaque. Neither coordinate is rounded.
 if(image)reinterpret_cast<W3DDisplay*>(TheDisplay)->rva0004D6B3(image,position.x,position.y,position.x+size.x,position.y+size.y,-1,2);
}
Rva002D5188ResourceBar::Rva002D5188ResourceBar():unknown00(0),unknown04(0),flag08(false),resources(-2),commandPoints(-1),unknown14(-1),multiplier(0.0f),image(0) {
 reinterpret_cast<Rva00222A8BTarget*>(g_bfmeAptWindowManager)->rva002239FA(AsciiString("ResourceBar/ResourceIcon"),AsciiString("Resource_Icon"));
 {
  AsciiString name("RenderFactionIcon");
  AddResourceRender(name,DelegateDesc(reinterpret_cast<ResourceDrawMethod>(&Rva002D5188ResourceBar::rva002D2D63),this));
 }
 {
  AsciiString name("Palantir/ResourceBar/Resources/");
  AptRef<AptOverButtonHandler>::Resources binding={&resources};
  reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddOverButtonHandler(name,AptRef<AptOverButtonHandler>(binding));
 }
 {
  AsciiString name("Palantir/ResourceBar/ResourceMultiplier/");
  AptRef<AptOverButtonHandler>::Multiplier binding={&multiplier};
  reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddOverButtonHandler(name,AptRef<AptOverButtonHandler>(binding));
 }
 {
  AsciiString name("Palantir/ResourceBar/CommandPoints/");
  AptRef<AptOverButtonHandler>::CommandPoints binding={&commandPoints};
  reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddOverButtonHandler(name,AptRef<AptOverButtonHandler>(binding));
 }
}

// Retail 0x002D3B30..0x002D3C5F (303 bytes), the destructor ~AptPalantir
// runs on its +0x98 member: with the Apt window manager still up, drop the
// icon image, the faction icon render and the three over-button handlers
// the constructor registered, then the two owned records.
Rva002D5188ResourceBar::~Rva002D5188ResourceBar() {
 if(g_bfmeAptWindowManager) {
  {AsciiString name("ResourceBar/ResourceIcon");reinterpret_cast<Rva00223A94*>(g_bfmeAptWindowManager)->rva00223A94(&name);}
  {AsciiString name("RenderFactionIcon");reinterpret_cast<Rva002246B1*>(g_bfmeAptWindowManager)->rva002246B1(&name);}
  {AsciiString name("Palantir/ResourceBar/Resources/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
  {AsciiString name("Palantir/ResourceBar/ResourceMultiplier/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
  {AsciiString name("Palantir/ResourceBar/CommandPoints/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
 }
}
