// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// ??0MonitorConditionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00491633, 46 bytes.
// MonitorConditionUpdate behavior ctor over the rowed UpdateModule base
// (0x253390); the compiler installs the three vptrs and the AsciiString
// member's default ctor zeroes +0x20. Class views are MonitorConditionUpdate.cpp's.
//
// ??1MonitorConditionUpdateModuleData@@UAE@XZ retail 0x00491711 63B.
// Dtor lane: ctor rowed at 0x004915FD in ModelConditionSpecialAbilityUpdateModuleDataCtor.cpp
// vtable 0x00C4DA50 with slot0 ??_G at 0x004916F5. Destroys AsciiString at +0x68
// then AsciiString at +0x54 through pinned 0x36410 then restores Snapshot base
// vtable 0x00BBB554. Layout follows ctor TU (+0 vtable +4 unused +8 filter 0x4C
// +0x54 string +0x58 flags 16B +0x68 string size 0x6C matching factory 0x24D849
// news 0x6C). Shape follows LargeGroupBonusUpdateModuleDataDtor and
// FlammableUpdateModuleDataDtor (TU-local Snapshot with inline BBB554 restore
// empty derived body novtable suppresses entry derived store retail lacks).
// Caller is ??_G at 0x004916F8. EH states 1 then 0 for the two strings.

// ?getModuleNameKey@MonitorConditionUpdate@@UBE?AW4NameKeyType@@XZ @0x491667
// (69B): cached pool-name key for MonitorConditionUpdate. The class
// identity comes from the pool-name string the body pushes
// ("MonitorConditionUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

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
	MonitorConditionUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~MonitorConditionUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_rememberedCommandSet; // +0x20
};

// ??0MonitorConditionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x491633
MonitorConditionUpdate::MonitorConditionUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
}
