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
class Player {public: char unknown00[0x90];Money money;};
class BfmeMemberRV {public: bool bfmeAskRV();};
class Rva0050F0AB {public: char unknown00[0x6c];unsigned amount;void rva0050F2AF(unsigned);};
inline const unsigned &minAmount(const unsigned &a,const unsigned &b){return a<b?a:b;}
class Rva0050F041 { public: void rva0050FF1C(); };
class Rva0050F5A6 { public:
 void rva0050FFC0(); void rva0050F4D0();
 char unknown00[0x20];int count;
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
