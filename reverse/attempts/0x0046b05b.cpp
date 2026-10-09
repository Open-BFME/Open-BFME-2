// ?rva0046B05B@Rva0046E6EA@@QAEXPAURva0046E6EAObject@@PBURva0046E6EACoord@@PAU3@@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
//
// NEAR draft (not exact): 2010 of 2037 bytes; same control flow, frame (0x78) and
// stack slots as retail. Remaining: SSE register allocation and operand order in
// the target = start + dir*r block (retail loads dir.x/dir.y into xmm0/xmm1 and
// multiplies by r in xmm2), in the three inline Matrix3D transforms (retail term
// order row[2]*z first, local.x spilled to the dir slot before fabs), and in the
// owner-direction block (retail builds it in the dir slot before normalize).
// ?rva0046B05B@Rva0046E6EA@@QAEXPAURva0046E6EAObject@@PBURva0046E6EACoord@@PAU3@@Z,
// retail 0x0046B05B 2037B. HordeContain (the Rva0046E6EA receiver: the matched
// caller 0x0046E6EA takes its +0x11C interface; the body ends in the rowed
// HordeContain::rva00468B24 on the same this) computes where a horde member
// lands when it moves toward a point.
// Identities beyond the rowed callees stay address-derived.
#include <math.h>

// class-gate: allow Coord3D canonical header is data-only; this body calls the
// rowed Coord3D::length (0x00003571) normalize (0x000035B6) and
// GetLengthEstimate (0x00003ACE) thiscalls on stack Coord3Ds.
struct Coord3D
{
	float x;
	float y;
	float z;
	float length() const;
	void normalize();
	float GetLengthEstimate() const;
};

class Matrix3D
{
public:
	void Get_Orthogonal_Inverse(Matrix3D &set_inverse) const;
	float Row[3][4];
};

__forceinline void Rva0046B05BTransform(const Matrix3D &m, Coord3D *v)
{
	float x = v->x;
	float y = v->y;
	float z = v->z;
	v->x = m.Row[0][0] * x + m.Row[0][1] * y + m.Row[0][2] * z + m.Row[0][3];
	v->y = m.Row[1][0] * x + m.Row[1][1] * y + m.Row[1][2] * z + m.Row[1][3];
	v->z = m.Row[2][0] * x + m.Row[2][1] * y + m.Row[2][2] * z + m.Row[2][3];
}

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
	char m_pad00[0x10];
	float m_10;                 // +0x10
	char m_pad14[0x24 - 0x14];
	float m_majorRadius;        // +0x24
};

enum KindOfType
{
	KINDOF_67 = 0x67,
	KINDOF_69 = 0x69
};

enum ObjectID
{
	INVALID_ID = 0
};

struct Rva0046B05BTemplate
{
	char m_pad000[0x11A];
	unsigned short m_11A;       // +0x11A
	unsigned char m_11C;        // +0x11C
	char m_pad11D[0x121 - 0x11D];
	unsigned char m_121;        // +0x121
};

class Rva002627E8
{
public:
	float rva002627E8() const;
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
	bool isSignificantlyAboveTerrain() const;
	Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *other) const;

	void *m_vtbl;
	const Rva0046B05BTemplate *m_template;  // +0x04
	Matrix3D m_transform;                   // +0x08
	Coord3D m_position;                     // +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_74;                          // +0x74
	char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geometry;                // +0xA8
	char m_padD4[0x258 - 0xA8 - sizeof(GeometryInfo)];
	Rva002627E8 *m_258;                     // +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;                    // +0x438
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
	virtual float getGroundHeight(float x, float y, Coord3D *normal); // +0x18
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class Pathfinder
{
public:
	void *rva001E4461(int layer, int pos);
};

class AI
{
public:
	Pathfinder *getPathfinder() { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;               // +0x10
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern GameLogic *TheGameLogic;

class HordeContain
{
public:
	void rva00468B24(float value);
};

struct Rva0046E6EAObject;
struct Rva0046E6EACoord;

class Rva0046E6EA
{
public:
	void rva0046B05B(Rva0046E6EAObject *objectView, const Rva0046E6EACoord *positionView, Rva0046E6EACoord *otherView);
	char m_pad00[8];
	Object *m_object;                       // +0x08
	char m_pad0C[0x2F0 - 0x0C];
	ObjectID m_2F0;                         // +0x2F0
};

__forceinline Object *Rva0046B05BFindAt(PathfindLayerEnum layer, const Coord3D *pos)
{
	return TheGameLogic->findObjectByID((ObjectID)(int)TheAI->getPathfinder()->rva001E4461(layer, (int)pos));
}

void Rva0046E6EA::rva0046B05B(Rva0046E6EAObject *objectView, const Rva0046E6EACoord *positionView, Rva0046E6EACoord *otherView)
{
	Object *obj = (Object *)objectView;
	Coord3D *pos = (Coord3D *)positionView;
	Object *other = (Object *)otherView;

	float dist;
	bool far;
	float r;
	Coord3D start;
	Coord3D target;
	{
		Coord3D dir;
		dir.x = pos->x;
		dir.y = pos->y;
		dir.z = pos->z;
		dir.x -= obj->m_position.x;
		dir.y -= obj->m_position.y;
		dir.z -= obj->m_position.z;
		dir.z = 0.0f;
		dist = dir.length();
		dir.normalize();
		far = dist > 2.0f * m_object->m_geometry.m_10;

		r = dist < other->m_258->rva002627E8() ? dist : other->m_258->rva002627E8();
		r *= 0.7f;
		r = r < 7.0f ? r : 7.0f;

		float d;
		{
			Coord3D toward;
			obj->getPlanarDirectionTo(&toward, m_object);
			d = toward.GetLengthEstimate();
		}
		if (d > 200.0f)
			d = 200.0f;
		else if (d <= 1.0f)
			d = 1.0f;
		float t = (200.0f - d) / 200.0f;
		r *= t * 0.8f + 0.2f;
		if (r > 10.0f)
			r = 10.0f;
		if (obj->m_template->m_11C & 0x10)
			r *= 0.8f;
		if (far)
			r = r > 9.0f ? r : 9.0f;

		start.x = obj->m_position.x;
		start.y = obj->m_position.y;
		start.z = obj->m_position.z;
		target.x = start.x;
		target.y = start.y;
		target.z = start.z;
		dir.x *= r;
		dir.y *= r;
		dir.z *= r;
		target.x += dir.x;
		target.y += dir.y;
		target.z += dir.z;
	}

	Object *o = Rva0046B05BFindAt(TheTerrainLogic->getLayerForDestination(obj, &target), &target);
	if (o == 0)
	{
		if (!obj->isKindOf(KINDOF_67) && !obj->isKindOf(KINDOF_69) && !obj->isSignificantlyAboveTerrain())
		{
			Coord3D mid;
			mid.z = target.z;
			mid.x = (start.x + target.x) * 0.5f;
			mid.y = (start.y + target.y) * 0.5f;
			o = Rva0046B05BFindAt(TheTerrainLogic->getLayerForDestination(obj, &mid), &mid);
			if (o)
				target = mid;
		}
	}

	bool raised = false;
	bool lowered = false;
	if (o && (o->m_template->m_121 & 2) && !(o->m_438 & 1))
	{
		if (o->m_74 != m_2F0)
		{
			Object *owner = TheGameLogic->findObjectByID(m_2F0);
			if (owner)
				o = owner;
		}
		Coord3D local;
		local.x = target.x;
		local.y = target.y;
		local.z = target.z;
		Matrix3D inverse;
		o->m_transform.Get_Orthogonal_Inverse(inverse);
		Rva0046B05BTransform(inverse, &local);
		GeometryInfo *geom = &o->m_geometry;
		bool inside = fabs(local.x) <= geom->m_majorRadius && geom->getMaxHeightAbovePosition() >= local.z;
		if (!inside && !obj->isKindOf(KINDOF_67) && !obj->isKindOf(KINDOF_69) && !obj->isSignificantlyAboveTerrain())
		{
			local.x = (start.x + target.x) * 0.5f;
			local.y = (start.y + target.y) * 0.5f;
			local.z = target.z;
			Rva0046B05BTransform(inverse, &local);
			inside = fabs(local.x) <= geom->m_majorRadius && geom->getMaxHeightAbovePosition() >= local.z;
		}
		if (inside)
		{
			float top = geom->getMaxHeightAbovePosition();
			float baseZ = o->m_position.z;
			float topZ = baseZ + top;
			if (start.z < topZ)
			{
				Rva0046B05BTransform(inverse, &start);
				if (start.x > geom->m_majorRadius)
					start.x = geom->m_majorRadius;
				else if (-geom->m_majorRadius > start.x)
					start.x = -geom->m_majorRadius;
				Rva0046B05BTransform(o->m_transform, &start);
				float half = obj->m_geometry.getMaxHeightAbovePosition() * 0.5f;
				if (baseZ + half > start.z)
					start.z = baseZ + half;
				else if (far)
					start.z += r * 0.8f;
				else
					start.z += r * 0.6f;
				if (start.z > topZ)
					start.z = topZ;
				raised = true;
			}
		}
	}
	else
	{
		float ground = TheTerrainLogic->getGroundHeight(start.x, start.y, 0);
		if (start.z > ground)
		{
			if (far)
				start.z -= r * 0.8f;
			else
				start.z -= r * 0.6f;
			if (start.z < ground)
				start.z = ground;
			lowered = true;
		}
		else if (o && (o->m_template->m_11A & 0x1040) && o->m_74 != m_2F0)
		{
			Object *owner = TheGameLogic->findObjectByID(m_2F0);
			if (owner)
			{
				Coord3D a;
				a.x = (owner->m_position.x - obj->m_position.x) + (obj->m_position.x - o->m_position.x) * 2.0f;
				a.y = (owner->m_position.y - obj->m_position.y) + (obj->m_position.y - o->m_position.y) * 2.0f;
				a.z = (owner->m_position.z - obj->m_position.z) + (obj->m_position.z - o->m_position.z) * 2.0f;
				a.normalize();
				Coord3D c;
				c.x = obj->m_position.x + a.x * r;
				c.y = obj->m_position.y + a.y * r;
				c.z = obj->m_position.z + a.z * r;
				target = c;
			}
		}
	}
	if (!lowered && !raised)
		start = target;
	*pos = start;
	reinterpret_cast<HordeContain *>(this)->rva00468B24(dist);
}
