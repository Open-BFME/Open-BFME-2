// cl: /G7 /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// BFME2 MeshModelClass::install_materials, retail RVA 0x0018A070 (298 bytes through
// the ret 4 at 0x0018A197). Adapted from BFME1 MeshModelInstallMaterials.cpp
// (RVA 0x0096E7C0). Dedicated TU like MeshModelInstallAlternate.cpp: the shared
// meshmdlio.cpp TU cannot host this body under its include chain. TU-local views
// anchored to retail immediates: DefMatDesc +0x8C, AlternateMatDesc +0x90, MatInfo
// +0x98, context vertex materials +0xC8/+0xD4 and TextureCount +0x11C. Callees
// resolve by name: install_alternate_material_desc 0x188290, Post_Load_Process
// 0x15BB00, Peek_Texture 0x188700, MaterialInfoClass::Add_Texture 0x16FBF0.

#include "MeshMatDescClass.h"
#include "MeshModelClass.h"

class TextureClass
{
public:
	void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p) {
			p->Add_Ref();
		}
	}
	~BfmeHandleCX(void)
	{
		if (p) {
			p->Release_Ref();
		}
	}
};

class MeshLoadContextClass
{
	friend class MeshModelClass;

	BfmeHandleCX Peek_Texture(int index);
	int Texture_Count(void) const { return TextureCount; }
	VertexMaterialClass *Peek_Vertex_Material(int index) const
	{
		return VertexMaterials[index];
	}
	int Vertex_Material_Count(void) const { return VertexMaterialCount; }

private:
	char BeforeVertexMaterials[0xc8];
	VertexMaterialClass **VertexMaterials;
	int VertexMaterialMax;
	unsigned char VertexMaterialValid;
	unsigned char VertexMaterialAllocated;
	unsigned char VertexMaterialPadding[2];
	int VertexMaterialCount;
	int VertexMaterialGrowth;
	char BeforeTextureCount[0x11c - 0xdc];
	int TextureCount;
};

class MaterialVector
{
private:
	struct Dispatch
	{
		virtual void DestructorSlot(void);
		virtual void EqualitySlot(void);
		virtual bool Resize(int newsize, VertexMaterialClass **array);
	};

public:
	bool Add(VertexMaterialClass *const &value)
	{
		if (ActiveCount >= VectorMax) {
			if ((!IsAllocated && VectorMax) || GrowthStep <= 0) {
				return false;
			}
			if (!((Dispatch *)this)->Resize(VectorMax + GrowthStep, 0)) {
				return false;
			}
		}
		int index = ActiveCount++;
		Vector[index] = value;
		return true;
	}

private:
	unsigned int Vtable;
	VertexMaterialClass **Vector;
	int VectorMax;
	unsigned char Valid;
	unsigned char IsAllocated;
	unsigned char Padding[2];
	int ActiveCount;
	int GrowthStep;
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);

	void *Add_Texture(void *texture);
	void Add_Vertex_Material(VertexMaterialClass *material)
	{
		if (material) {
			material->Add_Ref();
		}
		VertexMaterials.Add(material);
	}

private:
	int RefCount;
	MaterialVector VertexMaterials;
};


void MeshModelClass::install_materials(MeshLoadContextClass *context)
{
	int i;

	install_alternate_material_desc(context);

	bool lighting_enabled = true;
	if (Flags & PRELIT_VERTEX) {
		lighting_enabled = false;
	}
	DefMatDesc->Post_Load_Process(lighting_enabled, this);
	if (AlternateMatDesc != 0) {
		AlternateMatDesc->Post_Load_Process(lighting_enabled, this);
	}

	// Passing the returned handle's address straight to the out-of-line Add_Texture
	// gives retail's allocation (this in EBX, the -1 unwind state and the vertex
	// material in EBP); the inline const-reference wrapper swaps the two registers.
	for (i = 0; i < context->Texture_Count(); i++) {
		MatInfo->Add_Texture((void *)&context->Peek_Texture(i));
	}

	for (i = 0; i < context->Vertex_Material_Count(); i++) {
		MatInfo->Add_Vertex_Material(context->Peek_Vertex_Material(i));
	}
}
