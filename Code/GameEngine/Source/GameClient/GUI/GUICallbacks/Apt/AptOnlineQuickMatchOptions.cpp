// cl: /vmg /vmm /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BF1 donor2f243e26d AptOnlineQuickMatch.cpp rva0055A240 semantic guide.
// Target5BB5F6..5BBDAC: two response drains, NAT failure prompt, native all-stats1348.
// Start-request5BBF15..5BC474: ZH WOLQuickMatchMenu buttonStart is the
// semantic guide; BFME2 WB and native bytes fix the request fields, rank
// range (one eighth), class offsets, calls, and omitted random-side retry.
// Address names preserve unknown native class/method identity.
#include <cstdlib>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}
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
        struct { int words[79]; } payload_316;
        struct { int words[48]; } payload_192;
    };
};
class PSPlayerAllStats {public:int id;char rest[0x548-4];PSPlayerAllStats(int);PSPlayerAllStats(const PSPlayerAllStats &);~PSPlayerAllStats();void setID(int);};
class GameWindow;
class PlayerInfo {public:int id;AsciiString baseName;char rest[20];};
struct AsciiComparator {bool operator()(const AsciiString &,const AsciiString &)const;};
typedef _STL::map<AsciiString,PlayerInfo,AsciiComparator> PlayerInfoMap;
#define V(n) virtual void slot##n();
class GameSpyInfoInterface {public:
 V(0)virtual void reset();V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)
 virtual PlayerInfoMap *getPlayerInfoMap();
 V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)virtual int getLocalProfileID();V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)V(58)V(59)V(60)V(61)V(62)V(63)V(64)V(65)V(66)V(67)V(68)V(69)V(70)virtual AsciiString &getPingString();V(72)V(73)V(74)V(75)V(76)V(77)V(78)V(79)V(80)V(81)V(82)V(83)V(84)V(85)V(86)V(87)
 virtual bool isDisconnectedAfterGameStart(void *);virtual void markAsDisconnectedAfterGameStart(int);
 V(90)V(91)V(92)virtual int getMaxMessagesPerUpdate();};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyPeerMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)virtual bool getResponse(PeerResponse &);};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class Rva00385333;
class GameSpyPSMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)virtual void trackPlayerStats(PSPlayerAllStats);V(9)V(10)V(11)virtual PSPlayerAllStats findPlayerStatsByID(int);virtual Rva00385333 getStats(int);};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
class GameTextInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)virtual UnicodeString fetch(const char *,bool *exists=0);virtual UnicodeString fetch(const AsciiString &,bool *exists=0);V(16)virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;
enum NameKeyType;class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)virtual int getLocalProfileID();V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)V(58)V(59)virtual GameWindow *winGetWindowFromId(GameWindow *,int);};
extern GameWindowManager *TheWindowManager;
extern int g_00DB9198;
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int=-1,bool=true);
class GameSlot {public:bool isHuman()const;};
struct Rva004FDCE1AsciiField {AsciiString get()const;};
struct SlotFields {char pad[0x1ac];int profile;};
class GameInfo {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)virtual void startGame(int);char pad04[0xd];bool inProgress;int getSlotNum(AsciiString)const;};
class GameSpyGameSlot:public GameSlot {};class GameSpyStagingRoom:public GameInfo {public:GameSpyGameSlot *getGameSpySlot(int);void launchGame();};
extern GameSpyStagingRoom *TheGameSpyGame;
class Rva005A6D47 {public:virtual void *destroy(unsigned);int rva005A8F57();void rva005A8ABF(int,const char *);};
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
struct BfmeOpaqueOwnedRecord492;
struct Rva005BB5F6 {char prefix[0x60];int state;void rva005BB5F6();void rva005BBDAC(BfmeOpaqueOwnedRecord492 &);void rva005BBF15();void rva005BA39F(int);void rva005BAF35(const PeerResponse &);};
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

struct BfmeOpaqueOwnedRecord492 {
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	int unknown_00;
	std::string unknown_04;
        std::wstring unknown_10;
        std::string unknown_1c;
        std::string unknown_28;
        std::string unknown_34;
        std::string unknown_40;
        std::string unknown_4c;
        std::string unknown_58;
        std::string unknown_64;
        std::string unknown_70[8];
        unsigned int unknown_d0[10];
        std::string unknown_f8;
        std::vector<bool> unknown_104;
        union {
          struct {
            int word;
          } payload_word0;
          struct {
            int word;
          } payload_word1;
          struct {
            int word;
          } payload_word2;
          struct {
            bool value;
          } payload_flag0;
          struct {
            bool value;
          } payload_flag1;
          struct {
            int word;
          } payload_word3;
          struct {
            int words[15];
          } payload_60;
          struct {
            int words[53];
          } payload_212a;
          struct {
            bool value;
          } payload_flag2;
          struct {
            int words[26];
          } payload_104;
          struct {
            int words[7];
          } payload_28;
          struct {
            int first;
            int second;
          } payload_8c;
        };
};

class GameSpyConfigInterface {
public:
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual int getPingTimeoutInMs();
  virtual void s4();
  virtual void s5();
  virtual _STL::list<AsciiString> getQMMaps();
  virtual int getQMBotID();
  virtual int getQMChannel();
};
extern GameSpyConfigInterface *TheGameSpyConfig;
class Rva0054D8D8 {
public:
  UnicodeString name;
  char p4[8];
  int players;
  char p10[9];
  bool randomFactions;
  char p1a[2];
  _STL::list<AsciiString> maps;
  _STL::list<AsciiString> factions;
  char p24[4];
  AsciiString address;
  unsigned short port;
};
void GadgetComboBoxGetSelectedPos(GameWindow *, int *);
#include <cmath>
#include <ctime>
class Rva00385333 {
public:
  char bytes[0x1a8];
  ~Rva00385333();
};
class Rva00553E47StatsCore;
class Rva00553E47StatsCore;
class Rva00559D0CRankWeights {
public:
  int rva00559D0C(const Rva00553E47StatsCore *) const;
};
// The Other rank-weight table at VA 0x00E06000, defined (with the layout
// Rva00559A11.cpp proves) in the unit whose arg-ctor bodies fill it,
// Common/Rva007ABEF3ArgCtorInits.cpp.
extern Rva00559D0CRankWeights g_00E06000;
class Rva0054D974 {
public:
  Rva0054D8D8 *rva0054D6C8(int);
};
extern Rva0054D974 *TheLadderList;
class PlayerTemplate {
public:
  char p[0x18];
  AsciiString side;
};
class PlayerTemplateStore {
public:
  char p[0xc];
  char *begin, *end;
  const PlayerTemplate *getNthPlayerTemplate(int) const;
  int count() const { return (end - begin) / 0x1dc; }
};
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameClientRandomValue(int, int, char *, int);
class OptionPreferences {
public:
  OptionPreferences();
  virtual ~OptionPreferences();
  char p[0x10];
  int getFirewallBehavior();
};
class LadderPref {
public:
  LadderPref() {}
  LadderPref(const LadderPref &);
  ~LadderPref();
  UnicodeString name;
  AsciiString address;
  unsigned short port;
  long lastPlayDate;
};
class LadderPreferences {
public:
  LadderPreferences();
  virtual ~LadderPreferences();
  char p[0x1c];
  bool loadProfile(int);
  virtual bool write();
  void addRecentLadder(LadderPref);
};
class Rva00323674 {
public:
  int rva00323674() const;
};
class Rva003236C4 {
public:
  int rva003236C4(int);
};
class Rva00237E28 {
public:
  int v[4];
  void rva00237E28(Rva00237E28 *);
};
extern int g_00E0654C, g_009C0758, g_009C075C, g_Va00E02548, g_Va00E0254C;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct NativeQuickMatchRequest {
  int minPointPercentage, maxPointPercentage, points, widenTime, ladderID, ladderPassCRC, maxPing,
      maxDiscons, searchTime;
  char pings[20];
  int numPlayers, botID, roomID, side, color, NAT;
  Rva00237E28 data;
  unsigned exeCRC, iniCRC;
};
void *GadgetComboBoxGetItemData(GameWindow *, int);
void Rva005BB5F6::rva005BBF15() {
  BfmeOpaqueOwnedRecord492 request;
  request.unknown_00 = 16;
  rva005BBDAC(request);
  UnicodeString u;
  AsciiString a;
  NativeQuickMatchRequest &qm = *(NativeQuickMatchRequest *)&request.payload_word0;
  qm.maxPointPercentage = 100;
  qm.minPointPercentage = 0;
  qm.widenTime = 0;
  qm.maxDiscons = 0x7fffffff;
  int val;
  GadgetComboBoxGetSelectedPos(*(GameWindow **)((char *)this + 0x8c), &val);
  if (val < 0)
    val = 0;
  if (val >= g_00E0654C - 1)
    qm.maxPing = TheGameSpyConfig->getPingTimeoutInMs();
  else
    qm.maxPing = (val + 1) * 100;
  qm.maxPing = qm.maxPing * 255 / TheGameSpyConfig->getPingTimeoutInMs();
  Rva00385333 stats = TheGameSpyPSMessageQueue->getStats(TheGameSpyInfo->getLocalProfileID());
  qm.points =
      ((Rva00559D0CRankWeights *)&g_00E06000)->rva00559D0C((Rva00553E47StatsCore *)&stats);
  int ladderIndex, index, selected;
  GameWindow **ladderWindow = (GameWindow **)((char *)this + 0x90);
  GadgetComboBoxGetSelectedPos(*ladderWindow, &selected);
  ladderIndex = (int)GadgetComboBoxGetItemData(*ladderWindow, selected);
  Rva0054D8D8 *ladder = 0;
  if (ladderIndex < 0)
    ladderIndex = 0;
  if (ladderIndex) {
    ladder = TheLadderList->rva0054D6C8(ladderIndex);
    if (!ladder)
      ladderIndex = 0;
  }
  qm.ladderID = ladderIndex;
  qm.ladderPassCRC = 0;
  index = -1;
  GameWindow **sideWindow = (GameWindow **)((char *)this + 0x88);
  GadgetComboBoxGetSelectedPos(*sideWindow, &selected);
  if (selected >= 0)
    index = (int)GadgetComboBoxGetItemData(*sideWindow, selected);
  qm.side = index;
  if (ladder && ladder->randomFactions) {
    int sideNum =
        GetGameClientRandomValue(0, ladder->factions.size() - 1,
                                 "C:"
                                 "\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameC"
                                 "lient\\Gui\\GUICallbacks\\Apt\\AptOnlineQuickMatch.cpp",
                                 710);
    _STL::list<AsciiString>::const_iterator i = ladder->factions.begin();
    while (sideNum) {
      ++i;
      --sideNum;
    }
    if (i != ladder->factions.end()) {
      int count = ThePlayerTemplateStore->count();
      AsciiString side = *i;
      for (int c = 0; c < count; ++c) {
        const PlayerTemplate *p = ThePlayerTemplateStore->getNthPlayerTemplate(c);
        if (p && p->side == side) {
          qm.side = c;
          break;
        }
      }
    }
  }
  Rva00323674 *color = (Rva00323674 *)((char *)this + 0x80);
  qm.color = ((Rva003236C4 *)color)->rva003236C4(color->rva00323674());
  OptionPreferences natPref;
  qm.NAT = natPref.getFirewallBehavior();
  if (ladderIndex)
    qm.numPlayers = ladder ? ladder->players * 2 : 2;
  else {
    GadgetComboBoxGetSelectedPos(*(GameWindow **)((char *)this + 0x84), &val);
    if (val < 0)
      val = 0;
    qm.numPlayers = (val + 1) * 2;
  }
  switch (qm.numPlayers) {
  case 2:
    *(int *)((char *)this + 0x9c) = 1;
    break;
  case 4:
    *(int *)((char *)this + 0x9c) = 2;
    break;
  default:
    *(int *)((char *)this + 0x9c) = 0;
    break;
  }
  qm.searchTime = 10000;
  strncpy(qm.pings, TheGameSpyInfo->getPingString().str(), 17);
  qm.pings[16] = 0;
  qm.botID = TheGameSpyConfig->getQMBotID();
  qm.roomID = TheGameSpyConfig->getQMChannel();
  ((Rva00237E28 *)((char *)TheWritableGlobalData + 0xb08))->rva00237E28(&qm.data);
  qm.exeCRC = *(unsigned *)((char *)TheWritableGlobalData + 0xb04);
  qm.iniCRC = *(unsigned *)((char *)TheWritableGlobalData + 0xb38);
  unsigned points;
  if (*(int *)((char *)this + 0x9c) == 1) {
    qm.points = g_009C0758;
    points = g_Va00E02548;
  } else if (*(int *)((char *)this + 0x9c) == 2) {
    qm.points = g_009C075C;
    points = g_Va00E0254C;
  } else {
    qm.points = -1;
    points = 0;
  }
  if (qm.points <= 0)
    qm.points = -1;
  qm.minPointPercentage = 1;
  qm.maxPointPercentage = 0x7fffffff;
  if (points)
    qm.maxPointPercentage = points;
  int base = qm.points > 0 ? qm.points : qm.maxPointPercentage;
  double range = points * 0.125;
  int low = base - (int)ceil(range);
  qm.minPointPercentage = _STL::max(low, 1);
  qm.maxPointPercentage = _STL::min(base + (int)floor(range), qm.maxPointPercentage);
  // The native request dispatch is vtable slot six.
  struct Queue {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void addRequest(const BfmeOpaqueOwnedRecord492 &);
  };
  ((Queue *)TheGameSpyPeerMessageQueue)->addRequest(request);
  if (ladderIndex > 0) {
    LadderPreferences prefs;
    prefs.loadProfile(TheGameSpyInfo->getLocalProfileID());
    LadderPref p;
    p.lastPlayDate = time(0);
    p.address = ladder->address;
    p.port = ladder->port;
    p.name = ladder->name;
    prefs.addRecentLadder(p);
    prefs.write();
  }
}
