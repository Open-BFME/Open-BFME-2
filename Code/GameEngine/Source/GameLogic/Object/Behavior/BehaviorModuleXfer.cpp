// cl: /DNDEBUG /MD /GX
// stlport
//
// ?xfer@BehaviorModule@@MAEXPAVXfer@@@Z retail 0x004C9C7D
// 24 bytes. BehaviorModule base xfer used by the UpdateModule xfer chain
// (UpdateModule::xfer rowed over its pin; row supersedes that pin here).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Behavior/BehaviorModule.cpp):
// Version1 on the stream, then the ObjectModule base xfer (pinned).
// Version1 resolves via its row.

// Retail table 0x00BEEA7C (BehaviorModule's) holds this body at slot 3: a
// protected virtual, as the module headers declare it. ObjectModule's view
// carries the Snapshot vptr at +0 (virtual destructor), so the base call
// keeps `this`.
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

class ObjectModule
{
public:
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);
};

class BehaviorModule : public ObjectModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@BehaviorModule@@MAEXPAVXfer@@@Z @0x004C9C7D
void BehaviorModule::xfer(Xfer *xfer)
{
	xfer->Version1();

	ObjectModule::xfer(xfer);
}
