// ?rva00370554@Rva00370554@@QAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.8074 date=2026-10-06
// ?rva00370554@Rva00370554@@QAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /Oy-
// ?rva00370554@Rva00370554@@QAEXPAVObject@@W4CommandSourceType@@@Z @0x00370554 110B evidence: leaf between AIGroup 0x00370517 and 0x00370680 same flags; calls rowed Object::rva002931F5 and AICommandInterface::rva0036EC1D; Object+0x258 AIUpdate and +0x20 command as neighbours.
class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void rva0036EC1D(Object *obj, CommandSourceType cmd);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	Object *rva002931F5(bool checkProducer);
	char m_pad00[0x258];
	AIUpdateInterface *m_aiUpdate;
};

struct Rva00370554Node
{
	Rva00370554Node *m_next;
	Rva00370554Node *m_prev;
	Object *m_obj;
};

struct Rva00370554Head
{
	Rva00370554Node *m_next;
	Rva00370554Node *m_prev;
};

class Rva00370554
{
public:
	void rva00370554(Object *arg1, CommandSourceType arg2);
private:
	char m_pad00[4];
	Rva00370554Head *m_head;
};

void Rva00370554::rva00370554(Object *arg1, CommandSourceType arg2)
{
	Object *a = arg1;
	Rva00370554Head *head = m_head;
	if (head->m_next == (Rva00370554Node *)head)
		return;
	Object *firstObj = head->m_next->m_obj;
	if (firstObj == 0)
		return;
	if (a == 0)
		return;
	if (firstObj->rva002931F5(false) != 0)
		firstObj = firstObj->rva002931F5(false);
	if (a->rva002931F5(false) != 0)
		arg1 = a->rva002931F5(false);
	AIUpdateInterface *ai = firstObj->m_aiUpdate;
	if (ai == 0)
		return;
	ai->m_command.rva0036EC1D(arg1, arg2);
}
