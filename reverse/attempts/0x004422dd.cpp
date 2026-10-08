// ?HostValidateColors@AptMpGameSetup@@QAEXXZ
// partial score=0.96 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Near-exact 0x004422DD..0x004424E7 (522B), WB HostValidateColors lead.
// Native facts: host gate at owner vslot +4, GameInfo pointer via +5C;
// GameSlot color +C/state +4, offered vector<bool> +3C4, optional colors +3DC.
// The local map uses native ctor 33C432 (25B) / unsigned find 357180 (56B),
// subscript 2077D6 (69B), and clear/free dtor 43FE62 (56B). The Rva-named
// destructor owner is retained; no application class inheritance is inferred.
// The int/void map supplies only its proven 12-byte physical storage and ctor;
// unsigned-key and GameSlot pointer access use the existing native facades.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f MpGameSetup and
// SkirmishScreenState reference units provided semantic leads; native WB and
// retail accesses, calls and control flow establish the target deltas above.
// Current 522B output has every instruction and call aligned, but reserves
// 0x2C vs 0x28 bytes and swaps saved-this / loop-index stack slots. Bit reference
// and map storage are each four bytes too low; no padding/asm/pins were added.
#include <map>
#include <vector>
#include <new>
class GameSlot {public: bool isHuman() const; bool isObserver() const;
 char pad00[4]; int state; char pad08[4]; int color;};
class GameInfo {public: GameSlot *getSlot(int);};
class Rva0043DA65 {public: int rva0043DA65(); char data[12];};
class ColorSetupOwner {public: virtual void slot0(); virtual bool amIHost();
 virtual void slot2(); virtual void slot3(); virtual void SetColor(GameSlot*,int);};
namespace _STL {template<> map<int,void*>::map();}
class Rva0043EA9C {public:
 _STL::map<int,void*> storage;
 ~Rva0043EA9C();
};
class BFME2RespawnRuleTree {public: void *find(const unsigned&) const; void *sentinel;};
class Image;
class ImageSubscriptMap {public: Image *&operator[](const unsigned&);};
class AptMpGameSetup {public: void HostValidateColors();
 char pad00[0x58]; ColorSetupOwner *owner; Rva0043DA65 *game;
 char pad60[0x3c4-0x60]; _STL::vector<bool> allowed;
 char pad3d8[4]; bool special;
};
void AptMpGameSetup::HostValidateColors() {
 if(!owner->amIHost()) return;
 GameInfo *info=(GameInfo*)game->rva0043DA65();
 if(!info) return;
 Rva0043EA9C reserved;
 bool repair=false;
 for(unsigned i=0;i<8;++i) {
  GameSlot *slot=info->getSlot(i);
  if(!slot) continue;
  int color=slot->color;
  if(color<0) {
   if(!special && !slot->isObserver() && slot->state!=1) repair=true;
   continue;
  }
  BFME2RespawnRuleTree *lookup=(BFME2RespawnRuleTree*)&reserved;
  ImageSubscriptMap *map=(ImageSubscriptMap*)&reserved;
  if(lookup->find((unsigned)color)!=lookup->sentinel) {
   repair=true;
   if(((GameSlot*)((*map)[(unsigned)color]))->isHuman()) continue;
  }
  (*map)[(unsigned)color]=(Image*)slot;
 }
 if(repair) {
  for(unsigned i=0;i<8;++i) {
   GameSlot *slot=info->getSlot(i);
   if(!slot) continue;
   int color=slot->color;
   if(color<0 && (special || slot->isObserver() || slot->state==1)) continue;
   ImageSubscriptMap *map=(ImageSubscriptMap*)&reserved;
    if((GameSlot*)(*map)[(unsigned)color]==slot) continue;
   if(special) owner->SetColor(slot,-1);
   else {
    int c;
    for(c=0;c<allowed.size();++c) {
     BFME2RespawnRuleTree *lookup=(BFME2RespawnRuleTree*)&reserved;
     if(allowed[c] && lookup->find((unsigned)c)==lookup->sentinel) {
      (*map)[(unsigned)c]=(Image*)slot;
      owner->SetColor(slot,c);
      break;
     }
    }
   }
  }
 }
}
