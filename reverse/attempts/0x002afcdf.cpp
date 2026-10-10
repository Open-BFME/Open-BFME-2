// ?initFromDict@Player@@QAEXPBVDict@@@Z
// partial score=0.6108683812511932 date=2026-10-10
// Reference: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/Player.cpp:360-541.
// Identity: game.dat 2AF729..2AFCDF and WB C10C00 Player::init; target
// member accesses, allocated relation/squad sizes, calls and EH data define
// this BFME2 layout. Donor establishes purpose; unnamed fields remain unknown.
// Container adapters below reuse verified, payload-independent algorithms:
// hashtable begin(427195) scans the 20-byte bucket/header view; vector erase
// (532803) moves 4-byte trivial scalars. These views do not identify the
// Player keys as windows or its science IDs as particle IDs. The list<int>
// erase(438539) unlinks/frees nodes without reading payload or its size.
// NeutralPlayerColor is a descriptive name: target data RVA 9BBD28 holds
// FF404040 and the null-template branch copies it into both color fields.
// WB debug labels on reset include an inlined BitFlags::SetBit; its scoring
// masks, map resets, player-index store and native call site identify reset.
// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <list>
#include <vector>
#include <hash_map>
enum ParticleSystemID {INVALID_PARTICLE_SYSTEM_ID=0};
class GameWindow;class WindowVideo;
class WindowVideoManager {public:struct hashConstGameWindowPtr {unsigned operator()(const GameWindow*) const;};};
typedef _STL::hash_map<const GameWindow*,WindowVideo*,WindowVideoManager::hashConstGameWindowPtr,_STL::equal_to<const GameWindow*> > WindowMapView;
typedef _STL::hashtable<_STL::pair<const GameWindow*const,WindowVideo*>,const GameWindow*,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<_STL::pair<const GameWindow*const,WindowVideo*> >,_STL::equal_to<const GameWindow*>,_STL::allocator<_STL::pair<const GameWindow*const,WindowVideo*> > > WindowTableView;
namespace _STL {template<> WindowTableView::iterator WindowTableView::begin();}
extern "C" void free(void*);
extern "C" void* memset(void*,int,unsigned);
class ThingTemplate {public:char pad[0x64];AsciiString name;};
class Object {public:char pad0[4];const ThingTemplate*tmplate;char pad8[0x38-8];Coord3D position;float angle;char pad48[0x74-0x48];unsigned id;};
class Rva002AAE81 {public:void rva002AAE81(AsciiString);};
class BuildListInfo {public:BuildListInfo();void*vt;AsciiString building,tmplate;Coord3D position;char pad18[8];float angle;char pad24[4];int rebuilds;BuildListInfo*next;char pad30[0x47-0x30];bool priority;unsigned id;char pad4C[0x80-0x4C];};
class Player; class PlayerTemplate;
struct Rva002ADF9C{void rva002ADF9C(const Player*,Object*);};
class PolymorphicOwner {public: virtual ~PolymorphicOwner();};
class UpgradeView:public PolymorphicOwner {public:char gap4[8];UpgradeView*next;};
class PlayerRelationMap:public PolymorphicOwner {char opaque[20];public:PlayerRelationMap();};
class Rva003A3959:public PolymorphicOwner {char opaque[20];public:Rva003A3959();};
class ResourceGatheringManager:public PolymorphicOwner {char rest[8];public:ResourceGatheringManager();};
class TunnelTracker:public PolymorphicOwner {char rest[0x24];public:TunnelTracker();};
class Squad:public PolymorphicOwner {char opaque[24];public:Squad() throw();};
struct Rva002AAC74PoolList {void*head;void clear();};
struct Rva004F599E{void*vt;int words[42];void rva004F597F();};
struct EnergyView {int first;int production;int consumption;Player*owner;};
struct Rva001FD42B {void*header;unsigned count;char compare[4];void rva001FD630();Rva001FD42B*rva001FD8DF(const Rva001FD42B&);};
struct Rva001FD458 {void*header;unsigned count;char compare[4];void rva001FD659();Rva001FD458*rva001FD952(const Rva001FD458&);};
struct Rva000427195 {void*words[5];Rva000427195&operator=(const Rva000427195&);void rva003A2A41();};
class Rva000411084 {public: void*node;void*table;void*next();};
struct Rva002AE4C5 {int&rva002AE4C5(const AsciiString*);};
struct Rva002AE318{void rva002AE318();};
struct Rva002A7761 {void rva002A7761();};
struct UnitRevivalTracker{int unknown;void*vec[3];void rva0037F26D();};
class Rva0039B7AD;
struct Rva003B0D7C{virtual ~Rva003B0D7C();int money;int owner;void rva003B0D7C(int,Rva0039B7AD*,bool);};
struct Rva003B0E75 {float values[4];void rva003B0E75();};
class Dict;struct Handicap {float values[4];void readFromDict(const Dict*);};
class RGBColor {public:float red,green,blue;int getAsInt()const;};
class ScoreKeeper {public:void reset(int);};
enum NameKeyType{NAMEKEY_INVALID=0};class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);NameKeyType nameToKey(const char*);};
extern NameKeyGenerator* TheNameKeyGenerator;
class GlobalData;extern GlobalData*TheWritableGlobalData;
class GameLogic;extern GameLogic*TheGameLogic;
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class GameInfo;extern GameInfo*TheGameInfo;
unsigned int NeutralPlayerColor=0xFF404040u;
struct LogicModeView{char gap[0x114];int mode;};
struct LivingWorldModeView{char gap[0xB4];bool mode;};
struct GlobalCashView{char gap[0xBB8];int cash;};
struct GameCashView{char gap[0x70];int cash;};
struct ReadyTimer {int power;int ready;};
struct ProductionCostModifier {void*filter;float*first;float*last;float*end;unsigned object;bool all;__forceinline ~ProductionCostModifier(){if(first)free(first);}};
namespace _STL {
template<> vector<void*>::iterator vector<void*>::erase(iterator,iterator);
template<> vector<ParticleSystemID>::iterator vector<ParticleSystemID>::erase(iterator,iterator);
}
class PlayerTemplate {public:
char gap00[0x18];AsciiString side;Handicap handicap;Rva003B0D7C money;RGBColor color;
char gap44[0xF4-0x44];Rva001FD42B cost;Rva000427195 time;Rva001FD458 veterancy;
char gap120[0x150-0x120];bool observer;char gap151[3];unsigned char property154;
};
enum PlayerType {PLAYER_HUMAN,PLAYER_COMPUTER};
class Player {public:
void init(const PlayerTemplate*);void initFromDict(const class Dict*);
void setPlayerType(PlayerType,bool);void rva002AD25B(const AsciiString&);bool rva002AC4D4(int*);
void addToBuildList(Object*);
void addToPriorityBuildList(const AsciiString&,Coord3D*,float);
void deleteUpgradeList();void rva002A99FA();void initPlayerUpgrades();
char gap00[0xC];const unsigned char*property;
char gap10[0x34-0x10];const PlayerTemplate*tmplate;UnicodeString displayName;Handicap handicap;
AsciiString name;NameKeyType nameKey;int index;AsciiString side;int type;
Rva002A7761 r60;char gap61[0x90-0x61];Rva003B0D7C money;UpgradeView*upgradeList;
int radar;int disableRadar;bool radarDisabled;char gapA9[3];int bombard;int hold;int search;void*battle;
char gapBC[0x1BC-0xBC];EnergyView energy;Rva004F599E stats;
PolymorphicOwner*buildList;int unknown27C;unsigned color;unsigned nightColor;
Rva001FD42B cost;Rva000427195 time;Rva000427195 scratchTime;Rva000427195 timeCounts;Rva001FD458 veterancy;
PolymorphicOwner*ai;void*defaultTeam;PolymorphicOwner*resources;PolymorphicOwner*tunnel;
int unknown2EC;char gap2F0[0x2FC-0x2F0];_STL::vector<unsigned int> disabled;_STL::vector<unsigned int>hidden;
float bounty;char gap318[4];int unknown31C;_STL::vector<void*>elements;
Rva002AAC74PoolList prototypes;PlayerRelationMap*playerRelations;Rva003A3959*teamRelations;
bool canBuildBase,canBuildUnits,observer,flag33B,listInScoreScreen,unitsHunt,flag33E,flag33F;
bool attackedBy[20];int attackedFrame;unsigned attackFrames[20];int unknown3A8;int unknown3AC;char gap3B0[12];
ScoreKeeper score;char gap3BD[0x6F0-0x3BD];int unknown6F0;_STL::list<ProductionCostModifier*>modifiers;float unknown6F8;int unknown6FC;
_STL::_List_base<int,_STL::allocator<int> >unknown700;
_STL::list<ReadyTimer>timers;Squad*squads[10];Squad*selection;bool dead;bool flag735;char gap736[2];UnitRevivalTracker revival;char gap748[4];AsciiString text74C;
};

class StaticNameKey {public:NameKeyType key()const;private:int value;const char*name;};
extern const StaticNameKey TheKey_playerFaction,TheKey_playerDisplayName,TheKey_playerName,TheKey_playerIsSkirmish,TheKey_playerIsHuman,TheKey_playerIsPreorder,TheKey_multiplayerStartIndex,TheKey_skirmishDifficulty,TheKey_playerStartMoney,TheKey_playerHandicap,TheKey_teamName,TheKey_teamOwner;
class Rva00148F5ECache {public:NameKeyType get();};
extern Rva00148F5ECache TheKey_playerAIType,TheKey_playerFactionIcon,TheKey_livingWorldPlayerID;

class Dict {public:
 Dict(const Dict&d):data(d.data){if(data)++*(unsigned short*)data;}
 ~Dict(){releaseData();}enum DataType{DICT_NONE=-1,DICT_BOOL,DICT_INT,DICT_REAL,DICT_ASCIISTRING,DICT_UNICODESTRING};DataType getType(int)const;
 AsciiString getAsciiString(int,bool * =0)const;UnicodeString getUnicodeString(int,bool * =0)const;
 bool getBool(int,bool * =0)const;int getInt(int,bool * =0)const;
 void setAsciiString(int,const AsciiString&);
 private:void releaseData();void*data;
};
class ScriptList {public:ScriptList(const ScriptList&);virtual ~ScriptList();private:char opaque[0x48];};
class SidesInfo {public:void*build;Dict dict;ScriptList scripts;char tail[12];Dict*getDict(){return &dict;}ScriptList*getScriptList(){return &scripts;}void setScriptList(ScriptList*);};
struct TeamRec {short next,prev,reserved,flags;int gen;Dict dict;};
class TeamsInfoRec {public:char index[12];TeamRec*records;char rest[12];
 int first()const{return records[0].next;}int next(int n)const{return records[n].next;}Dict*get(int n){return &records[n].dict;}
 int addTeam(const Dict*);void removeTeam(int);
};
class SidesList {public:char pad[0x7c0];int skirmishCount;SidesInfo skirmishSides[20];TeamsInfoRec teams,skirmishTeams;
 SidesInfo*getSkirmishSideInfo(int);SidesInfo*getSideInfo(int);
};
extern SidesList*TheSidesList;
class PlayerTemplateStore{public:const PlayerTemplate*findPlayerTemplate(NameKeyType)const;};extern PlayerTemplateStore*ThePlayerTemplateStore;
class Rva002A9ACC {public:void rva002A9ACC(const Dict*);};
struct Rva000B3F84Pair {const char *text;int len;};struct AsciiStringRef {const AsciiString *string;};
struct Rva002226E5TextPlusString {Rva002226E5TextPlusString(){}Rva000B3F84Pair left;AsciiStringRef right;operator AsciiString();};
Rva002226E5TextPlusString operator+(const char*,const AsciiString&);
bool Rva002ACFC1Equal(int,int);
struct DifficultyView{char pad[0x1a4c4];int value;};class ScriptEngine;extern ScriptEngine*TheScriptEngine;
struct Rva004DFC20{void clear();};
struct RegionManagerView{void*getCurrent();};
class Rva0020E6B7RegionManager{public:class Rva003F468D*rva0020E6B7();};
class Rva003F468D{public:char pad[0x24];class LivingWorldRegion*region;class RegionOwner*rva003F4DA9();};
class RegionOwner{public:char pad[0x14];int index;};class CreateAHeroData;
class LivingWorldRegion{public:char pad[0x11c];bool flag;int rva003F0614(CreateAHeroData*)const;};
struct CampaignView{char pad[0xb0];Rva0020E6B7RegionManager*regions;bool active;};
void*Rva002B47B1Get();void*Rva002B479FGet();
inline __declspec(noinline) SidesInfo*SidesList::getSkirmishSideInfo(int i){return i>=0 && i<skirmishCount?&skirmishSides[i]:0;}
void Player::initFromDict(const Dict*d){
 AsciiString tmplname=d->getAsciiString(TheKey_playerFaction.key());
 const PlayerTemplate*pt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(tmplname));
 if(!pt)pt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionCivilian"));
 init(pt);displayName=d->getUnicodeString(TheKey_playerDisplayName.key());AsciiString pname=d->getAsciiString(TheKey_playerName.key());name=pname;nameKey=TheNameKeyGenerator->nameToKey(pname);
 bool exists;bool skirmish=false;bool forceHuman=false;
 bool wasObserver=pt->observer;if(!wasObserver && d->getBool(TheKey_playerIsSkirmish.key(),&exists)){
  for(int sp=0;sp<TheSidesList->skirmishCount;++sp){
   AsciiString faction=TheSidesList->getSkirmishSideInfo(sp)->getDict()->getAsciiString(TheKey_playerFaction.key());
   const PlayerTemplate*spt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(faction));
   if(spt && spt->side==side){skirmish=true;break;}
  }
  if(!skirmish)forceHuman=true;
 }
 defaultTeam=(void*)d->getInt(TheKey_multiplayerStartIndex.key(),&exists);
 ((Rva002A9ACC*)this)->rva002A9ACC(d);unknown27C=d->getInt(TheKey_playerHandicap.key(),&exists);
 if(d->getBool(TheKey_playerIsHuman.key()) || forceHuman){
  setPlayerType(PLAYER_HUMAN,skirmish);
  if(d->getBool(TheKey_playerIsPreorder.key(),&exists))flag33B=true;
  if(TheSidesList->skirmishCount>0 && d->getAsciiString(TheKey_playerName.key())!="ReplayObserver" && tmplname!="FactionObserver"){
   if(d->getType(TheKey_playerAIType.get())!=3){
    AsciiString humanSide("SkirmishHuman");
    for(int i=0;i<TheSidesList->skirmishCount;++i){
     if(TheSidesList->getSkirmishSideInfo(i)->getDict()->getAsciiString(TheKey_playerName.key())==humanSide){{
 ScriptList scripts(*TheSidesList->getSkirmishSideInfo(i)->getScriptList());TheSidesList->getSideInfo(index)->setScriptList(&scripts);
 AsciiString original=TheSidesList->getSkirmishSideInfo(i)->getDict()->getAsciiString(TheKey_playerName.key());
 for(int id=TheSidesList->skirmishTeams.first();id;id=TheSidesList->skirmishTeams.next(id)){
  if(TheSidesList->skirmishTeams.get(id)->getAsciiString(TheKey_teamOwner.key())==original){Dict team(*TheSidesList->skirmishTeams.get(id));AsciiString tname=team.getAsciiString(TheKey_teamName.key());if(Rva002ACFC1Equal((int)&tname,(int)&("team"+original)))team.setAsciiString(TheKey_teamName.key(),"team"+pname);team.setAsciiString(TheKey_teamOwner.key(),pname);TheSidesList->teams.addTeam(&team);}
 }
}break;}
    }
   }
   skirmish=false;rva002AD25B(pname);
  }
 }else setPlayerType(PLAYER_COMPUTER,skirmish);
 if(skirmish){
  int skirmishNdx;if(!rva002AC4D4(&skirmishNdx))return;
  int diff=d->getInt(TheKey_skirmishDifficulty.key(),&exists);int difficulty=((DifficultyView*)TheScriptEngine)->value;if(exists)difficulty=diff;
  if(ai)*(int*)((char*)ai+0x2c)=difficulty;
  if(d->getType(TheKey_playerAIType.get())!=3){
   ScriptList scripts(*TheSidesList->getSkirmishSideInfo(skirmishNdx)->getScriptList());TheSidesList->getSideInfo(index)->setScriptList(&scripts);
   for(int id=TheSidesList->teams.first();id;){int next=TheSidesList->teams.next(id);if(TheSidesList->teams.get(id)->getAsciiString(TheKey_teamOwner.key())==pname)TheSidesList->teams.removeTeam(id);id=next;}
   // Keep copyTeams' team semantics inline without recopying the script list.
   AsciiString original=TheSidesList->getSkirmishSideInfo(skirmishNdx)->getDict()->getAsciiString(TheKey_playerName.key());
   for(int id=TheSidesList->skirmishTeams.first();id;id=TheSidesList->skirmishTeams.next(id)){
    if(TheSidesList->skirmishTeams.get(id)->getAsciiString(TheKey_teamOwner.key())==original){Dict team(*TheSidesList->skirmishTeams.get(id));AsciiString tname=team.getAsciiString(TheKey_teamName.key());if(Rva002ACFC1Equal((int)&tname,(int)&("team"+original)))team.setAsciiString(TheKey_teamName.key(),"team"+pname);team.setAsciiString(TheKey_teamOwner.key(),pname);TheSidesList->teams.addTeam(&team);}
   }
  }
  rva002AD25B(pname);
 }
 if(resources){::delete resources;resources=0;}resources=new ResourceGatheringManager;
 if(tunnel){::delete tunnel;tunnel=0;}tunnel=new TunnelTracker;
 handicap.readFromDict(d);((Rva004DFC20*)((char*)playerRelations+4))->clear();((Rva004DFC20*)((char*)teamRelations+4))->clear();
 for(int i=0;i<20;++i){attackedBy[i]=false;attackFrames[i]=0;}unknown3A8=0;
 int m=d->getInt(TheKey_playerStartMoney.key(),&exists);if(exists)money.rva003B0D7C(m,(Rva0039B7AD*)&score,false);
 for(int i=0;i<10;++i){if(squads[i]){::delete squads[i];squads[i]=0;}squads[i]=new Squad;}
 if(selection){::delete selection;selection=0;}selection=new Squad;
 text74C=d->getAsciiString(TheKey_playerFactionIcon.get(),&exists);int ri=d->getInt(TheKey_livingWorldPlayerID.get(),&exists);if(exists)unknown3AC=ri;
 if(((LogicModeView*)TheGameLogic)->mode!=3 && ((CampaignView*)TheLivingWorldLogic)->active){
  Rva003F468D*cur=((CampaignView*)TheLivingWorldLogic)->regions->rva0020E6B7();
  if(cur){RegionOwner*owner=cur->rva003F4DA9();void*cash;if(owner && owner->index==unknown3AC && (cur->region->rva003F0614((CreateAHeroData*)1)>=1 || cur->region->flag))cash=Rva002B47B1Get();else cash=Rva002B479FGet();money.rva003B0D7C((int)cash,(Rva0039B7AD*)&score,false);}
 }
}
