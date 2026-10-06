// cl: /DNDEBUG /MD
//
// StealthUpgrade::upgradeImplementation, retail 0x004B53C5 (13 bytes), and
// StealthUpgrade::upgradeRemovalImplementation, retail 0x004B53D2 (13 bytes): slots 10 and
// 8 of the +0x10 UpgradeMux vtable 0x00C57DE8 installed by the matched StealthUpgrade
// ctor (slot 9 is setUpgradeExecuted, the rowed UpgradeMux::rva00452354).
// Bodies: set and clear object status 0x12 (the Zero Hour OBJECT_STATUS_CAN_STEALTH setStatus
// of StealthUpgrade.cpp, here through the rowed setStatus(ObjectStatusTypes, bool)).
typedef bool Bool;
typedef float Real;
enum ObjectStatusTypes
{
	OBJECT_STATUS_CAN_STEALTH = 0x12
};
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};
class ModuleData;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
template <int N> class StealthUpgradeMuxSlots : public StealthUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class StealthUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public StealthUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class StealthUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void StealthUpgrade::upgradeImplementation()
{
	// The logic that does the stealthupdate will notice this and start stealthing
	Object *me = getObject();
	me->setStatus(OBJECT_STATUS_CAN_STEALTH, true);
}
void StealthUpgrade::upgradeRemovalImplementation()
{
	Object *me = getObject();
	me->setStatus(OBJECT_STATUS_CAN_STEALTH, false);
}
