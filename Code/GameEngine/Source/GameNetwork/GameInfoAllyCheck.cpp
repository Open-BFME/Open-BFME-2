// cl: /O1 /DNDEBUG /MD
// ?Rva005BF28EIsAlly@@YA_NPBVGameInfo@@PBVGameSlot@@@Z @0x005BF28E 57B: GameInfo local-ally team check via getLocalSlotNum slot 13 (+0x34) and rowed getConstSlot; evidence retail virtual call + getConstSlot row + team at +0x1c.

typedef int Int;
typedef bool Bool;

class GameSlot
{
public:
	virtual void reset();
	Int getTeamNumber() const { return m_teamNumber; }

private:
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	char m_pad0A[2];
	Int m_color;
	Int m_startPos;
	char m_pad14[4];
	Int m_playerTemplate;
	Int m_teamNumber;
};

class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual Int getLocalSlotNum() const = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual Bool rva003FF3B5() = 0;

	const GameSlot *getConstSlot(Int slotNum) const;
};

Bool Rva005BF28EIsAlly(const GameInfo *gameInfo, const GameSlot *slot)
{
	const GameSlot *localSlot = gameInfo->getConstSlot(gameInfo->getLocalSlotNum());
	if (localSlot == 0)
		return true;
	if (slot == localSlot)
		return true;
	Int team = slot->getTeamNumber();
	if (team < 0)
		return false;
	return team == localSlot->getTeamNumber();
}
