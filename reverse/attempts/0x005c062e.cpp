// ?ProcessOnlineGameResults@StatsReporter@@SAXPAVPlayer@@@Z
// partial score=0.995706 date=2026-10-09
// ?ProcessOnlineGameResults@StatsReporter@@SAXPAVPlayer@@@Z
// partial score=0.9957 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT
#include "ascii_string.h"
#include <new>
// stlport
#include <cstdlib>
void Rva00030830GameFree(void*);
#define free Rva00030830GameFree
#include <map>
#include <vector>
#undef free
typedef int Int;
class XferStub;
typedef _STL::map<unsigned char,short> StatsShortMap;
typedef _STL::map<unsigned char,int> StatsIntMap;
typedef _STL::map<unsigned char,float> StatsFloatMap;
template<>short&StatsShortMap::operator[](const unsigned char&);
template<>int&StatsIntMap::operator[](const unsigned char&);
template<>float&StatsFloatMap::operator[](const unsigned char&);
namespace _STL {template<class C>class char_traits;template<class C>class allocator;
template<class C,class T,class A>class basic_string {public:basic_string();~basic_string();basic_string&operator=(const C*);C*start;C*finish;C*storageEnd;};}
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > Rva00385333String;
class Rva00553E47StatsCore {
public:
    Rva00553E47StatsCore(const Rva00553E47StatsCore &);
    Rva00553E47StatsCore(int id);
    virtual void reset();
    virtual void rva005550A0(XferStub *);
    virtual void rva00555109(XferStub *);
    virtual void rva00554AF2(const Rva00553E47StatsCore *);
    friend class Rva00559D0CRankWeights;
public:
    StatsShortMap m_maps04_0;
    StatsShortMap m_maps04_1;
    StatsShortMap m_maps04_2;
    StatsShortMap m_maps04_3;
    StatsShortMap m_maps04_4;
    StatsShortMap m_maps04_5;

    StatsShortMap m_maps4c[6];
    StatsShortMap m_maps94[6];
    StatsFloatMap m_mapsdc_0;
    StatsFloatMap m_mapsdc_1;
    StatsFloatMap m_mapsdc_2;
    StatsFloatMap m_mapsdc_3;
    StatsFloatMap m_mapsdc_4;
    StatsFloatMap m_mapsdc_5;
    StatsFloatMap m_mapsdc_6;
    StatsFloatMap m_mapsdc_7;

    unsigned m_13c, m_140;
    unsigned short m_144, m_146, m_148, m_14a, m_14c;
    unsigned short m_unmodelled14e;
public:
    int m_id;
    unsigned short getField144() const { return m_144; }
};

typedef char StatsCoreSizeCheck[sizeof(Rva00553E47StatsCore) == 0x154 ? 1 : -1];
class Rva003844D7 : public Rva00553E47StatsCore {
public:
    Rva003844D7(int);
    Rva003844D7(const Rva003844D7 &);
    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva00555845(const Rva003844D7 *);
    ~Rva003844D7();
    Rva003844D7 &operator=(const Rva003844D7 &);
    StatsIntMap m_map154;
    StatsShortMap m_map160, m_map16c;
    StatsFloatMap m_map178, m_map184;
};
typedef char OpenPlaySizeCheck[sizeof(Rva003844D7)==0x190?1:-1];

class Rva0038454E : public Rva00553E47StatsCore	// strategic stats block
{
public:
    Rva0038454E(int);
    Rva0038454E(const Rva0038454E &);
    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva0055524B(const Rva0038454E *);
	~Rva0038454E();						// 0x0038454E
	Rva0038454E &operator=(const Rva0038454E &that);	// 0x00387945

    StatsFloatMap m_map154;
    StatsFloatMap m_map160;
    StatsFloatMap m_map16c;
    StatsFloatMap m_map178;
    StatsFloatMap m_map184;
    StatsFloatMap m_map190;
    StatsFloatMap m_map19c;
    StatsFloatMap m_map1a8;
    StatsShortMap m_map1b4;
    StatsShortMap m_map1c0;
    StatsFloatMap m_map1cc;
    StatsFloatMap m_map1d8;
    StatsFloatMap m_map1e4;
    StatsFloatMap m_map1f0;
    StatsFloatMap m_map1fc;

};

class Rva00385333 : public Rva003844D7	// tournament stats block
{
public:
	Rva00385333(int);
	Rva00385333(const Rva00385333 &);
    void rva00555DDC(XferStub *);
	void rva00555F68();
	~Rva00385333();						// 0x00385333
	Rva00385333 &operator=(const Rva00385333 &that);	// 0x00387A68

	unsigned short m_190;
	unsigned short m_192;
	Int m_194;
	Int m_198;
	Rva00385333String m_text19C;
};

class PSPlayerAllStats
{
public:
    PSPlayerAllStats(Int id);
    PSPlayerAllStats(const PSPlayerAllStats&);
    ~PSPlayerAllStats();
    void rva00552CB8();
    void rva00552E9E(Int v);
    Rva003844D7 rva00389DF1() const;
    Rva0038454E rva00389E0F() const;
    Rva00385333 rva00556508() const;
	PSPlayerAllStats &operator=(const PSPlayerAllStats &that);
	void setOpenPlayStats(Rva003844D7 stats);
	void setStrategicStats(Rva0038454E stats);
	void setTournamentStats(Rva00385333 stats);
	Int getLocale() const { return m_locale; }
	void setID(Int id);

public:
	Int m_id;						// +0x000
	Int m_locale;					// +0x004 set by rva00552E9E, copied by operator= @0x003874B0
	Rva00385333 m_tournamentStats;				// +0x008
	Rva003844D7 m_openPlayStats;				// +0x1B0
	Rva0038454E m_strategicStats;				// +0x340
};

struct BfmeOpaqueOwnedRecord1432
{
	BfmeOpaqueOwnedRecord1432();
	~BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432 &operator=(const BfmeOpaqueOwnedRecord1432 &that);
	Int requestType;
	Int m_04;
	PSPlayerAllStats player;
	Rva00385333String cdkey;
	Rva00385333String nick;
	Rva00385333String password;
	Rva00385333String email;
	bool addDiscon;
	bool addDesync;
	Int lastHouse;
	Int m_588;
	Rva00385333String results;
};
typedef char RequestRecordSizeCheck[sizeof(BfmeOpaqueOwnedRecord1432) == 0x598 ? 1 : -1];


struct BfmeOpaqueOwnedRecord1408 {BfmeOpaqueOwnedRecord1408():player(0){} int kind;int m04;PSPlayerAllStats player;char tail[0x30];};
class GameSpyGameSlot;class Player;
class GameSpyStagingRoom {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual int localSlot();
GameSpyGameSlot*getGameSpySlot(int);AsciiString generateGameSpyGameResultsPacket(bool,bool);
 int getMode()const{return mode;}
 char beforeMode[0x5c-4];int mode;char beforeFlags[0xff4-0x60];bool flagFF4;bool getFF4()const{return flagFF4;}char gap[3];int ladder;
};
class GameSpyInfoInterface {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual int localProfile();
virtual AsciiString nickname();
virtual void v33();
virtual AsciiString password();
virtual void v35();
virtual void v36();
virtual AsciiString cdkey();
virtual void updated(PSPlayerAllStats);
};
class GameSpyPSMessageQueueInterface {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void addRequest(const BfmeOpaqueOwnedRecord1432&);virtual void v5();virtual void addResponse(const BfmeOpaqueOwnedRecord1408&);virtual void v7();virtual void store(PSPlayerAllStats);virtual void v9();virtual void va();virtual void vb();virtual PSPlayerAllStats getStats(int);
};
class VictoryConditionsInterface {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual bool hasWon(Player*);
virtual void v15();
virtual void v16();
virtual void v17();
virtual bool isLocalAlliedVictory();
virtual bool isLocalAlliedDefeat();
virtual bool gameEnded();
virtual bool skipReporting();
virtual unsigned elapsed();
virtual void v23();
virtual void v24();
virtual bool quit(int);
};
class GameSlot {public:virtual void reset();bool isOccupied()const;bool isAI()const;bool isHuman()const;bool disconnected()const;char beforeName[0x30];AsciiString name;char gap38[0xc];unsigned stamp;unsigned getStamp()const{return stamp;}};
class GameSpyGameSlot:public GameSlot {public:char gap48[0x18];bool hasHero;char gap61[3];};
class GameInfo {public:GameSlot*getSlot(int);const GameSlot*getConstSlot(int)const;};
class PlayerTemplate {public:int rva001FD234()const;};
class ScoreKeeper {public:int getTotalBuildingsDestroyed();int getTotalUnitsDestroyed();char pad0[4];int value04,value08;char padC[0x64];int value70,value74;char pad78[0x50];int valueC8,valueCC;};
class Player {public:char gap0[0x34];PlayerTemplate*playerTemplate;char gap38[0x374];int strategicID;char gap3B0[0xc];ScoreKeeper score;int getStrategicID()const{return strategicID;}};
struct Rva00045411BitSet {unsigned words[7];Rva00045411BitSet(int,int);};
template<int N>class BitFlags {unsigned words[7];};
class Rva0039BF0B {public:int rva0039BF0B(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva0039BF39 {public:int rva0039BF39(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE35D {public:int rva004EE35D(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3AB {public:int rva004EE3AB(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3F9 {public:int rva004EE3F9(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class LivingWorldScoreKeeper {public:int GetBuildingsOfTypeBuilt(int);int rva004EE33B();int rva004EE043();char pad0[0x34];_STL::vector<unsigned>v34;_STL::vector<unsigned>v40;char pad4c[0x48];int value94,value98;char pad9c[0xc];int valueA8,valueAC,valueB0;char padB4[0x24];int valueD8,valueDC,valueE0,valueE4,valueE8,valueEC,valueF0;int getD8()const{return valueD8;}int getDC()const{return valueDC;}int getE0()const{return valueE0;}int getE4()const{return valueE4;}int getA8()const{return valueA8;}int getAC()const{return valueAC;}};
class LivingWorldPlayer {public:char pad0[0x2c8];LivingWorldScoreKeeper score;char pad3bc[8];bool lost;};
class Rva002E2903Player;class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);};
class LivingWorldLogic {};
class Rva0021937DTarget;class Rva0021937D {public:void rva002193D9(Rva0021937DTarget*);void rva00219407(Rva0021937DTarget*);};
class CreateAHeroManager {};
class GameLogic {public:char gap0[0x40];unsigned frame;char gap44[0x2d];bool desync;bool getDesync()const{return desync;}char gap72[0x232];int result;};
class GlobalData {public:char gap0[0x110c];float minDuration;};
enum NameKeyType {INVALID_NAME_KEY=-1};class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};
class PlayerList {public:Player*findPlayerWithNameKey(NameKeyType);};
class Rva005B8053 {public:void*rva005B8053(const unsigned char*);};
struct Gen_uw_00385371;void Rva00556FB8(const Gen_uw_00385371&);
extern GameSpyStagingRoom*TheGameSpyGame;extern GameSpyInfoInterface*TheGameSpyInfo;extern GameSpyPSMessageQueueInterface*TheGameSpyPSMessageQueue;
extern VictoryConditionsInterface*TheVictoryConditions;extern GameInfo*TheGameInfo;extern LivingWorldLogic*TheLivingWorldLogic;
extern GameLogic*TheGameLogic;extern GlobalData*TheWritableGlobalData;extern CreateAHeroManager*TheCreateAHeroManager;
extern NameKeyGenerator*TheNameKeyGenerator;extern PlayerList*ThePlayerList;
extern int g_Va00DBA4E4;extern int g_Va00DC0758;extern int g_Va00DC075C;extern const BitFlags<116>g_defaultStorage009FEFA4;
template<class T>inline const T&maxRef(const T&a,const T&b){return a>b?a:b;}
template<class T>inline const T&minRef(const T&a,const T&b){return a<b?a:b;}
__forceinline const char*retailStr(const AsciiString&s){return reinterpret_cast<const StringBase<char>*>(&s)->str();}
inline const BitFlags<116>&mask(const Rva00045411BitSet&x){return reinterpret_cast<const BitFlags<116>&>(x);}
inline unsigned short&word(short&x){return reinterpret_cast<unsigned short&>(x);}
// WB lead identifies ProcessOnlineGameResults. ZH ScoreScreen.cpp is the
// wins/losses reference spine. Native5C062E..5C1860 supplies BFME2 conditions,
// member offsets, record types and call ordering; donor9cbfb551fe20.
class StatsReporter {public:static void ProcessOnlineGameResults(Player*);};
void StatsReporter::ProcessOnlineGameResults(Player*player){
 LivingWorldPlayer*lw=0;int mode=0;
 if(TheGameSpyGame->getMode()==1){lw=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(player->getStrategicID(),0));mode=2;}
 else if(TheGameSpyGame->ladder==1||TheGameSpyGame->ladder==2)mode=1;
 int profile=TheGameSpyInfo->localProfile();if(!profile)return;
 int local=TheGameSpyGame->localSlot();GameSpyGameSlot*localSlot=TheGameSpyGame->getGameSpySlot(local);if(!localSlot)return;
 if(TheVictoryConditions->skipReporting())return;
 PSPlayerAllStats stats=TheGameSpyPSMessageQueue->getStats(profile);
 Rva0038454E strategic(0);Rva00385333 tournament(0);Rva003844D7 open(0);Rva00553E47StatsCore*core;
 if(mode==2){strategic=stats.rva00389E0F();core=&strategic;}else if(mode==1){tournament=stats.rva00556508();core=&tournament;}else{open=stats.rva00389DF1();core=&open;}
 unsigned otherMaximum=0,maximum=0;bool disconnected=false;
 bool noData=TheGameLogic->result==1||TheGameLogic->result==0;bool otherHuman=false;
 for(int i=0;i<8;++i){const GameSlot*slot=TheGameInfo->getConstSlot(i);if(slot->isOccupied()&&i!=local&&!slot->isAI())otherHuman=true;
 if(slot->isOccupied())maximum=maxRef(maximum,slot->getStamp());if(slot->isHuman()&&i!=local)otherMaximum=maxRef(otherMaximum,slot->getStamp());}
 for(int i=0;i<8;++i){const GameSlot*slot=TheGameInfo->getConstSlot(i);if(slot->isOccupied()&&slot->disconnected()){disconnected=true;break;}}
 if(!otherHuman)return;
 bool report=false;if(TheVictoryConditions->isLocalAlliedDefeat()||TheVictoryConditions->isLocalAlliedVictory())report=true;
 if(TheVictoryConditions->gameEnded())report=true;if(TheGameLogic->desync||noData||disconnected)report=true;
 if(TheVictoryConditions->quit(local))report=true;if(mode==2)report=true;if(!report)return;
 if(TheGameSpyGame->getMode()!=1){float bound=TheWritableGlobalData?TheWritableGlobalData->minDuration*g_Va00DBA4E4:25.0f;if(TheVictoryConditions->elapsed()<bound+g_Va00DBA4E4)return;}
 bool canReportPackets=TheGameSpyGame->getFF4();bool reportPacket=false;
 if(canReportPackets){if(TheGameLogic->getDesync())goto report_packet;else if(TheVictoryConditions->isLocalAlliedVictory()&&!noData){
 for(int i=0;i<8;++i){AsciiString name;name=TheGameInfo->getSlot(i)->name;if(!name.isEmpty()){Player*p=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));if(p){GameSlot*slot=reinterpret_cast<GameInfo*>(TheGameSpyGame)->getSlot(i);if(TheVictoryConditions->hasWon(p)&&!slot->disconnected()){if(TheGameSpyGame->localSlot()==i)reportPacket=true;break;}}}}
 }}
 if(reportPacket){
 report_packet:;
 AsciiString packet=TheGameSpyGame->generateGameSpyGameResultsPacket(TheGameLogic->getDesync(),disconnected);BfmeOpaqueOwnedRecord1432 req;req.requestType=6;req.results=retailStr(packet);TheGameSpyPSMessageQueue->addRequest(req);
 }else{BfmeOpaqueOwnedRecord1432 req;req.requestType=7;TheGameSpyPSMessageQueue->addRequest(req);}
 if(!player->playerTemplate)return;int faction=player->playerTemplate->rva001FD234();
 if(stats.m_id==0){if(noData||TheGameLogic->desync){BfmeOpaqueOwnedRecord1432 req;req.requestType=1;req.m_04=1;req.email=retailStr(TheGameSpyInfo->nickname());req.nick=retailStr(TheGameSpyInfo->cdkey());req.password="";req.player=stats;req.addDesync=TheGameLogic->desync;req.addDiscon=noData;req.lastHouse=faction;TheGameSpyPSMessageQueue->addRequest(req);}return;}
 bool win=false;if(mode==2){if(lw)win=!lw->lost;}else win=TheVictoryConditions->isLocalAlliedVictory()&&!TheVictoryConditions->quit(local);
 if(TheGameLogic->desync)++core->m_140;else if(noData)++core->m_13c;else if(win){
 ++core->m_maps04_0[(unsigned char)faction];core->m_14a=0;core->m_maps04_3[(unsigned char)faction]=0;++core->m_146;++core->m_maps04_2[(unsigned char)faction];core->m_148=maxRef(core->m_146,core->m_148);
 word(core->m_maps04_5[(unsigned char)faction])=maxRef(word(core->m_maps04_5[(unsigned char)faction]),word(core->m_maps04_2[(unsigned char)faction]));
 if(mode==2){Rva0021937DTarget*hero=localSlot->hasHero?reinterpret_cast<Rva0021937DTarget*>(reinterpret_cast<char*>(localSlot)+0x64):0;if(hero)reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva002193D9(hero);}
 }else{
 ++core->m_maps04_1[(unsigned char)faction];++core->m_14a;++core->m_maps04_3[(unsigned char)faction];core->m_146=0;core->m_maps04_2[(unsigned char)faction]=0;core->m_14c=maxRef(core->m_14a,core->m_14c);
 word(core->m_maps04_4[(unsigned char)faction])=maxRef(word(core->m_maps04_4[(unsigned char)faction]),word(core->m_maps04_3[(unsigned char)faction]));
 if(mode==2){Rva0021937DTarget*hero=localSlot->hasHero?reinterpret_cast<Rva0021937DTarget*>(reinterpret_cast<char*>(localSlot)+0x64):0;if(hero)reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva00219407(hero);}
 }
 if(TheGameSpyGame&&!noData&&mode==1){if(TheGameSpyGame->ladder==1){++tournament.m_190;tournament.m_text19C="1v1";if(g_Va00DC0758>0)tournament.m_194=tournament.m_194>0?minRef(g_Va00DC0758,tournament.m_194):g_Va00DC0758;}
 else if(TheGameSpyGame->ladder==2){++tournament.m_192;tournament.m_text19C="2v2";if(g_Va00DC075C>0)tournament.m_198=tournament.m_198>0?minRef(g_Va00DC075C,tournament.m_198):g_Va00DC075C;}}
 if(mode!=2||!lw){ScoreKeeper*s=&player->score;
 core->m_mapsdc_5[(unsigned char)faction]+=(float)s->valueC8;core->m_mapsdc_3[(unsigned char)faction]+=(float)s->getTotalBuildingsDestroyed();core->m_mapsdc_4[(unsigned char)faction]+=(float)s->valueCC;
 core->m_mapsdc_2[(unsigned char)faction]+=(float)s->value70;core->m_mapsdc_0[(unsigned char)faction]+=(float)s->getTotalUnitsDestroyed();core->m_mapsdc_1[(unsigned char)faction]+=(float)s->value74;
 core->m_mapsdc_6[(unsigned char)faction]+=(float)s->value04;core->m_mapsdc_7[(unsigned char)faction]+=(float)s->value08;
 unsigned seconds=TheGameLogic->frame/(unsigned)g_Va00DBA4E4;Rva003844D7*rt=static_cast<Rva003844D7*>(core);
 rt->m_map178[(unsigned char)faction]+=(float)reinterpret_cast<Rva0039BF0B*>(s)->rva0039BF0B(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179));
 rt->m_map184[(unsigned char)faction]+=(float)reinterpret_cast<Rva0039BF39*>(s)->rva0039BF39(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179));
 rt->m_map154[(unsigned char)faction]+=(unsigned short)seconds;{
 void*n=reinterpret_cast<Rva005B8053*>(&rt->m_map160)->rva005B8053(&static_cast<const unsigned char&>((unsigned char)faction));
 if(n!=*reinterpret_cast<void**>(&rt->m_map160)){unsigned short&old=*reinterpret_cast<unsigned short*>(static_cast<char*>(n)+0x12);old=maxRef(reinterpret_cast<const unsigned short&>(seconds),old);}else word(rt->m_map160[(unsigned char)faction])=(unsigned short)seconds;
 n=reinterpret_cast<Rva005B8053*>(&rt->m_map16c)->rva005B8053(&static_cast<const unsigned char&>((unsigned char)faction));
 if(n!=*reinterpret_cast<void**>(&rt->m_map16c)&&*reinterpret_cast<unsigned short*>(static_cast<char*>(n)+0x12)){unsigned short&old=*reinterpret_cast<unsigned short*>(static_cast<char*>(n)+0x12);old=minRef(reinterpret_cast<const unsigned short&>(seconds),old);}else word(rt->m_map16c[(unsigned char)faction])=(unsigned short)seconds;
}
 }else{LivingWorldScoreKeeper*s=&lw->score;{const unsigned char buildKey=(unsigned char)faction;for(int i=0;i<5;++i)strategic.m_map19c[buildKey]+=(float)s->GetBuildingsOfTypeBuilt(i);}
 strategic.m_map1a8[(unsigned char)faction]+=(float)s->value98;strategic.m_map190[(unsigned char)faction]+=(float)s->value94;strategic.m_map184[(unsigned char)faction]+=(float)s->rva004EE33B();strategic.m_map16c[(unsigned char)faction]+=(float)s->valueB0;strategic.m_map178[(unsigned char)faction]+=(float)(s->getA8()+s->getAC());
 core->m_mapsdc_5[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE35D*>(s)->rva004EE35D(Rva00045411BitSet(0,7),reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4));
 core->m_mapsdc_3[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE3F9*>(s)->rva004EE3F9(Rva00045411BitSet(0,7),reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4));
 core->m_mapsdc_4[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE3AB*>(s)->rva004EE3AB(Rva00045411BitSet(0,7),reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4));
 core->m_mapsdc_2[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE35D*>(s)->rva004EE35D(reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4),Rva00045411BitSet(0,7));
 core->m_mapsdc_0[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE3F9*>(s)->rva004EE3F9(reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4),Rva00045411BitSet(0,7));
 core->m_mapsdc_1[(unsigned char)faction]+=(float)reinterpret_cast<Rva004EE3AB*>(s)->rva004EE3AB(reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4),Rva00045411BitSet(0,7));
 float seconds=(float)s->rva004EE043();_STL::vector<unsigned>times=s->v40;int sum=0;for(int i=0;i!=(int)times.size();++i)sum+=times[i];float elapsed=seconds-(float)(int)sum;
 float&totalSeconds=strategic.m_map154[(unsigned char)faction];seconds+=totalSeconds;totalSeconds=seconds;strategic.m_map160[(unsigned char)faction]=maxRef(elapsed,strategic.m_map160[(unsigned char)faction]);
 strategic.m_map1b4[(unsigned char)faction]+=s->getD8();strategic.m_map1c0[(unsigned char)faction]+=s->getDC();
 {float&sumMap=strategic.m_map1cc[(unsigned char)faction];int combined=s->valueE0+s->valueE4;const unsigned char key=(unsigned char)faction;sumMap+=(float)combined;strategic.m_map1d8[key]+=(float)s->valueE8;}strategic.m_map1e4[(unsigned char)faction]+=(float)s->valueEC;strategic.m_map1fc[(unsigned char)faction]+=(float)s->valueF0;strategic.m_map1f0[(unsigned char)faction]+=(float)s->v34.size();
 }
 if(mode==2)stats.setStrategicStats(strategic);else if(mode==1)stats.setTournamentStats(tournament);else stats.setOpenPlayStats(open);
 BfmeOpaqueOwnedRecord1432 req;req.requestType=1;req.m_04=3;req.email=retailStr(TheGameSpyInfo->nickname());req.nick=retailStr(TheGameSpyInfo->cdkey());req.password=retailStr(TheGameSpyInfo->password());req.player=stats;req.addDesync=TheGameLogic->desync;req.addDiscon=noData;req.lastHouse=faction;TheGameSpyPSMessageQueue->addRequest(req);
 TheGameSpyPSMessageQueue->store(stats);BfmeOpaqueOwnedRecord1408 response;response.kind=0;response.player=stats;TheGameSpyPSMessageQueue->addResponse(response);Rva00556FB8(reinterpret_cast<const Gen_uw_00385371&>(stats));TheGameSpyInfo->updated(stats);
}
