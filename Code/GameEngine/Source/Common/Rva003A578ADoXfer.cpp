// cl: /MD
// ?DoXfer@Rva003AE07D@@UAEXAAVXfer@@@Z, retail 0x003A578A, 31 bytes.
// Honest-address DoXfer for a single-float holder (float at +0x04): Version1
// via rowed 0x000053EE then float transfer through Xfer slot +0x70 (proven as
// the float overload by GpuDrawModuleInfo::DoXfer at 0x0056390A which xfers
// its float at +0x10 through the same +0x70). Caller is 0x003A57BC in
// 0x003A57A9 which xfers its subobject at +0x0C through here; prev is the
// SubsystemNameGetters4 name row, next is the DefaultModuleHeadBase ctor row.
// Xfer declaration is the UpdateModuleXfer/GpuDraw-proven spelling with
// overloaded operator== in declaration order (MSVC reverses them).

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

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/Rva003AE07D.h"

class Rva003A57A9
{
public:
    virtual void DoXfer(Xfer &xfer);
    virtual ~Rva003A57A9();
private:
    char m_pad04[8];
    Rva003AE07D m_sub0C;
};

void Rva003AE07D::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_real04;
}

void Rva003A57A9::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    m_sub0C.Rva003AE07D::DoXfer(xfer);
}
