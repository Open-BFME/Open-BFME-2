// cl: /MD
// ?DoXfer@Rva003A578A@@UAEXAAVXfer@@@Z, retail 0x003A578A, 31 bytes.
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

class Rva003A578A
{
public:
    virtual void DoXfer(Xfer &xfer);
    virtual ~Rva003A578A();
private:
    float m_float04;
};

class Rva003A57A9
{
public:
    virtual void DoXfer(Xfer &xfer);
    virtual ~Rva003A57A9();
private:
    char m_pad04[8];
    Rva003A578A m_sub0C;
};

void Rva003A578A::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_float04;
}

void Rva003A57A9::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    m_sub0C.Rva003A578A::DoXfer(xfer);
}
