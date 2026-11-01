// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <set>
// Native2E07FA..2E0856 RET0 and WBDE9400 establish the four-value
// unsigned transfer; exception identity is independently recovered at CFFD18.
// Native2E30C8..2E3442 RET4 supplies the complete player transfer sequence.
// WBDE7920 and the missing-player-template error independently identify the
// receiver. BF1 f98983a7 LivingWorldPlayerArmyXfer.cpp is a serialization guide;
// target vslots, version1..5, offsets, snapshot receivers and revival strideD8
// come from BF2. 1C8 uses the float slot70; 18/258/274/2C8 use Snapshot slot30.
// The original player transfer method name and those snapshot classes are unknown.
// ?Rva002E07FAXfer@@YAPAVXfer@@PAV1@PAI@Z
class AsciiString; class UnicodeString; class PooledString; class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D; class Coord2D; class ICoord2D; class Region2D; class IRegion2D; class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot; class XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"


#include "../../../../Include/Common/XferException.h"
Xfer *Rva002E07FAXfer(Xfer *xfer, unsigned int *values) {
 unsigned int count=4;
 *xfer == count;
 if(count != 4) throw XferException(0,0);
 for(unsigned int i=0;i<4;++i) *xfer == values[i];
 return xfer;
}
