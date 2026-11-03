// cl: /MD
// ?DoXfer@RenderObjectUpdateModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z (retail export 1174)
// @0x00562182 177B: slot 3 xfer (slot 7 of ConcreteModuleTemplate wrapper);
// IsLightCRC early-out, Version1, twelve GameClientRandomVariables at
// +0x4..+0x88 via rowed xferRandomVariable, mode at +0x94 via rowed
// XferRotationType. Layout mirrors DefaultCtor.

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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);
void XferRotationType(Xfer *xfer, int *value);

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
namespace FXParticleSystem
{


}

void FXParticleSystem::RenderObjectUpdateModuleInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;
	xfer.Version1();
	xferRandomVariable(xfer, m_var0);
	xferRandomVariable(xfer, m_var1);
	xferRandomVariable(xfer, m_var2);
	xferRandomVariable(xfer, m_var3);
	xferRandomVariable(xfer, m_var4);
	xferRandomVariable(xfer, m_var5);
	xferRandomVariable(xfer, m_var6);
	xferRandomVariable(xfer, m_var7);
	xferRandomVariable(xfer, m_var8);
	xferRandomVariable(xfer, m_var9);
	xferRandomVariable(xfer, m_var10);
	xferRandomVariable(xfer, m_var11);
	XferRotationType(&xfer, &m_mode);
}
