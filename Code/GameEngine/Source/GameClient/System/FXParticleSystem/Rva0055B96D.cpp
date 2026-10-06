// cl: /MD
//
// ?rva0055B96D@Rva0055BC8B@@UAEXPAVXfer@@@Z, retail 0x0055B96D, 80 bytes.
// Evidence: slot 3 of 0x0081D1A4 (class of Rva0055BC8B ctor); IsLightCRC
// early-out via Xfer slot 0x10 plus Version1 rowed 0x000053EE plus Xfer
// slots 0x3C RGBColor and 0x78 uint over 8x0x10 elems at +0x04/+0x10 plus
// float at +0x84 via slot 0x70; caller 0x0055BB7A.
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

class RGBColor
{
public:
	int m_color;
};

struct Rva0055BC8BElem
{
	RGBColor m_a;
	char m_pad[8];
	unsigned int m_b;
};

class Rva0055BC8B
{
	Rva0055BC8BElem m_elems[8];
	float m_trailing;
public:
	virtual void rva0055B96D(Xfer *xfer);
};

void Rva0055BC8B::rva0055B96D(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	unsigned int *pVal = &m_elems[0].m_b;
	int n = 8;
	do {
		*xfer == *(RGBColor *)(pVal - 3);
		*xfer == *pVal;
		pVal += 4;
	} while (--n != 0);
	*xfer == m_trailing;
}
