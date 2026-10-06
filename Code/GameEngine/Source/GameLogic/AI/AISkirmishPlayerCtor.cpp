// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0AISkirmishPlayer@@QAE@PAVPlayer@@@Z @0x004EF3A3 116B: Zero Hour
// AISkirmishPlayer::AISkirmishPlayer(Player *p). Identity: the vtable it
// installs (0x00C62AF8) has the rowed ?xfer@AISkirmishPlayer 0x004EF52F in
// slot 3 and the rowed deleting dtor 0x004EF635 in slot 0; the base call goes
// to 0x004F04FC, which installs the AIPlayer vftable 0x00C62DC8 (pinned here
// as AIPlayer(Player*)). Body: zero the defense counters/angles at
// +0x78..+0x9C, m_frameLastBuildingBuilt = TheGameLogic->getFrame() (+0x40),
// then p->setCanBuildUnits(true) (Player +0x338). Caller: 0x002A9AAC.

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

class AIPlayer
{
public:
	AIPlayer(Player *p);
	virtual ~AIPlayer();
protected:
	char m_pad04[0x28 - 0x04];
	unsigned int m_frameLastBuildingBuilt;
	char m_pad2C[0x78 - 0x2C];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	AISkirmishPlayer(Player *p);
	virtual ~AISkirmishPlayer();
protected:
	int m_curFlankBaseDefense;
	int m_curFrontBaseDefense;
	float m_curFlankLeftDefenseAngle;
	float m_curFlankRightDefenseAngle;
	float m_curFrontLeftDefenseAngle;
	float m_curFrontRightDefenseAngle;
	float m_curLeftFlankRightDefenseAngle;
	float m_curRightFlankLeftDefenseAngle;
	unsigned int m_frameToCheckEnemy;
	Player *m_currentEnemy;
};

AISkirmishPlayer::AISkirmishPlayer(Player *p) :
	AIPlayer(p),
	m_curFlankBaseDefense(0),
	m_curFrontBaseDefense(0),
	m_curFlankLeftDefenseAngle(0.0f),
	m_curFlankRightDefenseAngle(0.0f),
	m_curFrontLeftDefenseAngle(0.0f),
	m_curFrontRightDefenseAngle(0.0f),
	m_curLeftFlankRightDefenseAngle(0.0f),
	m_curRightFlankLeftDefenseAngle(0.0f),
	m_frameToCheckEnemy(0),
	m_currentEnemy(0)
{
	m_frameLastBuildingBuilt = TheGameLogic->getFrame();
	p->setCanBuildUnits(true);
}
