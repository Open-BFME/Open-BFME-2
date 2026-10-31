// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord2D.h"

#include "../../../../../reference/shims/wwmath/Vector2.h"

class Render2DClass
{
public:
	void Add_Tri(const Vector2 &, const Vector2 &, const Vector2 &,
		const Vector2 &, const Vector2 &, const Vector2 &, unsigned long);
};

// Native 0x001049C7..0x00104A75 ends in RET: one renderer pointer and
// six pointers to two-float coordinates, copied to six Vector2 temporaries.
// The call target 0x00045708 independently allocates three vertices and
// indices via the established 0x0011BD80 renderer helper, transforms the
// first three vectors, assigns the next three UVs and uses the final color.
// This agrees with the BFME 1 Render2DClassAddTri.cpp at revision
// 968ca36c3265b295297e6aed45a6bd89ffe59c40 and ZH Add_Tri declaration.
// Callee identity and Vector2 ABI are reference-supported; the wrapper's
// original name and the input coordinate type are unknown measured views.
void Rva001049C7AddTriangle(Render2DClass *renderer,
	const Coord2D *vertex0, const Coord2D *vertex1, const Coord2D *vertex2,
	const Coord2D *texCoord0, const Coord2D *texCoord1, const Coord2D *texCoord2)
{
	renderer->Add_Tri(Vector2(vertex0->x, vertex0->y),
		Vector2(vertex1->x, vertex1->y), Vector2(vertex2->x, vertex2->y),
		Vector2(texCoord0->x, texCoord0->y), Vector2(texCoord1->x, texCoord1->y),
		Vector2(texCoord2->x, texCoord2->y), 0xFFFFFFFFUL);
}

// Native 104956..1049C7, ret4 at1049C4. Vslot23 of7CF6F0 installed by
// rowed ctor1040D5; intrusive list+60/+64, node payload+0C points8 beyond
// render receiver. Each receiver gets the opaque input word via slot12.
// The same word is passed to final cdecl flush1173F0; its unused parameter
// is corroborated by BFME1 WW3D::Flush(RenderInfoClass&), while the original
// wrapper and receiver names/types remain unknown target views.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
void __cdecl rva001173f0(unsigned int);

class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();
};

class Slot12Target
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void slot12(unsigned int arg);
};

struct ListNode
{
	void *m_prev;
	ListNode *m_next;
	void *m_unk08;
	void *m_ptrPlus8;
};

// Native 10473F..104956, ret 10. Points the camera at +0x18 straight down
// (Rotate_X by -pi/2, then back along Z by the .data float 160.0 that only
// this function reads), sets its viewport to the x/y/width/height pixel
// rectangle over TheDisplay's size and a 50-degree view plane, then renders
// it with the +0x14 owner through 0x00118660. The Matrix3D and Vector4
// members are the WWMath donor's, forced inline as WWINLINE spells them (a
// plain inline Matrix3D is called out of line at /O1); the bool constructor
// and Translate_Z are dllimport so this unit emits no copy of either to
// compete with retail's (0x0004C91A for the constructor). The display size is
// one Vector2 built from getWidth() and getHeight(): its arguments run right
// to left, which is retail's getHeight-first call order and float homes.
class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	WWINLINE float &operator[](int i) { return (&X)[i]; }
	WWINLINE void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};

class Matrix3D
{
public:
	__declspec(dllimport) __forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	WWINLINE void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	WWINLINE void Rotate_X(float theta)
	{
		float tmp1, tmp2;
		float sinTheta, c;

		sinTheta = sinf(theta);
		c = cosf(theta);

		tmp1 = Row[0][1]; tmp2 = Row[0][2];
		Row[0][1] = (float)( c*tmp1 + sinTheta*tmp2);
		Row[0][2] = (float)(-sinTheta*tmp1 + c*tmp2);

		tmp1 = Row[1][1]; tmp2 = Row[1][2];
		Row[1][1] = (float)( c*tmp1 + sinTheta*tmp2);
		Row[1][2] = (float)(-sinTheta*tmp1 + c*tmp2);

		tmp1 = Row[2][1]; tmp2 = Row[2][2];
		Row[2][1] = (float)( c*tmp1 + sinTheta*tmp2);
		Row[2][2] = (float)(-sinTheta*tmp1 + c*tmp2);
	}
	__declspec(dllimport) __forceinline void Translate_Z(float z)
	{
		Row[0][3] += (float)(Row[0][2]*z);
		Row[1][3] += (float)(Row[1][2]*z);
		Row[2][3] += (float)(Row[2][2]*z);
	}

	Vector4 Row[3];
};

class CameraClass
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void Set_Transform(const Matrix3D &m); // slot 21
	void Set_Viewport(const Vector2 &min, const Vector2 &max);
	void Set_View_Plane(float hfov, float vfov);
};

class Display
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual unsigned int getWidth(); // slot 16
	virtual unsigned int getHeight(); // slot 17
};
extern Display *TheDisplay;
static float s_cameraDistance = 160.0f;
bool Rva00118660Call(void *owner, void *camera);

class Rva001040D5 : public Rva00142960Base
{
public:
	void rva0010473F(int viewportX, int viewportY, int width, int height);
	virtual void rva00104956(unsigned int arg);
private:
	char m_pad04[0x14 - 0x04];
	void *m_owner;
	CameraClass *m_camera;
	unsigned int m_active;
	char m_pad20[0x60 - 0x20];
	ListNode m_list;
};

void Rva001040D5::rva0010473F(int viewportX, int viewportY, int width, int height)
{
	if (m_active)
	{
		Matrix3D transform(true);
		transform.Rotate_X(-1.5707963705062866f);
		transform.Translate_Z(s_cameraDistance);
		m_camera->Set_Transform(transform);
		Vector2 scale((float)TheDisplay->getWidth(), (float)TheDisplay->getHeight());
		Vector2 inv(1.0f / scale.X, 1.0f / scale.Y);
		{
			Vector2 low((float)viewportX * inv.X, (float)viewportY * inv.Y);
			Vector2 high((float)width * inv.X + low.X, (float)height * inv.Y + low.Y);
			m_camera->Set_Viewport(low, high);
		}
		m_camera->Set_View_Plane(0.87266463f, -1.0f);
		Rva00118660Call(m_owner, m_camera);
	}
}

void Rva001040D5::rva00104956(unsigned int arg)
{
	DX8Wrapper::Apply_Render_State_Changes();
	Vector3 black = { 0.0f, 0.0f, 0.0f };
	DX8Wrapper::Clear(false, true, true, black, 0.0f, 1.0f, 0);
	ListNode *listNode = m_list.m_next;
	while (listNode != &m_list)
	{
		void *nodePayload = listNode->m_ptrPlus8;
		Slot12Target *slot12Target = nodePayload ? (Slot12Target *)((char *)nodePayload - 8) : 0;
		slot12Target->slot12(arg);
		listNode = listNode->m_next;
	}
	rva001173f0(arg);
}
