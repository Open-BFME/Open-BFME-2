// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/iniexception
// SpawnArmy: native 88-byte record, named by WB LivingWorldCampaignObjects.cpp
// constructor 128AFA0 and retail virtual name "SpawnArmy" at 4E30C6.
// Retain the existing address-class binding used by its verified callers.
// Native C61F28 has four Snapshot slots: deleting destructor, loadPostProcess,
// GetSnapshotName and xfer. The real STLport vector supplies the constructor's
// allocator lifetime; a three-pointer declaration alone emits an extra byte.
// Constructor 4E30D5/175B, copy 4E2F9F/295B, destructor 4E3184/201B and
// xfer 4E3991/221B each match their complete retail bodies; all three emitted
// constructor/destructor exception tables are exact. Target field offsets and
// defaults are independent of the BFME1 9cbfb551fe20 semantic parser lead.
// stlport
#include <memory>
#include <vector>
#include "ascii_string.h"
// Keep the real vector destructor provider and its destruction helpers.
// The ordinary member bodies retain their native inline releaseBuffer calls.
extern template _STL::vector<AsciiString, _STL::allocator<AsciiString> >::~vector();

#include "unicode_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class LivingWorldManager;
struct SpawnManagerCostView{unsigned char opaque[0xf0];float revivalCost;};
extern LivingWorldManager *TheLivingWorldManager;
struct FieldParse;
class Image;
class SpawnArmy:public Snapshot{public:SpawnArmy(int);virtual ~SpawnArmy();
	void *rva004E23E2();
	UnicodeString rva004E25AF(int);
	UnicodeString GetButtonHelp(int);
	int rva004E1755();
	bool rva00319CED();
 SpawnArmy(const SpawnArmy&);
 const Image *GetButtonImage(int);
 const Image *GetPortraitImage(int);
 static const FieldParse m_fieldParseTable[];
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer*);
 AsciiString m_04,m_08,m_constructButtonImage,m_constructButtonTitle,m_14,m_18,m_1c;
 float m_position,m_24;
 AsciiString m_initialRegion,m_playerArmy,m_palantirMovie,m_iconSize;
 _STL::vector<AsciiString> m_spawnForTemplates;
 float m_moveSpeed;int m_buildTime,m_4c;AsciiString m_heroTemplateName;bool m_isCity,m_spawnAtActStart;
};
SpawnArmy::SpawnArmy(int index):m_position(0.0f),m_24(0.0f),m_playerArmy(AsciiString::TheEmptyString),m_buildTime(1),m_4c(index),m_isCity(false),m_spawnAtActStart(true){
 if(TheLivingWorldManager) m_moveSpeed=((const SpawnManagerCostView *)TheLivingWorldManager)->revivalCost;
 else m_moveSpeed=5.0f;
}

SpawnArmy::~SpawnArmy() {}
void SpawnArmy::loadPostProcess() {}
const char *SpawnArmy::GetSnapshotName()const{return "SpawnArmy";}
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

#include "Coord2D.h"

void Rva004E12D7Parse(void *a, void *b);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void SpawnArmy::xfer(Xfer *stream)
{
 Xfer &xfer=*stream;
	Xfer::Version version(1, 3);
	xfer == version;
	Rva004E12D7Parse(&xfer, &m_4c);
	xfer == m_04;
	xfer == m_08;
	xfer == *(Coord2D *)&m_position;
	xfer == m_playerArmy;
	xfer == m_palantirMovie;
	xfer == m_iconSize;
	xferAsciiStringVector(&xfer, &m_spawnForTemplates);
	xfer == m_isCity;
	xfer == m_heroTemplateName;
	xfer == m_moveSpeed;
	xfer == m_spawnAtActStart;
	if (version.m_minimum >= 2) {
		xfer == m_18;
	}
	if (version.m_minimum >= 3) {
		xfer == m_initialRegion;
		xfer == m_1c;
	}
}

// Native 4E324D/135B and its WB128B450 twin create this complete 88-byte
// record with TheLivingWorldLogic's incremented ID, parse it through C616C0,
// append it to the act's +0x20 collection, then destroy the temporary.
// The reused error literal does not establish an original callback name.
// Table C616C0: all 304 bytes, 18 full strings and callback bindings,
// all offsets, zero user data and the null terminator independently verified.
#include "../../../../Include/Common/INI/INI.h"
#include "../../../../Include/Common/INI/FieldParse.h"
const FieldParse SpawnArmy::m_fieldParseTable[]={
 {"Icon",INI::parseAsciiString,0,0x04},
 {"Banner",INI::parseAsciiString,0,0x08},
 {"Position",INI::parseCoord2D,0,0x20},
 {"InitialRegion",INI::parseAsciiString,0,0x28},
 {"PlayerArmy",INI::parseAsciiString,0,0x2c},
 {"PalantirMovie",INI::parseAsciiString,0,0x30},
 {"IconSize",INI::parseAsciiString,0,0x34},
 {"SpawnForTemplates",INI::parseAsciiStringVector,0,0x38},
 {"ScriptingName",INI::parseAsciiString,0,0x18},
 {"TooltipStringTag",INI::parseAsciiString,0,0x1c},
 {"IsCity",INI::parseBool,0,0x54},
 {"HeroTemplateName",INI::parseAsciiString,0,0x50},
 {"MoveSpeed",INI::parseReal,0,0x44},
 {"BuildTime",INI::parseInt,0,0x48},
 {"ConstructButtonImage",INI::parseAsciiString,0,0x0c},
 {"ConstructButtonTitle",INI::parseAsciiString,0,0x10},
 {"ConstructButtonHelp",INI::parseAsciiString,0,0x14},
 {"SpawnAtActStart",INI::parseBool,0,0x55},
 {0,0,0,0}
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B3171BumpCounter { public:int bump(); };
struct BfmePod88 { int a[22]; };
class Rva00566AB7 { public:void rva00566AB7(const BfmePod88&); };
// 0x004E3BD8 90B: the same record parsed straight into a vector<BfmePod88>
// (the S3L field table's "ArmyToSpawn" callback at 0x004E3BD8, declared in
// GapBodiesS3L.cpp). Retail appends through the out-of-line push_back, so the
// member stays declaration-only here.
namespace _STL { template <> void vector<BfmePod88, allocator<BfmePod88> >::push_back(const BfmePod88 &); }
void rva004E3BD8(INI *ini,int,_STL::vector<BfmePod88> *vec) {
 SpawnArmy record(((Rva002B3171BumpCounter*)TheLivingWorldLogic)->bump());
 ini->initFromINI(&record,SpawnArmy::m_fieldParseTable);
 vec->push_back((const BfmePod88&)record);
}
void Rva004E324DParse(INI *ini,void *instance,void*,const void*) {
 if(!ini || !instance) throw INIException(3,"ParseArmyMoveToBlock::Invalid data passed in.");
 SpawnArmy record(((Rva002B3171BumpCounter*)TheLivingWorldLogic)->bump());
 ini->initFromINI(&record,SpawnArmy::m_fieldParseTable);
 ((Rva00566AB7*)instance)->rva00566AB7((const BfmePod88&)record);
}

#include "../../../../Include/GameClient/Image.h"
extern ImageCollection *TheMappedImageCollection;
class CreateAHeroHero;
#include "../../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;
struct Rva002B2579Result;
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class Rva002E2903Player;
#include "../../../../Include/GameLogic/Rva004E0705.h"
#include "../../../../Include/GameLogic/LivingWorldPlayer.h"

// Complete native body and associated EH graph verified against retail.
const Image *SpawnArmy::GetButtonImage(int id) {
 static const Image *missing=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 void *thing=((SpawnArmy*)this)->rva004E23E2();
 if(!thing)return missing;
 const Image *image;
 if(*((unsigned char*)thing+0x11f)&0x40) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return missing;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return missing;
  void *hero=((LivingWorldPlayer*)player)->rva002E06EF();
  if(!hero)return missing;
  image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName((const CreateAHeroHero*)hero));
 } else image=TheMappedImageCollection->findImageByName(m_constructButtonImage);
 return image?image:missing;
}

#include "../../../../Include/Common/ThingTemplate.h"

// Complete native body and associated EH graph verified against retail.
const Image *SpawnArmy::GetPortraitImage(int id) {
 static const Image *missing=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 void *thing=((SpawnArmy*)this)->rva004E23E2();
 if(!thing)return missing;
 const Image *image;
 if(*((unsigned char*)thing+0x11f)&0x40) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return missing;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return missing;
  void *hero=((LivingWorldPlayer*)player)->rva002E06EF();
  if(!hero)return missing;
  image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName((const CreateAHeroHero*)hero));
 } else image=((ThingTemplate*)thing)->getButtonImage();
 return image?image:missing;
}

// WB128BD80 identifies SpawnArmy::GetButtonTitle. Native 4E25AF/176B
// returns UnicodeString by value, including the hidden output pointer and
// every EH state transition. The old pointer-return interpretation missed
// those states. Preserve the existing SpawnArmy binding used by callers.
// The native AsciiString text-fetch overload occupies vtable slot0x38;
// this interface and ABI also match AptMapPreview's existing consumers.
#include "../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
UnicodeString SpawnArmy::rva004E25AF(int id) {
 UnicodeString title=TheGameText->fetch(((SpawnArmy*)this)->m_constructButtonTitle);
 void *thing=rva004E23E2();
 if(thing && (*((unsigned char*)thing+0x11f)&0x40)) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return title;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return title;
  void *hero=((LivingWorldPlayer*)player)->rva002E06EF();
  if(!hero)return title;
  return *(const UnicodeString*)((char*)hero+8);
 }
 return title;
}

// Native MoveCamera parser 4E141D/110B, constructor 4E13EB/43B,
// destructor 4E1416/7B and deleting destructor 4E186D/28B.
// WB128D8A0 and the complete target body independently establish the parser
// and its 32-byte temporary; BFME1 9cbfb551fe20 supplies the semantic lead.
// C618CC has one deleting-destructor slot, followed by the SummaryEvent
// string. This record has no Snapshot base. Keep its existing address name.
// Retail's deleting destructor calls the seven-byte destructor out of line;
// noinline preserves that witnessed call instead of folding its vptr store.
// Keeping the constructor visible also preserves EDX for the parser's EH
// state write. Normal C++ throw and the complete EH graph match retail.
// Table C61940: all 96 bytes, five full strings, callback bindings, offsets,
// zero user data and null terminator independently verified. The duration
// callback retains its existing opaque name, not the distinct 338B30 body.
class Rva004E13EB
{
public:
	Rva004E13EB();
	__declspec(noinline) virtual ~Rva004E13EB();
	static const FieldParse m_fieldParseTable[];
	int m04;
	float m08;
	float m0c;
	float m10;
	float m14;
	int m18;
	unsigned char m1c;
};

class Rva003A6F70
{
	char m_pad[0x20];
};

class Rva00566547Owner
{
public:
	void append(const Rva003A6F70 &record);
};


Rva004E13EB::Rva004E13EB():m04(0),m08(0.0f),m0c(0.0f),m10(0.0f),m14(0.0f),m18(0),m1c(0) {}
Rva004E13EB::~Rva004E13EB() {}

const FieldParse Rva004E13EB::m_fieldParseTable[]={
 {"DelayFromActStart",INI::dup_002F0F7,0,0x04},
 {"Position",INI::parseCoord3D,0,0x08},
 {"ViewAngle",INI::parseReal,0,0x14},
 {"ScrollTime",INI::dup_002F0F7,0,0x18},
 {"SummaryEvent",INI::parseBool,0,0x1c},
 {0,0,0,0}
};

void Rva004E141DParse(INI *ini,void *instance,void*,const void*) {
 if(!ini || !instance) throw INIException(3,"ParseMoveCameraBlock::Invalid data passed in.");
 Rva004E13EB record;
 ini->initFromINI(&record,Rva004E13EB::m_fieldParseTable);
 ((Rva00566547Owner*)instance)->append((const Rva003A6F70&)record);
}

class Rva0020E89C { public:UnicodeString rva0020E89C(); };
class Rva00318C32Ret;
#include "../../../../Include/GameLogic/Rva00318C79Owner.h"
struct ArmyHelpBuildingView { unsigned char pad[0x24]; Rva0020E89C *region; };

// 0x004E265F 738B: the hero-unit help text of the army spawn record: the
// build time and cost line, then the already-queued or already-built notice.
// Layout lessons from the WB debug shape: every early exit is its own `return
// help` site (the null army and null region tests are two ifs, not one ||) and
// the queued-building counter sits in its own block, which lets cl share its
// slot with the fetch return temporary like retail.
UnicodeString SpawnArmy::GetButtonHelp(int id)
{
 SpawnArmy *spawn=(SpawnArmy *)this;
 UnicodeString help=TheGameText->fetch(spawn->m_14);
 static AsciiString singular("CONTROLBAR:LW_Unit_BuildTimeAndCostSingular");
 static AsciiString plural("CONTROLBAR:LW_Unit_BuildTimeAndCostPlural");
 bool found=false;
 UnicodeString cost;
 if(spawn->m_buildTime==1)cost=TheGameText->fetch(singular,&found);
 else cost=TheGameText->fetch(plural,&found);
 if(!found)return help;
 int duration=spawn->m_buildTime;
 cost.format(&cost,duration,rva004E1755());
 help+=cost;
 if(!rva00319CED())return help;
 void *thing=rva004E23E2();
 if(!thing || !(*((unsigned char*)thing+0x113)&4))return help;
 Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
 if(!building)return help;
 LivingWorldPlayer *player=(LivingWorldPlayer *)((Rva004E0705*)building)->rva004E0705();
 if(!player)return help;
     {
     int queuedBuilding=0;
     if(player->HasArmyQueuedInAnyBuilding((void*)spawn->m_4c,&queuedBuilding,id)) {
      UnicodeString msg=TheGameText->fetch("CONTROLBAR:LW_HeroUnitAlreadyBeingTrained");
      ArmyHelpBuildingView *queued=(ArmyHelpBuildingView*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(queuedBuilding);
      if(queued && queued->region) {
       msg.format(&msg,queued->region->rva0020E89C().str());
      }
      help+=msg;
     } else if(!player->rva002E12F3(spawn->m_4c)) {
      UnicodeString msg=TheGameText->fetch("CONTROLBAR:LW_HeroUnitAlreadyBuilt");
      Rva00318C79Owner *army=(Rva00318C79Owner*)player->FindArmyWithHero(thing,spawn->m_4c);
      Rva00318C32Ret *region;
      if(!army)return help;
      if(!(region=army->rva00318C32()))return help;
      {
       msg.format(&msg,((Rva0020E89C*)region)->rva0020E89C().str());
      }
      help+=msg;
     }
     }
 return help;
}

// Native0x791c0a complete1B action: Independent1B RET action in the whole738B help parent native EH graph. The neighbouring24B conditional cleanup branches to this named entry; disjoint extents prevent duplicate coverage.
// Whole native parent and complete EH graph independently prove ownership.

// Native0x791bf2 complete24B action: Complete24B conditional hidden-output UnicodeString cleanup in the whole738B help parent. It tests and clears mask1 atEBP-28 then tail-jumps with return bufferEBP+8 to same-object whole5B destructor5B804E or branches to independently named1B RET791C0A. Replaces the separately retired standalone assembly range.
// Whole native parent and complete EH graph independently prove ownership.

// Native0x791b4f complete13B action: Complete13B static-image initialization failure guard cleanup in the whole208B GetButtonImage parent. Both DIR32 relocations bind the same actual compiler-owned guard atVA E04438. Clear bit0 and preserve remaining bits; no callee or address-named global added.
// Whole native parent and complete EH graph independently prove ownership.
