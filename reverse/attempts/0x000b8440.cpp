// ?rva000B8440@Rva000B8F5AOuter@@QAEHHPAM@Z
// partial score=0.95 date=2026-10-09
// ?rva000B8440@Rva000B8F5AOuter@@QAEHHPAM@Z
// partial score=0.88 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// NEAR draft (not exact): ?rva000B8440@Rva000B8F5AOuter@@QAEHHPAM@Z
// retail 0x000B89E9..0x000B8F5A (1393 bytes) thiscall RET 8; compiled body is
// 1393 bytes with 42 differing instructions (score ~0.88).
// Identity (WorldBuilder 0x009400F0): W3DScriptedModelDraw::
// getLogicSafeObjectTransformedPolygon (W3DScriptedModelDraw.cpp line 7851
// assert "Invalid range."). Takes a ref-counted render object (released on
// every exit) and a float out; sets the draw's render object transform from
// the drawable's object; for a mesh (Class_ID 0) with < 100 verts and polys
// welds equal vertices then collects edges used by exactly one polygon
// (static helper 0x000B36CE with its private EAX/ECX/EDX/EDI ABI: it must sit
// in this TU; its row moves here and it still matches exactly in this file),
// chains them into a perimeter, and builds a PolygonTrigger (new 0x64; ctor
// 0x002E3EB8 with the virtual-base flag) fed through the vcall-shaped stubs
// 0x005CB260 (add point) and 0x005CB274 (elevation) for every perimeter
// vertex transformed by the mesh transform; *outZ gets the last z.
// Remaining differences: numPolys/polys spill slots swapped ([ebp+8] vs
// [ebp-0x20]) with the matching helper-argument load order; and in the
// final loop the inline Matrix3D::Transform_Vector out/tmp slots are swapped
// (retail out -0xA4 tmp -0x98) with a different mulss operand order.

#include "Coord2D.h"

typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

struct Rva000B36CEPackedEntry
{
	UnsignedShort vertex[3];
};

static __declspec(noinline) int Rva000B36CECountSharedEdges(
	int entryCount, const Rva000B36CEPackedEntry *entries,
	const int *vertexRemap, int firstVertex, int secondVertex)
{
	int sharedCount = 0;
	for (int i = 0; i < entryCount; ++i)
	{
		bool hasFirst =
			firstVertex == vertexRemap[entries[i].vertex[0]] ||
			firstVertex == vertexRemap[entries[i].vertex[1]] ||
			firstVertex == vertexRemap[entries[i].vertex[2]];
		bool hasSecond =
			secondVertex == vertexRemap[entries[i].vertex[0]] ||
			secondVertex == vertexRemap[entries[i].vertex[1]] ||
			secondVertex == vertexRemap[entries[i].vertex[2]];
		if (hasFirst && hasSecond)
			++sharedCount;
	}
	return sharedCount;
}

struct Vector3
{
	Real X, Y, Z;
	Vector3() {}
	Vector3(Real x,Real y,Real z) : X(x),Y(y),Z(z) {}
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

__forceinline bool operator==(const Vector3 &a, const Vector3 &b)
{
	return (a.X == b.X) && (a.Y == b.Y) && (a.Z == b.Z);
}

class Vector4
{
public:
	Real X, Y, Z, W;
	__forceinline Vector4() {}
	__forceinline void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	__forceinline Matrix3D(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }
	__forceinline Matrix3D &operator=(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; return *this; }
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = &in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
	__forceinline Vector3 Get_Translation() const { return Vector3(Row[0].W,Row[1].W,Row[2].W); }
	__forceinline void Set_Translation(const Vector3 &v) { Row[0].W=v.X;Row[1].W=v.Y;Row[2].W=v.Z; }
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	Vector4 Row[3];
};

struct Rva000B89E9ShareBuffer
{
	char m_pad00[0x0C];
	void *m_array;			// +0x0C
};

class MeshModelClass
{
public:
	Int Get_Polygon_Count() const { return m_polyCount; }
	Int Get_Vertex_Count() const { return m_vertexCount; }
	const Rva000B36CEPackedEntry *Get_Polygon_Array() const { return (const Rva000B36CEPackedEntry *)m_polys->m_array; }
	const Vector3 *Get_Vertex_Array() const { return (const Vector3 *)m_vertices->m_array; }
private:
	char m_pad00[0x24];
	Int m_polyCount;			// +0x24
	Int m_vertexCount;			// +0x28
	Rva000B89E9ShareBuffer *m_polys;	// +0x2C
	Rva000B89E9ShareBuffer *m_vertices;	// +0x30
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void v1();
	virtual void v2();
	virtual Int Class_ID() const;
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &m);
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return m_transform;
	}
	MeshModelClass *Peek_Model() const { return m_model; }
private:
	Int m_numRefs;				// +0x04
	char m_pad08[0x18 - 0x08];
	Matrix3D m_transform;			// +0x18
	char m_pad48[0xC4 - 0x48];
	MeshModelClass *m_model;		// +0xC4
};

class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	char m_pad00[0x08];
	Matrix3D m_transform;			// +0x08
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
	const Matrix3D *getTransformMatrix() const;
private:
	char m_pad000[0xFC];
	Object *m_object;			// +0xFC
};


class Rva005CB260
{
public:
	void rva005CB260(Int);
};

struct Rva000B89E9Elevation
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
	virtual void setBoundaryElevation(Int z);
};
typedef void (Rva000B89E9Elevation::*Rva000B89E9ElevationFn)(Int);

class Rva000B89E9VirtualBase
{
public:
	virtual ~Rva000B89E9VirtualBase();
};

class PolygonTrigger : public virtual Rva000B89E9VirtualBase
{
public:
	PolygonTrigger(Int initialAllocation);
private:
	char m_body[0x64 - 8];
};

struct Rva000B8440ModuleData { char pad[0x69]; bool ignoreRotation; };
class W3DScriptedModelDraw { public: void rva000B710D(Matrix3D &); };
struct Rva000B8F5AOuter
{
	Int rva000B8440(Int robjArg, Real *outZ);
private:
	char m_pad00[4];
	Rva000B8440ModuleData *moduleData;
	Drawable *m_drawable;			// +0x08
	char m_pad0C[0x50 - 0x0C];
	RenderObjClass *m_renderObject;		// +0x50
};

#define MAX_POLYGON_VERTICES 100

Int Rva000B8F5AOuter::rva000B8440(Int robjArg, Real *outZ)
{
	RenderObjClass *robj = (RenderObjClass *)robjArg;
	Int numEdges = 0;
	Int edges[2][MAX_POLYGON_VERTICES];
	edges[0][0] = 0;
	edges[1][0] = 0;

	Object *obj = m_drawable->getObject();
	if (obj == 0)
	{
		if (robj)
			robj->Release_Ref();
		return 0;
	}

	Matrix3D tm(true);
	if(moduleData->ignoreRotation) {
 tm.Set_Translation(m_drawable->getTransformMatrix()->Get_Translation());
 } else tm = *obj->getTransformMatrix();
 ((W3DScriptedModelDraw *)this)->rva000B710D(tm);
	m_renderObject->Set_Transform(tm);

	if (robj && robj->Class_ID() == 0)
	{
		Matrix3D objTm(robj->Get_Transform());
		MeshModelClass *model = robj->Peek_Model();
		Int numVertices = model->Get_Vertex_Count();
		const Vector3 *vertices = model->Get_Vertex_Array();
		Int numPolys = model->Get_Polygon_Count();
		const Rva000B36CEPackedEntry *polys = model->Get_Polygon_Array();
		if (numVertices >= MAX_POLYGON_VERTICES || numPolys >= MAX_POLYGON_VERTICES)
		{
			robj->Release_Ref();
			return 0;
		}

		Int remap[MAX_POLYGON_VERTICES];
		Int i;
		for (i = 0; i < numVertices; ++i)
			remap[i] = i;
		for (i = 0; i < numVertices; ++i)
		{
			for (Int j = i + 1; j < numVertices; ++j)
			{
				if (vertices[i] == vertices[j])
					remap[j] = remap[i];
			}
		}

		for (i = 0; i < numPolys; ++i)
		{
			Int a = remap[polys[i].vertex[0]];
			Int b = remap[polys[i].vertex[1]];
			if (Rva000B36CECountSharedEdges(numPolys, polys, remap, a, b) == 1)
			{
				edges[0][numEdges] = a;
				edges[1][numEdges] = b;
				++numEdges;
			}
			a = remap[polys[i].vertex[1]];
			b = remap[polys[i].vertex[2]];
			if (Rva000B36CECountSharedEdges(numPolys, polys, remap, a, b) == 1)
			{
				edges[0][numEdges] = a;
				edges[1][numEdges] = b;
				++numEdges;
			}
			a = remap[polys[i].vertex[2]];
			b = remap[polys[i].vertex[0]];
			if (Rva000B36CECountSharedEdges(numPolys, polys, remap, a, b) == 1)
			{
				edges[0][numEdges] = a;
				edges[1][numEdges] = b;
				++numEdges;
			}
		}

		if (numEdges > 0)
		{
			Int *perimeter = remap;
			perimeter[0] = edges[0][0];
			perimeter[1] = edges[1][0];
			edges[0][0] = -1;
			edges[1][0] = -1;
			Int count = 2;
			Int cur = perimeter[1];
			while (count < MAX_POLYGON_VERTICES && cur != perimeter[0])
			{
				bool found = false;
				for (i = 0; i < numEdges; ++i)
				{
					if (edges[0][i] == cur)
					{
						cur = edges[1][i];
						edges[1][i] = -1;
						edges[0][i] = -1;
						if (cur != perimeter[0])
							perimeter[count++] = cur;
						found = true;
					}
					else if (edges[1][i] == cur)
					{
						cur = edges[0][i];
						edges[1][i] = -1;
						edges[0][i] = -1;
						if (cur != perimeter[0])
							perimeter[count++] = cur;
						found = true;
					}
					if (found)
						break;
				}
				if (!found)
					break;
			}

			if (count > 2)
			{
				PolygonTrigger *area = new PolygonTrigger(count + 1);
				for (i = 0; i < count; ++i)
				{
					Vector3 pos;
					Matrix3D::Transform_Vector(objTm, vertices[perimeter[i]], &pos);
					Coord2D pt;
					pt.x = pos.X;
					pt.y = pos.Y;
					((Rva005CB260 *)area)->rva005CB260((Int)&pt);
					Rva000B89E9ElevationFn setElevation = &Rva000B89E9Elevation::setBoundaryElevation;
					(((Rva000B89E9Elevation *)area)->*setElevation)((Int)pos.Z);
					*outZ = pos.Z;
				}
				robj->Release_Ref();
				return (Int)area;
			}
		}
	}

	if (robj)
		robj->Release_Ref();
	return 0;
}
