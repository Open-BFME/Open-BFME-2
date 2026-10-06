// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Get_Bone_Transform@RenderObjClass@@UAE?AVMatrix3D@@PBD@Z @0x0006D06D 106B
// RenderObjClass::Get_Bone_Transform default body (BFME1 donor rendobj.h: { return Get_Transform(); }),
// vftable 0x00BD2F68 slots 51 (by name) and 52 (by index) both point here; BFME2 returns Matrix3D
// by value (hidden pointer, RET 8) as Animatable3DObjClass's override at 0x001A4DE0 does.
// Get_Transform is the inline Validate_Transform (slot 20, +0x50) then Transform at +0x18.
// The by-index overload compiles to the same bytes and retail folds the two.
// Size-optimised (/O1) like its 0x0006Cxxx neighbours: the Row[3] default construction goes through ??_H.
#include "matrix3d.h"

// Private slice of RenderObjClass: only the slots and fields this body touches.
class RenderObjClass
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
	virtual void Validate_Transform(void) const;
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
	virtual void pad42() = 0;
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

private:
	unsigned char m_pad04[0x18 - 4];
	Matrix3D Transform;
};

Matrix3D RenderObjClass::Get_Bone_Transform(const char *bonename)
{
	Validate_Transform();
	return Transform;
}

Matrix3D RenderObjClass::Get_Bone_Transform(int boneindex)
{
	Validate_Transform();
	return Transform;
}
