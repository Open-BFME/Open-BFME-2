// cl: /O1

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
class Coord2D;
struct Coord3DBase;
struct ICoord2D;
struct ICoord3D;
struct Region2D;
struct IRegion2D;
struct Region3D;
struct IRegion3D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
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
