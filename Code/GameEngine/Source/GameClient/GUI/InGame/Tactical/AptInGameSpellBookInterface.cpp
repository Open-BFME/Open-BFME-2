// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder retains AptInGameSpellBookInterface.cpp and helper identities.
// Twenty-four20B button caches start50. WB and retail agree on level4/string8.
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
class AptCommandTarget {};
struct DelegateDesc {
 template<class T> DelegateDesc(T *o,void(T::*m)(const char*)) : object(o),method(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(m)) {}
 template<class T> DelegateDesc(T *o,void(T::*m)(int)) : object(o),method(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(m)) {}
 void *object;void(AptCommandTarget::*method)(const char*);
};
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
 AptRef(const DelegateDesc*d){((Rva00579E47*)this)->Rva00579E47::Rva00579E47(*d);}
 AptRef(const SpellTimerDesc*d){((Rva0052A786*)this)->rva0052A786((const DelegateDesc*)d);}
 AptRef(const AptRef &other):ptr(other.ptr){if(ptr)++ptr->refCount;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
private:T *ptr;
};
class AptPlayer {public:void AddOverButtonHandler(const AsciiString &,AptRef<AptOverButtonHandler>);};
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
class BfmeSelectionState {public:bool isSelectionLocked() const;};
class BfmeMemberRV {public:bool bfmeAskRV();};
class BfmeThingRV {public:BfmeMemberRV *bfmePickRV();};
class PlayerList;extern PlayerList *ThePlayerList;
class Object {public:const AsciiString *rva00290E67() const;};
class Player {public:Object *rva002AC629();};
class CommandButton;
class ControlBar { public: int rva00539A65(void *,int,int); };
extern ControlBar *TheControlBar;
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
struct SpellAptModeView {char prefix00[0x318];int mode318;};
class CommandSet;
class Rva0031D5F8 {public:void *rva0031D5F8(const AsciiString *);};
// Native52A34D..52A36A is the 29B constructor callback passed by52AD30
// to the plain array constructor: 24 entries, stride20, starting at+50.
// The existing52A36A accessor independently reads float+8 and int+C.
// Original entry spelling and the roles of fields0/C/10 remain unknown.
struct Rva0052A34D {
 Rva0052A34D();
 int unknown0,state; float value8; int unknownC; bool unknown10;
};
Rva0052A34D::Rva0052A34D():unknown0(0),state(0),value8(1.0f),unknownC(0),unknown10(false){}
class AptInGameSpellBookInterface {
public: class Impl {
 public: void SetButtonState(int slotNum,int state);
 void OnClipLoaded(const char *params);
 void OnClipUnloaded(const char *params);
 void OnButtonPressed(const char *params);
 void rva0052A53B();
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
// Keep the established ControlBar callee spelling. Its pointer/bool/bool
// call view preserves the two observed Boolean arguments and RET12 ABI.
void AptInGameSpellBookInterface::Impl::OnButtonPressed(const char *param) {
 int index=atoi(param);
 if(index<0 || index>=24)return;
 const CommandButton *button=(const CommandButton *)m_slots[index].unknown0;
 if(button) {
  typedef int (ControlBar::*ProcessCommand)(const CommandButton *,bool,bool);
  (TheControlBar->*reinterpret_cast<ProcessCommand>(&ControlBar::rva00539A65))
    (button,((SpellAptModeView *)g_bfmeAptWindowManager)->mode318!=2,false);
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
class AptCommandMapAdder {
public:AptCommandMapAdder();~AptCommandMapAdder();
 void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);
 __forceinline void bind(const AsciiString&name,DelegateDesc d){AddCommandMap(name,&d);}
private:int names[3];
};
class Rva00524349 {public:~Rva00524349();private:int names[3];};
class AptTimerAdder : public Rva00524349 {
public:AptTimerAdder();void AddTimer(const AsciiString&,AptRef<AptTimer>);
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
 maps.bind("OnAptInGameSpellBookLoaded",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnClipLoaded));
 maps.bind("OnAptInGameSpellBookUnloaded",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnClipUnloaded));
 maps.bind("OnAptInGameSpellBookShown",DelegateDesc((Rva0052A4B5*)this,&Rva0052A4B5::rva0052A65A));
 maps.bind("OnAptInGameSpellBookButtonPressed",DelegateDesc(self,&AptInGameSpellBookInterface::Impl::OnButtonPressed));
 for(bool *p=flashFlags;p!=flashFlags+32;++p)*p=true;
 for(int index=0;index<24;++index) {
  AsciiString name;
  name.format("InGameSpellBookSpell%dTimer",index+1);
  SpellTimerDesc desc={this,index};
  timers.AddTimer(name,&desc);
 }
}
