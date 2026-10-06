// cl: /DNDEBUG /MD
//
// LocomotorSetUpgrade::upgradeImplementation, retail 0x004B3F58 (35 bytes), and
// LocomotorSetUpgrade::upgradeRemovalImplementation, retail 0x004B3F7B (21 bytes): slots 10 and
// 8 of the +0x10 UpgradeMux vtable 0x00C574E8 installed by the matched LocomotorSetUpgrade
// ctor (slot 9 is setUpgradeExecuted, the rowed UpgradeMux::rva00452354).
// Bodies: the Zero Hour LocomotorSetUpgrade.cpp setLocomotorUpgrade call on the
// object's AI (rowed AIUpdateInterface::rva00262804); BFME2 passes whether the
// module data byte +0x118 is clear, and the removal passes 0.
typedef bool Bool;
typedef float Real;
class AIUpdateInterface
{
public:
	void rva00262804(unsigned char upgraded);
};
class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
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
template <int N> class LocomotorSetUpgradeMuxSlots : public LocomotorSetUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class LocomotorSetUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public LocomotorSetUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class LocomotorSetUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Bool m_118; // +0x118
};
class LocomotorSetUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void LocomotorSetUpgrade::upgradeImplementation()
{
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
		ai->rva00262804(((const LocomotorSetUpgradeModuleData *)m_moduleData)->m_118 == 0);
}
void LocomotorSetUpgrade::upgradeRemovalImplementation()
{
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
		ai->rva00262804(0);
}
