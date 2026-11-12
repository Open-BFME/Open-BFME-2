// ?DoAnyHeroTransfer@@YA_NXZ (0x0044C3D4, 493 B): WB DoAnyHeroTransfer (HeroTransfer.cpp).
// The slot switch follows WB: a doIt flag set per kind, with send copied from it
// only in the case 1/3 arm, which gives retail's send home and unthreaded test.
// cl: /O1 /G6 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// R12 (W7-U1): middle loop declares its own counter (for(int i=0;...)) instead of the function-top i: retail keeps the ONE hoisted zero in EBP (ebx is the first loop counter, xor ebx,ebx later) -> nd 58 -> 34.
// Residue (15 B): retail keeps `send` (bool) with a memory home [esp+0x12] (store at each def, reload `cmp byte [esp+0x12],0` in case 2) and does NOT jump-thread the else path of the
// case1/3 test (remote=true falls into test bl,bl;je) -> send behaves address-exposed. Tried: function-scope decl, &send mentions, refs, struct/array holders: all inert.
// stlport
#include <vector>
void Rva00030830GameFree(void *);
namespace _STL {
template <> inline void vector<unsigned int>::_M_clear() {
 if(this->_M_start)Rva00030830GameFree(this->_M_start);
}
}
// Native HeroTransfer.cpp family. WB names are leads; field offsets and
// call ABIs below are from the complete retail bodies and their providers.
class CreateAHeroData;
#include "../../Include/Common/Rva0040A3F9.h"
#include "../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;
#include "../../Include/GameNetwork/Rva003FF0E7DwordSlot.h"
struct HeroTransferDataStats {char before[0xC];int first,second;};
class GameSlot {public:
 bool isOccupied() const;
 bool isAI() const;
 void rva0037AD8D(const CreateAHeroData &);
 char before[0x18];int playerTemplate;char beforeKind[0x50-0x1C];int kind,first,second,index;bool hasData;char align[3];char data[4];
 CreateAHeroData *heroData(){return hasData?(CreateAHeroData*)data:0;}
};
struct HeroTransferSavedSlot {
 char before[0x9C];int kind,first,second,index;bool hasData;char align[3];
 char data[0x1AC-0xB0];
 CreateAHeroData *heroData(){return hasData?(CreateAHeroData*)data:0;}
};
class GameInfo {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
#undef V
 virtual bool amIHost() const;
 virtual int getLocalSlotNum() const;
 GameSlot *getSlot(int);
 char before[0x88-4];int dispatchID;char beforeSaved[0xC8-0x8C];HeroTransferSavedSlot *saved;
};
extern GameInfo *TheGameInfo;
class NetworkInterface;
extern NetworkInterface *TheNetwork;
// Call-only prefix; no object or vtable is constructed from this view.
class HeroTransferNetworkCalls {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
 V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
 V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
 V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
#undef V
 virtual void beginHeroTransfer();
 virtual void endHeroTransfer();
 virtual void sendHero(const CreateAHeroData &,int,int,int);
};
void SelectRandomHero();
bool Rva0044C277Wait();


#include "../../Include/Common/PlayerTemplate.h"
#include "../../Include/Common/PlayerTemplateStore.h"
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameClientRandomValue(int,int,char *,int);


static __forceinline bool heroTransferReady() { return TheGameInfo && TheCreateAHeroManager; }
bool DoAnyHeroTransfer() {
 int i=0;
 if(!heroTransferReady())return false;
 else {
 HeroTransferSavedSlot *saved=TheGameInfo->saved;
 if(saved) {
  for(int i=0;i<8;++i,++saved) {
   CreateAHeroData *data=saved->heroData();
   if(data) {
    GameSlot *slot=TheGameInfo->getSlot(i);
    if(slot) {
     slot->rva0037AD8D(*data);
     slot->first=saved->first;
     slot->second=saved->second;
     ((Rva003FF0E7DwordSlot*)slot)->set(saved->index);
     slot->kind=saved->kind;
    }
   }
  }
  return true;
 }
 SelectRandomHero();
 if(TheNetwork)((HeroTransferNetworkCalls*)TheNetwork)->beginHeroTransfer();
 Rva0040A3F9 *heroes=TheCreateAHeroManager->rva0021F797();
 bool remote=false;
 for(int i=0;i<8;++i) {
  GameSlot *slot=TheGameInfo->getSlot(i);
  if(!slot || !slot->isOccupied())continue;
  bool doIt=false;
  bool send=false;
  switch(slot->kind) {
   case 1:
   case 3:
    if(i==TheGameInfo->getLocalSlotNum())doIt=true;
    else if(TheGameInfo->amIHost() && slot->isAI())doIt=true;
    else remote=true;
    send=doIt;
    break;
   case 2:
    doIt=true;
    break;
   default:
    doIt=false;
  }
  if(doIt) {
   CreateAHeroData *data=heroes->rva0040A32F(slot->index);
   if(data) {
    TheCreateAHeroManager->rva0021A428(*data);
    slot->rva0037AD8D(*data);
    if(send && TheGameInfo)((HeroTransferNetworkCalls*)TheNetwork)->sendHero(*data,TheGameInfo->dispatchID,i,0xFF);
   }
  }
 }
 bool ready=true;
 if(remote)ready=Rva0044C277Wait();
 if(TheNetwork)((HeroTransferNetworkCalls*)TheNetwork)->endHeroTransfer();
 if(ready) {
  for(int i=0;i<8;++i) {
   GameSlot *slot=TheGameInfo->getSlot(i);
   if(slot) {
    CreateAHeroData *data=slot->heroData();
    if(data && slot->kind==1) {
     HeroTransferDataStats *stats=(HeroTransferDataStats*)data;
     slot->first=stats->first;
     slot->second=stats->second;
    }
   }
  }
 }
 return ready;
 }
}
