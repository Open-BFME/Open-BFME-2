// cl: /O1 /DNDEBUG /MD
//
// ?rva0036DF14@AIGroup@@QAEXPBVUpgradeTemplate@@@Z, retail 0x0036DF14, 57 bytes.
// Leaf between queueUpgrade 0x0036DE89 and isIdle 0x0036DF4D. Evidence: same
// AIGroup member-list walk at this+0x04, same Object::rva0028BC58 pin 0x0028BC58
// returning the ProductionUpdate, same null-upgrade early-out as queueUpgrade,
// caller at 0x003782E9. Calls ProductionUpdate vtable slot +0x10 with the upgrade.
#include <list>

class UpgradeTemplate;

class ProductionUpdateInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void rvaSlot10(const UpgradeTemplate *upgrade);
};

class Object
{
public:
	void *rva0028BC58(int arg);
};

class AIGroup
{
public:
	void rva0036DF14(const UpgradeTemplate *upgrade);
private:
	std::list<Object *> m_memberList; // +0x00, head at +0x04 like queueUpgrade/isIdle siblings
};

void AIGroup::rva0036DF14(const UpgradeTemplate *upgrade)
{
	if (!upgrade)
		return;
	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *member = *i;
		ProductionUpdateInterface *prod = (ProductionUpdateInterface *)member->rva0028BC58(0);
		if (!prod)
			continue;
		prod->rvaSlot10(upgrade);
	}
}
