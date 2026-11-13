// cl: /MD
// ?rva005C4808@Rva005C4808@@QAEXPAVXfer@@@Z retail 0x005C4808 61B
// Version(1 2) via Xfer slot 0x28 gated helper Rva004CE6E4 then int at +0x20 via Xfer slot 0x7C.
// Evidence: chain from 0x004CE6E4 landing; no callers; class unproven so honest Rva name.
class AsciiString; class UnicodeString; class PooledString; struct XferUnknown11;
class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D;
class Coord2D; class ICoord2D; class Region2D; class IRegion2D;
class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot;
#include "../../Include/Common/BfmeXfer.h"
class Xfer::Version
{
public:
    unsigned char m_current;
    unsigned char m_minimum;
};
#include "../../Include/Common/Rva004CE6E4.h"
class Rva005C4808 {
public:
    void rva005C4808(Xfer *xfer);
private:
    char m_pad[0x20];
    int m_val;
};
void Rva005C4808::rva005C4808(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 2;
    *xfer == version;
    if (version.m_minimum >= 2)
        ((Rva004CE6E4 *)this)->rva004CE6E4(xfer);
    *xfer == m_val;
}
