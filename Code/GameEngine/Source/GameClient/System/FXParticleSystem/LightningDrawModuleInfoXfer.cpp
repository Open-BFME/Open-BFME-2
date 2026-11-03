// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/moduledata
// ?DoXfer@LightningDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z @0x005614D9 78B (retail export 1170) evidence: slot 3 per vtable 0x0081BE80 slot7 and 0x0081BD80 slot3; Version1 then 3x xferRandomVariable 0x00306183 at +4/+0x10/+0x1c then float +0x28 via Xfer slot 0x70 then flag +0x2c via slot 0x90; Ghidra DoXfer.
// Snapshot slot-3 xfer via 4.7 recipe.
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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

// Use the existing BFME2 Snapshot ABI and destructor provider.
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

#include "../../../../Include/GameClient/LightningDrawModuleInfo.h"
namespace FXParticleSystem
{


}

void FXParticleSystem::LightningDrawModuleInfo::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	xferRandomVariable(xfer, m_var0);
	xferRandomVariable(xfer, m_var1);
	xferRandomVariable(xfer, m_var2);
	xfer == m_28;
	xfer == m_2c;
}
