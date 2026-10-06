// cl: /MD
//
// ?xfer@Rva003424B1@@MAEXPAVXfer@@@Z, retail 0x003424B1, 81 bytes.
// Chain from 0x0033FF76 (Rva0033FF2B::xfer). Derived xfer calling
// Xfer::Version1 via rowed 0x000053EE then bools at +0x55/+0x54/+0x4C via
// slot 0x90 then int at +0x50 via slot 0x7C then base Rva0033FF2B xfer via
// rowed 0x0033FF76 last. Prev/next are Rva00341E22Xfer/Rva00342502Xfer
// (/O1 /MD). Layout is base 0x4C plus bool plus pad plus int plus bools.
// Identity is base-call plus Version1; class stays honest Rva with xfer.

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

class Rva0033FF2B
{
public:
	virtual ~Rva0033FF2B();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x4C - 0x04];
};

class Rva003424B1 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_4C;
	char m_pad4D[0x50 - 0x4D];
	int m_50;
	bool m_54;
	bool m_55;
};

void Rva003424B1::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_55;
	*xfer == m_54;
	*xfer == m_4C;
	*xfer == m_50;
	Rva0033FF2B::xfer(xfer);
}
