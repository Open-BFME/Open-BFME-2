// cl: /MD
// ?rva005C4469@Rva005C4469@@QAEXPAVXfer@@@Z retail 0x005C4469 58B
// Version(1 1) via Xfer slot 0x28 then rowed Rva004CE6E4 then bool at +0xC via Xfer slot 0x90.
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
class Rva005C4469 {
public:
    void rva005C4469(Xfer *xfer);
private:
    char m_pad[0xC];
    bool m_flag;
};
void Rva005C4469::rva005C4469(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 1;
    *xfer == version;
    ((Rva004CE6E4 *)this)->rva004CE6E4(xfer);
    *xfer == m_flag;
}
