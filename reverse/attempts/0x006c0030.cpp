// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z
// partial score=0.94 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /GX- /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z, retail 0x006C0030, 382 bytes.
// The BC4E94 table installed by the rowed GeometryInfo constructor has the
// GeometryInfo name getter at slot 2 and this function at Snapshot slot 3.
// The rowed ctor/copy ctor/dtor and geometry helpers place the 0x24-byte
// shape vector at +0x2C, with the two trailing Coord3D caches at +0x44/+0x50.
// Target code transfers a shape count, grows that vector through the rowed
// BfmeVec60::resize, then transfers each shape. The local version controls the
// second shape flag. The ZH Geometry.cpp donor establishes the GeometryInfo
// scalar serialization semantics; this body retains the BFME2 Snapshot API
// and target-only shape and cache fields visible in retail.

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

struct Coord3DBase
{
	__forceinline Coord3DBase() throw() : x(0.0f), y(0.0f), z(0.0f) {}
	float x;
	float y;
	float z;
};
typedef Coord3DBase BfmeCoord3D;
typedef Coord3DBase Coord3D;

struct BfmeAsciiString
{
	__forceinline BfmeAsciiString() throw() : m_data(0) {}
	char *m_data;
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f),
		  m_minorRadius(1.0f), m_offset(), m_name(), m_enabled(true), m_flag21(true)
	{
	}
	__forceinline BfmeElem60(const BfmeElem60 &other) throw()
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_offset = other.m_offset;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
		m_flag21 = other.m_flag21;
	}
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	BfmeCoord3D m_offset;
	BfmeAsciiString m_name;
	bool m_enabled;
	bool m_flag21;
	char m_padding[2];
};

typedef char BfmeElem60_size_check[sizeof(BfmeElem60) == 0x24 ? 1 : -1];

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value);
	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

class GeometryInfo : public Snapshot
{
public:
	virtual void DoXfer(Xfer &xfer);
private:
	bool m_isSmall;
	char m_pad05[3];
	int m_scalar08;
	int m_scalar0c;
	float m_boundingCircleRadius;
	float m_boundingSphereRadius;
	Coord3D m_boundsCenter18;
	float m_extent24;
	float m_extent28;
	BfmeVec60 m_shapes;
	char m_records[12];
	Coord3D m_cache44;
	Coord3D m_cache50;
};

// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z present-unmatched
void GeometryInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	xfer == version;
	GeometryInfo *self = this;
	BfmeVec60 *shapes = &self->m_shapes;
	xfer == self->m_isSmall;

	int shapeCount = (int)(shapes->m_end - shapes->m_begin);
	xfer == shapeCount;
	shapes->resize(shapeCount, BfmeElem60());

	BfmeElem60 *shape = shapes->m_begin;
	for (int i = 0; i < shapeCount; ++i, ++shape)
	{
		xfer.XferEnum("GeometryType", &shape->m_type, sizeof(shape->m_type));
		xfer == shape->m_height;
		xfer == shape->m_majorRadius;
		xfer == shape->m_minorRadius;
		xfer == shape->m_offset;
		if (version.m_minimum > 1)
			xfer == shape->m_enabled;
	}

	xfer == self->m_boundingCircleRadius;
	xfer == self->m_boundingSphereRadius;
	xfer == self->m_extent24;
	xfer == self->m_extent28;
	xfer == self->m_boundsCenter18;
	xfer == self->m_cache44;
	xfer == self->m_cache50;
}
