// cl: /O1 /DNDEBUG /MD
//
// DelayedUpgrade::upgradeImplementation, retail 0x004B3CC2 (121 bytes): slot
// 10 of the +0x10 UpgradeMux vtable 0x00C572E0 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). Builds two cleared
// 0x80-byte upgrade masks (the rowed Rva001EAE6FHelper::clear80), has mux
// slot 11 fill them (the activation masks, Zero Hour's
// getUpgradeActivationMasks), then walks the Object's null-terminated
// behavior-module list (+0x244): each module's upgrade interface (its +0x0C
// interface slot 21) that answers the first mask (slot 0) gets the module
// data's +0x118 delay (slot 1).
typedef bool Bool;
class ModuleData;
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
private:
	unsigned char m_bytes[0x80];
};
class Rva004B3CC2Upgrade
{
public:
	virtual Bool rvaSlot0(const Rva001EAE6FHelper *mask) = 0;
	virtual void rvaSlot1(int delay) = 0;
};
template <int N> class Rva004B3CC2Slots : public Rva004B3CC2Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva004B3CC2Slots<0>
{
};
class BehaviorModuleInterface : public Rva004B3CC2Slots<21>
{
public:
	virtual Rva004B3CC2Upgrade *rvaSlot21();
};
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	BehaviorModuleInterface *getInterface() { return &m_interface; }
private:
	unsigned char m_pad04[0x0C - 0x04];
	BehaviorModuleInterface m_interface;	// +0x0C
};
class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors;		// +0x244
};
struct DelayedUpgradeModuleData
{
	unsigned char m_pad00[0x118];
	int m_delay;				// +0x118
};
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
class UpgradeMuxIface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual void m02() = 0;
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
	virtual void getUpgradeActivationMasks(Rva001EAE6FHelper *activation, Rva001EAE6FHelper *conflicting) = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class DelayedUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeImplementation();
};
void DelayedUpgrade::upgradeImplementation()
{
	int delay = ((const DelayedUpgradeModuleData *)m_moduleData)->m_delay;
	Object *obj = m_object;
	Rva001EAE6FHelper activation;
	Rva001EAE6FHelper conflicting;
	activation.clear80();
	conflicting.clear80();
	getUpgradeActivationMasks(&activation, &conflicting);
	for (BehaviorModule **module = obj->getBehaviorModules(); *module; ++module)
	{
		Rva004B3CC2Upgrade *upgrade = (*module)->getInterface()->rvaSlot21();
		if (upgrade && upgrade->rvaSlot0(&activation))
			upgrade->rvaSlot1(delay);
	}
}
