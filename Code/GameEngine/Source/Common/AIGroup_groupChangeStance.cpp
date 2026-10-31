// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?groupChangeStance@AIGroup@@QAEXH@Z, retail 0x0036E269, 62 bytes.
// Evidence: circular intrusive list head at +0x04 (same ListNode as Rva0036E346Count: next +0 obj +8); iterates objects calling rowed findModule with rowed Stances key 0x0045EE2C then rowed StancesBehavior::changeStance with int arg; caller at 0x00379814.
#include <list>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType Rva0045EE2CGet(void);

#include "../../Include/Common/Module.h"

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIGroup;
};

class StancesBehavior
{
public:
	bool changeStance(int v);
};

class AIGroup
{
public:
	void groupChangeStance(int v);

private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupChangeStance(int v)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (obj != 0)
		{
			NameKeyType key = Rva0045EE2CGet();
			Module *mod = obj->findModule(key);
			if (mod != 0)
				((StancesBehavior *)mod)->changeStance(v);
		}
	}
}
