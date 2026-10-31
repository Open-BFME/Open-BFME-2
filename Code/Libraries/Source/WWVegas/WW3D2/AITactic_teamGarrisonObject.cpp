// cl: /O1 /MD
//
// ?teamGarrisonObject@AITactic@@QAEXHPAVObject@@@Z @ 0x004ED2ED, 85 bytes.
// HLod group-fill helper like rowed sibling 0x004ED1A1: find node via rowed
// 0x004ECF05 then create AI group, fill via Team, issue group order via rowed
// 0x00372BB9 with (victim, 0), destroy group via rowed 0x002FE712, clear +0x10.
// Evidence: same chain as the sibling (find/create/fill/destroy plus pin
// findTeamByID 0x0039F761); globals TheAI TheTeamFactory; ret 8 two args.
class Object;
class AIGroup;
class Team;
class AI;
class AITactic;
class TeamFactory;
extern class AI *TheAI;
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
class AIGroup
{
public:
	void rva00372BB9(const void *a, int b);
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
	void teamGarrisonObject(int id, Object *victim);
};
void AITactic::teamGarrisonObject(int id, Object *victim)
{
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		AIGroup *group = TheAI->createGroup();
		Team *team = TheTeamFactory->findTeamByID((unsigned int)node->m_model);
		team->getTeamAsAIGroup(group);
		group->rva00372BB9(victim, 0);
		TheAI->destroyGroup(group);
		node->m_10 = 0;
	}
}
