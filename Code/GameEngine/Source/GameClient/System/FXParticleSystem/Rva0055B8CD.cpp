// cl: /MD
//
// ?rva0055B8CD@Rva0055B8CD@@QAEXPAVXfer@@@Z, retail 0x0055B8CD, 70 bytes.
// Evidence: vtable slots 7 of 0x0081BF20 plus 3 of 0x0081BA90 (DoXfer);
// callee Version1 rowed 0x000053EE plus Xfer slots 0x3C RGBColor and 0x78 uint
// over 8x0x10 elems at +0x04/+0x10 plus xferRandomVariable rowed 0x00306183
// with GameClientRandomVariable at +0x84; Ghidra DoXfer 70B; caller 0x0055B951.
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
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

#include "../../../../../Libraries/Include/Lib/RGBColor.h"

struct Rva0055B8CDElem
{
	RGBColor m_a;
	unsigned int m_b;
};

class Rva0055B8CD
{
	Rva0055B8CDElem m_elems[8];
	GameClientRandomVariable m_var;
public:
	virtual void rva0055B8CD(Xfer *xfer);
};

void Rva0055B8CD::rva0055B8CD(Xfer *xfer)
{
	xfer->Version1();
	unsigned int *pVal = &m_elems[0].m_b;
	int n = 8;
	do {
		*xfer == *(RGBColor *)(pVal - 3);
		*xfer == *pVal;
		pVal += 4;
	} while (--n != 0);
	xferRandomVariable(*xfer, m_var);
}
