// cl: /MD
//
// ?xfer@OathbreakersFadeAwayBehavior@@MAEXPAVXfer@@@Z, retail 0x004B8A28, 81 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0085928C (class of rowed dtor
// ??1OathbreakersFadeAwayBehavior@@UAE@XZ in Rva0024A797Derived.cpp): Version(1,3) via Xfer
// slot 0x28 then version-gated base UpdateModule xfer via rowed 0x44DF9F
// (min>=2) then version-gated float at +0x24 via Xfer slot 0x70 (min>=3)
// then bool at +0x20 via Xfer slot 0x90. Layout is UpdateModule base 0x20
// plus bool plus float (cf. rowed dtor 0x4B89C4 three vptrs). Identity is
// slot 3 plus the UpdateModule base call; class name stays honest Rva.

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

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	const char *name() const;
	virtual NameKeyType getModuleNameKey() const;
	void rva004B8B0F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	float m_24;
};

void OathbreakersFadeAwayBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	if (version.m_minimum >= 2) {
		UpdateModule::xfer(xfer);
	}
	if (version.m_minimum >= 3) {
		*xfer == m_24;
	}
	*xfer == m_20;
}
