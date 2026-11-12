// cl: /MD
//
// ?rva002BE833@Rva002BE833@@QAEXPAVXfer@@@Z, RVA 0x002BE833, 155 bytes.
// Xfer-style body: Version(1,1) via Xfer slot 0x28, IsCRC early-out via slot
// 0x0C, then two Coord3DBase via slot 0x60 and six floats via slot 0x70 plus
// one bool via slot 0x90, in retail order 0x74 0x7C 0x78 0x6C 0x70 0x54 0x60
// 0x80 0x84. Same Version+IsCRC prefix as caller 0x0009AAFB which calls this
// body then xfers +0x11C +0x134 +0x138 plus float array at +0xF8 via rowed
// Rva0030612AXfer; slot mapping (Version 0x28 bool 0x90 float 0x70 Coord 0x60
// IsCRC 0x0C) from Xfer.cpp reverse-order run and WeaponFireSpecialAbility
// IsCRC precedent. Layout is pad to +0x54 then members to +0x88.
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
struct RealRange
{
    float lo;
    float hi;
};
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
void Rva002BE833::rva002BE833(Xfer *xfer)
{
    Xfer::Version version(1, 1);
    *xfer == version;
    if (xfer->IsCRC())
        return;
    *xfer == m_74;
    *xfer == m_7C;
    *xfer == m_78;
    *xfer == m_6C;
    *xfer == m_70;
    *xfer == m_54;
    *xfer == m_60;
    *xfer == m_80;
    *xfer == m_84;
}
