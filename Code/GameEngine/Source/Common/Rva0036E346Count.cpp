// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0036E346@Rva0036E346@@QAEHXZ, retail 0x0036E346, 17 bytes.
// Circular intrusive-list count: head at +0x04, first at [head], next at
// [node+0x00], counted until back to head. Callers at 0x003540D7 (AIGroup
// path via createGroup) and 0x00548A7D (SpecialPower vector sizing) both
// pass a holder whose +0x04 is the sentinel.

struct ListNode
{
	ListNode *m_next; // +0x00
	char m_pad4[4]; // +0x04
	class Object *m_obj; // +0x08
};

class AIHolder
{
public:
	char m_pad[0x3DA];
	unsigned char m_flag3DA; // +0x3DA
};

class Object
{
public:
	char m_pad[0x258];
	AIHolder *m_ai; // +0x258
	char m_mid[0x438 - 0x25C]; // +0x25C..+0x437
	unsigned char m_flag438; // +0x438
	void *rva0028BD5D(int v) const;
};

class Rva0036E346
{
public:
	int rva0036E346();

private:
	char m_pad0[4]; // +0x00
	ListNode *m_head; // +0x04
};

int Rva0036E346::rva0036E346()
{
	ListNode *head = m_head;
	ListNode *cur = head->m_next;
	int count = 0;
	while (cur != head)
	{
		cur = cur->m_next;
		++count;
	}
	return count;
}

// The holder of 0x0036E2E2 and 0x0036E0E3 is AIGroup: evaluateAndProgressAll-
// SequentialScripts (0x0020C83F) calls both on the group TheAI->createGroup()
// returned and Team::getTeamAsAIGroup filled.
class AIGroup
{
public:
	void rva0036E2E2(bool flag);
	bool rva0036E0E3();

private:
	char m_pad0[4]; // +0x00
	ListNode *m_head; // +0x04
};

void AIGroup::rva0036E2E2(bool flag)
{
	ListNode *cur = m_head->m_next;
	if (cur == m_head)
		return;
	do
	{
		Object *obj = cur->m_obj;
		AIHolder *ai = obj->m_ai;
		if (ai)
			ai->m_flag3DA = flag;
		cur = cur->m_next;
	} while (cur != m_head);
}

bool AIGroup::rva0036E0E3()
{
	ListNode *head = m_head;
	ListNode *cur = head->m_next;
	bool ok = true;
	if (cur != head)
	{
		do
		{
			Object *obj = cur->m_obj;
			if (obj)
				ok = ok && ((obj->m_flag438 & 1) != 0);
			cur = cur->m_next;
		} while (cur != head);
	}
	return ok;
}

class Rva0036E1F7Result
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04();
	virtual void slot05(int v);
};

class Rva0036E1F7
{
public:
	void rva0036E1F7(int a, int b, int c);

private:
	char m_pad0[4];
	ListNode *m_head;
};

void Rva0036E1F7::rva0036E1F7(int a, int b, int c)
{
	(void)c;
	ListNode *cur = m_head->m_next;
	if (cur == m_head)
		return;
	do
	{
		Object *obj = cur->m_obj;
		if (obj != 0)
		{
			void *p = obj->rva0028BD5D(a);
			if (p != 0)
				((Rva0036E1F7Result *)p)->slot05(b);
		}
		cur = cur->m_next;
	} while (cur != m_head);
}

// ?rva0036E2A7@Rva0036E2A7@@QAEXPAVSequentialScript@@H@Z, retail 0x0036E2A7, 59 bytes.
// Chain from 0x00262453: same list holder (+0x04 head, [node+0x00] next,
// [node+0x08] Object, Object+0x258 AIHolder), AIHolder+0x3D0 is the
// ScriptTracker script slot (its +0x0A is the +0x3DA flag). Forwards (p, 1,
// dummy). Caller at 0x003B3DF5.

class SequentialScript;

class ScriptTracker
{
public:
	void setCurScript(SequentialScript *p, bool b, int dummy);
};

class Rva0036E2A7
{
public:
	void rva0036E2A7(SequentialScript *p, int dummy);

private:
	char m_pad0[4]; // +0x00
	ListNode *m_head; // +0x04
};

void Rva0036E2A7::rva0036E2A7(SequentialScript *p, int dummy)
{
	ListNode *cur = m_head->m_next;
	if (cur == m_head)
		return;
	do
	{
		Object *obj = cur->m_obj;
		AIHolder *ai = obj->m_ai;
		if (ai != 0)
			((ScriptTracker *)((char *)ai + 0x3D0))->setCurScript(p, true, dummy);
		cur = cur->m_next;
	} while (cur != m_head);
}
