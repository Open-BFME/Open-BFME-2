// cl: /Ireference/shims/bfmeshader /FIshader.h /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "../../../../../reference/shims/meshmatdesclayout/meshmatdesc.h"	// BFME2 MeshMatDescClass layout wins the include guard (TextureArray +0xC8)
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
// bfme link decl-only begin
template <> bool VectorClass<ShaderClass>::Resize(int, ShaderClass const *);
// bfme link decl-only end

// MaterialInfoClass's constructor and destructor are rowed in
// MaterialInfoClassCtor.cpp (0x001708D0) and MaterialInfoDtor.cpp (0x00170130).


// ?Clone@MaterialInfoClass@@QBEPAV1@XZ present-unmatched
MaterialInfoClass * MaterialInfoClass::Clone(void) const
{ 
	return W3DNEW MaterialInfoClass(*this); 
}


// MaterialInfoClass::Get_Texture_Index is rowed with BFME2's body in
// MaterialInfoGetTextureIndex.cpp; the donor copy here was a second definition.

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


// MaterialRemapperClass ctor: rowed in MaterialRemapperClassCtor.cpp

// Owned by MaterialRemapperClassDtor.cpp.


// MaterialRemapperClass::Remap_Vertex_Material and Remap_Mesh are owned by
// MaterialRemapMesh.cpp, where their shared body visibility matches retail.

// MaterialCollectorClass::MaterialCollectorClass is defined with its retail-matched body in
// MaterialCollectorClassCtor.cpp. Its member vectors' constructors are rowed here.
template DynamicVectorClass<ShaderClass>::DynamicVectorClass(unsigned, ShaderClass const *);
template DynamicVectorClass<VertexMaterialClass *>::DynamicVectorClass(unsigned, VertexMaterialClass * const *);
template DynamicVectorClass<TextureClass *>::DynamicVectorClass(unsigned, TextureClass * const *);

// MaterialCollectorClass::~MaterialCollectorClass is defined with its retail-matched body in MaterialCollectorDestructor.cpp.

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorCollectMaterials.cpp

// MaterialCollectorClass::Reset is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorDestructor.cpp (0x0016F460).


inline void MaterialCollectorClass::Add_Shader(ShaderClass shader)
{
	if (shader == LastShader) return;
	if (Find_Shader(shader) != -1) return;
	Shaders.Add(shader);
	LastShader = shader;
}

inline void MaterialCollectorClass::Add_Vertex_Material(VertexMaterialClass * vmat)
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


VertexMaterialClass * MaterialCollectorClass::Peek_Vertex_Material(int i)
{
	return VertexMaterials[i];
}

// ?MaterialCollectorClass::Find_Shader present-unmatched
inline int MaterialCollectorClass::Find_Shader(const ShaderClass & shader)
{
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) {
			return si;
		}
	}
	return -1;
}


inline int MaterialCollectorClass::Find_Vertex_Material(VertexMaterialClass * mat)
{
	for (int vi=0; vi<VertexMaterials.Count(); vi++) {
		if (VertexMaterials[vi] == mat) {
			return vi;
		}
	}
	return -1;
}
