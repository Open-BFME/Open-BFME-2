// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z retail 0x00050B74 183 bytes.
// GeometryInfo five-argument constructor: installs the BC4E94 vtable, default
// constructs the shape and record vectors at +0x2C/+0x38, delegates extents to
// the rowed five-argument set at 0x6BFF50, then zeroes the +0x44/+0x48 cache,
// stores the height-scaled +0x4C through the height-scale global, zeroes the
// +0x50/+0x54/+0x58 tail in order, and erases the record vector through the
// rowed 0x50AF7. Direct reuse of the BFME1 GeometryInfoConstructor.cpp donor
// (retail 0x00100580 there); the ordered volatile tail keeps the scaled height
// live on the x87 stack across the two preceding zero stores.

#include <vector>

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

struct AsciiString
{
	~AsciiString();

	char *m_data;
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	char m_unmodelled00c[0x0C];
	Real m_offsetZ;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
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

extern Real g_geometryHeightScale;

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

private:
	Bool m_isSmall;
	Real m_scalar08;
	Real m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	Real m_cached44;
	Real m_cached48;
	Real m_cached4c;
	Real m_cached50;
	Real m_cached54;
	Real m_cached58;
};

GeometryInfo::GeometryInfo(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	m_scalar08 = 0;
	m_scalar0c = 0;
	std::vector<GeometryRecord> *records = &m_records;
	set(type, isSmall, height, majorRadius, minorRadius);
	Real scaledHeight = *(volatile Real *)&height * g_geometryHeightScale;
	m_cached44 = 0;
	m_cached48 = 0;
	m_cached4c = scaledHeight;
	m_cached50 = 0;
	m_cached54 = 0;
	m_cached58 = 0;
	records->erase(records->begin(), records->end());
}
