// cl: /DNDEBUG /MD
//
// ?xfer@SpellStore@@MAEXPAVXfer@@@Z, retail 0x0043C718, 60 bytes.
// Slot 3 of the four-slot vftable 0x00C3D690 whose slot-2 name getter
// (rowed 0x0043C712) returns "SpellStore" (slot 0 the ICF-shared
// ??_GObjectModule). A CRC pass (Xfer slot 3) transfers nothing; otherwise
// Version(1,1) then the bool at +4. Member name not recovered.

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

class SpellStore
{
protected:
	virtual ~SpellStore();
	virtual void v01();
	virtual const char *v02() const;
	virtual void xfer(Xfer *xfer);

private:
	bool m_04;
};

// ?xfer@SpellStore@@MAEXPAVXfer@@@Z @0x0043C718
void SpellStore::xfer(Xfer *xfer)
{
	if (xfer->IsCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	*xfer == m_04;
}
