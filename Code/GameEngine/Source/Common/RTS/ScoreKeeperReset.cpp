// cl: /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME1 ScoreKeeperReset9cbfb551 donor: scoring masks, counts, map sweep.
// Native39C5FD..39C7A5 differs with20 players, two further count arrays,
// six standalone maps, frame vectors and the tracked-kill cleanup.
#include <bitset>
#include <map>
#include <vector>

// vector<long> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
long *vector<long>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
long *vector<long>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
unsigned *vector<unsigned>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
unsigned *vector<unsigned>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
bool less<unsigned>::operator()(const unsigned &x, const unsigned &y) const
{ return x < y; }
}
template <int Bits> class ScoreMask {
 _STL::bitset<Bits> bits;
 public:void set(int bit){bits._Unchecked_set(bit);}
};
// Retail's one set of masks, owned by Rva007ADC9CMaskInits.cpp; ScoreKeeper.cpp reads the same ones.
extern unsigned char g_00E0284C[28], g_00E02868[28], g_00E02884[28], g_00E028A0[28];
#define scoringBuildingMask (*reinterpret_cast<ScoreMask<223> *>(g_00E0284C))
#define scoringBuildingDestroyMask (*reinterpret_cast<ScoreMask<223> *>(g_00E02868))
#define scoringBuildingCreateMask (*reinterpret_cast<ScoreMask<223> *>(g_00E02884))
#define scoringMask17 (*reinterpret_cast<ScoreMask<223> *>(g_00E028A0))
// This storage-compatible clear provider never observes key/value payloads.
// Native tree nodes carry four-byte key/value slots; their semantics are
// still taken from the ScoreKeeper donor only where independently supported.
typedef _STL::map<unsigned,void*> ScoreCountMap;
namespace _STL {
template<> void _Rb_tree<unsigned,pair<const unsigned,void*>,_Select1st<pair<const unsigned,void*> >,less<unsigned>,allocator<pair<const unsigned,void*> > >::clear();
template<> long *vector<long,allocator<long> >::erase(long*,long*);
template<> void vector<long,allocator<long> >::push_back(const long&);
}
class Rva0039B893{char bytes[0x14];};
class Rva0039C190 { public:
 Rva0039B893*rva0039C190(Rva0039B893*,Rva0039B893*);
 void clear(){rva0039C190(begin,end);}
 int size()const{return end-begin;}
 Rva0039B893 *begin,*end,*capacity;
};
class ScoreKeeper {
public:
 void reset(int);
 void addObjectBuilt(class Object*,int);
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
 _STL::vector<long> field328;
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
#include "../../../Include/Common/Player.h"
class Image;class ImageSubscriptMap{public:Image*&operator[](const unsigned&);};
template<int N> class BitFlags {public:unsigned words[7];BitFlags(int,int);
 __forceinline bool test(int i)const{return (((const unsigned char*)words)[i>>3]&(1<<(i&7)))!=0;}
 bool testSetAndClear(const BitFlags&,const BitFlags&)const;};
// BitFlags<116>::test otherwise emits a per-TU COMDAT that loses in link order.
template<> __declspec(dllimport) __forceinline bool BitFlags<116>::test(int i)const{return (((const unsigned char*)words)[i>>3]&(1<<(i&7)))!=0;}
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
#include "../../../Include/GameLogic/Module/Rva2225E0Filter.h"
class GlobalData {public:char pad[0x1168];Rva2225E0Filter filter;};extern GlobalData*TheWritableGlobalData;
extern GameLogic*TheGameLogic;
// BFME1 ScoreKeeperCounters addObjectBuilt(Object*,Int) supplies the
// category totals and clamped per-template counts. Native39CBCE..39CDF0 (546B)
// independently adds the second totals, completion gating, two further
// count maps and the frame-stat index bookkeeping. WB FA2290 confirms one
// template local supplies the keys. Rejoin that value after each count block
// before storing its result, so the register value and key share one home.
// These tree operations do not change the key or return its local address.
void ScoreKeeper::addObjectBuilt(Object*object,int amount){
 if(!TheGameLogic->isScoringEnabled())return;
 if(object->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))return;
 const ThingTemplate*thingTemplate=object->getTemplate();
 unsigned key=(unsigned)thingTemplate;
 bool addToCount=false;
 if(thingTemplate->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingMask,KINDOFMASK_NONE)){
  field10C+=amount;
  if(field110){buildingsBuilt+=amount;field168+=amount;addToCount=true;}
 }else if(thingTemplate->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingCreateMask,KINDOFMASK_NONE)){
  field10C+=amount;
  if(field110){buildingsBuilt+=amount;field168+=amount;addToCount=true;}
 }else if(TheWritableGlobalData->filter.accepts(object,0)){
  field108+=amount;
  if(field110){unitsBuilt+=amount;field1C0+=amount;addToCount=true;}
 }
 if(addToCount){
  int existingCount=0;
  ScoreCountMap::iterator it=objectsBuilt.find(key);
  if(it._M_node!=objectsBuilt.end()._M_node)existingCount=(int)it->second;
  int newCount=0>existingCount+amount?0:existingCount+amount;
  ((ImageSubscriptMap*)&objectsBuilt)->operator[](key)=(Image*)newCount;
  existingCount=0;
  it=map1C8.find(key);
  if(it._M_node!=map1C8.end()._M_node)existingCount=(int)it->second;
  newCount=0>existingCount+amount?0:existingCount+amount;
  Image *&destination=((ImageSubscriptMap*)&map1C8)->operator[](key);
  thingTemplate=(const ThingTemplate*)key;
  destination=(Image*)newCount;
 }
 if(object->getTemplate()->kind.test(109)){
  int existingCount=0;
  ScoreCountMap::iterator it=map1E4.find(key);
  if(it._M_node!=map1E4.end()._M_node)existingCount=(int)it->second;
  int newCount=0>existingCount+amount?0:existingCount+amount;
  Image *&destination=((ImageSubscriptMap*)&map1E4)->operator[](key);
  thingTemplate=(const ThingTemplate*)key;
  destination=(Image*)newCount;
 }
 if(field110&&thingTemplate->kind.testSetAndClear(*(const KindOfMaskType*)&scoringMask17,KindOfMaskType(0,179)))
  field328.push_back(frameStats.size());
 if(field110&&fieldF4==0&&thingTemplate->kind.test(90)&&!thingTemplate->kind.test(179))
  fieldF4=frameStats.size();
}

// ZH addObjectDestroyed supplies category and per-player count semantics.
// Native39CDF0..39CF1D301B independently adds completion gating, the
// second totals and tracked-kill predicate/position notifications.
void ScoreKeeper::addObjectDestroyed(const Object*object){
 if(!TheGameLogic->isScoringEnabled())return;
 if(object->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))return;
 int playerIdx=object->getControllingPlayer()->getPlayerIndex();
 
 bool addToCount=false;
 if(object->getTemplate()->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingMask,KINDOFMASK_NONE)){
  if(field110){++buildingsDestroyed[playerIdx];++counts118[playerIdx];addToCount=true;}
 }else if(object->getTemplate()->kind.testSetAndClear(*(const KindOfMaskType*)&scoringBuildingDestroyMask,KINDOFMASK_NONE)){
  if(field110){++buildingsDestroyed[playerIdx];++counts118[playerIdx];addToCount=true;}
 }else if(TheWritableGlobalData->filter.accepts((Object*)object,0)){
  if(field110){++unitsDestroyed[playerIdx];++counts170[playerIdx];addToCount=true;}
 }
 if(addToCount){
  
  int existingCount=0;
  ScoreCountMap::iterator it=objectsDestroyed[playerIdx].find((unsigned)object->getTemplate());
  if(it._M_node!=objectsDestroyed[playerIdx].end()._M_node)existingCount=(int)it->second;
  ((ImageSubscriptMap*)&objectsDestroyed[playerIdx])->operator[]((unsigned)object->getTemplate())=(Image*)(existingCount+1);
  for(unsigned*tracker=trackedKills.begin(),*end=trackedKills.end();tracker!=end;++tracker){
   if(((ScoredKillTracker*)*tracker)->rva0055A892(object))((ScoredKillTracker*)*tracker)->friend_addTrackedKill(object->getPosition());
  }
 }
}
