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
//
// ?onSpecialPowerCreation@SpecialPowerModule@@UAEXXZ, retail 0x004933C2,
// 246 bytes: SpecialPowerModuleInterface slot 7 in every SpecialPowerModule
// family vftable (e.g. 0x0085C4B8), reached on the +0x10 subobject. Name and
// outline from the Zero Hour body; it is the mirror of the dtor above
// (TheInGameUI slot 0x88 addSuperweapon beside slot 0x8C removeSuperweapon).
// Target evidence: startPowerRecharge(1.0) through slot 15; for a template
// whose final override has the shared flag at +0x59 the controlling player
// gets the rowed timer pair 0x002AC75C (template, frame) / 0x002AC7A0, the
// latter stored at +0x18; module data +0x0D pauses through slot 9 (pinned
// pauseCountdown 0x00492FC2); the superweapon is added only for a structure
// (template KindOf 7, the donor's KINDOF_STRUCTURE, tested inline at +0x108).
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
	bool isSharedNSync() const { return getFO()->m_sharedNSync; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	AsciiString m_name;
	char m_pad14[0x58 - 0x14];
	bool m_publicTimer;
	bool m_sharedNSync;
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

class Rva002AC6B1PlayerTimers
{
public:
	void rva002AC75C(const SpecialPowerTemplate *temp, unsigned int frame);
	unsigned int getOrStart(const SpecialPowerTemplate *temp);
};

enum KindOfType { KINDOF_STRUCTURE = 7 };

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	__forceinline bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
private:
	void *m_vptr;
	const ThingTemplate *m_template;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct SpecialPowerCreationFrameView { char m_pad[0x40]; unsigned int m_frame; };

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
	bool m_updateModuleStartsAttack;
	bool m_startsPaused;
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
	virtual void v32(); virtual void v33();
	virtual void addSuperweapon(int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate);
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
	virtual void s00() = 0; virtual void s01() = 0; virtual void s02() = 0;
	virtual void s03() = 0; virtual void s04() = 0;
	virtual AsciiString getPowerName() const = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void onSpecialPowerCreation() = 0;
	virtual void s08() = 0;
	virtual void pauseCountdown(bool pause) = 0;
	virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0;
	virtual void s13() = 0; virtual void s14() = 0;
	virtual void startPowerRecharge(float percent) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual ~SpecialPowerModule();
	virtual AsciiString getPowerName() const;
	virtual void onSpecialPowerCreation();
protected:
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)getModuleData(); }
private:
	int m_unknown14;
	unsigned int m_availableOnFrame;
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

void SpecialPowerModule::onSpecialPowerCreation()
{
	startPowerRecharge(1.0f);

	if (getSpecialPowerTemplate()->isSharedNSync())
	{
		Player *player = getObject()->getControllingPlayer();
		if (player)
		{
			((Rva002AC6B1PlayerTimers *)player)->rva002AC75C(getSpecialPowerTemplate(), ((SpecialPowerCreationFrameView *)TheGameLogic)->m_frame);
			m_availableOnFrame = ((Rva002AC6B1PlayerTimers *)player)->getOrStart(getSpecialPowerTemplate());
		}
	}

	const SpecialPowerModuleData *md = getSpecialPowerModuleData();
	if (md->m_startsPaused)
		pauseCountdown(true);

	if (getSpecialPowerModuleData()->m_specialPowerTemplate->hasPublicTimer() &&
			getObject()->getControllingPlayer() &&
			getObject()->isKindOf(KINDOF_STRUCTURE))
	{
		TheInGameUI->addSuperweapon(getObject()->getControllingPlayer()->getPlayerIndex(),
									getPowerName(),
									getObject()->getID(),
									getSpecialPowerModuleData()->m_specialPowerTemplate);
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00493DEF@@UAE@XZ=??1SpecialPowerModule@@UAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorAnchor@BehaviorModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
