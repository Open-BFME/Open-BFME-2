// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// BFME2 network Transport helpers. The class is a BFME2 rewrite of the
// Zero Hour / BFME1 Transport: the message rings still sit at +0x00000 and
// +0x20700 with stride 0x40E, but the tail is reworked around an 8-slot
// table (cleared one slot at a time through the word-indexed slot clearer
// at 0x4D5133) and a winsock-active byte flag at +0x40E08.
// The winsock init (0x004D53B5) and slot setter (0x004D51A7) were folded in
// from split units with these exact flags. The constructor keeps its own
// unit: it builds the slot array against an out-of-line element destructor.

extern "C" {
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAStartup(unsigned short wVersionRequired, void *lpWSAData);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
}

struct WSAData40E
{
	unsigned char m_versionLow;
	unsigned char m_versionHigh;
	char m_pad[0x190 - 2];
};

struct SlotVals
{
	int x;
	int y;
};

#define NULL 0

// ?clearBuffer_Rva004D4A59@Transport@@QAEXXZ present-unmatched
// (declared-only; resolves through the pin at 0x004D4A59)

// Zero Hour's UDP socket wrapper; AllowBroadcasts is rowed at 0x00594B2E.
struct sockaddr_in
{
    short m_family;
    unsigned short m_port;
    unsigned long m_addr;
    char m_zero[8];
};

// ABI-only declaration of the existing receiver provider at 0x005952C4.
// No receiver fields, size or original class identity are inferred here.
// Existing address-owned send provider; only its witnessed ABI is used.
class Rva00594C12
{
public:
    int rva00594C12(const char *, int, unsigned long, unsigned short);
};

class Rva00594DC0
{
public:
    bool rva005952C4(void *, unsigned short, unsigned short *);
};

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
unsigned int ComputeCRC(const unsigned char *, unsigned int, unsigned int);

class UDP
{
public:
	int AllowBroadcasts(bool status);
	int Read(unsigned char *, unsigned int, sockaddr_in *);
};

#include "../../Include/GameNetwork/Transport.h"

// Matched slot constructor at 0x004D4A80: zero the pointer, int and short,
// leaving the two padding bytes untouched.
Rva004D4A80Slot::Rva004D4A80Slot(void)
{
	m_object = NULL;
	m_x = 0;
	m_y = 0;
}

// ?Rva004D5496@Transport@@QAEXXZ
// retail 0x004D5496, 43 bytes. Clears the 8 transport slots, then shuts
// down winsock if the active flag is set.
void Transport::Rva004D5496(void)
{
	for (int i = 0; i < 8; ++i)
		RemoveSocketForSlot((unsigned short)i);
	if (m_winsockActive) {
		WSACleanup();
		m_winsockActive = false;
	}
}

// ??0Transport@@QAE@XZ
// retail 0x004D4AF2, 153 bytes.
// Transport::Transport: defined in TransportCtor.cpp (its row's unit).

// ??1Transport@@QAE@XZ
// retail 0x004494BA, 64 bytes. Runs the slot clearer, then the eight
// slot destructors run through the vector destructor iterator.
Transport::~Transport(void)
{
	Rva004D5496();
}

// Transport::allowBroadcasts, retail 0x004D5112 (33 bytes): Zero Hour's body
// under WB's name (Transport.cpp). The UDP socket is the first slot's object;
// retail folds the two tests into one && (xor/inc for the true arm).
bool Transport::allowBroadcasts(bool allowBroadcasts)
{
	UDP *udpsock = (UDP *)m_slots[0].m_object;
	return udpsock != NULL && udpsock->AllowBroadcasts(allowBroadcasts) != 0;
}

// ?setSlotSocket@Transport@@QAEXPAXGPAH@Z @0x004D51A7 70B: Transport slot setter
// at +0x40E0C. When index < 8 clears the slot via rowed clearSlot then
// stores object and two ints. Evidence: retail cmp word 8 jae plus call
// 0x004D5133 plus dual imul 0xC plus stores at +0x40E0C/+0x40E10/+0x40E14;
// ret 0xC proves 3 args; caller at 0x005A6E62.
void Transport::setSlotSocket(void *obj, unsigned short index, int *vals)
{
	if (index >= 8)
		return;
	RemoveSocketForSlot(index);
	m_slots[index].m_object = obj;
	*(SlotVals *)&m_slots[index].m_x = *(SlotVals *)vals;
}

// ?rva004D53B5@Transport@@QAE_NPAX@Z @0x004D53B5 225B: Transport winsock init plus buffer clear.
// Target evidence: WSAStartup IAT 0x00BBA96C plus WSACleanup 0x00BBA970 plus
// timeGetTime 0x00BBA918 plus clearSlot 0x004D5133 plus offsets
// +0x40E00/+0x40E04/+0x40E08/+0x40E6C/+0x40E70 plus ret 4; caller 0x005A6B28.
bool Transport::rva004D53B5(void *addr)
{
	if (!m_winsockActive)
	{
		unsigned short verReq = 0x202;
		WSAData40E wsadata;
		int err = WSAStartup(verReq, &wsadata);
		if (err != 0)
			return false;
		if (wsadata.m_versionLow != 2 || wsadata.m_versionHigh != 2)
		{
			WSACleanup();
			return false;
		}
		m_winsockActive = true;
	}
	m_flag40E00 = false;
	m_ptr40E04 = addr;
	for (int i = 0; i < 8; ++i)
		RemoveSocketForSlot((unsigned short)i);
	for (int i = 0; i < 128; ++i)
	{
		m_outBuffer[i].m_length = 0;
		m_inBuffer[i].m_length = 0;
	}
	for (int i = 0; i < 30; ++i)
	{
		m_stats0[i] = 0;
		m_stats2[i] = 0;
		m_stats1[i] = 0;
		m_stats3[i] = 0;
		m_stats5[i] = 0;
		m_stats4[i] = 0;
		m_badPackets = 0;
	}
	m_int40E6C = 0;
	m_int40E70 = (int)timeGetTime();
	return true;
}

// WB Transport::setDestAddrToSocket, complete native 004D51ED..004D5219.
// CMP word [esp+4],8 and MOVZX consume only the low 16 index bits.
// The address consists of two copied dwords; original parameter typedefs
// are not asserted by this ABI view. Both NAT callers pass a full word.
void Transport::setDestAddrToSocket(int index, void *address)
{
	unsigned short slot = (unsigned short)index;
	if (slot >= 8)
		return;
	*(SlotVals *)&m_slots[slot].m_x = *(SlotVals *)address;
}

// Primary semantic lead: BFME 1 Transport.cpp at 9cbfb551fe20.
// Target-specific eight slots and optional receiver are witnessed by WB
// Transport::doRecv and native [004D4D08,004D4EC6), including RET4.
static inline void decryptTransportMessage(unsigned char *buf, int len)
{
    unsigned int mask = 0x38D9B7D4;
    unsigned int *words = (unsigned int *)buf;
    for (int i = 0; i < len / 4; ++i) {
        *words = htonl(*words);
        *words ^= mask;
        ++words;
        mask -= 0x7F39C50E;
    }
}

bool Transport::doRecv(Rva00594DC0 *receiver)
{
    int i;
    for (i = 0; i < 8; ++i)
        if (m_slots[i].m_object)
            break;
    if (i == 8)
        return false;

    bool retval = false;
    sockaddr_in from;
    Message incomingMessage;
    Rva004D4A80Slot *slot = m_slots;
    int remaining = 8;
    do {
        if (slot->m_object) {
            int len;
            while ((len = ((UDP *)slot->m_object)->Read((unsigned char *)&incomingMessage,
                                      sizeof(Message), &from)) > 0) {
                unsigned short receiverResult;
                if (receiver && receiver->rva005952C4(&incomingMessage,
                                      (unsigned short)len, &receiverResult))
                    continue;
                decryptTransportMessage((unsigned char *)&incomingMessage, len);
                incomingMessage.m_addr = htonl(from.m_addr);
                incomingMessage.m_port = htons(from.m_port);
                unsigned int msgLen = len - 4;
                incomingMessage.m_length = msgLen;
                if (msgLen <= 0 || msgLen > 0x400 ||
                    incomingMessage.m_crc != ComputeCRC(incomingMessage.m_data, msgLen, 0)) {
                    ++m_badPackets;
                    ++m_stats4[m_int40E6C];
                    m_stats1[m_int40E6C] += len;
                    continue;
                }
                ++m_stats3[m_int40E6C];
                m_stats0[m_int40E6C] += len;
                for (int j = 0; j < 128; ++j) {
                    if (m_inBuffer[j].m_length == 0) {
                        memcpy(&m_inBuffer[j], &incomingMessage, sizeof(Message));
                        retval = true;
                        break;
                    }
                }
            }
        }
        ++slot;
    } while (--remaining);
    return retval;
}

// BF1 Transport.cpp rev9cbfb551fe20 supplies queue/statistics semantics.
// WB Transport::doSend and native [004D4BA7,004D4D08) supply the eight-slot
// selection and clear-on-missing-destination behavior.
bool Transport::doSend()
{
    int i;
    for (i = 0; i < 8; ++i)
        if (m_slots[i].m_object)
            break;
    if (i == 8)
        return false;

    unsigned int now = timeGetTime();
    if ((unsigned int)m_int40E70 + 1000 < now) {
        m_int40E70 = now;
        m_int40E6C = (m_int40E6C + 1) % 30;
        m_stats5[m_int40E6C] = 0;
        m_stats2[m_int40E6C] = 0;
        m_stats3[m_int40E6C] = 0;
        m_stats0[m_int40E6C] = 0;
        m_stats4[m_int40E6C] = 0;
        m_stats1[m_int40E6C] = 0;
    }
    // A cursor over the witnessed packed message trailer: length, IPv4, port.
    struct MessageTail {
        int m_length;
        unsigned long m_addr;
        unsigned short m_port;
    };
    bool retval = true;
    char *cursor = (char *)&m_outBuffer[0].m_length;
    for (int n = 0; n < 128; ++n, cursor += sizeof(Message)) {
        MessageTail &message = *(MessageTail *)cursor;
        if (message.m_length != 0) {
            Rva00594C12 *socket;
            if (m_flag40E00) {
                socket = (Rva00594C12 *)m_slots[0].m_object;
            } else {
                socket = 0;
                for (int j = 0; j < 8; ++j) {
                    if (m_slots[j].m_object &&
                        (unsigned long)m_slots[j].m_x == message.m_addr &&
                        (unsigned short)m_slots[j].m_y == message.m_port) {
                        socket = (Rva00594C12 *)m_slots[j].m_object;
                        break;
                    }
                }
            }
            if (!socket) {
                message.m_length = 0;
                continue;
            }
            if (socket->rva00594C12(cursor - sizeof(m_outBuffer[0].m_crc) - sizeof(m_outBuffer[0].m_data),
                       message.m_length + 4, message.m_addr, message.m_port) > 0) {
                ++m_stats5[m_int40E6C];
                m_stats2[m_int40E6C] += message.m_length + 4;
                message.m_length = 0;
            } else {
                retval = false;
            }
        }
    }
    return retval;
}
