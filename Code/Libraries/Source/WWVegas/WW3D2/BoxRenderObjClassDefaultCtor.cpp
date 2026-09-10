// cl: /O2 /arch:SSE2 /MD
//
// BoxRenderObjClass default ctor, retail 0x00174C80, 155 bytes.
// Dedicated TU so boxrobj.cpp keeps its existing matched bodies.
// Two vptrs: RefCount at +0 and MultiListObject at +8; Name at +0xC4.

#include <string.h>

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

private:
	unsigned char Pad[0xB4];
};

class Vector3
{
public:
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	float X;
	float Y;
	float Z;
};

class BoxRenderObjClass : public RenderObjClass
{
public:
	BoxRenderObjClass();

private:
	char Name[32];
	Vector3 Color;
	Vector3 ObjSpaceCenter;
	Vector3 ObjSpaceExtent;
	float Opacity;
};

BoxRenderObjClass::BoxRenderObjClass()
{
	memset(Name, 0, sizeof(Name));
	Color.Set(1, 1, 1);
	Opacity = 0.25f;
	ObjSpaceCenter.Set(0, 0, 0);
	ObjSpaceExtent.Set(1, 1, 1);
}
