// cl: /O1 /DNDEBUG /MD
//
// ?rva004A33EE@BroadcastStealthUpdate@@QAEXXZ @0x004A33EE 64B.
// Walk the ObjectID list at +0x28. Each live object whose stealth helper
// 0x0028F4BC returns a module gets 0x00373D23, then the list resets
// through Rva0029FB3BMember::reset.

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

class Object;

class Rva00373EC6
{
public:
	void rva00373D23();
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Rva004A33EENode
{
	Rva004A33EENode *m_next;
	Rva004A33EENode *m_prev;
	ObjectID m_id;
};

class Rva0029FB3BMember
{
public:
	void reset();
	void *m_head;
};

class BroadcastStealthUpdate
{
public:
	void rva004A33EE();

private:
	char m_pad[0x28];
	Rva0029FB3BMember m_member;
};

void BroadcastStealthUpdate::rva004A33EE()
{
	Rva004A33EENode *head = (Rva004A33EENode *)m_member.m_head;
	Rva004A33EENode *node = head->m_next;
	if (node != head)
	{
		do
		{
			Object *obj = TheGameLogic->findObjectByID(node->m_id);
			if (obj != 0)
			{
				Rva00373EC6 *stealth = obj->rva0028F4BC();
				if (stealth != 0)
					stealth->rva00373D23();
			}
			node = node->m_next;
		} while (node != (Rva004A33EENode *)m_member.m_head);
	}
	m_member.reset();
}
