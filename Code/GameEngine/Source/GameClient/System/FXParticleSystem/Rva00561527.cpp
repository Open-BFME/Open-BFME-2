// cl: /DNDEBUG /MD /EHsc /Ob2
// ?rva00561527@Rva00561527@@UAEXPAVXfer@@@Z @0x00561527 28B evidence: Version1 0x000053EE then Lightning xfer 0x005614D9 on base at +0x18; caller jmp 0x003ABBC6.
// Honest-address wrapper (naming rule).
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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/LightningDrawModuleInfo.h"
class Pad018
{
public:
	virtual ~Pad018();
private:
	char m_pad[0x18 - 4];
};

class Rva00561527 : public Pad018, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	virtual void rva00561527(Xfer *xfer);
};

void Rva00561527::rva00561527(Xfer *xfer)
{
	xfer->Version1();
	FXParticleSystem::LightningDrawModuleInfo::DoXfer(*xfer);
}

