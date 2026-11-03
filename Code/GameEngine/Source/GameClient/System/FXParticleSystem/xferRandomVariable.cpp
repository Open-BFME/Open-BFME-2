// cl: /DNDEBUG /MD /GX-
// ?xferRandomVariable@@YAAAVXfer@@AAV1@AAVGameClientRandomVariable@@@Z retail 0x00306183 149 bytes.
// BFME1 donor: Code/GameEngine/Source/GameClient/System/FXParticleSystem/xferRandomVariable.cpp
// BFME2 deltas: Version1 helper for the 1/1 version pair, XferDistributionType helper for the enum,
// xferReal at vtable slot 28 (0x70). Callers: 40+ DoXfer bodies including 0x0055EA8E vslot candidate.
// Callees rowed: Version1 0x53EE, XferDistributionType 0x305F92, setRange 0x2341E7.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

void XferDistributionType(Xfer *xfer, int *value);

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var)
{
	float low;
	float high;
	GameClientRandomVariable::DistributionType type;

	xfer.Version1();

	low = 0.0f;
	high = 0.0f;
	type = GameClientRandomVariable::CONSTANT;

	if (xfer.IsStoring()) {
		low = var.m_low;
		high = var.m_high;
		type = var.m_type;
	}

	xfer == low;
	xfer == high;
	XferDistributionType(&xfer, (int *)&type);

	if (!xfer.IsStoring()) {
		var.setRange(low, high, type);
	}
	return xfer;
}
