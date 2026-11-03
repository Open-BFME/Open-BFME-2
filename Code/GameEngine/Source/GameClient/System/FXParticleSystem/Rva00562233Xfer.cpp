// cl: /MD
// ?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z @0x00562233 28B: containing
// xfer (slot 3 of 0x81CF38/0x81D728) delegating to RenderObjectUpdateModuleInfo
// member at +0x1C via rowed 177B xfer after rowed Version1. Tail-called from
// 0x3ABE88 wrapper.

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

#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
namespace FXParticleSystem
{


}

struct Pad01C
{
	virtual ~Pad01C();

	char m_bytes[0x1C - 4];
};

class Rva00562233 : public Pad01C, public FXParticleSystem::RenderObjectUpdateModuleInfo
{
public:
	virtual void rva00562233(Xfer *xfer);
};

void Rva00562233::rva00562233(Xfer *xfer)
{
	xfer->Version1();
	RenderObjectUpdateModuleInfo::xfer(xfer);
}
