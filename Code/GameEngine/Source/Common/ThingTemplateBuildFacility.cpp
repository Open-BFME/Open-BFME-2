// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?getBuildFacilityTemplate@ThingTemplate@@QBEPBV1@PBVPlayer@@@Z @0x0033A97F 38B ThingTemplate prereq vector +0x324 element 0x24 tailcalls ProductionPrerequisite::getExistingBuildFacilityTemplate callers 0x0033AB48 donor ThingTemplate.cpp Zero Hour
#include <math.h>
#include <vector>
#include "GameLogicObjectLookupView.h"
// Whole-file recovery: keep the existing frame-rate data owner, rather than
// assert an original target variable name. Its mutable int ABI is retail-proven.

typedef int Int;

class Player;
class ThingTemplate;

class ProductionPrerequisite
{
public:
	const ThingTemplate *getExistingBuildFacilityTemplate(const Player *player) const;
private:
	char m_unmodelled[0x24];
};

class ThingTemplate
{
public:
	const ThingTemplate *getBuildFacilityTemplate(const Player *player) const;
	// Native getter and facility body read start/end at +324/+328 and
 // divide by 36. The old vector::size owner divides by 24; read this
 // target-supported range directly without offering that conflicting copy.
 Int getPrereqCount() const {
  const ProductionPrerequisite *const *p =
   reinterpret_cast<const ProductionPrerequisite *const *>(&m_prereqInfo);
  return p[1] - p[0];
 }
 int calcTimeToBuild(const Player *player,int objectCarrier,int timeOverride)const;
private:
	char beforeName[0x64];
 char name[4];
 char beforeKind[0x108-0x68];
 unsigned char kind;
 char beforePrereqs[0x324-0x109];
	_STL::vector<ProductionPrerequisite> m_prereqInfo;
 char beforeTime[0x4dc-0x330];
 float time;
 char beforeCompletion[0x5f3-0x4e0];
 signed char completion;
};

const ThingTemplate *ThingTemplate::getBuildFacilityTemplate(const Player *player) const
{
	if (getPrereqCount() > 0)
	{
		return m_prereqInfo[0].getExistingBuildFacilityTemplate(player);
	}
	else
	{
		return 0;
	}
}

static inline const float &buildMax(const float &a,const float &b){return a>b?a:b;}
static inline const float &buildMin(const float &a,const float &b){return a<b?a:b;}
// Native 0x0033AA1F..0x0033AC7F, 608 bytes, RET 12.
// ZH ThingTemplate::calcTimeToBuild (the donor retained in ThingTemplate.cpp)
// supplies production/energy/factory semantics. WB 0x00BCBAA0 corroborates
// the optional module and multiplayer/difficulty paths; its name is unknown.
// Retail establishes all offsets, slot 27, signed completion byte, integer
// override and final frame scaling. Existing address-derived ABI is retained;
// objectCarrier is an integer ABI carrier interpreted as Object* here.
// The final floor call is the CRT import. Its result is rounded with the
// existing engine fast_float2long_round idiom: x87 FISTP is required by native,
// while a C++ cast calls _ftol2. This is an x87 codegen constraint, not a lift.
// Global owner names and callee contracts are the existing ledger providers;
// RegistryBuildView::factor has no independently recovered semantic name.
static inline float buildFloor(float f){return (float)floor(f);}
class ThingTemplate; class Player; class GlobalData; class GameLogic;
class Overridable;
class Rva0033A68A {public: Overridable *rva0033A68A();};
class Handicap {public: enum HandicapType {BUILDCOST,BUILDTIME}; float getHandicap(HandicapType,const ThingTemplate*)const; char opaque[16];};
class Rva002AE98B {public: float rva002AE98B(const class AsciiString*);};
class Energy {public: float getEnergySupplyRatio()const;};
struct PlayerBuildView {char before[0x3c];Handicap handicap; char after[0x1bc-0x4c];Energy energy;};
#include "../../Include/Common/Player.h"
class Object {public:void *rva0028BC94();};
class BuildTimeModule {public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
 virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
 virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
 virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
 virtual void slot24(); virtual void slot25(); virtual void slot26();
 virtual float multiplier(const ThingTemplate*);
};
#include "../../Include/Common/MultiPlayMults.h"
struct GlobalDataBuildView {char before[0xa74];float minimum,maximum,penalty,multiple;char after[0xec4-0xa84];MultiPlayMults multiplay;};
extern GlobalData *TheWritableGlobalData;
// Existing owned multiplayer predicate; the shared header owns GameLogic.
#include "../../Include/Common/BfmeGlob939D.h"
extern GameLogic *TheGameLogic;
#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../Include/Common/Rva002A9BF2.h"
struct Rva002A8AB1Record;
#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
struct RegistryBuildView {char before[0x854];float factor;};
extern int BfmeLogicFramesPerSecond;
__forceinline long fast_float2long_round(float f) {
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}

int ThingTemplate::calcTimeToBuild(const Player *player,int objectCarrier,int timeOverride)const {
 int buildTime = timeOverride == -1 ? ((const ThingTemplate *)((Rva0033A68A *)this)->rva0033A68A())->time : timeOverride;
 buildTime *= ((const PlayerBuildView *)player)->handicap.getHandicap(Handicap::BUILDTIME,this);
 float factionModifier = 1.0f + ((Rva002AE98B *)player)->rva002AE98B((const AsciiString*)name);
 buildTime *= factionModifier;
 Object *object=(Object *)objectCarrier;
 if(object) {BuildTimeModule *module=(BuildTimeModule *)object->rva0028BC94();if(module)buildTime *= module->multiplier(this);}
 float energyPercent=((const PlayerBuildView *)player)->energy.getEnergySupplyRatio();
 if(energyPercent>1.0f)energyPercent=1.0f;
 float shortage=1.0f-energyPercent;
 shortage *= ((const GlobalDataBuildView *)TheWritableGlobalData)->penalty;
 float rate=1.0f-shortage;
 rate = buildMax(rate,((const GlobalDataBuildView *)TheWritableGlobalData)->minimum);
 if(energyPercent<1.0f)rate=buildMin(rate,((const GlobalDataBuildView *)TheWritableGlobalData)->maximum);
 if(rate<=0.0f)rate=0.01f;
 buildTime /= rate;
 if(completion==1) {
  const ThingTemplate *facility=getBuildFacilityTemplate(player);int count=0;
  if(facility) {
   player->countObjectsByThingTemplate(1,&facility,false,&count,true);
   float mult=((const GlobalDataBuildView *)TheWritableGlobalData)->multiple;
   if(mult>0.0f)for(int i=0;i<count-1;i++)buildTime*=mult;
  }
 }
 if(((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()) {
  int count=ThePlayerList->rva002A7C0B(false);
  float mult=kind&0x80 ? ((const GlobalDataBuildView *)TheWritableGlobalData)->multiplay.getBuildingSpeedMult(count) : ((const GlobalDataBuildView *)TheWritableGlobalData)->multiplay.getUnitSpeedMult(count);
  buildTime*=mult;
 }
 if(((Rva002A9BF2 *)player)->rva002A9BF2()==(void *)3 && TheSkirmishAIManager->rva002A8AB1((void*)player)) {
  float mult=((const RegistryBuildView *)TheSkirmishAIManager)->factor < 1.0f ? ((const RegistryBuildView *)TheSkirmishAIManager)->factor : 1.0f;
  return fast_float2long_round(buildFloor((1.0f-mult)*(buildTime*BfmeLogicFramesPerSecond)));
 }
 return fast_float2long_round(buildFloor((float)(buildTime*BfmeLogicFramesPerSecond)));
}
