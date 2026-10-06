// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
#define _DLL
#include <string.h>

// Retail 0x0060C0A0 288B vtable slot 25 (offset 0x64) of 0x007BB910 (class of
// ??1Xfer@@UAE@XZ). Xfer::operator==(PooledString&) via astr tag 0x61737472,
// strlen 0x629170, AsciiString temp with getBufferForRead 0x36640 and
// releaseBuffer 0x36410, PooledString::operator=(AsciiString) 0x60BE7F.
// Evidence: slot order Ascii 27 / Unicode 26 / Pooled 25 (reverse overload
// order); callers: PooledString assign caller at 0x60C19C; donor:
// XferAsciiStringTransfer.cpp logic with PooledString strlen/getLength.

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

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
    int x;
    int y;
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

class Xfer;

class Snapshot
{
public:
    virtual ~Snapshot();
    virtual void crc(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
    virtual void xfer(Xfer *xfer) = 0;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

#include "ascii_string.h"


#include "unicode_string.h"

struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

class PooledString
{
public:
    PooledString &operator=(const AsciiString &that);
    const char *str() const { return m_entry->m_text; }

    PooledStringEntry *m_entry;
};

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

Xfer &Xfer::operator==(PooledString &ps)
{
    if (IsStoring())
    {
        int length = (int)strlen(ps.m_entry->m_text);
        if (length >= 255)
        {
            unsigned char marker = 255;
            XferData(0x61737472, &marker, 1);
            XferData(0, &length, 4);
        }
        else
        {
            XferData(0x61737472, &length, 1);
        }
        XferData(0, (void *)ps.str(), length);
    }
    else
    {
        AsciiString temp;
        int length = 0;
        XferData(0x61737472, &length, 1);
        if (length == 255)
        {
            XferData(0, &length, 4);
        }
        if (length != 0)
        {
            XferData(0, ((StringBase<char> *)&temp)->getBufferForRead(length), length);
            ((StringBase<char> *)&temp)->getBufferForRead(length)[length] = 0;
        }
        else
        {
            temp.clear();
        }
        ps = temp;
    }
    return *this;
}
