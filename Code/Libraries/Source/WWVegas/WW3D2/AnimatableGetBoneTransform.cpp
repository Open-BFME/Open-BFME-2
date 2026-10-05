// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Get_Bone_Transform@Animatable3DObjClass@@UAE?AVMatrix3D@@PBD@Z @0x001A4DE0 133B
// Animatable3DObjClass::Get_Bone_Transform by-name forwarder to by-index at slot 51 (+0xCC); BFME1 donor animobj.cpp Get_Bone_Transform but BFME2 returns Matrix3D by value (hidden ptr, ret 8); vtable 0x7D6D10 slot 52; HTree +0xF8 Transform +0x18; callee Get_Bone_Index 0x160B60 rowed.
// ?Get_Bone_Transform@Animatable3DObjClass@@UAE?AVMatrix3D@@H@Z @0x001A56E0 537B, the by-index target at slot 51: Zero Hour's body, with the pivot expanded through a local Matrix3D (retail keeps its 0x30-byte frame).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "matrix3d.h"

// BFME 2's pivot keeps its current transform as a rotation quaternion at +0x30
// and a translation at +0x40 (HTreePivotClass.cpp's constructor and assignment
// prove the offsets); Get_Bone_Transform expands it into a Matrix3D.
struct HTreeBoneTransform
{
	float X, Y, Z, W;
	Vector3 Position;
};

struct HTreeBone
{
	unsigned char m_pad00[0x30];
	HTreeBoneTransform Transform;
	unsigned char m_pad4C[0x50 - 0x4C];
	bool m_captured;
	unsigned char m_pad51[88 - 0x50 - 1];
};

static __forceinline Matrix3D &boneMatrix(const HTreeBoneTransform &q, Matrix3D &m)
{
	const float xx = q.X * q.X * 2.0f;
	const float xy = q.X * q.Y * 2.0f;
	const float xz = q.Z * q.X * 2.0f;
	const float wx = q.W * q.X * 2.0f;
	const float yy = q.Y * q.Y * 2.0f;
	const float yz = q.Z * q.Y * 2.0f;
	const float wy = q.W * q.Y * 2.0f;
	const float zz = q.Z * q.Z * 2.0f;
	const float wz = q.W * q.Z * 2.0f;

	m[0][0] = 1.0f - yy - zz;
	m[0][1] = xy - wz;
	m[0][2] = xz + wy;
	m[1][0] = xy + wz;
	m[1][1] = 1.0f - zz - xx;
	m[1][2] = yz - wx;
	m[2][0] = xz - wy;
	m[2][1] = yz + wx;
	m[2][2] = 1.0f - yy - xx;
	m[0][3] = q.Position.X;
	m[1][3] = q.Position.Y;
	m[2][3] = q.Position.Z;
	return m;
}

class HTreeClass
{
	friend class Animatable3DObjClass;

public:
	int Get_Bone_Index(const char *bonename) const;

private:
	unsigned char m_pad00[0x14];
	HTreeBone *m_bones;
};

class Animatable3DObjClass
{
public:
	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void pad4() = 0;
	virtual void pad5() = 0;
	virtual void pad6() = 0;
	virtual void pad7() = 0;
	virtual void pad8() = 0;
	virtual void pad9() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual void pad16() = 0;
	virtual void pad17() = 0;
	virtual void pad18() = 0;
	virtual void pad19() = 0;
	virtual void Validate_Transform();
	virtual void pad21() = 0;
	virtual void pad22() = 0;
	virtual void pad23() = 0;
	virtual void pad24() = 0;
	virtual void pad25() = 0;
	virtual void pad26() = 0;
	virtual void pad27() = 0;
	virtual void pad28() = 0;
	virtual void pad29() = 0;
	virtual void pad30() = 0;
	virtual void pad31() = 0;
	virtual void pad32() = 0;
	virtual void pad33() = 0;
	virtual void pad34() = 0;
	virtual void pad35() = 0;
	virtual void pad36() = 0;
	virtual void pad37() = 0;
	virtual void pad38() = 0;
	virtual void pad39() = 0;
	virtual void pad40() = 0;
	virtual void pad41() = 0;
	virtual void Update_Sub_Object_Transforms();
	virtual void pad43() = 0;
	virtual void pad44() = 0;
	virtual void pad45() = 0;
	virtual void pad46() = 0;
	virtual void pad47() = 0;
	virtual void pad48() = 0;
	virtual void pad49() = 0;
	virtual void pad50() = 0;
	virtual Matrix3D Get_Bone_Transform(const char *bonename);
	virtual Matrix3D Get_Bone_Transform(int boneindex);
	virtual bool rva001A4E70(int boneindex);

private:
	unsigned char m_pad04[0x18 - 4];
	Matrix3D m_transform;
	unsigned char m_pad48[0xF4 - 0x48];
	bool m_hierarchyValid;
	unsigned char m_padF5[0xF8 - 0xF5];
	HTreeClass *m_htree;
};

Matrix3D Animatable3DObjClass::Get_Bone_Transform(const char *bonename)
{
	if (m_htree) {
		int idx = m_htree->Get_Bone_Index(bonename);
		return Get_Bone_Transform(idx);
	} else {
		Validate_Transform();
		return m_transform;
	}
}

bool Animatable3DObjClass::rva001A4E70(int boneindex)
{
	Validate_Transform();
	if (m_htree) {
		if (!m_hierarchyValid)
			Update_Sub_Object_Transforms();
		return m_htree->m_bones[boneindex].m_captured;
	} else {
		return true;
	}
}

Matrix3D Animatable3DObjClass::Get_Bone_Transform(int boneindex)
{
	Validate_Transform();
	if (m_htree) {
		if (!m_hierarchyValid)
			Update_Sub_Object_Transforms();
		Matrix3D m;
		return boneMatrix(m_htree->m_bones[boneindex].Transform,m);
	} else {
		return m_transform;
	}
}
