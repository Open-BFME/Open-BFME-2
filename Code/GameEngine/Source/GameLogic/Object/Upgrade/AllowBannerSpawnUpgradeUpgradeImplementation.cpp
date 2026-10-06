// cl: /DNDEBUG /MD
//
// AllowBannerSpawnUpgrade::upgradeImplementation, retail 0x004B8510 (8 bytes),
// and upgradeRemovalImplementation, retail 0x004B8518 (8 bytes): slots 10 and 8
// of the +0x10 UpgradeMux vtable 0x00C58FE8 installed by the matched
// AllowBannerSpawnUpgrade ctor; each only runs the UpgradeModule condition
// apply 0x004CE4A0 / removal 0x004CE4A8 on the module base (tail jumps).
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
template <int N> class AllowBannerSpawnUpgradeMuxSlots : public AllowBannerSpawnUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AllowBannerSpawnUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public AllowBannerSpawnUpgradeMuxSlots<8>
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
class AllowBannerSpawnUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void AllowBannerSpawnUpgrade::upgradeImplementation()
{
	rva004CE4A0();
}
void AllowBannerSpawnUpgrade::upgradeRemovalImplementation()
{
	rva004CE4A8();
}
