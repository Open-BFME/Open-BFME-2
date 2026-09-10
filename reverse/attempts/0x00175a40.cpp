// ??0BoxRenderObjClass@@QAE@ABUW3dBoxStruct@@@Z
// partial score=0.95 date=2026-09-10
// cl: /O2 /arch:SSE2 /EHsc /MD
//
// BoxRenderObjClass(const W3dBoxStruct &), retail 0x00175A40, 266 bytes.
// Dedicated TU so boxrobj.cpp keeps its matched bodies.

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
	RenderObjClass();
	virtual void Set_Collision_Type(int type, bool recurse);

private:
	unsigned char Pad[0xB4];
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct W3dBoxStruct
{
	unsigned Unknown0;
	unsigned Attributes;
	char Name[32];
	unsigned char ColorR;
	unsigned char ColorG;
	unsigned char ColorB;
	unsigned char ColorPad;
	float CenterX;
	float CenterY;
	float CenterZ;
	float ExtentX;
	float ExtentY;
	float ExtentZ;
};

class BoxRenderObjClass : public RenderObjClass
{
public:
	BoxRenderObjClass(const W3dBoxStruct &def);

private:
	char Name[32];
	Vector3 Color;
	Vector3 ObjSpaceCenter;
	Vector3 ObjSpaceExtent;
	float Opacity;
};

BoxRenderObjClass::BoxRenderObjClass(const W3dBoxStruct &def)
{
	char *dst = Name;
	const char *src = def.Name;
	for (;;) {
		char c = *src++;
		*dst++ = c;
		if (c == 0)
			break;
	}

	const float scale = 1.0f / 255.0f;
	Color.X = (float)def.ColorR * scale;
	Color.Y = (float)def.ColorG * scale;
	Color.Z = (float)def.ColorB * scale;
	ObjSpaceCenter.X = def.CenterX;
	ObjSpaceCenter.Y = def.CenterY;
	ObjSpaceCenter.Z = def.CenterZ;
	ObjSpaceExtent.X = def.ExtentX;
	ObjSpaceExtent.Y = def.ExtentY;
	ObjSpaceExtent.Z = def.ExtentZ;
	int col_bits = (def.Attributes >> 4) & 0xFF;
	RenderObjClass::Set_Collision_Type(col_bits << 1, false);
	Opacity = 0.25f;
}
