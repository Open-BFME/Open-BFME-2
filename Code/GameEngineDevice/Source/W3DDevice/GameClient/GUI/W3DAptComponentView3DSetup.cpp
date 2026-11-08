// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva007402C0@W3DAptComponentView3D@@UAEXXZ, retail 0x007402C0, 661 bytes.
// Slot 1 of the W3DAptComponentView3D vtable 0x008F1600 (slot 0 is the
// deleting dtor 0x0074058D, slot 3 AddRenderObj 0x00740BCD, slot 4 SetLight
// 0x00740169); WB twin 0x017EDA60 (unnamed). Target facts: allocates the
// 0x108-byte SimpleSceneClass-derived scene (rowed base ctor 0x00142960, then
// vtable 0x008F1578 of Rva00740555, whose own ctor 0x00740157 is rowed) into
// +0x0C and gives it a 0.5 grey ambient light through scene slot 6; allocates
// the 0x3FC-byte CameraClass (0x00134AB0) into +0x10 with clip planes 1..5000
// (0x00133D00) and view plane 0.8726646 rad (50 degrees) by -1 (0x00133AD0);
// builds an identity Matrix3D, rotates it by -pi about Y and +pi about Z and
// hands it to camera slot 21 (+0x54). The rotations are Zero Hour's
// WWMath matrix3d.h Rotate_Y / Rotate_Z inlines (donor shape: sin before cos
// for Y, cos before sin for Z, both read off retail's call order). The
// method's original name is unknown, hence the address-derived name; class
// views below carry only the slots and sizes this body uses.
#include <math.h>

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
static __forceinline void copyVector4(Vector4 &row,const Vector4 &other){row.X=other.X;row.Y=other.Y;row.Z=other.Z;row.W=other.W;}

#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
// WWMath matrix3d.h's inline Rotate_Y and Rotate_Z, which the canonical header leaves to units.
static __forceinline void matrixRotateY(Matrix3D &m, float theta)
{
	float tmp1,tmp2;
	float s,c;

	s = sinf(theta);
	c = cosf(theta);

	tmp1 = m.Row[0].X; tmp2 = m.Row[0].Z;
	m.Row[0].X = (float)(c*tmp1 - s*tmp2);
	m.Row[0].Z = (float)(s*tmp1 + c*tmp2);

	tmp1 = m.Row[1].X; tmp2 = m.Row[1].Z;
	m.Row[1].X = (float)(c*tmp1 - s*tmp2);
	m.Row[1].Z = (float)(s*tmp1 + c*tmp2);

	tmp1 = m.Row[2].X; tmp2 = m.Row[2].Z;
	m.Row[2].X = (float)(c*tmp1 - s*tmp2);
	m.Row[2].Z = (float)(s*tmp1 + c*tmp2);
}
static __forceinline void matrixRotateZ(Matrix3D &m, float theta)
{
	float tmp1,tmp2;
	float c,s;

	c = cosf(theta);
	s = sinf(theta);

	tmp1 = m.Row[0].X; tmp2 = m.Row[0].Y;
	m.Row[0].X = (float)( c*tmp1 + s*tmp2);
	m.Row[0].Y = (float)(-s*tmp1 + c*tmp2);

	tmp1 = m.Row[1].X; tmp2 = m.Row[1].Y;
	m.Row[1].X = (float)( c*tmp1 + s*tmp2);
	m.Row[1].Y = (float)(-s*tmp1 + c*tmp2);

	tmp1 = m.Row[2].X; tmp2 = m.Row[2].Y;
	m.Row[2].X = (float)( c*tmp1 + s*tmp2);
	m.Row[2].Y = (float)(-s*tmp1 + c*tmp2);
}

#define SLOT(n) virtual void slot##n();
// Leading slots of retail vtable 0x008F1578 (27 slots): 0 Delete_This (0x6CE57),
// 1 deleting dtor 0x1042CF, 2-5 the rowed SimpleSceneClass Add_Render_Object /
// Remove_Render_Object / Create_Iterator / Destroy_Iterator, 6 SceneClass::
// Set_Ambient_Light (0x6E265). Shared by every unit that emits ??_7Rva00740555.
class Vector3;
class RenderObjClass;
class SceneIterator;
#include "../../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/SimpleSceneClass.h"

class Rva00740555 : public SimpleSceneClass
{
public:
	Rva00740555() {}
	virtual ~Rva00740555();
};

class CameraClass
{
public:
	CameraClass();
	virtual ~CameraClass();
	SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
	SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
	virtual void Set_Transform( const Matrix3D &m ); // slot 21 (+0x54)
	void Set_Clip_Planes( float znear, float zfar );
	void Set_View_Plane( float hfov, float vfov );
private:
	char m_pad04[0x3FC - 4];
};

class Rva007401F6
{
public:
	virtual ~Rva007401F6();
private:
	char m_pad04[8];
};

class W3DAptComponentView3D : public Rva007401F6
{
public:
	virtual ~W3DAptComponentView3D();
	virtual void rva007402C0();
private:
	SimpleSceneClass *m_scene; // +0x0C
	CameraClass *m_camera; // +0x10
};

void W3DAptComponentView3D::rva007402C0()
{
	m_scene = new Rva00740555;
	m_scene->Set_Ambient_Light(Vector3(0.5f, 0.5f, 0.5f));
	m_camera = new CameraClass;
	m_camera->Set_Clip_Planes(1.0f, 5000.0f);
	m_camera->Set_View_Plane(0.87266463f, -1.0f);
	Matrix3D transform(true);
	matrixRotateY(transform, -3.1415927f);
	matrixRotateZ(transform, 3.1415927f);
	m_camera->Set_Transform(transform);
}
