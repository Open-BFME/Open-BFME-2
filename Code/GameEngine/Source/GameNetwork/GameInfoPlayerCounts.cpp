// cl: /O1 /DNDEBUG /MD /EHsc

// GameInfo player-count file-unit plus the two GameSlot predicates the
// counts call through. BFME1 GameNetwork/GameInfo.cpp donor shapes, with two
// BFME2 deltas proven by retail bytes: the human slot state moved 5 -> 6 for
// a new fifth state that rides with the AI states, and isOccupied() also
// requires the occupancy byte at +0x1A4. The predicates must live in this TU
// with the counters: same-TU visibility into isOccupied's definition is what
// lets the counters keep the slot pointer in EDX across the call with the
// count/limit in EDI/ESI (calling the pin as an opaque extern instead spills
// the pointer to ESI and the count to EBX).
//
// ?rva003FF496@GameInfo@@QBE_NG@Z @0x003FF496 62B: false only when the slot
// at the given index is occupied, its +0x50 dword is set and the +0x64 block
// it guards with the +0x60 byte is absent; true otherwise (including an
// out-of-range index). The same same-TU visibility of isOccupied keeps the
// slot pointer in ECX across that call. The +0x50/+0x60/+0x64 fields are
// unidentified, hence the address name.

typedef int Int;

enum { MAX_SLOTS = 8 };

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	// Retail compares against state 5 alongside the AI states in both
	// isOccupied and isAI; ZH has no fifth state, so this BFME2 addition
	// keeps a mechanical name until its identity is proven.
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

enum
{
	PLAYERTEMPLATE_RANDOM = -1,
	PLAYERTEMPLATE_OBSERVER = -2
};

unsigned char Rva0056BD91Pack(unsigned char a, unsigned char b,
	unsigned char c, unsigned char d);

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	unsigned int m_ip;
	unsigned short m_port;
};

class GameSlot
{
public:
	virtual void reset();
	bool isOccupied() const;
	bool isAI() const;
	Int rva003FF145(const BfmeNetAddress *other) const;
	bool isObserver() const;
	unsigned char rva003FF16F() const;
	bool isOpen() const { return m_state == SLOT_OPEN; }
	Int getPlayerTemplate() const { return m_playerTemplate; }

private:
	Int m_state;                    // +0x04
	char m_pad08[0x10];             // +0x08
	Int m_playerTemplate;           // +0x18
	char m_pad1C[0x1C];             // +0x1C..+0x37
	BfmeNetAddress m_addr38;        // +0x38
	char m_pad40[0x10];             // +0x40
public:
	Int m_50;                       // +0x50
	Int m_54;                       // +0x54
	Int m_58;                       // +0x58
	Int m_5c;                       // +0x5C
public:
	// Retail loads these whole and narrows at the byte-wide call; reading
	// the fields directly lets the compiler narrow the loads instead.
	Int rva54() const { return m_54; }
	Int rva58() const { return m_58; }
	Int rva5C() const { return m_5c; }
	unsigned char m_60;             // +0x60
	char m_pad61[3];
	Int m_64;                       // +0x64
	const Int *rva64() const { return m_60 ? &m_64 : 0; }
private:
	char m_pad68[0x1A4 - 0x68];     // +0x68..+0x1A3
	unsigned char m_occupancy;      // +0x1A4
};

class GameInfo
{
public:
	Int getNumPlayers() const;
	Int getNumNonObserverPlayers() const;
	Int getNumOpenOrOccupiedSlots() const;
	const GameSlot *getConstSlot(Int slotNum) const;
	bool rva003FF496(unsigned short slotNum) const;
private:
	char m_pad[0x18];
	GameSlot *m_slot[MAX_SLOTS];
};

// ?isOccupied@GameSlot@@QBE_NXZ
bool GameSlot::isOccupied() const
{
	return (m_state == SLOT_PLAYER || m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI
		|| m_state == SLOT_BRUTAL_AI || m_state == SLOT_AI_5) && m_occupancy;
}

// ?isAI@GameSlot@@QBE_NXZ
bool GameSlot::isAI() const
{
	return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI
		|| m_state == SLOT_BRUTAL_AI || m_state == SLOT_AI_5;
}

Int GameSlot::rva003FF145(const BfmeNetAddress *other) const
{
	if (m_state == SLOT_PLAYER && m_addr38.Rva00248CBF(other))
		return 1;
	return 0;
}

// ?isObserver@GameSlot@@QBE_NXZ
// No BFME1 donor: the observer template (-2) read as a predicate. Fifteen
// direct callers, mostly lobby UI.
bool GameSlot::isObserver() const
{
	return m_playerTemplate == PLAYERTEMPLATE_OBSERVER;
}

// ?rva003FF16F@GameSlot@@QBEEXZ
// No donor: the byte the LAN lobby's hero setter 0x004456B8 sends as
// "Hero=%d". Kind 1 is a plain yes, kinds 2 and 3 pack the +0x5C or the
// +0x54/+0x58 pair through the rowed Rva0056BD91Pack 0x0056BD91; the kind
// field +0x50 and the packed fields are unidentified, hence the address name.
unsigned char GameSlot::rva003FF16F() const
{
	switch (m_50)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 3:
		return Rva0056BD91Pack(rva54() + 2, rva58(), 0, 0);
	case 2:
		return Rva0056BD91Pack(1, rva5C(), 0, 0);
	}
	return 0;
}

// ?getNumPlayers@GameInfo@@QBEHXZ
Int GameInfo::getNumPlayers() const
{
	Int numPlayers = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied())
			numPlayers++;
	}
	return numPlayers;
}

// ?getConstSlot@GameInfo@@QBEPBVGameSlot@@H@Z
// Unrowed second definition: the row lives in GameSlotApparent.cpp, but this
// file-unit's counters need same-TU visibility into the body (it preserves
// EDX: only EAX is written) so their index loops stay in EDX across the call
// instead of spilling to a third callee-saved register.
const GameSlot *GameInfo::getConstSlot(Int slotNum) const
{
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return 0;
	return m_slot[slotNum];
}

// ?getNumNonObserverPlayers@GameInfo@@QBEHXZ
Int GameInfo::getNumNonObserverPlayers() const
{
	Int numPlayers = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied()
			&& m_slot[i]->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
			numPlayers++;
	}
	return numPlayers;
}

// ?getNumOpenOrOccupiedSlots@GameInfo@@QBEHXZ
// No BFME1 donor: counts slots that are open for joining plus slots already
// taken (state OPEN read inline, the rest via the in-TU isOccupied). Both
// callers pair it with getNumPlayers, so the difference is the open count.
Int GameInfo::getNumOpenOrOccupiedSlots() const
{
	Int numSlots = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot->isOpen() || slot->isOccupied())
			numSlots++;
	}
	return numSlots;
}

bool GameInfo::rva003FF496(unsigned short slotNum) const
{
	if (m_slot && slotNum < MAX_SLOTS) {
		const GameSlot *slot = m_slot[slotNum];
		if (slot->isOccupied() && slot->m_50 != 0 && !slot->rva64())
			return false;
	}
	return true;
}
