// cl: /DNDEBUG /MD /EHsc
// ?xfer@W3DLightDraw@@MAEXPAVXfer@@@Z @0x000CFAB1 72B
// Slot 3 (offset 0x0C) of vtable 0x007CD728 (class of ??1W3DLightDraw@@UAE@XZ).
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawConstructor.cpp
// (m_light +0x0C then m_phase +0x10 m_radius +0x14 m_angle +0x18 m_height +0x1C).
// Retail: Version1 via rowed 0x000053EE then 4 floats via Xfer slot 0x70 then base DrawModule::xfer via rowed 0x004CBF58.

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
class W3DDynamicLight;

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

// The rowed W3DDynamicLight::setEnabled 0x00042F30.
class W3DDynamicLight
{
public:
	void setEnabled(bool enabled);
};

#include "../../../../../../GameEngine/Include/Common/ObjectModule.h"

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

class W3DLightDraw : public DrawModule
{
public:
	W3DLightDraw(Thing *thing, const ModuleData *moduleData);
	virtual void rva000CFA99(bool hidden);

protected:
	virtual void xfer(Xfer *xfer);

private:
	W3DDynamicLight *m_light; // +0x0C
	float m_phase; // +0x10
	float m_radius; // +0x14
	float m_angle; // +0x18
	float m_height; // +0x1C
};

// Retail 0x000CFA99 (24 bytes), the W3DLightDraw vftable entry just before
// the Xfer::IsCRC stub slot (where W3DFloorDraw keeps its +0x15 setter):
// switches the light at +0x0C off while the flag is set. The slot's
// DrawModule name is not proven, so it stays address-derived.
void W3DLightDraw::rva000CFA99(bool hidden)
{
	if (m_light)
		m_light->setEnabled(!hidden);
}

void W3DLightDraw::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_phase;
	*xfer == m_radius;
	*xfer == m_angle;
	*xfer == m_height;
	DrawModule::xfer(xfer);
}
