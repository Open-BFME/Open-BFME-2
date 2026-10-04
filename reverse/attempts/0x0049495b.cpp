// ?doSpecialPowerAtObject@SpecialPowerModule@@UAEXPAVObject@@I@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// SpecialPowerModule's three "do" entries, Zero Hour SpecialPowerModule.cpp
// shape with the BFME 2 differences the bytes show:
//   ?doSpecialPower@SpecialPowerModule@@UAEXI@Z                   0x0049490F  76B
//   ?doSpecialPowerAtObject@SpecialPowerModule@@UAEXPAVObject@@I@Z 0x0049495B 125B
//   ?doSpecialPowerAtLocation@SpecialPowerModule@@UAEXPBUCoord3D@@I@Z 0x004949D8 82B
// They are SpecialPowerModuleInterface overrides, so `this` is the +0x10
// interface subobject (pause count +0x0C there, the Object at -0x08, module
// data at -0x0C). BFME 2 differences: the pause / disabled early-out is
// skipped when the options carry 0x40000 (a script-fired power);
// doSpecialPowerAtLocation lost its angle; initiateIntentToDoSpecialPower
// (0x004946F3) takes the options third and a trailing pointer the three
// pass as NULL (ZH's way slot: name and type of that last parameter are
// inferred); and doSpecialPowerAtObject, when the owner has status 0x26 and
// module data byte +0x68 is set, first swaps the target for what
// 0x0028CCB9 (an Object method, unnamed) returns for (owner, 1, 0).
// triggerSpecialPower is 0x004941F3; isDisabled is the inline
// BitFlags<11>::any of Object +0x1C8.

#include <stddef.h>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

enum
{
	COMMAND_FIRED_BY_SCRIPT = 0x40000
};

template <int NUMBITS>
class BitFlags
{
public:
	Bool any() const;

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint;

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isDisabled() const { return m_disabledMask.any(); }
	const Coord3D *getPosition() const { return &m_pos; }
	Object *rva0028CCB9(Object *owner, Int a, Int b);

private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;                          // +0x38
	unsigned char m_pad044[0x1C8 - 0x44];
	BitFlags<11> m_disabledMask;            // +0x1C8
};

class SpecialPowerModuleData
{
public:
	unsigned char m_pad00[0x0C];
	Bool m_updateModuleStartsAttack;        // +0x0C
	unsigned char m_pad0D[0x68 - 0x0D];
	Bool m_data68;                          // +0x68
};

class Module
{
public:
	virtual ~Module();

protected:
	const SpecialPowerModuleData *m_moduleData; // +0x04
};

class ObjectModule : public Module
{
public:
	Object *getObject() const { return m_object; }

protected:
	Object *m_object;                       // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot0();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions);

	Bool initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
		UnsignedInt commandOptions, const Waypoint *way);
	void triggerSpecialPower(const Coord3D *location);

private:
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }

	Int m_value14;                          // +0x14
	Int m_value18;                          // +0x18
	Int m_pausedCount;                      // +0x1C
};

void SpecialPowerModule::doSpecialPower(UnsignedInt commandOptions)
{
	if (!(commandOptions & COMMAND_FIRED_BY_SCRIPT) && (m_pausedCount > 0 || getObject()->isDisabled()))
		return;

	initiateIntentToDoSpecialPower(NULL, NULL, commandOptions, NULL);

	if (!getSpecialPowerModuleData()->m_updateModuleStartsAttack)
		triggerSpecialPower(NULL);
}

void SpecialPowerModule::doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions)
{
	if (!(commandOptions & COMMAND_FIRED_BY_SCRIPT) && (m_pausedCount > 0 || getObject()->isDisabled()))
		return;

	Object *owner = getObject();
	if (owner->testStatus(OBJECT_STATUS_26) && getSpecialPowerModuleData()->m_data68)
		obj = obj->rva0028CCB9(owner, 1, 0);

	initiateIntentToDoSpecialPower(obj, NULL, commandOptions, NULL);

	if (!getSpecialPowerModuleData()->m_updateModuleStartsAttack)
		triggerSpecialPower(obj->getPosition());
}

void SpecialPowerModule::doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions)
{
	if (!(commandOptions & COMMAND_FIRED_BY_SCRIPT) && (m_pausedCount > 0 || getObject()->isDisabled()))
		return;

	initiateIntentToDoSpecialPower(NULL, loc, commandOptions, NULL);

	if (!getSpecialPowerModuleData()->m_updateModuleStartsAttack)
		triggerSpecialPower(loc);
}
