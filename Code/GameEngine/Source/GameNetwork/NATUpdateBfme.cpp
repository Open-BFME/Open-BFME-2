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
class PortNegotiationSchema{public:char pad00[0x18];int state[81];char pad15c[0x738-0x15c];unsigned timeout[8][8];unsigned short tries[8][8];bool rva005DBA9C(bool);bool rva005DBA60(unsigned short);bool rva005DC586(_STL::vector<Rva005A7A96Pair>*);};
class NAT{public:bool rva005A6709();void rva005A7C9C();void rva005A6CA5();void sendPings();void processUDPPacket();void rva005A879B();void rva005A7A96(const _STL::vector<Rva005A7A96Pair>*);};
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
