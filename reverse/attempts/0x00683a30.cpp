// _CommUdpProcess
// partial score=0.9 date=2026-09-22
// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Near miss for _CommUdpProcess at 0x00683A30 (2207 bytes). Drop this function
// into Code/Libraries/Source/DirtySock/commudp.cpp in place of the 'Convert to
// real C++ separately' note, and change that file's extern "C" prototype to
// int CommUdpProcess(unsigned int tick) (its caller already passes tick).
// State: the frame (0x44, /GZ guards around fromLength and from[]) and the first
// 0x5A3 bytes match exactly. After the indirect callback at +0x592 retail picks
// ecx where this picks eax for the next statement, and from there 155 of 162
// diffs are pure eax/ecx/edx permutation (the rest are 1-byte jump shifts that
// follow from it). Tried: 3 decrement spellings, 3 call spellings, struct-member
// call, &&/?: guards, /RTC1 /RTCsu /RTCsc, and compiling as C -- no change. With
// /GZ removed the choice is still eax, so the ESP check is not the trigger.
// The CommUDP tick. Reads at most one datagram per pass into the shared receive
// record, dispatches it to the connection it belongs to (setup, poke, split
// packets), then runs every connection's timers; a poke from an unexpected
// address retargets the matching peer. Returns how many datagrams it read, so
// the caller loops while it is positive.
//
// Written from the retail body (0x00683A30): the BFME1 donor was a lifted
// byte-dump. The two static receive records share one layout: payload length,
// source address, packet kind, connection identifier, then the payload.
struct CommUdpRawPacket
{
	int len;
	unsigned int from;
	unsigned int kind;
	unsigned int ident;
	unsigned char data[0x240];
};

extern CommUdpRawPacket g_commUdpRecv;		// retail 0x00E0A728
extern CommUdpRawPacket g_commUdpSplit;		// retail 0x00E0A978
extern char *g_commUdpRefs;			// retail 0x00E0ABA0, linked through +0x78

extern "C" {
	int Rva007FDA50(void *socket, void *buffer, int length, int flags, void *from, int *fromLength);
	int Rva007FF720(const void *left, const void *right);
	void Rva008186C0(void *ref, void *packet);
	int Rva008187E0(void *ref, void *packet);
	void Rva00818620(void *ref);
	void Rva00816F60(void *ref);
	void Rva00818AD0(void *ref);
}

int CommUdpProcess(unsigned int tick)
{
	int fromLength;
	int count;
	char *ref;
	char *pending;
	unsigned char from[0x10];
	void *socket;
	int savedWindow;
	int pieces;
	unsigned int idle;

	count = 0;
	pending = 0;
	memset(from, 0, sizeof(from));
	g_commUdpRecv.len = -1;
	socket = 0;

	for (ref = g_commUdpRefs; ref != 0; ref = *(char **)(ref + 0x78)) {
		if (*(void **)(ref + 0x7C) != 0 && *(void **)(ref + 0x7C) != socket) {
			socket = *(void **)(ref + 0x7C);
			fromLength = sizeof(from);
			fromLength = Rva007FDA50(socket, &g_commUdpRecv.kind, 0x220, 0, from, &fromLength);
			if (fromLength > 0) {
				g_commUdpRecv.len = fromLength - 8;
				g_commUdpRecv.from = (((from[8] << 8 | from[9]) << 8 | from[10]) << 8) | from[11];
				if (g_commUdpRecv.kind == 1) {
					Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_INIT\n");
				}
				if (g_commUdpRecv.kind == 2) {
					Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_CONN\n");
				}
				count++;
				break;
			}
		}
	}

	for (ref = g_commUdpRefs; ref != 0; ref = *(char **)(ref + 0x78)) {
		tick = Rva007FEA00();

		if (pending == 0 && socket == *(void **)(ref + 0x7C) && *(int *)(ref + 0x90) == 3
		    && g_commUdpRecv.len == 0 && g_commUdpRecv.kind == 1
		    && *(unsigned int *)(ref + 0x94) == g_commUdpRecv.ident) {
			pending = ref;
		}

		if (g_commUdpRecv.len >= 0 && *(int *)(ref + 0x90) != 3 && *(int *)(ref + 0x90) != 5
		    && socket == *(void **)(ref + 0x7C) && Rva007FF720(ref + 0x80, from) == 0) {
			*(int *)(ref + 0x60) += g_commUdpRecv.len;
			*(int *)(ref + 0x68) += 1;
			if (g_commUdpRecv.kind == 1 || g_commUdpRecv.kind == 2 || g_commUdpRecv.kind == 3) {
				CommUdpSetup(ref, &g_commUdpRecv, from);
			} else if (*(int *)(ref + 0x90) != 4) {
			} else if (g_commUdpRecv.kind == 4) {
				*(unsigned int *)(ref + 0xDC) = g_commUdpRecv.from;
				Rva008186C0(ref, &g_commUdpRecv);
			} else if (g_commUdpRecv.kind > 0x10000000) {
				savedWindow = *(int *)(ref + 0xAC);
				pieces = g_commUdpRecv.kind >> 28;
				g_commUdpSplit.from = g_commUdpRecv.from;
				g_commUdpSplit.kind = (g_commUdpRecv.kind & 0x0FFFFFFF) - pieces;
				g_commUdpSplit.ident = g_commUdpRecv.ident;
				*(unsigned int *)(ref + 0xDC) = g_commUdpRecv.from;
				for (; pieces >= 0; pieces--) {
					if (pieces > 0) {
						g_commUdpRecv.len -= 1;
						g_commUdpSplit.len = g_commUdpRecv.data[g_commUdpRecv.len];
					} else {
						g_commUdpSplit.len = g_commUdpRecv.len;
					}
					g_commUdpRecv.len -= g_commUdpSplit.len;
					memcpy(g_commUdpSplit.data, g_commUdpRecv.data + g_commUdpRecv.len, g_commUdpSplit.len);
					Rva008186C0(ref, &g_commUdpSplit);
					if (Rva008187E0(ref, &g_commUdpSplit) < 0) {
						pieces = 0;
					}
					if (pieces > 0 && savedWindow != *(int *)(ref + 0xAC)) {
						savedWindow = *(int *)(ref + 0xAC);
					}
					g_commUdpSplit.kind += 1;
				}
			} else {
				*(unsigned int *)(ref + 0xDC) = g_commUdpRecv.from;
				Rva008186C0(ref, &g_commUdpRecv);
				Rva008187E0(ref, &g_commUdpRecv);
			}
			g_commUdpRecv.len = -1;
		}

		if (*(int *)(ref + 0x90) == 2 && tick - *(unsigned int *)(ref + 0xD8) > 1000) {
			Rva00818620(ref);
		}
		if (*(int *)(ref + 0x90) == 4 && *(int *)(ref + 0xC8) != *(int *)(ref + 0xC0)) {
			Rva00817640(ref);
		}
		if (*(int *)(ref + 0x90) == 4 && tick - *(unsigned int *)(ref + 0xDC) > 120000
		    && tick - *(unsigned int *)(ref + 0xD8) < 2000) {
			Rva007FE780Printf("CommUDP: closing connection due to timeout\n");
			Rva007FE780Printf("CommUDP: tick=%d, rtick=%d, stick=%d\n",
			                   tick, *(unsigned int *)(ref + 0xDC), *(unsigned int *)(ref + 0xD8));
			Rva00816F60(ref);
		}
		if (*(int *)(ref + 0x90) == 3 && *(unsigned short *)(ref + 0x80) == 2
		    && tick > *(unsigned int *)(ref + 0xD8) + 1000) {
			CommUdpPoke(ref);
		}
		if (*(int *)(ref + 0x21C) == 0 && tick > *(unsigned int *)(ref + 0xE0) + 250) {
			*(unsigned int *)(ref + 0xE0) = tick;
			*(int *)(ref + 0x21C) |= 4;
		}
		if (*(int *)(ref + 0x218) == 0 && *(int *)(ref + 0x21C) != 0) {
			*(int *)(ref + 0x218) += 1;
			if (*(void **)(ref + 0x220) != 0) {
				(*(void (__cdecl **)(void *, int))(ref + 0x220))(ref, *(int *)(ref + 0x21C));
			}
			*(int *)(ref + 0x218) -= 1;
			*(int *)(ref + 0x21C) = 0;
			tick = Rva007FEA00();
		}
		if (*(int *)(ref + 0x90) == 4 && *(int *)(ref + 0xC8) == *(int *)(ref + 0xC0)) {
			idle = tick - *(unsigned int *)(ref + 0xD8);
			if ((idle > 100 && *(int *)(ref + 0xB0) != *(int *)(ref + 0xAC))
			    || (idle > 100 && *(int *)(ref + 0xC0) != *(int *)(ref + 0xC4))
			    || idle > 2500 || *(int *)(ref + 0xB4) >= 0x800) {
				*(int *)(ref + 0xB4) = 0;
				Rva00818AD0(ref);
			}
		}
	}

	if (g_commUdpRecv.len >= 0 && g_commUdpRecv.kind == 5 && *(unsigned short *)&from[0] == 2) {
		Rva007FE780Printf("CommUDP: received poke packet (from=%08x)\n",
		                   (((from[4] << 8 | from[5]) << 8 | from[6]) << 8) | from[7]);
		for (ref = g_commUdpRefs; ref != 0; ref = *(char **)(ref + 0x78)) {
			if (*(int *)(ref + 0x90) == 2 && *(unsigned short *)(ref + 0x80) == 2
			    && *(unsigned int *)(ref + 0x94) == g_commUdpRecv.ident) {
				Rva007FE780Printf("CommUdp: poke source = %08x -- forcing match\n",
				                   (((*(unsigned char *)(ref + 0x84) << 8 | *(unsigned char *)(ref + 0x85)) << 8 | *(unsigned char *)(ref + 0x86)) << 8) | *(unsigned char *)(ref + 0x87));
				if (socket == *(void **)(ref + 0x7C)) {
					Rva007FE780Printf("CommUDP: changing peer to %08x:%d due to poke (was expecting %08x:%d)\n",
					                   (((from[4] << 8 | from[5]) << 8 | from[6]) << 8) | from[7],
					                   from[2] << 8 | from[3],
					                   (((*(unsigned char *)(ref + 0x84) << 8 | *(unsigned char *)(ref + 0x85)) << 8 | *(unsigned char *)(ref + 0x86)) << 8) | *(unsigned char *)(ref + 0x87),
					                   *(unsigned char *)(ref + 0x82) << 8 | *(unsigned char *)(ref + 0x83));
					memcpy(ref + 0x80, from, sizeof(from));
					break;
				}
			}
		}
	}

	if (pending != 0 && g_commUdpRecv.len == 0) {
		ref = pending;
		if (*(unsigned int *)(ref + 0x94) == g_commUdpRecv.ident) {
			memcpy(ref + 0x80, from, sizeof(from));
			*(int *)(ref + 0x90) = 4;
			CommUdpSetup(ref, &g_commUdpRecv, from);
		}
	}
	return count;
}
