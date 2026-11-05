#ifndef BFME2_RADAR_UPDATE_VIEW_H
#define BFME2_RADAR_UPDATE_VIEW_H

// Shared receiver declarations for the update, transfer and pool-key consumers.
// Existing target accesses establish module data/object at +4/+8, the update
// interface at +0x10 and the three RadarUpdate fields at +0x20/+0x24/+0x25.
// These declarations preserve those consumers; they do not establish the
// complete virtual interface used by the separate constructor donor.
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

struct RadarUpdateModuleData;
enum NameKeyType { NK_UNKNOWN = 0 };

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual void xfer(Xfer *xfer);
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class RadarUpdate : public UpdateModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
	void extendRadar();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
private:
	const RadarUpdateModuleData *getRadarUpdateModuleData() const
	{
		return (const RadarUpdateModuleData *)m_moduleData;
	}

	unsigned int m_extendDoneFrame; // +0x20
	bool m_extendComplete; // +0x24
	bool m_radarActive; // +0x25
};

#endif
