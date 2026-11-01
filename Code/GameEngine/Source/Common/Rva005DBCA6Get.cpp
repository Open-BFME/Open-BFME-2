// cl: /DNDEBUG /MD
// PortNegotiationSchema::getActionID (WorldBuilder name, PortNegotiationSchema.cpp line 421: the +0x118 action table lookup).
// was ?rva005DBCA6@Rva005DBCA6@@QAEHGG@Z 0x005DBCA6 43B
// Bounds-checked 2D dword lookup at +0x118 (8x8).
// Evidence: callers 0x5A6FD4 0x5A80B4 0x5A81EA 0x5A820E; same shape as Rva005DB9BC 2D dword.
#include "../../Include/GameNetwork/GameInfo.h"

class PortNegotiationSchema
{
	char m_pad[0x18];
	int m_state[64];	// +0x018
	int m_arr[64];		// +0x118
	char m_pad218[0x838 - 0x218];
	unsigned short m_retries[64];	// +0x838
	GameSlot **m_slots;	// +0x8B8
public:
	int getActionID(unsigned short x, unsigned short y);
	bool isConnectionDone(unsigned short first, unsigned short second);
	bool isRetryConnectingOverLimit(unsigned short first, unsigned short second);
};

int PortNegotiationSchema::getActionID(unsigned short x, unsigned short y)
{
	if (x < 8)
	{
		if (y < 8)
			return m_arr[y + x * 8];
	}
	return 0;
}

// PortNegotiationSchema::isConnectionDone (WorldBuilder name, assert line
// 387), retail 0x005DBBC1..0x005DBC2E (109 bytes): for two distinct slots in
// range, done unless both are human with a state (+0x18 table) other than 3.
// Retail saves EBX/ESI only after the first bound test: that test returns on
// its own and the rest is its else scope, as in WB's per-bound returns.
bool PortNegotiationSchema::isConnectionDone(unsigned short first, unsigned short second)
{
	if (first >= 8)
		return false;
	else
	{
		if (second >= 8)
			return false;
		if (first != second &&
			(!m_slots[first] || !m_slots[first]->isHuman() || !m_slots[second] || !m_slots[second]->isHuman() ||
			 m_state[second + first * 8] == 3))
			return true;
		return false;
	}
}

// PortNegotiationSchema::isRetryConnectingOverLimit (WorldBuilder name),
// retail 0x005DBC2E..0x005DBCA6 (120 bytes): between two human slots, state 4
// with at least five retries (+0x838). Scoped as isConnectionDone, but here
// the distinctness test comes before the EBX/EDI saves.
bool PortNegotiationSchema::isRetryConnectingOverLimit(unsigned short first, unsigned short second)
{
	if (first >= 8)
		return false;
	else
	{
		if (second >= 8)
			return false;
		if (first == second)
			return false;
		if (m_slots[first] && m_slots[first]->isHuman() && m_slots[second] && m_slots[second]->isHuman() &&
			m_state[second + first * 8] == 4 && m_retries[second + first * 8] >= 5)
			return true;
		return false;
	}
}
