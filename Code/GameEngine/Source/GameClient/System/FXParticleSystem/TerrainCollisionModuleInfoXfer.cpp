// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Target export names TerrainCollisionModuleInfo::DoXfer(Xfer&) at0x0056445E,57B.
// Subobject xfer at overall+0x20: Version1 plus RandomVariable at +0x8 via rowed xferRandomVariable plus AsciiString at +0x4 via Xfer slot 0x6C plus bool at +0x14 via Xfer slot 0x90. Caller at 0x005644BC; unblocks 0x005644A9.
// Xfer declaration with reverse-order overloads gives 0x6C AsciiString 0x90 bool 0x78 uint; pattern from Rva003AF22E xfer 0x0055EA8E.
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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem {

class TerrainCollisionModuleInfo : public Snapshot
{
public:
	virtual ~TerrainCollisionModuleInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &stream);
private:
	AsciiString m_04;
	GameClientRandomVariable m_08;
	bool m_14;
	int m_18;
};

void TerrainCollisionModuleInfo::DoXfer(Xfer &stream)
{
	Xfer *xfer = &stream;
	xfer->Version1();
	xferRandomVariable(*xfer, m_08);
	*xfer == m_04;
	*xfer == m_14;
}

} // namespace FXParticleSystem
