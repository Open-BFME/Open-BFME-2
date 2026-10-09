// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?reset@ConnectionManager@@UAEXXZ, retail 0x004D0669, 428 bytes.
//
// Reference: Zero Hour ConnectionManager::reset (delete the transport,
// the connections and the per-slot frame data; create the pending, relayed
// and wrapper lists on first use and reset them; local slot and packet
// router slot back to -1; router fallback list cleared to -1).
// BFME 2 differences read from this body: the transport pointer is at +0x12024
// and is deleted through its rowed destructor 0x004494BA, the eight
// connections at +4 through 0x004D060B, the frame data at +0x12104 through
// their virtual destructor; both command lists are 0x10-byte objects built by
// 0x0058B06A and reset by 0x0058B283 (which is also the init target), the
// wrapper list is 8 bytes (0x0058C0AE, reset 0x0058C0F0, cleared first by the
// folded dword clearer 0x0055059A). The FPS/latency history loops are
// replaced by five per-slot int arrays (+0x12060/+0x12080/+0x120A0/+0x120C0/
// +0x120E0, the third reset to 1) plus the frame ceiling +0x1205C, and the
// reset ends with the timer words at +0x12130/+0x12134/+0x12135.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#include "../../Include/GameNetwork/Transport.h"

void __cdecl operator delete(void *block);
void *__cdecl operator new(UnsignedInt size);


// The connection, held in the ledger under its destructor's address name.
class Rva004D060B
{
public:
	~Rva004D060B();
};

// Vtable slot 0 is the scalar deleting destructor: flag 0 destroys without
// freeing and hands back the object, which the caller then frees.
class FrameDataManager
{
public:
	virtual void *destroy(UnsignedInt flags);
};

class NetCommandList
{
public:
	NetCommandList();
	void init();
	void reset();

private:
	char m_data[0x10];
};

class NetCommandWrapperList
{
public:
	NetCommandWrapperList();
	void reset();

private:
	char m_data[8];
};

// The folded dword clearer 0x0055059A, NetCommandWrapperList::init's target.
class Rva0055059ADwordClearer
{
public:
	void clear();
};

class ConnectionManager
{
public:
	virtual void slot0();
	virtual void reset();

private:
	Rva004D060B *m_connections[8];			// +0x04
	char m_pad024[0x12024 - 0x24];
	Transport *m_transport;					// +0x12024
	Int m_localSlot;						// +0x12028
	Int m_packetRouterSlot;					// +0x1202C
	Int m_packetRouterFallback[8];			// +0x12030
	char m_pad12050[0x1205C - 0x12050];
	UnsignedInt m_frameCeiling;				// +0x1205C
	Int m_playerLatestFrame[8];				// +0x12060
	Int m_slotWords12080[8];				// +0x12080
	Int m_slotWords120A0[8];				// +0x120A0
	Int m_playerClientFrame[8];				// +0x120C0
	Int m_slotWords120E0[8];				// +0x120E0
	char m_pad12100[0x12104 - 0x12100];
	FrameDataManager *m_frameData[8];		// +0x12104
	NetCommandList *m_pendingCommands;		// +0x12124
	NetCommandList *m_relayedCommands;		// +0x12128
	NetCommandWrapperList *m_netCommandWrapperList;	// +0x1212C
	UnsignedInt m_timerStamp;				// +0x12130
	Bool m_flag12134;
	Bool m_flag12135;
};

void ConnectionManager::reset()
{
	if (m_transport != 0) {
		delete m_transport;
		m_transport = 0;
	}

	Int i;
	for (i = 0; i < 8; ++i) {
		if (m_connections[i] != 0) {
			delete m_connections[i];
			m_connections[i] = 0;
		}
	}

	for (i = 0; i < 8; ++i) {
		if (m_frameData[i] != 0) {
			operator delete(m_frameData[i]->destroy(0));
			m_frameData[i] = 0;
		}
	}

	if (m_pendingCommands == 0) {
		m_pendingCommands = new NetCommandList;
		m_pendingCommands->init();
	}
	m_pendingCommands->reset();

	if (m_relayedCommands == 0) {
		m_relayedCommands = new NetCommandList;
		m_relayedCommands->init();
	}
	m_relayedCommands->reset();

	if (m_netCommandWrapperList == 0) {
		m_netCommandWrapperList = new NetCommandWrapperList;
		((Rva0055059ADwordClearer *)m_netCommandWrapperList)->clear();
	}
	m_netCommandWrapperList->reset();

	m_localSlot = -1;
	m_packetRouterSlot = -1;
	m_frameCeiling = 0;
	for (i = 0; i < 8; ++i) {
		m_packetRouterFallback[i] = -1;
		m_playerLatestFrame[i] = 0;
		m_playerClientFrame[i] = 0;
		m_slotWords120E0[i] = 0;
		m_slotWords12080[i] = 0;
		m_slotWords120A0[i] = 1;
	}
	m_timerStamp = 0;
	m_flag12134 = false;
	m_flag12135 = true;
}
