// ?rva0050EB0A@Rva0050F5A6@@QAEXPBD@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5101E2..510233:81B; served125B incorrectly includes adjacent helpers.
// Native RET510232 is followed by distinct add-ECX24 RET4 helper510233
// (independent call reference at510C54) and erase adapter51023E. Native
// vtable word atRVA865684 points at5101E2. WB1359980/tribute.cpp1369..1370
// corroborates enable-once update semantics but supplies no original owner
// or method name. Canonical4B StringBase and Apt-manager owner are used.
// Child at24 shares the proved Rva0050F5A6 array view with rowed5101C0
// router; native tail callee50FFC0..50FFEC is ordinary ECX method RET0.
#include "ascii_string.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int Rva005FB5E6AptCall(Rva00222A8BTarget*,void*,const char*,const char*,const char*);
bool Rva0023D339Get();
class Player;
class PlayerList {public: char unknown00[0x10]; Player *localPlayer;};
extern PlayerList *ThePlayerList;
class Money {public: char unknown00[4];unsigned amount;};
class Player {public: bool isLocalPlayer() const; char unknown00[0x54];int index;char unknown58[0x38];Money money;};
class BfmeMemberRV {public: bool bfmeAskRV();};
class Rva0050F0AB {public: char unknown00[0x6c];unsigned amount;void rva0050F2AF(unsigned);};
inline const unsigned &minAmount(const unsigned &a,const unsigned &b){return a<b?a:b;}
class Rva0050F041 { public: void rva0050FF1C(); };
class Rva0050F5A6 { public:
 void rva0050FFC0(); void rva0050F4D0(); void rva0050FFEC(const char*); void rva0050EB0A(const char*);
 int level;char unknown04[0x1c];int count;
 struct Entry { Player *player;Rva0050F041 *object; };
 Entry *entries() { return reinterpret_cast<Entry *>((char *)this+0x24); }
};
class Rva005101E2 { public:
 void rva005101E2();
 char unknown00[8];void *level;AsciiString name;char unknown10[16];bool enabled;char unknown21[3];Rva0050F5A6 *child;
};
void Rva005101E2::rva005101E2() {
 if (!enabled && Rva0023D339Get()) {
  Rva005FB5E6AptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,level,name.str(),"SetState","_enabled");
  enabled=true;
 }
 if (child) child->rva0050FFC0();
}

// Native50FFC0..50FFEC44B. Array count20 and stride8 at28 independently
// agree with rowed50FF7F message router and50F5A6 focus-reset walker.
void Rva0050F5A6::rva0050FFC0() {
 rva0050F4D0();
 for(int i=0;i<count;++i) {
  Rva0050F041 *object=entries()[i].object;
  if(object) object->rva0050FF1C();
 }
}

// Native50F4D0..50F5A6 214B RET0. WB13587F0 tribute assertions1126..1163
// proves the same two allocation passes, nullable Money pointer access and
// reference-returning min. PlayerList local10 and BF2 Player Money90 are native;
// WB Money94 is not copied. Slot player24/UI28 agrees with rowed router and
// walkers. UI6C and setter50F2AF use that provider's measured view; eligibility
// uses the existing BfmeMemberRV ABI name without claiming an original name.
// Re-read the slot after calls: native also reloads it, rather than caching UI.
void Rva0050F5A6::rva0050F4D0() {
 Player *local=ThePlayerList->localPlayer;
 unsigned money=0;
 Money *cash=&local->money;
 if(cash) money=cash->amount;
 unsigned available=money;
 for(int i=0;i<count;++i) {
  Entry &slot=entries()[i];
  if(slot.player==local) continue;
  if(slot.object && reinterpret_cast<BfmeMemberRV*>(slot.player)->bfmeAskRV()) {
   unsigned amount=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
   available-=minAmount(available,amount);
  }
 }
 unsigned remaining=money;
 for(int i=0;i<count;++i) {
  Entry &slot=entries()[i];
  if(slot.player==local) continue;
  if(slot.object) {
   if(reinterpret_cast<BfmeMemberRV*>(slot.player)->bfmeAskRV()) {
    unsigned amount=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount+available;
    reinterpret_cast<Rva0050F0AB*>(slot.object)->rva0050F2AF(minAmount(remaining,amount));
   } else reinterpret_cast<Rva0050F0AB*>(slot.object)->rva0050F2AF(0);
   remaining-=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
  }
 }
}

extern "C" __declspec(dllimport) int __cdecl atoi(const char*);
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
int Rva004128BBGetLevel(const char*);
const char *Rva00412845AfterLevel(const char*);
class Rva0050FC54 {public: Rva0050FC54(int,const AsciiString&,Player*);char opaque[0x80];};
class Rva0050FF55 {public: Rva0050FF55(Rva0050F5A6*,int,const AsciiString&,Player*);int rva0050EAC1();char opaque[0x80];Rva0050F5A6 *parent;};
class Object;
class Rva00575674 {public:void rva00575674(Object*);};
void Rva0050F5A6::rva0050FFEC(const char *params) {
 AsciiString indexText;
 if(!Rva004128F0GetParam(params,"index",indexText))return;
 int index=atoi(indexText.str());
 if(index<0 || index>count)return;
 Entry &slot=entries()[index];
 if(slot.object)return;
 AsciiString name;
 if(!Rva004128F0GetParam(params,"name",name))return;
 int rowLevel=Rva004128BBGetLevel(name.str());
 if(rowLevel!=level)return;
 if(slot.player->isLocalPlayer())
  reinterpret_cast<Rva00575674*>(&slot.object)->rva00575674(reinterpret_cast<Object*>(new Rva0050FF55(this,rowLevel,AsciiString(Rva00412845AfterLevel(name.str())),slot.player)));
 else
  reinterpret_cast<Rva00575674*>(&slot.object)->rva00575674(reinterpret_cast<Object*>(new Rva0050FC54(rowLevel,AsciiString(Rva00412845AfterLevel(name.str())),slot.player)));
}

int Rva0050FF55::rva0050EAC1(){
 int total=0;
 for(int i=0;i<parent->count;++i){
  Rva0050F5A6::Entry &slot=parent->entries()[i];
  if(!slot.player->isLocalPlayer() && slot.object)
   total-=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
 }
 return total;
}

class GameWindow;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class AptTributeWindowManager {public:
#define W(n) virtual void slot##n();
 W(0) W(1) W(2) W(3) W(4) W(5) W(6) W(7) W(8) W(9)
 W(10) W(11) W(12) W(13) W(14) W(15) W(16) W(17) W(18) W(19)
 W(20) W(21) W(22) W(23) W(24) W(25) W(26) W(27) W(28) W(29)
 W(30) W(31) W(32) W(33) W(34) W(35) W(36) W(37) W(38) W(39)
 W(40) W(41) W(42) W(43) W(44) W(45) W(46) W(47) W(48)
#undef W
 virtual int winSetFocus(GameWindow*);
};
class GameMessage {public:void appendIntegerArgument(int);};
class MessageStream {public:
#define M(n) virtual void slot##n();
 M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7) M(8) M(9)
 M(10) M(11) M(12) M(13) M(14) M(15) M(16) M(17)
#undef M
 virtual GameMessage *appendMessage(int);
};
extern MessageStream *MessageStreamSubsystem;
void Rva0050F5A6::rva0050EB0A(const char *unused){
 reinterpret_cast<AptTributeWindowManager*>(TheWindowManager)->winSetFocus(0);
 Player *local=ThePlayerList->localPlayer;
 if(!reinterpret_cast<BfmeMemberRV*>(local)->bfmeAskRV())return;
 for(int i=0;i<count;++i){
  Entry &slot=entries()[i];
  Player *player=slot.player;
  if(player==local || !reinterpret_cast<BfmeMemberRV*>(player)->bfmeAskRV())continue;
  if(!slot.object)continue;
  unsigned amount=reinterpret_cast<Rva0050F0AB*>(slot.object)->amount;
  if(amount>0){
   GameMessage *message=MessageStreamSubsystem->appendMessage(0x466);
   if(message){
    message->appendIntegerArgument(local->index);
    message->appendIntegerArgument(player->index);
    message->appendIntegerArgument(amount);
   }
  }
 }
}
