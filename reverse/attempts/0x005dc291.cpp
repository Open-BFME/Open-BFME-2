// ?playerJoin@PortNegotiationSchema@@QAEXG@Z
// partial score=0.65 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE
// PortNegotiationSchema.cpp -- schema members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. A valid slot (below 8) first resets the schema
// (0x005DB9E4, unnamed), then records the slot list at +0x8B8 and the slot
// at +0x14.

typedef unsigned short UnsignedShort;
typedef int Int;

enum { MAX_PORT_SLOTS = 8 };

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern unsigned int g_Va00DD35D0;
class Rva005DBE6AListener { public: virtual void notify(void *, int, int); };
class Rva00281A15Listener { public: virtual void notify(); };
class Rva005DBE6AList {
public:
    void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *, int, int);
private:
    void *begin, *end, *capacity;
    unsigned int index;
};
struct Rva005DB86EPingStats {
    int prefix;
    float sampleA, sampleB, sampleC;
    int count;
    void reset() { count = 0; sampleA = 0.0f; sampleB = 0.0f; sampleC = 0.0f; }
};

class GameSlot { public: bool isHuman() const; };

class PortNegotiationSchema
{
public:
	void attachSlotList(void *slotList, UnsignedShort slot);
	void negotiationStarted(UnsignedShort slot1, UnsignedShort slot2, int value, bool setTimeout);
	void reconnectPlayers(UnsignedShort slot1, UnsignedShort slot2, bool resetRetries);
	void playerJoin(UnsignedShort slot);

private:
	void rva005DB9E4();			// 0x005DB9E4

	unsigned int m_unknown;
	Rva005DBE6AList m_list;
	UnsignedShort m_slot;			// +0x014
	unsigned char m_pad016[2];
	Int m_tableA[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x018
	Int m_tableB[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x118
	Rva005DB86EPingStats m_ping[MAX_PORT_SLOTS][MAX_PORT_SLOTS];
	Int m_perSlot[MAX_PORT_SLOTS];		// +0x718
	Int m_tableC[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x738
	UnsignedShort m_tableD[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x838
	void *m_slotList;			// +0x8B8
};

// Retail 0x005DB9E4: clear the schema.
void PortNegotiationSchema::rva005DB9E4()
{
	for (Int i = 0; i < MAX_PORT_SLOTS; ++i)
	{
		for (Int j = 0; j < MAX_PORT_SLOTS; ++j)
		{
			m_tableA[i][j] = 0;
			m_tableB[i][j] = 0;
			m_tableC[i][j] = 0;
			m_tableD[i][j] = 0;
		}
		m_perSlot[i] = 0;
	}
	m_slotList = 0;
	m_slot = MAX_PORT_SLOTS;
}

// PortNegotiationSchema::attachSlotList, retail 0x005DBA3D.
void PortNegotiationSchema::attachSlotList(void *slotList, UnsignedShort slot)
{
	if (slot < 8)
	{
		rva005DB9E4();
		m_slotList = slotList;
		m_slot = slot;
	}
}

// WB15C6B80, PortNegotiationSchema.cpp:182; target5DBF8C..5DC070.
// Starts both directed negotiations, optionally sets the reverse timeout,
// counts retries, resets ping statistics and notifies the listener list.
void PortNegotiationSchema::negotiationStarted(UnsignedShort slot1,
    UnsignedShort slot2, int value, bool setTimeout)
{
    if (slot1 >= 8 || slot2 >= 8 || slot1 == slot2) return;
    m_tableA[slot2][slot1] = 2;
    m_tableA[slot1][slot2] = 2;
    m_tableB[slot2][slot1] = value;
    m_tableB[slot1][slot2] = value;
    if (setTimeout) m_tableC[slot2][slot1] = timeGetTime() + (g_Va00DD35D0 * 3 >> 1);
    ++m_tableD[slot1][slot2];
    ++m_tableD[slot2][slot1];
    m_ping[slot1][slot2].reset();
    m_ping[slot2][slot1].reset();
    m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva00281A15Listener::notify,
        this, slot1, slot2);
}

// WB15C70A0: reconnect both directions and notify each directed pair.
void PortNegotiationSchema::reconnectPlayers(UnsignedShort slot1,
    UnsignedShort slot2, bool resetRetries)
{
    if (slot1 >= 8 || slot2 >= 8 || slot1 == slot2) return;
    m_tableA[slot2][slot1] = 1;
    m_tableA[slot1][slot2] = 1;
    m_tableB[slot2][slot1] = 0;
    m_tableB[slot1][slot2] = 0;
    m_tableC[slot2][slot1] = -1;
    m_tableC[slot1][slot2] = -1;
    m_ping[slot1][slot2].reset();
    m_ping[slot2][slot1].reset();
    if (slot1 == m_slot) m_perSlot[slot2] = 0;
    if (slot2 == m_slot) m_perSlot[slot1] = 0;
    if (resetRetries) {
        m_tableD[slot2][slot1] = 0;
        m_tableD[slot1][slot2] = 0;
    }
    m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva00281A15Listener::notify,
        this, slot1, slot2);
    m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva00281A15Listener::notify,
        this, slot2, slot1);
}

// WB15C72E0: start peer negotiations for human slots; clear other peers.
void PortNegotiationSchema::playerJoin(UnsignedShort slot)
{
    if (slot >= 8) return;
    for (int i = 0; i < MAX_PORT_SLOTS; ++i) {
        if (i == slot) continue;
        if (((GameSlot **)m_slotList)[i] && ((GameSlot **)m_slotList)[i]->isHuman()) {
            m_tableA[i][slot] = 1;
            m_tableA[slot][i] = 1;
            m_tableC[i][slot] = -1;
            m_tableC[slot][i] = -1;
            m_ping[slot][i].reset();
            m_ping[i][slot].reset();
            m_tableB[i][slot] = 0;
            m_tableB[slot][i] = 0;
            m_tableD[i][slot] = 0;
            m_tableD[slot][i] = 0;
        } else {
            m_tableA[i][slot] = 0;
            m_tableA[slot][i] = 0;
        }
        m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva00281A15Listener::notify,
            this, slot, i);
    }
    m_perSlot[slot] = 0;
}
