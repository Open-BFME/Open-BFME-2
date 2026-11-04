// flags: region default (reverse/retail_inventory/flag_regions.csv) plus NDEBUG and the canonical camera header include paths
// cl: /DNDEBUG /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// ?Set_Reflected_Projection_Matrix@CameraClass@@QAEXABVMatrix4@@@Z, retail 0x00133DA0, 150 bytes.
// CameraClass AdditionalTransform setter (second Matrix4 at +0x38C, BFME2
// addition per bfmecamera shim; setter at RVA 0x133DA0 writes all 16 floats).
// Gap between Get_Aspect_Ratio 0x133D90/7 and Convert_Old 0x133E40/55 in
// camera.cpp; new file beside it (minimal /O1 with 16 explicit dword stores
// gives the unrolled movs with last via eax saving 3B; struct-copy = would
// give rep movsd 22B, not retail). Identity is address-derived honest name
// (CameraClass proven by neighbours + shim + copy ctor/operator= copying
// AdditionalTransform; 64B Matrix4 copy + sole caller 0x7F7E1). No fallback
// paths.

#include "CameraClass.h"

// ?Set_Reflected_Projection_Matrix@CameraClass@@QAEXABVMatrix4@@@Z @0x00133DA0
void CameraClass::Set_Reflected_Projection_Matrix(const Matrix4 &src)
{
	const int *from = (const int *)&src;
	((int *)field38C)[0] = from[0];
	((int *)field38C)[1] = from[1];
	((int *)field38C)[2] = from[2];
	((int *)field38C)[3] = from[3];
	((int *)field38C)[4] = from[4];
	((int *)field38C)[5] = from[5];
	((int *)field38C)[6] = from[6];
	((int *)field38C)[7] = from[7];
	((int *)field38C)[8] = from[8];
	((int *)field38C)[9] = from[9];
	((int *)field38C)[10] = from[10];
	((int *)field38C)[11] = from[11];
	((int *)field38C)[12] = from[12];
	((int *)field38C)[13] = from[13];
	((int *)field38C)[14] = from[14];
	((int *)field38C)[15] = from[15];
}
