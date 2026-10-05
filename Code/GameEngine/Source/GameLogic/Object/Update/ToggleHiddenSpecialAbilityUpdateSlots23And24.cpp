// cl: /O1 /DNDEBUG /MD /EHsc
//
// Slots 23 and 24 of ToggleHiddenSpecialAbilityUpdate's vftable 0x00C552D8
// (installed by the matched ctor 0x004AE16E). The class's matched slot-17
// override 0x004AE22D (ToggleSpecialAbilityUpdateSlot17.cpp) tail-calls
// slot 23 when the owner has status 0x10 and slot 24 otherwise; these rows
// keep that unit's address names. Method identities are not established.
//
// ?rva004AE2D0@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ, retail 0x004AE2D0,
// 196 bytes: with status 0x10 set on the owner, clears it, clears condition
// bit 8*32+3 (notifying through the rowed Object::rva0028AE6D), clears
// weapon-set flag 0x3D, passes false to slot 9 of the owner's special power
// module for the module data's +0x38 template (pinned
// Object::getSpecialPowerModule 0x0028BB9E), and false to the owner's
// "InvisibilityUpdate" module (found by its cached name key) through
// 0x004A39D0.
//
// ?rva004AE394@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ, retail 0x004AE394,
// 279 bytes: the reverse, only when the +0x20 interface's slot 8 answers
// true for a null argument, the owner lacks status 0x10 and has an AI
// (Object+0x258): passes true to the special power module's slot 9, idles
// the AI (CMD_FROM_AI) on the rowed Object gate rva0028B7C8 (filed as int,
// retail tests AL) or the AI's slot 111, stamps TheGameLogic+0x40 into +0x88,
// sets status 0x10, weapon-set flag 0x3D and condition bit 8*32+3, and passes
// true to the InvisibilityUpdate module.

class ModuleData;
class Module;
class SpecialPowerTemplate;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_40; // +0x40
};

extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

template <int N> class Rva004AE2D0Slots : public Rva004AE2D0Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004AE2D0Slots<0>
{
};

class SpecialPowerModuleInterface : public Rva004AE2D0Slots<9>
{
public:
	virtual void rva004AE2D0Slot9(bool on) = 0;
};

class InvisibilityUpdate
{
public:
	void rva004A39D0(bool on);
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterfaceSlots : public Rva004AE2D0Slots<111>
{
public:
	virtual bool rva004AE394Slot111() = 0;
};

class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command; // +0x20
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
	friend class ToggleHiddenSpecialAbilityUpdate;
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *t) const;
	int rva0028B7C8() const;
	void rva0028AE6D();
protected:
	Module *findModule(NameKeyType key) const;
public:
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};

static const int HIDDEN_CONDITION_BIT = 8 * 32 + 3;
static const ObjectStatusTypes HIDDEN_STATUS = (ObjectStatusTypes)0x10;
static const WeaponSetType HIDDEN_WEAPONSET = (WeaponSetType)0x3D;

struct ToggleHiddenSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0x38];
	const SpecialPowerTemplate *m_38; // +0x38
};

class SpecialPowerUpdateInterface : public Rva004AE2D0Slots<8>
{
public:
	virtual bool rva004AE394Slot8(const void *button) = 0;
};

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class ToggleHiddenSpecialAbilityUpdate : public UpdateModuleView, public SpecialPowerUpdateInterface
{
public:
	virtual void rva004AE2D0();
	virtual void rva004AE394();
private:
	unsigned char m_pad24[0x88 - 0x24];
	unsigned int m_88; // +0x88
};

// ?rva004AE2D0@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ @0x004AE2D0
void ToggleHiddenSpecialAbilityUpdate::rva004AE2D0()
{
	Object *obj = m_object;
	if (!obj || !obj->testStatus(HIDDEN_STATUS))
		return;

	obj->setStatus(HIDDEN_STATUS, false);
	if (obj->m_conditionBits.test(HIDDEN_CONDITION_BIT))
	{
		obj->m_conditionBits.clear(HIDDEN_CONDITION_BIT);
		obj->rva0028AE6D();
	}
	obj->clearWeaponSetFlag(HIDDEN_WEAPONSET);

	const ToggleHiddenSpecialAbilityUpdateModuleData *data = (const ToggleHiddenSpecialAbilityUpdateModuleData *)m_moduleData;
	SpecialPowerModuleInterface *power = obj->getSpecialPowerModule(data->m_38);
	if (power)
		power->rva004AE2D0Slot9(false);

	static NameKeyType key_InvisibilityUpdate = TheNameKeyGenerator->nameToKey("InvisibilityUpdate");
	InvisibilityUpdate *invisibility = (InvisibilityUpdate *)obj->findModule(key_InvisibilityUpdate);
	if (invisibility)
		invisibility->rva004A39D0(false);
}

// ?rva004AE394@ToggleHiddenSpecialAbilityUpdate@@UAEXXZ @0x004AE394
void ToggleHiddenSpecialAbilityUpdate::rva004AE394()
{
	if (!rva004AE394Slot8(0))
		return;
	Object *obj = m_object;
	if (!obj || obj->testStatus(HIDDEN_STATUS))
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return;

	const ToggleHiddenSpecialAbilityUpdateModuleData *data = (const ToggleHiddenSpecialAbilityUpdateModuleData *)m_moduleData;
	SpecialPowerModuleInterface *power = obj->getSpecialPowerModule(data->m_38);
	if (power)
		power->rva004AE2D0Slot9(true);

	if ((char)obj->rva0028B7C8() || ai->rva004AE394Slot111())
		ai->m_command.aiIdle(CMD_FROM_AI);

	m_88 = TheGameLogic->m_40;
	obj->setStatus(HIDDEN_STATUS, true);
	obj->setWeaponSetFlag(HIDDEN_WEAPONSET);
	if (!obj->m_conditionBits.test(HIDDEN_CONDITION_BIT))
	{
		obj->m_conditionBits.set(HIDDEN_CONDITION_BIT);
		obj->rva0028AE6D();
	}

	static NameKeyType key_InvisibilityUpdate = TheNameKeyGenerator->nameToKey("InvisibilityUpdate");
	InvisibilityUpdate *invisibility = (InvisibilityUpdate *)obj->findModule(key_InvisibilityUpdate);
	if (invisibility)
		invisibility->rva004A39D0(true);
}
