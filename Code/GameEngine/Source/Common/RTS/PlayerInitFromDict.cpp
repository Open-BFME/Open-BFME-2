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
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
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
class Player; class PlayerTemplate; class Object;
struct Rva002ADF9C{void rva002ADF9C(const Player*,Object*);};
class PolymorphicOwner {public: virtual ~PolymorphicOwner();};
class UpgradeView:public PolymorphicOwner {public:char gap4[8];UpgradeView*next;};
class PlayerRelationMap:public PolymorphicOwner {char opaque[20];public:PlayerRelationMap();};
class Rva003A3959:public PolymorphicOwner {char opaque[20];public:Rva003A3959();};
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
struct HandicapView {float values[4];};
class RGBColor {public:float red,green,blue;int getAsInt()const;};
class ScoreKeeper {public:void reset(int);};
enum NameKeyType{NAMEKEY_INVALID=0};class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};
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
char gap00[0x18];AsciiString side;HandicapView handicap;Rva003B0D7C money;RGBColor color;
char gap44[0xF4-0x44];Rva001FD42B cost;Rva000427195 time;Rva001FD458 veterancy;
char gap120[0x150-0x120];bool observer;char gap151[3];unsigned char property154;
};
class Player {public:
void init(const PlayerTemplate*);
void deleteUpgradeList();void rva002A99FA();void initPlayerUpgrades();
char gap00[0xC];const unsigned char*property;
char gap10[0x34-0x10];const PlayerTemplate*tmplate;UnicodeString displayName;HandicapView handicap;
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

void Player::init(const PlayerTemplate*pt){
 tmplate=pt;prototypes.clear();displayName.clear();deleteUpgradeList();
 radar=0;disableRadar=0;radarDisabled=false;bombard=0;hold=0;search=0;
 if(battle){::operator delete(battle);battle=0;}
 EnergyView&power=energy;power.production=0;power.consumption=0;power.owner=this;stats.rva004F597F();
 if(buildList){::delete buildList;buildList=0;}if(ai){::delete ai;ai=0;}defaultTeam=0;
 if(resources){::delete resources;resources=0;}if(tunnel){::delete tunnel;tunnel=0;}
 unknown2EC=0;bounty=0.0f;_STL::vector<void*>&items=elements;items.erase(items.begin(),items.end());unknown31C=0;
 if(playerRelations)::delete playerRelations;playerRelations=new PlayerRelationMap;
 if(teamRelations)::delete teamRelations;teamRelations=new Rva003A3959;
 canBuildBase=true;canBuildUnits=true;observer=false;flag33B=false;listInScoreScreen=true;unitsHunt=false;flag33E=false;flag33F=false;
 for(unsigned i=0;i<20;++i){attackedBy[i]=false;attackFrames[i]=0;}
 attackedFrame=0;unknown3A8=0;unknown3AC=-1;score.reset(index);
 unknown6F0=0;unknown6F8=0.f;unknown6FC=0;
 {Squad**squad=squads;int count=10;do{if(*squad)::delete *squad;*squad=new Squad;++squad;}while(--count);}
 if(selection)::delete selection;selection=new Squad;dead=false;flag735=true;revival.rva0037F26D();
 if(pt){property=&tmplate->property154;handicap=pt->handicap;name.clear();nameKey=NAMEKEY_INVALID;side=pt->side;type=1;
  Rva003B0D7C&cash=money;cash=pt->money;money.owner=index;
  if(money.money==0 && (((LogicModeView*)TheGameLogic)->mode==3 || !((LivingWorldModeView*)TheLivingWorldLogic)->mode)){
   if(TheGameInfo)cash.rva003B0D7C(((GameCashView*)TheGameInfo)->cash,0,false);
   else cash.rva003B0D7C(((GlobalCashView*)TheWritableGlobalData)->cash,0,false);
  }
  color=pt->color.getAsInt()|0xff000000;nightColor=color;unknown27C=0;
  cost.rva001FD8DF(pt->cost);time=pt->time;scratchTime=time;timeCounts.rva003A2A41();veterancy.rva001FD952(pt->veterancy);
  WindowTableView::iterator it=((WindowTableView*)&time)->begin();while(it._M_cur){((Rva002AE4C5*)&timeCounts)->rva002AE4C5((const AsciiString*)((char*)it._M_cur+4))=0;((Rva000411084*)&it)->next();}
  observer=pt->observer;dead=observer;
 }else{
  property=0;displayName=UnicodeString::TheEmptyString;((Rva003B0E75*)&handicap)->rva003B0E75();name=AsciiString::TheEmptyString;nameKey=TheNameKeyGenerator->nameToKey(AsciiString::TheEmptyString);side="";money.owner=index;unsigned c=NeutralPlayerColor;type=1;money.money=0;color=c;nightColor=c;unknown27C=0;
  cost.rva001FD630();time.rva003A2A41();scratchTime.rva003A2A41();timeCounts.rva003A2A41();veterancy.rva001FD659();
  ((Rva002ADF9C*)this)->rva002ADF9C(this,(Object*)2);
 }
 ((Rva002A7761*)&r60)->rva002A7761();rva002A99FA();((Rva002AE318*)((char*)this+8))->rva002AE318();_STL::vector<ParticleSystemID>&ds=(_STL::vector<ParticleSystemID>&)disabled;ds.erase(ds.begin(),ds.end());_STL::vector<ParticleSystemID>&hs=(_STL::vector<ParticleSystemID>&)hidden;hs.erase(hs.begin(),hs.end());initPlayerUpgrades();
 {_STL::list<int>&timerNodes=(_STL::list<int>&)timers;_STL::list<int>::iterator t=timerNodes.begin();while(t!=timerNodes.end()){pt=(const PlayerTemplate*)&*t;t=timerNodes.erase(t);if(pt){ReadyTimer*entry=(ReadyTimer*)pt;entry->power=0;entry->ready=-1;}}
 }
 {_STL::list<int>&modifierNodes=(_STL::list<int>&)modifiers;_STL::list<int>::iterator m=modifierNodes.begin();while(m!=modifierNodes.end()){pt=(const PlayerTemplate*)*m;m=modifierNodes.erase(m);if(pt){ProductionCostModifier*entry=(ProductionCostModifier*)pt;if(entry->first)free(entry->first);::operator delete((void*)pt);}}
}
 unknown700.clear();text74C.clear();
}

void Player::deleteUpgradeList(){
 UpgradeView*next;
 while(upgradeList){next=upgradeList->next;::delete upgradeList;upgradeList=next;}
 memset((char*)this+0xBC,0,0x80);
 memset((char*)this+0x13C,0,0x80);
}
