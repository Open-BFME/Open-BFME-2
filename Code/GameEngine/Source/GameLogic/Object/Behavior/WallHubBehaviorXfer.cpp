// cl: /DBFME_ASCII_DTOR_DECL /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common
// stlport
//
// ?xfer@WallHubBehavior@@MAEXPAVXfer@@@Z, retail 0x00452F25, 44 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0083FDBC (VA 0x00C3FDBC, class of
// rowed dtor ??1Rva00452D52@@UAE@XZ in Rva0024A797Grandchildren.cpp): slot 2
// name getter at 0x00452D72 returns WallHubBehavior, slot 4 pool key at
// 0x00452DA3 is WallHubBehavior pool key, slot 0 deleting dtor at 0x00452EC1.
// Version(1,1) via Xfer slot 0x28 then base UpdateModule xfer via rowed
// 0x0044DF9F. No members and no IsLightCRC early-out in retail. Layout is
// UpdateModule base 0x20. Recipe is the Rva0045B134Xfer Version-first slot-3
// pattern with protected xfer.

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

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

// The abstract interface at +0x20; its vtable holds five methods and the
// trailing slot.
class WallHubInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
};

class WallHubBehaviorModuleData;

class WallHubBehavior : public UpdateModule, public WallHubInterface
{
public:
	WallHubBehavior(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update() { return UPDATE_SLEEP_FOREVER; }
	// Retail 0x00452D52 (rowed ??1Rva00452D52) stores the four vptrs the ctor
	// installs and tail-jumps ~UpdateModule 0x0024A797; this body folds onto it.
	virtual ~WallHubBehavior() {}
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
protected:
	virtual void xfer(Xfer *xfer);

private:
	const WallHubBehaviorModuleData *getWallHubBehaviorModuleData() const { return (const WallHubBehaviorModuleData *)m_moduleData; }

	Real m_24; // +0x24
};

void WallHubBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
}
