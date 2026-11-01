// cl: /MD
// ?xfer@Rva003429B9@@MAEXPAVXfer@@@Z @0x003406A5 117B: slot 3 xfer of vtable 0x008126C0 (class of Rva003429B9 ctor 0x003429B9). Version(1 3) then base AIInternalMoveToState xfer then IsLightCRC early-out then Coord at +0x4C via slot 0x60 plus uint at +0x58 via slot 0x78 plus bool at +0x5C if min>=2 plus bool at +0x5D if min>=3. Evidence: callees rowed (base 0x0033FF76) layout from Rva003429B9Ctor floats 0x4C 0x50 0x54 as Coord plus int 0x58 plus bools 0x5C 0x5D.
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

#include "../../Include/Common/XferVersion.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
private:
	char m_pad04[8];
};

class AIInternalMoveToState : public Rva0049B47C
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad0C[0x20 - 0x0C];
	Coord3DBase m_20;
	float m_2C;
	int m_30;
	Coord3DBase m_34;
	unsigned int m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva003429B9 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Coord3DBase m_4C;
	unsigned int m_58;
	bool m_5C;
	bool m_5D;
};

void Rva003429B9::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_58;
	if (version.m_minimum >= 2) {
		*xfer == m_5C;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_5D;
	}
}
