// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?xfer@AutoAbilityBehavior@@MAEXPAVXfer@@@Z, retail 0x0045A291, 86 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0084175C (class of rowed dtor
// ??1AutoAbilityBehavior@@UAE@XZ in AutoAbilityBehaviorDtor.cpp): Version(1,2)
// via Xfer slot 0x28 then base UpdateModule xfer via rowed 0x0044DF9F then
// AsciiString at +0x20 via Xfer slot 0x6C then version-gated bool at +0x30
// via Xfer slot 0x90 and Coord3DBase at +0x24 via Xfer slot 0x60 (>=2).
// Layout is UpdateModule base 0x20 giving +0x20 start (AsciiString null at
// +0x20 plus three zeroed floats at +0x24/+0x28/+0x2C plus zeroed bool at
// +0x30 in pinned ctor 0x0045A78F; dtor only destroys the string at +0x20).
// Identity is slot 3 plus the UpdateModule base call; shape follows the rowed
// Rva0045ADC1 xfer at 0x0045AEC9 (same Version(1,2) plus add edi,0x24 tail).

#include "ascii_string.h"
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
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

class AutoAbilityBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_20;
	Coord3DBase m_24;
	bool m_30;
};

void AutoAbilityBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_20;
	if (version.m_minimum >= 2) {
		*xfer == m_30;
		*xfer == m_24;
	}
}
