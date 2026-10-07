// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : MatInfo.h                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/matinfo.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 6/15/01 5:50p                                               $*
 *                                                                                             *
 *                    $Revision:: 10                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "matinfo.h"
#include "wwdebug.h"
#include "meshmdl.h"
#include "texture.h"

// ??0MaterialInfoClass@@ present-unmatched
MaterialInfoClass::MaterialInfoClass(void)
{
}

// ??0MaterialInfoClass@@ present-unmatched
MaterialInfoClass::MaterialInfoClass(const MaterialInfoClass & src)
{
	for (int mi=0; mi<src.VertexMaterials.Count(); mi++) {
		VertexMaterialClass * vmat;
		vmat = src.VertexMaterials[mi]->Clone();
		VertexMaterials.Add(vmat);
	}
	
	for (int ti=0; ti<src.Textures.Count(); ti++) {
		TextureClass * tex = src.Textures[ti];
		tex->Add_Ref();
		Textures.Add(tex);
	}
}


// ??1MaterialInfoClass@@UAE@XZ present-unmatched
MaterialInfoClass::~MaterialInfoClass(void)
{
	Free();
}


// ?Clone@MaterialInfoClass@@QBEPAV1@XZ present-unmatched
MaterialInfoClass * MaterialInfoClass::Clone(void) const
{ 
	return W3DNEW MaterialInfoClass(*this); 
}

// ?Add_Texture@MaterialInfoClass@@QAEHPAVTextureClass@@@Z present-unmatched
int MaterialInfoClass::Add_Texture(TextureClass * tex)
{
	WWASSERT(tex != NULL);
	tex->Add_Ref();
	int index = Textures.Count();
	Textures.Add(tex);
	return index;
}

// ?Get_Texture_Index@MaterialInfoClass@@QAEHPBD@Z present-unmatched
int MaterialInfoClass::Get_Texture_Index(const char * name)
{
	for (int i=0; i<Textures.Count(); i++) {
		if (stricmp(name,Textures[i]->Get_Texture_Name()) == 0) {
			return i;
		}
	}
	return -1;
}

// ?Get_Texture@MaterialInfoClass@@QAEPAVTextureClass@@H@Z present-unmatched
TextureClass * MaterialInfoClass::Get_Texture(int index)
{
	WWASSERT(index >= 0);
	WWASSERT(index < Textures.Count());
	Textures[index]->Add_Ref();
	return Textures[index];
}

/*

// ?Set_Texture_Reduction_Factor@MaterialInfoClass@@ present-unmatched
void MaterialInfoClass::Set_Texture_Reduction_Factor(float trf)
{
	for (int i = 0; i < Textures.Count(); i++) {
		Textures[i]->Set_Reduction_Factor(trf);
	}
}


// ?Process_Texture_Reduction@MaterialInfoClass@@ present-unmatched
void MaterialInfoClass::Process_Texture_Reduction(void)
{
	for (int i = 0; i < Textures.Count(); i++) {
		Textures[i]->Process_Reduction();
	}
}
*/
// MaterialInfoClass::Free is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/MaterialInfoFree.cpp (0x0016EE70).


// ??0MaterialRemapperClass@@QAE@PAVMaterialInfoClass@@0@Z present-unmatched
MaterialRemapperClass::MaterialRemapperClass(MaterialInfoClass * src,MaterialInfoClass * dest) :
	TextureCount(0),
	TextureRemaps(NULL),
	VertexMaterialCount(0),
	VertexMaterialRemaps(NULL),
	LastSrcVmat(NULL),
	LastDestVmat(NULL),
	LastSrcTex(NULL),
	LastDestTex(NULL)
{
	WWASSERT(src);
	WWASSERT(dest);
	WWASSERT(src->Texture_Count() == dest->Texture_Count());
	WWASSERT(src->Vertex_Material_Count() == dest->Vertex_Material_Count());

	SrcMatInfo = src;
	SrcMatInfo->Add_Ref();
	DestMatInfo = dest;
	DestMatInfo->Add_Ref();

	if (src->Vertex_Material_Count() > 0) {
		VertexMaterialCount = src->Vertex_Material_Count();
		VertexMaterialRemaps = W3DNEWARRAY VmatRemapStruct[VertexMaterialCount];
		for (int i=0; i<src->Vertex_Material_Count(); i++) {
			VertexMaterialRemaps[i].Src = src->Peek_Vertex_Material(i);
			VertexMaterialRemaps[i].Dest = dest->Peek_Vertex_Material(i);
		}
	}

	if (src->Texture_Count() > 0) {
		TextureCount = src->Texture_Count();
		TextureRemaps = W3DNEWARRAY TextureRemapStruct[TextureCount];
		for (int i=0; i<src->Texture_Count(); i++) {
			TextureRemaps[i].Src = src->Peek_Texture(i);
			TextureRemaps[i].Dest = dest->Peek_Texture(i);
		}
	}
}

// Owned by MaterialRemapperClassDtor.cpp.

// ?Remap_Texture@MaterialRemapperClass@@QAEPAVTextureClass@@PAV2@@Z present-unmatched
TextureClass * MaterialRemapperClass::Remap_Texture(TextureClass * src)
{
	if (src == NULL) return src;
	if (src == LastSrcTex) return LastDestTex;
	for (int i=0; i<TextureCount; i++) {
		if (TextureRemaps[i].Src == src) {
			LastSrcTex = src;
			LastDestTex = TextureRemaps[i].Dest;
			return TextureRemaps[i].Dest;
		}
	}
	WWASSERT(0); // uh-oh didn't find the texture, what happend???
	return NULL;
}

// MaterialRemapperClass::Remap_Vertex_Material and Remap_Mesh are owned by
// MaterialRemapMesh.cpp, where their shared body visibility matches retail.

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// ??0MaterialCollectorClass@@QAE@XZ present-unmatched
MaterialCollectorClass::MaterialCollectorClass(void)
{
	LastShader = ShaderClass(0xFFFFFFFF);
	LastMaterial = NULL;
	LastTexture = NULL;
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClassDestructorThunk.cpp
// ??1MaterialCollectorClass@@QAE@XZ present-unmatched
MaterialCollectorClass::~MaterialCollectorClass(void)
{
	Reset();
}

// ?Collect_Materials@MaterialCollectorClass@@QAEXPAVMeshModelClass@@@Z present-unmatched
void MaterialCollectorClass::Collect_Materials(MeshModelClass * mesh)
{
	for (int pass = 0;pass < mesh->Get_Pass_Count(); pass++) {

		// Vertex materials (either single or per vertex)
		if (mesh->Has_Material_Array(pass)) {
			
			for (int vert_index = 0;vert_index < mesh->Get_Vertex_Count(); vert_index++) {
				VertexMaterialClass * mat = mesh->Peek_Material(vert_index,pass);
				Add_Vertex_Material(mat);
			}

		} else {
			VertexMaterialClass * mat = mesh->Get_Single_Material(pass);
			Add_Vertex_Material(mat);
			REF_PTR_RELEASE(mat);
		}
		

		// Shaders (single or per poly...)
		if (mesh->Has_Shader_Array(pass)) {
			for (int poly_index=0; poly_index < mesh->Get_Polygon_Count(); poly_index++) {
				Add_Shader(mesh->Get_Shader(poly_index,pass));
			}
		} else {
			ShaderClass sh = mesh->Get_Single_Shader(pass);
			Add_Shader(sh);
		}
				
		
		// Textures per pass, per stage (either array or single...)
		for (int stage = 0; stage < MeshMatDescClass::MAX_TEX_STAGES; stage++) {

			if (mesh->Has_Texture_Array(pass,stage)) {
				
				for (int poly_index = 0;poly_index < mesh->Get_Polygon_Count(); poly_index++) {
					TextureClass * tex = mesh->Peek_Texture(poly_index,pass,stage);
					Add_Texture(tex);
				}

			} else {
			
				TextureClass * tex = mesh->Peek_Single_Texture(pass,stage);
				Add_Texture(tex);

			}
		}
	}
}

// MaterialCollectorClass::Reset is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorDestructor.cpp (0x0016F460).

// ?Add_Texture@MaterialCollectorClass@@QAEXPAVTextureClass@@@Z present-unmatched
void MaterialCollectorClass::Add_Texture(TextureClass * tex)
{
	if (tex == NULL) return;
	if (tex == LastTexture) return;
	if (Find_Texture(tex) != -1) return;
	Textures.Add(tex);
	tex->Add_Ref();
	LastTexture = tex;
}

void MaterialCollectorClass::Add_Shader(ShaderClass shader)
{
	if (shader == LastShader) return;
	if (Find_Shader(shader) != -1) return;
	Shaders.Add(shader);
	LastShader = shader;
}

void MaterialCollectorClass::Add_Vertex_Material(VertexMaterialClass * vmat)
{
	if (vmat == NULL) return;
	if (vmat == LastMaterial) return;
	if (Find_Vertex_Material(vmat) != -1) return;
	VertexMaterials.Add(vmat);
	vmat->Add_Ref();
	LastMaterial = vmat;
}

// ?Get_Shader_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Shader_Count(void)
{
	return Shaders.Count();
}

// ?Get_Vertex_Material_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Vertex_Material_Count(void)
{
	return VertexMaterials.Count();
}

// ?Get_Texture_Count@MaterialCollectorClass@@QAEHXZ present-unmatched
int MaterialCollectorClass::Get_Texture_Count(void)
{
	return Textures.Count();
}
	
ShaderClass MaterialCollectorClass::Peek_Shader(int i)
{
	return Shaders[i];
}

// ?Peek_Texture@MaterialCollectorClass@@QAEPAVTextureClass@@H@Z present-unmatched
TextureClass * MaterialCollectorClass::Peek_Texture(int i)
{
	return Textures[i];
}

VertexMaterialClass * MaterialCollectorClass::Peek_Vertex_Material(int i)
{
	return VertexMaterials[i];
}

// ?MaterialCollectorClass::Find_Shader present-unmatched
int MaterialCollectorClass::Find_Shader(const ShaderClass & shader)
{
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) {
			return si;
		}
	}
	return -1;
}

// ?Find_Texture@MaterialCollectorClass@@QAEHPAVTextureClass@@@Z present-unmatched
int MaterialCollectorClass::Find_Texture(TextureClass * tex)
{
	for (int ti=0; ti<Textures.Count(); ti++) {
		if (Textures[ti] == tex) {
			return ti;
		}
	}
	return -1;
}

int MaterialCollectorClass::Find_Vertex_Material(VertexMaterialClass * mat)
{
	for (int vi=0; vi<VertexMaterials.Count(); vi++) {
		if (VertexMaterials[vi] == mat) {
			return vi;
		}
	}
	return -1;
}
