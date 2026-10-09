// cl: /Oa /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native416C69..4177B5 RET +32B eight-case table4177B5..4177D5.
// /Oa reproduces the shared-global virtual-call scheduling; the target
// reload of the shell pointer in the FESL26AD path is retained explicitly.
// Donor revision874e38488; WB13370A0 names HandleBuddyResponses, BuddyDefs.cpp.
// Target offsets and all eight cases come from retail; ZH WOLBuddyOverlay
// is the semantic donor; FESL and forced-disconnect/invite are target deltas.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <wchar.h>
#undef _CRTIMP
#define _CRTIMP
#include <set>
#include <map>
#include <string>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
struct PeerResponse {
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


class BuddyInfo {public: BuddyInfo(); int id; AsciiString name,email,country; int status; UnicodeString statusString,location; ~BuddyInfo();};
// The default constructor is emitted here after retiring the older donor body.
BuddyInfo::BuddyInfo() {}
class BuddyMessage {public:unsigned timestamp;int sender;AsciiString senderNick;int recipient;AsciiString recipientNick;UnicodeString message;~BuddyMessage();};
struct BfmeStringRecord00415F34 {BuddyMessage message;BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &);};
class Rva004E9B70 {public:int words[7];Rva004E9B70 &operator=(const Rva004E9B70 &);};
class Gen_004E9FD0 {public:unsigned words[7];};
typedef _STL::map<int,Gen_004E9FD0> BuddyValueMap;
namespace _STL {template<> Gen_004E9FD0 &BuddyValueMap::operator[](const int &);}
// Existing key-only tree erase wrapper. The retail caller passes a profile
// word; unconstrained provider payload bytes remain its opaque ABI view.
struct Rva00385CBAElement {char bytes[8];};
namespace _STL {template<> unsigned _Rb_tree<Rva00385CBAElement,Rva00385CBAElement,_Identity<Rva00385CBAElement>,less<Rva00385CBAElement>,allocator<Rva00385CBAElement> >::erase(const Rva00385CBAElement &);}
typedef _STL::_Rb_tree<Rva00385CBAElement,Rva00385CBAElement,_STL::_Identity<Rva00385CBAElement>,_STL::less<Rva00385CBAElement>,_STL::allocator<Rva00385CBAElement> > RequestEraseTree;
struct BuddyResponse {
 int type,profile,result;
 union {
  struct {unsigned date;char nick[31];unsigned short text[128];} message;
  struct {char nick[31],email[51],country[3];unsigned short text[1024];} request;
  struct {int errorResult,errorCode;char message[128];int fatal;} error;
  struct {char nick[31],email[51],country[3],location[256];int status;char text[256];} status;
 } arg;
};
struct BuddyRequest {int type,profile;char unknown[0x2b8-8];};
#define V(n) virtual void slot##n();
class GameSpyBuddyMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)virtual void addRequest(const BuddyRequest &);V(7)V(8)virtual bool getResponse(BuddyResponse &);};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
class GameSpyPeerMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)virtual void addResponse(const PeerResponse &);};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class GameSpyInfoInterface {public:
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)
virtual _STL::map<int,int> *getBuddyMap();virtual _STL::map<int,int> *getBuddyRequestMap();V(26)virtual bool hasBuddyRequest(int);
V(28)V(29)V(30)virtual int getLocalProfileID();V(32)V(33)V(34)V(35)V(36)virtual AsciiString getLocalBaseName();
V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)V(58)V(59)V(60)V(61)V(62)V(63)V(64)V(65)V(66)V(67)V(68)V(69)V(70)V(71)V(72)V(73)V(74)V(75)V(76)virtual bool isSavedIgnored(int);
V(78)V(79)V(80)V(81)V(82)V(83)V(84)V(85)V(86)V(87)V(88)V(89)V(90)V(91)V(92)V(93)V(94)V(95)V(96)V(97)virtual void setConnected(bool);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)virtual UnicodeString fetch(const char *,bool *exists=0);virtual UnicodeString fetch(const AsciiString &,bool *exists=0);V(16)virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;
#undef V
class BfmeObjELB {public:char prefix[0xd1];bool disconnected;char pad[10];bool fesl26ad;};
extern BfmeObjELB *g_bfmeObjELB;
struct Rva00416088 {int word0,word1;AsciiString text0,text1;~Rva00416088();};
class BuddyInviteGameInfo {public:int profile;Rva00416088 data;int word14;BuddyInviteGameInfo():profile(-1){data.word0=-1;data.word1=-1;word14=-1;}void LocationFromString(const AsciiString &);};
struct Rva00517048 {void rva00517CC9(const BuddyInviteGameInfo &);};
extern Rva00517048 *g_Va00A04904;
extern unsigned char g_Va00A0308C;extern unsigned char g_Va00A03094;
extern int g_Va00A03090;extern int g_Va00A03098;

void Rva00415EF8Close();void Rva004163E1Notify(AsciiString,UnicodeString);void Rva00381900(int);
void Rva00416A5DPush(const BfmeStringRecord00415F34 &);void Rva00416589(BfmeStringRecord00415F34);
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)(void));
std::wstring MultiByteToWideCharSingleLine(const char *);
static __forceinline BuddyInfo &value(_STL::map<int,int> *map,const int &profile){return *(BuddyInfo *)&((BuddyValueMap *)map)->operator[](profile);}
// ?HandleBuddyResponses@@YAXXZ retail416C69 extent2924 including32B table
void HandleBuddyResponses()
{
 if(TheGameSpyBuddyMessageQueue){BuddyResponse resp;if(TheGameSpyBuddyMessageQueue->getResponse(resp)){
 switch(resp.type){
 case 0:Rva00415EF8Close();TheGameSpyInfo->setConnected(true);break;
 case 6:
  if(g_bfmeObjELB)g_bfmeObjELB->disconnected=true;
  if(TheGameSpyPeerMessageQueue){PeerResponse peer;peer.unknown_00=1;peer.payload_word0.value=21;TheGameSpyPeerMessageQueue->addResponse(peer);}
  TheGameSpyInfo->setConnected(false);break;
 case 1:{
  g_Va00A0308C=false;g_Va00A03090=0;Rva004163E1Notify(AsciiString::TheEmptyString,TheGameText->fetch("Buddy:MessageDisconnected"));
  UnicodeString title,message;AsciiString reason;
  reason.format("GUI:GSGPDisconReason%d",resp.arg.error.errorCode);
  title=TheGameText->fetch("GUI:GSErrorTitle");message=TheGameText->fetch(reason);GSMessageBoxOk(title,message,0);
  if(g_bfmeObjELB)g_bfmeObjELB->disconnected=true;
  if(TheGameSpyPeerMessageQueue){PeerResponse peer;peer.unknown_00=1;peer.payload_word0.value=3;TheGameSpyPeerMessageQueue->addResponse(peer);}
  TheGameSpyInfo->setConnected(false);break;}
 case 5:{
  g_Va00A0308C=false;g_Va00A03090=0;Rva004163E1Notify(AsciiString::TheEmptyString,TheGameText->fetch("Buddy:MessageDisconnected"));
  UnicodeString title,message;AsciiString reason;
  reason.format("FESL:FESL%d",resp.arg.error.errorResult);
  title=TheGameText->fetch("GUI:GSErrorTitle");message=TheGameText->fetch(reason);GSMessageBoxOk(title,message,0);
  if(g_bfmeObjELB){g_bfmeObjELB->disconnected=true;if(resp.arg.error.errorResult==0x26ad)(*(BfmeObjELB *volatile *)&g_bfmeObjELB)->fesl26ad=true;}
  if(TheGameSpyPeerMessageQueue){PeerResponse peer;peer.unknown_00=1;peer.payload_word0.value=3;TheGameSpyPeerMessageQueue->addResponse(peer);}
  TheGameSpyInfo->setConnected(false);break;}
 case 2:{
  if(!wcscmp(resp.arg.message.text,L"I have authorized your request to add me to your list"))break;
  if(TheGameSpyInfo->isSavedIgnored(resp.profile))break;
  BuddyMessage message;message.timestamp=resp.arg.message.date;message.sender=resp.profile;
  message.recipient=TheGameSpyInfo->getLocalProfileID();message.recipientNick=TheGameSpyInfo->getLocalBaseName();message.message=resp.arg.message.text;
  _STL::map<int,int> *map=TheGameSpyInfo->getBuddyMap();_STL::map<int,int>::iterator sender=map->find(message.sender);AsciiString nick;
  if(sender!=map->end())nick=((BuddyInfo *)&sender->second)->name.str();else nick=resp.arg.message.nick;
  message.senderNick=nick;Rva00416A5DPush(*(const BfmeStringRecord00415F34 *)&message);Rva00416589(*(const BfmeStringRecord00415F34 *)&message);break;}
 case 3:{
  if(TheGameSpyInfo->isSavedIgnored(resp.profile)){BuddyRequest request;request.type=8;request.profile=resp.profile;TheGameSpyBuddyMessageQueue->addRequest(request);break;}
  _STL::map<int,int> *map=TheGameSpyInfo->getBuddyMap();_STL::map<int,int>::iterator buddy=map->find(resp.profile);if(buddy!=map->end()){BuddyRequest request;request.type=7;request.profile=resp.profile;TheGameSpyBuddyMessageQueue->addRequest(request);break;}
  map=TheGameSpyInfo->getBuddyRequestMap();BuddyInfo info;info.country=resp.arg.request.country;info.email=resp.arg.request.email;info.name=resp.arg.request.nick;info.id=resp.profile;info.status=0;info.statusString=resp.arg.request.text;*(Rva004E9B70 *)&value(map,resp.profile)=*(const Rva004E9B70 *)&info;
  Rva00381900(0);g_Va00A0308C=false;g_Va00A03090=0;
  BuddyMessage message;message.timestamp=0;message.recipient=TheGameSpyInfo->getLocalProfileID();message.recipientNick=TheGameSpyInfo->getLocalBaseName();message.senderNick=info.name;message.message=TheGameText->fetch("Buddy:AddNotification");message.message.format(&message.message,message.senderNick.str());Rva00416A5DPush(*(const BfmeStringRecord00415F34 *)&message);Rva00416589(*(const BfmeStringRecord00415F34 *)&message);break;}
 case 4:{
  _STL::map<int,int> *map=TheGameSpyInfo->getBuddyMap();_STL::map<int,int>::const_iterator it=map->find(resp.profile);bool seen=false;int oldStatus=0;int newStatus=resp.arg.status.status;
  if(it!=map->end()){seen=true;oldStatus=value(map,resp.profile).status;}
  BuddyInfo info;info.country=resp.arg.status.country;info.email=resp.arg.status.email;info.name=resp.arg.status.nick;info.id=resp.profile;info.status=newStatus;
  info.statusString=UnicodeString(MultiByteToWideCharSingleLine(resp.arg.status.text).c_str());info.location=UnicodeString(MultiByteToWideCharSingleLine(resp.arg.status.location).c_str());*(Rva004E9B70 *)&value(map,resp.profile)=*(const Rva004E9B70 *)&info;
  if(TheGameSpyInfo->hasBuddyRequest(resp.profile)){map=TheGameSpyInfo->getBuddyRequestMap();if(map->find(resp.profile)!=map->end()){BuddyRequest request;request.type=7;request.profile=resp.profile;TheGameSpyBuddyMessageQueue->addRequest(request);((RequestEraseTree *)map)->erase(*(const Rva00385CBAElement *)&resp.profile);}}
  Rva00381900(0);BuddyMessage message;message.timestamp=0;message.recipient=TheGameSpyInfo->getLocalProfileID();message.recipientNick=TheGameSpyInfo->getLocalBaseName();message.senderNick=info.name;
  if((newStatus==0&&seen)||(newStatus==1&&(oldStatus==0||!seen))){AsciiString marker;marker.format("Buddy:%lsNotification",info.statusString.str());g_Va00A0308C=true;if(newStatus!=0)++g_Va00A03090;message.message=TheGameText->fetch(marker);message.message.format(&message.message,message.senderNick.str());Rva00416A5DPush(*(const BfmeStringRecord00415F34 *)&message);Rva00416589(*(const BfmeStringRecord00415F34 *)&message);}
  else if(newStatus==4&&!seen){g_Va00A0308C=true;++g_Va00A03090;message.message=TheGameText->fetch("Buddy:OnlineNotification");message.message.format(&message.message,message.senderNick.str());Rva00416A5DPush(*(const BfmeStringRecord00415F34 *)&message);Rva00416589(*(const BfmeStringRecord00415F34 *)&message);}
  break;}
 case 7:{Rva00517048 *host=g_Va00A04904;if(!host)return;{BuddyInviteGameInfo info;info.profile=resp.profile;info.LocationFromString(AsciiString(resp.arg.message.nick));host->rva00517CC9(info);}break;}
 }
 }}
 if(g_Va00A03094&&timeGetTime()>g_Va00A03098)Rva00415EF8Close();
}

extern int g_00DB9198;
extern int g_Va00E046B8;
void Rva00381C82AddChatText(int,const UnicodeString &,int);
// ?Rva00416589@@YAXUBfmeStringRecord00415F34@@@Z retail416589338B
// Target-specific ZH insertChat equivalent; GameSpyColor baseDB9198 index8.
void Rva00416589(BfmeStringRecord00415F34 record)
{
 BuddyMessage &message=record.message;
 UnicodeString text;text.format(L"[%hs] %s",message.senderNick.str(),message.message.str());
 Rva00381C82AddChatText(0,text,(&g_00DB9198)[8]);
 if(!g_Va00E046B8){
  UnicodeString snippet=message.message;
  while(snippet.getLength()>11)snippet.removeLastChar();
  UnicodeString notification;
  notification.format(TheGameText->fetchFormat("Buddy:MessageNotification"),message.senderNick.str(),snippet.str());
  g_Va00A0308C=false;g_Va00A03090=0;
  Rva004163E1Notify(AsciiString::TheEmptyString,notification);
 }
}
