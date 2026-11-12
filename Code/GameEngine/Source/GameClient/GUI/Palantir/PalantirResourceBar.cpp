// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
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
#include "../../../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../../Include/Common/Rva00222A8BTarget.h"
class Rva00223A94 {public:int rva00223A94(const AsciiString *);};
#include "../../../../Include/GameClient/Rva002246B1.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __single_inheritance ResourceDrawTarget {};
typedef void (ResourceDrawTarget::*ResourceDrawMethod)(const Coord2D &,const Coord2D &,void *,void *);
#include "../../../../Include/Common/DelegateDesc.h"
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
 __forceinline AptRef(const DelegateDesc *delegateDesc){reinterpret_cast<Rva00579E47*>(this)->Rva00579E47::Rva00579E47(*delegateDesc);}
 AptRef(const AptRef &aptRef):ptr(aptRef.ptr){if(ptr)++reinterpret_cast<int*>(ptr)[1];}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(ptr));}
 struct Resources {int *slot;};
 struct Multiplier {float *slot;};
 struct CommandPoints {int *slot;};
 __forceinline AptRef(Resources d){reinterpret_cast<Rva002D4594*>(this)->Rva002D4594::Rva002D4594(reinterpret_cast<const int*>(&d.slot));}
 __forceinline AptRef(Multiplier d){reinterpret_cast<Rva002D45C9*>(this)->Rva002D45C9::Rva002D45C9(reinterpret_cast<const int*>(&d.slot));}
 __forceinline AptRef(CommandPoints d){reinterpret_cast<Rva002D45FE*>(this)->Rva002D45FE::Rva002D45FE(reinterpret_cast<const int*>(&d.slot));}
 void *ptr;
};
#include "../../../../../Libraries/Source/Apt/AptPlayerClass.h"
__forceinline void AddResourceRender(const AsciiString &name,DelegateDesc desc) {
 reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddCustomRender(name,&desc);
}
// The owned image records: their releases are rowed out of line
// (0x002D3869 checks for null, 0x0055076F does not); the destructor below
// inlines both.
#include <new>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
class PlayerList;extern PlayerList *ThePlayerList;
#include "../../../../Include/Common/BfmeSelectionState.h"
#include "../../../../Include/Common/BfmeMemberRV.h"
class BfmeThingRV {public:BfmeMemberRV *bfmePickRV();};
struct PlayerTemplateView {char pad[0x151];bool playable;};
struct MoneyView {void *vptr;unsigned value;};
struct PlayerView {char pad[0x34];PlayerTemplateView *playerTemplate;char pad38[0x90-0x38];MoneyView money;};
#include "../../../../Include/GameLogic/Rva002A7461.h"
#include "../../../../Include/GameLogic/Rva002A7389.h"
#include "../../../../Include/Common/Rva002E0CD4.h"
#include "../../../../Include/Common/Rva002E0C68.h"
class Rva002E0C2B {public:int rva002E0C2B();};
struct CountBaseView {char pad[8];int value;};
struct RegionView {char pad[0x40];CountBaseView *base;};
struct LogicView {char pad[0x98];Rva002E0CD4 *region;char pad9c[0xb4-0x9c];bool mode;};
class Rva002D2DB2 {public:Rva002D2DB2 &initialize(int,int)throw();int delay,value,delta,accum;};
class Rva002D2DD4 {public:Rva002D2DD4 &initialize(float)throw();int delay,hold;float value;};
class Rva002D387A {public:void rva002D387A(void*);};
class Rva002D3389 {public:void rva002D3389(void*);};
void Rva002D46ADSet(int);void setResourceIconState(bool);void playCommandPointEffect();
bool Rva003FEECBSetPalantirCommandPoints(int,int);bool Rva003FEF80SetPalantirMultiplier(float);

// Native update initializes and reads these timer records through owned methods.
typedef Rva002D2DB2 ResourceOwnedRecord20;
struct ResourceOwned20 {ResourceOwned20():ptr(0){} ~ResourceOwned20(){ResourceOwnedRecord20 *p=ptr;ptr=0;if(p)delete p;} ResourceOwnedRecord20 *ptr;};
struct ResourceOwned24 {ResourceOwned24():ptr(0){} ~ResourceOwned24(){void *p=ptr;ptr=0;delete p;} Rva002D2DD4 *ptr;};
static __forceinline Rva002D2DB2 *allocateCounter(int from,int to) {
 Rva002D2DB2 *raw=(Rva002D2DB2*)::operator new(0x10);
 if(raw)return &raw->initialize(from,to-from);
 return 0;
}
// Retail 0x002D2D33: a percent bonus as a multiplier (1 + percent/100), a
// file static the multiplier allocation inlines; cl keeps this copy, which
// returns in XMM0 under its register convention.
static float multiplierFromPercent(int percent) {
 return percent*.01f+1.f;
}
static __forceinline Rva002D2DD4 *allocateMultiplier(const int &percent) {
 // Retail reads the member after operator new. A by-value factory argument
 // snapshots it too early and changes both the load and register allocation.
 Rva002D2DD4 *raw=(Rva002D2DD4*)::operator new(0xc);
 if(raw)return &raw->initialize(multiplierFromPercent(percent));
 return 0;
}

class Rva002D5188ResourceBar {
public:
 Rva002D5188ResourceBar();
 ~Rva002D5188ResourceBar();
 void update();
 void renderFactionIcon(const Coord2D &,const Coord2D &,void *,void *);
private:
 int unknown00,unknown04;bool flag08;int resources,commandPoints,unknown14;
 float multiplier;Image *image;ResourceOwned20 owned20;ResourceOwned24 owned24;
};
void Rva002D5188ResourceBar::renderFactionIcon(const Coord2D &position,const Coord2D &size,void *,void *) {
 // Complete79B RET16 leaf; constructor binds the receiver and method under
 // RenderFactionIcon. WB F409A0 confirms two point references; the unused
 // trailing argument types remain opaque. Neither coordinate is rounded.
 if(image)reinterpret_cast<W3DDisplay*>(TheDisplay)->rva0004D6B3(image,position.x,position.y,position.x+size.x,position.y+size.y,-1,2);
}
Rva002D5188ResourceBar::Rva002D5188ResourceBar():unknown00(0),unknown04(0),flag08(false),resources(-2),commandPoints(-1),unknown14(-1),multiplier(0.0f),image(0) {
 reinterpret_cast<Rva00222A8BTarget*>(g_bfmeAptWindowManager)->rva002239FA(AsciiString("ResourceBar/ResourceIcon"),AsciiString("Resource_Icon"));
 {
  AsciiString name("RenderFactionIcon");
  AddResourceRender(name,DelegateDesc(reinterpret_cast<ResourceDrawMethod>(&Rva002D5188ResourceBar::renderFactionIcon),this));
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
  {AsciiString name("RenderFactionIcon");reinterpret_cast<Rva002246B1*>(g_bfmeAptWindowManager)->RemoveCustomRender(&name);}
  {AsciiString name("Palantir/ResourceBar/Resources/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
  {AsciiString name("Palantir/ResourceBar/ResourceMultiplier/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
  {AsciiString name("Palantir/ResourceBar/CommandPoints/");reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);}
 }
}

// Native2D4748..2D4A69,801B, resource-bar update on the same28-byte owner.
// BF1 575ba2b Rva0058DBC0OwnerUpdate.cpp supplies animation purpose/flow;
// native accesses establish Logic98/B4, Player34/60/90 and Template151.
// The timer barriers preserve the separate post-decrement read while a local
// retains the same receiver. They replace the bank's unrelated entry barrier.
void Rva002D5188ResourceBar::update() {
 bool livingWorld=TheLivingWorldLogic&&((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked();
 BfmeMemberRV *player=((BfmeThingRV*)ThePlayerList)->bfmePickRV();
 Rva002E0CD4 *region=TheLivingWorldLogic?((LogicView*)TheLivingWorldLogic)->region:0;
 bool moneyShown=false;int money=-1;
 if(player&&player->bfmeAskRV()&&!livingWorld&&((PlayerView*)player)->playerTemplate&&((PlayerView*)player)->playerTemplate->playable) {
  MoneyView *wallet=&((PlayerView*)player)->money;
  if(wallet){money=wallet->value;moneyShown=true;}
 }
 if(money!=resources){resources=money;Rva002D46ADSet(money);}
 if(moneyShown!=flag08){setResourceIconState(moneyShown);flag08=moneyShown;}
 int count=-1,total=-1;
 if(!livingWorld) {
  Rva002D2DB2 *old=owned20.ptr;owned20.ptr=0;if(old)::operator delete(old);
  if(player&&player->bfmeAskRV()&&((PlayerView*)player)->playerTemplate&&((PlayerView*)player)->playerTemplate->playable) {
   count=((Rva002A7461*)((char*)player+0x60))->rva002A7461();
   total=((Rva002A7389*)((char*)player+0x60))->get(1);
  }
 } else {
  total=-1;
  int limit=0;
  if(region) {
   int value=region->rva002E14DD();
   if(value!=unknown00) {
    if(value>unknown00) {
     int from=((RegionView*)region)->base->value+unknown00;
     int to=region->get();
     Rva002D2DB2 *next=allocateCounter(from,to);
     ((Rva002D387A*)&owned20.ptr)->rva002D387A(next);
    }
    unknown00=value;
   }
   limit=region->get();total=((Rva002E0C68*)region)->rva002E0C68();
  }
  if(owned20.ptr) {
   if(owned20.ptr->delay>0){Rva002D2DB2 *anim=owned20.ptr;--anim->delay;_ReadWriteBarrier();if(anim->delay==0)playCommandPointEffect();}
   else {owned20.ptr->accum+=owned20.ptr->delta;while(owned20.ptr->accum>=66){owned20.ptr->value++;owned20.ptr->accum-=66;}}
   count=owned20.ptr->value;
   if(count>=limit){Rva002D2DB2 *old=owned20.ptr;owned20.ptr=0;if(old)::operator delete(old);count=limit;}
  } else count=limit;
 }
 if(count!=commandPoints||unknown14!=total){if(Rva003FEECBSetPalantirCommandPoints(count,total)){commandPoints=count;unknown14=total;}}
 float multiplier;
 if(!livingWorld) {
  Rva002D2DD4 *old=owned24.ptr;owned24.ptr=0;::operator delete(old);
  if(TheLivingWorldLogic&&((LogicView*)TheLivingWorldLogic)->mode&&region)
   multiplier=((Rva002E0C2B*)region)->rva002E0C2B()*.01f+1.f;
  else multiplier=1.f;
 } else {
  int percent=region?((Rva002E0C2B*)region)->rva002E0C2B():0;
  if(percent!=unknown04){Rva002D2DD4 *next=allocateMultiplier(unknown04);
   ((Rva002D3389*)&owned24.ptr)->rva002D3389(next);unknown04=percent;}
  if(owned24.ptr) {
   multiplier=(owned24.ptr ? owned24.ptr : owned24.ptr)->value;
   if((owned24.ptr ? owned24.ptr : owned24.ptr)->delay>0){Rva002D2DD4 *anim=owned24.ptr;--anim->delay;_ReadWriteBarrier();if(anim->delay==0)playCommandPointEffect();}
   else if(--(owned24.ptr ? owned24.ptr : owned24.ptr)->hold<=0){Rva002D2DD4 *old=owned24.ptr;owned24.ptr=0;::operator delete(old);}
  } else multiplier=unknown04*.01f+1.f;
 }
 if(multiplier!=this->multiplier){if(Rva003FEF80SetPalantirMultiplier(multiplier))this->multiplier=multiplier;}
}
