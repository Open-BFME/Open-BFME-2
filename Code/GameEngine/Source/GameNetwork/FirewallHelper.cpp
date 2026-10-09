// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 FirewallHelperClass empty-message scan, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameNetwork/FirewallHelper.cpp).
// Retail BFME2 keeps the same table: 8 packed 0x1E-byte entries at +0x8A with
// the length field at entry+0x14. The packing matches the Zero Hour donor
// (reference/.../GameEngine/Include/GameNetwork/FirewallHelper.h): despite
// its stale "size = 16 bytes" comment, the packed ManglerData is 20 bytes,
// so the packed message is 30 bytes and the stride falls out naturally.
// The spare-socket search (0x00594D77) was folded in from a split unit with
// these exact flags; its spareSockets[8] table sits at +0x14.

#pragma pack(push, 1)

struct ManglerData
{
	unsigned int m_crc;
	unsigned short m_magic;
	unsigned short m_packetID;
	unsigned short m_mangledPortNumber;
	unsigned short m_originalPortNumber;
	unsigned char m_mangledAddress[4];
	unsigned char m_netCommandType;
	unsigned char m_blitzMe;
	unsigned short m_padding;
};

struct ManglerMessage
{
	ManglerData m_data;	// 20 bytes
	int m_length;		// +0x14
	unsigned int m_ip;
	unsigned short m_port;
};	// 30 bytes packed

#pragma pack(pop)

struct SpareEntry
{
	void *udp;
	unsigned short port;
	char _pad[2];
};

class FirewallHelperClass
{
public:
	void *rva00594D77(unsigned short port);
	void rva00594EEF();
	unsigned char rva00594F0C();

private:
	ManglerMessage *findEmptyMessage();

private:
	char _pad00[4];
	unsigned int m_behavior; // +4: native detection updates use this word
	char _pad08[0x0C];
	SpareEntry m_spare[8];			// +0x14
	unsigned char m_pad54[0x8A - 0x54];
	ManglerMessage m_messages[8];	// +0x8A
	unsigned int m_currentState; // +0x17C after natural two-byte padding
};

// ?findEmptyMessage@FirewallHelperClass@@AAEPAUManglerMessage@@XZ
ManglerMessage *FirewallHelperClass::findEmptyMessage()
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_messages[i].m_length == 0)
		{
			return &(m_messages[i]);
		}
	}
	return 0;
}

// ?rva00594D77@FirewallHelperClass@@QAEPAXG@Z @0x00594D77 (37B): search
// spareSockets[8] at +0x14 by port at +0x18 stride 8; return entry or 0;
// layout from Rva00594CDDPermuted ctor; neighbours FirewallHelperClass ctor
// and findEmptyMessage.
void *FirewallHelperClass::rva00594D77(unsigned short port)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_spare[i].port == port)
			return &m_spare[i];
	}
	return 0;
}

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 FirewallHelper.cpp
// detectFirewallBehavior supplies the two-state-store expression. Target
// 594EEF..594EFC is independently RET-bounded: write 1 at +4 and +17C.
// The rowed same-class detection updates independently establish the fields;
// the original operation spelling is not established by a direct caller.
void FirewallHelperClass::rva00594EEF()
{
	m_behavior = 1;
	m_currentState = 1;
}

// BF1 detectionTest5Update is the source guide. Complete target
// 594F0C..594F19 follows the separate word getter's RET and ends RET:
// write 9 at +17C and return raw AL=1. The target's original operation
// spelling and whether its byte result was declared bool remain unresolved.
unsigned char FirewallHelperClass::rva00594F0C()
{
	m_currentState = 9;
	return 1;
}

// BFME2 native NAT port allocation helper at 594F19, 263B.
// ZH FirewallHelper::getNATPortAllocationScheme is the semantic donor at BFME1
// pointer 9cbfb551fe20dae985f91f2319d8997287b6a705; native target omits sorting
// and adds Int relativeDelta mode2. Caller FirewallHelperDetection confirms
// the existing address-derived receiver and five-argument ABI.
// Completes the banked 2026-10-04 partial. The guarded pointer walk retains
// retail loop scheduling while preserving the donor port-offset calculation.
typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define TRUE true
#define FALSE false
#define NUM_TEST_PORTS 4
class Rva00594F19 {
public:
    Int rva00594F19(Int, UnsignedShort *, UnsignedShort *, Int &, Bool &);
};

Int Rva00594F19::rva00594F19(Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts, Int &relativeDelta, Bool &looksGood)
{
	Int diff1 = mangledPorts[1] - mangledPorts[0];
	Int diff2 = mangledPorts[2] - mangledPorts[1];
	Int diff3 = mangledPorts[3] - mangledPorts[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = 0;
		looksGood = TRUE;
		return(diff1);
	}

	if (diff1 == diff2) {
		relativeDelta = 0;
		looksGood = FALSE;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = 0;
		looksGood = FALSE;
		return(diff2);
	}

	/*
	** See if the mangled ports keep a constant offset from the source ports.
	*/
	Int deltas[NUM_TEST_PORTS];
	Int i = 0;
	if (i < numPorts) {
		UnsignedShort *source = originalPorts;
		UnsignedShort *mapped = mangledPorts;
		for (; i<numPorts ; i++, source++, mapped++) {
			deltas[i] = *mapped - *source;
		}
	}

	diff1 = deltas[1] - deltas[0];
	diff2 = deltas[2] - deltas[1];
	diff3 = deltas[3] - deltas[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = 1;
		looksGood = TRUE;
		return(diff1);
	}

	if (diff1 == diff2 || diff1 == diff3) {
		relativeDelta = 1;
		looksGood = FALSE;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = 1;
		looksGood = FALSE;
		return(diff2);
	}

	/*
	** BFME 2: the mangled ports' deltas themselves grow by a constant step.
	*/
	diff1 = mangledPorts[1] - mangledPorts[0];
	diff2 = mangledPorts[2] - mangledPorts[1];
	diff3 = mangledPorts[3] - mangledPorts[2];
	if (diff2 - diff1 == diff3 - diff2) {
		relativeDelta = 2;
		looksGood = TRUE;
		return(diff1);
	}

	looksGood = FALSE;
	relativeDelta = 0;
	return(0);
}

