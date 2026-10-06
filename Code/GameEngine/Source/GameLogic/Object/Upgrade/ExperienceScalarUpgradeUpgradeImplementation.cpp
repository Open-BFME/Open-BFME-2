// cl: /DNDEBUG /MD
//
// ExperienceScalarUpgrade::upgradeImplementation, retail 0x004B6213 (35 bytes), and
// ExperienceScalarUpgrade::upgradeRemovalImplementation, retail 0x004B6236 (35 bytes): slots 10 and
// 8 of the +0x10 UpgradeMux vtable 0x00C584A0 installed by the matched ExperienceScalarUpgrade
// ctor (slot 9 is setUpgradeExecuted, the rowed UpgradeMux::rva00452354).
// Bodies: the Zero Hour ExperienceScalarUpgrade.cpp body adding the module data scalar
// (+0x118) to the experience tracker's scalar (Object+0x264, tracker +0x1C);
// the removal subtracts it.
typedef bool Bool;
typedef float Real;
class ExperienceTracker
{
public:
	Real getExperienceScalar() const { return m_experienceScalar; }
	void setExperienceScalar(Real scalar) { m_experienceScalar = scalar; }
private:
	unsigned char m_pad00[0x1C];
	Real m_experienceScalar; // +0x1C
};
class Object
{
public:
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	unsigned char m_pad000[0x264];
	ExperienceTracker *m_experienceTracker; // +0x264
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
template <int N> class ExperienceScalarUpgradeMuxSlots : public ExperienceScalarUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ExperienceScalarUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public ExperienceScalarUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class ExperienceScalarUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Real m_addXPScalar; // +0x118
};
class ExperienceScalarUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
private:
	const ExperienceScalarUpgradeModuleData *getExperienceScalarUpgradeModuleData() const { return (const ExperienceScalarUpgradeModuleData *)m_moduleData; }
};
void ExperienceScalarUpgrade::upgradeImplementation()
{
	//Grant the experience scalar bonus
	Object *obj = getObject();
	ExperienceTracker *xpTracker = obj->getExperienceTracker();
	if (xpTracker)
	{
		Real scalar = xpTracker->getExperienceScalar() + getExperienceScalarUpgradeModuleData()->m_addXPScalar;
		xpTracker->setExperienceScalar(scalar);
	}
}
void ExperienceScalarUpgrade::upgradeRemovalImplementation()
{
	Object *obj = getObject();
	ExperienceTracker *xpTracker = obj->getExperienceTracker();
	if (xpTracker)
	{
		Real scalar = xpTracker->getExperienceScalar() - getExperienceScalarUpgradeModuleData()->m_addXPScalar;
		xpTracker->setExperienceScalar(scalar);
	}
}
