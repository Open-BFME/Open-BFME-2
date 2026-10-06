// cl: /DNDEBUG /MD
//
// MaxHealthUpgrade::upgradeImplementation, retail 0x004B6357 (51 bytes), and
// MaxHealthUpgrade::upgradeRemovalImplementation, retail 0x004B638A (51 bytes):
// slots 10 and 8 of the +0x10 UpgradeMux vtable 0x00C58548 installed by the
// matched MaxHealthUpgrade ctor (slot 9 is setUpgradeExecuted, the rowed
// UpgradeMux::rva00452354). The implementation is the Zero Hour
// MaxHealthUpgrade.cpp body (body module setMaxHealth(getMaxHealth() + add,
// change type)); the removal subtracts. BFME2 layout: body module at
// Object+0x254 with getMaxHealth/setMaxHealth at vslots 6/22, module data
// add +0x118 and change type +0x11C.
typedef bool Bool;
typedef float Real;
enum MaxHealthChangeType
{
	SAME_CURRENTHEALTH = 0
};
template <int N> class MaxHealthUpgradeBodySlots : public MaxHealthUpgradeBodySlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class MaxHealthUpgradeBodySlots<0>
{
};
// BodyModuleInterface (Object +0x254): slot 6 getMaxHealth, slot 22 setMaxHealth.
class BodyModuleInterface : public MaxHealthUpgradeBodySlots<6>
{
public:
	virtual Real getMaxHealth() const = 0;
	virtual void s07() = 0; virtual void s08() = 0; virtual void s09() = 0;
	virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0;
	virtual void s13() = 0; virtual void s14() = 0; virtual void s15() = 0;
	virtual void s16() = 0; virtual void s17() = 0; virtual void s18() = 0;
	virtual void s19() = 0; virtual void s20() = 0; virtual void s21() = 0;
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType) = 0;
};
class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	unsigned char m_pad000[0x254];
	BodyModuleInterface *m_body; // +0x254
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
template <int N> class MaxHealthUpgradeMuxSlots : public MaxHealthUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class MaxHealthUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public MaxHealthUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class MaxHealthUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Real m_addMaxHealth; // +0x118
	MaxHealthChangeType m_maxHealthChangeType; // +0x11C
};
class MaxHealthUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
private:
	const MaxHealthUpgradeModuleData *getMaxHealthUpgradeModuleData() const { return (const MaxHealthUpgradeModuleData *)m_moduleData; }
};
void MaxHealthUpgrade::upgradeImplementation()
{
	const MaxHealthUpgradeModuleData *data = getMaxHealthUpgradeModuleData();

	//Simply add the xp scalar to the xp tracker!
	Object *obj = getObject();

	BodyModuleInterface *body = obj->getBodyModule();
	if (body)
	{
		body->setMaxHealth(body->getMaxHealth() + data->m_addMaxHealth, data->m_maxHealthChangeType);
	}
}
void MaxHealthUpgrade::upgradeRemovalImplementation()
{
	const MaxHealthUpgradeModuleData *data = getMaxHealthUpgradeModuleData();
	Object *obj = getObject();
	BodyModuleInterface *body = obj->getBodyModule();
	if (body)
	{
		body->setMaxHealth(body->getMaxHealth() - data->m_addMaxHealth, data->m_maxHealthChangeType);
	}
}
