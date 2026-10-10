// ?update@Rva002D4748@@QAEXXZ
// partial score=0.9294631710362048 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?update@Rva002D4748@@QAEXXZ
// partial score=0.9042 date=2026-10-10
// ?update@Rva002D4748@@QAEXXZ
// Native2D4748..2D4A69 RET0,801B; static resource/cmdpoint/multiplier callback
// callees independently establish the role. Clean BF1 575 donor
// game/GameEngine/Source/GameClient/Rva0058DBC0OwnerUpdate.cpp supplies purpose
// and animation control flow; native target establishes Logic98/B4/B5,
// Player34/60/90 and Template151 views, owning animation20/24, and getter/callback
// call targets. The now-rowed initializer methods return references; using
// constructor names would be an unverified alias, so these factories call the
// owned initializers. Layout labels remain target-access views, not full types.
// Remaining: stack-region and money/total/float home selection; null-arm merge,
// explicit decrement reloads and conditional loop placement. All bindings live.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
class PlayerList;extern PlayerList *ThePlayerList;
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class BfmeMemberRV {public:bool bfmeAskRV();};
class BfmeThingRV {public:BfmeMemberRV *bfmePickRV();};
struct PlayerTemplateView {char pad[0x151];bool playable;};
struct MoneyView {void *vptr;unsigned value;};
struct PlayerView {char pad[0x34];PlayerTemplateView *playerTemplate;char pad38[0x90-0x38];MoneyView money;};
class Rva002A7461 {public:int rva002A7461();};
class Rva002A7389 {public:int get(int);};
class Rva002E0CD4 {public:int get()const;int rva002E14DD()const;};
class Rva002E0C68 {public:int rva002E0C68();};
class Rva002E0C2B {public:int rva002E0C2B();};
struct CountBaseView {char pad[8];int value;};
struct RegionView {char pad[0x40];CountBaseView *base;};
struct LogicView {char pad[0x98];Rva002E0CD4 *region;char pad9c[0xb4-0x9c];bool mode;};
class Rva002D2DB2 {public:Rva002D2DB2 &initialize(int,int)throw();int delay,value,delta,accum;};
class Rva002D2DD4 {public:Rva002D2DD4 &initialize(float)throw();int delay,hold;float value;};
class Rva002D387A {public:void rva002D387A(void*);};
class Rva002D3389 {public:void rva002D3389(void*);};
void __cdecl operator delete(void*)throw();
void Rva002D46ADSet(int);void setResourceIconState(bool);void playCommandPointEffect();
bool Rva003FEECBSetPalantirCommandPoints(int,int);bool Rva003FEF80SetPalantirMultiplier(float);
class Rva002D4748 {public:void update();private:int lastDelta,lastPercent;bool resources;int shownMoney,shownCount,shownTotal;float shownMultiplier;int pad1c;Rva002D2DB2 *countAnim;Rva002D2DD4 *multAnim;};
static __forceinline Rva002D2DB2 *allocateCounter(int from,int to) {
 Rva002D2DB2 *raw=(Rva002D2DB2*)::operator new(0x10);
 if(raw)return &raw->initialize(from,to-from);
 return 0;
}
static __forceinline Rva002D2DD4 *allocateMultiplier(int percent) {
 Rva002D2DD4 *raw=(Rva002D2DD4*)::operator new(0xc);
 if(raw)return &raw->initialize(percent*.01f+1.f);
 return 0;
}
void Rva002D4748::update() {
 bool livingWorld=TheLivingWorldLogic&&((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked();
 BfmeMemberRV *player=((BfmeThingRV*)ThePlayerList)->bfmePickRV();
 Rva002E0CD4 *region=TheLivingWorldLogic?((LogicView*)TheLivingWorldLogic)->region:0;
 bool moneyShown=false;int money=-1;
 if(player&&player->bfmeAskRV()&&!livingWorld&&((PlayerView*)player)->playerTemplate&&((PlayerView*)player)->playerTemplate->playable) {
  MoneyView *wallet=&((PlayerView*)player)->money;
  if(wallet){money=wallet->value;moneyShown=true;}
 }
 if(money!=shownMoney){shownMoney=money;Rva002D46ADSet(money);}
 if(moneyShown!=resources){setResourceIconState(moneyShown);resources=moneyShown;}
 int count=-1,total=-1;
 if(!livingWorld) {
  Rva002D2DB2 *old=countAnim;countAnim=0;if(old)::operator delete(old);
  if(player&&player->bfmeAskRV()&&((PlayerView*)player)->playerTemplate&&((PlayerView*)player)->playerTemplate->playable) {
   count=((Rva002A7461*)((char*)player+0x60))->rva002A7461();
   total=((Rva002A7389*)((char*)player+0x60))->get(1);
  }
 } else {
  int limit=0;
  if(region) {
   int value=region->rva002E14DD();
   if(value!=lastDelta) {
    if(value>lastDelta) {
     int from=((RegionView*)region)->base->value+lastDelta;
     int to=region->get();
     Rva002D2DB2 *next=allocateCounter(from,to);
     ((Rva002D387A*)&countAnim)->rva002D387A(next);
    }
    lastDelta=value;
   }
   limit=region->get();total=((Rva002E0C68*)region)->rva002E0C68();
  }
  if(countAnim) {
   if(countAnim->delay>0){if(--countAnim->delay==0)playCommandPointEffect();}
   else {countAnim->accum+=countAnim->delta;while(countAnim->accum>=66){countAnim->value++;countAnim->accum-=66;}}
   count=countAnim->value;
   if(count>=limit){Rva002D2DB2 *old=countAnim;countAnim=0;if(old)::operator delete(old);count=limit;}
  } else count=limit;
 }
 if(count!=shownCount||shownTotal!=total){if(Rva003FEECBSetPalantirCommandPoints(count,total)){shownCount=count;shownTotal=total;}}
 float multiplier;
 if(!livingWorld) {
  Rva002D2DD4 *old=multAnim;multAnim=0;::operator delete(old);
  if(TheLivingWorldLogic&&((LogicView*)TheLivingWorldLogic)->mode&&region)
   multiplier=((Rva002E0C2B*)region)->rva002E0C2B()*.01f+1.f;
  else multiplier=1.f;
 } else {
  int percent=region?((Rva002E0C2B*)region)->rva002E0C2B():0;
  if(percent!=lastPercent){Rva002D2DD4 *next=allocateMultiplier(lastPercent);
   ((Rva002D3389*)&multAnim)->rva002D3389(next);lastPercent=percent;}
  if(multAnim) {
_ReadWriteBarrier();
   multiplier=(multAnim ? multAnim : multAnim)->value;
   if((multAnim ? multAnim : multAnim)->delay>0){if(--(multAnim ? multAnim : multAnim)->delay==0)playCommandPointEffect();}
   else if(--(multAnim ? multAnim : multAnim)->hold<=0){Rva002D2DD4 *old=multAnim;multAnim=0;::operator delete(old);}
  } else multiplier=lastPercent*.01f+1.f;
 }
 if(multiplier!=shownMultiplier){if(Rva003FEF80SetPalantirMultiplier(multiplier))shownMultiplier=multiplier;}
}
