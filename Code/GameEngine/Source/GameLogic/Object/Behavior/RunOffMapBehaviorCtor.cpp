// cl: /DNDEBUG /MD
//
// ??0RunOffMapBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0046217B,
// 49 bytes. Behavior-side ctor completing the RunOffMapBehavior file-unit
// (ModuleData proc/factory/ctor rowed at 0x46216A/0x254F24/0x254ECE;
// behavior factory rowed at 0x24B6B1 news 0x34 with this pinned 2-arg ctor;
// poolkey rowed at 0x4621B2).
//
// Shape: frameless ctor over the rowed BehaviorModule base 0x253330. Retail's first +0x10 store is
// RunOffMapBehaviorInterface's own table, written by that base's constructor before the class's three.

// Slots 1 and 3 make the base calls these two macros declare.
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#define BFME_BEHAVIORMODULE_XFER
class Thing;
class ModuleData;

class Object;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class RunOffMapBehaviorInterface {public:virtual void triggerFlee()=0;};
class RunOffMapBehavior : public BehaviorModule, public RunOffMapBehaviorInterface
{
public:
	RunOffMapBehavior(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual void triggerFlee();
	virtual void *slot35() { return static_cast<RunOffMapBehaviorInterface *>(this); } // 0x002533D3
protected:
	// Retail's slots 1-3: 0x0058B03E (a `jmp` to the shared empty body), the name getter 0x004621AC
	// and the shared xfer 0x004CE56D (Version 1, then BehaviorModule::xfer).
	virtual void loadPostProcess() { BehaviorModule::loadPostProcess(); }
	virtual const char *GetSnapshotName() const { return "RunOffMapBehavior"; }
	virtual void xfer(Xfer *xfer);
};

// ??0RunOffMapBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0046217B
RunOffMapBehavior::RunOffMapBehavior(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
}

// ?xfer@RunOffMapBehavior@@MAEXPAVXfer@@@Z @0x004CE56D: slot 3, Version1 then the base, folded with its siblings'.
void RunOffMapBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
}
