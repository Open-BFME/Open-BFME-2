// cl: /DNDEBUG /MD /EHsc

// ?getSlot@GameInfo@@QAEPAVGameSlot@@H@Z @0x3FF29F (29B):
// GameInfo::getSlot. BFME1 GameInfo.cpp shape (a null check on the array
// itself, kept by the compiler as lea/test, plus bounds guards), except
// BFME2 spells the bounds as separate guards: the && form lays the dead
// null tail mid-function, while retail shares it at the end.
typedef int Int;

enum { MAX_SLOTS = 8 };
enum { SLOT_PLAYER = 6 };

class GameSlot
{
public:
	bool isHuman() const { return m_state == SLOT_PLAYER; }
	void setAccept() { m_isAccepted = true; }
	void unAccept() { if (isHuman()) m_isAccepted = false; }
private:
	void *m_vtable;
	Int m_state;
	bool m_isAccepted;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);
	void resetAccepted();
private:
	char m_pad[0x18];
	GameSlot *m_slot[8];
};

// ?getSlot@GameInfo@@QAEPAVGameSlot@@H@Z
GameSlot *GameInfo::getSlot(Int slotNum)
{
	if (m_slot == 0)
		return 0;
	return (slotNum < 0 || slotNum >= MAX_SLOTS) ? 0 : m_slot[slotNum];
}

// ?resetAccepted@GameInfo@@QAEXXZ
// BFME1 GameInfo.cpp resetAccepted shape, with slot 0 spelled as a direct
// array load: retail inlines slot 0 to lea/test/mov (xor edx,edx; lea; inc)
// and issues getSlot calls only for slots 1..7, reusing dl for setAccept.
void GameInfo::resetAccepted()
{
	if (m_slot && m_slot[0])
		m_slot[0]->setAccept();
	for (Int i = 1; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = getSlot(i);
		if (slot)
			slot->unAccept();
	}
}
