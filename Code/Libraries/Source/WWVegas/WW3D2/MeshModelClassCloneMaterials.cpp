// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// MeshModelClass::clone_materials, retail 0x001881C0 (202 bytes).
// BFME1 meshmdlio.cpp clone_materials port (their 203B row): the release
// keeps the NULL store inside the taken branch (spelled out, not the
// ZH REF_PTR_RELEASE whose store sits outside), and MatInfo allocates
// through the global operator new (::new, not the pooled NEW_REF -- retail
// pushes 0x38 and calls ??2 at 0x2FDA0). The failing-new skip around the
// MaterialInfoClass copy falls out of the TU-local operator new declaration
// (BfmeMapPictureTextureCtor precedent). Release_Ref inlines the shared
// decref plus conditional slot-0 Delete_This; /G7 renders the decrement as
// add (partial-flag stall avoidance, cf. the HAnimCombo ADD precedent).
// Remapper ctor/dtor plus Remap_Mesh and the MaterialInfoClass copy resolve
// to pins (matinfo.cpp holds the future row bodies).

typedef unsigned int size_t;
void *__cdecl operator new(size_t bytes);

#define NULL 0

class MeshMatDescClass;

class MaterialInfoClass
{
public:
	MaterialInfoClass(const MaterialInfoClass &src);
	virtual void Delete_This();
	void Release_Ref() const
	{
		NumRefs--;
		if (NumRefs == 0)
			const_cast<MaterialInfoClass *>(this)->Delete_This();
	}

private:
	mutable int NumRefs;
	// VertexMaterials + Textures vector members live here; total instance
	// size 0x38 is proven by retail's push-0x38 at the ::new call below.
	// The true member layout belongs to the future MaterialInfoClass copy
	// conversion (351B body at 0x16FFD0).
	char m_pad[0x38 - 8];
};

class MaterialRemapperClass
{
public:
	MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest);
	~MaterialRemapperClass();
	void Remap_Mesh(const MeshMatDescClass *srcmeshmatdesc, MeshMatDescClass *destmeshmatdesc);

private:
	struct VmatRemapStruct
	{
		void *Src;
		void *Dest;
	};

	struct TextureRemapStruct
	{
		void *Src;
		void *Dest;
	};

	MaterialInfoClass *SrcMatInfo;
	MaterialInfoClass *DestMatInfo;

	int TextureCount;
	TextureRemapStruct *TextureRemaps;
	int VertexMaterialCount;
	VmatRemapStruct *VertexMaterialRemaps;

	void *LastSrcVmat;
	void *LastDestVmat;
	void *LastSrcTex;
	void *LastDestTex;
};

class MeshModelClass
{
protected:
	void clone_materials(const MeshModelClass &srcmesh);

private:
	char m_pad[0x94];
	MeshMatDescClass *CurMatDesc;
	MaterialInfoClass *MatInfo;
};

// ?clone_materials@MeshModelClass@@IAEXABV1@@Z
void MeshModelClass::clone_materials(const MeshModelClass &srcmesh)
{
	/*
	** Copy the material info and the materials within
	*/
	if (MatInfo != NULL) {
		MatInfo->Release_Ref();
		MatInfo = NULL;
	}
	MatInfo = ::new MaterialInfoClass(*(srcmesh.MatInfo));

	/*
	** remap!
	*/
	MaterialRemapperClass remapper(srcmesh.MatInfo, MatInfo);
	remapper.Remap_Mesh(srcmesh.CurMatDesc, CurMatDesc);
}
