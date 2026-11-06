// cl: /MD
// ?rva00562945@Rva00562945@@UAEXPAVXfer@@@Z @0x00562945 28B: containing
// xfer delegating to RenderObjectDrawModuleInfo second base at +0x18 via
// rowed slot-3 xfer after rowed Version1. Tail-called from 0x3ABB8E wrapper.

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
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

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"
namespace FXParticleSystem
{


}

struct Pad018
{
	virtual ~Pad018();

	char m_bytes[0x18 - 4];
};

class Rva00562945 : public Pad018, public FXParticleSystem::RenderObjectDrawModuleInfo
{
public:
	virtual void rva00562945(Xfer *xfer);
};

void Rva00562945::rva00562945(Xfer *xfer)
{
	xfer->Version1();
	RenderObjectDrawModuleInfo::DoXfer(*xfer);
}
