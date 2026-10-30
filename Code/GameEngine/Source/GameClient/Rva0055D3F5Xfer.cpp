// cl: /MD /ICode/Libraries/Include/Lib
// ?rva0055D3F5@Rva0055D3F5@@UAEXPAVXfer@@@Z at 0x0055D3F5 size 45
// Evidence: vslot slot3 of 0x0081D07C and 0x0081C7B8; Version1 rowed 0x000053EE plus 2 Xfer slots 0x90/0x70 over +0x20/+0x24; xfer recipe precedent FXParticleSystemLineXfer.cpp.

#include "Coord3D.h"

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
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

class TacticalView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(const Coord3D *center, float radius, unsigned int color);
};

extern class View *TheTacticalView;

class Rva0055D3F5
{
public:
	virtual void rva0055D3F5(Xfer *xfer);
	void debugDraw(Coord3D pos);
private:
	char m_pad[0x1C];
	bool m_20;
	char m_pad2[3];
	float m_radius;
};

void Rva0055D3F5::rva0055D3F5(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_radius;
}

// Native 0x0055D422..0x0055D48C (106 bytes, RET 0xC): slot 4 of the same
// sphere-volume tables (0x0081C7C8, 0x0081CBC4, 0x0081D08C), the debug draw
// beside the line volume's 0x0055CD70: two TacticalView slot-12 circles of
// the +0x24 radius in 0xCCAAFFFF, half a radius below and above the centre.
// The centre arrives by value and is moved in place.
void Rva0055D3F5::debugDraw(Coord3D pos)
{
	pos.z -= m_radius * 0.5f;
	((TacticalView *)TheTacticalView)->slot12(&pos, m_radius, 0xCCAAFFFF);
	pos.z += m_radius;
	((TacticalView *)TheTacticalView)->slot12(&pos, m_radius, 0xCCAAFFFF);
}
