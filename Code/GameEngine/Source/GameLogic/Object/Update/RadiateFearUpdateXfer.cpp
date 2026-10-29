// cl: /MD
//
// ?xfer@RadiateFearUpdate@@MAEXPAVXfer@@@Z, retail 0x0049C195, 61 bytes.
// Virtual slot 3 (offset 0x0C) of vtable RVA 0x00850FBC (VA 0x00C50FBC
// installed by rowed ctor 0x0049C106 in RadiateFearUpdateCtor.cpp): base
// UpdateModule xfer via rowed 0x44DF9F then IsLightCRC early-out via Xfer
// slot 0x10 then Version(1,1) via Xfer slot 0x28 then UpgradeMux member at
// +0x20 via rowed 0x004CE397. Layout is UpdateModule base 0x20 plus
// UpgradeMux m_20 (news 0x28 per rowed factory 0x24E6B0). Address cluster
// 0x49C106 ctor / 0x49C179 deleting-dtor / 0x49C195 xfer / 0x49C1D2 module
// data deleting-dtor proves the RadiateFearUpdate identity; no donor (BFME2
// only).

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

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class RadiateFearUpdate;

class UpgradeMux
{
	friend class RadiateFearUpdate;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class RadiateFearUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_20;
};

void RadiateFearUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 1);
	*xfer == version;
	m_20.UpgradeMux::upgradeMuxXfer(xfer);
}
