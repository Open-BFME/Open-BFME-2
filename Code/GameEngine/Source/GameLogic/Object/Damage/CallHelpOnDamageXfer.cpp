// cl: /DNDEBUG /MD
//
// ?xfer@CallHelpOnDamage@@MAEXPAVXfer@@@Z, retail 0x004BB4D6, 37 bytes.
// Slot 3 of the vftable 0x00C59FDC whose slot-2 name getter returns
// "CallHelpOnDamage" (installed by 0x004BB3A7). The rowed damage-module
// base xfer 0x004CE56D first (the EvacuateDamageXfer view), then Version1
// and the unsigned int at +0x14 (Xfer slot 0x78). Member name not recovered.

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

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);
	char m_unrecovered04[0x14 - 0x04];
};

class CallHelpOnDamage : public Rva004CE56D
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_14;
};

// ?xfer@CallHelpOnDamage@@MAEXPAVXfer@@@Z @0x004BB4D6
void CallHelpOnDamage::xfer(Xfer *xfer)
{
	Rva004CE56D::xfer(xfer);
	xfer->Version1();
	*xfer == m_14;
}
