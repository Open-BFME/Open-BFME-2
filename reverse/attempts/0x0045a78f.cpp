// ??0AutoAbilityBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /O1 /arch:SSE /G7
//
// ??0AutoAbilityBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0045A78F, 303 bytes. BFME 2's AutoAbilityBehavior constructor; BFME 1's
// (open-bfme-1 game/.../AutoAbilityBehaviorConstructor.cpp) only empties the
// +0x20 command string and sleeps forever. Target evidence: the body runs
// the rowed UpdateModule ctor 0x00253390, stores the three vtables the
// rowed dtor 0x0045A37F restores (0x00C4175C, 0x00BEFF90, 0x00C41750),
// null-constructs the +0x20 AsciiString, zeroes the floats at +0x24..+0x2C
// and the flag at +0x30. When the module data's +0x5C flag is set it looks
// up the data's +0x18 special power through the rowed
// SpecialPowerStore::findSpecialPowerTemplate 0x0029B6EB, finds the object's
// command set (rowed Object string getter 0x00290E67 and TheControlBar's
// rowed lookup 0x0031D5F8) and hands the first of its 0x20 buttons
// (rowed CommandSet::getCommandButton 0x00409EE8) whose command type is
// 0x18 and whose special power has the same +0x1C type and +0x10 name (both
// through the final override, rowed 0x00288609) to the rowed selector
// 0x0045A6FE. Otherwise it clears through the rowed 0x0045A413 and sleeps
// forever, as BFME 1 does.
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum
{
	MAX_COMMANDS_PER_SET = 0x20
};

enum GUICommandType
{
	GUI_COMMAND_SPECIAL_POWER_BFME = 0x18
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
private:
	unsigned char m_pad00[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	const AsciiString &getName() const { return getFO()->m_name; }
	Int getSpecialPowerType() const { return getFO()->m_type; }
	AsciiString m_name; // +0x10
	unsigned char m_pad14[0x1C - 0x14];
	Int m_type; // +0x1C
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
private:
	unsigned char m_pad00[0x14];
	GUICommandType m_command; // +0x14
	unsigned char m_pad18[0x44 - 0x18];
	const SpecialPowerTemplate *m_specialPower; // +0x44
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class ControlBar;
extern ControlBar *TheControlBar;

// TheControlBar's command-set lookup at 0x0031D5F8, rowed under an address
// name.
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class AutoAbilityBehaviorModuleData
{
public:
	unsigned char m_pad00[0x18];
	AsciiString m_specialPowerName; // +0x18
	unsigned char m_pad1C[0x5C - 0x1C];
	Bool m_startsActive; // +0x5C
};

class AutoAbilityBehavior : public UpdateModule
{
public:
	AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoAbilityBehavior();
	void rva0045A413();
	void rva0045A6FE(void *button);
private:
	const AutoAbilityBehaviorModuleData *getAutoAbilityBehaviorModuleData() const { return (const AutoAbilityBehaviorModuleData *)m_moduleData; }

	AsciiString m_command; // +0x20
	Real m_24;
	Real m_28;
	Real m_2c;
	Bool m_30;
};

AutoAbilityBehavior::AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_24(0.0f)
	, m_28(0.0f)
	, m_2c(0.0f)
	, m_30(false)
{
	const AutoAbilityBehaviorModuleData *data = getAutoAbilityBehaviorModuleData();
	if (data->m_startsActive)
	{
		Object *obj = getObject();
		const SpecialPowerTemplate *spTemplate = TheSpecialPowerStore->findSpecialPowerTemplate(data->m_specialPowerName);
		const AsciiString &spName = spTemplate->getName();
		const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
		for (Int i = 0; i < MAX_COMMANDS_PER_SET; i++)
		{
			const CommandButton *button = commandSet->getCommandButton(i);
			if (button == NULL || button->getCommandType() != GUI_COMMAND_SPECIAL_POWER_BFME)
				continue;
			const SpecialPowerTemplate *buttonTemplate = button->getSpecialPowerTemplate()->getFO();
			if (buttonTemplate->m_type != spTemplate->getFO()->m_type)
				continue;
			if (button->getSpecialPowerTemplate()->getName() == spName)
			{
				rva0045A6FE((void *)button);
				break;
			}
		}
	}
	else
	{
		rva0045A413();
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	}
}
