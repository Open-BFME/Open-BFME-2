// cl: /MD
// ?rva005644A9@Rva005644A9@@UAEXPAVXfer@@@Z, retail 0x005644A9, 96 bytes.
// Chain xfer after 0x0056445E: Version1 via rowed 0x000053EE plus subobject at +0x20 via rowed TerrainCollisionModuleInfo xfer 0x0056445E plus bools at +0x1c +0x1d +0x34 +0x40 via Xfer slot 0x90 plus uint at +0x3c via Xfer slot 0x78. Caller at 0x003ABEC7. Pattern from PoisonedBehaviorXfer and Rva00564522Xfer.
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

#include "../../../../Include/Common/BfmeXfer.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/GameClient/TerrainCollisionModuleInfo.h"
namespace FXParticleSystem {
}

class Rva005644A9
{
public:
	virtual void rva005644A9(Xfer *xfer);
};

void Rva005644A9::rva005644A9(Xfer *xfer)
{
	xfer->Version1();
	((FXParticleSystem::TerrainCollisionModuleInfo *)((char *)this + 0x20))->FXParticleSystem::TerrainCollisionModuleInfo::DoXfer(*xfer);
	*xfer == *(bool *)((char *)this + 0x1c);
	*xfer == *(bool *)((char *)this + 0x1d);
	*xfer == *(bool *)((char *)this + 0x34);
	*xfer == *(bool *)((char *)this + 0x40);
	*xfer == *(unsigned int *)((char *)this + 0x3c);
}
