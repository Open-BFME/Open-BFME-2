// cl: /DNDEBUG /MD
//
// Slot-18 overrides of the two SpecialAbilityUpdate subclasses whose slot-22
// overrides live in SpecialAbilityUpdateSlot22Overrides.cpp (same placeholder
// class names: matched ctors Rva00492179 and Rva00492402; their slot-2 name
// getters return "HeroModeSpecialAbilityUpdate" and
// "WeaponSetSpecialAbilityUpdate"). The SpecialAbilityUpdate vtable
// 0x00C3FBA8 holds the ICF-shared +0x2C clearer 0x004C12CB in slot 18; each
// override clears +0x2C itself and then drops the weapon set flag its slot 22
// raised. Address names.
// Retail 0x0049226C (15 bytes): Rva00492179 clears flag 0x1B.
// Retail 0x0049251D (38 bytes): Rva00492402 clears flag 0x12 or 0x13 for
// module data +0xCC == 1 or 2.
// Rva00492402 also overrides slot 17 (retail 0x004924BA, 31 bytes): the base
// SpecialAbilityUpdate slot 17 (pinned triggerAbilityEffect) and then +0x2C = frame +
// module data +0xC8.

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
class Object
{
public:
	void clearWeaponSetFlag(WeaponSetType wst);
};
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual int update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void triggerAbilityEffect();
protected:
	unsigned char m_pad24[0x2C - 0x24];
	unsigned int m_2C; // +0x2C
	unsigned char m_pad30[0x88 - 0x30];
};
class Rva00492179 : public SpecialAbilityUpdate
{
public:
	virtual void rva0049226C();
};
// ?rva0049226C@Rva00492179@@UAEXXZ @0x0049226C
void Rva00492179::rva0049226C()
{
	m_2C = 0;
	m_object->clearWeaponSetFlag((WeaponSetType)0x1B);
}
class Rva00492402ModuleData
{
public:
	unsigned char m_pad[0xC8];
	unsigned int m_C8; // +0xC8
	int m_CC; // +0xCC
};
class Rva00492402 : public SpecialAbilityUpdate
{
public:
	virtual void rva004924BA();
	virtual void rva0049251D();
};
// ?rva004924BA@Rva00492402@@UAEXXZ @0x004924BA
void Rva00492402::rva004924BA()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const Rva00492402ModuleData *data = (const Rva00492402ModuleData *)m_moduleData;
	m_2C = data->m_C8 + TheGameLogic->getFrame();
}
// ?rva0049251D@Rva00492402@@UAEXXZ @0x0049251D
void Rva00492402::rva0049251D()
{
	m_2C = 0;
	const Rva00492402ModuleData *data = (const Rva00492402ModuleData *)m_moduleData;
	Object *object = m_object;
	if (data->m_CC == 1)
		object->clearWeaponSetFlag((WeaponSetType)0x12);
	else if (data->m_CC == 2)
		object->clearWeaponSetFlag((WeaponSetType)0x13);
}
