// ?isRetryConnectingOverLimit@PortNegotiationSchema@@QAE_NGG@Z
// partial score=0.92 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE
// PortNegotiationSchema.cpp -- schema members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. A valid slot (below 8) first resets the schema
// (0x005DB9E4, unnamed), then records the slot list at +0x8B8 and the slot
// at +0x14.

typedef unsigned short UnsignedShort;
typedef int Int;

enum { MAX_PORT_SLOTS = 8 };

class GameSlot { public: bool isHuman() const; };

class PortNegotiationSchema
{
public:
	void attachSlotList(void *slotList, UnsignedShort slot);
	bool isRetryConnectingOverLimit(UnsignedShort slot1, UnsignedShort slot2);

private:
	void rva005DB9E4();			// 0x005DB9E4

	unsigned char m_pad000[0x14];
	UnsignedShort m_slot;			// +0x014
	unsigned char m_pad016[2];
	Int m_tableA[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x018
	Int m_tableB[MAX_PORT_SLOTS][MAX_PORT_SLOTS];	// +0x118
	unsigned char m_pad218[0x718 - 0x218];
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

// WB 15C7E70 names this method; retail 5DBC2E..5DBCA6 verifies the
// human-slot guards, negotiation state 4 and unsigned retry limit 5.
bool PortNegotiationSchema::isRetryConnectingOverLimit(UnsignedShort slot1, UnsignedShort slot2)
{
    if (slot1 >= MAX_PORT_SLOTS) return false;
    if (slot2 >= MAX_PORT_SLOTS) return false;
    if (slot1 == slot2) return false;
    if (((GameSlot **)m_slotList)[slot1] && ((GameSlot **)m_slotList)[slot1]->isHuman() &&
        ((GameSlot **)m_slotList)[slot2] && ((GameSlot **)m_slotList)[slot2]->isHuman() &&
        m_tableA[slot1][slot2] == 4 && m_tableD[slot1][slot2] >= 5)
        return true;
    return false;
}
