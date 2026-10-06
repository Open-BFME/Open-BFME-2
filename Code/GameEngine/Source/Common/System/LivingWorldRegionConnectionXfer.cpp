// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?DoXfer@LivingWorldRegionConnection@@UAEXAAVXfer@@@Z @0x003F3054 70B
// Snapshot slot 3 DoXfer: Version(1,1) + regionName + numberAllowed via helper
// + detourPoints via vector helper.
// Evidence: 70B ebp frame ret 4; vslot 3 of 0x836E48 (LivingWorldRegionConnection
// copy ctor TU); calls Xfer 0x28 (Version) + 0x6C (Ascii) + rowed Get 0x3EFE82
// + rowed Xfer 0x3F2C0C; callees all rowed/pinned.
#include <vector>
#include "ascii_string.h"

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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class Xfer
{
public:
    class Version
    {
    public:
        unsigned char data[2];
    };

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

struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *a, void *b);
struct BfmeE8
{
    float x;
    float y;
};
Xfer *Rva003F2C0CXfer(Xfer *xfer, _STL::vector<BfmeE8> *vec);

class Snapshot
{
public:
    virtual ~Snapshot();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);
};

class LivingWorldRegionConnection : public Snapshot
{
public:
    LivingWorldRegionConnection(const LivingWorldRegionConnection &that);
    virtual ~LivingWorldRegionConnection();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(Xfer &xfer);

private:
    AsciiString m_regionName;
    int m_numberAllowed;
    _STL::vector<BfmeE8> m_detourPoints;
};

void LivingWorldRegionConnection::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xfer == m_regionName;
    Rva003EFE82Get((Rva003EFE82Obj *)&xfer, &m_numberAllowed);
    Rva003F2C0CXfer(&xfer, &m_detourPoints);
}
