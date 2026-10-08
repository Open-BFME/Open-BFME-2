// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?groupAttackMoveToPosition@AIGroup@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z,
// retail 0x00372B09 (176 bytes).
// Donor (Zero Hour AIGroup.cpp AIGroup::groupAttackMoveToPosition): for each
// member with an AI, attack-move when it is able to attack, else plain move.
// Target evidence: WorldBuilder lead names 0x00372B09
// AIGroup::groupAttackMoveToPosition; the member walk is the +0x04 STLport
// list head with Object+0x258 AI and its +0x20 command interface, as in the
// matched AIGroup::groupAttackTeam (0x0036FF33). Callees are the matched
// Object::isAbleToAttack (0x00290B73), the matched position command
// 0x00295A0F (aiAttackMoveToPosition's argument order: pos, shots, source)
// and AICommandInterface::aiMoveToPosition (0x0026C26D).
// BFME 2 delta (target): a player-sourced order to a group of more than one
// member first tries the matched group formation dispatch 0x003724B8
// (rowed under the placeholder BfmeC986, same this) when two TheAI data flags
// (+0xBA, +0xBD) are set, and stops if it took the order.
typedef int Int;
typedef float Real;

struct Coord3D;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int maxShotsToFire, int cmdSource);
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	bool isAbleToAttack() const;
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

struct AIData
{
	char m_pad[0xBA];
	bool m_flagBA; // +0xBA
	char m_padBB[2];
	bool m_flagBD; // +0xBD
};

class AI
{
public:
	const AIData *getAiData() const { return m_aiData; }

private:
	char m_pad[0x18];
	AIData *m_aiData; // +0x18
};

extern AI *TheAI;

class BfmeC986
{
public:
	char rva003724B8(int pos, int a, int b, int c, int d);
};

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

class AIGroup
{
public:
	void groupAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);

private:
	unsigned int size() const
	{
		unsigned int n = 0;
		for (ObjectListNode *p = m_head->m_next; p != m_head; p = p->m_next)
			++n;
		return n;
	}

	char m_pad[0x04];
	ObjectListNode *m_head; // +0x04
};

void AIGroup::groupAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if ((Real)size() > 1.0f && TheAI->getAiData()->m_flagBA && cmdSource == CMD_FROM_PLAYER
		&& TheAI->getAiData()->m_flagBD)
	{
		if (((BfmeC986 *)this)->rva003724B8((int)pos, 0, 1, 0, 1))
			return;
	}

	for (ObjectListNode *i = m_head->m_next; i != m_head; i = i->m_next)
	{
		AIUpdateInterface *ai = i->m_data->m_ai;
		if (ai)
		{
			if (i->m_data->isAbleToAttack())
				((Rva00295A0FCommands *)&ai->m_commands)->Rva00295A0FCommand((void *)pos, maxShotsToFire, cmdSource);
			else
				ai->m_commands.aiMoveToPosition(pos, cmdSource);
		}
	}
}
