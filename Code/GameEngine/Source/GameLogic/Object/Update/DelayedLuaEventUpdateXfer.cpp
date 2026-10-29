// cl: /DNDEBUG /MD /GX
//
// ?xfer@DelayedLuaEventUpdate@@MAEXPAVXfer@@@Z, retail 0x004A8E0A, 113 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00853A5C, same primary as rowed ctor
// 0x004A8E7B and dtor 0x004A8D4A and deleting dtor 0x004A8EEF. Base
// UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer slot
// 0x10, Version(1,1) via Xfer slot 0x28, float at +0x70 via slot 0x70, bools
// at +0x74/+0x75 via slot 0x90, uint at +0x20 via XferRawBytes slot 0x24,
// then member DelayedLuaEventList at +0x24 via its slot-3 xfer (rowed
// 0x003316D2). Layout is the rowed class (UpdateModule base 0x20 plus m_event
// +0x20 plus events +0x24 size 0x4C plus m_range +0x70 plus flags +0x74/+0x75)
// from DelayedLuaEventUpdateCtor/Dtor. Recipe is the InvisibilityUpdateXfer
// slot-3 pattern with DelayedLuaEventListXfer Version(1,1) and float/bool
// slots.

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
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Thing;
class ModuleData;
class Object;
class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleBase
{
public:
	UpdateModuleBase(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModuleBase();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class UpdateModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class UpdateModuleInterface2
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public UpdateModuleBase,
		     public UpdateModuleInterface1,
		     public UpdateModuleInterface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DelayedLuaEventList
{
public:
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
	DelayedLuaEventList &rva004A8DDE(const DelayedLuaEventList &other);

private:
	char m_pad[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DelayedLuaEventUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004A8F0B(unsigned int f20, const DelayedLuaEventList &events, UpdateSleepTime sleep, float f70, bool f74, bool f75);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_event;			// +0x20
	DelayedLuaEventList m_events;	// +0x24
	float m_range;			// +0x70
	bool m_f74;			// +0x74
	bool m_f75;			// +0x75
};

void DelayedLuaEventUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_range;
	*xfer == m_f74;
	*xfer == m_f75;
	xfer->XferRawBytes(&m_event, 4);
	m_events.xfer(xfer);
}
