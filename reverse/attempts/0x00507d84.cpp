// ?rva00507D84@Made002CC5E1@@UAEXPAXPBUCoord3D@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Retail 0x00507D84 (924B, ret 8): Made002CC5E1 (DamageNugget) vtable 0x00864048
// slot 6, the position effect that slot 5 (0x00507991) hands the target's
// +0x38 position to. WorldBuilder's debug build names it
// DamageNugget::doEffectPosition (DamageNugget.cpp).
// Target body: radius = max(+0x130, 1); source = the weapon's +0x08 object id.
// Partition mode 1 when +0x1A0 is set, else 4 for radius >= 10 unless the
// source has template bytes +0x11D&8 and +0x10A&0x20 and a contain, else 3.
// Objects in range through the rowed kind-of filter 0x0004584D (none-mask
// 0x009FEFA4, bits 0x59/0x36 from 0x0006EE7A) are skipped outside the +0x138
// cone around source->position (the transform X axis when the position
// coincides; +0x13C inverts the test, PI disables it), when slot 1 refuses,
// when they stand more than +0x140 above the source or +0x144 above terrain
// (-1 disables each), or inside +0x134; slot 14 (0x005084FC) applies the
// damage and a hit stops the walk when TheGlobalData +0xB40 >= radius.
// Offsets/slots/constants from the native body; meanings are readings.
typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x, y, z;
	Real length() const;
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real Length2() const { return X * X + Y * Y + Z * Z; }
	void Normalize();
	Real X, Y, Z;
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

__forceinline void Vector3::Normalize()
{
	Real len2 = Length2();
	if (len2 != 0.0f)
	{
		Real oolen = WWMath::Inv_Sqrt(len2);
		X *= oolen;
		Y *= oolen;
		Z *= oolen;
	}
}

inline Real Dot_Product(const Vector3 &a, const Vector3 &b)
{
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

Real Cos(Real angle);

enum ObjectID { INVALID_ID = 0 };

class Rva00507D84TemplateView
{
public:
	unsigned char pad00[0x10A];
	unsigned char kind10A;
	unsigned char pad10B[0x11D - 0x10B];
	unsigned char kind11D;
};

class Thing
{
public:
	Real getHeightAboveTerrain() const;
};

class Object : public Thing
{
public:
	Real rva002615E3(const Coord3D *position) const;
	const Coord3D *getPosition() const { return &m_position; }
	unsigned char pad00[4];
	Rva00507D84TemplateView *m_template;	// +0x04
	Real m_transform[3][4];			// +0x08
	Coord3D m_position;			// +0x38
	unsigned char pad44[0x250 - 0x44];
	void *m_contain;			// +0x250
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char pad00[0xB40];
	Real m_singleTargetRadius;		// +0xB40
};
extern GlobalData *TheGlobalData;

class Rva000421C8
{
public:
	~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(Int unused, Int bit1, Int bit2);
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &mustBeSet, const BfmeFixedStorage0004543D &mustBeClear);
	virtual bool allow(Object *obj);
private:
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeWideResult
{
	~BfmeWideResult();
	Object *next();
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, Real radius, Int mode, Rva000421C8 *filter, Int flags);
};
extern PartitionManager *ThePartitionManager;

struct Rva00507D84WeaponView
{
	unsigned char pad00[8];
	ObjectID sourceID08;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
};

class Made002CC5E1 : public Rva00507823
{
public:
	virtual Bool v1(void *weapon, Object *target);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void rva00507D84(void *weapon, const Coord3D *position);
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual Bool v14(void *weapon, Object *target, const Coord3D *position);
private:
	unsigned char pad04[0x130 - 4];
	Real m_radius130;
	Real m_minRange134;
	Real m_coneAngle138;
	Bool m_invertCone13C;
	unsigned char pad13D[3];
	Real m_maxHeightAbove140;
	Real m_maxAltitude144;
	unsigned char pad148[0x1A0 - 0x148];
	Bool m_flag1A0;
};

void Made002CC5E1::rva00507D84(void *weapon, const Coord3D *position)
{
	Real radius = m_radius130;
	if (1.0f > radius)
		radius = 1.0f;
	Object *source = TheGameLogic->findObjectByID(static_cast<Rva00507D84WeaponView *>(weapon)->sourceID08);
	Int mode = 3;
	if (m_flag1A0)
		mode = 1;
	else if (radius >= 10.0f)
	{
		if (!(source->m_template->kind11D & 8) || !(source->m_template->kind10A & 0x20) || !source->m_contain)
			mode = 4;
	}
	Rva0004584D filter(g_defaultStorage009FEFA4, BfmeFixedStorage0004543D(0, 0x59, 0x36));
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(position, radius, mode, &filter, 0);
	Object *obj;
	while ((obj = iter.next()) != 0)
	{
		if (m_coneAngle138 < 3.14159265359f)
		{
			Coord3D toObj;
			toObj.x = obj->m_position.x - position->x;
			toObj.y = obj->m_position.y - position->y;
			toObj.z = obj->m_position.z - position->z;
			Coord3D delta;
			delta.x = position->x - source->m_position.x;
			delta.y = position->y - source->m_position.y;
			delta.z = position->z - source->m_position.z;
			Vector3 facing(delta.x, delta.y, delta.z);
			if (delta.length() == 0.0f)
				facing = Vector3(source->m_transform[0][0], source->m_transform[1][0], source->m_transform[2][0]);
			Vector3 dir(toObj.x, toObj.y, toObj.z);
			facing.Normalize();
			dir.Normalize();
			Real dot = Dot_Product(dir, facing);
			if (!(dot >= Cos(m_coneAngle138)))
			{
				if (!m_invertCone13C)
					continue;
			}
			else if (m_invertCone13C)
				continue;
		}
		if (!v1(weapon, obj))
			continue;
		if (m_maxHeightAbove140 != -1.0f)
		{
			Real sourceZ = source->getPosition()->z;
			if (obj->getPosition()->z - sourceZ > m_maxHeightAbove140)
				continue;
		}
		if (m_maxAltitude144 != -1.0f)
		{
			obj->getHeightAboveTerrain();
			if (obj->getHeightAboveTerrain() > m_maxAltitude144)
				continue;
		}
		if (m_minRange134 > 0.0f)
		{
			Real minRange = m_minRange134;
			if (obj->rva002615E3(position) < minRange * minRange)
				continue;
		}
		if (!v14(weapon, obj, position))
			continue;
		if (TheGlobalData->m_singleTargetRadius >= radius)
			break;
	}
}
