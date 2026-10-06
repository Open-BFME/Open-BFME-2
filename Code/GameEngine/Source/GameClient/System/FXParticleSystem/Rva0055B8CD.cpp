// cl: /MD
//
// ?rva0055B8CD@Rva0055B8CD@@QAEXPAVXfer@@@Z, retail 0x0055B8CD, 70 bytes.
// Evidence: vtable slots 7 of 0x0081BF20 plus 3 of 0x0081BA90 (DoXfer);
// callee Version1 rowed 0x000053EE plus Xfer slots 0x3C RGBColor and 0x78 uint
// over 8x0x10 elems at +0x04/+0x10 plus xferRandomVariable rowed 0x00306183
// with GameClientRandomVariable at +0x84; Ghidra DoXfer 70B; caller 0x0055B951.
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

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

class RGBColor
{
public:
	int m_color;
};

struct Rva0055B8CDElem
{
	RGBColor m_a;
	char m_pad[8];
	unsigned int m_b;
};

class Rva0055B8CD
{
	Rva0055B8CDElem m_elems[8];
	GameClientRandomVariable m_var;
public:
	virtual void rva0055B8CD(Xfer *xfer);
};

void Rva0055B8CD::rva0055B8CD(Xfer *xfer)
{
	xfer->Version1();
	unsigned int *pVal = &m_elems[0].m_b;
	int n = 8;
	do {
		*xfer == *(RGBColor *)(pVal - 3);
		*xfer == *pVal;
		pVal += 4;
	} while (--n != 0);
	xferRandomVariable(*xfer, m_var);
}
