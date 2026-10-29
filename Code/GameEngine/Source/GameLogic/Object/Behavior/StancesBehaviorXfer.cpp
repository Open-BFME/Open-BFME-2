// cl: /DNDEBUG /MD
//
// ?xfer@StancesBehavior@@MAEXPAVXfer@@@Z, retail 0x0045ED9D, 56 bytes.
// StancesBehavior xfer (slot 3 offset 0x0C of vtable 0x008424DC, same
// primary as the rowed ctor 0x45EF80): Version(1,1) via Xfer slot 0x28,
// then UpdateModule base xfer via rowed 0x44DF9F, then the +0x30 stances
// value via rowed XferStancesEnum 0x45ED66 ("StancesEnum" label). Layout is
// the rowed ctor shape (UpdateModule base 0x20 plus 0x10 member plus int at
// +0x30). Recipe is the BloodthirstyUpdateXfer Version-first pattern.

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

void XferStancesEnum(Xfer *xfer, int *stances);

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

class StancesBehavior : public UpdateModule
{
public:
	StancesBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_member20[0x10];
	int m_30;
};

void StancesBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferStancesEnum(xfer, &m_30);
}
