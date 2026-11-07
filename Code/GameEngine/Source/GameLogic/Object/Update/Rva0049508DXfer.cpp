// cl: /MD
//
// ?xfer@AutoFindHealingUpdate@@MAEXPAVXfer@@@Z, retail 0x0049508D, 39 bytes.
// Slot 3 (offset 0xC) of vtable 0x0084EC10 (class of ??1Rva0049506E) and
// slot 3 of 0x0085191C (class of ??1Rva0049FE7B); xfer with Version1 then
// rowed UpdateModule::xfer 0x0044DF9F then int at +0x20 via Xfer slot 0x7c.
// Layout follows DemoTrapUpdateXfer (Version1 plus base plus int): UpdateModule
// base 0x20 plus int at +0x20. Xfer declaration copied verbatim from
// PoisonedBehaviorXfer.cpp. Evidence: vtable slots, Version1 row 0x53EE,
// base row 0x44DF9F, int slot 0x7c per DynamicShroud precedent.

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

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class AutoFindHealingUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_20;
};

void AutoFindHealingUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_20;
}
