// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?xfer@Rva0055EF6E@@QAEXPAVXfer@@@Z 87B @0x0055EF6E: version-gated
// Xfer helper for the sub-object at +0x0C (float at +4 via slot 0x70,
// bool at +8 via slot 0x90 if version >= 2, bool at +9 via slot 0x90
// if version >= 3). Called by the parent xfer at 0x0055EFC5 after
// Version1. Xfer declaration copied verbatim from
// PoisonedBehaviorXfer.cpp; Version is two back-to-back bytes per Xfer.cpp.

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

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

class Rva0055EF6E
{
public:
	void xfer(Xfer *xfer);
private:
	unsigned char m_pad00[4];
	float m_04;
	bool m_08;
	bool m_09;
};

void Rva0055EF6E::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_04;
	if (version.m_minimum >= 2)
		*xfer == m_08;
	if (version.m_minimum >= 3)
		*xfer == m_09;
}
