// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ??0SpecialPowerModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00493C5A,
// 330 bytes. Zero Hour's SpecialPowerModule::SpecialPowerModule (GeneralsMD
// GameLogic/Object/SpecialPower/SpecialPowerModule.cpp), reshaped by BFME 2.
// Target evidence: the body runs the rowed BehaviorModule ctor 0x00253330
// and the implicit ctor of SpecialPowerModuleInterface at +0x10 (vtable
// 0x0084E2B0, every slot _purecall), then stores the vtables the rowed dtor
// 0x00493DEF restores (0x0084E868 primary, slot 0 the rowed
// ??_GSpecialPowerModule 0x004941D7; 0x0085E080 for the interface, whose
// slot 5 is the rowed getPowerName 0x004934B8). Its direct calls on the
// interface subobject land on interface slot 15 (0x0049369D, ZH's slot of
// startPowerRecharge, here taking a ready fraction: ret 4, called with 1.0)
// and slot 9 (0x00492FC2, ZH's pauseCountdown slot; its rowed body is ZH's
// pauseCountdown on the +0x18/+0x1C/+0x20/+0x24 frame, count, paused frame
// and percent members). As in ZH the recharge starts unless the object is
// under construction (status 2) or the template is shared-sync (final
// override +0x59), the module data's +0x0D flag pauses the countdown, and
// a shared-sync public-timer (+0x58) superweapon on a structure (template
// kind-of byte +0x108 bit 7) with a controlling player is added to
// TheInGameUI (slot 0x88, the one before the dtor's removeSuperweapon).
// BFME 2 drops resolveSpecialPower and adds: the module data's +0x61 flag
// makes the power ready now (TheGameLogic frame at +0x40), the flag tests
// are non-zero tests, and the members at +0x14, +0x28, +0x2C, +0x30.
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
#define TRUE true

class Thing;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

enum ObjectID
{
	INVALID_ID = 0
};

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
	Bool hasPublicTimer() const { return getFO()->m_publicTimer; }
	Bool isSharedNSync() const { return getFO()->m_sharedNSync; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	AsciiString m_name;
	char m_pad14[0x58 - 0x14];
	Bool m_publicTimer; // +0x58
	Bool m_sharedNSync; // +0x59
};

class ThingTemplate
{
public:
	Bool isStructure() const { return (m_kindOf108 & 0x80) != 0; }
private:
	char m_pad[0x108];
	unsigned char m_kindOf108; // +0x108
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x54];
	Int m_playerIndex; // +0x54
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	Bool isKindOfStructure() const { return m_template->isStructure(); }
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	char m_pad04[4];
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x08
	char m_pad0C[1];
	Bool m_startsPaused; // +0x0D
	char m_pad0E[0x61 - 0x0E];
	Bool m_readyAtCreation; // +0x61
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
	virtual void addSuperweapon(Int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate);
};

extern InGameUI *TheInGameUI;

class ObjectModule
{
protected:
	virtual ~ObjectModule();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BehaviorModule();
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual AsciiString getPowerName() const = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void pauseCountdown(Bool pause) = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void startPowerRecharge(Real readyFraction) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
	virtual ~SpecialPowerModule();
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual AsciiString getPowerName() const;
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void pauseCountdown(Bool pause);
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void startPowerRecharge(Real readyFraction);
protected:
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)getModuleData(); }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return getSpecialPowerModuleData()->m_specialPowerTemplate; }
private:
	UnsignedInt m_rechargeFrames; // +0x14
	UnsignedInt m_availableOnFrame; // +0x18
	Int m_pausedCount; // +0x1C
	UnsignedInt m_pausedOnFrame; // +0x20
	Real m_pausedPercent; // +0x24
	Bool m_28;
	Int m_2c;
	Bool m_30;
};

SpecialPowerModule::SpecialPowerModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	m_rechargeFrames = 0;
	m_availableOnFrame = 0;
	m_pausedCount = 0;
	m_pausedOnFrame = 0;
	m_pausedPercent = 0.0f;
	m_28 = false;
	m_2c = 0;
	m_30 = false;

	// if we're pre-built, start counting down
	if (!getObject()->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
	{
		//A sharedNSync special only startPowerRecharges when first scienced or when executed,
		//Since a new modue with same SPTemplates may construct at any time.
		if (!getSpecialPowerTemplate()->isSharedNSync())
			startPowerRecharge(1.0f);
	}

	// Some Special powers need to be activated by an Upgrade, so prevent the timer from going until then
	const SpecialPowerModuleData *md = (const SpecialPowerModuleData *)moduleData;
	if (md->m_startsPaused)
		pauseCountdown(TRUE);

	if (md->m_readyAtCreation)
		m_availableOnFrame = TheGameLogic->getFrame();

	// add this weapon to the UI if it has a public timer for all to see
	if (m_pausedCount == 0)
	{
		const SpecialPowerModuleData *data = getSpecialPowerModuleData();
		if (data->m_specialPowerTemplate->isSharedNSync() &&
				data->m_specialPowerTemplate->hasPublicTimer() &&
				getObject()->getControllingPlayer() &&
				getObject()->isKindOfStructure())
		{
			TheInGameUI->addSuperweapon(getObject()->getControllingPlayer()->getPlayerIndex(),
																	getPowerName(),
																	getObject()->getID(),
																	getSpecialPowerModuleData()->m_specialPowerTemplate);
		}
	}
}
