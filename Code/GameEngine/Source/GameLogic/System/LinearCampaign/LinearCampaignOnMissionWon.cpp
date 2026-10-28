// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
//
// ?onCurrentMissionWon@LinearCampaign@@QAEXXZ @0x001EC3B5 648B
// WB 0x00AF6700 names LinearCampaign::onCurrentMissionWon
// (LinearCampaignManager.cpp 337..488): mark the mission won, collect the
// carry-over units of live objects and of every player's revival list, then
// from the first human player copy the grantable sciences and the upgrades
// whose template carries over. The WB twin tests and sets the 1024-bit
// upgrade masks through BitFlags<1024,UpgradeID>::test/SetBit; spelling the
// loop through those inline bit helpers on a reference to the player's mask
// replaces the earlier bank's volatile index reads.
#include <vector>
#include <string.h>
struct BfmePod172 {int a[43];};
struct BfmeAssignRecord172 {int a[43];};

class CarryoverUnit {public: CarryoverUnit(); virtual ~CarryoverUnit(); private: char m_pad[168];};
struct Rva00291198Dest;
class Rva00291198Host {public:void rva002910B7(Rva00291198Dest*);};
class Rva0037EACC {public:void rva0037EACC(void*);};
class Rva0037E421 {public:void* rva0037E421(int);};
class Object {public:char p0[0x8c]; Object* next;char p90[0x438-0x90];unsigned char status;};
#include "GameLogicObjectLookupView.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<BfmePod172,allocator<BfmePod172> >::push_back(BfmePod172 const &); }
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmePod172, BfmePod172>(BfmePod172 *, BfmePod172 const &); }
namespace _STL { template <> void _Destroy<BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *); }
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> void vector<BfmePod172, allocator<BfmePod172> >::_M_insert_overflow(BfmePod172 *, BfmePod172 const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> BfmeAssignRecord172 * vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::erase(BfmeAssignRecord172 *, BfmeAssignRecord172 *); }
// bfme link decl-only end
extern GameLogic*TheGameLogic;
enum ScienceType {SCIENCE_INVALID=-1};
// Calls in the matched parent use the rowed ScienceType providers.
namespace _STL {
template <> void vector<ScienceType, allocator<ScienceType> >::reserve(unsigned int);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
template <> ScienceType *vector<ScienceType, allocator<ScienceType> >::erase(ScienceType *, ScienceType *);
template <> void vector<ScienceType, allocator<ScienceType> >::_M_insert_overflow(ScienceType *, const ScienceType &, const __false_type &, unsigned int, bool);
}

struct Bits1024 {unsigned int words[32];__forceinline bool test(unsigned n)const {return (words[n/32] & (1U<<(n%32)))!=0;} __forceinline void set(unsigned n){words[n/32] |= 1U<<(n%32);} };
class Player {public:char p0[0x14];int value14;char p18[0x5c-0x18];int value5C;char p60[0x13c-0x60];Bits1024 upgrades;char p1BC[0x2f0-0x1bc];_STL::vector<ScienceType>sciences;char p2FC[0x314-0x2fc];float value314;char p318[0x738-0x318];Rva0037E421 revival;};
class PlayerList {public:Player* getNthPlayer(int);int rva002A7D30();Player*getEachPlayerFromMask(int&);char p0[0x14];int count;};extern PlayerList*ThePlayerList;
class ScienceStore {public:bool isScienceGrantable(ScienceType)const;};extern ScienceStore*TheScienceStore;
class UpgradeTemplate {public:char p0[0x78];bool carryover;};
class UpgradeCenter {public:const UpgradeTemplate*rva0026EEA0(int)const;};extern UpgradeCenter*TheUpgradeCenter;
class LinearCampaign {public:void onCurrentMissionWon();char p0[0x10];int value10;_STL::vector<ScienceType>sciences;Bits1024 upgrades;float valueA0;_STL::vector<BfmePod172>units;char pB0[4];_STL::vector<BfmeAssignRecord172>used;bool won;};
void LinearCampaign::onCurrentMissionWon(){
 won=true;
 if(TheGameLogic){
  for(Object*object=TheGameLogic->getFirstObject();object;object=object->next){
   if((object->status&0x10)&&!(object->status&1)){
    units.push_back(*reinterpret_cast<const BfmePod172*>(&CarryoverUnit()));
    reinterpret_cast<Rva00291198Host*>(object)->rva002910B7(reinterpret_cast<Rva00291198Dest*>(&units.back()));
    ++units.back().a[0x94/4];
   }
  }
 }
 if(ThePlayerList){
  for(int i=0;i<ThePlayerList->count;++i){
   Player*currentPlayer=ThePlayerList->getNthPlayer(i);
   if(currentPlayer){Rva0037E421*revivalList=&currentPlayer->revival;
    if(revivalList){int j=0;void*reviveEntry;
     while((reviveEntry=revivalList->rva0037E421(j))!=0){
      if(((unsigned char*)reviveEntry)[0xa1]){
       units.push_back(*reinterpret_cast<const BfmePod172*>(&CarryoverUnit()));
       reinterpret_cast<Rva0037EACC*>(reviveEntry)->rva0037EACC(&units.back());
       ++units.back().a[0x94/4];
      }++j;
     }
    }
   }
  }
 }
 used.clear();
 if(ThePlayerList){
  Player*player=0;struct MaskStore{int mask;ScienceType s;} ms;ms.mask=ThePlayerList->rva002A7D30();
  while(!player&&ms.mask){Player*currentPlayer=ThePlayerList->getEachPlayerFromMask(ms.mask);if(currentPlayer&&currentPlayer->value5C==0)player=currentPlayer;}
  if(player){
   value10=player->value14;sciences.clear();
   const _STL::vector<ScienceType>&ps=player->sciences;
   sciences.reserve(ps.size());
   for(_STL::vector<ScienceType>::const_iterator it=ps.begin(),end=ps.end();it!=end;++it){ms.s=*it;if(TheScienceStore->isScienceGrantable(ms.s))sciences.push_back(ms.s);}
   memset(&upgrades,0,sizeof(upgrades));
   const Bits1024 &have=player->upgrades;
   for(int i=0;i<1024;++i){if(have.test(i)){const UpgradeTemplate*upgradeTemplate=TheUpgradeCenter->rva0026EEA0(i);if(upgradeTemplate&&upgradeTemplate->carryover)upgrades.set(i);}}
   valueA0=player->value314;
  }
 }
}
