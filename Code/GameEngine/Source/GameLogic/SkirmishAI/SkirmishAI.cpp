// cl: /O1 /EHsc /MD /arch:SSE
// SkirmishAI.cpp -- SkirmishAI members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function and its
// callee SkirmishAI::transferUnitsToPlayer (0x002C6AFA); retail supplies the
// bytes. When a slave AI dies its units go to the player whose index is at
// +0x178.

typedef int Int;

// Player view: rva002AE2ED (rowed) grants this player the other player's
// sciences; +0x24 is copied from the dying AI's player (retail-measured).
class Player
{
public:
	void rva002AE2ED(Player *other);			// 0x002AE2ED
	Int getField24() const { return m_field24; }
	void setField24(Int value) { m_field24 = value; }

private:
	unsigned char m_pad00[0x24];
	Int m_field24;						// +0x24
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);				// 0x002A7A29
};

extern PlayerList *ThePlayerList;

class Object;

// SkirmishAI's AIBuilder base sits at offset 0; its onUnitCreated (WB name,
// unrowed 0x004EC3AC) takes the new unit, an object and a horde flag.
class AIBuilder
{
public:
	void onUnitCreated(Object *object, Object *other, bool isHorde);	// 0x004EC3AC
};

class SkirmishAI : public AIBuilder
{
public:
	void onUnitCreated(Object *object, Object *other);
	void onHordeCreated(Object *object, Object *other);
	void doSpecialSlaveAIDying();
	void doSpecialMasterAIDying();
	void transferUnitsToPlayer(Player *player);		// 0x002C6AFA
	Int resetMaster();					// 0x002C68CE
	void doSpecialSlaveAIUpdate();				// 0x002C6879

private:
	unsigned char m_pad000[0x15C];
	Player *m_player;					// +0x15C
	unsigned char m_pad160[0x168 - 0x160];
	bool m_disabled168;					// +0x168, set: creations are ignored
	unsigned char m_pad169[0x178 - 0x169];
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

// SkirmishAI::onUnitCreated, retail 0x002C6A8D (27 bytes): WB names it in
// SkirmishAI.cpp (asserts the object at line 357) and its callee
// AIBuilder::onUnitCreated, forwarded with the horde flag clear.
void SkirmishAI::onUnitCreated(Object *object, Object *other)
{
	if (!m_disabled168)
		AIBuilder::onUnitCreated(object, other, false);
}

// SkirmishAI::onHordeCreated, retail 0x002C6AA8 (27 bytes): WB's twin of
// onUnitCreated, forwarding with the horde flag set.
void SkirmishAI::onHordeCreated(Object *object, Object *other)
{
	if (!m_disabled168)
		AIBuilder::onUnitCreated(object, other, true);
}
