// cl: /MD
//
// ?rva003FD2C2@Rva003FD2C2@@MAEXPAVXfer@@@Z, retail 0x003FD2C2, 52 bytes.
// Chain: calls 0x003FD1C5 which just landed (base Rva003FD1C5 handling
// +0x04/+0x08). Then persists Coord at +0x0C via Xfer slot 0x60, float at
// +0x18 via Xfer slot 0x70, uint at +0x1C via Xfer slot 0x78. Same minimal
// shape as the base plus three members (Coord ends where float starts).

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

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva002B3092
{
public:
	virtual ~Rva002B3092();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_04;
	bool m_08;
};

class Rva003FD2C2 : public Rva002B3092
{
protected:
	virtual void rva003FD2C2(Xfer *xfer);
private:
	Coord3DBase m_0c;
	float m_18;
	unsigned int m_1c;
};

void Rva003FD2C2::rva003FD2C2(Xfer *xfer)
{
	Rva002B3092::xfer(xfer);
	*xfer == m_0c;
	*xfer == m_18;
	*xfer == m_1c;
}
