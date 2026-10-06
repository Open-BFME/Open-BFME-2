// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?groupChangeStance@AIGroup@@QAEXH@Z, retail 0x0036E269, 62 bytes.
// Evidence: circular intrusive list head at +0x04 (same ListNode as Rva0036E346Count: next +0 obj +8); iterates objects calling rowed findModule with rowed Stances key 0x0045EE2C then pinned StancesBehavior::rva0045F084 with int arg; caller at 0x00379814.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType Rva0045EE2CGet(void);

class Module
{
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIGroup;
};

class StancesBehavior
{
public:
	void rva0045F084(int v);
};

struct ListNode
{
	ListNode *m_next;
	char m_pad4[4];
	Object *m_obj;
};

class AIGroup
{
public:
	void groupChangeStance(int v);

private:
	char m_pad0[4];
	ListNode *m_head;
};

void AIGroup::groupChangeStance(int v)
{
	ListNode *cur = m_head->m_next;
	if (cur == m_head)
		return;
	do
	{
		Object *obj = cur->m_obj;
		if (obj != 0)
		{
			NameKeyType key = Rva0045EE2CGet();
			Module *mod = obj->findModule(key);
			if (mod != 0)
				((StancesBehavior *)mod)->rva0045F084(v);
		}
		cur = cur->m_next;
	} while (cur != m_head);
}
