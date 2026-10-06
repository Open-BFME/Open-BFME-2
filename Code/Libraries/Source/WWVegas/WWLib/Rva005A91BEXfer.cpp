// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// ?rva005A91BE@Rva005A91BE@@QAEXPAVXfer@@@Z, retail 0x005A91BE, 87 bytes.
// Xfer-style body: Version(1,2) via Xfer slot 0x28 then count via slot 0x78
// then uint at +0x10 via slot 0x78 then version-gated int at +0x14 via slot 0x7c.
// Layout is vector of 8-byte items at +0x04 with uint at +0x10 and int at +0x14.
// Evidence: virtual slots 0x28/0x78/0x7c match Xfer Version/uint/int ordering,
// mov byte 1/2 plus cmp second byte, sar 3 count, caller 0x00505710.

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

struct Item8
{
	int a;
	int b;
};

class Rva005A91BE
{
public:
	virtual ~Rva005A91BE();
	void rva005A91BE(Xfer *xfer);
private:
	Item8 *m_begin;
	Item8 *m_end;
	Item8 *m_cap;
	unsigned int m_10;
	int m_14;
};

void Rva005A91BE::rva005A91BE(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	unsigned int count = (unsigned int)(m_end - m_begin);
	*xfer == count;
	*xfer == m_10;
	if (version.m_minimum >= 2) {
		*xfer == m_14;
	}
}
