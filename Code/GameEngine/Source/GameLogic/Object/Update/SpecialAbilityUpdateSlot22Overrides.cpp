// cl: /DNDEBUG /MD
//
// Slot-22 overrides of two SpecialAbilityUpdate subclasses whose classes are
// rowed only under placeholder names (matched ctors Rva00492179 0x00492179 and
// Rva00492402 0x00492402). Their primary vtables 0x00C4DEF8 and 0x00C4DFF8
// hold these bodies in slot 22, where the SpecialAbilityUpdate vtable 0x00C3FBA8
// holds 0x004508B7 (also inherited by ArrowStormUpdate), the base slot each
// override calls first (pinned as ?rva004508B7@SpecialAbilityUpdate@@UAEXXZ).
// Slot names are not established, hence address names.
// Retail 0x00492231 (59 bytes): Rva00492179 sets weapon set flag 0x1B when the
// matched Object::rva0029091E gate passes, then stores frame + data +0xCC at
// +0x2C. Retail 0x004924D9 (68 bytes): Rva00492402 sets weapon set flag 0x12 or
// 0x13 for data +0xCC == 1 or 2, then stores frame + data +0xC8 + data +0x88.
// SpecialAbilityUpdate layout as in GloriousChargeUpdateUpdate.cpp.

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
class Object
{
public:
	void setWeaponSetFlag(WeaponSetType wst);
	bool rva0029091E(unsigned int i) const;
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
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void rva004508B7();
protected:
	unsigned char m_pad24[0x2C - 0x24];
	unsigned int m_2C; // +0x2C
	unsigned char m_pad30[0x88 - 0x30];
};
class Rva00492179ModuleData
{
public:
	unsigned char m_pad[0xCC];
	unsigned int m_CC; // +0xCC
};
class Rva00492179 : public SpecialAbilityUpdate
{
public:
	virtual void rva00492231();
};
void Rva00492179::rva00492231()
{
	SpecialAbilityUpdate::rva004508B7();
	Object *object = m_object;
	const Rva00492179ModuleData *data = (const Rva00492179ModuleData *)m_moduleData;
	if (object->rva0029091E(0x1B))
		object->setWeaponSetFlag((WeaponSetType)0x1B);
	m_2C = TheGameLogic->getFrame() + data->m_CC;
}
class Rva00492402ModuleData
{
public:
	unsigned char m_pad[0x88];
	unsigned int m_88; // +0x88
	unsigned char m_pad8C[0xC8 - 0x8C];
	unsigned int m_C8; // +0xC8
	int m_CC; // +0xCC
};
class Rva00492402 : public SpecialAbilityUpdate
{
public:
	virtual void rva004924D9();
};
void Rva00492402::rva004924D9()
{
	SpecialAbilityUpdate::rva004508B7();
	const Rva00492402ModuleData *data = (const Rva00492402ModuleData *)m_moduleData;
	Object *object = m_object;
	if (data->m_CC == 1)
		object->setWeaponSetFlag((WeaponSetType)0x12);
	else if (data->m_CC == 2)
		object->setWeaponSetFlag((WeaponSetType)0x13);
	m_2C = TheGameLogic->getFrame() + data->m_C8 + data->m_88;
}
