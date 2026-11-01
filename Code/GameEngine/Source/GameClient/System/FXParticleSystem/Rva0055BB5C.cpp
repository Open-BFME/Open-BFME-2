// cl: /MD
//
// ?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z, retail 0x0055BB5C, 82 bytes.
// Evidence: calls inner ?xfer rowed 0x0055B96D at +0x0C plus Version1
// rowed 0x000053EE plus IsLightCRC slot 0x10 plus RGB slots 0x3C at +0x94
// and +0xA0 plus string slot 0x7C at +0xAC; caller jmp 0x003AC9AA.
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

#include "../../../../Include/Common/BfmeXfer.h"

class RGBColorFull
{
public:
	float r;
	float g;
	float b;
};


class RGBColorKey
{
public:
	int m_color;
};

struct InnerElem
{
	RGBColorKey m_a;
	char m_pad[8];
	unsigned int m_b;
};

class Rva0055BC8B
{
	InnerElem m_elems[8];
	float m_trailing;
public:
	virtual void xfer(Xfer *xfer);
};

class Rva0055BB5C
{
	char m_pad[8];
	Rva0055BC8B m_inner;
	RGBColorFull m_c0;
	RGBColorFull m_c1;
	int m_val;
public:
	virtual void rva0055BB5C(Xfer *xfer);
};

void Rva0055BB5C::rva0055BB5C(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	m_inner.Rva0055BC8B::xfer(xfer);
	*xfer == (RGBColor &)m_c0;
	*xfer == (RGBColor &)m_c1;
	*xfer == m_val;
}
