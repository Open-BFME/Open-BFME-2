// cl: /Oy- /DNDEBUG /MD
// ?rva003705C2@AIGroup@@QAEXXZ, retail 0x003705C2, 190 bytes.
// AIGroup order-issuing walk over the raw member list at +4 (same ListNode
// idiom as AIGroupRva0036DF92): phase 1 keeps the first
// non-null AIUpdateInterface::getCurrentVictim (rowed 0x268D71, called twice
// like retail) as `found`; members with a container at +0x274 are skipped.
// Phase 2 orders every member that has no container, passes rowed
// Object::isAbleToAttack (0x290B73), has an AI with no current victim and
// passes the slot-110 virtual (rowed AIUpdateInterface::isIdle, +0x1B8):
// its +0x20 Rva00295A0FCommands run rowed Rva00295A0FCommand (0x295A0F) with
// the victim position at found+0x38, 0x7FFFFFFF and CMD_FROM_AI.
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

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
	virtual void aiDoCommand(const AICommandParms *parms);
	void Rva00295A0FCommand(void *pos, int maxShots, int source);
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
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }

	char m_pad258[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

struct ListNode
{
	ListNode *m_next;
	char m_pad04[4];
	Object *m_obj;
};

class AIGroup
{
public:
	void rva003705C2();

private:
	char m_pad00[4];
	ListNode *m_head;
};

void AIGroup::rva003705C2()
{
	Object *found = NULL;
	ListNode *head = m_head;
	for (ListNode *node = head->m_next; node != head; node = node->m_next) {
		if (found != NULL)
			goto PHASE2;
		Object *obj = node->m_obj;
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
	for (ListNode *node = m_head->m_next; node != head; node = node->m_next) {
		Object *obj = node->m_obj;
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
		ai->m_commands.Rva00295A0FCommand((void *)((char *)found + 0x38), 0x7FFFFFFF, 2);
	}
}
