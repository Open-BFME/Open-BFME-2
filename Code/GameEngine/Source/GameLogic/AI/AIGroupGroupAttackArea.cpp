// cl: /O1 /DNDEBUG /MD /GX
//
// AIGroup::groupAttackArea (?groupAttackArea@AIGroup@@QAEXPAVPolygonTrigger@@W4CommandSourceType@@@Z),
// retail 0x00370517, 61 bytes.
// Pinned name; caller is ScriptActions::doTeamAttackArea at 0x003BEF20 which
// builds an AIGroup from the named team and calls this with the qualified
// trigger and command source 1. Donor is ZH GeneralsMD AIGroup.cpp:2562
// AIGroup::groupAttackArea iterating m_memberList and calling
// AIUpdateInterface::aiAttackArea; BFME1 ScriptActionsTeamOrders.cpp
// doTeamAttackArea passes the same trigger plus CMD_FROM_SCRIPT to
// AIGroup::groupAttackArea. Callee is pinned aiAttackArea at 0x0036F136
// through the AIUpdateInterface+0x20 command subobject; Object+0x258 holds
// the AIUpdateInterface pointer. AIGroup list sits at +0 (MSVC list head
// at +4 matches retail [edi+4] loads).
#include <list>

class PolygonTrigger;
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiAttackArea(const PolygonTrigger *area, CommandSourceType cmd);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commandInterface;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface()
	{
		return *(AIUpdateInterface **)((char *)this + 0x258);
	}
};

class AIGroup
{
public:
	void groupAttackArea(PolygonTrigger *area, CommandSourceType cmd);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupAttackArea(PolygonTrigger *areaToGuard, CommandSourceType cmdSource)
{
	if (!areaToGuard) {
		return;
	}
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		Object *obj = *i;
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai) {
			ai->m_commandInterface.aiAttackArea(areaToGuard, cmdSource);
		}
	}
}
