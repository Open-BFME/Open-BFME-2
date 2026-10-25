// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source
// stlport
#include <vector>
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
// GetRandomPlayablePlayerTemplateIndex: native 0x0052BBF3..0x0052BCAB (184B).
// WB names this file-static helper at 0x0133BD80; the native call at
// 0x0052C535 supplies hero-info in EAX, with plain RET at 0x0052BCAA.
// A genuine same-TU CreatePlayers body preserves that private register ABI.
// Native hero class/subclass accesses at +0x0C/+0x10 feed the existing
// CreateAHeroManager::GetFactionMaskType, and bit testing rejects incompatible
// factions before accepting the random index. The path literal and line 196
// are read from retail, including its double backslashes.
// BFME1 donor a10e4cba LivingWorldCampaign.cpp was read whole: it has no
// corresponding helper or CreatePlayers body. Reconstruction uses WB/native
// target evidence; existing callee/type labels retain their ledger evidence.
// Private EAX input is target evidence from the same-TU CreatePlayers caller.
// Offsets, 7-bit faction mask, randomized retry loop and exact path are retail evidence.
extern "C" void *memset(void *,int,unsigned int);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// GameSlotHeroInfo reuses the target-owned slot view from GameLogicInit.cpp.
// Its label is a reconstruction; native class/subclass offsets are independently read here.
struct GameSlotHeroInfo { char prefix[12]; unsigned heroClass; unsigned heroSubclass; };
class CreateAHeroManager { public: void *GetFactionMaskType(unsigned,unsigned); };
extern CreateAHeroManager *TheCreateAHeroManager;
class PlayerTemplate { public: int rva001FD234() const; AsciiString getName() const; char pad[0x151]; bool playable; char rest[0x1dc-0x152]; };
class PlayerTemplateStore { public: const PlayerTemplate *getNthPlayerTemplate(int) const; const PlayerTemplate *findPlayerTemplate(NameKeyType) const; char pad[12]; PlayerTemplate *first,*last; };
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameLogicRandomValue(int,int,char*,int);
struct HeroFactionMask {
 unsigned words[1];
 HeroFactionMask(){memset(words,0,sizeof(words));}
 bool any() const { for(unsigned i=0;i<1;++i) if(words[i]) return true; return false; }
 bool test(unsigned bit) const { return (words[bit>>5] & (1U<<(bit&31)))!=0; }
};
static __declspec(noinline) int GetRandomPlayablePlayerTemplateIndex(const GameSlotHeroInfo *heroInfo)
{
 HeroFactionMask heroFactions;
 if(heroInfo){
  unsigned subclass=heroInfo->heroSubclass;
  unsigned factionClass=heroInfo->heroClass;
  _ReadWriteBarrier();
  heroFactions.words[0]=*static_cast<const unsigned *>(TheCreateAHeroManager->GetFactionMaskType(factionClass,subclass));
  if(!heroFactions.any())heroInfo=0;
 }
 int index;
 for(;;) {
  int count=ThePlayerTemplateStore->last-ThePlayerTemplateStore->first;
  index=GetGameLogicRandomValue(0,count-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldCampaign.cpp",196);
  const PlayerTemplate *player=ThePlayerTemplateStore->getNthPlayerTemplate(index);
  if(!player || !player->playable)index=-1;
  else if(heroInfo && !heroFactions.test((unsigned)player->rva001FD234()))continue;
  if(index!=-1)break;
 }
 return index;
}
// Reused provider declarations retain address-qualified provisional identities.
#include "ascii_string.h"
#include "unicode_string.h"

class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class GameSlot {
public:
 bool isHuman() const; void setPlayerTemplate(int);
 char pad00[4]; int state; char pad08[4]; int color,start,at14,templateIndex,team,at20;
 char pad24[12]; UnicodeString name; char pad34[0x60-0x34]; bool hasHero;
 char pad61[3]; GameSlotHeroInfo heroInfo;
};
class GameInfo {
public:
 virtual ~GameInfo();
 virtual void gi04(); virtual void gi08(); virtual void gi0C();
 virtual void gi10(); virtual void gi14(); virtual void gi18();
 virtual void gi1C(); virtual void gi20(); virtual void gi24();
 virtual void gi28(); virtual void gi2C(); virtual void gi30();
 virtual int getLocalSlotNum() const; // Same existing GameLogicInit pointer view; native vslot 0x34.
 GameSlot *getSlot(int);
};
extern GameInfo *TheGameInfo;
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
#include "Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva00210C66CmpBoolField {public: bool get() const;};
class Glo012F1028Type {public: void rva002B7D91();};
struct Rva002BA8F1Input;
struct Rva002BA8F1Slot;
class Rva002E2903Player;
class Rva002BA8F1Logic {public:
 Rva002E2903Player *GetPlayerAtIndex(int);
};
class Rva002E067DDwordSlot {public: void set(int);};
class Rva0020E89C {public:char pad[0x14]; AsciiString name;};
class Rva0020EAF6View {public: Rva0020E89C *rva0020EAF6(int);};
class LivingWorldLogic {public:
 void ValidatePlayers(); void AddPlayer(Rva002BA8F1Input *,bool,int,Rva002BA8F1Slot *); char pad[0xb0]; Rva0020EAF6View *regions;
};
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva002E1904Entry;
class Rva002E1904Lookup {public: Rva002E1904Entry *find(const AsciiString &);};
class Rva002E18C3Lookup;
extern Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
class Rva002E0F1E {public: virtual ~Rva002E0F1E();};
struct Rva002E0EF7 {
 void *vtable;
 int m_04,m_08,m_0C,m_10,m_14,m_18,m_1C,m_20; unsigned char m_24;
 Rva002E0EF7();
 ~Rva002E0EF7() { ((Rva002E0F1E *)this)->Rva002E0F1E::~Rva002E0F1E(); }
 AsciiString &narrow(int offset) {return *(AsciiString *)((char *)this+offset);}
 UnicodeString &wide() {return *(UnicodeString *)((char *)this+4);}
};
int Rva0052C06CGet(GameInfo *);
// A campaign's 184-byte mission records (+0x0C begin, +0x10 end); the
// byte at +0xB4 marks a record the step below selects.
struct LivingWorldCampaignRecord
{
	char m_pad00[0xB4];
	bool m_selected;						// +0xB4
	char m_padB5[0xB8 - 0xB5];
};

struct LivingWorldCampaignRecords
{
	LivingWorldCampaignRecord *m_start;
	LivingWorldCampaignRecord *m_finish;
	LivingWorldCampaignRecord *m_endOfStorage;

	unsigned int size() const { return m_finish - m_start; }
	LivingWorldCampaignRecord &operator[](unsigned int i) { return m_start[i]; }
};

class LivingWorldCampaign {
public:
 LivingWorldCampaign(const AsciiString &name);
 void rva0052C0C8();
 static void ParseLivingWorldCampaignBlock(class INI *ini);
 void CreatePlayers(); int AdjustStartingPositionForScenario(int);
 char pad00[0x0c]; LivingWorldCampaignRecords m_records; int m_currentIndex;
 char pad1c[8]; _STL::vector<Rva002E0EF7> players; AsciiString localName;
 char pad34[0x4c-0x34]; unsigned char fromCampaign;
};
// CreatePlayers: native 0x0052C45E..0x0052C72B (717B), plain RET.
// WB 0x0133B280 names this method and LivingWorldCampaign.cpp (256..365).
// Native fields are a 40B record vector at +0x24, local-name string +0x30,
// and byte flag +0x4C. The existing default record ctor and qualified dtor
// establish its 40B lifetime; names of its unreconciled record fields remain
// address-based. Region id adjustment, AddPlayer arguments, state updates,
// and the campaign fallback's !local argument are individually read from
// native and WB. Native call boundaries and associative EH data establish
// the record and temporary-string lifetimes.
void LivingWorldCampaign::CreatePlayers()
{
 ((Glo012F1028Type *)TheLivingWorldLogic)->rva002B7D91();
 GameInfo *gameInfo=0;
 unsigned char campaign=fromCampaign;
 _ReadWriteBarrier();
 if(!campaign) {
  GameLogic *logic=TheGameLogic;
  if(((Rva00210C66CmpBoolField *)logic)->get()) {
   if(!TheGameInfo)return;
   gameInfo=TheGameInfo;
  } else if(logic->m_114!=3) {
   if(!(*(GameInfo **)&TheSkirmishGameInfo))return;
   gameInfo=(*(GameInfo **)&TheSkirmishGameInfo);
  }
 }
 if(gameInfo) {
  int local=gameInfo->getLocalSlotNum();
  int playerCount=0;
  for(int i=0;i<8;++i) {
   GameSlot *slot=gameInfo->getSlot(i);
   if(slot->state==1)continue;
   bool isLocal=i==local;
   bool human=slot->isHuman();
   Rva002E0EF7 player;
   player.wide()=slot->name;
   const PlayerTemplate *playerTemplate;
   if(slot->templateIndex>=0) {
    playerTemplate=ThePlayerTemplateStore->getNthPlayerTemplate(slot->templateIndex);
    player.narrow(8).format("Player_%d",i+1);
   } else if(slot->templateIndex==-1) {
    int index=GetRandomPlayablePlayerTemplateIndex(slot->hasHero ? &slot->heroInfo:0);
    slot->setPlayerTemplate(index);
    playerTemplate=ThePlayerTemplateStore->getNthPlayerTemplate(index);
    player.narrow(8).format("Player_%d",i+1);
   } else {
    playerTemplate=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
    player.narrow(8).format("Observer_%d",i+1);
   }
   Rva002E1904Entry *entry=((Rva002E1904Lookup *)TheLivingWorldPlayerTemplateStore)->find(playerTemplate->getName());
   if(!entry)continue;
   player.narrow(12)=*(const AsciiString *)entry;
   int baseRegion=slot->start;
   if(baseRegion==-1 || baseRegion<0)continue;
   baseRegion=AdjustStartingPositionForScenario(baseRegion);
   slot->start=baseRegion;
   Rva0020EAF6View *regions=TheLivingWorldLogic->regions;
   _ReadWriteBarrier();
   Rva0020E89C *region=regions->rva0020EAF6(baseRegion);
   if(!region)continue;
   {
     player.narrow(20)=region->name;
     player.narrow(16)="DefaultAITemplate";
     if(slot->color==-1)slot->color=Rva0052C06CGet(gameInfo);
     player.m_18=slot->color;
     player.m_1C=slot->team;
     player.m_20=-slot->at20;
     TheLivingWorldLogic->AddPlayer((Rva002BA8F1Input *)&player,isLocal,!human,(Rva002BA8F1Slot *)slot);
     Rva002E2903Player *created=((Rva002BA8F1Logic *)TheLivingWorldLogic)->GetPlayerAtIndex(playerCount);
     ((Rva002E067DDwordSlot *)created)->set(slot->state);
     ++playerCount;
   }
  }
  GameLogic *logic=TheGameLogic;
  if(((Rva00210C66CmpBoolField *)logic)->get())logic->CreateWOTRMPPlayers();
 } else {
  for(unsigned int i=0;i<players.size();++i) {
   bool local=players[i].narrow(8)==localName;
   TheLivingWorldLogic->AddPlayer((Rva002BA8F1Input *)&players[i],local,!local,0);
  }
 }
 TheLivingWorldLogic->ValidatePlayers();
}

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x002F11E
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);		// rowed 0x002EF56
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);		// rowed 0x002E850
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x002EF72
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);		// rowed 0x002EFC0
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class ModuleData;

class Rva00289218
{
public:
	void rva00289218(const ModuleData *data);
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;

// Retail's campaign block field table at RVA 0x008688A8 (.rdata, 240 bytes = fourteen 16-byte records and a zero
// sentinel), transcribed from retail's own bytes; every procedure is rowed. Records whose parser takes fewer
// arguments than the FieldParse callback (the cdecl caller cleans the stack) are stored through a cast.
class ScenarioOwnerView;
class Rva003F7BE9;
class LivingWorldPlayer { public: static void ParseLivingWorldPlayer(INI *ini, void *instance); };	// rowed 0x002E1D22
namespace LivingWorldScenario { class Scenario { public: static void ParseINI(INI *ini, ScenarioOwnerView *owner); }; }	// rowed 0x004FD94E
void ParseLivingWorldCampaignAct(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x00566D83
void Rva003F9258Parse(INI *ini, Rva003F7BE9 *holder);	// rowed 0x003F9258
extern const FieldParse LivingWorldCampaignFields[] =
{
	{ "AddPlayer", (INIFieldParseProc)LivingWorldPlayer::ParseLivingWorldPlayer, 0, 0 },
	{ "LocalPlayer", INI::parseAsciiString, 0, 0x30 },
	{ "Act", ParseLivingWorldCampaignAct, 0, 0 },
	{ "SecondsPerReinforcement", INI::parseInt, 0, 0x38 },
	{ "IsScriptedCampaign", INI::parseBool, 0, 0x4C },
	{ "IsEvilCampaign", INI::parseBool, 0, 0x4D },
	{ "ForceAdvanceTurnPhase", INI::parseBool, 0, 0x4E },
	{ "ScriptHolder", INI::parseAsciiString, 0, 0x34 },
	{ "Scenario", (INIFieldParseProc)LivingWorldScenario::Scenario::ParseINI, 0, 0 },
	{ "Tutorial", (INIFieldParseProc)Rva003F9258Parse, 0, 0 },
	{ "StartingCashRTS", INI::parseUnsignedInt, 0, 0x3C },
	{ "StartingCashRTSWithFort", INI::parseUnsignedInt, 0, 0x40 },
	{ "InitialRevivalCostMultiplier", INI::parseReal, 0, 0x44 },
	{ "InitialRevivalTimeMultiplier", INI::parseReal, 0, 0x48 },
	{ 0, 0, 0, 0 }
};


// ?ParseLivingWorldCampaignBlock@LivingWorldCampaign@@SAXPAVINI@@@Z
// @0x0052D04E 200B: the "LivingWorldCampaign" INI block parser.
// Target evidence: the block-parse registration at VA 0x00DD19A0
// (Rva007ABBF6BlockParseInits.cpp) binds token "LivingWorldCampaign" to
// 0x0052D04E; retail literal 0x00C68998 "ParseLivingWorldCampaignBlock::
// Campaign name expected" thrown as INIException(3) through
// __TI1?AVINIException@@ 0x008FE2FC. Body: skip when TheCampaignManager
// (0x00A02D6C) is null, read the name with getNextToken(0), new a 0x50-byte
// campaign through its constructor 0x0052CF0F (pushes the name), fill it from
// field table 0x008688A8 via INI::initFromINI, run 0x0052C0C8 on it, then hand
// it to the manager through the 16-byte forwarder 0x00289218 (rowed under an
// address name; its other caller is 0x002892CF).
// Name and file from the WorldBuilder build (LivingWorldCampaign.cpp,
// assert line 523, the null-manager DEBUG compiled out of retail); the
// constructor's class follows from this allocation and is a structural
// inference, the 0x0052C0C8 step keeps an address name.
void LivingWorldCampaign::ParseLivingWorldCampaignBlock(INI *ini)
{
	if (TheCampaignManager == 0)
		return;

	AsciiString name(ini->getNextToken(0));
	if (name.getLength() == 0)
		throw INIException(3, "ParseLivingWorldCampaignBlock::Campaign name expected");

	LivingWorldCampaign *campaign = new LivingWorldCampaign(name);
	ini->initFromINI(campaign, LivingWorldCampaignFields);
	campaign->rva0052C0C8();
	((Rva00289218 *)TheCampaignManager)->rva00289218((const ModuleData *)campaign);
}

// LivingWorldCampaign::rva0052C0C8, retail 0x0052C0C8 (81 B; WB 0x0133BFA0,
// unnamed, LivingWorldCampaign.cpp): the current index (+0x18) becomes the
// first record whose +0xB4 byte is set, else the last record. Record stride
// 0xB8 and both offsets are retail's; the names are structural.
void LivingWorldCampaign::rva0052C0C8()
{
	m_currentIndex = m_records.size() - 1;
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].m_selected)
		{
			m_currentIndex = i;
			break;
		}
	}
}
