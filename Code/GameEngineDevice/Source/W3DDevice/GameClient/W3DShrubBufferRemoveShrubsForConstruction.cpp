// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// ?rva000E9D18@W3DShrubBuffer@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z @0x000E9D18 228B
// Shrub counterpart of W3DPropBuffer::removePropsForConstruction (W3DPropBufferRemovePropsForConstruction.cpp,
// whose GeometryInfo view this unit copies) and Zero Hour's W3DTreeBuffer::removeTreesForConstruction:
// every live shrub (type >= 0) is tested against a 35 x 14 x 14 cylinder at its location with the construction
// footprint; a hit marks it removed (type -2) and sets the changed flag. Evidence: target bytes and WB debug
// body 00895DB0 (unnamed); shrub layout (location +0, type +0x40, stride 0xA0 from +0x1958 in the buffer,
// count +0x4FB58, changed flag +0x4FB5C) from the rowed W3DShrubBuffer units. The method name is unproven.

#include <vector>

typedef float Real;
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// The canonical Coord3D::set is out of line; retail inlines the three-component store.
static inline void setCoord(Coord3D &c, Real nx, Real ny, Real nz)
{
	c.x = nx;
	c.y = ny;
	c.z = nz;
}

struct Vector3
{
	Real x;
	Real y;
	Real z;

	void set(Real nx, Real ny, Real nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}
};

struct SphereClass
{
	Vector3 Center;
	Real Radius;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_major_radius;
	char m_unmodelled_00c[0x0C];
	Real m_offset_z;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled_21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	StringBase<char> m_name;
	~GeometryRecord();
};

#include "Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> vector<GeometryRecord, allocator<GeometryRecord> >::~vector(); }
namespace _STL { template <> vector<GeometryShape, allocator<GeometryShape> >::~vector(); }
// bfme link decl-only end

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(GeometryType type, Bool is_small, Real height,
		Real major_radius, Real minor_radius);

	Bool CollidesWith(const Coord3D &this_pos, Real this_angle,
		const GeometryInfo &that, const Coord3D &that_pos, Real that_angle) const;

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

private:
	Bool m_is_small;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
public:
	virtual ~GeometryInfo();	// rowed elsewhere; declared so this unit binds to it
};
struct Rva000E9D18Shrub
{
	Coord3D location;
	char m_pad0C[0x34];
	int treeType;	// +0x40
	char m_pad44[0x5C];
};

class W3DShrubBuffer
{
public:
	void rva000E9D18(const Coord3D *pos, const GeometryInfo &geom, Real angle);

private:
	char m_pad0000[0x1958];
	Rva000E9D18Shrub m_shrubs[2000];
	int m_numShrubs;	// +0x4FB58
	Bool m_anythingChanged;	// +0x4FB5C
};

void W3DShrubBuffer::rva000E9D18(const Coord3D *pos, const GeometryInfo &geom, Real angle)
{
	for (int i = 0; i < m_numShrubs; ++i)
	{
		if (m_shrubs[i].treeType < 0)
			continue;

		GeometryInfo info(GEOMETRY_CYLINDER, false, 35.0f, 14.0f, 14.0f);
		Coord3D shrubPos;
		setCoord(shrubPos, m_shrubs[i].location.x, m_shrubs[i].location.y, m_shrubs[i].location.z);
		if (geom.CollidesWith(*pos, angle, info, shrubPos, 0.0f))
		{
			m_shrubs[i].treeType = -2;
			m_anythingChanged = true;
		}
	}
}
