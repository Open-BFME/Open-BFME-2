// cl: /O1 /MD
//
// ??1DelayedWeaponSetUpgradeUpdate@@MAE@XZ, retail 0x00488268, 32 bytes.
// Destructor completing the DelayedWeaponSetUpgradeUpdate file-unit (ctor
// rowed at 0x4882E4 in DelayedWeaponSetUpgradeUpdateCtorModuleFactory.cpp).
//
// Donor: BFME1 DelayedWeaponSetUpgradeUpdateDestructor.cpp trivial dtor. The
// body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 plus the UpdateModule middle slots at +0x0C/+0x10
// and the DelayedUpgradeUpdateInterface slot at +0x20 -- then tail-jumps to
// the UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ at
// 0x0024A797). The interface base has a trivial destructor, so it
// contributes a store but no call. The UpdateModule middle is declared but
// never defined here so the call resolves via the pin, and the vtable
// values are DIR32 auto-patches.

class Thing;
class ModuleData;
class Object;

class Module
{
public:
	virtual ~Module();

private:
	unsigned int m_storage[2];
};

class BehaviorModuleInterface
{
public:
	virtual void anchor();
};

class BehaviorModule : public Module, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModuleInterface
{
public:
	virtual void anchor();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	unsigned int m_storage[3];
};

class DelayedUpgradeUpdateInterface
{
public:
	virtual void setDelay();
};

class DelayedWeaponSetUpgradeUpdate : public UpdateModule, public DelayedUpgradeUpdateInterface
{
protected:
	virtual ~DelayedWeaponSetUpgradeUpdate();
};

DelayedWeaponSetUpgradeUpdate::~DelayedWeaponSetUpgradeUpdate()
{
}
