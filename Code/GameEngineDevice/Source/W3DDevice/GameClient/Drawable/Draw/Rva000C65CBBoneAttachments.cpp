// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?rva000C65CB@Rva000C65CB@@QAEXXZ  retail 0x000C65CB..0x000C6878 (685B)
// WorldBuilder twin 0x00947720 (1607B; its only name lead is the inlined
// RefCountClass::Release_Ref assert from refcount.h).
//
// Per-frame update of the bone-attached render objects: returns unless +0x14
// and the render object at +0x50 are set; then walks the 0x20-byte records of
// the vector at +0x164. A record whose frame count (+0x1C) has run out has its
// bone name pushed onto the string vector at +0x170 and its render object
// removed from W3DDisplay::m_3DScene (scene slot +0x0C) and released
// (Release_Ref inlined: Delete_This at slot 0) and is erased. Otherwise when
// the bone name is not empty the bone transform (render object slot +0xD0
// returning a Matrix3D by value) is rotated about X then Y then Z by the
// record's angles (+0x10/+0x14/+0x18; WWMath Matrix3D::Rotate_X/Y/Z inlined:
// sin then cos for X and Y and cos then sin for Z) and set on the record's
// render object (slot +0x54 Set_Transform); its count is decremented.
//
// Target facts: callee rows vector<string>::push_back 0x0007A773 and the
// record erase 0x000C4D52 (Rva000C24EAVector::eraseOne; record layout from
// Rva000C24EAVectorErase.cpp: word0 basic_string at +4 triple at +0x10 word at
// +0x1C); _sin/_cos imports; scene global 0x009E1B34. The sole caller
// 0x000C6E1A reads the drawable at +8 like W3DModelDraw and +0x50 is
// W3DModelDraw's render object; the owning class is not established so the
// name stays address-derived. Reading the angles through a reference to the
// record's triple is what reproduces retail's x87 schedule in Rotate_X.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>
#include <math.h>
#include "Coord3D.h"

class Vector4
{
public:
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline void Rotate_X(float theta)
	{
		float tmp1, tmp2;
		float s, c;

		s = sinf(theta);
		c = cosf(theta);

		tmp1 = Row[0][1]; tmp2 = Row[0][2];
		Row[0][1] = (float)( c*tmp1 + s*tmp2);
		Row[0][2] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][1]; tmp2 = Row[1][2];
		Row[1][1] = (float)( c*tmp1 + s*tmp2);
		Row[1][2] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][1]; tmp2 = Row[2][2];
		Row[2][1] = (float)( c*tmp1 + s*tmp2);
		Row[2][2] = (float)(-s*tmp1 + c*tmp2);
	}
	__forceinline void Rotate_Y(float theta)
	{
		float tmp1, tmp2;
		float s, c;

		s = sinf(theta);
		c = cosf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][2];
		Row[0][0] = (float)(c*tmp1 - s*tmp2);
		Row[0][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][2];
		Row[1][0] = (float)(c*tmp1 - s*tmp2);
		Row[1][2] = (float)(s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][2];
		Row[2][0] = (float)(c*tmp1 - s*tmp2);
		Row[2][2] = (float)(s*tmp1 + c*tmp2);
	}
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;

		c = cosf(theta);
		s = sinf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}

	Vector4 Row[3];
};

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass
{
public:
	virtual void Delete_This();								// +0x00
	RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03)
	RENDEROBJ_SLOT(04) RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07)
	RENDEROBJ_SLOT(08) RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11)
	RENDEROBJ_SLOT(12) RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15)
	RENDEROBJ_SLOT(16) RENDEROBJ_SLOT(17) RENDEROBJ_SLOT(18) RENDEROBJ_SLOT(19)
	RENDEROBJ_SLOT(20)
	virtual void Set_Transform(const Matrix3D &m);						// +0x54
	RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23)
	RENDEROBJ_SLOT(24) RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27)
	RENDEROBJ_SLOT(28) RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31)
	RENDEROBJ_SLOT(32) RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35)
	RENDEROBJ_SLOT(36) RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39)
	RENDEROBJ_SLOT(40) RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43)
	RENDEROBJ_SLOT(44) RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47)
	RENDEROBJ_SLOT(48) RENDEROBJ_SLOT(49)
	virtual int Get_Bone_Index(const char *bonename);					// +0xC8
	virtual Matrix3D Get_Bone_Transform(const char *bonename);				// +0xD0
	virtual Matrix3D Get_Bone_Transform(int boneindex);					// +0xCC

	void Release_Ref() const
	{
		NumRefs--;
		if (NumRefs == 0)
			const_cast<RenderObjClass *>(this)->Delete_This();
	}

private:
	mutable int NumRefs;									// +0x04
};

class SceneClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void Remove_Render_Object(RenderObjClass *obj);				// +0x0C
};
class RTS3DScene : public SceneClass {};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class Rva000C24EA
{
public:
	RenderObjClass *m_robj;			// +0x00
	_STL::basic_string<char> m_bone;	// +0x04
	Coord3D m_rotation;    			// +0x10
	int m_frames;				// +0x1C
};

class Rva000C24EAVector
{
public:
	Rva000C24EA *begin() { return _M_start; }
	Rva000C24EA *end() { return _M_finish; }
	Rva000C24EA *eraseOne(Rva000C24EA *position);
private:
	Rva000C24EA *_M_start, *_M_finish, *_M_end;
};

class Rva000C65CB
{
public:
	void rva000C65CB();
private:
	char m_pad00[0x14];
	void *m_14;					// +0x14
	char m_pad18[0x50 - 0x18];
	RenderObjClass *m_renderObject;		// +0x50
	char m_pad54[0x164 - 0x54];
	Rva000C24EAVector m_attached;		// +0x164
	_STL::vector<_STL::basic_string<char> > m_removed;	// +0x170
};

void Rva000C65CB::rva000C65CB()
{
	if (m_14 == 0 || m_renderObject == 0)
		return;
	Rva000C24EA *it = m_attached.begin();
	while (it != m_attached.end()) {
		if (it->m_frames <= 0) {
			m_removed.push_back(it->m_bone);
			W3DDisplay::m_3DScene->Remove_Render_Object(it->m_robj);
			it->m_robj->Release_Ref();
			it = m_attached.eraseOne(it);
			continue;
		}
		if (!it->m_bone.empty()) {
			Matrix3D tm = m_renderObject->Get_Bone_Transform(it->m_bone.c_str());
			const Coord3D &rot = it->m_rotation;
			tm.Rotate_X(rot.x);
			tm.Rotate_Y(rot.y);
			tm.Rotate_Z(rot.z);
			it->m_robj->Set_Transform(tm);
		}
		--it->m_frames;
		++it;
	}
}
