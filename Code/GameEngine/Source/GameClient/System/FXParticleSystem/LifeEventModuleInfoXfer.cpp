// cl: /MD /Ireference/shims/bfme2_ascii
// ?DoXfer@LifeEventModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z, retail 0x00563E72, 54 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0081C188 (class of ??0LifeEventModuleInfo@FXParticleSystem@@QAE@ABV01@@Z)
// and slot 5 of 0x0081C2DC. IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, GameClientRandomVariable at +8 via rowed xferRandomVariable 0x00306183,
// AsciiString at +4 via Xfer slot 0x6C. No base call (Snapshot base is pure virtual).
// Layout from LifeEventModuleInfoDefaultCtor 0x00564001 and GetEventFX 0x0056410F
// (AsciiString m_eventName at +4, GameClientRandomVariable at +8, cache at +0x14).
// Precedent: RenderObjectUpdateModuleInfoXfer 0x00562182 (/O1 /MD, IsLightCRC+Version1
// plus xferRandomVariable). Caller 0x00563ED1 becomes ready.

#include "ascii_string.h"

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

namespace FXParticleSystem
{

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void DoXfer(Xfer &xfer) = 0;
};

class LifeEventModuleInfo : public SnapshotBase
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_name;
	GameClientRandomVariable m_var;
	const void *m_cached;
};

}

void FXParticleSystem::LifeEventModuleInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;
	xfer.Version1();
	xferRandomVariable(xfer, m_var);
	xfer == m_name;
}
