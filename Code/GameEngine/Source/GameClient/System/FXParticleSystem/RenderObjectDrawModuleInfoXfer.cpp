// cl: /Ireference/shims/bfme2_ascii /MD
// ?DoXfer@RenderObjectDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
// @0x00562871 194B: slot 3 xfer over vtable 0x81C1B8; Version1 then bool
// +0xC, AsciiString/uint/float/int-enum triples at +0x10/+0x20/+0x30, header
// bool/float at +0x4/+0x8. Layout mirrors DefaultCtor; Xfer decl verbatim
// from PoisonedBehaviorXfer; enum via rowed XferParticleShaderType.

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

#include "../../../../Include/Common/BfmeXfer.h"

void XferParticleShaderType(Xfer *xfer, int *value);

#include "ascii_string.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"

void FXParticleSystem::RenderObjectDrawModuleInfo::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	xfer == m_0C;
	xfer == m_10;
	xfer == m_14;
	xfer == m_18;
	XferParticleShaderType(&xfer, &m_1C);
	xfer == m_20;
	xfer == m_24;
	xfer == m_28;
	XferParticleShaderType(&xfer, &m_2C);
	xfer == m_30;
	xfer == m_34;
	xfer == m_38;
	XferParticleShaderType(&xfer, &m_3C);
	xfer == m_04;
	xfer == m_08;
}
