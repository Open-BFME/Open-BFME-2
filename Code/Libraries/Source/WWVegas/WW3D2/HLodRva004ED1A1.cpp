// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?teamAttackObject@AITactic@@QAEXHPAVObject@@@Z @0x004ED1A1 92B
// HLod attack helper: find node via rowed 0x004ECF05 then create AI group, fill via Team, attack victim, destroy group, clear +0x10.
// Evidence: chain via 0x004ECF05; callees rowed createGroup 0x002FEC4B getTeamAsAIGroup 0x003A0F62 destroyGroup 0x002FE712 plus pins findTeamByID 0x0039F761 groupAttackObjectPrivate 0x0036FD64; globals TheAI TheTeamFactory; ret 8 two args.
class Object;
enum CommandSourceType
{
	CommandSourceType_0 = 0
};
class AIGroup;
class Team;
class AI;
class AITactic;
class TeamFactory;
extern AI *TheAI;
extern TeamFactory *TheTeamFactory;
struct Rva003A2FD4Proto;
class AsciiString;
class TeamPrototype;
class TeamFactory
{
public:
	Rva003A2FD4Proto *initTeamForTacticalAI(const AsciiString &name, void *ownerName, int targetID, unsigned int tacticID);
	TeamPrototype *findTeamPrototypeByID(unsigned int id);
	Team *findTeamByID(unsigned int id); // 0x0039F761
};
struct Rva004ECECDNode
{
public:
	void *m_model; // +0x00
	char m_pad04[0xC];
	int m_10; // +0x10
};
struct Coord3D;
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};
class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};
class AIGroup
{
public:
	void groupMoveToPosition(Rva00372571Params *params, int source);
	void groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
private:
	void groupAttackObjectPrivate(bool a, Object *victim, int b, CommandSourceType c);
	friend class AITactic;
};
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *);
};
#include "../../../../GameEngine/Include/Common/TeamBFME2.h"
class AITactic
{
public:
	Rva004ECECDNode *rva004ECF05(int id);
	void teamAttackObject(int id, Object *victim);
	void teamAttackMove(int id, const struct Coord3D *pos);
	void teamForceMove(int id, const struct Coord3D *pos);
	void rva004ED342(void *pos);
	void rva004ED372(const struct Coord3D *pos);
private:
	char m_pad00[0x14];
	Rva004ECECDNode *m_begin;
	Rva004ECECDNode *m_end;
	char m_pad1C[0x8];
	Rva002A9BF2 *m_24;
};
void AITactic::teamAttackObject(int id, Object *victim)
{
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		AIGroup *group = TheAI->createGroup();
		Team *team = TheTeamFactory->findTeamByID((unsigned int)node->m_model);
		team->getTeamAsAIGroup(group);
		group->groupAttackObjectPrivate(false, victim, 0x7fffffff, (CommandSourceType)0);
		TheAI->destroyGroup(group);
		node->m_10 = 0;
	}
}

// ?teamAttackMove@AITactic@@QAEXHPBUCoord3D@@@Z @ 0x004ED1FD 90B.
// Gap-lane like teamAttackObject but move-order via rowed groupAttackMoveToPosition 0x00372B09 with
// (p, 0x7fffffff, 0). Same rowed find/create/fill/destroy plus globals.
// Evidence: pin QAEXHPBUCoord3D; callers 0x004ED274 0x004ED362 0x005A9EBA 0x005A9F31.
void AITactic::teamAttackMove(int id, const struct Coord3D *pos)
{
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		AIGroup *group = TheAI->createGroup();
		Team *team = TheTeamFactory->findTeamByID((unsigned int)node->m_model);
		team->getTeamAsAIGroup(group);
		group->groupAttackMoveToPosition(pos, 0x7fffffff, (CommandSourceType)0);
		TheAI->destroyGroup(group);
		node->m_10 = 0;
	}
}

// ?teamForceMove@AITactic@@QAEXHPBUCoord3D@@@Z @0x004ED257 150B
// Guarded move-order helper: if +0x24 difficulty source is null delegate to rowed teamAttackMove, else node via 0x004ECF05 then create AI group, fill via Team, issue group move via 0x00372571 with position block, destroy group, clear +0x10.
// Evidence: same TU/class as teamAttackObject siblings; callees rowed rva002A9BF2 0x002A9BF2 rva004ECF05 0x004ECF05 createGroup 0x002FEC4B getTeamAsAIGroup 0x003A0F62 destroyGroup 0x002FE712 plus pins teamAttackMove 0x004ED1FD findTeamByID 0x0039F761 groupMoveToPosition 0x00372571; globals TheAI TheTeamFactory; ret 8 two args.
void AITactic::teamForceMove(int id, const struct Coord3D *pos)
{
	if (m_24->rva002A9BF2() == 0)
	{
		teamAttackMove(id, pos);
		return;
	}
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		AIGroup *group = TheAI->createGroup();
		Team *team = TheTeamFactory->findTeamByID((unsigned int)node->m_model);
		team->getTeamAsAIGroup(group);
		Rva00372571Params params;
		params.m_14 = -1;
		params.m_pos = pos;
		params.m_04 = false;
		params.m_08 = 0;
		params.m_0C = 0;
		params.m_10 = 0;
		params.m_18 = 0;
		params.m_1C = false;
		group->groupMoveToPosition(&params, 0);
		TheAI->destroyGroup(group);
		node->m_10 = 0;
	}
}

// ?rva004ED342@AITactic@@QAEXPAX@Z @ 0x004ED342 (48B). Loop over Rva004ECECDNode range calling rowed teamAttackObject-style helper teamAttackMove. Count is (m_end-m_begin)/0x14 via idiv. No donor. Callers 0x005A9BB4 0x005AA66A. Honest pin name.
void AITactic::rva004ED342(void *pos)
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	for (unsigned int i = 0; i < count; ++i)
		teamAttackMove((int)i, (const struct Coord3D *)pos);
}

// ?rva004ED372@AITactic@@QAEXPBUCoord3D@@@Z @0x004ED372 48B
// Loop over Rva004ECECDNode range calling rowed 0x004ED257 with same point; count is (m_end-m_begin)/0x14 via idiv like sibling 0x004ED342.
// Evidence: chain via just-landed 0x004ED257; callers 0x004EDA76 0x005A991D 0x005AB713 pass getPosition and record points; pin QAEXPBUCoord3D const Coord3D spelling.
void AITactic::rva004ED372(const struct Coord3D *pos)
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	for (unsigned int i = 0; i < count; ++i)
		teamForceMove((int)i, pos);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
