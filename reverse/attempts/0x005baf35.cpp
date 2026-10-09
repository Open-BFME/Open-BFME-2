// ?rva005BAF35@Rva005BB5F6@@QAEXAAVPeerResponse@@@Z
// partial score=0.985 date=2026-10-09
// AptOnlineQuickMatch::OnMatched
// partial score=0.985 date=2026-10-09
// cl: /vmg /vmm /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BF1 donor2f243e26d AptOnlineQuickMatch.cpp rva0055A240 semantic guide.
// Target5BB5F6..5BBDAC: two response drains, NAT failure prompt, native all-stats1348.
#include <cstdlib>
#include <map>
#include <list>
#include <cstring>
#include <string>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class PeerResponse {public:
    PeerResponse();
    ~PeerResponse();
    int unknown_00;
    std::string unknown_04;
    std::string unknown_10;
    std::string unknown_1c;
    std::wstring unknown_28;
    std::string unknown_34;
    std::string unknown_40;
    std::wstring unknown_4c;
    std::string unknown_58;
    std::string unknown_64;
    std::string unknown_70;
    std::string unknown_7c;
    std::string unknown_88[8];
    std::string unknown_e8;
    std::string unknown_f4;
    _STL::vector<AsciiString> unknown_100;
    union {
        struct { int value; } payload_word0;
        struct { int value; } payload_word1;
        struct { int words[8]; } payload_32;
        struct { int first; int second; } payload_8a;
        struct { int value; } payload_4;
        struct { int words[3]; } payload_12;
        struct { int first; int second; } payload_8b;
        struct { int words[143]; } payload_572;
        struct{int reason,progress,mapIndex,seed;unsigned IP[8];unsigned short ports[8];int side[8],color[8],nat[8],teams[8];} qmStatus;
        struct { int words[79]; } payload_316;
        struct { int words[48]; } payload_192;
    };
};
class PSPlayerAllStats {public:int id;char rest[0x548-4];PSPlayerAllStats(int);PSPlayerAllStats(const PSPlayerAllStats &);~PSPlayerAllStats();void setID(int);};
class GameWindow;
class PlayerInfo {public:AsciiString name,baseName,locale;int words[10];PlayerInfo();PlayerInfo(const PlayerInfo &);~PlayerInfo();};
struct AsciiComparator {bool operator()(const AsciiString &,const AsciiString &)const;};
typedef _STL::map<AsciiString,PlayerInfo,AsciiComparator> PlayerInfoMap;
#define V(n) virtual void slot##n();
class GameSpyInfoInterface {public:
 V(0)virtual void reset();V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)virtual void updatePlayerInfo(PlayerInfo,AsciiString);V(20)
 virtual PlayerInfoMap *getPlayerInfoMap();
 V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)V(31)V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)V(58)V(59)V(60)V(61)V(62)V(63)V(64)V(65)V(66)V(67)V(68)V(69)V(70)V(71)V(72)V(73)V(74)V(75)V(76)V(77)V(78)V(79)V(80)V(81)V(82)V(83)V(84)virtual unsigned getLocalIP();virtual unsigned short getLocalPort();V(86)V(87)
 virtual bool isDisconnectedAfterGameStart(void *);virtual void markAsDisconnectedAfterGameStart(int);
 V(90)V(91)V(92)virtual int getMaxMessagesPerUpdate();};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyPeerMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)virtual bool getResponse(PeerResponse &);};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class GameSpyPSMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)virtual void trackPlayerStats(PSPlayerAllStats);V(9)V(10)V(11)virtual PSPlayerAllStats findPlayerStatsByID(int);};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class GameTextInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)virtual UnicodeString fetch(const char *,bool *exists=0);virtual UnicodeString fetch(const AsciiString &,bool *exists=0);V(16)virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;
enum NameKeyType;class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)V(31)V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)V(58)V(59)virtual GameWindow *winGetWindowFromId(GameWindow *,int);};
extern GameWindowManager *TheWindowManager;
extern int g_00DB9198;
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int=-1,bool=true);
enum SlotState {SLOT_OPEN,SLOT_CLOSED,SLOT_AI2,SLOT_AI3,SLOT_AI4,SLOT_AI5,SLOT_PLAYER};
struct IPAndPort{unsigned ip;unsigned short port;IPAndPort(unsigned i,unsigned short p):port(p),ip(i){}};
struct GameSlotConnectInfo{unsigned ip;unsigned short port;GameSlotConnectInfo():ip(0),port(0){}GameSlotConnectInfo(unsigned i,unsigned short p):port(p),ip(i){}};
class GameSlot {public:char at00[0xc];int color;char at10[0xc];int team;char at20[0x20];int nat;bool isHuman()const;void setState(SlotState,UnicodeString=UnicodeString::TheEmptyString,const GameSlotConnectInfo* = &GameSlotConnectInfo());void setPlayerTemplate(int);};
struct Rva004FDCE1AsciiField {AsciiString get()const;};
struct SlotFields {char pad[0x1ac];int profile;};
class GameInfo {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)virtual void clear();virtual void startGame(int);V(12)virtual int localSlot();char pad04[0xd];bool inProgress;int getSlotNum(AsciiString)const;void enterGame();void setSeed(int);void setMap(AsciiString);};
class GameSpyGameSlot:public GameSlot {public:char at44[0x18c];int rva1d0,rva1d4;};class GameSpyStagingRoom:public GameInfo {public:GameSpyGameSlot *getGameSpySlot(int);void launchGame();};
extern GameSpyStagingRoom *TheGameSpyGame;
class Rva005A6D47 {public:virtual void *destroy(unsigned);void rva005A8F57();void rva005A8ABF(int,const char *);};
extern Rva005A6D47 *g_Va00E063F8;
struct Rva005BA3AD {bool rva005BA3AD();};struct Rva005BA31F {int rva005BA31F();};
class Rva00222A8BTarget {public:int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E06550;
static __forceinline void *movieLevel(){return *(void **)((char *)*(void **)((char *)g_Va00E06550+0x58)+0x274);}
class Shell {public:void rva0035BEC7();};extern Shell *TheShell;
void HandleBuddyResponses();void rva005BDAC1();void rva005AF12F(void *);void Rva00511730(int);void Rva00548C1ACleanup();void GSMessageBoxOk(UnicodeString,UnicodeString,void(*)()=0);void TearDownGameSpy();
struct TargetRef00217D4C {void *vtbl;int references;};void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;typedef void(FunctorTarget::*FunctorMethod)(int);
struct FunctorBinding {FunctorTarget *target;unsigned pad;FunctorMethod method;FunctorBinding(FunctorMethod m,FunctorTarget*t):target(t),method(m){}};
struct Rva0057BC63FunctorHolder {Rva0057BC63FunctorHolder(const FunctorBinding &);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o):ptr(o.ptr){if(ptr)++ptr->references;}TargetRef00217D4C *ptr;~Rva0057BC63FunctorHolder(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva0023E8D8 : public Rva0057BC63FunctorHolder {public:__forceinline Rva0023E8D8(const FunctorBinding &b):Rva0057BC63FunctorHolder(b){} Rva0023E8D8(const Rva0023E8D8&o):Rva0057BC63FunctorHolder(o){} };
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
static __forceinline FunctorBinding bind(FunctorMethod m,FunctorTarget*t){FunctorBinding r(m,t);return r;}
struct Rva005BB5F6 {char prefix[0x60];int state;char at64[0x16];bool matched;char at7b[0x21];int mode;void rva005BB5F6();void rva005BA39F(int);void rva005BAF35(PeerResponse &);};
#undef V
void Rva005BB5F6::rva005BB5F6(){
 HandleBuddyResponses();rva005BDAC1();
 if(TheGameSpyGame&&TheGameSpyGame->inProgress){
  if(TheGameSpyInfo->isDisconnectedAfterGameStart(0))return;
  int allowed=TheGameSpyInfo->getMaxMessagesPerUpdate();bool important=false;PeerResponse r;
  while(allowed--&&!important&&TheGameSpyPeerMessageQueue->getResponse(r)){
   rva005AF12F(&r);
   switch(r.unknown_00){case 1:{important=true;AsciiString reason;reason.format("GUI:GSDisconReason%d",r.payload_word0.value);
    NameKeyType key=TheNameKeyGenerator->nameToKey("ScoreScreen.wnd:ListboxChatWindowScoreScreen");GameWindow *w=TheWindowManager->winGetWindowFromId(0,key);
    if(w)GadgetListBoxAddEntryText(w,TheGameText->fetch(reason),g_00DB9198,-1);
    TheGameSpyInfo->markAsDisconnectedAfterGameStart(r.payload_word0.value);
   }break;}
  }return;
 }
 if(g_Va00E063F8){
  g_Va00E063F8->rva005A8F57();
  if(((Rva005BA3AD *)g_Va00E063F8)->rva005BA3AD()){TheGameSpyGame->startGame(0);TheGameSpyGame->launchGame();return;}
  else if((unsigned char)((Rva005BA31F *)g_Va00E063F8)->rva005BA31F()){
   void *memory=g_Va00E063F8?g_Va00E063F8->destroy(0):0;operator delete(memory);g_Va00E063F8=0;state=3;
   Rva00437F61(0,TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:NATNegotiationFailed"),Rva0023E8D8(bind(reinterpret_cast<FunctorMethod>(&Rva005BB5F6::rva005BA39F),(FunctorTarget *)this)));
   ((Rva00222A8BTarget*)g_bfmeAptWindowManager)->invoke(movieLevel(),"CallChild",1,"CloseFoundAndReset",0,0,0,0);return;
  }
 }
 int allowed=TheGameSpyInfo->getMaxMessagesPerUpdate();bool important=false;PeerResponse r;
 while(allowed--&&!important&&TheGameSpyPeerMessageQueue->getResponse(r)){
  if(!state)rva005AF12F(&r);else Rva00511730(0);
  switch(r.unknown_00){
  case 16:{
   AsciiString nick;PlayerInfoMap::iterator found=TheGameSpyInfo->getPlayerInfoMap()->find(r.unknown_10.c_str());
   if(found!=TheGameSpyInfo->getPlayerInfoMap()->end())nick=found->second.baseName;else nick=r.unknown_10.c_str();
   if(!_strcmpi(r.unknown_e8.c_str(),"STATS")){
    AsciiString data=r.unknown_f4.c_str();AsciiString idText;data.nextToken(&idText," ");int id=atoi(idText.str());
    PSPlayerAllStats stats(0);PSPlayerAllStats oldStats=TheGameSpyPSMessageQueue->findPlayerStatsByID(id);stats.setID(id);
    if(stats.id&&!oldStats.id)TheGameSpyPSMessageQueue->trackPlayerStats(stats);
    for(int i=0;i<8;++i){GameSlot *slot=TheGameSpyGame->getGameSpySlot(i);if(slot&&slot->isHuman()&&((Rva004FDCE1AsciiField *)slot)->get().compareNoCase(nick)==0){((SlotFields *)slot)->profile=id;break;}}
   }else{
    int slot=TheGameSpyGame->getSlotNum(nick);
    if(slot>=0&&slot<8&&!_strcmpi(r.unknown_e8.c_str(),"NAT")){important=true;if(g_Va00E063F8)g_Va00E063F8->rva005A8ABF(slot,r.unknown_f4.c_str());}
   }
  }break;
  case 1:{important=true;UnicodeString title,body;AsciiString reason;reason.format("GUI:GSDisconReason%d",r.payload_word0.value);
   title=TheGameText->fetch("GUI:GSErrorTitle");body=TheGameText->fetch(reason);Rva00548C1ACleanup();GSMessageBoxOk(title,body);
   TheGameSpyInfo->reset();TheShell->rva0035BEC7();TearDownGameSpy();}break;
  case 8:{if(r.payload_word0.value==0){UnicodeString s;s.format(L"Created staging room");}else{UnicodeString s;s.format(L"createStagingRoom result: %d",r.payload_word0.value);}}break;
  case 9:{unsigned char ok=*(unsigned char *)((char *)&r.payload_word0+4);if(ok==1){UnicodeString s;s.format(L"joinStagingRoom result: %d",ok);}else{UnicodeString s;s.format(L"joinStagingRoom result: %d",ok);}}break;
  case 4:{UnicodeString s;s.format(L"Staging room list callback",r.unknown_10.c_str());}break;
  case 17:{important=true;switch(r.payload_8a.first){
   case 4:{UnicodeString s;s.format(TheGameText->fetchFormat("QM:WORKING"),r.payload_8a.second);}break;
   case 5:{UnicodeString s;s.format(TheGameText->fetchFormat("QM:POOLSIZE"),r.payload_8a.second);}break;
   case 7:((Rva00222A8BTarget*)g_bfmeAptWindowManager)->invoke(movieLevel(),"CallChild",1,"DoOpenFound",0,0,0,0);rva005BAF35(r);break;
  }}break;
  }
 }
}

// Native5BA39F..5BA3AD RET4: prompt result clears quick-match state only for zero.
void Rva005BB5F6::rva005BA39F(int result){if(!result)state=0;}

typedef char PeerResponseSize[sizeof(PeerResponse)==0x348?1:-1];
typedef char StatsSize[sizeof(PSPlayerAllStats)==0x548?1:-1];

class GameSpyConfigInterface {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual _STL::list<AsciiString> getQMMaps();};extern GameSpyConfigInterface *TheGameSpyConfig;
class MapMetaData {public:char pad[0x20];int players;};class MapCache{public:const MapMetaData *findMap(AsciiString);};extern MapCache *TheMapCache;
class Rva003821E2 {public:void assign(UnicodeString);};class Rva004FDD36AsciiField{public:void rva004FDD36(AsciiString);};
void Rva00559FAC(int,void*);void SendStatsToOtherPlayers(GameInfo*);
class Rva005A734B{public:char storage[0x974];Rva005A734B();};class NAT{public:void attachSlotList(GameInfo*,int,unsigned,unsigned,bool);};
// ?Rva005BB5F6::rva005BAF35 present-unmatched
void Rva005BB5F6::rva005BAF35(PeerResponse &resp){
 TheGameSpyGame->clear();TheGameSpyGame->enterGame();TheGameSpyGame->setSeed(resp.payload_572.words[3]);
 {GameSpyStagingRoom *game=TheGameSpyGame;int m=mode;*(bool*)((char*)game+0xff4)=true;*(int*)((char*)game+0xff8)=m;}
 int rules[10];memset(rules,0xff,sizeof(rules));Rva00559FAC(0,rules);rules[0]=0;rules[2]=0;memcpy((char*)TheGameSpyGame+0x60,rules,sizeof(rules));
 int numPlayers=0;for(int i=0;i<8;++i)if(!resp.unknown_88[i].empty())++numPlayers;
 _STL::list<AsciiString> maps=TheGameSpyConfig->getQMMaps();
 for(_STL::list<AsciiString>::const_iterator it=maps.begin();it!=maps.end();++it){AsciiString map=*it;map.toLower();const MapMetaData *md=TheMapCache->findMap(map);if(md&&md->players==numPlayers){TheGameSpyGame->setMap(*it);if(resp.payload_572.words[2]--==0)break;}}
 int numPerTeam=numPlayers/2;if(!numPerTeam)numPerTeam=1;
 for(int i=0;i<8;++i){GameSpyGameSlot *slot=TheGameSpyGame->getGameSpySlot(i);
  if(resp.unknown_88[i].empty())slot->setState(SLOT_CLOSED);else{
   AsciiString aName=resp.unknown_88[i].c_str();char baseName[256]="";strncpy(baseName,resp.unknown_88[i].c_str(),255);
   PlayerInfo player;player.name=resp.unknown_88[i].c_str();player.baseName=baseName;TheGameSpyInfo->updatePlayerInfo(player,AsciiString::TheEmptyString);
   UnicodeString uName;uName.translate(baseName);IPAndPort connect(resp.qmStatus.IP[i],resp.qmStatus.ports[i]);
   slot->setState(SLOT_PLAYER,uName,(const GameSlotConnectInfo*)&connect);slot->color=resp.payload_572.words[24+i];slot->setPlayerTemplate(resp.payload_572.words[16+i]);slot->nat=resp.payload_572.words[32+i];((Rva004FDD36AsciiField*)slot)->rva004FDD36("");slot->team=i/numPerTeam;
   switch(numPerTeam){case 1:slot->rva1d0=resp.payload_572.words[40+i];slot->rva1d4=-1;break;case 2:slot->rva1d0=-1;slot->rva1d4=resp.payload_572.words[40+i];break;default:slot->rva1d0=-1;slot->rva1d4=-1;}
   if(i==0)((Rva003821E2*)TheGameSpyGame)->assign(uName);
  }
 }
 SendStatsToOtherPlayers(TheGameSpyGame);matched=true;
 if(g_Va00E063F8){operator delete(g_Va00E063F8->destroy(0));g_Va00E063F8=0;}
 if(TheGameSpyGame->localSlot()>=0){g_Va00E063F8=(Rva005A6D47*)new Rva005A734B;struct Address{unsigned ip;unsigned short port;} address;address.ip=TheGameSpyInfo->getLocalIP();address.port=TheGameSpyInfo->getLocalPort();*(unsigned*)((char*)TheGameSpyGame+0x38)=address.ip;*(unsigned*)((char*)TheGameSpyGame+0x3c)=*(const volatile unsigned*)&address.port;
 unsigned &transportIP=*(unsigned*)((char*)TheGameSpyGame+0x38);((NAT*)g_Va00E063F8)->attachSlotList(TheGameSpyGame,TheGameSpyGame->localSlot(),transportIP,30000,TheGameSpyGame->localSlot()==0);}
}
