// cl: /O1 /G6 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Preserve inline construction while binding any out-of-line call to the retail provider.
namespace _STL {
template <> _Vector_base<unsigned int, allocator<unsigned int> >::_Vector_base(const allocator<unsigned int>&);
template <> __declspec(dllimport) __forceinline
vector<unsigned int>::vector(const allocator<unsigned int>& a)
    : _Vector_base<unsigned int, allocator<unsigned int> >(a) {}
}
void Rva00030830GameFree(void *);
namespace _STL {
template <> inline void vector<unsigned int>::_M_clear() {
 if(this->_M_start)Rva00030830GameFree(this->_M_start);
}
}
// HeroTransfer.cpp: native44C2C6..44C3D4 has its own EH entry and complete
// return. WB014B7FD0 names SelectRandomHero and carries the matching source
// file and call graph. Keep the established address name pending identity
// convergence. Native fields: slot player-template18, hero-kind50/index5C;
// GameInfo virtual host12/local-slot13. No reference implementation used.
// The vector<unsigned> and conditional game-free specialization follow the
// independently byte-verified CreateAHeroManagerAvailableHeroes.cpp provider.
class CreateAHeroData;
#include "../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;
#include "../../Include/GameNetwork/Rva003FF0E7DwordSlot.h"
#include "../../Include/GameNetwork/GameInfo.h"
extern GameInfo *TheGameInfo;
#include "../../Include/Common/PlayerTemplate.h"
class PlayerTemplateStore {public:const PlayerTemplate *getNthPlayerTemplate(int) const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameClientRandomValue(int,int,char *,int);

// WorldBuilder SelectRandomHero, WB VA 0x014B7FD0 (callgraph lead, score 2.0).
void SelectRandomHero() {
 if(!TheGameInfo)return;
 for(int i=0;i<8;++i) {
  GameSlot *slot=TheGameInfo->getSlot(i);
  if(!slot || slot->m_field50!=1 || !slot->isOccupied())continue;
  if(i!=TheGameInfo->getLocalSlotNum() && !(TheGameInfo->amIHost() && slot->isAI()))continue;
  std::vector<unsigned int> available;
  const PlayerTemplate *playerTemplate=ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_playerTemplate);
  int faction=playerTemplate?playerTemplate->rva001FD234():-1;
  TheCreateAHeroManager->GetAvailableHeroesForFaction(&available,faction);
  if(available.size()>0) {
   int selected=GetGameClientRandomValue(0,available.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameNetwork\\HeroTransfer.cpp",65);
   ((Rva003FF0E7DwordSlot*)slot)->set(available.begin()[selected]);
  }
 }
}
