// cl: /MD
//
// ?xfer@Rva00341930@@MAEXPAVXfer@@@Z,
// retail 0x00341930, 73 bytes. Dedicated TU.
// Version(1,2) via Xfer slot 0x28 then base Rva0033FF2B xfer via rowed
// 0x0033FF76 then ObjectID at +0x4C via rowed XferObjectID 0x003060B2
// then version>=2 uint at +0x50 via Xfer slot 0x78. Prev is our
// Rva00341557 (/O1 /MD) and next is Rva0049B47CDerived (/O1 /MD).
// Identity is base-call plus Version plus ObjectID; class stays honest Rva.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva0033FF2B
{
public:
	virtual ~Rva0033FF2B();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x4C - 0x04];
};

class Rva00341930 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_4C;
	unsigned int m_50;
};

// ?xfer@Rva00341930@@MAEXPAVXfer@@@Z
void Rva00341930::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	Rva0033FF2B::xfer(xfer);
	XferObjectID(xfer, &m_4C);
	if (version.m_minimum >= 2) {
		*xfer == m_50;
	}
}
