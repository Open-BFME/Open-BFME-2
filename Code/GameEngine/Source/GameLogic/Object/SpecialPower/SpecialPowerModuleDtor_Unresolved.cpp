// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Split from SpecialPowerModuleDtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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


#include "../../../../Include/Common/Overridable.h"

#include "../../../../Include/Common/SpecialPower.h"

#include "../../../../Include/Common/Player.h"

enum ObjectID { INVALID_ID = 0 };

#include "../../../../Include/GameLogic/Module/Rva002AC6B1PlayerTimers.h"

enum KindOfType { KINDOF_STRUCTURE = 7 };

#include "../../../../Include/Common/ThingTemplate.h"
// The view's inline kind test: a byte test on the canonical +0x108 mask.
static __forceinline bool thingTemplateIsKindOf(const ThingTemplate *tmpl, KindOfType t)
{
	return (((const unsigned char *)tmpl->m_kindof)[t >> 3] & (1 << (t & 7))) != 0;
}

class Object
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	__declspec(dllimport) __forceinline bool isKindOf(KindOfType t) const { return thingTemplateIsKindOf(m_template, t); }
private:
	void *m_vptr;
	const ThingTemplate *m_template;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct SpecialPowerCreationFrameView { char m_pad[0x40]; unsigned int m_frame; };

#include "../../../../Include/Common/ModuleData.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"


#include "../../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// Retail's BehaviorModule destructor is inline and empty: ~SpecialPowerModule restores
// BehaviorModule's 0x00BEEA7C at +0 and 0x00BEE9C0 at +0x0C before ~ObjectModule. The
// canonical header only declares it, so this unit supplies the body its destructor expands
// (as FXListDie.cpp does); the out-of-line copy is 0x004607E1 (??1BehaviorModule@@MAE@XZ).
inline BehaviorModule::~BehaviorModule()
{
}

#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	// BehaviorModuleInterface slot 8 of the table 0x00BEFCF8 this destructor restores at +0x0C:
	// retail 0x002533D3, the +0x10 interface (inline, the COMDAT SpecialPowerModuleCtor.cpp emits)
	virtual SpecialPowerModuleInterface *getSpecialPower() { return this; }
	virtual ~SpecialPowerModule();
	virtual AsciiString getPowerName() const;
	virtual void onSpecialPowerCreation();
	virtual void pauseCountdown(bool pause);
	virtual void startPowerRecharge(float percent);
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

