// cl: /MD
//
// ?xfer@Rva00485BD4@@MAEXPAVXfer@@@Z, retail 0x00485BD4 69B: Version(1,2) via Xfer slot 0x28
// then base Rva0045CE8C xfer via rowed 0x0045CE8C then uint at +0x14 via Xfer slot 0x78
// then version-gated helper Rva00485BB8 xfer via rowed 0x00485BB8 with this+0x14.
// Evidence: slot 3 of vtable 0x0084A8D4 (class of rowed ??1Rva00485983 in Rva0048593DDerived.cpp);
// callees rowed 0x000053EE/0x0045CE8C/0x00485BB8; class unproven so honest Rva name.
// Recipe is the Rva0049B2A2 Version(1,2) pattern with helper call for the gated tail.
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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva0045CE8C
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x14 - 4];
};

class Rva00485BB8
{
public:
	void xfer(Xfer *xfer);

	unsigned int m_00;
};

class Rva00485BD4 : public Rva0045CE8C
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva00485BB8 m_14;
};

void Rva00485BD4::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	Rva0045CE8C::xfer(xfer);
	*xfer == m_14.m_00;
	if (version.m_minimum >= 2) {
		m_14.xfer(xfer);
	}
}
