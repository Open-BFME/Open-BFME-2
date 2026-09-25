// cl: /O1 /DNDEBUG /MD /GX /arch:SSE

// GpuDrawModuleInfo::DoXfer, retail 0x0056390A (64B). BFME2-new class (no
// BFME1 donor). Member semantics from the writeINI field strings at
// 0x00563D3F: TotalFrames, FramesPerRow, DetailTexture, SpeedMultiplier,
// matching the default ctor's 1, 1, 0, 1.0f. Occupies the GpuDraw vtable
// (0xC1C1E8) slots 0xC/0x2C. Xfer declaration is the UpdateModuleXfer-proven
// spelling; Version1 resolves to the rowed 0x53EE.

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

// AsciiString with its inline nulling default, as retail's TU sees it: the
// default ctor (rowed 6B at 0x326BE6, `m_text = 0`) folds into the member
// slot with no out-of-line call, and the member transfers via ==AsciiString.
class AsciiString
{
public:
    AsciiString() { m_text = 0; }
    ~AsciiString();

private:
    char *m_text;
};

namespace FXParticleSystem
{

class GpuDrawModuleInfo
{
public:
    virtual void DoXfer(Xfer &xfer);
    virtual ~GpuDrawModuleInfo();

private:
    int m_totalFrames;
    int m_framesPerRow;
    AsciiString m_detailTexture;
    float m_speedMultiplier;
};

// ?DoXfer@GpuDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void GpuDrawModuleInfo::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_totalFrames;
    xfer == m_framesPerRow;
    xfer == m_detailTexture;
    xfer == m_speedMultiplier;
}

}
