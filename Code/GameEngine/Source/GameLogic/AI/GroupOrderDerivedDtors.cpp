// cl: /O1 /MD /Ireference/shims/moduledata
//
// GroupOrder is the shared base: matched constructor/xfer TUs
// identify it for GarrisonObjectGroupOrder and AttackObjectGroupOrder, whose dtors tail-jump to 0x548948.
// ChangeStanceGroupOrder uses the same tail target; keep all derived names opaque.
// Model only the known 0x18 base extent needed by these destructor bodies.
#include "Common/Snapshot.h"

class GroupOrder : public Snapshot
{
public:
	virtual ~GroupOrder();

private:
	unsigned char m_pad04[0x14];
};

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	virtual ~ChangeStanceGroupOrder();
};

ChangeStanceGroupOrder::~ChangeStanceGroupOrder()
{
}

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	virtual ~GarrisonObjectGroupOrder();
};

GarrisonObjectGroupOrder::~GarrisonObjectGroupOrder()
{
}

class AttackObjectGroupOrder : public GroupOrder
{
public:
	virtual ~AttackObjectGroupOrder();
};

AttackObjectGroupOrder::~AttackObjectGroupOrder()
{
}
