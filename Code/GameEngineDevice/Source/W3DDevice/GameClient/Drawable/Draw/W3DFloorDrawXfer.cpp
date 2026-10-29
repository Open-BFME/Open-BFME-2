// cl: /DNDEBUG /MD
// ?xfer@W3DFloorDraw@@MAEXPAVXfer@@@Z @0x000CF074 98B
// Slot 3 (offset 0x0C) of vtable 0x007CD4E0 (class of ??0W3DFloorDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Layout from W3DFloorDrawCtor.cpp (W3DPropDraw base 0x10 plus m_10 +0x10 plus flags +0x14..+0x17).
// Retail: Version(1,3) via Xfer slot 0x28 then base W3DPropDraw::xfer via rowed 0x000B221A
// then bool at +0x16 via slot 0x90 if >=2 then bools at +0x17 +0x15 via slot 0x90 if >=3.

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

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class DrawModule;

#include "../../../../../../GameEngine/Include/Common/ObjectModule.h"

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

class W3DPropDraw : public DrawModule
{
public:
	W3DPropDraw(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

	bool m_propAdded; // +0x0C
};

class W3DFloorDraw : public W3DPropDraw
{
public:
	W3DFloorDraw(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const void *m_10; // +0x10
	bool m_flag14; // +0x14
	bool m_flag15; // +0x15
	bool m_flag16; // +0x16
	bool m_flag17; // +0x17
};

void W3DFloorDraw::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	W3DPropDraw::xfer(xfer);
	if (version.m_minimum >= 2) {
		*xfer == m_flag16;
	}
	if (version.m_minimum >= 3) {
		(*xfer == m_flag17) == m_flag15;
	}
}
