// cl: /DNDEBUG /MD
//
// ??1ObjectCreationUpgrade@@MAE@XZ, retail 0x004B3F90, 36 bytes.
// ObjectCreationUpgrade behavior dtor: four vptr stores (+0x00 0x857660
// +0x08 0x85762C +0x14 0x857570 +0x18 0x857560, DIR32) then tail-jmp to the
// UpdateModule base dtor (pin ??1UpdateModule@@UAE@XZ at 0x0024A797).
// Layout is UpgradeMux base at +0 (vptr plus bool) plus UpdateModule base
// at +8 (BehaviorModule 0x0C plus two interface vptrs at +0x14/+0x18).
// UpgradeMux dtor is trivial bool so only the UpdateModule call remains.
// Identity is the ObjectCreationUpgrade cluster: dtor 0x004B3F90 plus name
// 0x004B3FB4 returning ObjectCreationUpgrade plus pool key 0x004B3FF5 plus
// ctor 0x004B40A6 plus deleting dtor 0x004B40EA calling here. Donor is ZH
// ObjectCreationUpgrade.cpp:79 trivial dtor. Shape follows ArmorUpgradeDtor
// (four vptrs plus tail-jmp, protected virtual MAE).

class Thing;
class ModuleData;

class UpgradeMux
{
public:
	virtual void muxAnchor();

private:
	bool m_executed;
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };



class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ObjectCreationUpgrade();
	// Slot 0 of the +0x18 vftable 0x00C57560 is 0x004B42DB, this class's update.
	virtual UpdateSleepTime update();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

// ??1ObjectCreationUpgrade@@MAE@XZ @0x004B3F90
ObjectCreationUpgrade::~ObjectCreationUpgrade()
{
}
