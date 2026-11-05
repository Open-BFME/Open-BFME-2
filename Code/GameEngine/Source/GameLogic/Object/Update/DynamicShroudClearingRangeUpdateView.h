#pragma once

// Shared class view for the behavior ctor, dtor, pool key, update, decal and
// transfer rows and the ModuleData dtor. Native rows place Object at +0x08,
// the update interfaces at +0x0C/+0x10, state at +0x20, the boolean at +0x40
// and the decal array at +0x50. The interface names are the seed's (their
// vftable names are data-ledger keys); retail's update slot is the +0x10 one.
// The ModuleData ctor keeps its own view: it stores the derived vftable before
// its member ctor, which this novtable class cannot express.
// Keep Xfer operands beside its include to withstand merge include hoisting.

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

#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"


class Xfer;
class Thing;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class ModuleData;

class Player;

class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() {}
};

// Retail's update interface (vftable 0xC4BEB0, update in slot 0) sits at +0x10.
class ModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual void moduleInterfaceAnchor() {}
};

struct Coord3D;

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	Player *getControllingPlayer() const;
	float getShroudClearingRange() const;
	void setShroudClearingRange(float range);
};

class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	// Retail's Snapshot slots 1 and 2 precede xfer (slot 3, table 0x0084BEBC).
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void xfer(Xfer *xfer);
	Object *getObject() const { return m_object; }

protected:
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
};

class RadiusDecal
{
public:
	void clear();
public:
	void setPosition(const Coord3D &pos);
	void setOpacity(float opacity);
private:
	const void *m_template;
private:
	void *m_decal;
private:
	unsigned char m_empty;
private:
	unsigned char m_pad_09[3];
private:
	float m_unknown0C;
public:
	RadiusDecal();
public:
	~RadiusDecal();
};

class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *owningPlayer, RadiusDecal &result) const;
};

class DynamicShroudClearingRangeUpdateModuleData;

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	DynamicShroudClearingRangeUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DynamicShroudClearingRangeUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
public:
	void killGridDecals();
	void rva0048B256();
	virtual void xfer(Xfer *xfer);
protected:
	const DynamicShroudClearingRangeUpdateModuleData *getDynamicShroudClearingRangeUpdateModuleData() const
	{
		return (const DynamicShroudClearingRangeUpdateModuleData *)m_moduleData;
	}

	enum DSCRU_STATE
	{
		DSCRU_NOT_STARTED_YET,
		DSCRU_GROWING,
		DSCRU_SUSTAINING,
		DSCRU_SHRINKING,
		DSCRU_DONE_FOREVER,
		DSCRU_SLEEPING
	};
private:
	DSCRU_STATE m_state;
private:
	int m_stateCountDown;
private:
	int m_totalFrames;
private:
	unsigned int m_growStartDeadline;
private:
	unsigned int m_sustainDeadline;
private:
	unsigned int m_shrinkStartDeadline;
private:
	unsigned int m_doneForeverFrame;
private:
	unsigned int m_changeIntervalCountdown;
private:
	bool m_decalsCreated;
private:
	unsigned char m_pad_41[3];
private:
	float m_visionChangePerInterval;
private:
	float m_nativeClearingRange;
private:
	float m_currentClearingRange;
private:
	RadiusDecal m_gridDecal[30];
public:
	void createGridDecals(const RadiusDecalTemplate &tmpl, float radius, const Coord3D &pos);
};

// 0xB6CF1 is rowed as BfmeStringRecord000B94D2's dtor.
class BfmeStringRecord000B94D2
{
public:
	~BfmeStringRecord000B94D2();

private:
	unsigned char m_data[0x34];
};

class __declspec(novtable) DynamicShroudClearingRangeUpdateModuleData : public Snapshot
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleData();

	const RadiusDecalTemplate &getGridDecalTemplate() const
	{
		return *(const RadiusDecalTemplate *)&m_gridDecalTemplate;
	}

	unsigned int m_unused04; // +0x04, unstored gap
	unsigned int m_shrinkDelay; // +0x08
	unsigned int m_shrinkTime; // +0x0C
	unsigned int m_growDelay; // +0x10
	unsigned int m_growTime; // +0x14
	float m_finalVision; // +0x18
	unsigned int m_changeInterval; // +0x1C
	unsigned int m_growInterval; // +0x20
	bool m_doSpySatFX; // +0x24
	unsigned char m_pad25[3];
	BfmeStringRecord000B94D2 m_gridDecalTemplate; // +0x28
};
