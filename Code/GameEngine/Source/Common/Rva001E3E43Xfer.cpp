// cl: /MD
//
// ?xfer@Locomotor@@MAEXPAVXfer@@@Z, retail 0x001E525A 382B. Slot 3 (offset 0xC)
// of vtable 0x007DE888 (the class's dtor is rowed at 0x001E3E43).
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

#include "../../Include/GameLogic/LocomotorClass.h"

void Locomotor::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	Xfer::Version ver;
	ver.m_major = 1;
	ver.m_minor = 3;
	*xfer == ver;
	*xfer == reinterpret_cast<Coord3DBase &>(m_maintainPos);
	*xfer == m_brakingFactor;
	*xfer == m_maxLift;
	*xfer == m_maxSpeed;
	*xfer == m_maxAccel;
	*xfer == m_maxBraking;
	*xfer == m_maxTurnRate;
	*xfer == m_closeEnoughDist;
	*xfer == m_40;
	*xfer == m_flags;
	*xfer == m_preferredHeight;
	*xfer == m_4C;
	*xfer == m_preferredHeightDamping;
	*xfer == m_angleOffset;
	*xfer == m_offsetIncrement;
	*xfer == m_98;
	*xfer == m_A0;
	*xfer == m_A4;
	*xfer == reinterpret_cast<Coord3DBase &>(m_14);
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
