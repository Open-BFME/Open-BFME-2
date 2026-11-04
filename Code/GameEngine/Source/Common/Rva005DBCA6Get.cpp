// cl: /DNDEBUG /MD
// PortNegotiationSchema::getActionID (WorldBuilder name, PortNegotiationSchema.cpp line 421: the +0x118 action table lookup).
// was ?rva005DBCA6@Rva005DBCA6@@QAEHGG@Z 0x005DBCA6 43B
// Bounds-checked 2D dword lookup at +0x118 (8x8).
// Evidence: callers 0x5A6FD4 0x5A80B4 0x5A81EA 0x5A820E; same shape as Rva005DB9BC 2D dword.
#include "../../Include/GameNetwork/GameInfo.h"

class GameSlot;

struct Elem005DB98E
{
public:
	void rva005DB885(int a);
	void rva005DB8F7(float a, float b, float c);
	int m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	float m_0C; // +0x0C
	unsigned long m_10; // +0x10
};

class Rva005DBE6AListener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva005DBDF7Call
{
	void (Rva005DBE6AListener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva005DBE6AList
{
public:
	void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva005DBDF7Call &call);
private:
	Rva005DBE6AListener **m_begin; // +0x00
	Rva005DBE6AListener **m_end; // +0x04
	Rva005DBE6AListener **m_capacity; // +0x08
	unsigned int m_index; // +0x0C
};

class PortNegotiationSchema
{
public:
	void* peekPing(unsigned short x, unsigned short y);
	int GetConnectionState(unsigned short x, unsigned short y);
	bool IsConflictingWithProceedingNegotiation(unsigned short x);
	bool rva005DBA9C(bool flag);
	int getTimeToSendPing(unsigned short idx);
	int getActionID(unsigned short x, unsigned short y);
	bool isConnectionDone(unsigned short first, unsigned short second);
	bool isRetryConnectingOverLimit(unsigned short first, unsigned short second);
	bool receivedAPong(unsigned short x, unsigned short y, int a);
	bool setPingStats(unsigned short x, unsigned short y, float a, float m_pingsSent, float pongsReceived);
	bool sentAPingPacket(unsigned short x, unsigned short y);
	void handleNegotiationResult(unsigned short a, unsigned short b, int expected, int newVal);
	char m_pad00[0x4];
private:
	Rva005DBE6AList m_list; // +0x04
	unsigned short m_cur; // +0x14
	char m_pad16[0x2];
	int m_arr2[64]; // +0x18
	int m_arr118[64]; // +0x118
	Elem005DB98E m_arr[64]; // +0x218
	int m_718[8]; // +0x718
	char m_pad738[0x100];
	unsigned short m_retries[64]; // +0x838
	GameSlot **m_slots; // +0x8B8
};

int PortNegotiationSchema::getActionID(unsigned short x, unsigned short y)
{
	if (x < 8)
	{
		if (y < 8)
			return m_arr118[y + x * 8];
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
			 m_arr2[second + first * 8] == 3))
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
			m_arr2[second + first * 8] == 4 && m_retries[second + first * 8] >= 5)
			return true;
		return false;
	}
}
