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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <string>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/GameNetwork/Transport.h"
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
#include "../../Include/GameNetwork/GameInfo.h"
class GameSpyGameSlot:public GameSlot{public:int profile;};
class GameSpyStagingRoom{public:GameSpyGameSlot *getGameSpySlot(int);};extern GameSpyStagingRoom *TheGameSpyGame;
class PSPlayerAllStats{public:int id;char rest[0x544];~PSPlayerAllStats();};
class GameSpyPSMessageQueueInterface{public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual PSPlayerAllStats findPlayerStatsByID(int);};extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
struct Rva00A063B0Obj;extern Rva00A063B0Obj *g_a063b0;
bool g_natTransportContextEnabled=false;unsigned g_natStatsWaitStartTick=0;
struct Rva005A7A96Pair{void *opaque00;unsigned short first,second;};
struct Rva005A7172:public _STL::vector<int>{~Rva005A7172();};
class PortNegotiationSchema{public:void negotiationStarted(unsigned short,unsigned short,int,bool);char pad00[0x18];int state[81];char pad15c[0x738-0x15c];unsigned timeout[8][8];unsigned short tries[8][8];bool rva005DBA9C(bool);bool IsConflictingWithProceedingNegotiation(unsigned short);bool rva005DC586(_STL::vector<Rva005A7A96Pair>*);};
struct Rva005A684FWord{unsigned m_00;unsigned short m_04;};
class NAT{public:void findMyMangledPort();void StartNegotiationAction(int,int);void notifyNATHostSlot();void rva005A6CA5();void sendPings();void processUDPPacket();int connectionUpdate();void processManglerResponse(unsigned short);bool SetUDPSocketForSlot(unsigned short,unsigned short,void*);void notifyConnectionToTargetFailed();void notifyConnectionFromTargetDone();void notifyHostMyNATCreated(int);void rva005A6C90(int);void sendAProbeToTarget();void rva005A7974(unsigned short,void*);static unsigned s_probeRetryInterval;static int s_manglerMaxRetryCount;bool rva005A6732()const;void rva005A7A96(const _STL::vector<Rva005A7A96Pair>*);unsigned get(unsigned)const;void probeMangler();char pad[0x90c];Rva005A684FWord *m_slots[8];};
class Rva005A6709{public:int rva005A6709()const;};typedef bool (Rva005A6709::*Rva005A6709BoolShape)()const;
#define NAT_READY(p) ((((Rva005A6709*)(p))->*reinterpret_cast<Rva005A6709BoolShape>(&Rva005A6709::rva005A6709))())
class Rva005A6D47 {public:void *vptr;Transport *transport;GameSpyGameSlot **slots;int host,state,local;char pad18[0x10];PortNegotiationSchema schema;int rva005A8F57();};
int Rva005A6D47::rva005A8F57(){
 NAT *nat=(NAT*)this;
 if(NAT_READY(nat)&&((UnicodeString*)((char*)slots[local]+0x30))->getLength()>0)nat->notifyNATHostSlot();
 if(transport){nat->rva005A6CA5();nat->sendPings();if(g_natTransportContextEnabled)transport->update((Rva00594DC0*)g_a063b0);else transport->update(0);nat->processUDPPacket();}
 switch(state){
 case 2:{bool all=true;bool timeout=false;for(int i=0;i<8;++i){GameSpyGameSlot *slot=TheGameSpyGame->getGameSpySlot(i);if(slot&&slot->isHuman()){PSPlayerAllStats stats=TheGameSpyPSMessageQueue->findPlayerStatsByID(slot->profile);if(!stats.id)all=false;}}
 unsigned now=timeGetTime();if(now>g_natStatsWaitStartTick+5000)timeout=true;if(all||timeout)state=0;
 }break;
 case 1:{if(!nat->rva005A6732())nat->connectionUpdate();if(schema.rva005DBA9C(NAT_READY(nat))){state=2;g_natStatsWaitStartTick=timeGetTime();}else if(NAT_READY(nat)){Rva005A7172 pairs;if(schema.rva005DC586((_STL::vector<Rva005A7A96Pair>*)&pairs))nat->rva005A7A96((_STL::vector<Rva005A7A96Pair>*)&pairs);}}
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
   if(!IsConflictingWithProceedingNegotiation(first)&&!IsConflictingWithProceedingNegotiation(second)){
    _STL::vector<Rva005A7A96Pair>::iterator it=pairs->begin();for(;it!=pairs->end();++it){if(it->first==first||it->second==first||it->first==second||it->second==second)goto skipPair;}
    {Rva005DBCD1 pair(first,second);((_STL::vector<Elem003AF7A0>*)pairs)->push_back(*(const Elem003AF7A0*)&pair);}
   }
  }
 skipPair:;
 }}
 return pairs->size()>0;
}

// WorldBuilder PortNegotiationSchema::IsConflictingWithProceedingNegotiation, WB VA 0x015C7940 (callsite lead, score 1).
__declspec(noinline) bool PortNegotiationSchema::IsConflictingWithProceedingNegotiation(unsigned short x){if(x<8){for(int i=0;i<8;++i){if(i!=x&&state[i+x*8]==2)return true;if(state[x+i*8]==2)return true;}}return false;}

class Rva00594E07{public:unsigned short rva00594E07(unsigned short,int);};class Rva0059534A{public:void rva0059534A(unsigned short);};class Rva0059517F{public:bool sendToManglerFromPort(unsigned long,unsigned short,unsigned short,unsigned short,bool);};class FirewallHelperClass{public:static void getManglerName(int,char*);void flagNeedToRefresh(bool);};
extern unsigned long g_00DD35BC;int NAT::s_manglerMaxRetryCount=25;
struct NatConnectionView{char pad00[8];GameSpyGameSlot **slots;int host,parentState;int local,target;unsigned localIP,cookie;bool sendPort,receivedPort;char pad26[0x92c-0x26];int retries,maxRetries;unsigned short packetID,spareSocket;unsigned manglerRetryTime;int manglerRetries;unsigned short previousSource;bool beenProbed,unknown943;unsigned manglerAddress,nextSendTime;int connectionState,previousState;char pad954[8];unsigned nextPortSendTime,timeoutTime,roundTimeout,unknown968,nextHostTick;bool active;};
// BF1 f98983a7d NAT_connectionUpdate.cpp supplies mangler retry/port/probe
// semantics. Target WB14DAEB0 connectionUpdate and full551B retail control
// flow supply compact BF2 callbacks and offsets. State IDs4/5 differ from
// BF1. Retry maximum25 at9D35C0 is proven native initialized data.
int NAT::connectionUpdate(){
 NatConnectionView *natConnectionView=(NatConnectionView*)this;
 if(natConnectionView->target<0||natConnectionView->target>=8){natConnectionView->connectionState=4;return 4;}
 GameSpyGameSlot *target=natConnectionView->slots[natConnectionView->target];
 if(!natConnectionView->beenProbed&&timeGetTime()>=natConnectionView->nextPortSendTime){AsciiString name;name.translate(*(UnicodeString*)((char*)target+0x30));if(natConnectionView->sendPort){rva005A7974(get(natConnectionView->local),target);natConnectionView->nextPortSendTime=timeGetTime()+s_probeRetryInterval;}}
 if(natConnectionView->connectionState==2){
  if(!natConnectionView->sendPort){unsigned short mangled;if(g_a063b0&&(mangled=((Rva00594E07*)g_a063b0)->rva00594E07(natConnectionView->packetID,0))!=0){processManglerResponse(mangled);((Rva0059534A*)g_a063b0)->rva0059534A(natConnectionView->spareSocket);natConnectionView->spareSocket=0;}
   else if(timeGetTime()>=natConnectionView->manglerRetryTime){if(++natConnectionView->manglerRetries>s_manglerMaxRetryCount)rva005A7974(get(natConnectionView->local),target);else{if(g_a063b0)((Rva0059517F*)g_a063b0)->sendToManglerFromPort(natConnectionView->manglerAddress,natConnectionView->spareSocket,natConnectionView->packetID,4321,false);natConnectionView->manglerRetryTime=timeGetTime()+g_00DD35BC;}}
  }
  if(!natConnectionView->receivedPort){if(timeGetTime()>natConnectionView->timeoutTime){rva005A6C90(5);notifyConnectionToTargetFailed();}}
  if(natConnectionView->receivedPort&&natConnectionView->sendPort)rva005A6C90(3);
 }else if(natConnectionView->connectionState==3){if(natConnectionView->nextSendTime!=-1&&natConnectionView->nextSendTime<=timeGetTime()){if(natConnectionView->retries>natConnectionView->maxRetries){rva005A6C90(5);notifyConnectionToTargetFailed();}else{sendAProbeToTarget();++natConnectionView->retries;}}}
 if(timeGetTime()>natConnectionView->roundTimeout&&natConnectionView->connectionState!=4&&natConnectionView->connectionState!=5){rva005A6C90(5);notifyConnectionToTargetFailed();}
 if(natConnectionView->previousState!=4)((FirewallHelperClass*)g_a063b0)->flagNeedToRefresh(true);
 return natConnectionView->connectionState;
}

__declspec(noinline) unsigned NAT::get(unsigned index)const{return m_slots[index]?m_slots[index]->m_04:0;}

class GlobalData;extern GlobalData *TheWritableGlobalData;struct GlobalPortDeltaView{char pad[0xa58];short delta;};
// BF1 f98983a7d NAT.cpp processManglerResponse is the semantic guide.
// Target WB14DDD40/native282 add UDP slot binding before PORT notification;
// source port is spare+1 and simple allocation includes flags10/40.
void NAT::processManglerResponse(unsigned short mangledPort){
 NatConnectionView *natConnectionView=(NatConnectionView*)this;GameSpyGameSlot *target=natConnectionView->slots[natConnectionView->target];if(!target){rva005A6C90(5);return;}
 short delta=((GlobalPortDeltaView*)TheWritableGlobalData)->delta;unsigned short sourcePort=natConnectionView->spareSocket+1;unsigned short returnPort=0;
 unsigned fw=*(unsigned*)((char*)natConnectionView->slots[natConnectionView->local]+0x40);
 if(fw&0x10) returnPort=mangledPort+delta;else if(fw&0x40)returnPort=mangledPort+delta;else if(delta==100){returnPort=sourcePort-natConnectionView->spareSocket+mangledPort+100;}else if(!delta){returnPort=sourcePort;}else{returnPort=(mangledPort/delta+1)*delta+sourcePort%delta;}
 if(returnPort>65535)returnPort-=65535;if(returnPort<1024)returnPort+=1024;
 struct Address{unsigned ip;unsigned short port;Address():ip(0),port(0){}} address;natConnectionView->previousSource=returnPort;
 if(!SetUDPSocketForSlot(sourcePort,natConnectionView->target,&address)){probeMangler();return;}
 m_slots[natConnectionView->local]->m_04=natConnectionView->spareSocket+1;rva005A7974(returnPort,target);
 if(natConnectionView->receivedPort){rva005A6C90(3);((Rva005A6D47*)this)->transport->setDestAddrToSocket(natConnectionView->target,m_slots[natConnectionView->target]);}
}

// BF1 socket-allocation semantics guide the cleanup and ownership transfer.
// Target WB14E58F0 and retail5A6DAC..5A6E7A prove the32B allocator,
// UDP unsigned-IP Bind ABI, localIP1C, one-second retry and slot handoff.
// Checking result first retains the native EBX result across the timeout.
class UDP{public:char bytes[32];UDP();~UDP();int Bind(unsigned,unsigned short);};
bool NAT::SetUDPSocketForSlot(unsigned short port,unsigned short slot,void* address){
 Rva005A6D47 *base=(Rva005A6D47*)this;NatConnectionView*natConnectionView=(NatConnectionView*)this;
 if(slot>=8)return false;if(!base->transport)return false;
 UDP *socket=new UDP;if(!socket)return false;
 int result=-1;unsigned start=timeGetTime();while(result!=0){if(timeGetTime()-start>=1000)break;result=((UDP*)socket)->Bind(*(unsigned*)((char*)natConnectionView+0x1c),port);}
 if(result){socket->~UDP();operator delete(socket);return false;}
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
__forceinline bool validSlots(GameSpyGameSlot*gameSpyGameSlot,GameSpyGameSlot*b){if(!gameSpyGameSlot)return false;if(!b)return false;return true;}
void NAT::notifyConnectionToTargetFailed(){NatConnectionView *natConnectionView=(NatConnectionView*)this;GameSpyGameSlot *local=natConnectionView->slots[natConnectionView->local];GameSpyGameSlot *target=natConnectionView->slots[natConnectionView->target];if(!validSlots(local,target)){natConnectionView->connectionState=5;natConnectionView->previousState=5;}else{ BfmeOpaqueOwnedRecord492 request;AsciiString options;options.format("CONNFAILED%d %d %X",natConnectionView->local,natConnectionView->target,natConnectionView->cookie);request.unknown_00=13;request.payload_flag0.value=true;request.unknown_34="NAT";
 __declspec(align(4)) char delimiter;AsciiString names,tmp;tmp.translate(*(UnicodeString*)((char*)natConnectionView->slots[natConnectionView->host]+0x30));if(!names.isEmpty()){delimiter=',';((StringBase<char>*)&names)->concat(&delimiter,1);}names+=tmp;
 tmp.translate(*(UnicodeString*)((char*)natConnectionView->slots[natConnectionView->target]+0x30));if(!names.isEmpty()){delimiter=',';((StringBase<char>*)&names)->concat(&delimiter,1);}names+=tmp;
 request.unknown_04=names.str();request.unknown_40=options.str();TheGameSpyPeerMessageQueue->addRequest(request);
}}
// WorldBuilder NAT::notifyHostMyNATCreated, WB VA 0x014E08D0 (strings lead, score 1).
void NAT::notifyHostMyNATCreated(int hostIndex){
 NatConnectionView*natConnectionView=(NatConnectionView*)this;GameSpyGameSlot*local=natConnectionView->slots[natConnectionView->local];GameSpyGameSlot*host=natConnectionView->slots[natConnectionView->host];if(!local||!host)return;
 BfmeOpaqueOwnedRecord492 request;AsciiString options,name;name.translate(*(UnicodeString*)((char*)local+0x30));options.format("NATINITED%d %d %s",natConnectionView->local,hostIndex,name.str());request.unknown_00=13;request.payload_flag0.value=true;request.unknown_34="NAT";
 AsciiString hostName;hostName.translate(*(UnicodeString*)((char*)natConnectionView->slots[natConnectionView->host]+0x30));request.unknown_04=hostName.str();request.unknown_40=options.str();TheGameSpyPeerMessageQueue->addRequest(request);
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
 NatConnectionView *natConnectionView=(NatConnectionView*)this;
 unsigned int sourcePort=get(natConnectionView->local);
 unsigned int flags=*(unsigned*)((char*)natConnectionView->slots[natConnectionView->local]+0x40);
 GameSpyGameSlot *targetSlot=natConnectionView->slots[natConnectionView->target];
 if (!targetSlot) { rva005A6C90(5); return; }
 GameSpyGameSlot *localSlot=natConnectionView->slots[natConnectionView->local];
 if (!localSlot) { rva005A6C90(5); return; }
 rva005A6C90(2);
 if (m_slots[natConnectionView->target]->m_00 == m_slots[natConnectionView->local]->m_00) {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)natConnectionView->target,(int *)&values)) break;
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
  memcpy(&natConnectionView->manglerAddress,host->addr_list[0],4);
  natConnectionView->manglerAddress=htonl(natConnectionView->manglerAddress);
  natConnectionView->manglerRetryTime=timeGetTime()+g_00DD35BC;
  natConnectionView->manglerRetries=0;
  if(g_a063b0) probeMangler();
 } else {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)natConnectionView->target,(int *)&values)) break;
   ++sourcePort;
  }
  rva005A7974((unsigned short)sourcePort,targetSlot);
  natConnectionView->previousSource=(unsigned short)sourcePort;
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
void NAT::StartNegotiationAction(int target,int cookie){
 NatConnectionView*natConnectionView=(NatConnectionView*)this;natConnectionView->retries=0;natConnectionView->target=target;natConnectionView->connectionState=1;natConnectionView->previousState=1;natConnectionView->active=true;natConnectionView->beenProbed=false;natConnectionView->unknown943=false;natConnectionView->sendPort=false;natConnectionView->receivedPort=false;natConnectionView->cookie=cookie;natConnectionView->roundTimeout=timeGetTime()+g_Va00DD35D0;
 GameSpyGameSlot*other=natConnectionView->slots[natConnectionView->target];GameSpyGameSlot*local=natConnectionView->slots[natConnectionView->local];
 if(other&&local){
  Rva005A684FWord *entry=m_slots[target];_ReadWriteBarrier();entry->m_00=*(unsigned*)((char*)other+0x38);
  ((Rva005A6D47*)this)->schema.negotiationStarted(natConnectionView->local,target,cookie,!NAT_READY(this));
  if(!(*(unsigned*)((char*)other+0x40)&8)&&(*(unsigned*)((char*)local+0x40)&8))natConnectionView->nextSendTime=-1;
  findMyMangledPort();natConnectionView->nextPortSendTime=timeGetTime()+s_probeRetryInterval;natConnectionView->timeoutTime=timeGetTime()+g_natPortWaitInterval;((Rva005A6D47*)this)->state=1;
 }else{natConnectionView->connectionState=5;natConnectionView->previousState=5;}
}
