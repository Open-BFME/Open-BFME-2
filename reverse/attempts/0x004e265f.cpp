// ?rva004E265F@Rva00319CED@@QAE?AVUnicodeString@@H@Z
// partial score=0.6531165311653117 date=2026-10-10
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
class Rva004E3184:public Snapshot{public:Rva004E3184(int);virtual ~Rva004E3184();
 Rva004E3184(const Rva004E3184&);
 const Image *GetButtonImage(int);
 const Image *GetPortraitImage(int);
 static const FieldParse m_fieldParseTable[];
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer*);
 AsciiString m_04,m_08,m_0c,m_10,m_14,m_18,m_1c;
 float m_20,m_24;
 AsciiString m_28,m_2c,m_30,m_34;
 _STL::vector<AsciiString> m_38;
 float m_44;int m_48,m_4c;AsciiString m_50;bool m_54,m_55;
};
Rva004E3184::Rva004E3184(int index):m_20(0.0f),m_24(0.0f),m_2c(AsciiString::TheEmptyString),m_48(1),m_4c(index),m_54(false),m_55(true){
 if(TheLivingWorldManager) m_44=((const SpawnManagerCostView *)TheLivingWorldManager)->revivalCost;
 else m_44=5.0f;
}

Rva004E3184::~Rva004E3184() {}
void Rva004E3184::loadPostProcess() {}
const char *Rva004E3184::GetSnapshotName()const{return "SpawnArmy";}
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "Coord2D.h"

void Rva004E12D7Parse(void *a, void *b);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void Rva004E3184::xfer(Xfer *stream)
{
 Xfer &xfer=*stream;
	Xfer::Version version(1, 3);
	xfer == version;
	Rva004E12D7Parse(&xfer, &m_4c);
	xfer == m_04;
	xfer == m_08;
	xfer == *(Coord2D *)&m_20;
	xfer == m_2c;
	xfer == m_30;
	xfer == m_34;
	xferAsciiStringVector(&xfer, &m_38);
	xfer == m_54;
	xfer == m_50;
	xfer == m_44;
	xfer == m_55;
	if (version.m_minimum >= 2) {
		xfer == m_18;
	}
	if (version.m_minimum >= 3) {
		xfer == m_28;
		xfer == m_1c;
	}
}

// Native 4E324D/135B and its WB128B450 twin create this complete 88-byte
// record with TheLivingWorldLogic's incremented ID, parse it through C616C0,
// append it to the act's +0x20 collection, then destroy the temporary.
// The reused error literal does not establish an original callback name.
// Table C616C0: all 304 bytes, 18 full strings and callback bindings,
// all offsets, zero user data and the null terminator independently verified.
class INI { public:
 void initFromINI(void*,const FieldParse*);
 static void parseAsciiString(INI*,void*,void*,const void*);
 static void parseCoord2D(INI*,void*,void*,const void*);
 static void parseCoord3D(INI*,void*,void*,const void*);
 static void dup_002F0F7(INI*,void*,void*,const void*);
 static void parseAsciiStringVector(INI*,void*,void*,const void*);
 static void parseBool(INI*,void*,void*,const void*);
 static void parseReal(INI*,void*,void*,const void*);
 static void parseInt(INI*,void*,void*,const void*);
};
struct FieldParse { const char *name; void (*parse)(INI*,void*,void*,const void*); const void *userData; int offset; };
const FieldParse Rva004E3184::m_fieldParseTable[]={
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
#include "Common/INIException.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B3171BumpCounter { public:int bump(); };
struct BfmePod88;
class Rva00566AB7 { public:void rva00566AB7(const BfmePod88&); };
void Rva004E324DParse(INI *ini,void *instance,void*,const void*) {
 if(!ini || !instance) throw INIException(3,"ParseArmyMoveToBlock::Invalid data passed in.");
 Rva004E3184 record(((Rva002B3171BumpCounter*)TheLivingWorldLogic)->bump());
 ini->initFromINI(&record,Rva004E3184::m_fieldParseTable);
 ((Rva00566AB7*)instance)->rva00566AB7((const BfmePod88&)record);
}

class ImageCollection { public:const Image *findImageByName(const AsciiString&); };
extern ImageCollection *TheMappedImageCollection;
class CreateAHeroHero;
class CreateAHeroManager { public:const AsciiString &GetButtonImageName(const CreateAHeroHero*); };
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva00319CED { public:void *rva004E23E2(); UnicodeString rva004E25AF(int); UnicodeString rva004E265F(int); int rva004E1755(); bool rva00319CED(); };
struct Rva002B2579Result;
class Rva002BA8F1Logic { public:Rva002B2579Result *rva002B2579(int); };
class Rva002E2903Player;
class Rva004E0705 { public:Rva002E2903Player *rva004E0705(); };
class Rva002E06B8 { public:void *rva002E06EF(); };

// Complete native body and associated EH graph verified against retail.
const Image *Rva004E3184::GetButtonImage(int id) {
 static const Image *missing=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 void *thing=((Rva00319CED*)this)->rva004E23E2();
 if(!thing)return missing;
 const Image *image;
 if(*((unsigned char*)thing+0x11f)&0x40) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return missing;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return missing;
  void *hero=((Rva002E06B8*)player)->rva002E06EF();
  if(!hero)return missing;
  image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName((const CreateAHeroHero*)hero));
 } else image=TheMappedImageCollection->findImageByName(m_0c);
 return image?image:missing;
}

class ThingTemplate { public:const Image *getButtonImage(); };

// Complete native body and associated EH graph verified against retail.
const Image *Rva004E3184::GetPortraitImage(int id) {
 static const Image *missing=TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
 void *thing=((Rva00319CED*)this)->rva004E23E2();
 if(!thing)return missing;
 const Image *image;
 if(*((unsigned char*)thing+0x11f)&0x40) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return missing;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return missing;
  void *hero=((Rva002E06B8*)player)->rva002E06EF();
  if(!hero)return missing;
  image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName((const CreateAHeroHero*)hero));
 } else image=((ThingTemplate*)thing)->getButtonImage();
 return image?image:missing;
}

// WB128BD80 identifies SpawnArmy::GetButtonTitle. Native 4E25AF/176B
// returns UnicodeString by value, including the hidden output pointer and
// every EH state transition. The old pointer-return interpretation missed
// those states. Preserve the existing Rva00319CED binding used by callers.
// The native AsciiString text-fetch overload occupies vtable slot0x38;
// this interface and ABI also match AptMapPreview's existing consumers.
class GameTextInterface { public:
 virtual ~GameTextInterface();
 virtual void slot04()=0;virtual void slot08()=0;virtual void slot0C()=0;
 virtual void slot10()=0;virtual void slot14()=0;virtual void slot18()=0;
 virtual void slot1C()=0;virtual void slot20()=0;virtual void reset()=0;
 virtual void slot28()=0;virtual void slot2C()=0;virtual void slot30()=0;virtual void slot34()=0;
 virtual UnicodeString fetch(const char*,bool* =0)=0;
 virtual UnicodeString fetch(const AsciiString&,bool* =0)=0;
};
extern GameTextInterface *TheGameText;
UnicodeString Rva00319CED::rva004E25AF(int id) {
 UnicodeString title=TheGameText->fetch(((Rva004E3184*)this)->m_10);
 void *thing=rva004E23E2();
 if(thing && (*((unsigned char*)thing+0x11f)&0x40)) {
  Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
  if(!building)return title;
  Rva002E2903Player *player=((Rva004E0705*)building)->rva004E0705();
  if(!player)return title;
  void *hero=((Rva002E06B8*)player)->rva002E06EF();
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

class LivingWorldPlayer { public:
 bool HasArmyQueuedInAnyBuilding(void *,int *,int);
 bool rva002E12F3(int);
 void *FindArmyWithHero(void *,int);
};
class Rva0020E89C { public:UnicodeString rva0020E89C(); };
class Rva00318C32Ret;
class Rva00318C79Owner { public:Rva00318C32Ret *rva00318C32(); };
struct ArmyHelpBuildingView { unsigned char pad[0x24]; Rva0020E89C *region; };

UnicodeString Rva00319CED::rva004E265F(int id)
{
 Rva004E3184 *spawn=(Rva004E3184 *)this;
 UnicodeString help=TheGameText->fetch(spawn->m_14);
 static AsciiString singular("CONTROLBAR:LW_Unit_BuildTimeAndCostSingular");
 static AsciiString plural("CONTROLBAR:LW_Unit_BuildTimeAndCostPlural");
 bool found=false;
 UnicodeString cost;
 if(spawn->m_48==1)cost=TheGameText->fetch(singular,&found);
 else cost=TheGameText->fetch(plural,&found);
 if(!found)return help;
 int duration=spawn->m_48;
 cost.format(&cost,duration,rva004E1755());
 help+=cost;
 if(!rva00319CED())return help;
 void *thing=rva004E23E2();
 if(!thing || !(*((unsigned char*)thing+0x113)&4))return help;
 Rva002B2579Result *building=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(id);
 if(!building)return help;
 LivingWorldPlayer *player=(LivingWorldPlayer *)((Rva004E0705*)building)->rva004E0705();
 if(!player)return help;
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
      if(!army || !(region=army->rva00318C32()))return help;
      {
       msg.format(&msg,((Rva0020E89C*)region)->rva0020E89C().str());
      }
      help+=msg;
     }
 return help;
}
