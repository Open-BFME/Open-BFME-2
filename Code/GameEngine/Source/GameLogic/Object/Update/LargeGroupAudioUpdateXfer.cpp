// cl: /DNDEBUG /MD
//
// ?xfer@LargeGroupAudioUpdate@@MAEXPAVXfer@@@Z, retail 0x004AB9EA, 135 bytes.
// Slot 3 of ??_7LargeGroupAudioUpdate 0x00C549BC (slot-2 name getter
// returns "LargeGroupAudioUpdate"). The rowed UpdateModule::xfer 0x0044DF9F,
// the light-CRC out, Version(1,2), a Coord2D at +0x28 (Xfer slot 0x50), the
// members at +0x30 and +0x7C through their pinned non-virtual transfers
// (0x000BB710, 0x00292550), a bool at +0x8C, from version 2 an int at
// +0x90, and a bool at +0x8D. Member names not recovered.

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "LargeGroupAudioUpdateView.h"

// The two flag sets xfer through the rowed BitFlags<591>::xfer (0x000BB710)
// and BitFlags<101>::xfer (0x00292550); their sizes, 0x4C and 0x10, are the
// dword arrays those bit counts need.

// ?xfer@LargeGroupAudioUpdate@@MAEXPAVXfer@@@Z @0x004AB9EA
void LargeGroupAudioUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	*xfer == static_cast<Coord2D &>(m_28);
	m_30.xfer(xfer);
	m_7C.xfer(xfer);
	*xfer == m_8C;
	if (version.m_minimum >= 2)
		*xfer == m_90;
	*xfer == m_8D;
}
