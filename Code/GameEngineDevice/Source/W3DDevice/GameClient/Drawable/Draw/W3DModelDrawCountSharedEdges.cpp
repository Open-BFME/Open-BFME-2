// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
//
// Two bodies of one retail unit (W3DScriptedModelDraw.cpp in BFME2) kept
// together because the static edge counter has a private register ABI that
// cl only reproduces when its caller is compiled in the same unit.
//   ?Rva000B36CECountSharedEdges@@YAHHHPBURva000B36CEPackedEntry@@HPBH@Z  0x000B36CE 111B
//   ?getPolygon@W3DScriptedModelDraw@@QAEPAVPolygonTrigger@@PAVRenderObjClass@@PAM@Z  0x000B8440 1449B
//
// Edge counter (BFME 1 donor 1399ad37d42ea52a63829e417c46a1ba9ed2cd20
// Drawable/Draw/Rva0075C690CountSharedEdges.cpp; original name unknown):
// counts packed triangles containing both remapped vertices. WorldBuilder's
// out-of-line copy (wb 0x93ffe0) is called with the pushes (first vertex
// second vertex polys count remap); that parameter order is what makes
// getPolygon spill the polygon count (not the array) into the dead robj
// argument slot as retail does and it keeps the helper's own 111 bytes
// (EAX=count ECX=polys EDX=remap EDI=first plus the pushed second vertex).
//
// getPolygon (WorldBuilder twin 0x93EAD0 W3DScriptedModelDraw::getPolygon
// with ASSERT W3DScriptedModelDraw.cpp:7700): builds the identity transform
// or the object transform (module data +0x69 keeps only the drawable
// translation) then adjustTransformMtx (0x000B710D) and the render object's
// Set_Transform. For a mesh render object (Class_ID 0) of under 100 vertices
// and polygons it welds coincident vertices then keeps the edges used by one
// triangle only and walks them into a perimeter loop. Over two perimeter
// points build a PolygonTrigger (0x64 bytes ctor 0x002E3EB8 with the virtual
// base flag) whose boundary gets each transformed point
// (PolygonalArea::addBoundaryPoint folded to 0x005CB260) and its integer
// elevation (PolygonalArea::setBoundaryElevation folded onto the slot +0x18
// vcall thunk 0x005CB274) while the float Z goes to *height. The robj
// argument reference is always released. Callers: getRamp 0x000B9EC2 and
// 0x000BAD2B. The point is built as a temporary from (X Y) like
// WorldBuilder's inline two-argument constructor; the elevation call goes
// through the slot +0x18 member pointer (retail target ??_9@$BBI@AE).
#include "matrix3d.h"

typedef unsigned short UnsignedShort;

struct Rva000B36CEPackedEntry
{
	UnsignedShort vertex[3];
};

static __declspec(noinline) int Rva000B36CECountSharedEdges(
	int firstVertex, int secondVertex, const Rva000B36CEPackedEntry *entries,
	int entryCount, const int *vertexRemap)
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

#define SLOT(n) virtual void slot##n();

template <class T>
struct ShareBufferView
{
	char m_pad00[0x0C];
	T *m_array;
};

class MeshModelClass
{
public:
	int Get_Polygon_Count() const { return m_polyCount; }
	int Get_Vertex_Count() const { return m_vertexCount; }
	const Rva000B36CEPackedEntry *Get_Polygon_Array() const { return m_polys->m_array; }
	const Vector3 *Get_Vertex_Array() const { return m_vertices->m_array; }
	char m_pad00[0x24];
	int m_polyCount;
	int m_vertexCount;
	ShareBufferView<Rva000B36CEPackedEntry> *m_polys;
	ShareBufferView<Vector3> *m_vertices;
};

class RenderObjClass
{
public:
	enum { CLASSID_MESH = 0 };
	virtual void Delete_This();
	SLOT(01) SLOT(02)
	virtual int Class_ID() const;
	SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &m);
	void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }
	const Matrix3D &Get_Transform() const { Validate_Transform(); return m_transform; }
	int m_numRefs;
	char m_pad08[0x18 - 0x08];
	Matrix3D m_transform;
};

class MeshClass : public RenderObjClass
{
public:
	MeshModelClass *Peek_Model() const { return m_model; }
	char m_pad48[0xC4 - 0x48];
	MeshModelClass *m_model;
};

struct BfmeE8
{
	BfmeE8(float ax, float ay) { x = ax; y = ay; }
	float x;
	float y;
};

class PolygonalArea
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05)
	virtual void setBoundaryElevationSlot(int z);
	void rva005CB260(const BfmeE8 &point);
};

class PolygonTriggerBase
{
public:
	virtual void slot();
};

class PolygonTrigger : public PolygonalArea, public virtual PolygonTriggerBase
{
public:
	PolygonTrigger(int initialAllocation);
	char m_pad[0x64 - 12];
};

class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	char m_pad00[0x08];
	Matrix3D m_transform;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	Object *getObject() const { return m_object; }
	char m_pad00[0xFC];
	Object *m_object;
};

struct W3DScriptedModelDrawModuleData
{
	char m_pad00[0x69];
	bool m_attachAtDrawablePosition;
};

class W3DScriptedModelDraw
{
public:
	virtual void slot00();
	void rva000B710D(Matrix3D &mtx);
	PolygonTrigger *getPolygon(RenderObjClass *robj, float *height);

	const W3DScriptedModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	char m_pad0C[0x50 - 0x0C];
	RenderObjClass *m_renderObject;
};

PolygonTrigger *W3DScriptedModelDraw::getPolygon(RenderObjClass *robj, float *height)
{
	const int MAX_POLY_VERTS = 100;
	int numEdges = 0;
	int edgeStart[MAX_POLY_VERTS];
	int edgeEnd[MAX_POLY_VERTS];
	edgeStart[0] = 0;
	edgeEnd[0] = 0;

	Object *obj = m_drawable->getObject();
	if (!obj)
	{
		if (robj)
			robj->Release_Ref();
		return 0;
	}

	Matrix3D mtx(true);
	if (m_moduleData->m_attachAtDrawablePosition)
		mtx.Set_Translation(m_drawable->getTransformMatrix()->Get_Translation());
	else
		mtx = *obj->getTransformMatrix();
	rva000B710D(mtx);
	m_renderObject->Set_Transform(mtx);

	if (robj && robj->Class_ID() == RenderObjClass::CLASSID_MESH)
	{
		Matrix3D tm = robj->Get_Transform();
		MeshModelClass *model = ((MeshClass *)robj)->Peek_Model();
		int numVerts = model->Get_Vertex_Count();
		const Vector3 *verts = model->Get_Vertex_Array();
		int numPolys = model->Get_Polygon_Count();
		const Rva000B36CEPackedEntry *polys = model->Get_Polygon_Array();
		if (numVerts < MAX_POLY_VERTS && numPolys < MAX_POLY_VERTS)
		{
			int remap[MAX_POLY_VERTS];
			int i;
			for (i = 0; i < numVerts; i++)
				remap[i] = i;
			for (i = 0; i < numVerts; i++)
			{
				for (int j = i + 1; j < numVerts; j++)
				{
					if (verts[i] == verts[j])
						remap[j] = remap[i];
				}
			}
			for (i = 0; i < numPolys; i++)
			{
				int a = remap[polys[i].vertex[0]];
				int b = remap[polys[i].vertex[1]];
				if (Rva000B36CECountSharedEdges(a, b, polys, numPolys, remap) == 1)
				{
					edgeStart[numEdges] = a;
					edgeEnd[numEdges] = b;
					numEdges++;
				}
				a = remap[polys[i].vertex[1]];
				b = remap[polys[i].vertex[2]];
				if (Rva000B36CECountSharedEdges(a, b, polys, numPolys, remap) == 1)
				{
					edgeStart[numEdges] = a;
					edgeEnd[numEdges] = b;
					numEdges++;
				}
				a = remap[polys[i].vertex[2]];
				b = remap[polys[i].vertex[0]];
				if (Rva000B36CECountSharedEdges(a, b, polys, numPolys, remap) == 1)
				{
					edgeStart[numEdges] = a;
					edgeEnd[numEdges] = b;
					numEdges++;
				}
			}
			if (numEdges > 0)
			{
				remap[0] = edgeStart[0];
				edgeStart[0] = -1;
				remap[1] = edgeEnd[0];
				edgeEnd[0] = -1;
				int cur = remap[1];
				int count = 2;
				while (count < MAX_POLY_VERTS && cur != remap[0])
				{
					bool found = false;
					for (i = 0; i < numEdges; i++)
					{
						if (edgeStart[i] == cur)
						{
							cur = edgeEnd[i];
							edgeEnd[i] = -1;
							edgeStart[i] = -1;
							if (cur != remap[0])
								remap[count++] = cur;
							found = true;
						}
						else if (edgeEnd[i] == cur)
						{
							cur = edgeStart[i];
							edgeEnd[i] = -1;
							edgeStart[i] = -1;
							if (cur != remap[0])
								remap[count++] = cur;
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
					PolygonTrigger *poly = new PolygonTrigger(count + 1);
					for (i = 0; i < count; i++)
					{
						Vector3 pt;
						Matrix3D::Transform_Vector(tm, verts[remap[i]], &pt);
						poly->rva005CB260(BfmeE8(pt.X, pt.Y));
						void (PolygonalArea::*setElevation)(int) = &PolygonalArea::setBoundaryElevationSlot;
						(poly->*setElevation)((int)pt.Z);
						*height = pt.Z;
					}
					robj->Release_Ref();
					return poly;
				}
			}
		}
	}
	if (robj)
		robj->Release_Ref();
	return 0;
}
