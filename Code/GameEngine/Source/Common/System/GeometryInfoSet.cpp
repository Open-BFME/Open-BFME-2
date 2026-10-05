// cl: /O2 /DNDEBUG /MD /GX- /Ob2
// ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z retail 0x006BFF50 223 bytes.
// GeometryInfo five-argument extent setter: stores isSmall at +4, ensures the
// 0x24-byte shape vector at +0x2C holds one element through the rowed
// BfmeVec60::resize at 0x006BFCB0, assigns a stack GeometryShape built from
// (type height major (BOX?minor:major) center-0 name-0 enabled-1 flag-1)
// through the rowed GeometryShape::operator= at 0x00063627, recomputes extents
// through the rowed calcBoundingStuff at 0x006BE700, then destroys the stack
// shape name through the pinned StringBase<char> dtor at 0x00036410.
// Evidence: BFME1 donor Geometry.cpp set plus ZH Geometry.cpp set for the
// (type isSmall height major minor) signature and BOX-minor rule; callers at
// 0x00050BDA in the rowed five-arg ctor and at 0x0029846C; prev/next rows
// GeometryParseType/GeometryParseOther with the same // cl: line.
enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER = 1,
	GEOMETRY_BOX = 2
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

struct BfmeCoord3D
{
	__forceinline BfmeCoord3D() throw() : x(0.0f), y(0.0f), z(0.0f) {}
	float x;
	float y;
	float z;
};

struct BfmeAsciiString
{
	__forceinline BfmeAsciiString() throw() : m_data(0) {}
	char *m_data;
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f),
		  m_minorRadius(1.0f), m_center(), m_name(), m_enabled(true), m_flag21(true)
	{
	}
	__forceinline BfmeElem60(const BfmeElem60 &other) throw()
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_center = other.m_center;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
		m_flag21 = other.m_flag21;
	}
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	BfmeCoord3D m_center;
	BfmeAsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_flag21;
	unsigned char m_padding[2];
};

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value) throw();
	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

struct AsciiString
{
	~AsciiString();
	char *m_data;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_offset;
	char *m_name_data;
	unsigned char m_enabled;
	unsigned char m_byte21;
	unsigned char m_pad[2];
	GeometryShape &operator=(const GeometryShape &other);
};

class GeometryInfo : public Snapshot
{
public:
	void set(GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius);
private:
	void calcBoundingStuff();
	bool m_isSmall;
	char m_pad05[0x27];
	BfmeVec60 m_shapes;
};

#pragma optimize("t", off)
#pragma optimize("s", on)
static __forceinline void DestroyTmpName(AsciiString *p) { p->~AsciiString(); }
#pragma optimize("", on)

void GeometryInfo::set(GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius)
{
	GeometryShape tmp;
	tmp.m_type = type;
	tmp.m_height = height;
	tmp.m_majorRadius = majorRadius;
	tmp.m_minorRadius = (type == GEOMETRY_BOX) ? minorRadius : majorRadius;
	m_isSmall = isSmall;
	BfmeVec60 &shapes = m_shapes;
	tmp.m_offset.x = 0.0f;
	tmp.m_offset.y = 0.0f;
	tmp.m_offset.z = 0.0f;
	tmp.m_name_data = 0;
	tmp.m_enabled = 1;
	tmp.m_byte21 = 1;
	if (shapes.m_end - shapes.m_begin != 1)
		shapes.resize(1, BfmeElem60());
	((GeometryShape *)shapes.m_begin)[0] = tmp;
	calcBoundingStuff();
	DestroyTmpName((AsciiString *)&tmp.m_name_data);
}
