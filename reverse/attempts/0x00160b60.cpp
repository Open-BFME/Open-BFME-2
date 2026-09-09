// ?Get_Bone_Index@HTreeClass@@QBEHPBD@Z
// partial score=0.85 date=2026-09-08
// cl: /O2 /G6 /EHsc /MD /DNDEBUG
// BFME2 PivotClass stride is confirmed 0x58 (88) bytes and Name is its first
// field (offset 0): retail Get_Bone_Index (0x00560B60) increments its search
// pointer by 0x58 per iteration ("add edi,0x58") and retail Get_Bone_Name
// (0x00560BB0) computes &Pivot[boneidx] as Pivot + boneidx*0x58 via
// (boneidx*11)*8 == boneidx*0x58, then returns that pointer directly (Name
// is at offset 0, no adjustment). This agrees with the independently
// reverse-engineered HTreeClass::Control_Bone (htree_control.cpp) and a
// disassembly of HTreeClass::Base_Update (0x001628A0), both of which read
// HTreeClass::NumPivots at this+0x10 and HTreeClass::Pivot at this+0x14 --
// the same offsets used here. See reference/shims/bfme2htree/htree.h for the
// corrected HTreeClass layout (NumPivots@0x10, Pivot@0x14 there too).
//
// PivotClass's own full BFME2 layout is NOT reconstructed here (Base_Update
// shows its BaseTransform/Transform fields shrank from a 48-byte Matrix3D
// each to a 28-byte Quaternion+Vector3 pair, a real engine change, not a
// simple offset shift -- flagged for structural, not layout, work). Only the
// stride and the Name field at offset 0 are needed by these two functions,
// so the rest of the 0x58 bytes are left opaque.
#include <string.h>

class PivotClass
{
public:
	char Name[16];
	char _bfme_unk_10[0x58 - 16];
};

class HTreeClass
{
	char _bfme_unk_0[0x10];
	int NumPivots;
	PivotClass *Pivot;
public:
	int Get_Bone_Index(const char *name) const;
	const char *Get_Bone_Name(int boneidx) const;
};

int HTreeClass::Get_Bone_Index(const char *name) const
{
	if (NumPivots > 0) {
		int i = 0;
		PivotClass *pivot = Pivot;
		do {
			if (stricmp(pivot->Name, name) == 0) {
				return i;
			}
			++i;
			++pivot;
		} while (i < NumPivots);
	}
	return 0;
}

const char *HTreeClass::Get_Bone_Name(int boneidx) const
{
	return Pivot[boneidx].Name;
}