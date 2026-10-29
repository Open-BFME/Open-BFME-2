// cl: /MD
//
// ?xfer@Rva00458AAE@@MAEXPAVXfer@@@Z, retail 0x00458ACD, 61 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00840DA8 (class of rowed dtor
// ??1Rva00458AAE@@UAE@XZ in Rva0024A797Derived.cpp): Version1 via rowed
// 0x000053EE then base UpdateModule xfer via rowed 0x0044DF9F then float
// at +0x20 via Xfer slot 0x70 then ints at +0x24/+0x28 via Xfer slot 0x7C.
// Layout is UpdateModule base 0x20 giving +0x20 start. Identity is slot 3
// plus the UpdateModule base call; class name stays honest Rva address
// name.

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

#include "../../Include/Common/ObjectModule.h"

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

class Rva00458AAE : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	float m_20;
	int m_24;
	int m_28;
};

void Rva00458AAE::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
}
