// cl: /DNDEBUG /MD /EHsc
//
// HTreeClass::Get_Bone_Index (retail 0x00160B60, 68 bytes),
// HTreeClass::Get_Bone_Name (retail 0x00160BB0, 22 bytes) and
// HTreeClass::Get_Parent_Index (retail 0x00160BD0, 35 bytes).
//
// BFME 2 shrank Zero Hour's PivotClass (two 48-byte Matrix3D members plus
// capture data) to 0x58-byte records: Name[16], Parent at +0x10, two
// rotation-plus-translation blocks at +0x14/+0x30, Index at +0x4C,
// IsVisible at +0x50, PivotFade at +0x54. Proven by the landed
// HTreeClassCopyConstructor unit, whose TU-local model is reused here
// verbatim; htree.cpp's bfme2htree shim still carries Zero Hour's layout,
// so these two stride-sensitive accessors live in this dedicated unit
// (duplicate emissions across TUs pass the gates; htree.cpp keeps its own
// present-unmatched copies).
//
// Bodies are Zero Hour's htree.cpp verbatim except for the compare call:
// retail resolves it through the _strcmpi import slot (0x00BBA518), so the
// source spells _strcmpi, matching the landed BitFlags getSingleBitFromName
// family. /G7 is the unit's tell (same as the copy-constructor unit).

#include <string.h>
#include <assert.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
// (reduced BFME 2 model: 0x58-byte pivots, see note above)
struct PivotClass
{
public:
	char Name[16];
	PivotClass *Parent;					// +0x10
	unsigned char m_bfme14[0x4C - 0x14];
	int Index;							// +0x4C
	unsigned char m_bfme50[0x58 - 0x50];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	int Get_Bone_Index(const char * name) const;
	const char * Get_Bone_Name(int boneidx) const;
	int Get_Parent_Index(int bone_indx) const;

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
};

int HTreeClass::Get_Bone_Index(const char * name) const
{
	int i = 0;
	if (NumPivots > i) {
		do {
			if (_strcmpi(Pivot[i].Name, name) == 0) {
				return i;
			}
			++i;
		} while (i < NumPivots);
	}
	return 0;
}

const char * HTreeClass::Get_Bone_Name(int boneidx) const
{
	assert(boneidx >= 0);
	assert(boneidx < NumPivots);

	return Pivot[boneidx].Name;
}

int HTreeClass::Get_Parent_Index(int bone_indx) const
{
	assert(bone_indx >= 0);
	assert(bone_indx < NumPivots);

	if (Pivot[bone_indx].Parent != NULL) {
		return Pivot[bone_indx].Parent->Index;
	} else {
		return 0;
	}
}
