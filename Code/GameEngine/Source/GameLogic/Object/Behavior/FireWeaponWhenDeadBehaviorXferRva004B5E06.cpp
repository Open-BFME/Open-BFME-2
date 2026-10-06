// cl: /MD
// ?rva004B5E06@Rva004B5E06@@QAEXPAVXfer@@@Z retail 0x004B5E06 64B
// Slot 3 of vtables 0x008581CC 0x008583B0; Version(1 2) via Xfer slot 0x28 gating bool at +0x20 via slot 0x90 then base UpgradeModule xfer.
// Evidence: vtable slot 3 plus Xfer slot order Version 0x28 bool 0x90 from Rva005C45D2 plus rowed UpgradeModule xfer 0x004CE3F9.
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
	class Version
	{
	public:
		unsigned char m_current;
		unsigned char m_minimum;
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

class UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva004B5E06 : public UpgradeModule
{
public:
	void rva004B5E06(Xfer *xfer);
};

void Rva004B5E06::rva004B5E06(Xfer *xfer)
{
	Xfer::Version version;
	version.m_current = 1;
	version.m_minimum = 2;
	*xfer == version;
	if (version.m_minimum >= 2)
		*xfer == *(bool *)((char *)this + 0x20);
	UpgradeModule::xfer(xfer);
}
