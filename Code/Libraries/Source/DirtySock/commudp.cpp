// cl: /DNDEBUG /MD /GX /Od /GZ /GS

#define _DLL
#include <string.h>

// EA's DirtySock CommUDP transport, which BFME uses for its GameSpy/online
// traffic. It has no counterpart in the vendored Zero Hour reference, and no
// __FILE__ string for it survives in the executable, so the directory name here
// is inferred from the module prefixes retail logs -- commudp, commtcp,
// protoadvt, NetGameUtil -- and from the sibling EA middleware that already
// lives under Code/Libraries/Source (Compression/EAC). Move it if better
// evidence turns up; only the `source` column of these rows has to follow.
//
// The surviving log strings establish the named entry points; the address-
// derived Rva helpers are retained by their retail RVAs and call graph. They
// are declared extern "C" because DirtySock is a C library.
//
// The lockstep path does not run through here -- that is SAGE's own udp.cpp.

extern "C" {
	int CommUDPWrite(void *ref, void *packet);
	int CommUDPConnect(void *ref, const char *addr, int bind, int peer);
	int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider);
	int Rva007FD920(void *socket, const void *data, int length, int flags, void *address, int addressLength);
	unsigned int Rva007FEA00();
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void *Rva007FD2D0(int family, int type, int protocol);
	int Rva007FD510(void *socket, const void *address, int addressLength);
	void Rva007FD3F0(void *socket);
	void Rva00818FF0(void *ref, const char *text);
	int Rva00819590(void *ref, void *socket, const void *peerAddress);
	void Rva007FEBD0(void *lock);
	void Rva007FECB0(void *lock);
	void Rva00817640(void *ref);
}

struct CommUdpBuf
{
	int m_count;             // +0x00
	int m_reserved;          // +0x04
	int m_length;            // +0x08
	int m_ident;             // +0x0C
	unsigned int m_type;     // +0x10
	int m_typeExtra;         // +0x14
	unsigned char m_data[0x1000];   // +0x18
};

struct CommUdpLockRegion
{
	unsigned char m_gap[0x28];
	int m_978;               // +0x28
	int m_97c;               // +0x2C
	int m_980;               // +0x30
	int m_984;               // +0x34
	unsigned char m_payload[0x1F0];
};

extern "C" CommUdpLockRegion g_Rva0130AF38Lock;
extern "C" int g_Rva0130AD08Count;	// C linkage: Y4CommTransportLife.c (C) shares it

int Rva007FE780Printf(const char *format, ...);
// The C++ printf spelling and rowed C printer both resolve to retail VA 0x0066AC50.
#pragma comment(linker, "/alternatename:?Rva007FE780Printf@@YAHPBDZZ=_Rva007FE780")

// Always fails: it logs "CommUDPResolve: Resolve functionality not supported by
// CommUDP" and returns the error.
int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider)
{
	Rva007FE780Printf("CommUDPResolve: Resolve functionality not supported by CommUDP\n");
	return -1;
}

extern "C" void Rva00817230(void)
{
}

// Hands a datagram to the socket layer, logging "CommUDPWrite: SocketSendto
// returned %d" on the way out.
int CommUDPWrite(void *ref, void *packet)
{
	int result;
	int packetLength = *(int *)packet + 8;
	result = Rva007FD920(*(void **)((char *)ref + 0x7C),
	                     (char *)packet + 8, packetLength, 0,
	                     (char *)ref + 0x80, 0x10);
	if (result == packetLength) {
		*(unsigned int *)((char *)ref + 0xD8) = Rva007FEA00();
		*(int *)((char *)ref + 0x5C) += packetLength;
		++*(int *)((char *)ref + 0x64);
		if (*(int *)((char *)packet + 8) != 6) {
			*(int *)((char *)ref + 0xB4) = 0;
		}
	} else {
		Rva007FE780Printf("CommUDPWrite: SocketSendto returned %d\n", result);
		*(int *)((char *)ref + 0xD4) = result;
		result = -1;
	}
	return result;
}

// Opens the port. Logs "CommUdpConnect: addr=%08x, bind=%d, peer=%d
// connident=0x%08x" on entry and "CommUDPConnect: bind to %d failed with %d"
// when the bind is refused, then retries with port 0.
int CommUDPConnect(void *ref, const char *addr, int bind, int peer)
{
	int result;
	int iConnPort;
	int iListenPort;
	unsigned int uAddr;
	void *socket;
	unsigned char bindaddr[0x10];
	unsigned char peeraddr[0x10];
	unsigned int temp;

	*(unsigned short *)&peeraddr[0] = 2;
	*(unsigned short *)&peeraddr[2] = 0;
	*(unsigned int *)&peeraddr[4] = 0;
	*(unsigned int *)&peeraddr[8] = 0;
	*(unsigned int *)&peeraddr[12] = 0;
	*(unsigned short *)&bindaddr[0] = 2;
	*(unsigned short *)&bindaddr[2] = 0;
	*(unsigned int *)&bindaddr[4] = 0;
	*(unsigned int *)&bindaddr[8] = 0;
	*(unsigned int *)&bindaddr[12] = 0;
	result = Rva007FFDD0(&uAddr, &iListenPort, &iConnPort, addr);
	if ((result & 3) != 3) {
		return -3;
	}
	if (iConnPort == 0) {
		iConnPort = iListenPort;
		++iListenPort;
	}
	Rva00818FF0(ref, addr);
	Rva007FE780Printf("CommUdpConnect: addr=%08x, bind=%d, peer=%d connident=0x%08x\n",
	                   uAddr, iListenPort, iConnPort, *(int *)((char *)ref + 0x94));
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	bindaddr[2] = (unsigned char)(iListenPort >> 8);
	bindaddr[3] = (unsigned char)iListenPort;
	result = Rva007FD510(socket, bindaddr, 0x10);
	if (result < 0) {
		Rva007FE780Printf("CommUDPConnect: bind to %d failed with %d\n", iListenPort, result);
		bindaddr[2] = 0;
		bindaddr[3] = 0;
		result = Rva007FD510(socket, bindaddr, 0x10);
		Rva007FE780Printf("CommUDPConnect: bind to 0 with result %d\n", result);
	}
	if (result < 0) {
		Rva007FD3F0(socket);
		return -5;
	}
	temp = uAddr;
	peeraddr[7] = (unsigned char)temp; temp >>= 8;
	peeraddr[6] = (unsigned char)temp; temp >>= 8;
	peeraddr[5] = (unsigned char)temp; temp >>= 8;
	peeraddr[4] = (unsigned char)temp;
	peeraddr[2] = (unsigned char)(iConnPort >> 8);
	peeraddr[3] = (unsigned char)iConnPort;
	*(int *)((char *)ref + 0xD4) = 0;
	return Rva00819590(ref, socket, peeraddr);
}

extern "C" {
	int CommUdpProcess(unsigned int tick);
	void CommUdpSetup(void *ref, void *packet, void *sin);
	int CommUdpPoke(void *ref);
	int CommUdpListen(void *ref, const char *text);
	int CommUDPSend(void *ref, const void *buffer, int length, int flags);
	void Rva00818500(void *ref, void *sin);
	int Rva00819090(void *ref, void *socket, const void *address);
}

// The CommUDP tick. Logs "CommUdpProcess: got RAW_PACKET_INIT", closes the
// connection on timeout, and handles poke packets -- including retargeting the
// peer when one arrives sin an address other than the expected one.
// Reconstructed sin the BFME1 lift (identical instruction stream) as real C.

// The receive buffer and its state words are one .data region; the ledger names
// its head g_Rva0130AD08Count (VA 0xe0a720, provisional in commudp.cpp). The
// transmit-side state the tick touches sits in g_Rva0130AF38Lock's region.
struct CommUdpRef
{
	unsigned char m_gap[0x60];
	int m_60;                // +0x60
	int m_64;                // +0x64
	int m_68;                // +0x68
	unsigned char m_gap2[0x0C];
	struct CommUdpRef *m_next;      // +0x78
	void *m_socket;          // +0x7C
	unsigned char m_peer[0x10];     // +0x80
	int m_state;             // +0x90
	int m_sessionHash;       // +0x94
	unsigned char m_gap3[0x14];
	int m_recvSequence;      // +0xAC
	int m_reportedSequence;  // +0xB0
	int m_recvCounter;       // +0xB4
	unsigned char m_gap4[0x08];
	int m_sendWriteOffset;   // +0xC0
	int m_sendReadOffset;    // +0xC4
	int m_sendAckOffset;     // +0xC8
	unsigned char m_gap5[0x0C];
	unsigned int m_tickA;    // +0xD8
	unsigned int m_tickB;    // +0xDC
	unsigned int m_lastPoke; // +0xE0
	unsigned char m_gap6[0x134];
	int m_depth;             // +0x218
	int m_flags;             // +0x21C
	void *m_value;           // +0x220
};

// The receive buffer's head is g_Rva0130AD08Count (VA 0xe0a720); its fields are
// reached through the region view so the ledger's symbol keeps its own spelling.
#define g_commUdpPacket (*(CommUdpBuf *)&g_Rva0130AD08Count)

extern "C" int Rva007FDA50(void *socket, char *buffer, int length, int flags,
                           void *address, int *addressLength);
extern "C" int Rva007FF720(const void *first, const void *second);
extern "C" int Rva00816F60(struct CommUdpRef *comm);
extern "C" int Rva00818620(struct CommUdpRef *comm);
extern "C" void Rva008186C0(struct CommUdpRef *comm, void *payload);
extern "C" int Rva008187E0(struct CommUdpRef *comm, void *payload);
extern "C" int Rva00818AD0(struct CommUdpRef *comm);
extern "C" struct CommUdpRef *g_Rva0130B188List;

int CommUdpProcess(unsigned int tick)
{
	int len;
	int count;
	struct CommUdpRef *cur;
	struct CommUdpRef *ready;
	char sin[0x10];   // retail's /GZ descriptor names this local "sin" (a sockaddr_in)
	void *lastSocket;
	unsigned int lastTick;
	int index;
	unsigned int elapsed;

	count = 0;
	ready = 0;
	memset(sin, 0, 0x10);
	g_commUdpPacket.m_length = -1;
	lastSocket = 0;

	for (cur = g_Rva0130B188List; cur != 0; cur = cur->m_next)
	{
		if (cur->m_socket != 0)
		{
			if (cur->m_socket != lastSocket)
			{
				lastSocket = cur->m_socket;
				len = 0x10;
				// The packet header overlays the receive buffer: retail passes
				// the buffer head at +0x10 (native 0x683AD7 pushes VA 0xe0a730),
				// and m_type/m_typeExtra are the packet's first two dwords.
				len = Rva007FDA50(lastSocket, (char *)&g_commUdpPacket.m_type,
				                  0x220, 0, sin, &len);
				if (len > 0)
				{
					g_commUdpPacket.m_length = len - 8;
					g_commUdpPacket.m_ident =
						((((unsigned char)sin[8] << 8) | (unsigned char)sin[9]) << 8 |
						 (unsigned char)sin[10]) << 8 | (unsigned char)sin[11];
					if (g_commUdpPacket.m_type == 1)
						Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_INIT\n");
					if (g_commUdpPacket.m_type == 2)
						Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_CONN\n");
					count = count + 1;
					break;
				}
			}
		}
	}

	for (cur = g_Rva0130B188List; cur != 0; cur = cur->m_next)
	{
		tick = Rva007FEA00();
		if (ready == 0 && lastSocket == cur->m_socket && cur->m_state == 3 &&
		    g_commUdpPacket.m_length == 0 && g_commUdpPacket.m_type == 1 &&
		    cur->m_sessionHash == g_commUdpPacket.m_typeExtra)
		{
			ready = cur;
		}
		if (g_commUdpPacket.m_length >= 0)
		{
			if (cur->m_state != 3 && cur->m_state != 5 &&
			    lastSocket == cur->m_socket &&
			    Rva007FF720(cur->m_peer, sin) == 0)
			{
				cur->m_60 = cur->m_60 + g_commUdpPacket.m_length;
				cur->m_68 = cur->m_68 + 1;
				if (g_commUdpPacket.m_type == 1 || g_commUdpPacket.m_type == 2 ||
				    g_commUdpPacket.m_type == 3)
				{
					CommUdpSetup(cur, &g_commUdpPacket.m_length, sin);
				}
				else
				{
					if (cur->m_state != 4)
					{
					}
					else
					{
						if (g_commUdpPacket.m_type == 4)
						{
							cur->m_tickB = g_commUdpPacket.m_ident;
							Rva008186C0(cur, &g_commUdpPacket.m_length);
						}
						else if (g_commUdpPacket.m_type > 0x10000000)
						{
							lastTick = cur->m_recvSequence;
							index = g_commUdpPacket.m_type >> 28;
							g_Rva0130AF38Lock.m_97c = g_commUdpPacket.m_ident;
							g_Rva0130AF38Lock.m_980 =
								(g_commUdpPacket.m_type & 0x0FFFFFFF) - index;
							g_Rva0130AF38Lock.m_984 = g_commUdpPacket.m_typeExtra;
							cur->m_tickB = g_commUdpPacket.m_ident;
							for (; index >= 0; index--)
							{
								if (index > 0)
								{
									g_commUdpPacket.m_length =
										g_commUdpPacket.m_length - 1;
									g_Rva0130AF38Lock.m_978 =
										g_commUdpPacket.m_data[g_commUdpPacket.m_length];
								}
								else
								{
									g_Rva0130AF38Lock.m_978 = g_commUdpPacket.m_length;
								}
								g_commUdpPacket.m_length =
									g_commUdpPacket.m_length - g_Rva0130AF38Lock.m_978;
								memcpy(&g_Rva0130AF38Lock.m_payload[0],
								       &g_commUdpPacket.m_data[g_commUdpPacket.m_length],
								       g_Rva0130AF38Lock.m_978);
								Rva008186C0(cur, &g_Rva0130AF38Lock.m_978);
								if (Rva008187E0(cur, &g_Rva0130AF38Lock.m_978) < 0)
								{
									index = 0;
								}
								if (index > 0 && lastTick != cur->m_recvSequence)
								{
									lastTick = cur->m_recvSequence;
								}
								g_Rva0130AF38Lock.m_980 = g_Rva0130AF38Lock.m_980 + 1;
							}
						}
						else
						{
							cur->m_tickB = g_commUdpPacket.m_ident;
							Rva008186C0(cur, &g_commUdpPacket.m_length);
							Rva008187E0(cur, &g_commUdpPacket.m_length);
						}
					}
				}
				g_commUdpPacket.m_length = -1;
			}
		}
		if (cur->m_state == 2 && tick - cur->m_tickA > 0x3E8)
		{
			Rva00818620(cur);
		}
		if (cur->m_state == 4 && cur->m_sendAckOffset != cur->m_sendWriteOffset)
		{
			Rva00817640(cur);
		}
		if (cur->m_state == 4 && tick - cur->m_tickB > 0x1D4C0 &&
		    tick - cur->m_tickA < 0x7D0)
		{
			Rva007FE780Printf("CommUDP: closing connection due to timeout\n");
			Rva007FE780Printf("CommUDP: tick=%d, rtick=%d, stick=%d\n", tick,
			            cur->m_tickB, cur->m_tickA);
			Rva00816F60(cur);
		}
		if (cur->m_state == 3 && *(unsigned short *)cur->m_peer == 2 &&
		    tick > cur->m_tickA + 0x3E8)
		{
			CommUdpPoke(cur);
		}
		if (cur->m_flags == 0 && tick > cur->m_lastPoke + 0xFA)
		{
			cur->m_lastPoke = tick;
			cur->m_flags = cur->m_flags | 4;
		}
		if (cur->m_depth == 0 && cur->m_flags != 0)
		{
			cur->m_depth = cur->m_depth + 1;
			if (cur->m_value != 0)
			{
				((void (__cdecl *)(void *, int))cur->m_value)(cur, cur->m_flags);
			}
			// Empty dead block: retail's /Od register rotation for the two
			// statements below is one slot ahead of this spelling's; a
			// compiled-out if advances that counter without emitting code.
			if (0) { }
			cur->m_depth = cur->m_depth - 1;
			cur->m_flags = 0;
			tick = Rva007FEA00();
		}
		if (cur->m_state == 4 && cur->m_sendAckOffset == cur->m_sendWriteOffset)
		{
			elapsed = tick - cur->m_tickA;
			if ((elapsed > 0x64 && cur->m_reportedSequence != cur->m_recvSequence) ||
			    (elapsed > 0x64 && cur->m_sendWriteOffset != cur->m_sendReadOffset) ||
			    (elapsed > 0x9C4 || cur->m_recvCounter >= 0x800))
			{
				cur->m_recvCounter = 0;
				Rva00818AD0(cur);
			}
		}
	}

	if (g_commUdpPacket.m_length >= 0 && g_commUdpPacket.m_type == 5 &&
	    *(unsigned short *)sin == 2)
	{
		Rva007FE780Printf("CommUDP: received poke packet (sin=%08x)\n",
			((((unsigned char)sin[4] << 8) | (unsigned char)sin[5]) << 8 |
			 (unsigned char)sin[6]) << 8 | (unsigned char)sin[7]);
		for (cur = g_Rva0130B188List; cur != 0; cur = cur->m_next)
		{
			if (cur->m_state == 2 && *(unsigned short *)cur->m_peer == 2 &&
			    cur->m_sessionHash == g_commUdpPacket.m_typeExtra)
			{
				Rva007FE780Printf("CommUdp: poke source = %08x -- forcing match\n",
					((((unsigned char)cur->m_peer[4] << 8) | (unsigned char)cur->m_peer[5]) << 8 |
					 (unsigned char)cur->m_peer[6]) << 8 | (unsigned char)cur->m_peer[7]);
				if (lastSocket == cur->m_socket)
				{
					Rva007FE780Printf("CommUDP: changing peer to %08x:%d due to poke (was expecting %08x:%d)\n",
						((((unsigned char)sin[4] << 8) | (unsigned char)sin[5]) << 8 |
						 (unsigned char)sin[6]) << 8 | (unsigned char)sin[7],
						((unsigned char)sin[2] << 8) | (unsigned char)sin[3],
						((((unsigned char)cur->m_peer[4] << 8) | (unsigned char)cur->m_peer[5]) << 8 |
						 (unsigned char)cur->m_peer[6]) << 8 | (unsigned char)cur->m_peer[7],
						((unsigned char)cur->m_peer[2] << 8) | (unsigned char)cur->m_peer[3]);
					memcpy(cur->m_peer, sin, 0x10);
					break;
				}
			}
		}
	}
	if (ready != 0 && g_commUdpPacket.m_length == 0)
	{
		cur = ready;
		if (cur->m_sessionHash == g_commUdpPacket.m_typeExtra)
		{
			memcpy(cur->m_peer, sin, 0x10);
			cur->m_state = 4;
			CommUdpSetup(cur, &g_commUdpPacket.m_length, sin);
		}
	}
	return count;
}

// Answers an INIT with a CONN, and warns "commudp: warning - connident
// mismatch" when the connection identifier does not line up.
void CommUdpSetup(void *ref, void *packet, void *from)
{
	if (*(int *)packet != 0) {
		return;
	}

		if (*(int *)((char *)packet + 0x0C) != *(int *)((char *)ref + 0x94)) {
			Rva007FE780Printf("commudp: warning - connident mismatch\n");
			if (*(int *)((char *)packet + 8) == 1) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		} else {
			*(unsigned int *)((char *)ref + 0xDC) = Rva007FEA00() - 1000;
			if (*(int *)((char *)packet + 8) == 1) {
				Rva00818500(ref, from);
				Rva007FE780Printf("CommUdpSetup: sending CONN in response to INIT\n");
				*(int *)((char *)packet + 8) = 2;
				((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, packet);
			} else if (*(int *)((char *)packet + 8) == 2) {
				if (*(int *)((char *)ref + 0x90) == 2) {
					Rva00818500(ref, from);
					*(int *)((char *)ref + 0x90) = 4;
				}
			} else if (*(int *)((char *)packet + 8) == 3 &&
			           *(int *)((char *)ref + 0x90) == 4) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		}
}

// Sends a poke packet to prod a peer whose address may have moved.
int CommUdpPoke(void *ref)
{
	char packet[0x228];
	Rva007FE780Printf("CommUdpPoke: sending poke packet\n");
	*(int *)&packet[0] = 0;
	*(int *)&packet[8] = 5;
	*(int *)&packet[12] = *(int *)((char *)ref + 0x94);
	return ((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, &packet);
}

// Puts the socket into listening mode for an incoming CommUDP connection.
int CommUdpListen(void *ref, const char *text)
{
	int result;
	int iListenPort;
	int iConnPort;
	unsigned int poke;
	void *socket;
	unsigned char bindaddr[0x10];
	unsigned int temp;

	*(unsigned short *)&bindaddr[0] = 2;
	*(unsigned short *)&bindaddr[2] = 0;
	*(unsigned int *)&bindaddr[4] = 0;
	*(unsigned int *)&bindaddr[8] = 0;
	*(unsigned int *)&bindaddr[12] = 0;
	if ((Rva007FFDD0(&poke, &iListenPort, &iConnPort, text) & 2) == 0) {
		return -3;
	}
	bindaddr[2] = (unsigned char)(iListenPort >> 8);
	bindaddr[3] = (unsigned char)iListenPort;
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	result = Rva00819090(ref, socket, bindaddr);
	Rva00818FF0(ref, text);
	Rva007FE780Printf("CommUdpListen: err=%d, bind=%d, connident=0x%08x\n",
	                   result, iListenPort, *(int *)((char *)ref + 0x94));
	if (result == 0 && poke != 0) {
		if (iConnPort == 0) {
			iConnPort = iListenPort + 1;
		}
		Rva007FE780Printf("CommUdpListen: poke=%08x:%d\n", poke, iConnPort);
		*(unsigned short *)((char *)ref + 0x80) = 2;
		*(unsigned short *)((char *)ref + 0x82) = 0;
		*(unsigned int *)((char *)ref + 0x84) = 0;
		*(unsigned int *)((char *)ref + 0x88) = 0;
		*(unsigned int *)((char *)ref + 0x8C) = 0;
		temp = poke;
		*((unsigned char *)ref + 0x87) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x86) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x85) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x84) = (unsigned char)temp;
		*((unsigned char *)ref + 0x82) = (unsigned char)(iConnPort >> 8);
		*((unsigned char *)ref + 0x83) = (unsigned char)iConnPort;
	}
	*(int *)((char *)ref + 0xD4) = 0;
	return result;
}

// Queues an outbound packet, rejecting anything past the limit with
// "CommUDP: Oversized packet send (%d bytes)".
int CommUDPSend(void *ref, const void *buffer, int length, int flags)
{
	int queued;
	char *packet;
	unsigned int tick;

	if (*(int *)((char *)ref + 0x90) != 4) {
		return -2;
	}
	if ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
	        *(int *)((char *)ref + 0xBC) == *(int *)((char *)ref + 0xC4)) {
		return 0;
	}
	if (length > *(int *)((char *)ref + 0xB8) - 0x10) {
		Rva007FE780Printf("CommUDP: Oversized packet send (%d bytes)\n", length);
		return -6;
	}
	if (length == 0) {
		queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
		           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
		         *(int *)((char *)ref + 0xB8);
		return queued + 1;
	}
	packet = *(char **)((char *)ref + 0xCC) + *(int *)((char *)ref + 0xC0);
	*(int *)packet = length;
	memcpy(packet + 0x10, buffer, length);
	*(unsigned int *)(packet + 4) = Rva007FEA00();
	if ((flags & 1) != 0) {
		Rva007FEBD0(&g_Rva0130AF38Lock);
		*(int *)(packet + 8) = 6;
		*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
		CommUDPWrite(ref, packet);
		Rva007FECB0(&g_Rva0130AF38Lock);
		return 1;
	}
	*(int *)(packet + 8) = *(int *)((char *)ref + 0xD0);
	++*(int *)((char *)ref + 0xD0);
	*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
	*(int *)((char *)ref + 0xC0) =
		(*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
		*(int *)((char *)ref + 0xBC);
	queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
	           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
	         *(int *)((char *)ref + 0xB8);
	if (queued < 0x10) {
		Rva007FEBD0(&g_Rva0130AF38Lock);
		Rva00817640(ref);
		if (g_Rva0130AD08Count != 0) {
			tick = Rva007FEA00();
			while (CommUdpProcess(tick) > 0) {
			}
			g_Rva0130AD08Count = 0;
		}
		Rva007FECB0(&g_Rva0130AF38Lock);
	}
    return queued > 0 ? queued : 1;
}

// ?g_Rva0130AD08Count@@3HA: matched references place it at VA 0xe0a720; also referenced as _g_commUdpPacket.
int g_Rva0130AD08Count;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_Rva00817030=_CommUDPWrite")
#pragma comment(linker, "/alternatename:_Rva00817210Op=_CommUDPResolve")
#pragma comment(linker, "/alternatename:_Rva008173C0Op=_CommUDPSend")
#pragma comment(linker, "/alternatename:_Rva00818D90Op=_CommUdpListen")
#pragma comment(linker, "/alternatename:_Rva00819300Op=_CommUDPConnect")
