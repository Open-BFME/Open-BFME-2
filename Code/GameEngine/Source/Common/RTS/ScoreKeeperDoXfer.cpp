// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// Retail Xfer vtable BBB910 slot28 is operator==(float&) at554C.
// updateFrame39D1F1 independently reads +F8/+FC as floats.
// Clean BF1 ba7ddda Common/RTS/ScoreKeeperXfer.cpp semantic guide.
// WBFA4540 names ScoreKeeper::DoXfer; native39C7B8..39CADA804 proves target fields,
// version12 compatibility branches and all helper addresses. Member purpose
// labels follow the donor only where the same transfer sequence supports them.
#include <map>
class ThingTemplate;
struct TemplateCountKey { const ThingTemplate *pointer; };
typedef _STL::map<TemplateCountKey,int> ObjectCountMap;
class Rva0039C1C3;
// Target snapshot stride is20 including its vptr. These are byte-offset
// access views; record construction remains with the independently rowed provider.
struct ScoreFrameStatsView { void *vtable; int money; float score; short field0C,field0E; unsigned short field10; };
struct FrameStatsVector {
 unsigned int size()const{return finish-start;}
 ScoreFrameStatsView& operator[](unsigned int i){return start[i];}
 ScoreFrameStatsView *start,*finish,*end;
};
class Rva0039C190 { public: void rva0039D1D0(unsigned int); };
class Player { public: bool rva002AA245() const; char opaque[0x94]; int money; };
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../Include/Common/BfmeMemberRV.h"
struct Rva002A8AB1Record;
#include "../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ScoreWeightsView {
 char opaque116C[0x116C];
 float unitsBuilt,unitsDestroyed,buildingsBuilt,buildingsDestroyed;
 float heroesVetted,unitsVetted,field1184,money,powerPoints;
 char opaque1190[0x24];
 float realF8;
};
#include "../ScoredKillTrackerView.h"

struct XferVersion { unsigned char minimum,current; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/Common/XferException.h"
void xferThingTemplateCountMap(Xfer *,ObjectCountMap*);
Xfer *Rva0039C4F7XferSnapshotVector(Xfer *,Rva0039C1C3*);
class ScoreKeeper
{
public:
 virtual ~ScoreKeeper();
 virtual void LoadPostProcess();
 virtual const char*GetSnapshotName();
 virtual void DoXfer(Xfer *);
 void updateFrame(int);
private:
 int moneyEarned,moneySpent; //04,08
 int field0C,field10,field14,field18,field1C;
 int unitsDestroyed[20]; //20
 int unitsBuilt,unitsLost; //70,74
 int buildingsDestroyed[20]; //78
 int buildingsBuilt,buildingsLost; //C8,CC
 int heroesVetted,unitsVetted,powerPoints,fieldDC;
 int regionCommandPoints,regionResources,regionPowerPoints,currentScore;
 unsigned int frameOverride,fieldF4;
 float realF8, realFC;
 int field100,field104,field108,field10C;
 char opaque110[0xD4];
 ObjectCountMap map1E4,objectsBuilt,objectsDestroyed[20],objectsLost,objectsCaptured;
 char opaque304[0x18];
 FrameStatsVector stats;
};
void ScoreKeeper::DoXfer(Xfer *xfer)
{
 if(xfer->IsLightCRC())return;
 // The two transferred bytes occupy a four-byte native argument home.
 union VersionStorage {XferVersion version; unsigned int storage;} versionStorage;
 versionStorage.version.minimum=1;
 versionStorage.version.current=12;
 XferVersion &version=versionStorage.version;
 (*xfer == reinterpret_cast<Xfer::Version &>(version));
 if (version.current < 8)
 {
 (*xfer == moneyEarned);
 (*xfer == moneySpent);
 for (int i = 0; i < 20; ++i)
 {
  (*xfer == unitsDestroyed[i]);
  (*xfer == buildingsDestroyed[i]);
 }
 (*xfer == unitsBuilt);
 (*xfer == unitsLost);
 (*xfer == buildingsBuilt);
 (*xfer == buildingsLost);
 }
 else if (version.current < 9)
 {
 (*xfer == field108);
 (*xfer == field10C);
 }
 else
 {
 (*xfer == moneyEarned);
 (*xfer == moneySpent);
 for (int i = 0; i < 20; ++i)
 {
  (*xfer == unitsDestroyed[i]);
  (*xfer == buildingsDestroyed[i]);
 }
 (*xfer == unitsBuilt);
 (*xfer == unitsLost);
 (*xfer == buildingsBuilt);
 (*xfer == buildingsLost);
 (*xfer == field108);
 (*xfer == field10C);
 }
 (*xfer == fieldDC);
 (*xfer == currentScore);
 (*xfer == field100);
 if(version.current>=2){
  int legacyPowerPoints=0;
  (*xfer == heroesVetted);
 (*xfer == unitsVetted);
 (*xfer == legacyPowerPoints);
 (*xfer == powerPoints);
 }
 if(version.current>=3){(*xfer == regionCommandPoints);
 (*xfer == regionResources);
 (*xfer == regionPowerPoints);}
 if(version.current>=4)(*xfer == frameOverride);
 if(xfer->IsCRC())return;
 xferThingTemplateCountMap(xfer,&objectsBuilt);
 unsigned short destroyedArraySize=20;
 (*xfer == destroyedArraySize);
 if(destroyedArraySize!=20)throw XferException(5,0);
 for(unsigned short i=0;i<destroyedArraySize;++i)xferThingTemplateCountMap(xfer,&objectsDestroyed[i]);
 xferThingTemplateCountMap(xfer,&objectsLost);
 xferThingTemplateCountMap(xfer,&objectsCaptured);
 if(version.current>=5)Rva0039C4F7XferSnapshotVector(xfer,reinterpret_cast<Rva0039C1C3*>(&stats));
 if(version.current>=6)(*xfer == realF8);
 if(version.current>=7){(*xfer == fieldF4);
 (*xfer == field0C);
 (*xfer == field10);}
 if(version.current>=10)xferThingTemplateCountMap(xfer,&map1E4);
 if(version.current>=11){(*xfer == field104);
 (*xfer == realFC);}
 if(version.current>=12){(*xfer == field14);
 (*xfer == field18);
 (*xfer == field1C);}
}

// Native39D1F1..39D40F; WBFA1D10 names updateFrame and explains the owner,
// per-frame score record, and tracked-kill updates. Retail establishes all
// field offsets and weights. The already rowed112B PerFrameStats xfer39B823
// confirms two signed shorts and an unsigned short at10; that unsigned
// float conversion is native _ftol2 rather than the signed SSE shortcut.
void ScoreKeeper::updateFrame(int frameNumber)
{
 if(frameNumber<0)return;
 Player* owner=ThePlayerList->getPlayerFromMask(1<<field100);
 if(!owner)return;
 if(reinterpret_cast<BfmeMemberRV*>(owner)->bfmeAskRV() &&
    owner->rva002AA245())
 {
  if(static_cast<unsigned int>(frameNumber)>=stats.size())
   reinterpret_cast<Rva0039C190*>(&stats)->rva0039D1D0(frameNumber+1);
  ScoreFrameStatsView &record=stats[frameNumber];
  record.money=owner->money;
  if(TheSkirmishAIManager->rva002A8AB1(owner))
  {
   void *collector=TheSkirmishAIManager->rva002A8F24(owner);
   void *economy=*reinterpret_cast<void**>(static_cast<char*>(collector)+0xC);
   record.money+=*reinterpret_cast<int*>(static_cast<char*>(economy)+0x14);
  }
  record.field0C=static_cast<short>(field108);
  record.field0E=static_cast<short>(field10C);
  record.field10=static_cast<unsigned short>(realF8);
  record.score=realF8*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->realF8;
  record.score+=(moneyEarned-field0C)*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->money;
  record.score+=buildingsBuilt*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->buildingsBuilt;
  record.score+=unitsBuilt*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->unitsBuilt;
  for(int i=0;i<20;++i)
  {
   if(i==field100)continue;
   record.score+=unitsDestroyed[i]*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->unitsDestroyed;
   record.score+=buildingsDestroyed[i]*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->buildingsDestroyed;
  }
  record.score+=powerPoints*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->powerPoints;
  record.score+=heroesVetted*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->heroesVetted;
  record.score+=unitsVetted*reinterpret_cast<ScoreWeightsView*>(TheWritableGlobalData)->unitsVetted;
  record.score+=realFC;
 }
 ScoredKillTracker **it=*reinterpret_cast<ScoredKillTracker***>(reinterpret_cast<char*>(this)+0x304);
 ScoredKillTracker **end=*reinterpret_cast<ScoredKillTracker***>(reinterpret_cast<char*>(this)+0x308);
 while(it!=end){(*it)->friend_update();++it;}
}
