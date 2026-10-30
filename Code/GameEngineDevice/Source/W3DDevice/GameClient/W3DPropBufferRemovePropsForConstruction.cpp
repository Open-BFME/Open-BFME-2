// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRemovePropsForConstruction.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x000EF154 (278B).
// Open-BFME: BFME W3DPropBuffer construction clearing, BFME 1 retail 0x007039E0.

#include <vector>

typedef float Real;
typedef bool Bool;

// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"

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
class BfmeRenderObj
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

struct BfmeProp
{
	BfmeRenderObj *m_robj;
	int id;
	Coord3D location;
	int prop_type;
	int shroud_status;
	int visible;
	SphereClass bounds;
};

class W3DPropBuffer
{
public:
	void removePropsForConstruction(const Coord3D *pos,
		const GeometryInfo &geom, Real angle);

private:
	void *m_snapshot_vtable;
	BfmeProp m_props[4000];
	int m_num_props;
	Bool m_anything_changed;
};

void W3DPropBuffer::removePropsForConstruction(const Coord3D *pos,
	const GeometryInfo &geom, Real angle)
{
	int i;
	for (i = 0; i < m_num_props; ++i)
	{
		if (m_props[i].m_robj == 0)
			continue;

		Real radius = m_props[i].bounds.Radius;
		GeometryInfo info(GEOMETRY_CYLINDER, false,
			5 * radius, 2 * radius, 2 * radius);

		if (geom.CollidesWith(*pos, angle, info,
			m_props[i].location, 0.0f))
		{
			m_props[i].location.set(0, 0, 0);
			BfmeRenderObj *robj = m_props[i].m_robj;
			m_props[i].prop_type = -1;
			if (robj != 0)
			{
				robj->Release_Ref();
				m_props[i].m_robj = 0;
			}
			m_props[i].bounds.Center.set(0, 0, 0);
			m_props[i].bounds.Radius = 1;
			m_anything_changed = true;
		}
	}
}
