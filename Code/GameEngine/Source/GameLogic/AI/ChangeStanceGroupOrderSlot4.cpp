// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z, retail 0x00546BED,
// 57 bytes: slot 4 of the ChangeStanceGroupOrder vtable 0x00C6A36C. Finds the
// Object through TheGameLogic (rowed findObjectByID 0x00049DC5), looks up its
// StancesBehavior module by the cached "StancesBehavior" key (rowed
// Rva0045EE2CGet 0x0045EE2C, rowed Object::findModule 0x0028B6D6) and hands
// it the order's stance at +0x18 (StancesBehavior member 0x0045F084, pinned).
// The stance is the int the class's xfer 0x00546B91 runs through the stances
// enum. Names by address.
#include "../../Common/GameLogicObjectLookupView.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType Rva0045EE2CGet();

class Module;

class StancesBehavior
{
public:
	bool changeStance(int stance);
};

class ChangeStanceGroupOrder;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class ChangeStanceGroupOrder;
};


extern GameLogic *TheGameLogic;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0036E346;
class Xfer;
enum ObjectID;

// The direct base GroupOrder (ctor 0x005488C5, called only by the six group
// orders) is 0x18 bytes: vptr 0xC6A520, vector-built member at +4 via
// 0x211E58, zeros at +0x10/+0x14. Do NOT declare an explicit vptr member on
// the base: the hidden vptr sits at +0 and a declared one shifts every slot.
// Its table is Snapshot's: loadPostProcess in slot 1, the class-name getter
// in slot 2 and xfer (0x00548AC2) in slot 3 (GroupOrderDerivedDtors.cpp).
class GroupOrder : public Snapshot
{
public:
	GroupOrder();
	GroupOrder(Rva0036E346 *holder);
	GroupOrder(const GroupOrder &other);
	virtual ~GroupOrder();

	virtual void xfer(Xfer *xfer);

protected:
	unsigned char m_pad04[0x14];
};

// Table 0x0086A36C: slot 3 xfer 0x00546B91, slot 4 rva00546BED 0x00546BED.
class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder();
	ChangeStanceGroupOrder(Rva0036E346 *holder, int stance);
	ChangeStanceGroupOrder(const ChangeStanceGroupOrder &other);
	virtual ~ChangeStanceGroupOrder();

	virtual void xfer(Xfer *xfer);
	virtual void rva00546BED(ObjectID id);

private:
	int m_stance;		// +0x18
};

void ChangeStanceGroupOrder::rva00546BED(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj)
	{
		StancesBehavior *stances = (StancesBehavior *)obj->findModule(Rva0045EE2CGet());
		if (stances)
			stances->changeStance(m_stance);
	}
}
