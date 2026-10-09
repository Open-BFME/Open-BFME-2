// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
