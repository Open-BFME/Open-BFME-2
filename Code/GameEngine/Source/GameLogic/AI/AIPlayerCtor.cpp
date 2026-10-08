// cl: /DNDEBUG /MD /EHsc
//
// ??0AIPlayer@@QAE@PAVPlayer@@@Z @0x004F04FC 190B: AIPlayer::AIPlayer(Player*)
// after the BFME1/Zero Hour donor, on the BFME2 layout read from the retail
// stores (vftable 0x00C62DC8, whose slot-2 name getter 0x004F05BA returns
// AIPlayer). BFME2 adds the float at +0x44 (10.0f) and the dword at +0x74.
// Globals: TheGameLogic 0x00DFE78C (frame +0x40), TheScriptEngine 0x00DFE16C
// (global difficulty +0x1A4C4), TheAI 0x00DFF0F8 (AI data +0x18, team
// seconds float +0x08). The two queue heads are constructed subobjects; as
// plain pointers the scheduler hoists the scalar stores above the vptr.

class Player
{
public:
	void setCanBuildUnits(bool b) { m_canBuildUnits = b; }
private:
	char m_pad[0x338];
	bool m_canBuildUnits;
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

struct Rva004F04FCScriptEngine
{
	int getGlobalDifficulty() const { return m_difficulty; }
	char m_pad[0x1A4C4];
	int m_difficulty;
};
extern class ScriptEngine *TheScriptEngine;

struct Rva004F04FCAIData
{
	char m_pad[0x08];
	float m_teamSeconds;
};

struct Rva004F04FCAI
{
	const Rva004F04FCAIData *getAiData() const { return m_aiData; }
	char m_pad[0x18];
	Rva004F04FCAIData *m_aiData;
};
extern class AI *TheAI;

struct Coord3D
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class TeamInQueue;

struct Rva004F04FCDLinkHead
{
	Rva004F04FCDLinkHead() : m_head(0) {}
	TeamInQueue *m_head;
};

class AIPlayer
{
public:
	AIPlayer(Player *p);
	virtual ~AIPlayer();
protected:
	Rva004F04FCDLinkHead m_teamBuildQueue;
	Rva004F04FCDLinkHead m_teamReadyQueue;
	Player *m_player;
	bool m_readyToBuildTeam;
	bool m_readyToBuildStructure;
	int m_teamTimer;
	int m_structureTimer;
	int m_teamSeconds;
	int m_buildDelay;
	int m_teamDelay;
	unsigned int m_frameLastBuildingBuilt;
	int m_difficulty;
	int m_skillsetSelector;
	Coord3D m_baseCenter;
	bool m_baseCenterSet;
	float m_44;
	unsigned int m_structuresToRepair[2];
	unsigned int m_repairDozer;
	Coord3D m_repairDozerOrigin;
	int m_structuresInQueue;
	bool m_dozerQueuedForRepair;
	bool m_65;
	unsigned int m_supplySourceAttackCheckFrame;
	unsigned int m_attackedSupplyCenter;
	unsigned int m_curWarehouseID;
	int m_74;
};

AIPlayer::AIPlayer(Player *p) :
	m_player(p),
	m_readyToBuildTeam(false),
	m_readyToBuildStructure(false),
	m_teamTimer(2),
	m_structureTimer(2),
	m_teamSeconds(10),
	m_buildDelay(0),
	m_teamDelay(0),
	m_skillsetSelector(-1),
	m_44(10.0f),
	m_repairDozer(0),
	m_structuresInQueue(0),
	m_dozerQueuedForRepair(false),
	m_65(false),
	m_supplySourceAttackCheckFrame(0),
	m_attackedSupplyCenter(0),
	m_curWarehouseID(0),
	m_74(0)
{
	m_frameLastBuildingBuilt = TheGameLogic->getFrame();
	p->setCanBuildUnits(false);

	int i;
	for (i = 0; i < 2; i++) {
		m_structuresToRepair[i] = 0;
	}
	m_repairDozerOrigin.zero();
	m_baseCenter.zero();
	m_baseCenterSet = false;
	m_difficulty = (*(Rva004F04FCScriptEngine **)&TheScriptEngine)->getGlobalDifficulty();
	m_teamSeconds = (*(Rva004F04FCAI **)&TheAI)->getAiData()->m_teamSeconds;
}
