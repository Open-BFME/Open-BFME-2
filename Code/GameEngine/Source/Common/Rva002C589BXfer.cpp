// cl: /DNDEBUG /MD
// ?rva002C5B46@Rva002C589B@@QAEXPAVXfer@@@Z @0x002C5B46 217B: Version(1,2)
// via slot 0x28 then uint global g_00DFEFC0 plus members +4/+8 uint via
// slot 0x78 Coord at +C via 0x60 bools +18/+19 via 0x90 ints +1C/+20 via
// 0x7C uint +2C via 0x78 version>=2 float +28 via 0x70 int +30 via 0x7C
// ObjectID +34 via rowed XferObjectID 0x003060B2 uint +38 via 0x78.
// Evidence: prev/next Rva002C589BDtor.cpp layout plus rowed XferObjectID
// plus Version(1,2) bytes 1/2 plus slot pattern from Rva00340E97Xfer.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	OBJECTID_NONE = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
};

extern unsigned int g_00DFEFC0;
// g_00DFEFC0: matched references place it at VA 0xdfefc0 (zero-filled .bss).
unsigned int g_00DFEFC0;

class Rva002C589B
{
public:
	void rva002C5B46(Xfer *xfer);

private:
	int m_00;
	unsigned int m_04;
	unsigned int m_08;
	Coord3DBase m_0C;
	bool m_18;
	bool m_19;
	char m_pad1A[2];
	int m_1C;
	int m_20;
	Rva003ECDB7Object *m_24;
	float m_28;
	unsigned int m_2C;
	int m_30;
	ObjectID m_34;
	unsigned int m_38;
};

void Rva002C589B::rva002C5B46(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == g_00DFEFC0;
	{
		unsigned int tmp = m_04;
		*xfer == tmp;
		m_04 = tmp;
	}
	*xfer == m_08;
	*xfer == m_0C;
	*xfer == m_18;
	*xfer == m_19;
	*xfer == m_1C;
	*xfer == m_20;
	{
		unsigned int tmp = m_2C;
		*xfer == tmp;
		m_2C = tmp;
	}
	if (version.m_minimum >= 2)
		*xfer == m_28;
	*xfer == m_30;
	XferObjectID(xfer, &m_34);
	*xfer == m_38;
}
