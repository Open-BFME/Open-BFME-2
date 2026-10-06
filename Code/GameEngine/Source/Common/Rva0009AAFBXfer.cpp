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
struct Coord3DBase
{
    float x;
    float y;
    float z;
};
struct ICoord3D
{
    int x;
    int y;
    int z;
};
struct Region3D
{
    Coord3DBase lo;
    Coord3DBase hi;
};
struct IRegion3D
{
    ICoord3D lo;
    ICoord3D hi;
};
#include "../../../Libraries/Include/Lib/Coord2D.h"
struct ICoord2D
{
    int x;
    int y;
};
struct Region2D
{
    Coord2D lo;
    Coord2D hi;
};
struct IRegion2D
{
    ICoord2D lo;
    ICoord2D hi;
};
struct RealRange
{
    float lo;
    float hi;
};
struct RGBColor
{
    float red;
    float green;
    float blue;
};
struct RGBAColorReal
{
    float red;
    float green;
    float blue;
    float alpha;
};
struct RGBAColorInt
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
};
class Snapshot;
class Xfer
{
public:
    class Version;
    Xfer();
    virtual ~Xfer();
    void Version1();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &operator==(bool &value);
    virtual Xfer &operator==(char &value);
    virtual Xfer &operator==(unsigned char &value);
    virtual Xfer &operator==(short &value);
    virtual Xfer &operator==(unsigned short &value);
    virtual Xfer &operator==(int &value);
    virtual Xfer &operator==(unsigned int &value);
    virtual Xfer &operator==(__int64 &value);
    virtual Xfer &operator==(float &value);
    virtual Xfer &operator==(AsciiString &value);
    virtual Xfer &operator==(UnicodeString &value);
    virtual Xfer &operator==(PooledString &value);
    virtual Xfer &operator==(Coord3DBase &value);
    virtual Xfer &operator==(ICoord3D &value);
    virtual Xfer &operator==(Region3D &value);
    virtual Xfer &operator==(IRegion3D &value);
    virtual Xfer &operator==(Coord2D &value);
    virtual Xfer &operator==(ICoord2D &value);
    virtual Xfer &operator==(Region2D &value);
    virtual Xfer &operator==(IRegion2D &value);
    virtual Xfer &operator==(RealRange &value);
    virtual Xfer &operator==(RGBColor &value);
    virtual Xfer &operator==(RGBAColorReal &value);
    virtual Xfer &operator==(RGBAColorInt &value);
    virtual Xfer &operator==(Snapshot &value);
    virtual Xfer &operator==(XferUnknown11 &value) = 0;
    virtual Xfer &operator==(Version &value);
    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
    virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class Xfer::Version
{
public:
    Version(unsigned char current, unsigned char minimum)
        : m_current(current), m_minimum(minimum) {}
    unsigned char m_current;
    unsigned char m_minimum;
};
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
