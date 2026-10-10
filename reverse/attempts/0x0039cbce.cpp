// ?rva0039CBCE@Rva0039CBCE@@QAEXPAVObject@@H@Z
// partial score=0.8458501716665728 date=2026-10-10
// ?rva0039CBCE@Rva0039CBCE@@QAEXPAVObject@@H@Z
// partial score=0.72 date=2026-10-09
// cl: /I. /Ireference/shims/moduledata    /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// stlport
// BFME1 ScoreKeeperReset9cbfb551 donor: scoring masks, counts, map sweep.
// Native39C5FD..39C7A5 differs with20 players, two further count arrays,
// six standalone maps, frame vectors and the tracked-kill cleanup.
#include <bitset>
#include <map>
#include <vector>
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

// ZH addObjectBuilt supplies the score/category/map algorithm. The target
// adds a signed delta, live totals, three clamped maps and frame markers.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Image; class ModuleData; class Player;
class ImageSubscriptMap {public:Image*&operator[](const unsigned &);};
enum ObjectStatusTypes{OBJECT_STATUS_UNDER_CONSTRUCTION=0x4C};
template<int N> class BitFlags {unsigned words[7];public:
 bool testSetAndClear(const BitFlags&,const BitFlags&)const;
 bool test(int bit)const{return (words[(unsigned)bit>>5]&(1u<<(bit&31)))!=0;}
};
typedef BitFlags<116> KindOfMaskType;
extern KindOfMaskType KINDOFMASK_NONE;
class ThingTemplate { public:
 char opaque[0x108];KindOfMaskType kind;
 bool isKindOfMulti(const ScoreMask<223>&set,const KindOfMaskType&clear)const{return kind.testSetAndClear(*(const KindOfMaskType*)&set,clear);}
};
class Object {public:void*vtable;const ThingTemplate*m_template;
 bool testStatus(ObjectStatusTypes)const;
 const ThingTemplate*getTemplate()const{return m_template;}
};
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
class GlobalData {public:char opaque[0x1168];Rva2225E0Filter m_scoreUnitFilter;};extern GlobalData*TheWritableGlobalData;
extern GameLogic*TheGameLogic;
struct Rva00045411BitSet {unsigned bits[7];Rva00045411BitSet(int,int);};
struct FrameStat20 {char data[20];};
class FrameVectorView {public:FrameStat20*start,*finish,*capacity;unsigned size()const{return finish-start;}};
namespace _STL {template<>void vector<const ModuleData*,allocator<const ModuleData*> >::push_back(const ModuleData*const&);}
class Rva0039CBCE:public ScoreKeeper {public:void rva0039CBCE(Object*,int);};
void Rva0039CBCE::rva0039CBCE(Object*o,int delta)
{
 if(!TheGameLogic->isScoringEnabled())return;
 if(o->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))return;
 const ThingTemplate*tmpl=o->getTemplate();
 const unsigned&key=*(const unsigned*)&tmpl;
 bool addToCount=false;
 if(tmpl->isKindOfMulti(scoringBuildingMask,KINDOFMASK_NONE)){
  field10C+=delta;
  if(field110){buildingsBuilt+=delta;field168+=delta;addToCount=true;}
 }else if(tmpl->isKindOfMulti(scoringBuildingCreateMask,KINDOFMASK_NONE)){
  field10C+=delta;
  if(field110){buildingsBuilt+=delta;field168+=delta;addToCount=true;}
 }else if(TheWritableGlobalData->m_scoreUnitFilter.accepts(o,0)){
  field108+=delta;
  if(field110){unitsBuilt+=delta;field1C0+=delta;addToCount=true;}
 }
 if(addToCount){
  int existingCount=0;
  ScoreCountMap::iterator it=objectsBuilt.find(key);
  if(it._M_node!=objectsBuilt.end()._M_node)existingCount=(int)it->second;
  int total=existingCount+delta;if(total<0)total=0;
  ((ImageSubscriptMap*)&objectsBuilt)->operator[](key)=(Image*)total;
  existingCount=0;
  it=map1C8.find(key);
  if(it._M_node!=map1C8.end()._M_node)existingCount=(int)it->second;
  total=existingCount+delta;if(total<0)total=0;
  ((ImageSubscriptMap*)&map1C8)->operator[](key)=(Image*)total;
 }
 if(o->getTemplate()->kind.test(109)){
  int existingCount=0;
  ScoreCountMap::iterator it=map1E4.find(key);
  if(it._M_node!=map1E4.end()._M_node)existingCount=(int)it->second;
  int total=existingCount+delta;if(total<0)total=0;
  ((ImageSubscriptMap*)&map1E4)->operator[](key)=(Image*)total;
 }
 if(field110){
  Rva00045411BitSet invalid(0,179);
  if(tmpl->isKindOfMulti(scoringMask17,*(const KindOfMaskType*)&invalid)){
   int index=((const FrameVectorView*)&frameStats)->size();
   ((_STL::vector<const ModuleData*>*)&field328)->push_back(*(const ModuleData*const*)&index);
  }
 }
 if(field110&&fieldF4==0&&tmpl->kind.test(90)&&!tmpl->kind.test(179))fieldF4=((const FrameVectorView*)&frameStats)->size();
}
