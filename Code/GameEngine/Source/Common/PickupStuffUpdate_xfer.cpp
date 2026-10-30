// cl: /DNDEBUG /MD
//
// ?xfer@PickupStuffUpdate@@MAEXPAVXfer@@@Z, retail 0x00491F18, 66 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0084DDA8 (class of rowed dtor
// ??1PickupStuffUpdate@@UAE@XZ in Rva0024A797Derived.cpp): base UpdateModule xfer
// via rowed 0x44DF9F first, then Version(1,1) via Xfer slot 0x28 reusing the
// dead argument slot, then bool at +0x20 via Xfer slot 0x90, then uint at
// +0x24 via Xfer slot 0x78. Layout is UpdateModule base 0x20 plus bool plus
// uint. Identity is slot 3 plus the UpdateModule base call; class name
// stays honest Rva address name.

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

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};

class PickupStuffUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20; // +0x20
	unsigned int m_lastScanFrame; // +0x24
};

void PickupStuffUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_20;
	*xfer == m_lastScanFrame;
}
