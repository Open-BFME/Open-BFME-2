// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Link view first: Matrix3D copy ctor stays inline without emitting a copy that competes with retail's owner (0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_copy_link/matrix3d_copy_link.h"
// ?Get_Bone_Transform@RenderObjClass@@UAE?AVMatrix3D@@PBD@Z @0x0006D06D 106B
// RenderObjClass::Get_Bone_Transform default body (BFME1 donor rendobj.h: { return Get_Transform(); }),
// vftable 0x00BD2F68 slots 51 (by name) and 52 (by index) both point here; BFME2 returns Matrix3D
// by value (hidden pointer, RET 8) as Animatable3DObjClass's override at 0x001A4DE0 does.
// Get_Transform is the inline Validate_Transform (slot 20, +0x50) then Transform at +0x18.
// The by-index overload compiles to the same bytes and retail folds the two.
// Size-optimised (/O1) like its 0x0006Cxxx neighbours: the Row[3] default construction goes through ??_H.
#include "matrix3d.h"

// Private slice of RenderObjClass: only the slots and fields this body touches.
#include "rendobj.h"

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
