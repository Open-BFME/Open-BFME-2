// cl: /MD
//
// ?xfer@Rva001E3E43@@MAEXPAVXfer@@@Z, retail 0x001E525A 382B. Slot 3 (offset 0xC)
// of vtable 0x007DE888 (class of ??1Rva001E3E43 rowed at 0x001E3E43).
// No base xfer call. IsLightCRC early-out via Xfer slot 0x10. Version(1 3)
// via Xfer slot 0x28 with minor in second byte gating 0x9A (minor>1) and
// stack uint (minor>=3). Floats via 0x70 uints via 0x78 bools via 0x90
// Coord3DBase via 0x60 raw 4B at +0x9C via 0x24. Layout from retail offsets.

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

class Xfer::Version
{
public:
	unsigned char m_major;
	unsigned char m_minor;
	unsigned short m_pad;
};

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva001E3E43 : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad04[4];
	Coord3DBase m_08;
	Coord3DBase m_14;
	float m_20;
	float m_24;
	float m_28;
	unsigned char m_pad2C[4];
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	unsigned int m_44;
	float m_48;
	float m_4C;
	float m_50;
	float m_54;
	float m_58;
	float m_5C;
	unsigned int m_60;
	unsigned int m_64;
	unsigned char m_pad68[48];
	bool m_98;
	bool m_99;
	bool m_9A;
	unsigned char m_pad9B[1];
	int m_9C;
	float m_A0;
	float m_A4;
};

void Rva001E3E43::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	Xfer::Version ver;
	ver.m_major = 1;
	ver.m_minor = 3;
	*xfer == ver;
	*xfer == m_08;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_30;
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3C;
	*xfer == m_40;
	*xfer == m_44;
	*xfer == m_48;
	*xfer == m_4C;
	*xfer == m_50;
	*xfer == m_54;
	*xfer == m_58;
	*xfer == m_98;
	*xfer == m_A0;
	*xfer == m_A4;
	*xfer == m_14;
	*xfer == m_5C;
	*xfer == m_60;
	*xfer == m_64;
	*xfer == m_99;
	xfer->XferRawBytes(&m_9C, 4);
	if (ver.m_minor > 1)
		*xfer == m_9A;
	if (ver.m_minor < 3)
		return;
	unsigned int tmp = 0;
	*xfer == tmp;
}
