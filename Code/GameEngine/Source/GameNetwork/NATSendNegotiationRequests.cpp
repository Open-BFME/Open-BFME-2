// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A7A96@NAT@@QAEXPBV?$vector@URva005A7A96Pair@@V?$allocator@URva005A7A96Pair@@@_STL@@@_STL@@@Z
// @0x005A7A96 518B: NAT port-negotiation request sender (one caller,
// 0x005A90D6).  For every slot pair in the list whose two slots exist and
// both have their +0x8E4 byte gate set, take the next negotiation cookie
// (0x005A671D), format "NEGO%d %d %X" from the pair and cookie, address a
// "NAT/" player UTM to both slot names joined by ',', record the start in
// the PortNegotiationSchema member at +0x28 (0x005DBF8C) and queue the
// request (g_00A02340 slot 6).  An empty translated name abandons the walk.
// Request, queue and NAT layout follow the sibling Rva005A8666BoxNat.cpp
// (NAT::rva005A7974, the "PORT" request); WorldBuilder twin 0x014E30C0 is
// unnamed (string lead) and agrees on the flow.
// This parser imports strtok; keep the CRT declaration read under
// /D_CRTIMP= separate from the measured IAT declaration below.
#define strtok strtok_unimported
#include "ascii_string.h"
#include "../../Include/GameNetwork/Transport.h"
#include "unicode_string.h"
#include <string>
#include <vector>
#undef strtok

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
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
	union
	{
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

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(PeerRequest *rec);
};

extern Global003EF728V6 *g_00A02340;

int Rva005A671DNext();	// 0x005A671D next negotiation cookie

class PortNegotiationSchema
{
public:
	void negotiationStarted(unsigned short a, unsigned short b, int cookie, bool started);
    int getActionID(unsigned short,unsigned short);
    bool receivedAPong(unsigned short,unsigned short,int);
    void *peekPing(unsigned short,unsigned short);
    bool setPingStats(unsigned short,unsigned short,float,float,float);	// 0x005DBF8C
};

struct Rva005A7A96Slot
{
	char pad[0x30];
	UnicodeString m_name;	// +0x30
};

struct Rva005A7A96Pair
{
	int m_0;
	unsigned short m_a;	// +0x04 slot index
	unsigned short m_b;	// +0x06 slot index
};

struct NAT
{
	int m_0;
	Transport *m_04;
	Rva005A7A96Slot **m_8;	// slot list
	int m_hostSlot;
    int m_mode;
    int m_localSlot;
    int m_targetSlot;
    int m_unknown1c;
    int m_cookie;
    int m_unknown24;
	PortNegotiationSchema m_schema;	// +0x28
	char pad29[0x8E4 - 0x29];
	unsigned char m_8E4[8];	// per-slot gate
    int m_8ec[8];
    NetPacketAddress *m_addresses[8];
    char m_pad92c[0x943-0x92c];
    bool m_probeAnnounced;
    unsigned m_944;
    unsigned m_nextProbe;
    int m_state94c;
    int m_state950;
    char m_pad954[0x96c-0x954];
    unsigned m_nextHostUpdate;
    bool m_970;
    static unsigned s_hostUpdateInterval;
    static unsigned s_probeRetryInterval;

	void rva005A7A96(const std::vector<Rva005A7A96Pair> *pairs);
    void rva005A74D8();
    void rva005A7C9C();
    void processUDPPacket();
    void rva005A73DE(Rva005A7A96Slot*);
    void rva005A831E();
    void setConnectionState(int,int,int,int);
};

void NAT::rva005A7A96(const std::vector<Rva005A7A96Pair> *pairs)
{
	PeerRequest req;
	AsciiString options;
	if (pairs->size() == 0)
		return;
	for (std::vector<Rva005A7A96Pair>::const_iterator it = pairs->begin(); it != pairs->end(); ++it)
	{
		if (m_8[it->m_a] == 0 || m_8[it->m_b] == 0 || !m_8E4[it->m_a] || !m_8E4[it->m_b])
			continue;
		AsciiString name;
		int cookie = Rva005A671DNext();
		options.format("NEGO%d %d %X", it->m_a, it->m_b, cookie);
		req.unknown_00 = 0xd;
		req.payload_flag0.value = true;
		req.unknown_34 = "NAT/";
		name.translate(m_8[it->m_a]->m_name);
		if (name.getLength() == 0)
			return;
		req.unknown_04 = name.str();
		name.translate(m_8[it->m_b]->m_name);
		if (name.getLength() == 0)
			return;
		req.unknown_04.append(",");
		req.unknown_04.append(name.str());
		req.unknown_40 = options.str();
		m_schema.negotiationStarted(it->m_a, it->m_b, cookie, true);
		g_00A02340->f6(&req);
	}
}

__forceinline void natAppendChar(AsciiString &s,char c) {
 ((StringBase<char> *)&s)->concat(&c,1);
}
// Reference family: BFME1 nat.cpp notifyUsersOfConnectionDone (9cbfb551fe20).
// Target574D8..57683 carries both endpoint indices and the action cookie,
// selects the host and optional target names, and uses the492-byte PeerRequest.
// These target fields are witnessed by this body; original member name unknown.
void NAT::rva005A74D8() {
 Rva005A7A96Slot *local=m_8[m_localSlot];
 Rva005A7A96Slot *target=m_8[m_targetSlot];
 if(!local) { m_state94c=5;m_state950=5;return; }
 if(!target) { m_state94c=5;m_state950=5;return; }
 {
 PeerRequest req;
 AsciiString options;
 options.format("CONNDONE%d %d %X",m_targetSlot,m_localSlot,m_cookie);
 req.unknown_00=0xd;req.payload_flag0.value=true;req.unknown_34="NAT";
 AsciiString names,hostName;
 hostName.translate(m_8[m_hostSlot]->m_name);
 if(!names.isEmpty())natAppendChar(names,',');
 names.concat(hostName);
 if(m_targetSlot!=m_hostSlot) {
  hostName.translate(m_8[m_targetSlot]->m_name);
  if(!names.isEmpty())natAppendChar(names,',');
  names.concat(hostName);
 }
 req.unknown_04=names.str();req.unknown_40=options.str();g_00A02340->f6(&req);
}
}

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class GameSlot { public: bool isHuman() const; };
// Native data9D35D4 is4000, referenced only by this host-update loop.
// Its original symbol name is unknown; this label describes its role.
unsigned NAT::s_hostUpdateInterval=4000;
// Reference NAT notification purpose with BFME2 per-slot status payloads.
// Target5A7C9C..5A7EDC,576B; named notifyNATHostSlot by WB family.
void NAT::rva005A7C9C() {
 if(m_localSlot!=m_hostSlot)return;
 unsigned now=timeGetTime();
 if(m_nextHostUpdate>now)return;
 AsciiString hostName,name,options;
 PeerRequest req;
 hostName.translate(m_8[m_localSlot]->m_name);
 if(hostName.getLength()==0)return;
 for(int i=0;i<8;++i) {
  if(m_8E4[i])continue;
  if(!m_8 || !m_8[i] || !((GameSlot *)m_8[i])->isHuman())continue;
  if(m_8[i]->m_name.getLength()<=0 || !m_8ec[i])continue;
  name.translate(m_8[i]->m_name);
  if(name.getLength()==0)continue;
  options.format("NATHOST%d %d %s",m_localSlot,m_8ec[i],hostName.str());
  req.unknown_00=0xd;req.payload_flag0.value=true;req.unknown_34="NAT/";
  req.unknown_40=options.str();req.unknown_04=name.str();g_00A02340->f6(&req);
 }
 m_nextHostUpdate=now+s_hostUpdateInterval;
}

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *,const char *,...);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *,const char *);
struct NetPacketAddress { unsigned ip;unsigned short port; NetPacketAddress(unsigned i,unsigned short p):ip(i),port(p){} };
#pragma pack(push,1)
// Canonical Transport ring witness: same40E stride and field offsets;
// this local representation accesses the packet storage, not a second class view.
struct NATReceivedMessage {
 unsigned crc;char data[0x400];unsigned length;unsigned ip;unsigned short port;
};
#pragma pack(pop)
typedef char NativeNATPacketStride[sizeof(NATReceivedMessage)==0x40e?1:-1];
// WB NAT::processUDPPacket identity, target5A7EDC..5A831E1090B.
// BFME1 NAT/PortNegotiationSchema supplies probe/pong/ping semantics;
// BFME2's canonical Transport layout supplies the measured128-slot ring.
__forceinline NATReceivedMessage *natPacket(Transport *transport,int index) {return reinterpret_cast<NATReceivedMessage *>(reinterpret_cast<char *>(transport)+0x20700)+index;}
__forceinline unsigned natLength(Transport *transport,int index) {return natPacket(transport,index)->length;}
__forceinline char *natData(Transport *transport,int index) {return natPacket(transport,index)->data;}
__forceinline unsigned natAddress(Transport *transport,int index) {return natPacket(transport,index)->ip;}
__forceinline unsigned short natPort(Transport *transport,int index) {return natPacket(transport,index)->port;}
__forceinline void natClear(Transport *transport,int index) {natPacket(transport,index)->length=0;}
void NAT::processUDPPacket() {
 for(int i=0;i<128;++i) {
  if(natLength(m_04,i)>0) {
   char *ptr=natData(m_04,i);
   if(!memcmp(ptr,"PROBE",strlen("PROBE"))) {
    if(m_targetSlot<0 || m_targetSlot>=8) { natClear(m_04,i);return; }
    int target,cookie;
    sscanf(ptr+strlen("PROBE"),"%d %X",&target,&cookie);
    if(m_mode==1 && target==m_targetSlot && cookie==m_cookie) {
     m_state950=4;
     bool changed=false;
     { NetPacketAddress *address=m_addresses[m_targetSlot];unsigned incomingIP=natAddress(m_04,i);if(incomingIP!=address->ip) {address->ip=incomingIP;changed=true;} }
     { NetPacketAddress *address=m_addresses[m_targetSlot];unsigned short incomingPort=natPort(m_04,i);if(incomingPort!=address->port) {address->port=incomingPort;m_970=false;changed=true;} }
     if(changed)m_04->setDestAddrToSocket(m_targetSlot,m_addresses[m_targetSlot]);
     rva005A74D8();setConnectionState(m_targetSlot,m_localSlot,m_cookie,4);
    }
   } else if(!memcmp(ptr,"PONG",strlen("PONG"))) {
    int source,cookie,stamp;
    if(sscanf(ptr+strlen("PONG"),"%d %X %X",&source,&cookie,&stamp)==3 && source>=0 && source<8 && source!=m_localSlot && m_8 && m_8[source] && ((GameSlot *)m_8[source])->isHuman()) {
     if(cookie==m_schema.getActionID(m_localSlot,source)) {
      m_schema.receivedAPong(m_localSlot,source,stamp);m_schema.peekPing(m_localSlot,source);
     }
    }
   } else if(!memcmp(ptr,"PING",strlen("PING"))) {
    char *token=strtok(ptr+strlen("PING")," ");
    int source,cookie,stamp;
    if(token && sscanf(token,"%d",&source)==1) {
     token=strtok(0," ");
     if(token && sscanf(token,"%X",&cookie)==1) {
      token=strtok(0," ");
      if(token && sscanf(token,"%X",&stamp)==1 && source>=0 && source<8 && source!=m_localSlot && m_8 && m_8[source] && ((GameSlot *)m_8[source])->isHuman() && cookie==m_schema.getActionID(source,m_localSlot)) {
       AsciiString reply;
       reply.format("PONG%d %X %X",m_localSlot,m_schema.getActionID(source,m_localSlot),stamp);
       m_04->queueSend(m_addresses[source],(const unsigned char *)reply.str(),reply.getLength()+1);
       for(token=strtok(0," ");token;token=strtok(0," ")) {
        int other,latency;
        if(sscanf(token,"%X",&other)!=1)break;
        token=strtok(0," ");if(!token || sscanf(token,"%X",&latency)!=1)break;
        m_schema.setPingStats(source,other,(float)latency,1.0f,1.0f);
       }
      }
     }
    }
   }
  }
  natClear(m_04,i);
 }
}

// Native5A73DE..5A74D8: announce the peer's PROBE through the same492-byte
// request and queue used by the verified connection/host notifications.
// String translation accesses the selected slot name30; type13 and flag118
// are target facts. The original member name remains unresolved.
void NAT::rva005A73DE(Rva005A7A96Slot *slot) {
 PeerRequest request;
 AsciiString options;
 options.format("PROBED%d %X",m_localSlot,m_cookie);
 request.unknown_00=13;request.payload_flag0.value=true;request.unknown_34="NAT/";
 AsciiString name;
 name.translate(slot->m_name);
 request.unknown_04=name.str();request.unknown_40=options.str();
 g_00A02340->f6(&request);
}

// Target callback5A831E validates the peer index, sends the selected endpoint
// a PROBE, announces it once, and schedules the next probe using the1500ms
// data value referenced at VA DD35B8. Reference NAT supplies probe semantics.
unsigned NAT::s_probeRetryInterval=1500;
void NAT::rva005A831E() {
 if(m_targetSlot<0 || m_targetSlot>=8) {m_state94c=4;return;}
 Rva005A7A96Slot *slot=m_8[m_targetSlot];
 unsigned ip=m_addresses[m_targetSlot]->ip;
 unsigned short port=m_addresses[m_targetSlot]->port;
 AsciiString options;
 options.format("PROBE%d %X",m_localSlot,m_cookie);
 m_04->queueSend(&NetPacketAddress(ip,port),(const unsigned char *)options.str(),options.getLength()+1);
 m_04->doSend();
 if(!m_probeAnnounced) {rva005A73DE(slot);m_probeAnnounced=true;}
 m_nextProbe=timeGetTime()+s_probeRetryInterval;
}
