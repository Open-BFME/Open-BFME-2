// _CommUdpProcess
// partial score=0.9 date=2026-10-07
// _CommUdpProcess
// partial score=0.9 date=2026-09-22, campaign 2026-09-23 (peppy-penguin)
// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Near miss for _CommUdpProcess at 0x00683A30 (2207 bytes). Drop this function
// into Code/Libraries/Source/DirtySock/commudp.cpp in place of the 'Convert to
// real C++ separately' note, and change that file's extern "C" prototype to
// int CommUdpProcess(unsigned int tick) (its caller already passes tick).
// GRAFT RECIPE (proven 2026-09-23: compiles+links, all callees resolve): add
// the 7 missing callees to the TU extern "C" block with C linkage exactly as
// Rva007FDA50/Rva007FF720/Rva008186C0/Rva008187E0/Rva00818620/Rva00816F60/
// Rva00818AD0 (C decls match the _Rva rows; C++ decls do NOT resolve). The 3
// globals (g_commUdpRecv/g_commUdpSplit/g_commUdpRefs) need NO pins: DIR32
// slots are copied from retail and consistency-verified. Add the row with
// add_match --no-verify for iteration; REMOVE the row and revert the TU before
// committing anything else (never leave a nonmatching reconstruction in Code/).
// State: the frame (0x44, /GZ guards around fromLength and from[]) and the first
// 0x5A3 bytes match exactly. After the indirect callback at +0x592 retail picks
// ecx where this picks eax for the next statement, and from there 155 of 162
// diffs are pure eax/ecx/edx permutation (the rest are 1-byte jump shifts that
// follow from it). Tried: 3 decrement spellings, 3 call spellings, struct-member
// call, &&/?: guards, /RTC1 /RTCsu /RTCsc, and compiling as C -- no change. With
// /GZ removed the choice is still eax, so the ESP check is not the trigger.
// 2026-09-23 PROBE CAMPAIGN (build/probe_*.cpp+*.py harness, ignored scratch:
// compile_source + read_object_symbol_bytes + capstone; faithful harness proven
// when the full-body probe reproduces the TU's EAX-home exactly): REFUTED as
// flip levers -- expanded-assign/prefix-dec/post-dec-paren/+ -1 decrement forms;
// decl-order perms x10 (slots move but home stays EAX; only same-slot perms are
// TU-viable); empty-else x4 + comma-RMW + do-while-0 + nested-if-first-conjunct;
// init-hoisting x2 + break-to-goto x2 + pre/post-inc x2; uchar-ref dropped as too
// invasive; char-socket + unsigned-count + redundant-char-casts; &&/||
// associativity + not-canonicalization + nested-last-conjunct; __assume/assert
// no-ops. PROVEN: removing the dispatch block flips to ECX (so the trigger is
// dispatch interference in global coloring), as do dropping the compare call,
// the Setup call, or the socket conjunct -- but all change upstream bytes and
// are NOT TU-viable. for-to-while on loop2 flips to ECX but loses the retail
// loop-entry jmp (eb 09) so it breaks the prefix. Sole wall stands: post-call
// ref home ECX (retail) vs EAX (all shapes). Next levers untried: struct-typed
// ref member access (also a readability win), truthiness loop conditions.
//
// 2026-10-07 (claude-opus-5-5, t=75): REWRITTEN STRUCT-TYPED IN ITS HOME TU.
// The body below drops straight into Code/Libraries/Source/DirtySock/
// Y4CommTransportLife.c (C, same TU as CommUdpSetup/CommUdpPoke and the tick
// pump that calls it; place it just before the `// _g_Rva0130AD08Count:` line)
// with two struct edits in struct Rva00816BF0Comm:
//   m_name[0x20] at +0x4C becomes m_name[0x10] followed by
//   int m_dataSent (+0x5C), m_dataRecv (+0x60), m_packSent (+0x64),
//   m_packRecv (+0x68); and m_gap5[0x114] becomes
//   unsigned int m_tickIdle (+0xE0) + m_gap5[0x110].
// Rename the TU's Rva00817B30 prototype/call to CommUdpProcess, and in
// commudp.cpp change `int CommUdpProcess();` to `(unsigned int tick)`; drop
// the _Rva00817B30 pin in reverse/symbols.csv when landing. Same wall: first
// 0x5A3 bytes exact, then retail's next statement starts in ecx, ours in eax
// (188 masked diffs, all rotation). Further REFUTED this session: callback
// return types void/char/short/uchar/__int64/void*/float, unprototyped and
// variadic typedefs, (void) cast, comma, `if (call);` (test is dropped),
// ternary-void guard, base-struct pointer cast of the first argument,
// function-pointer-typed field with and without (*f)(), (*(T*)&field),
// array-indexed and byte-offset call targets, -=/--x/x-- decrements, empty
// else x4, no-op statements after the call x5, truthiness conditions on the
// loops/guards, and compiling the whole TU as C++. Survey of all matched
// DirtySock/GameSpy /GZ bodies: every rotation skip after a call is a call
// whose result is consumed through a pointer store (`p->f = call()`); no
// matched body skips after a discarded result.
struct Rva00816F60Message g_commUdpPacket = { 0 };
struct Rva00816F60Message g_commUdpPiece = { 0 };

int Rva007FDA50( struct Rva007FD4E0Socket *socket, char *buffer, int length,
	int flags, unsigned char *from, int *fromLength );
void CommUdpSetup( struct Rva00816BF0Comm *ref,
	struct Rva00816F60Message *packet, unsigned char *from );
int CommUdpPoke( struct Rva00816BF0Comm *ref );

typedef int ( __cdecl *CommUdpCallbackT )( struct Rva00816BF0Comm *comm,
	int flags );

int CommUdpProcess( unsigned int tick )
{
	int len;
	int iCount;
	struct Rva00816BF0Comm *pRef;
	struct Rva00816BF0Comm *pFind;
	unsigned char sin[ 0x10 ];
	struct Rva007FD4E0Socket *pSock;
	int iSeq;
	int iPieces;
	unsigned int uElapsed;

	iCount = 0;
	pFind = 0;
	memset( sin, 0, sizeof( sin ) );
	g_commUdpPacket.m_length = -1;

	pSock = 0;
	for ( pRef = g_Rva0130B188List; pRef != 0; pRef = pRef->m_next )
	{
		if ( pRef->m_socket != 0 && pRef->m_socket != pSock )
		{
			pSock = pRef->m_socket;
			len = sizeof( sin );
			len = Rva007FDA50( pSock, (char *)&g_commUdpPacket.m_code,
				sizeof( g_commUdpPacket ) - 8, 0, sin, &len );
			if ( len > 0 )
			{
				g_commUdpPacket.m_length = len - 8;
				g_commUdpPacket.m_tick = ( ( ( ( ( sin[ 8 ] << 8 )
					| sin[ 9 ] ) << 8 ) | sin[ 10 ] ) << 8 ) | sin[ 11 ];
				if ( g_commUdpPacket.m_code == 1 )
					Rva007FE780( "CommUdpProcess: got RAW_PACKET_INIT\n" );
				if ( g_commUdpPacket.m_code == 2 )
					Rva007FE780( "CommUdpProcess: got RAW_PACKET_CONN\n" );
				iCount = iCount + 1;
				break;
			}
		}
	}

	for ( pRef = g_Rva0130B188List; pRef != 0; pRef = pRef->m_next )
	{
		tick = Rva007FEA00();

		if ( pFind == 0 && pSock == pRef->m_socket && pRef->m_state == 3
			&& g_commUdpPacket.m_length == 0
			&& g_commUdpPacket.m_code == 1
			&& pRef->m_sessionHash == g_commUdpPacket.m_value )
		{
			pFind = pRef;
		}

		if ( g_commUdpPacket.m_length >= 0 && pRef->m_state != 3
			&& pRef->m_state != 5 && pSock == pRef->m_socket
			&& Rva007FF720( pRef->m_peer, sin ) == 0 )
		{
			pRef->m_dataRecv = pRef->m_dataRecv + g_commUdpPacket.m_length;
			pRef->m_packRecv = pRef->m_packRecv + 1;

			if ( g_commUdpPacket.m_code == 1 || g_commUdpPacket.m_code == 2
				|| g_commUdpPacket.m_code == 3 )
			{
				CommUdpSetup( pRef, &g_commUdpPacket, sin );
			}
			else if ( pRef->m_state != 4 )
			{
				/* data only flows on an open connection */
			}
			else if ( g_commUdpPacket.m_code == 4 )
			{
				pRef->m_tickB = g_commUdpPacket.m_tick;
				Rva008186C0( pRef, &g_commUdpPacket );
			}
			else if ( (unsigned int)g_commUdpPacket.m_code > 0x10000000 )
			{
				iSeq = pRef->m_recvSequence;
				iPieces = (unsigned int)g_commUdpPacket.m_code >> 28;
				g_commUdpPiece.m_tick = g_commUdpPacket.m_tick;
				g_commUdpPiece.m_code = ( g_commUdpPacket.m_code & 0x0FFFFFFF )
					- iPieces;
				g_commUdpPiece.m_value = g_commUdpPacket.m_value;
				pRef->m_tickB = g_commUdpPacket.m_tick;

				for ( ; iPieces >= 0; --iPieces )
				{
					if ( iPieces > 0 )
					{
						--g_commUdpPacket.m_length;
						g_commUdpPiece.m_length = ( (unsigned char *)
							g_commUdpPacket.m_body )[ g_commUdpPacket.m_length ];
					}
					else
					{
						g_commUdpPiece.m_length = g_commUdpPacket.m_length;
					}

					g_commUdpPacket.m_length = g_commUdpPacket.m_length
						- g_commUdpPiece.m_length;
					memcpy( g_commUdpPiece.m_body,
						g_commUdpPacket.m_body + g_commUdpPacket.m_length,
						g_commUdpPiece.m_length );

					Rva008186C0( pRef, &g_commUdpPiece );
					if ( Rva008187E0( pRef, &g_commUdpPiece ) < 0 )
						iPieces = 0;

					if ( iPieces > 0 && iSeq != pRef->m_recvSequence )
						iSeq = pRef->m_recvSequence;

					++g_commUdpPiece.m_code;
				}
			}
			else
			{
				pRef->m_tickB = g_commUdpPacket.m_tick;
				Rva008186C0( pRef, &g_commUdpPacket );
				Rva008187E0( pRef, &g_commUdpPacket );
			}

			g_commUdpPacket.m_length = -1;
		}

		if ( pRef->m_state == 2 && tick - pRef->m_tickA > 1000 )
			Rva00818620( pRef );

		if ( pRef->m_state == 4
			&& pRef->m_sendAckOffset != pRef->m_sendWriteOffset )
		{
			Rva00817640( pRef );
		}

		if ( pRef->m_state == 4 && tick - pRef->m_tickB > 120000
			&& tick - pRef->m_tickA < 2000 )
		{
			Rva007FE780( "CommUDP: closing connection due to timeout\n" );
			Rva007FE780( "CommUDP: tick=%d, rtick=%d, stick=%d\n", tick,
				pRef->m_tickB, pRef->m_tickA );
			Rva00816F60( pRef );
		}

		if ( pRef->m_state == 3 && *(unsigned short *)pRef->m_peer == 2
			&& tick > pRef->m_tickA + 1000 )
		{
			CommUdpPoke( pRef );
		}

		if ( pRef->m_flags == 0 && tick > pRef->m_tickIdle + 250 )
		{
			pRef->m_tickIdle = tick;
			pRef->m_flags = pRef->m_flags | 4;
		}

		if ( pRef->m_depth == 0 && pRef->m_flags != 0 )
		{
			pRef->m_depth = pRef->m_depth + 1;
			if ( pRef->m_value != 0 )
				( (CommUdpCallbackT)pRef->m_value )( pRef, pRef->m_flags );
			pRef->m_depth = pRef->m_depth - 1;
			pRef->m_flags = 0;
			tick = Rva007FEA00();
		}

		if ( pRef->m_state == 4
			&& pRef->m_sendAckOffset == pRef->m_sendWriteOffset )
		{
			uElapsed = tick - pRef->m_tickA;
			if ( ( uElapsed > 100
					&& pRef->m_reportedSequence != pRef->m_recvSequence )
				|| ( uElapsed > 100
					&& pRef->m_sendWriteOffset != pRef->m_sendReadOffset )
				|| uElapsed > 2500 || pRef->m_recvCounter >= 0x800 )
			{
				pRef->m_recvCounter = 0;
				Rva00818AD0( pRef );
			}
		}
	}

	if ( g_commUdpPacket.m_length >= 0 && g_commUdpPacket.m_code == 5
		&& *(unsigned short *)sin == 2 )
	{
		Rva007FE780( "CommUDP: received poke packet (from=%08x)\n",
			( ( ( ( ( sin[ 4 ] << 8 ) | sin[ 5 ] ) << 8 ) | sin[ 6 ] ) << 8 )
			| sin[ 7 ] );

		for ( pRef = g_Rva0130B188List; pRef != 0; pRef = pRef->m_next )
		{
			if ( pRef->m_state == 2 && *(unsigned short *)pRef->m_peer == 2
				&& pRef->m_sessionHash == g_commUdpPacket.m_value )
			{
				Rva007FE780( "CommUdp: poke source = %08x -- forcing match\n",
					( ( ( ( ( (unsigned char)pRef->m_peer[ 4 ] << 8 )
					| (unsigned char)pRef->m_peer[ 5 ] ) << 8 )
					| (unsigned char)pRef->m_peer[ 6 ] ) << 8 )
					| (unsigned char)pRef->m_peer[ 7 ] );

				if ( pSock == pRef->m_socket )
				{
					Rva007FE780( "CommUDP: changing peer to %08x:%d due to poke "
						"(was expecting %08x:%d)\n",
						( ( ( ( ( sin[ 4 ] << 8 ) | sin[ 5 ] ) << 8 )
						| sin[ 6 ] ) << 8 ) | sin[ 7 ],
						( sin[ 2 ] << 8 ) | sin[ 3 ],
						( ( ( ( ( (unsigned char)pRef->m_peer[ 4 ] << 8 )
						| (unsigned char)pRef->m_peer[ 5 ] ) << 8 )
						| (unsigned char)pRef->m_peer[ 6 ] ) << 8 )
						| (unsigned char)pRef->m_peer[ 7 ],
						( (unsigned char)pRef->m_peer[ 2 ] << 8 )
						| (unsigned char)pRef->m_peer[ 3 ] );
					memcpy( pRef->m_peer, sin, sizeof( sin ) );
					break;
				}
			}
		}
	}

	if ( pFind != 0 && g_commUdpPacket.m_length == 0 )
	{
		pRef = pFind;
		if ( pRef->m_sessionHash == g_commUdpPacket.m_value )
		{
			memcpy( pRef->m_peer, sin, sizeof( sin ) );
			pRef->m_state = 4;
			CommUdpSetup( pRef, &g_commUdpPacket, sin );
		}
	}

	return iCount;
}

