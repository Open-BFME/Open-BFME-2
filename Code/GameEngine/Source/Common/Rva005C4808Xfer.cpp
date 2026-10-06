// cl: /MD
// ?rva005C4808@Rva005C4808@@QAEXPAVXfer@@@Z retail 0x005C4808 61B
// Version(1 2) via Xfer slot 0x28 gated helper Rva004CE6E4 then int at +0x20 via Xfer slot 0x7C.
// Evidence: chain from 0x004CE6E4 landing; no callers; class unproven so honest Rva name.
class AsciiString; class UnicodeString; class PooledString; struct XferUnknown11;
class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D;
class Coord2D; class ICoord2D; class Region2D; class IRegion2D;
class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot;
class Xfer {
public:
    class Version {
    public:
        unsigned char m_current;
        unsigned char m_minimum;
    };
    virtual ~Xfer();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void SkipBadBlock(Snapshot &s, unsigned int size);
    virtual Xfer &XferRawBytes(void *d, unsigned int size);
    virtual Xfer &operator==(bool &v);
    virtual Xfer &operator==(char &v);
    virtual Xfer &operator==(unsigned char &v);
    virtual Xfer &operator==(short &v);
    virtual Xfer &operator==(unsigned short &v);
    virtual Xfer &operator==(int &v);
    virtual Xfer &operator==(unsigned int &v);
    virtual Xfer &operator==(__int64 &v);
    virtual Xfer &operator==(float &v);
    virtual Xfer &operator==(AsciiString &v);
    virtual Xfer &operator==(UnicodeString &v);
    virtual Xfer &operator==(PooledString &v);
    virtual Xfer &operator==(Coord3DBase &v);
    virtual Xfer &operator==(ICoord3D &v);
    virtual Xfer &operator==(Region3D &v);
    virtual Xfer &operator==(IRegion3D &v);
    virtual Xfer &operator==(Coord2D &v);
    virtual Xfer &operator==(ICoord2D &v);
    virtual Xfer &operator==(Region2D &v);
    virtual Xfer &operator==(IRegion2D &v);
    virtual Xfer &operator==(RealRange &v);
    virtual Xfer &operator==(RGBColor &v);
    virtual Xfer &operator==(RGBAColorReal &v);
    virtual Xfer &operator==(RGBAColorInt &v);
    virtual Xfer &operator==(Snapshot &v);
    virtual Xfer &operator==(XferUnknown11 &v) = 0;
    virtual Xfer &operator==(Version &v);
    virtual Xfer &XferEnum(const char *n, void *d, unsigned int s);
};
class Rva004CE6E4 {
public:
    void rva004CE6E4(Xfer *xfer);
};
class Rva005C4808 {
public:
    void rva005C4808(Xfer *xfer);
private:
    char m_pad[0x20];
    int m_val;
};
void Rva005C4808::rva005C4808(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 2;
    *xfer == version;
    if (version.m_minimum >= 2)
        ((Rva004CE6E4 *)this)->rva004CE6E4(xfer);
    *xfer == m_val;
}
