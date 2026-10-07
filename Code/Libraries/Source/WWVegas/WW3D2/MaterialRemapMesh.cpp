// cl: /DNDEBUG /MD /EHsc /Ob2
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Semantic donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/Libraries/Source/WWVegas/WW3D2/MaterialRemapMesh.cpp and matinfo.cpp.
// BFME2 clone_materials calls this 573-byte body at 0x16F220 with the source
// and destination material descriptions. Retail reads Material +0xA8,
// TextureArray +0xC8, MaterialArray +0xE8. Reference owning-handle lifetimes
// reproduce all four EH states and the texture remap/set/release call chain.
// BfmeHandleCX is the established donor placeholder name for the handle.
// Remap_Vertex_Material must be visible here: retail inlines its cache/search
// while keeping Remap_Texture out of line. /G7 matches the sibling matinfo TU.
class VertexMaterialClass;

class TextureClass
{
public:
	void Add_Ref(void)
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref(void);
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	int m_refs;
	int m_08;
	VertexMaterialClass **VmatVector;
	int m_10;
	int m_14;
	int VmatCount;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int TextureCount;

	int Vertex_Material_Count(void) const
	{
		return VmatCount;
	}

	VertexMaterialClass *Peek_Vertex_Material(int index)
	{
		return VmatVector[index];
	}

	void Add_Ref(void)
	{
		++m_refs;
	}
};

struct VmatRemapStruct
{
	VertexMaterialClass *Src;
	VertexMaterialClass *Dest;
};

// Same spelling as the ICF'd Get_Texture return so
// ?bfmeGet@Gen_007A0340@@QBE?AVBfmeHandleCX@@H@Z resolves.
class BfmeHandleCX
{
	public:
	TextureClass *p;

	BfmeHandleCX(void) : p(0)
	{
	}

	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p)
			p->Add_Ref();
	}

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p)
			other.p->Add_Ref();
		if (p)
			p->Release_Ref();
		p = other.p;
		return *this;
	}
};

struct TextureRemapStruct
{
	BfmeHandleCX Src;
	BfmeHandleCX Dest;
};

class Gen_007A0340
{
public:
	BfmeHandleCX bfmeGet(int index) const;
};

// BFME MeshMatDesc fields used by the original matinfo.cpp traversal.
class MeshMatDescClass {
public:
 int PassCount, VertexCount, PolygonCount;
 char pad[0x9C];
 VertexMaterialClass *Material[4];
 char beforeTextureArray[0x10];
 void *TextureArray[4][2];
 void *MaterialArray[4];
 int Get_Pass_Count() const { return PassCount; }
 int Get_Vertex_Count() const { return VertexCount; }
 int Get_Polygon_Count() const { return PolygonCount; }
 bool Has_Material_Array(int pass) const { return MaterialArray[pass] != 0; }
 bool Has_Texture_Array(int pass, int stage) const { return TextureArray[pass][stage] != 0; }
 VertexMaterialClass *Peek_Single_Material(int pass) const { return Material[pass]; }
 VertexMaterialClass *Peek_Material(int index, int pass) const;
 void Set_Material(int index, VertexMaterialClass *material, int pass);
 void Set_Single_Material(VertexMaterialClass *material, int pass);
 BfmeHandleCX Get_Texture(int index, int pass, int stage) const;
 BfmeHandleCX Get_Single_Texture(int pass, int stage) const;
 void Set_Texture(int index, const BfmeHandleCX &texture, int pass, int stage);
 void Set_Single_Texture(const BfmeHandleCX &texture, int pass, int stage);
};

class MaterialRemapperClass
{
public:
	MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest);
	~MaterialRemapperClass(void);
 BfmeHandleCX Remap_Texture(const BfmeHandleCX &src);
 VertexMaterialClass *Remap_Vertex_Material(VertexMaterialClass *src)
 {
	if (src == 0) return src;
	if (src == LastSrcVmat) return LastDestVmat;
	for (int i=0; i<VertexMaterialCount; i++) {
		if (VertexMaterialRemaps[i].Src == src) {
			LastSrcVmat = src;
			LastDestVmat = VertexMaterialRemaps[i].Dest;
			return VertexMaterialRemaps[i].Dest;
		}
	}
	return 0;
}
 void Remap_Mesh(const MeshMatDescClass *src, MeshMatDescClass *dest);

	MaterialInfoClass *SrcMatInfo;
	MaterialInfoClass *DestMatInfo;
	int TextureCount;
	TextureRemapStruct *TextureRemaps;
	int VertexMaterialCount;
	VmatRemapStruct *VertexMaterialRemaps;
	VertexMaterialClass *LastSrcVmat;
	VertexMaterialClass *LastDestVmat;
	BfmeHandleCX LastSrcTex;
	BfmeHandleCX LastDestTex;
};



void MaterialRemapperClass::Remap_Mesh(const MeshMatDescClass *src, MeshMatDescClass *dest)
{
 if (SrcMatInfo->Vertex_Material_Count() >= 1) {
  for (int pass = 0; pass < src->Get_Pass_Count(); ++pass) {
   if (src->Has_Material_Array(pass)) {
    for (int vertex = 0; vertex < src->Get_Vertex_Count(); ++vertex) {
     VertexMaterialClass *material = src->Peek_Material(vertex, pass);
     dest->Set_Material(vertex, Remap_Vertex_Material(material), pass);
    }
   } else {
    dest->Set_Single_Material(Remap_Vertex_Material(src->Peek_Single_Material(pass)), pass);
   }
  }
 }
 if (SrcMatInfo->TextureCount >= 1) {
  for (int pass = 0; pass < src->Get_Pass_Count(); ++pass) {
   for (int stage = 0; stage < 2; ++stage) {
    if (src->Has_Texture_Array(pass, stage)) {
     for (int polygon = 0; polygon < src->Get_Polygon_Count(); ++polygon) {
      BfmeHandleCX texture = src->Get_Texture(polygon, pass, stage);
      dest->Set_Texture(polygon, Remap_Texture(texture), pass, stage);
     }
    } else {
     BfmeHandleCX texture = src->Get_Single_Texture(pass, stage);
     dest->Set_Single_Texture(Remap_Texture(texture), pass, stage);
    }
   }
  }
 }
}

// Existing providers use the RefCountPtr spelling for the same one-pointer
// owning return ABI. Native calls at 0x16F35C and in the single-texture arm
// bind these operations to those byte-verified providers. ZH's single-texture
// arm calls Peek_Single_Texture, the header inline whose /O1 copy is D2026.
#pragma comment(linker, "/alternatename:?Get_Texture@MeshMatDescClass@@QBE?AVBfmeHandleCX@@HHH@Z=?Get_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HHH@Z")
#pragma comment(linker, "/alternatename:?Get_Single_Texture@MeshMatDescClass@@QBE?AVBfmeHandleCX@@HH@Z=?Peek_Single_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HH@Z")
