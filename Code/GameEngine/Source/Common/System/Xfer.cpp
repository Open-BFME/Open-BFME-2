// cl: /O1

// The composite transfer operators need real layouts: each one announces a
// four-character tag with a zero-length transfer and then moves the payload as
// raw bytes, so the sizes are the whole story. The region types go across in
// two halves rather than one block.
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

// Snapshot's own transfer entry point sits at vtable slot 3: the transfer
// operator below calls [vtable+0x0C] with the Xfer as its only argument, which
// is what orders the three pure virtuals behind the destructor.
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

// The retail vtable at 0x00BBB910 is 39 slots wide and the primitive transfer
// operators call slot 38 (0x98) through it, so every preceding slot has to be
// declared here in retail order even where only the pure-virtual shape of it is
// known. Slots 5, 6, 7, 11 and 38 all point at _purecall in the shipped table; slot 11
// sits inside the operator== run, whose parameter type is still unidentified.
// MSVC 7.1 gathers every overload of one name at the first declaration and
// emits them in reverse declaration order, so this run is written back to
// front against the shipped table.
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
    virtual bool IsDeepCRC() const;

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

// Two version bytes, stored back to back: the retail Version1 body writes 1 to
// both of them in a four-byte stack slot before handing their address to the
// slot-10 transfer operator.
class Xfer::Version
{
public:
    Version(unsigned char current, unsigned char minimum)
        : m_current(current), m_minimum(minimum) {}

    unsigned char m_current;
    unsigned char m_minimum;
};

Xfer::Xfer()
{
}

Xfer::~Xfer()
{
}

void Xfer::Version1()
{
    Version version(1, 1);
    *this == version;
}

Xfer &Xfer::operator==(char &value)
{
    XferData('byte', &value, sizeof(char));
    return *this;
}

Xfer &Xfer::operator==(unsigned char &value)
{
    XferData('ubyt', &value, sizeof(unsigned char));
    return *this;
}

Xfer &Xfer::operator==(bool &value)
{
    XferData('bool', &value, sizeof(bool));
    return *this;
}

Xfer &Xfer::operator==(int &value)
{
    XferData('int', &value, sizeof(int));
    return *this;
}

Xfer &Xfer::operator==(__int64 &value)
{
    XferData('i64', &value, sizeof(__int64));
    return *this;
}

Xfer &Xfer::operator==(unsigned int &value)
{
    XferData('uint', &value, sizeof(unsigned int));
    return *this;
}

Xfer &Xfer::operator==(short &value)
{
    XferData('shrt', &value, sizeof(short));
    return *this;
}

Xfer &Xfer::operator==(unsigned short &value)
{
    XferData('usht', &value, sizeof(unsigned short));
    return *this;
}

Xfer &Xfer::operator==(float &value)
{
    XferData('real', &value, sizeof(float));
    return *this;
}

Xfer &Xfer::operator==(Snapshot &value)
{
    value.xfer(this);

    return *this;
}

Xfer &Xfer::operator==(Coord3DBase &value)
{
    XferData('c3d', 0, 0);
    XferData(0, &value, sizeof(Coord3DBase));

    return *this;
}

Xfer &Xfer::operator==(ICoord3D &value)
{
    XferData('ic3d', 0, 0);
    XferData(0, &value, sizeof(ICoord3D));

    return *this;
}

Xfer &Xfer::operator==(Coord2D &value)
{
    XferData('c2d', 0, 0);
    XferData(0, &value, sizeof(Coord2D));

    return *this;
}

Xfer &Xfer::operator==(ICoord2D &value)
{
    XferData('ic2d', 0, 0);
    XferData(0, &value, sizeof(ICoord2D));

    return *this;
}

Xfer &Xfer::operator==(RealRange &value)
{
    XferData('rnge', 0, 0);
    XferData(0, &value, sizeof(RealRange));

    return *this;
}

Xfer &Xfer::operator==(RGBColor &value)
{
    XferData('rgb', 0, 0);
    XferData(0, &value, sizeof(RGBColor));

    return *this;
}

Xfer &Xfer::operator==(RGBAColorReal &value)
{
    XferData('rgbr', 0, 0);
    XferData(0, &value, sizeof(RGBAColorReal));

    return *this;
}

Xfer &Xfer::operator==(RGBAColorInt &value)
{
    XferData('rgbi', 0, 0);
    XferData(0, &value, sizeof(RGBAColorInt));

    return *this;
}

Xfer &Xfer::operator==(Region3D &value)
{
    XferData('r3d', 0, 0);
    XferData(0, &value.lo, sizeof(value.lo));
    XferData(0, &value.hi, sizeof(value.hi));

    return *this;
}

Xfer &Xfer::operator==(IRegion3D &value)
{
    XferData('ir3d', 0, 0);
    XferData(0, &value.lo, sizeof(value.lo));
    XferData(0, &value.hi, sizeof(value.hi));

    return *this;
}

Xfer &Xfer::operator==(Region2D &value)
{
    XferData('r2d', 0, 0);
    XferData(0, &value.lo, sizeof(value.lo));
    XferData(0, &value.hi, sizeof(value.hi));

    return *this;
}

Xfer &Xfer::operator==(IRegion2D &value)
{
    XferData('ir2d', 0, 0);
    XferData(0, &value.lo, sizeof(value.lo));
    XferData(0, &value.hi, sizeof(value.hi));

    return *this;
}

// Announces 'raw' with the size itself as the payload, then moves the bytes.
// The guard is not the obvious one: retail bails out only when the size is
// non-zero AND the pointer is null - a zero size falls straight through into
// both transfers - which is what a checked-pointer assert looks like once the
// assert itself is compiled out.
Xfer &Xfer::XferRawBytes(void *data, unsigned int size)
{
    if (size != 0 && data == 0) {
        return *this;
    }

    XferData('raw', &size, sizeof(size));
    XferData(0, data, size);

    return *this;
}

