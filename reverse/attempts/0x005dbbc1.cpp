// ?isConnectionDone@PortNegotiationSchema@@QAE_NGG@Z
// partial score=0.9 date=2026-10-09
// cl: /DNDEBUG /MD /O1
// ?isConnectionDone@PortNegotiationSchema@@QAE_NGG@Z retail 0x005DBBC1 109B
// ?isRetryConnectingOverLimit@PortNegotiationSchema@@QAE_NGG@Z retail 0x005DBC2E 120B
// Both take an ordered pair of distinct slot indices below 8 and read the 8x8
// state grid at +0x18 (index second + first * 8). Names are the debug build's
// PortNegotiationSchema members (wb-lead, callgraph score 2); the pair scan and
// offsets (+0x18 state ints, +0x838 retry words, +0x8B8 slot pointers) are
// retail's. Same class and callee isHuman 0x003FF0F1 as the neighbours.
class GameSlot
{
public:
	bool isHuman() const;
};

class PortNegotiationSchema
{
	char m_pad0[0x18];
	int m_state[64];
	char m_pad1[0x838 - 0x118];
	unsigned short m_retries[64];
	GameSlot **m_slots;
public:
	bool isConnectionDone(unsigned short first, unsigned short second);
	bool isRetryConnectingOverLimit(unsigned short first, unsigned short second);
};

bool PortNegotiationSchema::isConnectionDone(unsigned short first, unsigned short second)
{
	if (first >= 8)
		return false;
	if (second >= 8)
		return false;
	if (first == second)
		return false;
	GameSlot *a = m_slots[first];
	if (a && a->isHuman()) {
		GameSlot *b = m_slots[second];
		if (b && b->isHuman() && m_state[second + first * 8] != 3)
			return false;
	}
	return true;
}

bool PortNegotiationSchema::isRetryConnectingOverLimit(unsigned short first, unsigned short second)
{
	if (first >= 8)
		return false;
	if (second >= 8)
		return false;
	if (first == second)
		return false;
	GameSlot *a = m_slots[first];
	if (a && a->isHuman()) {
		GameSlot *b = m_slots[second];
		if (b && b->isHuman() && m_state[second + first * 8] == 4 && m_retries[second + first * 8] >= 5)
			return true;
	}
	return false;
}
