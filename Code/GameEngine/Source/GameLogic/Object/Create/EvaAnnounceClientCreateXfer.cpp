// cl: /DNDEBUG /MD
//
// ?xfer@EvaAnnounceClientCreate@@MAEXPAVXfer@@@Z, retail 0x004C9B44, 75 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085ED50 (same primary as rowed ctor
// 0x004C99D4): Version(1,2) via Xfer slot 0x28 then base ObjectModule xfer
// via rowed 0x00560AE1 then bool at +0x14 via Xfer slot 0x90 then
// version-gated uint at +0x10 via Xfer slot 0x78. Layout is the rowed
// 0x18-byte class (opaque Rva00362EC7 base 0x0C like ObjectModule plus
// secondary vptr at +0x0C giving +0x10 start; factory 0x00252A50 news 0x18
// is sole caller of the ctor); recipe is InvisibilityUpdateXfer slot-3
// Version(1,2) gating over RandomSoundSelectorClientBehaviorXfer base
// ObjectModule plus bool uint order.

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

#include "../../../../Include/Common/XferVersion.h"

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class EvaAnnounceSecondary
{
public:
	virtual void secondarySlot();
};

class EvaAnnounceClientCreate : public ObjectModule, public EvaAnnounceSecondary
{
public:
	EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_10;
	bool m_14;
};

void EvaAnnounceClientCreate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	reinterpret_cast<ObjectModule *>(this)->xfer(xfer);
	*xfer == m_14;
	if (version.m_minimum >= 2) {
		*xfer == m_10;
	}
}
