// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Oy-
//
// ?update@MonitorConditionUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0049176C, 289 bytes.
// Slot 0 of MonitorConditionUpdate's +0x10 UpdateModuleInterface vftable
// 0x00C4DACC (this at +0x10, so the module data is [this-0xC] and the object
// [this-8], as in the rowed SlaughterHordeContain::update). Swaps the
// object's command-set override by condition: while the object's +0x10C
// mask overlaps the module data's +0x08 mask it uses the +0x54 set, while
// the object's +0x370 status set passes the data's +0x58 test it uses the
// +0x68 set; switching to either remembers the set it replaced (at +0x20,
// unless that was the other monitored set). With neither condition it
// restores the remembered set and clears it. Every change dirties
// TheControlBar (+0x28). Always UPDATE_SLEEP_NONE.
//
// Evidence (target): the vftable slot and this adjustment, the rowed
// callees (mask overlap 0x00263546, Object command-set string 0x00290E67,
// AsciiString compare/set, the +0x370 getter 0x0028B7AE and its test
// 0x00331682, Object::setCommandSetStringOverride 0x0029336F), the
// AsciiString at +0x20 the rowed constructor zeroes, TheControlBar +0x28.
// Data member names are descriptive; the condition fields' identities are
// structural inferences.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "ascii_string.h"
#include "../../../../Include/Common/ObjectModule.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// ModelConditionFlags view: constructed through the rowed 0x0042526,
// compared through the rowed mask overlap 0x00263546.
class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

// Object +0x370 (rowed out-of-line lea getter).
class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void setCommandSetStringOverride(const AsciiString &newCommandSet);
	const Rva00263546 *getMask10C() const { return &m_mask10C; }
	const Rva00331682Holder *getStatus370() const
	{
		return (const Rva00331682Holder *)((const Rva0028B7AELeaGetter *)this)->get();
	}
private:
	unsigned char m_pad000[0x10C];
	Rva00263546 m_mask10C; // +0x10C
};

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }
private:
	unsigned char m_pad00[0x28];
	bool m_UIDirty; // +0x28
};
extern ControlBar *TheControlBar;

class __declspec(novtable) MonitorConditionUpdateModuleData : public Snapshot
{
public:
	virtual ~MonitorConditionUpdateModuleData();

	int m_unused04; // +4
	Rva00263546 m_modelConditionFlags; // +8
	AsciiString m_modelConditionCommandSet; // +0x54
	unsigned long m_weaponSetFlags[4]; // +0x58
	AsciiString m_weaponToggleCommandSet; // +0x68
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class MonitorConditionUpdate : public UpdateModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_rememberedCommandSet; // +0x20
};

// ?update@MonitorConditionUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0049176C
UpdateSleepTime MonitorConditionUpdate::update()
{
	const MonitorConditionUpdateModuleData *monitorConditionUpdateModuleData =
		(const MonitorConditionUpdateModuleData *)getModuleData();
	Object *obj = m_object;
	if (obj == 0 || monitorConditionUpdateModuleData == 0)
		return UPDATE_SLEEP_NONE;

	if (obj->getMask10C()->rva00263546(&monitorConditionUpdateModuleData->m_modelConditionFlags))
	{
		const AsciiString *current = obj->rva00290E67();
		if (current->compare(monitorConditionUpdateModuleData->m_modelConditionCommandSet) == 0)
			return UPDATE_SLEEP_NONE;
		current = obj->rva00290E67();
		if (current->compare(monitorConditionUpdateModuleData->m_weaponToggleCommandSet) != 0)
			((StringBase<char> *)&m_rememberedCommandSet)->set(*(const StringBase<char> *)obj->rva00290E67());
		obj->setCommandSetStringOverride(monitorConditionUpdateModuleData->m_modelConditionCommandSet);
		TheControlBar->markUIDirty();
	}
	else
	{
	const Rva00331682Holder *status = obj->getStatus370();
	if (status->test(monitorConditionUpdateModuleData->m_weaponSetFlags))
	{
		const AsciiString *current = obj->rva00290E67();
		if (current->compare(monitorConditionUpdateModuleData->m_weaponToggleCommandSet) == 0)
			return UPDATE_SLEEP_NONE;
		current = obj->rva00290E67();
		if (current->compare(monitorConditionUpdateModuleData->m_modelConditionCommandSet) != 0)
			((StringBase<char> *)&m_rememberedCommandSet)->set(*(const StringBase<char> *)obj->rva00290E67());
		obj->setCommandSetStringOverride(monitorConditionUpdateModuleData->m_weaponToggleCommandSet);
		TheControlBar->markUIDirty();
	}
	else
	{
		if (m_rememberedCommandSet.compare(AsciiString::TheEmptyString) == 0)
			return UPDATE_SLEEP_NONE;
		if (m_rememberedCommandSet.compare(*obj->rva00290E67()) == 0)
			return UPDATE_SLEEP_NONE;
		obj->setCommandSetStringOverride(m_rememberedCommandSet);
		((StringBase<char> *)&m_rememberedCommandSet)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
		TheControlBar->markUIDirty();
	}
	}
	return UPDATE_SLEEP_NONE;
}
