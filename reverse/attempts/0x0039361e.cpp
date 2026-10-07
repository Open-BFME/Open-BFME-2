// ?rva0039361E@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@H@Z
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfmelist /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0039361E@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@H@Z 291B @0x0039361E: virtual slot 18 of BuildAssistant (vtable 0x0081A088). Donor Zero Hour Common/System/BuildAssistant.cpp isLocationClearOfObjects/moveObjects pattern via PartitionFilterWouldCollide plus iterateObjectsInRange plus relationship plus distance. Evidence: vtable slot 18 plus rowed callees plus ThePartitionManager plus 1.1f/0.5f literals plus caller-free loop returning bool.
typedef bool Bool;
typedef float Real;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
	float length() const;
};

class GeometryInfo
{
public:
	__forceinline float getRadiusAt10() const { return m_radius10; }
	__forceinline float getBoundingSphereRadius() const { return m_boundingSphereRadius; }
private:
	char m_pad00[0x10];
	float m_radius10;
	float m_boundingSphereRadius;
	char m_pad18[0x5C - 0x18];
};

class ThingTemplate
{
public:
	__forceinline const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	__forceinline Bool isKindOf(Int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad00[0xA0];
	GeometryInfo m_geometryInfo;
	char m_padFC[0x108 - 0xFC];
	unsigned char m_kindOf[0x20];
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;
class Player;

class Object
{
public:
	__forceinline const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline const Coord3D *getPosition() const { return &m_position; }
	Relationship getRelationship(const Object *other) const;
	void *rva0028BCF4() const;
private:
	char m_pad00[4];
	const ThingTemplate *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;
};

class Player
{
public:
	char m_pad[4];
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

struct FilterPosition : public Coord3D
{
	FilterPosition(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
};

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
	virtual Bool allow(Object *objOther);
private:
	FilterPosition m_position;
	const GeometryInfo &m_geom;
	Real m_angle;
	Bool m_desiredCollisionResult;
};

inline Rva000421C8 *filterAddr(const Rva00261603Filter &f) { return (Rva000421C8 *)&f; }

struct BfmeWideResult
{
	Object *next();
	~BfmeWideResult();
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distType, Rva000421C8 *filters, int order);
};
extern PartitionManager *ThePartitionManager;

class Rva0028BCF4Iface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual Bool v03() = 0;
};

class BuildAssistant
{
public:
	Bool rva0039361E(const Coord3D *pos, const ThingTemplate *build, float angle, Object *builder, int unused);
};

Bool BuildAssistant::rva0039361E(const Coord3D *pos, const ThingTemplate *build, float angle, Object *builder, int unused)
{
	Bool found = false;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, build->getTemplateGeometryInfo().getBoundingSphereRadius() * 1.1f, 3, filterAddr(Rva00261603Filter(*pos, build->getTemplateGeometryInfo(), angle, true)), 0);
	for (Object *them = hits.next(); them; them = hits.next())
	{
		if (!them->getTemplate()->isKindOf(104))
			continue;
		if (builder->getRelationship(them) != ALLIES)
			continue;
		void *iface = them->rva0028BCF4();
		if (iface)
		{
			if (((Rva0028BCF4Iface *)iface)->v03())
				continue;
		}
		Coord3D diff;
		diff.x = them->getPosition()->x - pos->x;
		diff.y = them->getPosition()->y - pos->y;
		diff.z = them->getPosition()->z - pos->z;
		float dist = diff.length();
		float rad = them->getTemplate()->getTemplateGeometryInfo().getRadiusAt10() * 0.5f;
		if (rad > dist)
		{
			found = true;
			break;
		}
	}
	return found;
}
