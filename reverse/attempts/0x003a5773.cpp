// ??0Rva003AE07D@@QAE@XZ
// partial score=1.0 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// Native3A5773..3A5784 is an8B Snapshot-derived float holder default ctor.
// Same C1B568 table is installed by owned copy3AE07D; native table entries:
// G4A10FD, emptyB3FD0, name3A5784, transfer3A578A. Original class spelling
// is not independently exported; the table's name literal is ParticleWindModuleInfo.
// Reference f989 BaseY005E6030/6160 value constructors guide zero-float codegen,
// not original owner identity. Native Snapshot destructor7 and G28 are full folds.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
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


class Rva003AE07D : public Snapshot
{
public:
    Rva003AE07D();
    Rva003AE07D(const Rva003AE07D &other);
    virtual ~Rva003AE07D() {}
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void DoXfer(Xfer &xfer);
private:
    union { unsigned int m_bits04; float m_float04; };
};
Rva003AE07D::Rva003AE07D() : m_float04(0.0f) {}
Rva003AE07D::Rva003AE07D(const Rva003AE07D &other) : Snapshot(other)
{
    m_bits04 = other.m_bits04;
}
void Rva003AE07D::LoadPostProcess() {}
const char *Rva003AE07D::GetSnapshotName() const
{
    return "ParticleWindModuleInfo";
}
void Rva003AE07D::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_float04;
}
