// cl: /O1

// A text-dumping Xfer, vtable 0x00C7B388 (constructor 0x0060DEB1, destructor
// 0x0060DED5).  Every typed transfer prints its value with a labelled format --
// "%i=0x%x [byte]", "version: %i", "'%s' [ascii]" -- through the variadic
// helper at 0x0060D5F2, which either writes one indent unit per open block or
// formats into a 1 KB buffer and hands the text to the stream at +8.  A flag at
// +4 suppresses the indent once, after a label has been printed.  No string
// names the class, so its name is derived from the vtable address; the method
// names are the base Xfer's, mapped slot by slot (the operator== run is laid
// out in reverse declaration order, as Xfer.cpp explains).
//
// The base class and the value types below are Xfer.cpp's model verbatim, so
// the vtable lines up with the shipped one.

#include <stdarg.h>

// Declared by hand: retail calls _vsnprintf through the msvcr71 import table
// but strlen directly (its thunk at 0x00629170), which no one pair of CRT
// headers gives under a single /MD setting.
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *buffer, unsigned int count, const char *format, va_list args);
extern "C" unsigned int __cdecl strlen(const char *text);

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

class Coord2D
{
public:
    float x;
    float y;
};

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

// The string types are reduced to what their transfers read: a pointer to a
// data block whose text starts eight bytes in.  ASCII and Unicode fall back to
// the shared empty literals when the pointer is null; the pooled string reads
// through it unchecked.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
    struct Data { int unexamined0; int unexamined4; };
    Data *m_data;

public:
    const char *str() const { return m_data ? reinterpret_cast<const char *>(m_data + 1) : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
    struct Data { int unexamined0; int unexamined4; };
    Data *m_data;

public:
    // 16-bit characters: wchar_t is not a built-in type under this unit's flags.
    const unsigned short *str() const { return m_data ? reinterpret_cast<const unsigned short *>(m_data + 1) : reinterpret_cast<const unsigned short *>(L""); }
};

class PooledString
{
    struct Data { int unexamined0; int unexamined4; };
    Data *m_data;

public:
    const char *peek() const { return reinterpret_cast<const char *>(m_data + 1); }
};
struct XferUnknown11;

// upstream layout: Code/GameEngine/Source/Common/System/Xfer.cpp (retail vtable 0x00BBB910)
class Xfer
{
public:
    class Version;

    Xfer();
    virtual ~Xfer();

    void Version1();

    virtual bool IsStoring() const;
    virtual bool IsLoading() const;
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

// The text sink: only its write slot (+0x10) is called.
struct BfmeRva00C7B388Stream
{
    virtual void _M_slot_00();
    virtual void _M_slot_04();
    virtual void _M_slot_08();
    virtual void _M_slot_0c();
    virtual void Write(const char *text, int length);
};

class BfmeRva00C7B388 : public Xfer
{
public:
    static void __cdecl Print(BfmeRva00C7B388 *self, const char *format, ...);

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

private:
    bool m_bfme04;				// +0x04: skip the indent once, after a label
    BfmeRva00C7B388Stream *m_bfme08;	// +0x08
    char *m_bfme0C;				// +0x0C: open-block stack, 12-byte entries
    char *m_bfme10;
    char *m_bfme14;
};

// 0x0060D5F2: with no format, one indent unit per open block; otherwise the
// formatted text, measured and handed to the stream.
void __cdecl BfmeRva00C7B388::Print(BfmeRva00C7B388 *self, const char *format, ...)
{
    if (format == 0) {
        for (int depth = (self->m_bfme10 - self->m_bfme0C) / 12; depth != 0; --depth)
            self->m_bfme08->Write("  ", 2);
        return;
    }
    char buffer[0x400];
    va_list args;
    va_start(args, format);
    _vsnprintf(buffer, sizeof(buffer), format, args);
    self->m_bfme08->Write(buffer, strlen(buffer));
}

Xfer &BfmeRva00C7B388::operator==(bool &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i [bool]\n", value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(char &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [byte]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(unsigned char &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [ubyte]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(short &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [short]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(unsigned short &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [ushort]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(int &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [int]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(unsigned int &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%u=0x%x [uint]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(__int64 &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%I64i=0x%I64x [int64]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(float &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%1.6f=%f\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(AsciiString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "'%s' [ascii]\n", value.str());
    m_bfme04 = false;
    return *this;
}

// ??8BfmeRva00C7B388@@UAEAAVXfer@@AAVUnicodeString@@@Z present-unmatched
Xfer &BfmeRva00C7B388::operator==(UnicodeString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%'%S' [unicode]\n", value.str());
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(PooledString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "'%s' [pool]\n", value.peek());
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(Coord3DBase &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f,z:%1.6f [coord3d]\n", value.x, value.y, value.z);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(ICoord3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i,z:%i [icoord3d]\n", value.x, value.y, value.z);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(Region3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f,z:%1.6f to x:%1.6f,y:%1.6f,z:%1.6f [region3d]\n",
        value.lo.x, value.lo.y, value.lo.z, value.hi.x, value.hi.y, value.hi.z);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(IRegion3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i,z:%i to x:%i,y:%i,z:%i [iregion3d]\n",
        value.lo.x, value.lo.y, value.lo.z, value.hi.x, value.hi.y, value.hi.z);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(Coord2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f [coord2d]\n", value.x, value.y);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(ICoord2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i [icoord2d]\n", value.x, value.y);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(Region2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f to x:%1.6f,y:%1.6f [region2d]\n",
        value.lo.x, value.lo.y, value.hi.x, value.hi.y);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(IRegion2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i to x:%i,y:%i [iregion2d]\n",
        value.lo.x, value.lo.y, value.hi.x, value.hi.y);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(RealRange &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%1.6f to %1.6f [range]\n", value.lo, value.hi);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(RGBColor &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%1.3f,g:%1.3f,b:%1.3f [rgb]\n", value.red, value.green, value.blue);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(RGBAColorReal &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%1.3f,g:%1.3f,b:%1.3f,a:%1.3f [rgba]\n",
        value.red, value.green, value.blue, value.alpha);
    m_bfme04 = false;
    return *this;
}

Xfer &BfmeRva00C7B388::operator==(RGBAColorInt &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%i,g:%i,b:%i,a:%i [irgba]\n", value.red, value.green, value.blue, value.alpha);
    m_bfme04 = false;
    return *this;
}
