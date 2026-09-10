// cl: /O2 /G7 /MD
//
// MeshModelClass::get_sort_flags(int), retail 0x00189270, 125 bytes.
// Dedicated TU so meshmdlio.cpp keeps its matched bodies.
// Shader[pass] is at MatDesc+0x98; ShaderArray[pass] at +0xF8.

class ShaderClass
{
public:
	enum StaticSortCategoryType {
		SSCAT_OPAQUE,
		SSCAT_ALPHA_TEST,
		SSCAT_ADDITIVE,
		SSCAT_SCREEN,
		SSCAT_OTHER
	};
	unsigned Bits;
	StaticSortCategoryType Get_SS_Category() const;
};

class ShareBufferClass
{
	int Vptr;
	int NumRefs;
	ShaderClass *RawBuffer;
	ShaderClass *Array;
	int Count;
public:
	int Get_Count() { return Count; }
	ShaderClass &Get_Element(int index) { return Array[index]; }
};

class MeshMatDescClass
{
public:
	unsigned char Pad[0x98];
	ShaderClass Shader[4];
	unsigned char Mid[0x50];
	ShareBufferClass *ShaderArray[4];

	ShaderClass Get_Single_Shader(int pass) const { return Shader[pass]; }
	bool Has_Shader_Array(int pass) const { return ShaderArray[pass] != 0; }
};

class MeshModelClass
{
public:
	bool Has_Shader_Array(int pass) const { return CurMatDesc->Has_Shader_Array(pass); }
	ShaderClass Get_Single_Shader(int pass) const { return CurMatDesc->Get_Single_Shader(pass); }

protected:
	unsigned int get_sort_flags(int pass) const;

	unsigned char Pad[0x94];
	MeshMatDescClass *CurMatDesc;
};

unsigned int MeshModelClass::get_sort_flags(int pass) const
{
	unsigned int flags = 0;
	ShaderClass::StaticSortCategoryType scat;
	if (Has_Shader_Array(pass)) {
		for (int tri = 0; tri < CurMatDesc->ShaderArray[pass]->Get_Count(); tri++) {
			scat = CurMatDesc->ShaderArray[pass]->Get_Element(tri).Get_SS_Category();
			flags |= (1 << scat);
		}
	} else {
		scat = Get_Single_Shader(pass).Get_SS_Category();
		flags |= (1 << scat);
	}
	return flags;
}
