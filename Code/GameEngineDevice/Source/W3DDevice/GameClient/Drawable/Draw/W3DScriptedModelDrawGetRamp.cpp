// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
//
// ?getRamp@W3DScriptedModelDraw@@QAE_NPAVBridgeInfo@@VAsciiString@@PAPAVPolygonTrigger@@PAPAVRenderObjClass@@_N@Z
// retail 0x000B9EC2..0x000BAC53 (3473 bytes), thiscall ret 0x14, EH frame
// for the by-value AsciiString bone name.
//
// WorldBuilder twin 0x938E80 W3DScriptedModelDraw::getRamp (DEBUG "Ramp Mesh
// unsuitable to be a ramp." at W3DScriptedModelDraw.cpp:7345). The named
// sub-object of the draw's render object (vtable slot 49 = +0x50 getter
// 0x00225A98) is resolved with Get_Sub_Object_By_Name (render object slot
// 0x80) and its slot 0x14; the draw transform is built like getPolygon
// (identity or object transform then adjustTransformMtx 0x000B710D unless
// the caller asks for the plain object transform) and pushed with
// Set_Transform. For a mesh it optionally returns an extra reference and
// the getPolygon (0x000B8440) perimeter trigger (over two polygons). With a
// BridgeInfo it scans the mesh vertices: the Z range gives a 1/50 band at
// the bottom and the top; in each band the two mutually farthest vertices
// are found (two passes) and their midpoints transformed by the mesh
// transform become from/to; the band spans average into bridgeWidth. Over
// two polygons the four corners are the transformed band vertices rounded
// toward zero; otherwise they are from/to offset by half the width along
// the normalized XY perpendicular (Vector3::Normalize with
// WWMath::Inv_Sqrt 0x0004233A). BridgeInfo layout follows the matched
// TerrainLogic_getBridgeAttackPoints.cpp view (from to bridgeWidth
// fromLeft fromRight toLeft toRight).
//
// Schedule notes: the WWMath Matrix3D/Vector3 inlines come from the BFME1
// canonical headers. Retail's SSE reassociation of the four corner
// transforms only reproduces with the natural accessor inlines
// (getDrawable getW3DModelDrawModuleData ShareBuffer Get_Array) and with
// the band widths summed inline into the width.
#include "ascii_string.h"
#include "matrix3d.h"
#include "Coord3D.h"

#define SLOT(n) virtual void slot##n();
#define REF_PTR_RELEASE(x) { if (x) x->Release_Ref(); x = 0; }

template <class T>
struct ShareBufferView
{
	T *Get_Array() const { return m_array; }
	char m_pad00[0x0C];
	T *m_array;
};

class MeshModelClass
{
public:
	int Get_Polygon_Count() const { return m_polyCount; }
	int Get_Vertex_Count() const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array() const { return m_vertices->Get_Array(); }
	char m_pad00[0x24];
	int m_polyCount;
	int m_vertexCount;
	void *m_polys;
	ShareBufferView<Vector3> *m_vertices;
};

class RenderObjClass
{
public:
	enum { CLASSID_MESH = 0 };
	virtual void Delete_This();
	SLOT(01) SLOT(02)
	virtual int Class_ID() const;
	SLOT(04)
	virtual RenderObjClass *slot05();
	SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &m);
	SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	virtual RenderObjClass *Get_Sub_Object_By_Name(const char *name, int *index) const;
	void Add_Ref() { ++m_numRefs; }
	void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }
	const Matrix3D &Get_Transform() const { Validate_Transform(); return m_transform; }
	MeshModelClass *Peek_Model() const { return m_model; }
	int m_numRefs;
	char m_pad08[0x18 - 0x08];
	Matrix3D m_transform;
	char m_pad48[0xC4 - 0x48];
	MeshModelClass *m_model;
};

class PolygonTrigger;

class BridgeInfo
{
public:
	Coord3D from;
	Coord3D to;
	float bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
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
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48)
	virtual RenderObjClass *getRenderObject();
	void rva000B710D(Matrix3D &mtx);
	PolygonTrigger *getPolygon(RenderObjClass *robj, float *height);
	bool getRamp(BridgeInfo *info, AsciiString boneName, PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform);
	static void setCoord(Coord3D &c, float x, float y, float z) { c.x = x; c.y = y; c.z = z; }

	Drawable *getDrawable() const { return m_drawable; }
	const W3DScriptedModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	const W3DScriptedModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

bool W3DScriptedModelDraw::getRamp(BridgeInfo *info, AsciiString boneName, PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform)
{
	RenderObjClass *robj = getRenderObject();
	RenderObjClass *meshObj = 0;
	if (polygon)
		*polygon = 0;
	if (mesh)
		*mesh = 0;
	if (robj)
	{
		RenderObjClass *sub = robj->Get_Sub_Object_By_Name(boneName.str(), 0);
		if (sub)
		{
			meshObj = sub->slot05();
			if (!meshObj)
				sub->Release_Ref();
		}
	}
	Object *obj = getDrawable()->getObject();
	if (!obj)
	{
		REF_PTR_RELEASE(meshObj);
		return false;
	}
	Matrix3D mtx(true);
	if (getW3DModelDrawModuleData()->m_attachAtDrawablePosition && !useObjectTransform)
		mtx.Set_Translation(getDrawable()->getTransformMatrix()->Get_Translation());
	else
		mtx = *obj->getTransformMatrix();
	if (!useObjectTransform)
		rva000B710D(mtx);
	if (robj)
		robj->Set_Transform(mtx);
	if (meshObj && meshObj->Class_ID() == RenderObjClass::CLASSID_MESH)
	{
		if (mesh)
		{
			meshObj->Add_Ref();
			*mesh = meshObj;
		}
		if (polygon && meshObj->Peek_Model()->Get_Polygon_Count() > 2)
		{
			meshObj->Add_Ref();
			float height;
			*polygon = getPolygon(meshObj, &height);
		}
		if (info)
		{
			Matrix3D tm(meshObj->Get_Transform());
			int numVerts = meshObj->Peek_Model()->Get_Vertex_Count();
			Vector3 *verts = meshObj->Peek_Model()->Get_Vertex_Array();
			float maxZ = verts[0].Z;
			float minZ = maxZ;
			int i;
			for (i = 1; i < numVerts; i++)
			{
				if (minZ > verts[i].Z)
					minZ = verts[i].Z;
				if (maxZ < verts[i].Z)
					maxZ = verts[i].Z;
			}
			float tolerance = (maxZ - minZ) / 50.0f;
			Vector3 lowA(0, 0, 0);
			Vector3 lowB(0, 0, 0);
			Vector3 highA(0, 0, 0);
			Vector3 highB(0, 0, 0);
			bool foundLow = false;
			bool foundHigh = false;
			for (i = 0; i < numVerts; i++)
			{
				if (minZ + tolerance > verts[i].Z)
				{
					if (foundLow)
					{
						if ((lowA - lowB).Length2() < (lowA - verts[i]).Length2())
							lowB = verts[i];
					}
					else
					{
						lowB = verts[i];
						lowA = lowB;
						foundLow = true;
					}
				}
				else if (maxZ - tolerance < verts[i].Z)
				{
					if (foundHigh)
					{
						if ((highA - highB).Length2() < (highA - verts[i]).Length2())
							highB = verts[i];
					}
					else
					{
						highB = verts[i];
						highA = highB;
						foundHigh = true;
					}
				}
			}
			if (!foundLow || !foundHigh)
				return false;
			for (i = 0; i < numVerts; i++)
			{
				if (minZ + tolerance > verts[i].Z)
				{
					if ((lowA - lowB).Length2() < (lowB - verts[i]).Length2())
						lowA = verts[i];
				}
				else if (maxZ - tolerance < verts[i].Z)
				{
					if ((highA - highB).Length2() < (highA - verts[i]).Length2())
						highB = verts[i];
				}
			}
			Vector3 lowMid = (lowA + lowB) / 2.0f;
			Vector3 lowPt;
			Matrix3D::Transform_Vector(tm, lowMid, &lowPt);
			Vector3 highMid = (highA + highB) / 2.0f;
			Vector3 highPt;
			Matrix3D::Transform_Vector(tm, highMid, &highPt);
			float width = ((highA - highB).Length() + (lowA - lowB).Length()) / 2.0f;
			setCoord(info->from, highPt.X, highPt.Y, highPt.Z);
			setCoord(info->to, lowPt.X, lowPt.Y, lowPt.Z);
			info->bridgeWidth = width;
			if (meshObj->Peek_Model()->Get_Polygon_Count() > 2)
			{
				Matrix3D::Transform_Vector(tm, lowA, &lowPt);
				setCoord(info->toLeft, (int)lowPt.X, (int)lowPt.Y, (int)lowPt.Z);
				Matrix3D::Transform_Vector(tm, lowB, &lowPt);
				setCoord(info->toRight, (int)lowPt.X, (int)lowPt.Y, (int)lowPt.Z);
				Matrix3D::Transform_Vector(tm, highA, &lowPt);
				setCoord(info->fromLeft, (int)lowPt.X, (int)lowPt.Y, (int)lowPt.Z);
				Matrix3D::Transform_Vector(tm, highB, &lowPt);
				setCoord(info->fromRight, (int)lowPt.X, (int)lowPt.Y, (int)lowPt.Z);
			}
			else
			{
				Vector3 vec = lowPt - highPt;
				Vector3 normal(-vec.Y, vec.X, 0);
				normal.Normalize();
				info->fromLeft.x = highPt.X + normal.X * width * 0.5f;
				info->fromLeft.y = highPt.Y + normal.Y * width * 0.5f;
				info->fromLeft.z = highPt.Z + normal.Z * width * 0.5f;
				info->fromRight.x = highPt.X - normal.X * width * 0.5f;
				info->fromRight.y = highPt.Y - normal.Y * width * 0.5f;
				info->fromRight.z = highPt.Z - normal.Z * width * 0.5f;
				info->toLeft.x = lowPt.X + normal.X * width * 0.5f;
				info->toLeft.y = lowPt.Y + normal.Y * width * 0.5f;
				info->toLeft.z = lowPt.Z + normal.Z * width * 0.5f;
				info->toRight.x = lowPt.X - normal.X * width * 0.5f;
				info->toRight.y = lowPt.Y - normal.Y * width * 0.5f;
				info->toRight.z = lowPt.Z - normal.Z * width * 0.5f;
			}
		}
		REF_PTR_RELEASE(meshObj);
		return true;
	}
	REF_PTR_RELEASE(meshObj);
	return false;
}
