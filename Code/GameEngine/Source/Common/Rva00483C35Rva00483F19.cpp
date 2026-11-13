// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// ?rva00483F19@ClearanceTestingSlowDeathBehavior@@UAE_NXZ, retail 0x00483F19, 555 bytes.
// Target evidence: slot 6 of vtable 0x00C49D70 (the trailing interface base
// of ClearanceTestingSlowDeathBehavior, see Rva00483C35Rva00483DA4.cpp), the
// subobject this at +0x24 reads module data (+4) and object (+8) as [ecx-0x20]
// and [ecx-0x1C]. The WorldBuilder build (ClearanceTestingSlowDeathBehavior.cpp)
// shows a clearance test: the 0x1EC point of the module data transformed into
// the world, a closest-object query over a would-collide filter chained with
// a second (airborne) filter, then (when the terrain exists and either
// fraction limit is below 1) a grid walk of the footprint comparing the object
// height against the terrain layer height at module data +0x1F8/+0x200 and the
// high/low fractions against +0x1FC/+0x204.
#include "Common/Snapshot.h"
#include "vector3.h"
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "PartitionRangeQueryCallView.h"

typedef bool Bool;
typedef float Real;
enum PathfindLayerEnum { LAYER_GROUND = 1 };

#include "../../Include/Common/Geometry.h"

#include "Thing/thing.h"

#include "../GameLogic/Object/object.h"

struct Rva00483C35ClearanceData
{
	unsigned char m_pad000[0x190];
	GeometryInfo m_geometry;
	Coord3D m_clearanceGeometryOffset;
	float m_clearanceMaxHeight;
	float m_clearanceMaxHeightFraction;
	float m_clearanceMinHeight;
	float m_clearanceMinHeightFraction;
};

#include "../../Include/GameLogic/PartitionFilter.h"

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
	virtual bool allow(Object *obj);
	unsigned char m_pad[0x18];
};

class Rva00483C9FFilter : public Rva000421C8
{
public:
	Rva00483C9FFilter(Object *obj, char value) : m_object(obj), m_value(value) {}
	virtual bool allow(Object *obj);
	Object *m_object;
	char m_value;
};


#include "../../Include/GameLogic/TerrainLogic.h"

class Rva004DC1BF
{
public:
	GeometryInfo geometry;
	unsigned char m_rest[0xB4 - 0x5C];
	Rva004DC1BF(const GeometryInfo &, float, const Vector3 &);
	bool rva004DC096(Coord2D *out);
};

struct Rva00483F19Probe : Coord3D
{
	Rva00483F19Probe(float px, float py, float pz)
	{
		x = px;
		y = py;
		z = pz;
	}
};

extern PartitionManager *ThePartitionManager;
extern TerrainLogic *TheTerrainLogic;

struct B00 { virtual void f00(); Rva00483C35ClearanceData *m_moduleData; Object *m_object; };
#include "../../Include/Common/B0C.h"
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
struct B20 { virtual void f20(); };
struct B24
{
	virtual void f24();
	virtual void f28();
	virtual void f2C();
	virtual void f30();
	virtual void f34();
	virtual void f38();
	virtual bool rva00483F19() = 0;
	unsigned char m_pad[0x50 - 0x2C];
};
class Iface50
{
public:
	virtual void s00();
};
class ClearanceTestingSlowDeathBehavior : public B00, public B0C, public B10, public B20, public B24, public Iface50
{
public:
	virtual bool rva00483F19();
};

bool ClearanceTestingSlowDeathBehavior::rva00483F19()
{
	Rva00483C35ClearanceData *md = m_moduleData;
	Object *obj = m_object;
	if (0 == obj)
		return false;
	Coord3D center;
	obj->transformPoint(&md->m_clearanceGeometryOffset, &center);
	float base = md->m_geometry.m_boundingSphereRadius;
	float radius = base * 1.1f;
	if (ThePartitionManager->getClosestObject(&center, radius, 3,
			Rva00483C9FFilter(obj, obj->rva00294815()).link(&
				Rva00261603Filter(center, md->m_geometry, obj->m_cachedAngle, true))))
		return false;
	if (1.0f >= md->m_clearanceMaxHeightFraction || 1.0f >= md->m_clearanceMinHeightFraction)
	{
		if (TheTerrainLogic != 0)
		{
			int total = 0, high = 0, low = 0;
			float z = obj->m_cachedPos.z;
			Rva004DC1BF sampler(md->m_geometry, obj->m_cachedAngle, *(const Vector3 *)&center);
			Coord2D pt;
			while (sampler.rva004DC096(&pt))
			{
				++total;
				float h = TheTerrainLogic->getLayerHeight(pt.x, pt.y,
					TheTerrainLogic->getHighestLayerForDestination(&Rva00483F19Probe(pt.x, pt.y, z), false), 0, true);
				if (z + md->m_clearanceMaxHeight < h)
					++high;
				else if ((z + md->m_clearanceMinHeight > h))
					++low;
			}
			if (total != 0)
			{
				if ((float)high / (float)total >= md->m_clearanceMaxHeightFraction || (float)low / (float)total >= md->m_clearanceMinHeightFraction)
					return false;
			}
		}
	}
	return true;

 if (0) throw 1;
}
