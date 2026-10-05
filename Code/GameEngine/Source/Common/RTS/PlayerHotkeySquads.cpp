// cl: /O1 /MD /GX-
//
// Zero Hour Player.cpp hotkey squad handlers, between the rowed
// processCreateTeamGameMessage (0x002ACA86, PlayerRva002ACA86.cpp) and
// setCurrentlySelectedAIGroup (0x002ACC53) exactly as in ZH's source order.
// The callers fit: the GameLogic message dispatch calls 0x002ACA86 at
// 0x00377BD7, these at 0x00377DE1 and 0x003783F6.
//
// ?processSelectTeamGameMessage@Player@@QAEXHPAVGameMessage@@@Z @0x002ACAFB
// (173B) and ?processAddTeamGameMessage@Player@@QAEXHPAVGameMessage@@@Z
// @0x002ACBA8 (171B). ZH guards (hotkey in [0,10), squad +0x708[n] set,
// m_currentSelection +0x730 created on demand: BFME2 uses plain operator new
// 0x1C plus the pinned Squad ctor 0x00268CAC instead of newInstance). BFME2
// deltas: getLiveObjects takes a bool (0x004D6D4F, pinned as the BFME 1
// donor's Gen_0018BC70::bfmeCompact; retail push 1) and
// both handlers route every live object through GameLogic::selectObject
// (0x0023C924, sibling of the rowed deselectObject 0x0023C9F8) with the
// player mask 1 << +0x54. Select clears the selection first (rowed two-vector
// clear 0x004D6C29 = Squad::clearSquad) and starts a new selection with the
// first object only; Add appends each object to the selection (rowed
// 0x004D6C7C = Squad::addObject) and never starts a new one. The squad
// callees keep their ledger names through the inline forwarders below.

class Object;
class GameMessage;
typedef unsigned int PlayerMaskType;

// The squad's live-object vector (start, finish) as returned by the pinned
// getLiveObjects 0x004D6D4F, already named for its BFME 1 donor caller.
class BfmeVecAK
{
public:
	int size() const { return m_finish - m_start; }
	Object *operator[](int i) const { return m_start[i]; }

private:
	Object **m_start;
	Object **m_finish;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
};

class Rva004D6C29
{
public:
	void rva004D6C29();
};

class Rva004D6C7C
{
public:
	void rva004D6C7C(const Object *obj);
};

class Squad
{
public:
	Squad();
	void clearSquad() { ((Rva004D6C29 *)this)->rva004D6C29(); }
	void addObject(Object *obj) { ((Rva004D6C7C *)this)->rva004D6C7C(obj); }
	const BfmeVecAK &getLiveObjects(bool restart) { return *((Gen_0018BC70 *)this)->bfmeCompact(restart); }

private:
	char m_pad[0x1C];
};

class GameLogic
{
public:
	void selectObject(Object *obj, bool createNewSelection, PlayerMaskType playerMask, bool affectClient);
};

extern GameLogic *TheGameLogic;

enum
{
	NUM_HOTKEY_SQUADS = 10
};

class Player
{
public:
	void processSelectTeamGameMessage(int hotkeyNum, GameMessage *msg);
	void processAddTeamGameMessage(int hotkeyNum, GameMessage *msg);
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }

private:
	char m_pad[0x54];
	int m_playerIndex;							// +0x54
	char m_pad2[0x708 - 0x58];
	Squad *m_squads[NUM_HOTKEY_SQUADS];			// +0x708
	Squad *m_currentSelection;					// +0x730
};

void Player::processSelectTeamGameMessage(int hotkeyNum, GameMessage *msg)
{
	if (hotkeyNum < 0 || hotkeyNum >= NUM_HOTKEY_SQUADS)
		return;

	if (m_squads[hotkeyNum] == 0)
		return;

	if (m_currentSelection == 0)
		m_currentSelection = new Squad;

	m_currentSelection->clearSquad();

	const BfmeVecAK &objectList = m_squads[hotkeyNum]->getLiveObjects(true);
	int numObjs = objectList.size();
	bool createNewSelection = true;
	for (int i = 0; i < numObjs; ++i)
	{
		TheGameLogic->selectObject(objectList[i], createNewSelection, getPlayerMask(), false);
		createNewSelection = false;
	}
}
