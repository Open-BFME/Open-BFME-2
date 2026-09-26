// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1DynamicPortalBehaviour@@MAE@XZ, retail 0x00460C18, 91 bytes. Behavior-side
// destructor completing the DynamicPortalBehaviour file-unit (ctor rowed at
// 0x460B6C news 0x40, poolkey at 0x460BD3, vtable 0x008428C4 slot 0 ??_G at
// 0x460DDA).
//
// Shape: six vptr restores (+0 0x8428C4 +0x0C 0x842808 +0x10 0x8427C0
// +0x18 0x858790 +0x1C 0x8427B8 +0x20 0x8427A8, DIR32) then the explicit
// EBC-owner cleanup through the pinned ?bfmeCallEBC@BfmeOwnerEBC@@QAEXXZ at
// 0x46094C (six slots at +0x24 flag at +0x3C, same zeroed state the ctor
// builds) then the UpgradeModule base dtor through the twin pin
// ??1UpgradeModule@@MAE@XZ at 0x46089D (ICF-folded under the rowed
// ??1FireWeaponWhenDeadBehavior@@MAE@XZ there). Recipe: StealthUpgrade
// four-vptr tail plus PassiveAreaEffect/SlaveWatcher EH-guarded dtor with
// explicit body (and/or state, push ecx/push esi, fs restore).

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~UpgradeModule();
};

class DynamicPortalExtraA
{
public:
	virtual void dynamicPortalExtraA();
};

class DynamicPortalExtraB
{
public:
	virtual void dynamicPortalExtraB();
};

class BfmeOwnerEBC
{
public:
	void bfmeCallEBC();
};

class DynamicPortalBehaviour : public UpgradeModule,
	public DynamicPortalExtraA,
	public DynamicPortalExtraB
{
protected:
	virtual ~DynamicPortalBehaviour();

private:
	void *m_24[6];
	unsigned char m_3C;
	unsigned char m_3D;
	unsigned char m_pad3E[2];
};

// ??1DynamicPortalBehaviour@@MAE@XZ @0x00460C18
DynamicPortalBehaviour::~DynamicPortalBehaviour()
{
	((BfmeOwnerEBC *)this)->bfmeCallEBC();
}
