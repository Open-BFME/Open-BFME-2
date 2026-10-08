// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameNetwork/Transport_queueSend.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?queueSend@Transport@@QAE_NPAUNetPacketAddress@@PBEH@Z 0x004D4EC6 (180B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// Transport::queueSend, 0x00683830, 164 bytes, and the pass it runs over every
// outgoing message.
//
// Both live here together because the second one is a file-static that retail
// calls with the message in ecx and the byte count in eax -- neither a thiscall
// nor a fastcall, but MSVC's custom calling convention for a static function
// whose call sites it can all see. That only happens if the two are compiled in
// the same translation unit.
//
// The pass itself is BFME's own; the reference sends the packet as-is. Each
// dword is XORed with a key that starts at 0x38D9B7D4 and walks by subtracting
// 0x7F39C50E, then byte-swapped. It covers the CRC as well as the payload --
// hence the length plus four.
//
// The message layout the loop stride pins is packed: 0x40E bytes per entry, so
// the trailing UnsignedShort port is not padded out to a dword.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0
#define TRUE 1
#define FALSE 0

enum { MAX_PACKET_SIZE = 0x1DC };
enum { MAX_MESSAGES = 0x80 };

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long netlong);

UnsignedInt ComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc);

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

static void obfuscate(void *msg, Int numBytes)
{
	UnsignedInt key = 0x38D9B7D4;
	UnsignedInt *p = (UnsignedInt *)msg;
	Int count = numBytes / 4;

	for (Int i = 0; i < count; ++i) {
		*p ^= key;
		*p = htonl(*p);
		++p;
		key -= 0x7F39C50E;
	}
}

#include "../../Include/GameNetwork/Transport.h"

Bool Transport::queueSend(NetPacketAddress *addr, const UnsignedByte *data, Int len)
{
	if ((data == NULL) || ((UnsignedInt)len > MAX_PACKET_SIZE)) {
		return FALSE;
	}

	Int i = 0;
	do {
		if (m_outBuffer[i].m_length == 0) {
			goto found;
		}

		++i;
	} while (i < MAX_MESSAGES);

	return FALSE;

found:

	UnsignedInt crc = ComputeCRC(data, len, 0);

	m_outBuffer[i].m_addr = addr->ip;
	m_outBuffer[i].m_port = addr->port;
	m_outBuffer[i].m_length = len;
	memcpy(m_outBuffer[i].m_data, data, len);
	m_outBuffer[i].m_crc = crc;

	obfuscate(&m_outBuffer[i], len + 4);

	return TRUE;
}

// Uses the shared byte-verified Transport layout. The obfuscation helper
// consumes the serialized word buffer; it does not need a private message view.
