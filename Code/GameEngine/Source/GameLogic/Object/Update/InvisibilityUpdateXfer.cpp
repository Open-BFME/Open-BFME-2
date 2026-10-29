// cl: /DNDEBUG /MD
//
// ?xfer@InvisibilityUpdate@@MAEXPAVXfer@@@Z, retail 0x004A3981, 61 bytes.
// InvisibilityUpdate xfer (slot 3 offset 0x0C of vtable 0x00852534, same
// primary as rowed ctor 0x004A382D and dtor 0x004A389F): base UpdateModule
// xfer via rowed 0x0044DF9F, then Version(1,2) via Xfer slot 0x28, then
// version-gated bool at +0x24 via Xfer slot 0x90. Layout is the rowed
// 0x28-byte class (real UpdateModule base 0x20 plus trailing interface at
// +0x20 giving +0x24 start); donor is the Invisibility file-unit (pool key
// 0x004A393C, Rva004A390B update at slot 5). Recipe: SlowDeathBehaviorXfer
// slot-3 pattern with GameSlot Version(1,2) gating.

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

class InvisibilityTrailing { public: virtual void trailingSlot(); };

class InvisibilityUpdate : public UpdateModule, public InvisibilityTrailing
{
public:
	InvisibilityUpdate(Thing *, const ModuleData *);

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_stealth24;
};

void InvisibilityUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	Xfer::Version version(1, 2);
	*xfer == version;
	if (version.m_minimum >= 2) {
		*xfer == m_stealth24;
	}
}
