// cl: /MD

// ?xfer@Rva003AFDAA@@UAEXPAVXfer@@@Z @0x003AFDAA 71B: slot 3 (offset 0xC) of
// 0x0081D950 (class of ??1Rva003B0152) and 0x0081DA10 (class of ??1Rva003B0401).
// Xfer declaration is the UpdateModuleXfer-proven spelling (GpuDrawModuleInfoDoXfer).
// Retail order: IsCRC early-out (slot 0xC), Version{1,1} via ==Version (slot 0x28),
// uint temp of member +0x10 via ==uint (slot 0x78), then IsStoring (slot 8).

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
	struct Version
	{
		union
		{
			int i;
			unsigned char b[4];
		};
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

class Rva003AFDAA
{
public:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[12]; // +0x04..0x0F (vptr at +0x0)
	int m_10; // +0x10: transferred as unsigned int
};

void Rva003AFDAA::xfer(Xfer *xfer)
{
	if (xfer->IsCRC())
		return;
	Xfer::Version ver;
	ver.b[0] = 1;
	ver.b[1] = 1;
	*xfer == ver;
	unsigned int tmp = m_10;
	*xfer == tmp;
	xfer->IsStoring();
}
