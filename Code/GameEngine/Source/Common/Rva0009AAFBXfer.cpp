// cl: /MD
//
// ?rva0009AAFB@Rva0009AAFB@@QAEXPAVXfer@@@Z, RVA 0x0009AAFB, 112 bytes.
// Xfer-style body: Version(1 1) via Xfer slot 0x28, IsCRC early-out via slot
// 0x0C, then base Rva002BE833 xfer at +0x0, three floats at +0x11C +0x134
// +0x138 via slot 0x70, plus float triple at +0xF8 via rowed Rva0030612AXfer.
// Same Version+IsCRC prefix as callee 0x002BE833 which this body calls;
// slot mapping from Rva002BE833Xfer.cpp and XferEnumHelpers.cpp.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
#include "../../../Libraries/Include/Lib/Coord3DBase.h"
#include "../../../Libraries/Include/Lib/ICoord3D.h"
#include "../../../Libraries/Include/Lib/Region3D.h"
struct IRegion3D
{
    ICoord3D lo;
    ICoord3D hi;
};
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
#include "../../Include/Common/RealRange.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
struct RGBAColorReal
{
    float red;
    float green;
    float blue;
    float alpha;
};
#include "../../Include/Common/RGBAColorInt.h"
class Snapshot;
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/Common/XferVersion.h"
class Rva002BE833
{
public:
    void rva002BE833(Xfer *xfer);
private:
    char m_pad[0x54];
    Coord3DBase m_54;
    Coord3DBase m_60;
    float m_6C;
    float m_70;
    float m_74;
    bool m_78;
    char m_pad79[3];
    float m_7C;
    float m_80;
    float m_84;
};
void Rva0030612AXfer(Xfer *xfer, float *vals);
class Rva0009AAFB : public Rva002BE833
{
public:
    void rva0009AAFB(Xfer *xfer);
private:
    char m_pad88[0xF8 - 0x88];
    float m_F8[3];
    char m_pad104[0x11C - 0x104];
    float m_11C;
    char m_pad120[0x134 - 0x120];
    float m_134;
    float m_138;
};
void Rva0009AAFB::rva0009AAFB(Xfer *xfer)
{
    Xfer::Version version(1, 1);
    *xfer == version;
    if (xfer->IsCRC())
        return;
    rva002BE833(xfer);
    *xfer == m_11C;
    *xfer == m_134;
    *xfer == m_138;
    Rva0030612AXfer(xfer, m_F8);
}
