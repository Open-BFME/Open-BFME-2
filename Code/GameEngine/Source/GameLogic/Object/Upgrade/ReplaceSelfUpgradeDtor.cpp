// cl: /O1 /DNDEBUG /MD
//
// ??1ReplaceSelfUpgrade@@MAE@XZ, retail 0x004B70EB, 5 bytes.
// ReplaceSelfUpgrade behavior dtor: trivial tail-jmp to the UpgradeModule
// base dtor (twin pin ??1UpgradeModule@@MAE@XZ at 0x0046089D, ICF-folded
// under the rowed ??1FireWeaponWhenDeadBehavior@@MAE@XZ there).
// No vptr stores: novtable suppresses the derived store retail lacks.
// Identity is vtable 0x00858B10 of the rowed ctor 0x004B7045 plus sole caller
// ??_G 0x004B70CF slot 0. Shape follows ArmorUpgradeDtor (UpgradeModule
// multi-inheritance, protected virtual MAE, trivial donor ZH ArmorUpgrade).

class Thing;
class ModuleData;

class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~UpgradeModule();
};

class __declspec(novtable) ReplaceSelfUpgrade : public UpgradeModule
{
public:
	ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ReplaceSelfUpgrade();
};

ReplaceSelfUpgrade::~ReplaceSelfUpgrade()
{
}
