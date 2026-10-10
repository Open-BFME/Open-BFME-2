// ?onCurrentMissionWon@LinearCampaign@@QAEXXZ
// partial score=0.9407676332 date=2026-10-10
// ?onCurrentMissionWon@LinearCampaign@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <string.h>
struct BfmePod172 {int a[43];};
struct BfmeAssignRecord172 {int a[43];};
class CarryoverUnit {public: virtual ~CarryoverUnit();};
class Rva0037DF2C {public:Rva0037DF2C(); ~Rva0037DF2C(){reinterpret_cast<CarryoverUnit*>(this)->CarryoverUnit::~CarryoverUnit();} char data[172];};
struct Rva00291198Dest;
class Rva00291198Host {public:void rva002910B7(Rva00291198Dest*);};
class Rva0037EACC {public:void rva0037EACC(void*);};
class Rva0037E421 {public:void* rva0037E421(int);};
class Object {public:char p0[0x8c]; Object* next;char p90[0x438-0x90];unsigned char status;};
class GameLogic {public:Object*getFirstObject();};extern GameLogic*TheGameLogic;
enum ScienceType {SCIENCE_INVALID=-1};
struct Bits1024 {unsigned int words[32];__forceinline bool test(unsigned n)const {return *(const unsigned int*)((const char*)words+((n/32)*4)) & (1U<<(n%32));} __forceinline void set(unsigned n){*(unsigned int*)((char*)words+((n/32)*4)) |= 1U<<(n%32);} };
class Player {public:char p0[0x14];int value14;char p18[0x5c-0x18];int value5C;char p60[0x13c-0x60];Bits1024 upgrades;char p1BC[0x2f0-0x1bc];_STL::vector<ScienceType>sciences;char p2FC[0x314-0x2fc];float value314;char p318[0x738-0x318];Rva0037E421 revival;};
class PlayerList {public:Player* getNthPlayer(int);int rva002A7D30();Player*getEachPlayerFromMask(int&);char p0[0x14];int count;};extern PlayerList*ThePlayerList;
class ScienceStore {public:bool isScienceGrantable(ScienceType)const;};extern ScienceStore*TheScienceStore;
class UpgradeTemplate {public:char p0[0x78];bool carryover;};
class UpgradeCenter {public:const UpgradeTemplate*rva0026EEA0(int)const;};extern UpgradeCenter*TheUpgradeCenter;
class LinearCampaign {public:void onCurrentMissionWon();char p0[0x10];int value10;_STL::vector<ScienceType>sciences;Bits1024 upgrades;float valueA0;_STL::vector<BfmePod172>units;char pB0[4];_STL::vector<BfmeAssignRecord172>used;bool won;};
void LinearCampaign::onCurrentMissionWon(){
 won=true;
 if(TheGameLogic){
  for(Object*o=TheGameLogic->getFirstObject();o;o=o->next){
   if((o->status&0x10)&&!(o->status&1)){
    units.push_back(*reinterpret_cast<const BfmePod172*>(&Rva0037DF2C()));
    reinterpret_cast<Rva00291198Host*>(o)->rva002910B7(reinterpret_cast<Rva00291198Dest*>(&units.back()));
    ++units.back().a[0x94/4];
   }
  }
 }
 if(ThePlayerList){
  for(int i=0;i<ThePlayerList->count;++i){
   Player*p=ThePlayerList->getNthPlayer(i);
   if(p){Rva0037E421*r=&p->revival;
    if(r){int j=0;void*u;
     while((u=r->rva0037E421(j))!=0){
      if(((unsigned char*)u)[0xa1]){
       units.push_back(*reinterpret_cast<const BfmePod172*>(&Rva0037DF2C()));
       reinterpret_cast<Rva0037EACC*>(u)->rva0037EACC(&units.back());
       ++units.back().a[0x94/4];
      }++j;
     }
    }
   }
  }
 }
 used.clear();
 if(ThePlayerList){
  Player*player=0;int mask=ThePlayerList->rva002A7D30();
  while(!player&&mask){Player*p=ThePlayerList->getEachPlayerFromMask(mask);if(p&&p->value5C==0)player=p;}
  if(player){
   value10=player->value14;sciences.clear();sciences.reserve(player->sciences.size());
   _STL::vector<ScienceType>&ps=player->sciences;ScienceType*end=ps.end();
   for(ScienceType*it=ps.begin();end!=it;++it){ScienceType s=*it;if(TheScienceStore->isScienceGrantable(s))sciences.push_back(s);}
   memset(&upgrades,0,sizeof(upgrades));
   for(int i=0;i<1024;++i){unsigned int mask=1U<<(i&31);unsigned int index=((unsigned)i>>5)*4;if(*(unsigned int*)((char*)player+0x13c+index)&mask){const UpgradeTemplate*t=TheUpgradeCenter->rva0026EEA0(i);if(t&&t->carryover)*(unsigned int*)((char*)this+0x20+index)|=mask;}}
   valueA0=player->value314;
  }
 }
}
