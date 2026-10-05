// cl: /O1 /DNDEBUG /MD
//
// ?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z, retail 0x00546BED,
// 57 bytes: slot 4 of the ChangeStanceGroupOrder vtable 0x00C6A36C. Finds the
// Object through TheGameLogic (rowed findObjectByID 0x00049DC5), looks up its
// StancesBehavior module by the cached "StancesBehavior" key (rowed
// Rva0045EE2CGet 0x0045EE2C, rowed Object::findModule 0x0028B6D6) and hands
// it the order's stance at +0x18 (StancesBehavior member 0x0045F084, pinned).
// The stance is the int the class's xfer 0x00546B91 runs through the stances
// enum. Names by address.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType Rva0045EE2CGet();

class Module;

class StancesBehavior
{
public:
	void rva0045F084(int stance);
};

class ChangeStanceGroupOrder;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class ChangeStanceGroupOrder;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ChangeStanceGroupOrder
{
public:
	virtual ~ChangeStanceGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void rva00546BED(ObjectID id);
private:
	char m_pad04[0x18 - 4];
	int m_stance; // +0x18
};

void ChangeStanceGroupOrder::rva00546BED(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj)
	{
		StancesBehavior *stances = (StancesBehavior *)obj->findModule(Rva0045EE2CGet());
		if (stances)
			stances->rva0045F084(m_stance);
	}
}
