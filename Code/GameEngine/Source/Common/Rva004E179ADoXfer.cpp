// cl: /O1 /DNDEBUG /MD /EHsc
// ?DoXfer@Rva004E179A@@UAEXAAVXfer@@@Z retail 0x004E1398 83B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61B78 (class of unrowed dtor ??1 at 0x004E179A
// tearing down AsciiStrings at +0x0C then +0x08 then +0x04 before restoring
// Snapshot base 0x00BBB554). Snapshot order is dtor plus LoadPostProcess plus
// GetSnapshotName plus DoXfer per LivingWorldRegionConnectionDtor; slot 1 is
// the shared empty ret at 0x000B3FD0 and slot 2 is the rowed string getter at
// 0x004E1794 returning SpawnBuilding. Body is Version 1 1 via Xfer slot 0x28
// then AsciiString at +0x04 via Xfer slot 0x6C then AsciiString at +0x08 via
// Xfer slot 0x6C then AsciiString at +0x0C via Xfer slot 0x6C then bool at
// +0x10 via Xfer slot 0x90. Xfer declaration mirrors GpuDrawModuleInfoDoXfer
// for retail vtable 0x00BBB910. Layout is three AsciiStrings at +4/+8/+0x0C
// plus bool at +0x10.

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004E179ABase
{
public:
	virtual ~Rva004E179ABase() {}
};

class Rva004E179A : public Rva004E179ABase
{
public:
	virtual ~Rva004E179A();
	virtual void DoXfer(Xfer &xfer);

	AsciiString m_member04;
	AsciiString m_member08;
	AsciiString m_member0C;
	bool m_bool10;
};

void Rva004E179A::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_member08;
	xfer == m_member0C;
	xfer == m_bool10;
}
