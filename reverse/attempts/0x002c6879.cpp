// ?doSpecialSlaveAIUpdate@SkirmishAI@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /EHsc /MD /arch:SSE
// SkirmishAI.cpp -- SkirmishAI members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function and its
// callee SkirmishAI::transferUnitsToPlayer (0x002C6AFA); retail supplies the
// bytes. When a slave AI dies its units go to the player whose index is at
// +0x178.

typedef int Int;

// Address-named Player +0x08 sub-object (vtable; float value at its +0x0C,
// Player +0x14). rva003805BB(value, flag) is the pinned add used by
// Player::addSkillPointsForKill; slot 3 is called on the giver first.
class Rva003805BB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	bool rva003805BB(float value, bool flag);
	float getValue() const { return m_value; }

private:
	unsigned char m_pad04[0x0C - 0x04];
	float m_value; // +0x0C
};

// Player view: rva002AE2ED (rowed) grants this player the other player's
// sciences; +0x24 is copied from the dying AI's player (retail-measured).
class Player
{
public:
	void rva002AE2ED(Player *other);			// 0x002AE2ED
	Int getField24() const { return m_field24; }
	void setField24(Int value) { m_field24 = value; }
	Rva003805BB &getField08() { return m_field08; }

private:
	unsigned char m_pad00[0x08];
	Rva003805BB m_field08;					// +0x08
	unsigned char m_pad18[0x24 - 0x18];
	Int m_field24;						// +0x24
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);				// 0x002A7A29
};

extern PlayerList *ThePlayerList;

class SkirmishAI
{
public:
	void doSpecialSlaveAIDying();
	void doSpecialMasterAIDying();
	void transferUnitsToPlayer(Player *player);		// 0x002C6AFA
	Int resetMaster();					// 0x002C68CE
	void doSpecialSlaveAIUpdate();				// 0x002C6879

private:
	unsigned char m_pad000[0x15C];
	Player *m_player;					// +0x15C
	unsigned char m_pad160[0x178 - 0x160];
	Int m_masterPlayerIndex;				// +0x178
};

// SkirmishAI::doSpecialSlaveAIDying, retail 0x002C6BE1.
void SkirmishAI::doSpecialSlaveAIDying()
{
	transferUnitsToPlayer(ThePlayerList->getNthPlayer(m_masterPlayerIndex));
}

// SkirmishAI::doSpecialMasterAIDying, retail 0x002C6B92 (79 bytes).
// Identity (target): WB SkirmishAI.cpp names it and its callees resetMaster
// (0x002C68CE), doSpecialSlaveAIUpdate (0x002C6879) and transferUnitsToPlayer
// (wb-lead 3/callgraph). A new master index (not -1) is stored at +0x178;
// the new master inherits the dying AI player's sciences and +0x24 value and
// receives its units.
void SkirmishAI::doSpecialMasterAIDying()
{
	Int master = resetMaster();
	if (master != -1)
	{
		m_masterPlayerIndex = master;
		doSpecialSlaveAIUpdate();
		Player *masterPlayer = ThePlayerList->getNthPlayer(master);
		masterPlayer->rva002AE2ED(m_player);
		masterPlayer->setField24(m_player->getField24());
		transferUnitsToPlayer(masterPlayer);
	}
}

// SkirmishAI::doSpecialSlaveAIUpdate, retail 0x002C6879 (85 bytes).
// Identity (target): WB SkirmishAI.cpp names it as a callee of
// doSpecialMasterAIDying (wb-lead 2/callgraph). When this AI player's +0x14
// value is positive, its +0x08 sub-object runs slot 3 and the master player
// (index +0x178) receives the value through rva003805BB(value, false).
void SkirmishAI::doSpecialSlaveAIUpdate()
{
	Player *master = ThePlayerList->getNthPlayer(m_masterPlayerIndex);
	float value = m_player->getField08().getValue();
	if (value > 0.0f)
	{
		m_player->getField08().slot3();
		master->getField08().rva003805BB(value, false);
	}
}
