// cl: /O1 /DNDEBUG /MD
//
// ?rva004AAD69@Rva004AAD69@@QAEXXZ @0x004AAD69 72B.
// Value at [[this+0xD4]+4]+4, or 0xF423F when the middle pointer is null.
// When that value is 1, idle the AI on the object at this-0x3E4 and call
// slot 0x20 on the holder with 0.

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmd);
};

struct AIUpdateInterface
{
	char m_pad[0x20];
	AICommandInterface m_cmd;
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

struct Rva004AAD69Node
{
	char m_pad[4];
	int m_value;
};

class Rva004AAD69Holder
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8(int flag);
	Rva004AAD69Node *m_node;
};

class Rva004AAD69
{
public:
	void rva004AAD69();

private:
	char m_pad[0xD4];
	Rva004AAD69Holder *m_holder;
};

void Rva004AAD69::rva004AAD69()
{
	Rva004AAD69Node *node = m_holder->m_node;
	int value = node != 0 ? node->m_value : 0xF423F;
	if (value != 1)
		return;
	Object *obj = *(Object **)((char *)this - 0x3E4);
	AIUpdateInterface *ai = obj->m_ai;
	if (ai != 0)
		ai->m_cmd.aiIdle(CMD_FROM_AI);
	m_holder->s8(0);
}
