// cl: /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME1 ScoreKeeperReset9cbfb551 donor: scoring masks, counts, map sweep.
// Native39C5FD..39C7A5 differs with20 players, two further count arrays,
// six standalone maps, frame vectors and the tracked-kill cleanup.
#include <bitset>
#include <map>
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
template <int Bits> class ScoreMask {
 _STL::bitset<Bits> bits;
 public:void set(int bit){bits._Unchecked_set(bit);}
};
static ScoreMask<223> scoringBuildingMask;
static ScoreMask<223> scoringBuildingDestroyMask;
static ScoreMask<223> scoringBuildingCreateMask;
static ScoreMask<223> scoringMask17;
// This storage-compatible clear provider never observes key/value payloads.
// Native tree nodes carry four-byte key/value slots; their semantics are
// still taken from the ScoreKeeper donor only where independently supported.
typedef _STL::map<unsigned,void*> ScoreCountMap;
namespace _STL {
template<> void _Rb_tree<unsigned,pair<const unsigned,void*>,_Select1st<pair<const unsigned,void*> >,less<unsigned>,allocator<pair<const unsigned,void*> > >::clear();
template<> void **vector<void*,allocator<void*> >::erase(void**,void**);
}
class Rva0039B893;
class Rva0039C190 { public:
 Rva0039B893*rva0039C190(Rva0039B893*,Rva0039B893*);
 void clear(){rva0039C190(begin,end);}
 Rva0039B893 *begin,*end,*capacity;
};
class ScoreKeeper {
public:
 void reset(int);
 void addObjectDestroyed(const class Object*);
 void unhookAllScoredKillTrackers();
 void*vtable;
 int moneyEarned,moneySpent;
 int field0C,field10,field14,field18,field1C;
 int unitsDestroyed[20],unitsBuilt,unitsLost;
 int buildingsDestroyed[20],buildingsBuilt,buildingsLost;
 int heroesVetted,unitsVetted,powerPoints,fieldDC;
 int regionCommandPoints,regionResources,regionPowerPoints,currentScore;
 unsigned frameOverride,fieldF4;
 float realF8,realFC;
 int myPlayerIdx,field104,field108,field10C;
 bool field110;char padding111[3];
 int field114,counts118[20],field168,field16C,counts170[20],field1C0,field1C4;
 ScoreCountMap map1C8,map1D4;
 int field1E0;
 ScoreCountMap map1E4,objectsBuilt,objectsDestroyed[20],objectsLost,objectsCaptured;
 _STL::vector<unsigned> trackedKills;
 char padding310[0xC];
 Rva0039C190 frameStats;
 _STL::vector<void*> field328;
};
void ScoreKeeper::reset(int playerIdx){
 scoringBuildingMask.set(7);scoringBuildingMask.set(39);
 scoringBuildingCreateMask.set(7);scoringBuildingCreateMask.set(40);
 scoringBuildingDestroyMask.set(7);scoringBuildingDestroyMask.set(41);
 scoringMask17.set(39);scoringMask17.set(17);
 field1C=0;field18=0;field14=0;
 moneyEarned=moneySpent=0;
 field10=0;field0C=0;
 unitsBuilt=0;unitsLost=0;
 buildingsBuilt=0;buildingsLost=0;
 heroesVetted=0;unitsVetted=0;powerPoints=0;
 frameOverride=0;fieldF4=0;
 realF8=0;realFC=0;
 fieldDC=0;regionCommandPoints=0;regionResources=0;regionPowerPoints=0;currentScore=0;
 objectsBuilt.clear();objectsCaptured.clear();objectsLost.clear();map1E4.clear();
 field114=0;field168=0;field16C=0;field1C0=0;field1C4=0;
 map1C8.clear();map1D4.clear();field1E0=0;
 for(int i=0;i<20;++i){objectsDestroyed[i].clear();buildingsDestroyed[i]=0;unitsDestroyed[i]=0;counts118[i]=0;counts170[i]=0;}
 myPlayerIdx=playerIdx;field104=-1;
 frameStats.clear();
 field328.clear();
 unhookAllScoredKillTrackers();
 field108=0;field10C=0;field110=false;
}


#include "../GameLogicObjectLookupView.h"
#include "../ScoredKillTrackerView.h"
class Player {public:char pad[0x54];int index;int getPlayerIndex()const{return index;}};
class Image;class ImageSubscriptMap{public:Image*&operator[](const unsigned&);};
template<int N> class BitFlags {public:unsigned words[7];bool testSetAndClear(const BitFlags&,const BitFlags&)const;};
// ?BitFlags<116>::testSetAndClear present-unmatched
// Visible existing66B COMDAT makes MSVC cache the two template queries
// without replacing the object register; its bytes are verified separately.
template<> __declspec(noinline) inline bool BitFlags<116>::testSetAndClear(const BitFlags&set,const BitFlags&clear)const{
 for(unsigned i=0;i<7;i++){if(clear.words[i]&words[i])return false;if((set.words[i]&words[i])!=set.words[i])return false;}return true;
}
typedef BitFlags<116> KindOfMaskType;extern KindOfMaskType KINDOFMASK_NONE;
class ThingTemplate {public:char pad[0x108];KindOfMaskType kind;};
enum ObjectStatusTypes{OBJECT_STATUS_UNDER_CONSTRUCTION=0x4C};
class Object {public:void*vtable;const ThingTemplate*m_template;char pad08[0x38-8];Coord3D position;
 bool testStatus(ObjectStatusTypes)const;Player*getControllingPlayer()const;
 const ThingTemplate*getTemplate()const{return m_template;}
 const Coord3D*getPosition()const{return &position;}
};
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
class GlobalData {public:char pad[0x1168];Rva2225E0Filter filter;};extern GlobalData*TheWritableGlobalData;
extern GameLogic*TheGameLogic;
// ZH addObjectDestroyed supplies category and per-player count semantics.
// Native39CDF0..39CF1D301B independently adds completion gating, the
// second totals and tracked-kill predicate/position notifications.
void ScoreKeeper::addObjectDestroyed(const Object*o){
 if(!TheGameLogic->isScoringEnabled())return;
 if(o->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))return;
 int playerIdx=o->getControllingPlayer()->getPlayerIndex();
 
 bool addToCount=false;
 if(o->getTemplate()->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingMask,KINDOFMASK_NONE)){
  if(field110){++buildingsDestroyed[playerIdx];++counts118[playerIdx];addToCount=true;}
 }else if(o->getTemplate()->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingDestroyMask,KINDOFMASK_NONE)){
  if(field110){++buildingsDestroyed[playerIdx];++counts118[playerIdx];addToCount=true;}
 }else if(TheWritableGlobalData->filter.accepts((Object*)o,0)){
  if(field110){++unitsDestroyed[playerIdx];++counts170[playerIdx];addToCount=true;}
 }
 if(addToCount){
  
  int existingCount=0;
  ScoreCountMap::iterator it=objectsDestroyed[playerIdx].find((unsigned)o->getTemplate());
  if(it._M_node!=objectsDestroyed[playerIdx].end()._M_node)existingCount=(int)it->second;
  ((ImageSubscriptMap*)&objectsDestroyed[playerIdx])->operator[]((unsigned)o->getTemplate())=(Image*)(existingCount+1);
  for(unsigned*tracker=trackedKills.begin(),*end=trackedKills.end();tracker!=end;++tracker){
   if(((ScoredKillTracker*)*tracker)->rva0055A892(o))((ScoredKillTracker*)*tracker)->friend_addTrackedKill(o->getPosition());
  }
 }
}
