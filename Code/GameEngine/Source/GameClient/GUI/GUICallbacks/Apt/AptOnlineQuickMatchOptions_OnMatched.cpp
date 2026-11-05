// cl: /DBFME_ASCII_DTOR_DECL /vmg /vmm /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from AptOnlineQuickMatchOptions.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// BF1 donor2f243e26d AptOnlineQuickMatch.cpp rva0055A240 semantic guide.
// Target5BB5F6..5BBDAC: two response drains, NAT failure prompt, native all-stats1348.
// Start-request5BBF15..5BC474: ZH WOLQuickMatchMenu buttonStart is the
// semantic guide; BFME2 WB and native bytes fix the request fields, rank
// range (one eighth), class offsets, calls, and omitted random-side retry.
// WB places every member in AptOnlineQuickMatch.cpp and names 0x5BAF35
// AptOnlineQuickMatch::OnMatched (callgraph lead score 6); the other method
// names stay address-derived.
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <list>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

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
        struct{int reason,progress,mapIndex,seed;unsigned IP[8];unsigned short ports[8];int side[8],color[8],nat[8],teams[8];} qmStatus;
        struct { int words[79]; } payload_316;
        struct { int words[48]; } payload_192;
    };
};
class PSPlayerAllStats {public:int id;char rest[0x548-4];PSPlayerAllStats(int);PSPlayerAllStats(const PSPlayerAllStats &);~PSPlayerAllStats();void setID(int);};
class GameWindow;
#include "../../../../../Include/GameNetwork/PlayerInfo.h"
struct AsciiComparator {bool operator()(AsciiString,AsciiString)const;};
typedef _STL::map<AsciiString,PlayerInfo,AsciiComparator> PlayerInfoMap;
#define V(n) virtual void slot##n();
#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameSpyPeerMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)virtual bool getResponse(PeerResponse &);};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class Rva00385333;
class GameSpyPSMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)virtual void trackPlayerStats(PSPlayerAllStats);V(9)V(10)V(11)virtual PSPlayerAllStats findPlayerStatsByID(int);virtual Rva00385333 getStats(int);};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
#include "../../../../../Include/GameClient/GameText.h"
enum NameKeyType;
#include "../../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
extern int GameSpyColor[];
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int=-1,bool=true);
enum SlotState {SLOT_OPEN,SLOT_CLOSED,SLOT_AI2,SLOT_AI3,SLOT_AI4,SLOT_AI5,SLOT_PLAYER};
struct IPAndPort{unsigned ip;unsigned short port;IPAndPort(unsigned i,unsigned short p):port(p),ip(i){}};
struct GameSlotConnectInfo{unsigned ip;unsigned short port;GameSlotConnectInfo():ip(0),port(0){}GameSlotConnectInfo(unsigned i,unsigned short p):port(p),ip(i){}};
#include "../../../../../Include/GameNetwork/GameInfo.h"
struct Rva004FDCE1AsciiField {AsciiString get()const;};
struct SlotFields {char pad[0x1ac];int profile;};
class GameSpyGameSlot:public GameSlot {public:char at1AC[0x1D0 - 0x1AC];int rva1d0,rva1d4;};
#include "../../../../../Include/GameNetwork/GameSpyStagingRoom.h"

extern GameSpyStagingRoom *TheGameSpyGame;
class Rva005A6D47 {public:virtual void *destroy(unsigned);int rva005A8F57();};
// Bind the existing NAT datum; retain this unit's access view at use sites.
struct NAT {void processGlobalMessage(int,const char *);	// 0x005A8ABF, rowed
 void attachSlotList(GameInfo*,int,unsigned,unsigned,bool);};
extern NAT *TheNAT;
class PortNegotiationSchema {public:bool rva005DBA9C(bool);};
struct Rva005BA3AD
{
public:
	bool rva005BA3AD();
	char prefix[0x28]; // +0x00
	PortNegotiationSchema schema; // +0x28
};
struct Rva005BA31F {int rva005BA31F();};
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E06550;
static __forceinline void *movieLevel(){return *(void **)((char *)*(void **)((char *)g_Va00E06550+0x58)+0x274);}
#include "../../../../../Include/GameClient/Shell.h"
extern Shell *TheShell;
void HandleBuddyResponses();void HandlePersistentStorageResponses();class AptMessengerOnline { public: static bool ProcessGameSpyResponse(void *); };void Rva00511730(int);void Rva00548C1ACleanup();void GSMessageBoxOk(UnicodeString,UnicodeString,void(*)()=0);void TearDownGameSpy();
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;typedef void(FunctorTarget::*FunctorMethod)(int);
#include "../../../../../Include/GameClient/FunctorBinding.h"
struct Rva0057BC63FunctorHolder {Rva0057BC63FunctorHolder(const FunctorBinding &);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o):ptr(o.ptr){if(ptr)++ptr->references;}TargetRef00217D4C *ptr;~Rva0057BC63FunctorHolder(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva0023E8D8 : public Rva0057BC63FunctorHolder {public:__forceinline Rva0023E8D8(const FunctorBinding &b):Rva0057BC63FunctorHolder(b){} Rva0023E8D8(const Rva0023E8D8&o):Rva0057BC63FunctorHolder(o){} };
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
static __forceinline FunctorBinding bind(FunctorMethod m,FunctorTarget*functorTarget){FunctorBinding r(m,functorTarget);return r;}
struct BfmeOpaqueOwnedRecord492;class Rva0054D8D8;
struct AptOnlineQuickMatch {char prefix[0x60];int state;char at64[0x16];bool matched;char at7b[0x21];int mode;void rva005BB5F6();void rva005BBDAC(BfmeOpaqueOwnedRecord492 &);void rva005BBF15();void rva005BA39F(int);void OnMatched(PeerResponse &);Rva0054D8D8 *rva005BA36D();};
#undef V
void AptOnlineQuickMatch::rva005BB5F6(){
 HandleBuddyResponses();HandlePersistentStorageResponses();
 if(TheGameSpyGame&&TheGameSpyGame->m_inProgress){
  if(TheGameSpyInfo->isDisconnectedAfterGameStart(0))return;
  int allowed=TheGameSpyInfo->getMaxMessagesPerUpdate();bool important=false;PeerResponse r;
  while(allowed--&&!important&&TheGameSpyPeerMessageQueue->getResponse(r)){
   AptMessengerOnline::ProcessGameSpyResponse(&r);
   switch(r.unknown_00){case 1:{important=true;AsciiString reason;reason.format("GUI:GSDisconReason%d",r.payload_word0.value);
    NameKeyType key=TheNameKeyGenerator->nameToKey("ScoreScreen.wnd:ListboxChatWindowScoreScreen");GameWindow *gameWindow=TheWindowManager->winGetWindowFromId(0,key);
    if(gameWindow)GadgetListBoxAddEntryText(gameWindow,TheGameText->fetch(reason),GameSpyColor[0],-1);
    TheGameSpyInfo->markAsDisconnectedAfterGameStart(r.payload_word0.value);
   }break;}
  }return;
 }
 if(TheNAT){
  ((Rva005A6D47 *)TheNAT)->rva005A8F57();
  if(((Rva005BA3AD *)TheNAT)->rva005BA3AD()){TheGameSpyGame->startGame(0);TheGameSpyGame->launchGame();return;}
  else if((unsigned char)((Rva005BA31F *)TheNAT)->rva005BA31F()){
   void *memory=TheNAT?((Rva005A6D47 *)TheNAT)->destroy(0):0;operator delete(memory);TheNAT=0;state=3;
   Rva00437F61(0,TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:NATNegotiationFailed"),Rva0023E8D8(bind(reinterpret_cast<FunctorMethod>(&AptOnlineQuickMatch::rva005BA39F),(FunctorTarget *)this)));
   ((Rva00222A8BTarget*)g_bfmeAptWindowManager)->invoke(movieLevel(),"CallChild",1,"CloseFoundAndReset",0,0,0,0);return;
  }
 }
 int allowed=TheGameSpyInfo->getMaxMessagesPerUpdate();bool important=false;PeerResponse r;
 while(allowed--&&!important&&TheGameSpyPeerMessageQueue->getResponse(r)){
  if(!state)AptMessengerOnline::ProcessGameSpyResponse(&r);else Rva00511730(0);
  switch(r.unknown_00){
  case 16:{
   AsciiString nick;PlayerInfoMap::iterator found=TheGameSpyInfo->getPlayerInfoMap()->find(r.unknown_10.c_str());
   if(found!=TheGameSpyInfo->getPlayerInfoMap()->end())nick=found->second.m_at04;else nick=r.unknown_10.c_str();
   if(!_strcmpi(r.unknown_e8.c_str(),"STATS")){
    AsciiString data=r.unknown_f4.c_str();AsciiString idText;data.nextToken(&idText," ");int id=atoi(idText.str());
    PSPlayerAllStats stats(0);PSPlayerAllStats oldStats=TheGameSpyPSMessageQueue->findPlayerStatsByID(id);stats.setID(id);
    if(stats.id&&!oldStats.id)TheGameSpyPSMessageQueue->trackPlayerStats(stats);
    for(int i=0;i<8;++i){GameSlot *slot=TheGameSpyGame->getGameSpySlot(i);if(slot&&slot->isHuman()&&((Rva004FDCE1AsciiField *)slot)->get().compareNoCase(nick)==0){((SlotFields *)slot)->profile=id;break;}}
   }else{
    int slot=TheGameSpyGame->getSlotNum(nick);
    if(slot>=0&&slot<8&&!_strcmpi(r.unknown_e8.c_str(),"NAT")){important=true;if(TheNAT)TheNAT->processGlobalMessage(slot,r.unknown_f4.c_str());}
   }
  }break;
  case 1:{important=true;UnicodeString title,body;AsciiString reason;reason.format("GUI:GSDisconReason%d",r.payload_word0.value);
   title=TheGameText->fetch("GUI:GSErrorTitle");body=TheGameText->fetch(reason);Rva00548C1ACleanup();GSMessageBoxOk(title,body);
   TheGameSpyInfo->reset();TheShell->pop();TearDownGameSpy();}break;
  case 8:{if(r.payload_word0.value==0){UnicodeString s;s.format(L"Created staging room");}else{UnicodeString s;s.format(L"createStagingRoom result: %d",r.payload_word0.value);}}break;
  case 9:{unsigned char ok=*(unsigned char *)((char *)&r.payload_word0+4);if(ok==1){UnicodeString s;s.format(L"joinStagingRoom result: %d",ok);}else{UnicodeString s;s.format(L"joinStagingRoom result: %d",ok);}}break;
  case 4:{UnicodeString s;s.format(L"Staging room list callback",r.unknown_10.c_str());}break;
  case 17:{important=true;switch(r.payload_8a.first){
   case 4:{UnicodeString s;s.format(TheGameText->fetchPtr("QM:WORKING"),r.payload_8a.second);}break;
   case 5:{UnicodeString s;s.format(TheGameText->fetchPtr("QM:POOLSIZE"),r.payload_8a.second);}break;
   case 7:((Rva00222A8BTarget*)g_bfmeAptWindowManager)->invoke(movieLevel(),"CallChild",1,"DoOpenFound",0,0,0,0);OnMatched(r);break;
  }}break;
  }
 }
}


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

#include "../../../../../Include/GameNetwork/GameSpyConfigInterface.h"
extern GameSpyConfigInterface *TheGameSpyConfig;
class Rva0054D8D8
{
public:
	UnicodeString name; // +0x00
	char p4[8]; // +0x04
	int players; // +0x0C
	char p10[9]; // +0x10
	bool randomFactions; // +0x19
	char p1a[2]; // +0x1A
	_STL::list<AsciiString> maps; // +0x1C
	_STL::list<AsciiString> factions; // +0x20
	char p24[4]; // +0x24
	AsciiString address; // +0x28
	unsigned short port; // +0x2C
	char m_pad2E[0x2];
};
void GadgetComboBoxGetSelectedPos(GameWindow *, int *);
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_insert_aux(_Bit_iter<_Bit_reference, _Bit_reference *>, bool); }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
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
class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return side; }
	bool isPlayableSide() const { return m_playableSide; }

	char p[0x18];
	AsciiString side;			// +0x18
	unsigned char m_pad1C[0x151 - 0x1c];
	bool m_playableSide;			// +0x151
	unsigned char m_pad152[0x1dc - 0x152];
};
class QuickMatchPlayerTemplateRange : public _STL::vector<PlayerTemplate>
{
public:
	unsigned int count() const { return (unsigned int)(this->_M_finish - this->_M_start); }
};

class PlayerTemplateStore
{
public:
    int getPlayerTemplateCount() const { return m_playerTemplates.count(); }
    const PlayerTemplate *getNthPlayerTemplate(int) const;
    int count() const { return m_playerTemplates.count(); }

    unsigned char m_pad00[0x0c];
    QuickMatchPlayerTemplateRange m_playerTemplates; // +0x0C
};
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameClientRandomValue(int, int, char *, int);
extern int OnlineQuickMatchMaxPingEntries, g_009C0758, g_009C075C, BfmeOnlineLadderRank1v1, BfmeOnlineLadderRank2v2;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
void *GadgetComboBoxGetItemData(GameWindow *, int);


// Native5BAF35..5BB3A1 RET4 (1132B): the quick-match "matched" handler the
// response drain 0x005BB5F6 calls for QM status 7 after DoOpenFound. Semantic
// guide: BF1 handleMatched (AptOnlineQuickMatch.cpp, donor 2f243e26d); BFME 2
// adds the game reset, the native rules block, team-mode staging fields
// +0x1D0/+0x1D4 and the NAT negotiator setup. The local address record uses
// the connect-info type (its constructor zeroing is dead but sets retail's
// frame homes for the temporaries and the param-home reuse of the new NAT).
#include "../../../../../Include/GameClient/MapMetaData.h"
class MapCache{public:const MapMetaData *findMap(AsciiString);};extern MapCache *TheMapCache;
class Rva003821E2 {public:void assign(UnicodeString);};class Rva004FDD36AsciiField{public:void setClan(AsciiString);};
class MpGameRules { public: static void GetDefaults(int,void*); };void SendStatsToOtherPlayers(GameInfo*);
class Rva005A734B{public:char storage[0x974];Rva005A734B();};
void AptOnlineQuickMatch::OnMatched(PeerResponse &resp){
 TheGameSpyGame->reset();TheGameSpyGame->enterGame();TheGameSpyGame->setSeed(resp.payload_572.words[3]);
 {GameSpyStagingRoom *game=TheGameSpyGame;int m=mode;*(bool*)((char*)game+0xff4)=true;*(int*)((char*)game+0xff8)=m;}
 int rules[10];memset(rules,0xff,sizeof(rules));MpGameRules::GetDefaults(0,rules);rules[0]=0;rules[2]=0;memcpy((char*)TheGameSpyGame+0x60,rules,sizeof(rules));
 int numPlayers=0;for(int i=0;i<8;++i)if(!resp.unknown_88[i].empty())++numPlayers;
 _STL::list<AsciiString> maps=TheGameSpyConfig->getQMMaps();
 for(_STL::list<AsciiString>::const_iterator it=maps.begin();it!=maps.end();++it){AsciiString map=*it;map.toLower();const MapMetaData *md=TheMapCache->findMap(map);if(md&&md->m_numPlayers==numPlayers){TheGameSpyGame->setMap(*it);if(resp.payload_572.words[2]--==0)break;}}
 int numPerTeam=numPlayers/2;if(!numPerTeam)numPerTeam=1;
 for(int i=0;i<8;++i){GameSpyGameSlot *slot=TheGameSpyGame->getGameSpySlot(i);
  if(resp.unknown_88[i].empty())slot->setState(SLOT_CLOSED,UnicodeString::TheEmptyString,&GameSlotConnectInfo());else{
   AsciiString aName=resp.unknown_88[i].c_str();char baseName[256]="";strncpy(baseName,resp.unknown_88[i].c_str(),255);
   PlayerInfo player;player.m_at00=resp.unknown_88[i].c_str();player.m_at04=baseName;TheGameSpyInfo->updatePlayerInfo(player,AsciiString::TheEmptyString);
   UnicodeString uName;uName.translate(baseName);IPAndPort connect(resp.qmStatus.IP[i],resp.qmStatus.ports[i]);
   slot->setState(SLOT_PLAYER,uName,(const GameSlotConnectInfo*)&connect);slot->m_color=resp.payload_572.words[24+i];slot->setPlayerTemplate(resp.payload_572.words[16+i]);slot->m_field40=resp.payload_572.words[32+i];((Rva004FDD36AsciiField*)slot)->setClan("");slot->m_teamNumber=i/numPerTeam;
   switch(numPerTeam){case 1:slot->rva1d0=resp.payload_572.words[40+i];slot->rva1d4=-1;break;case 2:slot->rva1d0=-1;slot->rva1d4=resp.payload_572.words[40+i];break;default:slot->rva1d0=-1;slot->rva1d4=-1;}
   if(i==0)((Rva003821E2*)TheGameSpyGame)->assign(uName);
  }
 }
 SendStatsToOtherPlayers(TheGameSpyGame);matched=true;
 if(TheNAT){operator delete(((Rva005A6D47 *)TheNAT)->destroy(0));TheNAT=0;}
 if(TheGameSpyGame->getLocalSlotNum()>=0){TheNAT=(NAT*)new Rva005A734B;GameSlotConnectInfo address;address.ip=TheGameSpyInfo->getInternalIP();address.port=TheGameSpyInfo->getInternalPort();*(unsigned*)((char*)TheGameSpyGame+0x38)=address.ip;*(unsigned*)((char*)TheGameSpyGame+0x3c)=*(const volatile unsigned*)&address.port;
 unsigned &transportIP=*(unsigned*)((char*)TheGameSpyGame+0x38);((NAT*)TheNAT)->attachSlotList(TheGameSpyGame,TheGameSpyGame->getLocalSlotNum(),transportIP,30000,TheGameSpyGame->getLocalSlotNum()==0);}
}

// Post-include free redeclare drops dllimport for the metadata vector's
// deallocate call only: retail calls the engine _free directly at 0x30830
// (same recipe as stlport_vector_int_insert_overflow.cpp).
extern "C" void __cdecl free(void *);

// Native5BBDAC..5BBF15 RET4 (361B): quick-match map-selection vector builder.
// WB1589500 shows the request map-selection walk; BF1 donor rva0055A240 and
// ZH WOLQuickMatchMenu are the semantic guides. The local view classes below
// supply the partition predicate and comparator the native call site uses;
// the loop body holds *m in a named local, which reproduces retail's iterator
// register roles (EDI first-arg / ESI iterator) exactly.
