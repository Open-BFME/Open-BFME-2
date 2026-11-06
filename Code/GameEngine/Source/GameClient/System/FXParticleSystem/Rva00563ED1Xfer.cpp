// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva00563ED1@Rva00563ED1@@UAEXPAVXfer@@@Z, retail 0x00563ED1, 82 bytes.
// Chain of just-landed ?DoXfer@LifeEventModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
// at 0x00563E72. IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, LifeEventModuleInfo subobject at +0x20 via rowed 0x00563E72,
// flags at +0x1C +0x1D +0x3C via Xfer slot 0x90 (bool per LightningDrawModuleInfoXfer
// 0x005614D9 flag via 0x90). No base call. Layout: Pad20 (0x20, flags at end)
// then LifeEventModuleInfo (0x18) then cache dword at +0x38 then flag at +0x3C.
// Precedent: RenderObjectUpdateModuleInfoXfer 0x00562182 (/O1 /MD).

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

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/LifeEventModuleInfo.h"
namespace FXParticleSystem
{

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};


}

struct Pad20
{
	virtual ~Pad20();
	char m_pad[0x18];
	bool m_1c;
	bool m_1d;
	char m_padEnd[2];
};

class Rva00563ED1 : public Pad20, public FXParticleSystem::LifeEventModuleInfo
{
public:
	virtual void rva00563ED1(Xfer *xfer);

private:
	const void *m_38;
	bool m_3c;
};

void Rva00563ED1::rva00563ED1(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	FXParticleSystem::LifeEventModuleInfo::DoXfer(*xfer);
	*xfer == m_1c;
	*xfer == m_1d;
	*xfer == m_3c;
}
