// cl: /DNDEBUG /MD
// ?xfer@Rva00493009@@MAEXPAVXfer@@@Z @0x00493009 151B. versioned xfer
// Version(1,3) via slot 0x28 plus BehaviorModule base via rowed 0x004C9C7D
// plus gated uint at +0x14 plus uints at +0x18/+0x20 plus int at +0x1c
// plus float at +0x24 plus bools at +0x28/+0x30 plus ObjectID at +0x2c
// via rowed XferObjectID 0x003060B2. Evidence: caller 0x004C449E.

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

class BehaviorModule
{
public:
	void xfer(Xfer *xfer);
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00493009
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x10];

public:
	unsigned int m_14;
	unsigned int m_18;
	int m_1c;
	unsigned int m_20;
	float m_24;
	bool m_28;

private:
	unsigned char m_pad29[3];

public:
	ObjectID m_2c;
	bool m_30;
};

void Rva00493009::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	((BehaviorModule *)this)->xfer(xfer);
	if (version.m_minimum >= 2) {
		*xfer == m_14;
	}
	*xfer == m_18;
	*xfer == m_1c;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	XferObjectID(xfer, &m_2c);
	if (version.m_minimum >= 3) {
		*xfer == m_30;
	}
}
