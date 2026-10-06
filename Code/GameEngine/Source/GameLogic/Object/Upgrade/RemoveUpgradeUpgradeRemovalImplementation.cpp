// cl: /DNDEBUG /MD
//
// RemoveUpgradeUpgrade::upgradeRemovalImplementation, retail 0x004B7F27 (22
// bytes): slot 8 of the +0x10 UpgradeMux vtable 0x00C58DD8 installed by the
// matched RemoveUpgradeUpgrade dtor: the UpgradeModule condition removal
// 0x004CE4A8, then setUpgradeExecuted(false) (vslot 9).
typedef bool Bool;
class Object;
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
template <int N> class RemoveUpgradeUpgradeMuxSlots : public RemoveUpgradeUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class RemoveUpgradeUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public RemoveUpgradeUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
};
class RemoveUpgradeUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
};
void RemoveUpgradeUpgrade::upgradeRemovalImplementation()
{
	rva004CE4A8();
	setUpgradeExecuted(false);
}
