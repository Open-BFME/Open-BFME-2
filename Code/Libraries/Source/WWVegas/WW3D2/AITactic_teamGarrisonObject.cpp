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
#include "../../../../GameEngine/Include/Common/TeamFactory.h"
#include "../../../../GameEngine/Include/Common/Rva004ECECDNode.h"
enum CommandSourceType;
struct Coord3D;
struct Rva00372571Params;
#include "../../../../GameEngine/Include/GameLogic/AIGroup.h"
#include "../../../../GameEngine/Include/GameLogic/AI.h"
#include "../../../../GameEngine/Include/Common/TeamBFME2.h"
#include "../../../../GameEngine/Include/Common/AITactic.h"
void AITactic::teamGarrisonObject(int id, Object *target)
{
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		AIGroup *group = TheAI->createGroup();
		Team *team = TheTeamFactory->findTeamByID((unsigned int)node->m_model);
		team->getTeamAsAIGroup(group);
		group->rva00372BB9(target, 0);
		TheAI->destroyGroup(group);
		node->m_10 = 0;
	}
}
