// cl: /O1 /DNDEBUG /MD
// ?doSpecialPowerAtObject@Rva004C2A35@@UAEXPAVObject@@I@Z retail 0x004C2A35 53 bytes. SpecialPowerModule doSpecialPowerAtObject override slot 11 that guards disabled/null then calls base. Evidence: VTABLE slot 11 of table 0x0085C788 class SpecialPowerModule it overrides base and calls base 0x0049495B; rowed BitFlags<11>::any 0x0023C58B; REF table slot 0x0085C7B4 neighbours doSpecialPower; donor SpecialPowerModule.cpp:651 base body.
#include <stddef.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};
template <int NUMBITS>
class BitFlags
{
public:
	Bool any() const;
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
class Waypoint;
class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	const Coord3D *getPosition() const { return &m_pos; }
	Object *rva0028CCB9(Object *owner, Int a, Int b);
private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;
	unsigned char m_pad044[0x1C8 - 0x44];
	BitFlags<11> m_disabledMask;
};
#define OBJECT_DISABLED_MASK(object) \
	((const BitFlags<11> *)((const char *)(object) + 0x1C8))
class SpecialPowerModuleData
{
public:
	unsigned char m_pad00[0x0C];
	Bool m_updateModuleStartsAttack;
	unsigned char m_pad0D[0x68 - 0x0D];
	Bool m_data68;
};
class Module
{
public:
	virtual ~Module();
protected:
	const SpecialPowerModuleData *m_moduleData;
};
class ObjectModule : public Module
{
public:
	Object *getObject() const { return m_object; }
protected:
	Object *m_object;
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
	void initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way);
	void triggerSpecialPower(const Coord3D *location);
private:
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
	Int m_value14;
	Int m_value18;
	Int m_pausedCount;
};
class Rva004C2A35 : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
};
void Rva004C2A35::doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions)
{
	Object *owner = getObject();
	if (OBJECT_DISABLED_MASK(owner)->any())
		return;
	if (obj == 0)
		return;
	if (owner == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtObject(obj, commandOptions);
}
