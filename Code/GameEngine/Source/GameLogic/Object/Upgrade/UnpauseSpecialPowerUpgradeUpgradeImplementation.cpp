// cl: /DNDEBUG /MD
//
// UnpauseSpecialPowerUpgrade::upgradeImplementation, retail 0x004B54E9 (102
// bytes), and upgradeRemovalImplementation, retail 0x004B5574 (84 bytes): slots
// 10 and 8 of the +0x10 UpgradeMux vtable 0x00C57E60 installed by the matched
// UnpauseSpecialPowerUpgrade ctor. The Zero Hour body unpauses the special
// power module whose template is the module data one (+0x118); BFME2 walks
// every behavior module (Object+0x244, getSpecialPower at interface vslot 8)
// instead of stopping at the first, and unless the +0x11C flag is set also
// stamps the current frame through special power vslot 8. The removal, guarded
// by UpgradeMux vslot 0, pauses the same modules again.
typedef bool Bool;
typedef unsigned int UnsignedInt;
#define FALSE false
#define TRUE true
class SpecialPowerTemplate;
class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void s07() = 0;
	virtual void setReadyFrame(UnsignedInt frame) = 0;
	virtual void pauseCountdown(Bool pause) = 0;
};
class BehaviorModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual SpecialPowerModuleInterface *getSpecialPower();
};
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	BehaviorModuleInterface *getBehaviorModuleInterface() { return &m_interface; }
private:
	unsigned char m_pad04[0x0C - 0x04];
	BehaviorModuleInterface m_interface; // +0x0C
};
class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors; // +0x244
};
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
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
template <int N> class UnpauseSpecialPowerUpgradeMuxSlots : public UnpauseSpecialPowerUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class UnpauseSpecialPowerUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface : public UnpauseSpecialPowerUpgradeMuxSlots<0>
{
protected:
	virtual Bool slot00() const = 0;
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class UnpauseSpecialPowerUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	const SpecialPowerTemplate *m_specialPower; // +0x118
	Bool m_11C; // +0x11C
};
class UnpauseSpecialPowerUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
private:
	const UnpauseSpecialPowerUpgradeModuleData *getUnpauseSpecialPowerUpgradeModuleData() const { return (const UnpauseSpecialPowerUpgradeModuleData *)m_moduleData; }
};
void UnpauseSpecialPowerUpgrade::upgradeImplementation()
{
	for (BehaviorModule **m = getObject()->getBehaviorModules(); *m; ++m)
	{
		SpecialPowerModuleInterface *sp = (*m)->getBehaviorModuleInterface()->getSpecialPower();
		if (!sp)
			continue;
		const SpecialPowerTemplate *tmpl = sp->getSpecialPowerTemplate();
		if (tmpl != getUnpauseSpecialPowerUpgradeModuleData()->m_specialPower)
			continue;
		sp->pauseCountdown(FALSE);
		if (!getUnpauseSpecialPowerUpgradeModuleData()->m_11C)
			sp->setReadyFrame(TheGameLogic->getFrame());
	}
}
void UnpauseSpecialPowerUpgrade::upgradeRemovalImplementation()
{
	if (!slot00())
		return;
	for (BehaviorModule **m = getObject()->getBehaviorModules(); *m; ++m)
	{
		SpecialPowerModuleInterface *sp = (*m)->getBehaviorModuleInterface()->getSpecialPower();
		if (!sp)
			continue;
		if (sp->getSpecialPowerTemplate() != getUnpauseSpecialPowerUpgradeModuleData()->m_specialPower)
			continue;
		sp->pauseCountdown(TRUE);
	}
}
