// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata

// ?xfer@DelayedLuaEventList@@UAEXPAVXfer@@@Z, retail 0x003316D2, 68 bytes.
// Slot 3 (offset 0x0C) of vtable 0x007C9CF0 installed by the rowed ctor
// 0x000B6D8B. Snapshot shape (dtor plus crc plus loadPostProcess plus xfer)
// from Code/GameEngine/Source/Common/System/Snapshot.cpp puts xfer at slot 3.
// Xfer slot order (IsLightCRC at 0x10 plus Version at 0x28) from
// Code/GameEngine/Source/Common/System/XferEnumHelpers.cpp GameSlot::xfer
// which shows the identical IsLightCRC guard plus Version reuse of [ebp+8].
// Element array at +4 is three 0x18-byte Snapshot children whose own slot-3
// xfer is invoked; element ctor 0x000B694C installs 0x007C9CD0 and dtors at
// 0x000B6971 and 0x000B6DD2 restore Snapshot base 0x007BB554.

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

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

#include "Common/Snapshot.h"

class DelayedLuaEvent : public Snapshot
{
public:
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_data[0x14];
};

class DelayedLuaEventList : public Snapshot
{
public:
	virtual void xfer(Xfer *xfer);

private:
	DelayedLuaEvent m_events[3];
};

void DelayedLuaEventList::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	for (int i = 0; i < 3; ++i)
		m_events[i].xfer(xfer);
}
