// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
#include "Coord2D.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DClass.h"

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
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
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
// it with the +0x14 owner through 0x00118660. Matrix3D is WWMath's
// matrix3d.h (through CameraClass.h); Rotate_X and Translate_Z are its
// WWINLINE members. The display size is
// one Vector2 built from getWidth() and getHeight(): its arguments run right
// to left, which is retail's getHeight-first call order and float homes.
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "../../../../GameEngine/Include/GameClient/Display.h"
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
	Vector3 black(0.0f, 0.0f, 0.0f);
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
