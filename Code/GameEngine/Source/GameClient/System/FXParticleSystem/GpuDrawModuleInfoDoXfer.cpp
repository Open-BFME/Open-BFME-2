// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX

// GpuDrawModuleInfo::DoXfer, retail 0x0056390A (64B). The native
// transfer addresses are +0x04/+0x08 for the integer fields, +0x0C
// for the string and +0x10 for the float. The canonical header names
// these fields by offset; Version1 resolves to the rowed 0x53EE.

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

// AsciiString with its inline nulling default, as retail's TU sees it: the
// default ctor (rowed 6B at 0x326BE6, `m_text = 0`) folds into the member
// slot with no out-of-line call, and the member transfers via ==AsciiString.
#include "ascii_string.h"

#include "../../../../Include/GameClient/GpuDrawModuleInfo.h"

namespace FXParticleSystem
{

// ?DoXfer@GpuDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void GpuDrawModuleInfo::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_04;
    xfer == m_08;
    xfer == m_0C;
    xfer == m_10;
}

}
