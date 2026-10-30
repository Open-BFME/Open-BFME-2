// cl: /DNDEBUG /MD
//
// ?rva004C69FA@WoundArrowUpdate@@UAE_NH@Z, retail 0x004C69FA, 38 bytes: slot 8
// of the vtable 0x00C5DEDC that WoundArrowUpdate's ctors (0x004C6929,
// 0x004C6957) install at +0x20. False when bit 0 of the module data's +0xCC
// byte is set and the owner Object is KindOf 0xD6 (rowed Object::isKindOf);
// true otherwise. The argument is unread. Compiled with the +0x20 subobject
// this. Names by address.
enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum KindOfType
{
	KINDOF_INVALID = -1
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
};

class MultiIniFieldParse;

class __declspec(novtable) SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0xC4 bytes); only the 0xC8 size matters.
	unsigned char m_opaque[0xC4];
};

class __declspec(novtable) WoundArrowUpdateModuleData : public SpecialAbilityUpdateModuleData
{
	friend class WoundArrowUpdate;
public:
	WoundArrowUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 cap value.
	float m_capC8;
	// +0xCC cleared word (ends at the rowed 0xD0 instance size).
	unsigned int m_wordCC;
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };

class Xfer;
template <int N> class BitFlags;

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual BitFlags<13> getDisabledTypesToProcess() const = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual BitFlags<13> getDisabledTypesToProcess() const;
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class WoundArrowUpdateInterface
{
public:
	virtual void slot0() = 0; virtual void slot1() = 0; virtual void slot2() = 0; virtual void slot3() = 0;
	virtual void slot4() = 0; virtual void slot5() = 0; virtual void slot6() = 0; virtual void slot7() = 0;
	virtual bool rva004C69FA(int unused) = 0;
};

class SpecialAbilityUpdate : public UpdateModule, public WoundArrowUpdateInterface
{
public:
	SpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SpecialAbilityUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void s12();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void onExit(bool a, bool b);	// slot 13 (+0x34), 0x004502CE
public:
	virtual void s14(); virtual void s15(); virtual void s16();
	virtual void triggerAbilityEffect();	// slot 17
protected:
	unsigned char m_pad24[0x40 - 0x24];
	ObjectID m_targetID; // +0x40
	unsigned char m_pad44[0x88 - 0x44];
};

class WoundArrowUpdate : public SpecialAbilityUpdate
{
public:
	WoundArrowUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~WoundArrowUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual bool rva004C69FA(int unused);
	virtual void triggerAbilityEffect();	// slot 17
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_88; // +0x88
};

bool WoundArrowUpdate::rva004C69FA(int unused)
{
	if ((((const WoundArrowUpdateModuleData *)m_moduleData)->m_wordCC & 1) && m_object->isKindOf((KindOfType)0xD6))
		return false;
	return true;
}
