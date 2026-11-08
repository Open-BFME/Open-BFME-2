// cl: /MD
//
// ?xfer@CreateModule@@MAEXPAVXfer@@@Z, retail 0x004B8D4E, 51 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00859368 (class of rowed ctor
// ??0CreateModule@@QAE@PAVThing@@PBVModuleData@@@Z in CreateModule.cpp):
// base BehaviorModule xfer via rowed 0x4C9C7D then IsLightCRC early-out via
// Xfer slot 0x10 then Version1 via rowed 0x53EE then bool at +0x14 via Xfer
// slot 0x90. Layout is BehaviorModule 0x10 plus CreateModuleInterface giving
// +0x14 start; ZH donor CreateModule.cpp proves the base-plus-bool shape.

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

// BehaviorModule's xfer is the base call below; no BehaviorModule-derived table is emitted here.
#define BFME_BEHAVIORMODULE_XFER
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class CreateModuleInterface
{
public:
	virtual void createModuleInterfaceAnchor();
};

class CreateModule : public BehaviorModule,
	public CreateModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_needToRunOnBuildComplete;
};

void CreateModule::xfer(Xfer *xfer)
{
	BehaviorModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_needToRunOnBuildComplete;
}
