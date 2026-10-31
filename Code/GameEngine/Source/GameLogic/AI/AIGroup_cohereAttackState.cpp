// cl: /Oy- /DNDEBUG /MD
// platformsdk
// ?cohereAttackState@AIGroup@@QAEXXZ, retail 0x003705C2, 190 bytes.
// AIGroup order-issuing walk over the raw member list at +4 (same ListNode
// idiom as AIGroupRva0036DF92): phase 1 keeps the first
// non-null AIUpdateInterface::getCurrentVictim (rowed 0x268D71, called twice
// like retail) as `found`; members with a container at +0x274 are skipped.
// Phase 2 orders every member that has no container, passes rowed
// Object::isAbleToAttack (0x290B73), has an AI with no current victim and
// passes the slot-110 virtual (rowed AIUpdateInterface::isIdle, +0x1B8):
// its +0x20 Rva00295A0FCommands run rowed Rva00295A0FCommand (0x295A0F) with
// the victim position at found+0x38, 0x7FFFFFFF and CMD_FROM_AI.

#include <list>

#include <windows.h>
typedef bool Bool;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Object;

struct AICommandParms;

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int maxShots, int source);
	virtual void aiDoCommand(const AICommandParms *parms);
};

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual Bool isIdle() const;
	Object *getCurrentVictim() const;

	char m_pad[0x20 - 4];
	Rva00295A0FCommands m_commands;
};

class Object
{
public:
	Bool isAbleToAttack() const;
	__declspec(dllimport) __forceinline AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	__declspec(dllimport) __forceinline Object *getContainedBy() { return m_containedBy; }

	char m_pad258[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

class AIGroup
{
public:
	void cohereAttackState();

private:
	std::list<Object *> m_memberList;
};

// WorldBuilder AIGroup::cohereAttackState, WB VA 0x00EEB350 (callgraph lead, score 3).
void AIGroup::cohereAttackState()
{
	Object *found = NULL;
	std::list<Object *>::iterator head = m_memberList.end();
	for (std::list<Object *>::iterator node = m_memberList.begin(); node != head; ++node) {
		if (found != NULL)
			goto PHASE2;
		Object *obj = *node;
		if (obj->getContainedBy() != NULL)
			continue;
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai == NULL)
			continue;
		if (ai->getCurrentVictim() == NULL)
			continue;
		found = ai->getCurrentVictim();
	}
	if (found == NULL)
		return;
PHASE2:
	for (std::list<Object *>::iterator node = m_memberList.begin(); node != head; ++node) {
		Object *obj = *node;
		if (obj->getContainedBy() != NULL)
			continue;
		if (!obj->isAbleToAttack())
			continue;
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai == NULL)
			continue;
		if (ai->getCurrentVictim() != NULL)
			continue;
		if (!ai->isIdle())
			continue;
		reinterpret_cast<Rva00295A0FCommands *>(&ai->m_commands)->Rva00295A0FCommand((void *)((char *)found + 0x38), 0x7FFFFFFF, 2);
	}
}
