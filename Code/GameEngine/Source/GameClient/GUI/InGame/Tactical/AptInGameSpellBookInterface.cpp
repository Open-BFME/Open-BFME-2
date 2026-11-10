// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder retains AptInGameSpellBookInterface.cpp and helper identities.
// Twenty-four20B button caches start50. WB and retail agree on level4/string8.
#include <stdlib.h>
#include "ascii_string.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
// Retail's spell-book button-state table at VA 0x00C68508 (RVA 0x868508): six
// Apt button-state suffixes, in retail's index order, that SetButtonState passes to
// the Apt command invoker. Each suffix string is its own .rdata object at retail
// (VA 0x00C031B8 "_unused", 0x00BE5874 "_disabled", 0x00C684FC "_cantAfford",
// 0x00C684F4 "_static", 0x00C684E8 "_notReady", 0x00C031D8 "_up"), so the
// pointer array can hand the linker real targets instead of anonymous literals.
extern const char BfmeSpellButtonStateUnused[]="_unused";
extern const char BfmeSpellButtonStateDisabled[]="_disabled";
extern const char BfmeSpellButtonStateCantAfford[]="_cantAfford";
extern const char BfmeSpellButtonStateStatic[]="_static";
extern const char BfmeSpellButtonStateNotReady[]="_notReady";
extern const char BfmeSpellButtonStateUp[]="_up";
const char *g_00C68508[]={BfmeSpellButtonStateUnused,BfmeSpellButtonStateDisabled,BfmeSpellButtonStateCantAfford,BfmeSpellButtonStateStatic,BfmeSpellButtonStateNotReady,BfmeSpellButtonStateUp};
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const int &,const char *const &);
namespace AptUtils { AsciiString DotPath2SlashPath(const char *); }
#include "../../../../../../Libraries/Source/Apt/AptCommandTarget.h"
#include "../../../../../Include/Common/DelegateDesc.h"
struct SpellTimerDesc {void *receiver;int index;};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);private:void *ptr;};
class Rva0052A786 {public:Rva0052A786 &rva0052A786(const DelegateDesc*);private:void *ptr;};
struct SpellOverButtonDesc { void *receiver;int slotNum; };
class Rva0052A7C1 {public:Rva0052A7C1 &rva0052A7C1(const DelegateDesc *);private:void *ptr;};
class AptOverButtonHandler {public:void *vtable;int refCount;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template<class T> class AptRef {
public:
 AptRef(const SpellOverButtonDesc *desc) {((Rva0052A7C1 *)this)->rva0052A7C1((const DelegateDesc *)desc);}
 AptRef(const DelegateDesc*delegateDesc){((Rva00579E47*)this)->Rva00579E47::Rva00579E47(*delegateDesc);}
 AptRef(const SpellTimerDesc*spellTimerDesc){((Rva0052A786*)this)->rva0052A786((const DelegateDesc*)spellTimerDesc);}
 AptRef(const AptRef &other):ptr(other.ptr){if(ptr)++ptr->refCount;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
private:T *ptr;
};
#include "../../../../../../Libraries/Source/Apt/AptPlayerClass.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../../../../Include/Common/BfmeSelectionState.h"
class BfmeMemberRV {public:bool bfmeAskRV();};
class BfmeThingRV {public:BfmeMemberRV *bfmePickRV();};
class PlayerList;extern PlayerList *ThePlayerList;
class Object {public:const AsciiString *rva00290E67() const;};
#include "../../../../../Include/Common/Player.h"
class CommandButton;
enum CBCommandStatus { CBC_COMMAND_NOT_USED };
enum CommandAvailability { COMMAND_AVAILABLE=1 };
class GameWindow;
#include "../../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

#include "../../../../../Include/GameClient/CommandSet.h"

class Image;
#include "../../../../../Include/GameClient/CommandButton.h"
class GameWindow;
class SpellFrameClock 
{
 public:
 virtual void s00();
 virtual void s01();
 virtual void s02();
 virtual void s03();
 virtual void s04();
 virtual void s05();
 virtual void s06();
 virtual void s07();
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual unsigned getFrame();
 
}
;
// Retail reads the frame clock through VA 0x00DFE77C, TheGameClient (not TheDisplay).
class GameClient;
extern GameClient *TheGameClient;

struct SpellPlayerListView 
{
 char unknown0[0x10];
 BfmeMemberRV *localPlayer;
 
}
;
struct SpellControlBarColorView 
{
 char unknown0[0x208];
 unsigned color;
 
}
;
#include "../../../../../Include/Common/Rva00223A94.h"
class Rva002239B2 
{
 public:void rva002239E2(const AsciiString &,const Image *);
 
}
;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *,void *,const char *,const char *,const char *);
int __cdecl Rva0052519DFire(void *,void *,const char *,const char *,int *);
class BannerUI 
{
 public:void SetBannerSlotXOffset(unsigned,float);
 
}
;
extern BannerUI *TheBannerUI;
class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0029A767FloatField 
{
 public:void set(float);
 
}
;
struct SpellBannerLayout 
{
 float offsets[2];
 int limit;
 
}
;
static const SpellBannerLayout spellBannerLayouts[5]=
{
 
 {
  
  {
   0,0
  }
  ,7
 }
 ,
 {
  
  {
   0,60
  }
  ,9
 }
 ,
 {
  
  {
   60,60
  }
  ,18
 }
 ,
 {
  
  {
   60,102
  }
  ,20
 }
 ,
 {
  
  {
   102,102
  }
  ,0
 }
 
}
;
struct SpellWidthEntry 
{
 float width;
 int limit;
 
}
;
struct SpellWidthTable 
{
 SpellWidthEntry entries[2];
 float fallback;
 
}
;
static const SpellWidthTable spellWidths=
{
 
 {
  
  {
   0,7
  }
  ,
  {
   0.05859375f,18
  }
  
 }
 ,0.099609375f
}
;
__forceinline void SetSpellBannerLayout(int count) 
{
 if(!TheBannerUI)return;
 unsigned i=0;
 while(i<4 && count>=spellBannerLayouts[i].limit)++i;
 const float *offsets=spellBannerLayouts[i].offsets;
 for(unsigned j=0;j<2;++j)TheBannerUI->SetBannerSlotXOffset(j,offsets[j]);
 
}
__forceinline void SetSpellWindowWidth(int count) 
{
 unsigned i=0;
 while(i<2 && count>=spellWidths.entries[i].limit)++i;
 float width=*(const float *)((const char *)&spellWidths+i*8);
 ((Rva0029A767FloatField *)TheInGameUI)->set(width);
 
}
struct SpellAptModeView {char prefix00[0x318];int mode318;};
class CommandSet;
#include "../../../../../Include/Common/Rva0031D5F8.h"
// Native52A34D..52A36A is the 29B constructor callback passed by52AD30
// to the plain array constructor: 24 entries, stride20, starting at+50.
// The existing52A36A accessor independently reads float+8 and int+C.
// Original entry spelling and the roles of fields0/C/10 remain unknown.
struct Rva0052A34D {
 Rva0052A34D();
 const CommandButton *button; int state; float progress; unsigned color; bool flashing; char unknown11[3];
};
Rva0052A34D::Rva0052A34D():button(0),state(0),progress(1.0f),color(0),flashing(false){}
class AptInGameSpellBookInterface {
public: class Impl {
 public: void SetButtonState(int slotNum,int state);
 void OnClipLoaded(const char *params);
 void OnClipUnloaded(const char *params);
 void OnButtonPressed(const char *params);
 void rva0052A53B();
 void Update();
 static AsciiString GetButtonImageTargetName(int slotNum);
 private:
 typedef Rva0052A34D ButtonSlot;
 void *m_owner;void *m_level;AsciiString m_clipName;bool initialized;char unknownD[0x1b];BfmeMemberRV *m_player;CommandSet *m_commandSet;bool flashFlags[32];ButtonSlot m_slots[24];
};
};
class Rva0052A470 { public: void rva0052A66A(); };
// Native52A7FC..52A804 is the complete8B RET4 callback bound by52AD30.
// WB13C59E0 names OnClipUnloaded and calls the same established cleanup.
void AptInGameSpellBookInterface::Impl::OnClipUnloaded(const char *) {
 ((Rva0052A470 *)this)->rva0052A66A();
}
// Native52A3AA..52A3F1 is complete71B RET4; WB13C5400 names this
// callback and independently proves atoi, the24-slot bounds and mode318.
// Calls the rowed ControlBar::processCommandUI (0x00539A65): button, the
// mode-318 flag and false (pointer, bool, bool; RET12).
void AptInGameSpellBookInterface::Impl::OnButtonPressed(const char *param) {
 int index=atoi(param);
 if(index<0 || index>=24)return;
 const CommandButton *button=(const CommandButton *)m_slots[index].button;
 if(button) {
  TheControlBar->processCommandUI(button,((SpellAptModeView *)g_bfmeAptWindowManager)->mode318!=2,false);
 }
}
// WB013C4DD0 and native92B52A414..52A470: cdecl hidden AsciiString return.
// Format a local then copy it into the returned object before local cleanup.
AsciiString AptInGameSpellBookInterface::Impl::GetButtonImageTargetName(int slotNum) {
 AsciiString result;
 result.format("InGameSpellBookSpell%dImage",slotNum+1);
 return result;
}
// WB013C5600 and native244B52AC3C..52AD30: clip name plus24 hover handlers.
// The descriptor stores receiver/index and constructs the by-value reference in place.
void AptInGameSpellBookInterface::Impl::OnClipLoaded(const char *params) {
 m_clipName=params;
 AsciiString prefix;
 prefix.format("Palantir/%s/Spell%%d/",AptUtils::DotPath2SlashPath(m_clipName.str()).str());
 for(int i=0;i<24;++i) {
  AsciiString path;
  path.format(prefix.str(),i+1);
  SpellOverButtonDesc descriptor={this,i};
  ((AptPlayer *)g_bfmeAptWindowManager)->AddOverButtonHandler(path,&descriptor);
 }
}
// WB013C5DC0 and native89B52A804..52A85D RET8. The one-based index is
// a const-reference temporary; retail reuses the dead slotNum argument for it.
void AptInGameSpellBookInterface::Impl::SetButtonState(int slotNum,int state) {
 ButtonSlot &slot=m_slots[slotNum];
 if(slot.state==state)return;
 Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,m_level,m_clipName.str(),"SetButtonState",slotNum+1,g_00C68508[state]);
 slot.state=state;
}
// Entire165B52A53B..52A5E0; WB13C68C0 remains unnamed.
// Retail and WB prove cached player28, commandset2C and32 flash bytes30.
void AptInGameSpellBookInterface::Impl::rva0052A53B() {
 if(!TheGameLogic->rva0042219() || (TheLivingWorldLogic && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())) {
  m_player=0;m_commandSet=0;
 } else {
  BfmeMemberRV *player=((BfmeThingRV *)ThePlayerList)->bfmePickRV();
  if(player && !player->bfmeAskRV())player=0;
  if(player!=m_player) {
   m_player=player;m_commandSet=0;
   if(player) {
    Object *object=((Player *)player)->rva002AC629();
    if(object) {
     m_commandSet=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(object->rva00290E67());
     for(bool *p=flashFlags;p!=flashFlags+32;++p)*p=true;
    }
   }
  }
 }
}

class AptCommandMap {public:void *vtable;int refCount;};
class AptTimer {public:void *vtable;int refCount;};
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void bind(AptCommandMapAdder &adder, const AsciiString&name,DelegateDesc d)
{
	adder.AddCommandMap(name,&d);
}
class Rva00524349 {public:~Rva00524349();private:int names[3];};
class AptTimerAdder : public Rva00524349 {
public:AptTimerAdder();~AptTimerAdder();void AddTimer(const AsciiString&,AptRef<AptTimer>);
};

// Native52AD30..52AF1C492B; WB13C4EC0 proves the SpellBook Impl
// constructor, four command bindings and24 indexed timers. Retain the
// existing payload owner and opaque two-word ABI used by its rowed factory.
// Registration-list offsets10/1C and their destructor providers are retail
// facts; the array callback independently establishes the20B slot layout.
class Rva0052A4B5 {public:void rva0052A65A(int);};
class Rva0052AD30Payload {
public:Rva0052AD30Payload(void*,void*);
private:
 void *owner,*level;AsciiString clipName;bool initialized;
 AptCommandMapAdder maps;AptTimerAdder timers;void *player,*commandSet;
 bool flashFlags[32];Rva0052A34D slots[24];
};
Rva0052AD30Payload::Rva0052AD30Payload(void *o,void *l)
 :owner(o),level(l),initialized(false),player(0),commandSet(0) {
 AptInGameSpellBookInterface::Impl *self=(AptInGameSpellBookInterface::Impl*)this;
 bind(maps, "OnAptInGameSpellBookLoaded",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnClipLoaded));
 bind(maps, "OnAptInGameSpellBookUnloaded",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnClipUnloaded));
 bind(maps, "OnAptInGameSpellBookShown",DelegateDesc((Rva0052A4B5*)this,&Rva0052A4B5::rva0052A65A));
 bind(maps, "OnAptInGameSpellBookButtonPressed",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnButtonPressed));
 for(bool *p=flashFlags;p!=flashFlags+32;++p)*p=true;
 for(int index=0;index<24;++index) {
  AsciiString name;
  name.format("InGameSpellBookSpell%dTimer",index+1);
  SpellTimerDesc desc={this,index};
  timers.AddTimer(name,&desc);
 }
}

// Whole941B52A85D..52AC0A and WB13C6030 read. All table values from retail80B.
void AptInGameSpellBookInterface::Impl::Update() 
{
 if(((StringBase<char> *)&m_clipName)->isEmpty())return;
 if(!initialized) 
 {
  Rva005FB5E6AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,m_level,m_clipName.str(),"SetState","_show");
  return;
  
 }
 rva0052A53B();
 int slotNum=0;
 if(m_commandSet)for(int i=0;i<32 && slotNum<24;++i) 
 {
  bool &available=flashFlags[i];
  bool wasAvailable=available;
  available=false;
  const CommandButton *button=m_commandSet->getCommandButton(i);
  if(!button)continue;
  float progress;
  int availability=TheControlBar->getCommandAvailability(button,0,0,&progress,false);
  if(availability==3)continue;
  if(availability!=5)progress=1.0f;
  bool disabled=false;
  if(m_player!=((SpellPlayerListView *)ThePlayerList)->localPlayer) 
  {
   if(((SpellPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV())availability=0;
   else disabled=true;
   
  }
  int state;
  switch(availability) 
  {
   case 0:case 4:case 6:case 7:state=1;
   break;
   case 1:case 2:state=(button->getOptions() & 0x10000000)?3:5;
   break;
   case 5:state=4;
   break;
   default:state=1;
   break;
   
  }
  if(disabled && state==5)state=6;
  available=state==5 || state==3;
  ButtonSlot &slot=m_slots[slotNum];
  if(slot.button!=button) 
  {
   AsciiString target=GetButtonImageTargetName(slotNum);
   if(slot.button)((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&target);
   slot.button=button;
   const Image *image=button->rva0035B19E();
   if(image)((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(target,image);
   
  }
  SetButtonState(slotNum,state);
  slot.progress=progress;
  slot.color=TheControlBar?((SpellControlBarColorView *)TheControlBar)->color:0xc0000000;
  if(!wasAvailable && available) 
  {
   int index=slotNum+1;
   Rva0052519DFire(g_bfmeAptWindowManager,m_level,m_clipName.str(),"FlashButton",&index);
   
  }
  if(button->getFlashCount()>0 && ((SpellFrameClock *)TheGameClient)->getFrame()%10==0)button->setFlashCount(button->getFlashCount()-1);
  bool flashing=button->getFlashCount()>0;
  if(flashing!=slot.flashing) 
  {
   const char *stateText=flashing?"_show":"_hide";
   int index=slotNum+1;
   Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,m_level,m_clipName.str(),"SetButtonFlashEffectState",index,stateText);
   slot.flashing=flashing;
   
  }
  ++slotNum;
  
 }
 SetSpellBannerLayout(slotNum);
 SetSpellWindowWidth(slotNum);
 for(;slotNum<24;++slotNum) 
 {
  ButtonSlot &slot=m_slots[slotNum];
  if(slot.button) 
  {
   ((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&GetButtonImageTargetName(slotNum));
   slot.button=0;
   
  }
 if (0) { AsciiString t1_dead; }
  SetButtonState(slotNum,0);
  slot.progress=1.0f;
  slot.color=0;
  slot.flashing=false;
  
 }
 
}
