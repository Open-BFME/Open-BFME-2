// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?xfer@MonitorConditionUpdate@@UAEXPAVXfer@@@Z, retail 0x004915C6, 55 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084DAD8. Xfers Version(1,1) through the
// 0x28 slot, then the AsciiString at +0x20 through the 0x6C slot, then the
// UpdateModule base through the rowed 0x44DF9F body. Layout from the rowed
// ctor 0x00491633 (base 0x20 plus string at +0x20) joined to
// UpdateModuleCtor.cpp MI hierarchy and UpdateModuleXfer.cpp Xfer spelling.

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

void MonitorConditionUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_rememberedCommandSet;
	UpdateModule::xfer(xfer);
}
