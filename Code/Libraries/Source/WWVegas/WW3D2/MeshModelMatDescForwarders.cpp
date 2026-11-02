// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
//
// Out-of-line copies of the MeshModelClass forwarders that Zero Hour's
// meshmdl.h writes inline as CurMatDesc->X(...) (GPL-3.0-or-later donor:
// GeneralsMD WW3D2/meshmdl.h, Make_*_Unique in meshmdl.cpp). Retail keeps each
// as an 11-byte body: mov ecx, [ecx+0x94] (CurMatDesc, the offset the rowed
// MeshModelTextureReplacement.cpp verifies); tail jump to the rowed
// MeshMatDescClass member. Names are Zero Hour's; signatures are BFME's (the
// targets' mangling: textures as RefCountPtr<TextureClass>).
//
// Two more 11-byte bodies forward through a MeshModelClass pointer at +0xC4 to
// the rowed MeshModelClass::Replace_Texture / Replace_VertexMaterial. Zero
// Hour's MeshClass does exactly this, but BFME's MeshClass::Replace_Texture is
// already rowed elsewhere (a 189-byte virtual), so the owner of these two is
// unknown and they stay address-named. No referencing site was found for any
// of these nine in this pass.
class TextureClass;
template<class T> class RefCountPtr;
class VertexMaterialClass;

#include "MeshMatDescClass.h"

class MeshModelClass
{
public:
	VertexMaterialClass *Peek_Material(int vidx, int pass) const;
	void Set_Single_Texture(const RefCountPtr<TextureClass> &tex, int pass, int stage);
	void Set_Single_Material(VertexMaterialClass *vmat, int pass);
	void Set_Material(int vidx, VertexMaterialClass *vmat, int pass);
	void Set_Texture(int pidx, const RefCountPtr<TextureClass> &tex, int pass, int stage);
	void Make_UV_Array_Unique(int pass, int stage);
	void Make_Color_Array_Unique(int array_index);
	void Replace_Texture(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &new_texture);
	void Replace_VertexMaterial(VertexMaterialClass *vmat, VertexMaterialClass *new_vmat);
private:
	char m_gap00[0x94];
	MeshMatDescClass *CurMatDesc;	// +0x94
};

// 0x00143550
inline __declspec(noinline) VertexMaterialClass *MeshModelClass::Peek_Material(int vidx, int pass) const { return CurMatDesc->Peek_Material(vidx, pass); }
// 0x00149510
inline __declspec(noinline) void MeshModelClass::Set_Single_Texture(const RefCountPtr<TextureClass> &tex, int pass, int stage) { CurMatDesc->Set_Single_Texture(tex, pass, stage); }
// 0x00171680
inline __declspec(noinline) void MeshModelClass::Set_Single_Material(VertexMaterialClass *vmat, int pass) { CurMatDesc->Set_Single_Material(vmat, pass); }
// 0x00171690
inline __declspec(noinline) void MeshModelClass::Set_Material(int vidx, VertexMaterialClass *vmat, int pass) { CurMatDesc->Set_Material(vidx, vmat, pass); }
// 0x001716A0
void MeshModelClass::Set_Texture(int pidx, const RefCountPtr<TextureClass> &tex, int pass, int stage) { CurMatDesc->Set_Texture(pidx, tex, pass, stage); }
// 0x00171760
void MeshModelClass::Make_UV_Array_Unique(int pass, int stage) { CurMatDesc->Make_UV_Array_Unique(pass, stage); }
// 0x00171770
void MeshModelClass::Make_Color_Array_Unique(int array_index) { CurMatDesc->Make_Color_Array_Unique(array_index); }
// Peek_Material, Set_Single_Texture, Set_Single_Material and Set_Material are
// noinline inline COMDATs: MaterialCollectorCollectMaterials.cpp, meshmdlio.cpp
// and bfme2_mesh_material_pass.cpp compile byte-identical in-class copies from
// their meshmdl.h views, which now fold with these.
static VertexMaterialClass *(MeshModelClass::*s_anchor_Peek_Material)(int, int) const = &MeshModelClass::Peek_Material;
static void (MeshModelClass::*s_anchor_Set_Single_Texture)(const RefCountPtr<TextureClass> &, int, int) = &MeshModelClass::Set_Single_Texture;
static void (MeshModelClass::*s_anchor_Set_Single_Material)(VertexMaterialClass *, int) = &MeshModelClass::Set_Single_Material;
static void (MeshModelClass::*s_anchor_Set_Material)(int, VertexMaterialClass *, int) = &MeshModelClass::Set_Material;

class Rva00149BF0Owner
{
public:
	void rva00149BF0(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &new_texture);
	void rva00149C00(VertexMaterialClass *vmat, VertexMaterialClass *new_vmat);
private:
	char m_gap00[0xC4];
	MeshModelClass *m_model;	// +0xC4
};

// 0x00149BF0
void Rva00149BF0Owner::rva00149BF0(const RefCountPtr<TextureClass> &texture, const RefCountPtr<TextureClass> &new_texture) { m_model->Replace_Texture(texture, new_texture); }
// 0x00149C00
void Rva00149BF0Owner::rva00149C00(VertexMaterialClass *vmat, VertexMaterialClass *new_vmat) { m_model->Replace_VertexMaterial(vmat, new_vmat); }
