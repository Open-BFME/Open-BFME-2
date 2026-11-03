// cl: /MD
// ?xfer@Rva003AF22E@@MAEXPAVXfer@@@Z retail 0x0055EA8E 31 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0081C884 (class of rowed copy ctor
// ??0Rva003AF22E@@QAE@ABV0@@Z): Version1 plus GameClientRandomVariable member
// at +0x1C via rowed xferRandomVariable 0x306183. No base call. Precedent:
// Rva00499F45Xfer.cpp (?xfer@Rva00499F45@@MAEXPAVXfer@@@Z).
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

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

class Rva003AF22E
{
public:
	char m_pad[0x18];
	GameClientRandomVariable m_var;

protected:
	virtual void xfer(Xfer *xfer);
};

void Rva003AF22E::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_var);
}
