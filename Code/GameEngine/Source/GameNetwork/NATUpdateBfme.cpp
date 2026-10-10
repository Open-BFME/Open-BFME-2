// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BF1 NAT_update f98983a7d supplies stats-wait semantics; WB14DA930 and
// native5A8F57..5A90F9 RET0 supply BF2 schema/transport flow and returned state.
// Native zero bytes at A02D8C (one byte) and A06400 (four bytes); these names
// describe observed uses, not proven original global spellings.
// Schema output is a twelve-byte owning vector of eight-byte slot pairs;
// its existing 5A7172 destructor owns the range and base allocation.
// Vector<int> construction uses the existing exact 29B folded base initializer;
// only the twelve-byte header is accessed through this storage view.
#include <vector>
#include <string>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/GameNetwork/Transport.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class GameSlot{public:bool isHuman()const;};class GameSpyGameSlot:public GameSlot{public:char pad[0x1ac];int profile;};
class GameSpyStagingRoom{public:GameSpyGameSlot *getGameSpySlot(int);};extern GameSpyStagingRoom *TheGameSpyGame;
class PSPlayerAllStats{public:int id;char rest[0x544];~PSPlayerAllStats();};
class GameSpyPSMessageQueueInterface{public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual PSPlayerAllStats findPlayerStatsByID(int);};extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
struct Rva00A063B0Obj;extern Rva00A063B0Obj *g_a063b0;
bool g_natTransportContextEnabled=false;unsigned g_natStatsWaitStartTick=0;
struct Rva005A7A96Pair{void *opaque00;unsigned short first,second;};
struct Rva005A7172:public _STL::vector<int>{~Rva005A7172();};
class PortNegotiationSchema{public:void negotiationStarted(unsigned short,unsigned short,int,bool);char pad00[0x18];int state[81];char pad15c[0x738-0x15c];unsigned timeout[8][8];unsigned short tries[8][8];bool rva005DBA9C(bool);bool rva005DBA60(unsigned short);bool rva005DC586(_STL::vector<Rva005A7A96Pair>*);};
class NAT{public:void findMyMangledPort();void rva005A89C2(int,int);bool rva005A6709();void rva005A7C9C();void rva005A6CA5();void sendPings();void processUDPPacket();int rva005A879B();void processManglerResponse(unsigned short);bool SetUDPSocketForSlot(unsigned short,unsigned short,void*);void notifyConnectionToTargetFailed();void rva005A74D8();void rva005A7829(int);void rva005A6C90(int);void rva005A831E();void rva005A7974(unsigned short,void*);static unsigned s_probeRetryInterval;static int s_manglerMaxRetryCount;void rva005A7A96(const _STL::vector<Rva005A7A96Pair>*);};
class Rva005A6732{public:bool rva005A6732()const;};
class Rva005A6D47 {public:void *vptr;Transport *transport;GameSpyGameSlot **slots;int host,state,local;char pad18[0x10];PortNegotiationSchema schema;int rva005A8F57();};
int Rva005A6D47::rva005A8F57(){
 NAT *nat=(NAT*)this;
 if(nat->rva005A6709()&&((UnicodeString*)((char*)slots[local]+0x30))->getLength()>0)nat->rva005A7C9C();
 if(transport){nat->rva005A6CA5();nat->sendPings();if(g_natTransportContextEnabled)transport->update((Rva00594DC0*)g_a063b0);else transport->update(0);nat->processUDPPacket();}
 switch(state){
 case 2:{bool all=true;bool timeout=false;for(int i=0;i<8;++i){GameSpyGameSlot *slot=TheGameSpyGame->getGameSpySlot(i);if(slot&&slot->isHuman()){PSPlayerAllStats stats=TheGameSpyPSMessageQueue->findPlayerStatsByID(slot->profile);if(!stats.id)all=false;}}
 unsigned now=timeGetTime();if(now>g_natStatsWaitStartTick+5000)timeout=true;if(all||timeout)state=0;
 }break;
 case 1:{if(!((Rva005A6732*)this)->rva005A6732())nat->rva005A879B();if(schema.rva005DBA9C(nat->rva005A6709())){state=2;g_natStatsWaitStartTick=timeGetTime();}else if(nat->rva005A6709()){Rva005A7172 pairs;if(schema.rva005DC586((_STL::vector<Rva005A7A96Pair>*)&pairs))nat->rva005A7A96((_STL::vector<Rva005A7A96Pair>*)&pairs);}}
 }
 return state;
}

class Rva005DBCD1{public:unsigned short first,second;Rva005DBCD1(unsigned short a,unsigned short b):first(a),second(b){}Rva005DBCD1(const Rva005DBCD1&);virtual ~Rva005DBCD1(){}};
struct Elem003AF7A0{virtual ~Elem003AF7A0();char body[4];};
struct Rva005DC408Element{void *vptr;unsigned short first,second;};
namespace _STL{template<>void vector<Elem003AF7A0,allocator<Elem003AF7A0> >::push_back(const Elem003AF7A0&);template<>Rva005DC408Element *vector<Rva005DC408Element,allocator<Rva005DC408Element> >::erase(Rva005DC408Element*,Rva005DC408Element*);}
// Native412B: find disjoint ready slot pairs. No clean schema donor exists
// in the sanctioned BF1 source or ZH NAT.cpp; target WB15C7630 and native
// supply state/tries/timeout arrays and eligibility. Second retry check reads
// the first direction timeout exactly as retail does. Element vtable owner
// Rva005DBCD1 and existing erase/push providers establish eight-byte storage.
bool PortNegotiationSchema::rva005DC586(_STL::vector<Rva005A7A96Pair>*pairs){
 _STL::vector<Rva005DC408Element>*eraseView=(_STL::vector<Rva005DC408Element>*)pairs;eraseView->erase(eraseView->begin(),eraseView->end());
 unsigned now=timeGetTime();
 for(unsigned short first=0;first<8;++first){for(unsigned short second=first+1;second<8;++second){
  if((state[first*8+second]==1&&state[second*8+first]==1)||((state[first*8+second]==4||state[second*8+first]==4)&&tries[first][second]<5&&tries[second][first]<5&&(state[first*8+second]!=2||timeout[first][second]<now)&&(state[second*8+first]!=2||timeout[first][second]<now))){
   if(!rva005DBA60(first)&&!rva005DBA60(second)){
    _STL::vector<Rva005A7A96Pair>::iterator it=pairs->begin();for(;it!=pairs->end();++it){if(it->first==first||it->second==first||it->first==second||it->second==second)goto skipPair;}
    {Rva005DBCD1 pair(first,second);((_STL::vector<Elem003AF7A0>*)pairs)->push_back(*(const Elem003AF7A0*)&pair);}
   }
  }
 skipPair:;
 }}
 return pairs->size()>0;
}

__declspec(noinline) bool PortNegotiationSchema::rva005DBA60(unsigned short x){if(x<8){for(int i=0;i<8;++i){if(i!=x&&state[i+x*8]==2)return true;if(state[x+i*8]==2)return true;}}return false;}

struct Rva005A684FWord{unsigned m_00;unsigned short m_04;};class Rva005A684F{public:unsigned get(unsigned)const;char pad[0x90c];Rva005A684FWord *m_slots[8];};
class Rva00594E07{public:unsigned short rva00594E07(unsigned short,int);};class Rva0059534A{public:void rva0059534A(unsigned short);};class Rva0059517F{public:bool rva0059517F(unsigned long,unsigned short,unsigned short,unsigned short,bool);};class FirewallHelperClass{public:static void getManglerName(int,char*);void flagNeedToRefresh(bool);};
extern unsigned long g_00DD35BC;int NAT::s_manglerMaxRetryCount=25;
struct NatConnectionView{char pad00[8];GameSpyGameSlot **slots;int host,parentState;int local,target;unsigned localIP,cookie;bool sendPort,receivedPort;char pad26[0x92c-0x26];int retries,maxRetries;unsigned short packetID,spareSocket;unsigned manglerRetryTime;int manglerRetries;unsigned short previousSource;bool beenProbed,unknown943;unsigned manglerAddress,nextSendTime;int connectionState,previousState;char pad954[8];unsigned nextPortSendTime,timeoutTime,roundTimeout,unknown968,nextHostTick;bool active;};
// BF1 f98983a7d NAT_connectionUpdate.cpp supplies mangler retry/port/probe
// semantics. Target WB14DAEB0 connectionUpdate and full551B retail control
// flow supply compact BF2 callbacks and offsets. State IDs4/5 differ from
// BF1. Retry maximum25 at9D35C0 is proven native initialized data.
int NAT::rva005A879B(){
 NatConnectionView *v=(NatConnectionView*)this;
 if(v->target<0||v->target>=8){v->connectionState=4;return 4;}
 GameSpyGameSlot *target=v->slots[v->target];
 if(!v->beenProbed&&timeGetTime()>=v->nextPortSendTime){AsciiString name;name.translate(*(UnicodeString*)((char*)target+0x30));if(v->sendPort){rva005A7974(((Rva005A684F*)this)->get(v->local),target);v->nextPortSendTime=timeGetTime()+s_probeRetryInterval;}}
 if(v->connectionState==2){
  if(!v->sendPort){unsigned short mangled;if(g_a063b0&&(mangled=((Rva00594E07*)g_a063b0)->rva00594E07(v->packetID,0))!=0){processManglerResponse(mangled);((Rva0059534A*)g_a063b0)->rva0059534A(v->spareSocket);v->spareSocket=0;}
   else if(timeGetTime()>=v->manglerRetryTime){if(++v->manglerRetries>s_manglerMaxRetryCount)rva005A7974(((Rva005A684F*)this)->get(v->local),target);else{if(g_a063b0)((Rva0059517F*)g_a063b0)->rva0059517F(v->manglerAddress,v->spareSocket,v->packetID,4321,false);v->manglerRetryTime=timeGetTime()+g_00DD35BC;}}
  }
  if(!v->receivedPort){if(timeGetTime()>v->timeoutTime){rva005A6C90(5);notifyConnectionToTargetFailed();}}
  if(v->receivedPort&&v->sendPort)rva005A6C90(3);
 }else if(v->connectionState==3){if(v->nextSendTime!=-1&&v->nextSendTime<=timeGetTime()){if(v->retries>v->maxRetries){rva005A6C90(5);notifyConnectionToTargetFailed();}else{rva005A831E();++v->retries;}}}
 if(timeGetTime()>v->roundTimeout&&v->connectionState!=4&&v->connectionState!=5){rva005A6C90(5);notifyConnectionToTargetFailed();}
 if(v->previousState!=4)((FirewallHelperClass*)g_a063b0)->flagNeedToRefresh(true);
 return v->connectionState;
}

__declspec(noinline) unsigned Rva005A684F::get(unsigned index)const{return m_slots[index]?m_slots[index]->m_04:0;}

class GlobalData;extern GlobalData *TheWritableGlobalData;struct GlobalPortDeltaView{char pad[0xa58];short delta;};class Rva005A6A83{public:void rva005A6A83();};
// BF1 f98983a7d NAT.cpp processManglerResponse is the semantic guide.
// Target WB14DDD40/native282 add UDP slot binding before PORT notification;
// source port is spare+1 and simple allocation includes flags10/40.
void NAT::processManglerResponse(unsigned short mangledPort){
 NatConnectionView *v=(NatConnectionView*)this;GameSpyGameSlot *target=v->slots[v->target];if(!target){rva005A6C90(5);return;}
 short delta=((GlobalPortDeltaView*)TheWritableGlobalData)->delta;unsigned short sourcePort=v->spareSocket+1;unsigned short returnPort=0;
 unsigned fw=*(unsigned*)((char*)v->slots[v->local]+0x40);
 if(fw&0x10) returnPort=mangledPort+delta;else if(fw&0x40)returnPort=mangledPort+delta;else if(delta==100){returnPort=sourcePort-v->spareSocket+mangledPort+100;}else if(!delta){returnPort=sourcePort;}else{returnPort=(mangledPort/delta+1)*delta+sourcePort%delta;}
 if(returnPort>65535)returnPort-=65535;if(returnPort<1024)returnPort+=1024;
 struct Address{unsigned ip;unsigned short port;Address():ip(0),port(0){}} address;v->previousSource=returnPort;
 if(!SetUDPSocketForSlot(sourcePort,v->target,&address)){((Rva005A6A83*)this)->rva005A6A83();return;}
 ((Rva005A684F*)this)->m_slots[v->local]->m_04=v->spareSocket+1;rva005A7974(returnPort,target);
 if(v->receivedPort){rva005A6C90(3);((Rva005A6D47*)this)->transport->setDestAddrToSocket(v->target,((Rva005A684F*)this)->m_slots[v->target]);}
}

// BF1 socket-allocation semantics guide the cleanup and ownership transfer.
// Target WB14E58F0 and retail5A6DAC..5A6E7A prove the32B allocator,
// UDP unsigned-IP Bind ABI, localIP1C, one-second retry and slot handoff.
// Checking result first retains the native EBX result across the timeout.
class Rva005948F5 {public:char bytes[32];Rva005948F5();};class UDPDrain{public:~UDPDrain();};class UDP{public:int Bind(unsigned,unsigned short);};
bool NAT::SetUDPSocketForSlot(unsigned short port,unsigned short slot,void* address){
 Rva005A6D47 *base=(Rva005A6D47*)this;NatConnectionView*v=(NatConnectionView*)this;
 if(slot>=8)return false;if(!base->transport)return false;
 Rva005948F5 *socket=new Rva005948F5;if(!socket)return false;
 int result=-1;unsigned start=timeGetTime();while(result!=0){if(timeGetTime()-start>=1000)break;result=((UDP*)socket)->Bind(*(unsigned*)((char*)v+0x1c),port);}
 if(result){((UDPDrain*)socket)->~UDPDrain();operator delete(socket);return false;}
 base->transport->RemoveSocketForSlot(slot);base->transport->setSlotSocket(socket,slot,(int*)address);return true;
}
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
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};


class GameSpyPeerMessageQueueInterface {public:virtual void f0();virtual void f1();virtual void f2();virtual void f3();virtual void f4();virtual void f5();virtual void addRequest(const BfmeOpaqueOwnedRecord492&);};extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
// BF1 f98983a7d CONNFAILED notification purpose; WB14E01D0 and
// native5A7683..5A7829 prove target callback and request/string offsets.
// Inlining the null tests preserves the native shared early failure block;
// the comma is a byte in an independently aligned four-byte stack slot.
__forceinline bool validSlots(GameSpyGameSlot*a,GameSpyGameSlot*b){if(!a)return false;if(!b)return false;return true;}
void NAT::notifyConnectionToTargetFailed(){NatConnectionView *v=(NatConnectionView*)this;GameSpyGameSlot *local=v->slots[v->local];GameSpyGameSlot *target=v->slots[v->target];if(!validSlots(local,target)){v->connectionState=5;v->previousState=5;}else{ BfmeOpaqueOwnedRecord492 request;AsciiString options;options.format("CONNFAILED%d %d %X",v->local,v->target,v->cookie);request.unknown_00=13;request.payload_flag0.value=true;request.unknown_34="NAT";
 __declspec(align(4)) char delimiter;AsciiString names,tmp;tmp.translate(*(UnicodeString*)((char*)v->slots[v->host]+0x30));if(!names.isEmpty()){delimiter=',';((StringBase<char>*)&names)->concat(&delimiter,1);}names+=tmp;
 tmp.translate(*(UnicodeString*)((char*)v->slots[v->target]+0x30));if(!names.isEmpty()){delimiter=',';((StringBase<char>*)&names)->concat(&delimiter,1);}names+=tmp;
 request.unknown_04=names.str();request.unknown_40=options.str();TheGameSpyPeerMessageQueue->addRequest(request);
}}
void NAT::rva005A7829(int hostIndex){
 NatConnectionView*v=(NatConnectionView*)this;GameSpyGameSlot*local=v->slots[v->local];GameSpyGameSlot*host=v->slots[v->host];if(!local||!host)return;
 BfmeOpaqueOwnedRecord492 request;AsciiString options,name;name.translate(*(UnicodeString*)((char*)local+0x30));options.format("NATINITED%d %d %s",v->local,hostIndex,name.str());request.unknown_00=13;request.payload_flag0.value=true;request.unknown_34="NAT";
 AsciiString hostName;hostName.translate(*(UnicodeString*)((char*)v->slots[v->host]+0x30));request.unknown_04=hostName.str();request.unknown_40=options.str();TheGameSpyPeerMessageQueue->addRequest(request);
}

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
struct hostent { char *name; char **aliases; short addrtype,length; char **addr_list; };
extern "C" __declspec(dllimport) hostent *__stdcall gethostbyname(const char *);
struct UDPBindValues { unsigned long address; unsigned short port; };
// BF1 NAT.cpp at9cbfb551 supplies the mangled-source-port semantic lead.
// Target WB14DD120 names findMyMangledPort and retail5A8405..5A854C
// proves all327B, slot flags40, source/target14/18 and UDP retry loops.
// WB reloads the local slot after the target guard; preserve both lookups
// so the compiler keeps retail's local-slot null test. The eight-byte
// endpoint object is shared with the verified socket binder.
void NAT::findMyMangledPort() {
 NatConnectionView *v=(NatConnectionView*)this;
 unsigned int sourcePort=((const Rva005A684F *)this)->get(v->local);
 unsigned int flags=*(unsigned*)((char*)v->slots[v->local]+0x40);
 GameSpyGameSlot *targetSlot=v->slots[v->target];
 if (!targetSlot) { rva005A6C90(5); return; }
 GameSpyGameSlot *localSlot=v->slots[v->local];
 if (!localSlot) { rva005A6C90(5); return; }
 rva005A6C90(2);
 if (((Rva005A684F*)this)->m_slots[v->target]->m_00 == ((Rva005A684F*)this)->m_slots[v->local]->m_00) {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)v->target,(int *)&values)) break;
   ++sourcePort;
  }
  rva005A7974((unsigned short)sourcePort,targetSlot);
  return;
 }
 if (flags && !(flags&1)) {
  char name[256];
  FirewallHelperClass::getManglerName(1,name);
  hostent *host=gethostbyname(name);
  if (!host) { rva005A7974((unsigned short)sourcePort,targetSlot); return; }
  memcpy(&v->manglerAddress,host->addr_list[0],4);
  v->manglerAddress=htonl(v->manglerAddress);
  v->manglerRetryTime=timeGetTime()+g_00DD35BC;
  v->manglerRetries=0;
  if(g_a063b0) ((Rva005A6A83 *)this)->rva005A6A83();
 } else {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)v->target,(int *)&values)) break;
   ++sourcePort;
  }
  rva005A7974((unsigned short)sourcePort,targetSlot);
  v->previousSource=(unsigned short)sourcePort;
 }
}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern unsigned g_Va00DD35D0;unsigned g_natPortWaitInterval=15000;
// Native5A89C2..5A8ABF and WB14DC750 supply the two-slot reset ABI.
// BF1 NAT.cpp9cbfb551 supplies reset/probe semantics; the compact BF2
// schema and timer layout are independently read from target bytes.
// Keep the target-slot pointer read before the peer IP read: VC7.1
// otherwise swaps these independent loads. The barrier emits no code.
void NAT::rva005A89C2(int target,int cookie){
 NatConnectionView*v=(NatConnectionView*)this;v->retries=0;v->target=target;v->connectionState=1;v->previousState=1;v->active=true;v->beenProbed=false;v->unknown943=false;v->sendPort=false;v->receivedPort=false;v->cookie=cookie;v->roundTimeout=timeGetTime()+g_Va00DD35D0;
 GameSpyGameSlot*other=v->slots[v->target];GameSpyGameSlot*local=v->slots[v->local];
 if(other&&local){
  Rva005A684FWord *entry=((Rva005A684F*)this)->m_slots[target];_ReadWriteBarrier();entry->m_00=*(unsigned*)((char*)other+0x38);
  ((Rva005A6D47*)this)->schema.negotiationStarted(v->local,target,cookie,!rva005A6709());
  if(!(*(unsigned*)((char*)other+0x40)&8)&&(*(unsigned*)((char*)local+0x40)&8))v->nextSendTime=-1;
  findMyMangledPort();v->nextPortSendTime=timeGetTime()+s_probeRetryInterval;v->timeoutTime=timeGetTime()+g_natPortWaitInterval;((Rva005A6D47*)this)->state=1;
 }else{v->connectionState=5;v->previousState=5;}
}
