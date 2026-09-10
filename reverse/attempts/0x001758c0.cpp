// ?update_cached_box@OBBoxRenderObjClass@@MAEXXZ
// partial score=0.98 date=2026-09-10
// cl: /O2 /arch:SSE2 /MD
//
// OBBoxRenderObjClass::update_cached_box, retail 0x001758C0, 251 bytes.
// Dedicated TU so boxrobj.cpp keeps x87 bodies. Inlined Transform_Vector
// (alias check plus SSE) then Extent copy then Matrix3::Set(Transform).

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Matrix3D
{
public:
	float Row[3][4];
};

class Matrix3
{
public:
	void Set(const Matrix3D &m);
	float Row[3][3];
};

static void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	const Vector3 *v;
	if (out == &in) {
		tmp.X = in.X;
		tmp.Y = in.Y;
		tmp.Z = in.Z;
		v = &tmp;
	} else {
		v = &in;
	}
	out->X = A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + v->X * A.Row[0][0] + A.Row[0][3];
	out->Y = A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3];
	out->Z = A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3];
}

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	int Gap0;
	int Gap1;
	Matrix3D Transform;
	unsigned char Pad[0x7C];
};

class BoxRenderObjClass : public RenderObjClass
{
public:
	char Name[32];
	Vector3 Color;
	Vector3 ObjSpaceCenter;
	Vector3 ObjSpaceExtent;
	float Opacity;
};

class OBBoxClass
{
public:
	Matrix3 Basis;
	Vector3 Center;
	Vector3 Extent;
};

class OBBoxRenderObjClass : public BoxRenderObjClass
{
protected:
	virtual void update_cached_box();
	OBBoxClass CachedBox;
	friend void force_emit_update_cached_box(OBBoxRenderObjClass &box);
};

void force_emit_update_cached_box(OBBoxRenderObjClass &box)
{
	box.update_cached_box();
}

void OBBoxRenderObjClass::update_cached_box()
{
	Transform_Vector(Transform, ObjSpaceCenter, &CachedBox.Center);
	CachedBox.Extent.X = ObjSpaceExtent.X;
	CachedBox.Extent.Y = ObjSpaceExtent.Y;
	CachedBox.Extent.Z = ObjSpaceExtent.Z;
	CachedBox.Basis.Set(Transform);
}
