// cl: /DNDEBUG /MD
//
// WeaponBonusUpgrade::upgradeImplementation, retail 0x004B5680 (11 bytes): slot
// 10 of the +0x10 UpgradeMux vtable 0x00C57F20 installed by the matched
// WeaponBonusUpgrade ctor (slot 8 is the shared empty body). The Zero Hour
// WeaponBonusUpgrade.cpp body sets WEAPONBONUSCONDITION_PLAYER_UPGRADE on the
// object; in BFME2 the null check is gone and the setter is just the or of
// bit 5 into the weapon bonus condition word at Object+0x380.
typedef bool Bool;
enum WeaponBonusConditionType
{
	WEAPONBONUSCONDITION_PLAYER_UPGRADE = 5
};
class Object
{
public:
	void setWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition |= (1 << wst); }
private:
	unsigned char m_pad000[0x380];
	unsigned int m_weaponBonusCondition; // +0x380
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
template <int N> class WeaponBonusUpgradeMuxSlots : public WeaponBonusUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class WeaponBonusUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public WeaponBonusUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class WeaponBonusUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeImplementation();
};
void WeaponBonusUpgrade::upgradeImplementation()
{
	// Very simple; just need to flag the Object as having the player upgrade, and the WeaponSet chooser
	// will do the work of picking the right one from ini.
	Object *obj = getObject();
	obj->setWeaponBonusCondition(WEAPONBONUSCONDITION_PLAYER_UPGRADE);
}
