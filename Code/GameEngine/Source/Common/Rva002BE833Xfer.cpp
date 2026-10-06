// cl: /O1 /MD
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
