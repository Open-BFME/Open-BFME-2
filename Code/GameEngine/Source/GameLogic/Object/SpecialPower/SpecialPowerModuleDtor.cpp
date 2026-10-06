// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1SpecialPowerModule@@UAE@XZ, retail 0x00493DEF, 184 bytes (pinned; rowed
// deleting wrapper 0x004941D7), and
// ?getPowerName@SpecialPowerModule@@UBE?AVAsciiString@@XZ, retail
// 0x004934B8, 38 bytes (called from the dtor at 0x00493E41 and at
// 0x00493D4E, both on the +0x10 SpecialPowerModuleInterface subobject).
// Both bodies are the Zero Hour SpecialPowerModule.cpp ones: the dtor
// removes the superweapon timer from TheInGameUI (virtual slot 0x8C) when
// the template has a public timer and the object has a controlling player;
// getPowerName returns the template's name. BFME2 deltas (target evidence):
// the public-timer flag is tested for non-zero rather than == TRUE, the
// template's final override (rowed Overridable::friend_getFinalOverride)
// holds the name at +0x10 and the flag at +0x58, and the BehaviorModule
// base dtor is inline here (vtables 0x00BEEA7C/0x00BEE9C0 restored before
// ObjectModule's dtor 0x0049B47C). Retail's unwind map destroys that base
// (0x004607E1) in state 0 and the getPowerName temporary in state 1.
#include "ascii_string.h"


class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
private:
	char m_pad[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return getFO()->m_name; }
	bool hasPublicTimer() const { return getFO()->m_publicTimer; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	AsciiString m_name;
	char m_pad14[0x58 - 0x14];
	bool m_publicTimer;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x54];
	int m_playerIndex;
};

enum ObjectID { INVALID_ID = 0 };

class Object
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
private:
	char m_pad[0x74];
	ObjectID m_id;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	char m_pad04[4];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34();
	virtual void removeSuperweapon(int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate);
};

extern InGameUI *TheInGameUI;

class ObjectModule
{
protected:
	virtual ~ObjectModule();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class SpecialPowerModuleInterface
{
public:
	virtual AsciiString getPowerName() const = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual ~SpecialPowerModule();
	virtual AsciiString getPowerName() const;
protected:
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)getModuleData(); }
};

SpecialPowerModule::~SpecialPowerModule()
{
	if (getSpecialPowerModuleData()->m_specialPowerTemplate->hasPublicTimer() &&
			getObject()->getControllingPlayer())
		TheInGameUI->removeSuperweapon(getObject()->getControllingPlayer()->getPlayerIndex(),
										getPowerName(),
										getObject()->getID(),
										getSpecialPowerModuleData()->m_specialPowerTemplate);
}

AsciiString SpecialPowerModule::getPowerName() const
{
	return getSpecialPowerModuleData()->m_specialPowerTemplate->getName();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00493DEF@@UAE@XZ=??1SpecialPowerModule@@UAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorAnchor@BehaviorModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
