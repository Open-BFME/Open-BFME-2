// cl: /MD
// ?rva005644A9@Rva005644A9@@QAEXPAVXfer@@@Z, retail 0x005644A9, 96 bytes.
// Chain xfer after 0x0056445E: Version1 via rowed 0x000053EE plus subobject at +0x20 via rowed TerrainCollisionModuleInfo xfer 0x0056445E plus bools at +0x1c +0x1d +0x34 +0x40 via Xfer slot 0x90 plus uint at +0x3c via Xfer slot 0x78. Caller at 0x003ABEC7. Pattern from PoisonedBehaviorXfer and Rva00564522Xfer.
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

namespace FXParticleSystem {
class TerrainCollisionModuleInfo
{
public:
	void rva0056445E(Xfer *xfer);
};
}

class Rva005644A9
{
public:
	void rva005644A9(Xfer *xfer);
};

void Rva005644A9::rva005644A9(Xfer *xfer)
{
	xfer->Version1();
	((FXParticleSystem::TerrainCollisionModuleInfo *)((char *)this + 0x20))->rva0056445E(xfer);
	*xfer == *(bool *)((char *)this + 0x1c);
	*xfer == *(bool *)((char *)this + 0x1d);
	*xfer == *(bool *)((char *)this + 0x34);
	*xfer == *(bool *)((char *)this + 0x40);
	*xfer == *(unsigned int *)((char *)this + 0x3c);
}
