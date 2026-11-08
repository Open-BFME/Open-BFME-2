// cl: /MD /Ireference/shims/moduledata
//
// GroupOrder is the shared base: matched constructor/xfer TUs
// identify it for GarrisonObjectGroupOrder and AttackObjectGroupOrder, whose dtors tail-jump to 0x548948.
// ChangeStanceGroupOrder uses the same tail target; keep all derived names opaque.
// Model only the known 0x18 base extent needed by these destructor bodies.
#include "Common/Snapshot.h"

#include "ChangeStanceGroupOrderView.h"

class Xfer;
enum ObjectID;

// Table 0x0086A36C: slot 3 xfer 0x00546B91, slot 4 rva00546BED 0x00546BED;
// every unit that emits the table spells these two (ChangeStanceGroupOrder.cpp).


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
