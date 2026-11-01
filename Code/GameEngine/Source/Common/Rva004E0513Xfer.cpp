// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva004E0513@Rva004E0513@@QAEXPAVXfer@@@Z @0x004E0513 204B
// Versioned Xfer body for the Rva004E04FD layout: three ints at +0x00/+0x08/+0x04
// then Version(1 5) gating a pre-5 dummy int plus Unicode at +0x0C with
// Ascii upgrade when version<3 plus Ascii at +0x10 when version>=2 plus bool
// at +0x14 when version>=4. Order 0/8/4 and the translate+releaseBuffer tail
// match retail. Evidence: unlock lane; prev 0x004E04FD zeroing ctor zeroes the
// same five dwords plus byte 0x14; callees rowed translate 0x006CB6A0 and
// releaseBuffer 0x00036410; callers at 0x002980EF 0x0037DEC2 0x0037E57F.
#include "ascii_string.h"
#include "unicode_string.h"

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

#include "../../Include/Common/XferVersion.h"

class Rva004E0513
{
public:
	void rva004E0513(Xfer *xfer);
private:
	int m_00;
	int m_04;
	int m_08;
	UnicodeString m_0C;
	AsciiString m_10;
	bool m_14;
};

void Rva004E0513::rva004E0513(Xfer *xfer)
{
	Xfer::Version version(1, 5);
	*xfer == version;
	*xfer == m_00;
	*xfer == m_08;
	*xfer == m_04;
	if (version.m_minimum < 5) {
		int dummy = 0;
		*xfer == dummy;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_0C;
	} else {
		AsciiString tmp;
		*xfer == tmp;
		m_0C.translate(tmp);
	}
	if (version.m_minimum >= 2) {
		*xfer == m_10;
	}
	if (version.m_minimum >= 4) {
		*xfer == m_14;
	}
}
