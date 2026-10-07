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
	int Rva00817B30(unsigned int tick);
}

extern char g_Rva0130AF38Lock[4];
extern int g_Rva0130AD08Count;

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
	int CommUdpProcess();
	void CommUdpSetup(void *ref, void *packet, void *from);
	int CommUdpPoke(void *ref);
	int CommUdpListen(void *ref, const char *text);
	int CommUDPSend(void *ref, const void *buffer, int length, int flags);
	void Rva00818500(void *ref, void *from);
	int Rva00819090(void *ref, void *socket, const void *address);
}

// The CommUDP tick. Logs "CommUdpProcess: got RAW_PACKET_INIT", closes the
// connection on timeout, and handles poke packets -- including retargeting the
// peer when one arrives from an address other than the expected one.
// CommUdpProcess arrived as a lifted byte-dump in the BFME1 source; removed for
// conversion (anti-lift policy). Convert to real C++ separately.

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
		Rva007FEBD0(g_Rva0130AF38Lock);
		*(int *)(packet + 8) = 6;
		*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
		CommUDPWrite(ref, packet);
		Rva007FECB0(g_Rva0130AF38Lock);
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
		Rva007FEBD0(g_Rva0130AF38Lock);
		Rva00817640(ref);
		if (g_Rva0130AD08Count != 0) {
			tick = Rva007FEA00();
			while (Rva00817B30(tick) > 0) {
			}
			g_Rva0130AD08Count = 0;
		}
		Rva007FECB0(g_Rva0130AF38Lock);
	}
    return queued > 0 ? queued : 1;
}

// ?g_Rva0130AD08Count@@3HA: matched references place it at VA 0xe0a720; also referenced as _g_Rva0130AD08Count.
int g_Rva0130AD08Count;
#pragma comment(linker, "/alternatename:_g_Rva0130AD08Count=?g_Rva0130AD08Count@@3HA")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_Rva00817030=_CommUDPWrite")
#pragma comment(linker, "/alternatename:_Rva00817210Op=_CommUDPResolve")
#pragma comment(linker, "/alternatename:_Rva008173C0Op=_CommUDPSend")
#pragma comment(linker, "/alternatename:_Rva00818D90Op=_CommUdpListen")
#pragma comment(linker, "/alternatename:_Rva00819300Op=_CommUDPConnect")
