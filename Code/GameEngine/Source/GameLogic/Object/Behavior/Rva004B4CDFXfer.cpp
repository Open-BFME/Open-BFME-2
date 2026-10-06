// cl: /DNDEBUG /MD
//
// ?xfer@Rva004B4CDF@@MAEXPAVXfer@@@Z, retail 0x004B4F67, 42 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00857C40 (class of rowed dtor
// ??1Rva004B4CDF@@UAE@XZ in FireWeaponWhenDeadBehaviorDerived.cpp):
// Version1 via rowed 0x000053EE then bool at +0x20 via Xfer slot 0x90
// then base UpgradeModule xfer via rowed 0x004CE3F9. Layout is UpgradeModule
// base 0x1C plus pad to +0x20 with bool there (loadPostProcess in the donor
// TU tests byte at +0x20). Identity is slot 3 plus the UpgradeModule base
// call; shape follows GeometryUpgradeXfer/ReplaceSelfUpgradeXfer (Version
// plus base via 0x004CE3F9) with Version1-plus-bool order as retail shows.

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

class UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C - 4];
};

class Rva004B4CDF : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad1C[0x20 - 0x1C]; // +0x1C..+0x1F
	bool m_flag20; // +0x20
};

void Rva004B4CDF::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag20;
	UpgradeModule::xfer(xfer);
}
