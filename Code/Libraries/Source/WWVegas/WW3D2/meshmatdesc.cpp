// cl: /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmelight /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
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
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/meshmatdesc.cpp                        $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 1/18/02 8:03p                                               $*
 *                                                                                             *
 *                    $Revision:: 28                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Retail disagrees with the WW3D2-local vertmaterial.h about VertexMaterialClass
// on two points that Post_Load_Process is the first body to feel:
//   - it is 0x6C, not 0x70. Set_Ambient_Color_Source (0x00921160) writes
//     [ecx+0x10], so the local header's extra `_bfme_vmat_v0` dword ahead of
//     MaterialOld is not there; the reference copy, which omits it, is right.
//   - it has no pooled operator new. The allocation here is a bare
//     `push 0x6c; call ??2@YAPAXI@Z`, not the getClassMemoryPool() +
//     allocateFromW3DMemPool pair W3DMPO_GLUE generates.
// The local header is shared by 17 other TUs, so take the reference layout by
// angle-bracket include (its VERTMATERIAL_H guard then swallows the local copy
// meshmatdesc.h pulls in) and drop the glue for the length of that include only.
#include "always.h"
#pragma push_macro("W3DMPO_GLUE")
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include <vertmaterial.h>
#pragma pop_macro("W3DMPO_GLUE")

#include "meshmatdesc.h"
#include "texture.h"
#include "vertmaterial.h"
#include "realcrc.h"
#include	"dx8wrapper.h"
#include "dx8caps.h"
#include "meshmdl.h"

// The BFME2 ShaderClass specialization is defined in sharebuf_shader_copy_ctor.cpp.
template<> ShareBufferClass<ShaderClass>::~ShareBufferClass(void);

/**************************************************************************************************
**
**
** MatBufferClass Implementation
**
**
**************************************************************************************************/
MatBufferClass::MatBufferClass(const MatBufferClass & that) :
	ShareBufferClass<VertexMaterialClass *>(that)
{
	// add a reference for each pointer that was copied...
	// BFME: retail reads through RawBuffer here rather than Array; both hold the
	// same freshly-allocated pointer right after the base copy ctor runs (Alignment
	// is always 0 for this instantiation, so Array == RawBuffer), but the compiler
	// chose the RawBuffer member for this loop specifically.
	for (int i=0; i<Count; i++) {
		if (RawBuffer[i]) {
			RawBuffer[i]->Add_Ref();
		}
	}
}

// MatBufferClass::~MatBufferClass: defined in MatBufferCleanup.cpp (its row's unit).

// ShareBufferClass keeps its Array at +0x08 in BFME and at +0x0C here -- the same
// four bytes the MeshMatDescClass comment above records as an empty W3DMPO base
// this hierarchy does not have. The body is otherwise the REF_PTR_SET expansion
// unchanged: add-ref the incoming material, release the outgoing one through
// vtable slot 0 when its count reaches zero, then store.
struct BfmeMatBufferArray
{
	unsigned char m_unreconstructed_000[ 8 ];
	VertexMaterialClass **m_array;				///< retail this+0x08
};

void MatBufferClass::Set_Element(int index,VertexMaterialClass * mat)
{
	REF_PTR_SET(((BfmeMatBufferArray *)this)->m_array[index],mat);
}

// ?Get_Element@MatBufferClass@@ present-unmatched
VertexMaterialClass * MatBufferClass::Get_Element(int index)
{
	if (Array[index]) {
		Array[index]->Add_Ref();
	}
	return Array[index];
}

// MatBufferClass::Peek_Element: defined in MeshMatDescBufferAccessors.cpp (its row's unit).


/**************************************************************************************************
**
**
** TexBufferClass Implementation
**
**
**************************************************************************************************/
// TexBufferClass::TexBufferClass: defined in TexBufferClassCopyCtor.cpp (its row's unit).

// ??1TexBufferClass@@UAE@XZ present-unmatched
inline TexBufferClass::~TexBufferClass(void)
{
	for (int i=0;i<Count;i++) {
		REF_PTR_RELEASE(Array[i]);
	}
}

// ?Set_Element@TexBufferClass@@QAEXHPAVTextureClass@@@Z present-unmatched
void TexBufferClass::Set_Element(int index,TextureClass * tex)
{
	REF_PTR_SET(Array[index],tex);
}

// ?Get_Element@TexBufferClass@@QAEPAVTextureClass@@H@Z present-unmatched
TextureClass * TexBufferClass::Get_Element(int index)
{
	if (Array[index]) {
		Array[index]->Add_Ref();
	}
	return Array[index];
}

// ?Peek_Element@TexBufferClass@@ present-unmatched
TextureClass * TexBufferClass::Peek_Element(int index)
{
	return Array[index];
}


/**************************************************************************************************
**
**
** UVBufferClass Implementation
**
**
**************************************************************************************************/
UVBufferClass::UVBufferClass(const UVBufferClass & that) :
	ShareBufferClass<Vector2>(that)
{
	CRC = that.CRC;
}

bool UVBufferClass::operator == (const UVBufferClass & that)
{
	// NOTE: this only works if you've properly called Update_CRC after filling the array
	return (CRC == that.CRC);
}

// ?Is_Equal_To@UVBufferClass@@ present-unmatched
bool UVBufferClass::Is_Equal_To(const UVBufferClass & that)
{
	// NOTE: this only works if you've properly called Update_CRC after filling the array
	return (CRC == that.CRC);
}


inline void UVBufferClass::Update_CRC(void)
{
	CRC = CRC_Memory((unsigned char *)Get_Array(),Get_Count() * sizeof(Vector2));
}



/**************************************************************************************************
**
**
** MeshMatDescClass Implementation
**
**
**************************************************************************************************/
// ?NullShader@MeshMatDescClass@@2VShaderClass@@A present-unmatched
ShaderClass MeshMatDescClass::NullShader(0);	// Used to mark no shader data

// MeshMatDescClass default constructor is recovered in MeshMatDescDefaultCtor.cpp.

// MeshMatDescClass copy constructor is recovered in MeshMatDescDefaultCtor.cpp.

// MeshMatDescClass::operator = is recovered in MeshMatDescDefaultCtor.cpp.

// ??1MeshMatDescClass@@UAE@XZ present-unmatched
MeshMatDescClass::~MeshMatDescClass(void)
{
	Reset(0,0,0);
}

// ?Get_Single_Texture@MeshMatDescClass@@QBEPAVTextureClass@@HH@Z present-unmatched
TextureClass * MeshMatDescClass::Get_Single_Texture(int pass,int stage) const
{
	if (Texture[pass][stage]) {
		Texture[pass][stage]->Add_Ref();
	}
	return Texture[pass][stage];
}

// MeshMatDescClass::Reset is recovered in MeshMatDescReset.cpp.

// MeshMatDescClass::Init_Alternate is recovered in MeshMatDescDefaultCtor.cpp.

// MeshMatDescClass::Is_Empty is recovered in MeshMatDescDefaultCtor.cpp.

void MeshMatDescClass::Set_Single_Material(VertexMaterialClass * vmat,int pass)
{
	REF_PTR_SET(Material[pass],vmat);
}

// ?Set_Single_Texture@MeshMatDescClass@@QAEXPAVTextureClass@@HH@Z present-unmatched
void MeshMatDescClass::Set_Single_Texture(TextureClass * tex,int pass,int stage)
{
	REF_PTR_SET(Texture[pass][stage],tex);
}

void MeshMatDescClass::Set_Single_Shader(ShaderClass shader,int pass)
{
	Shader[pass] = shader;
}

void MeshMatDescClass::Set_Material(int vidx,VertexMaterialClass * vmat,int pass)
{
	MatBufferClass * mats = Get_Material_Array(pass,true);
	mats->Set_Element(vidx,vmat);
}

void MeshMatDescClass::Set_Shader(int pidx,ShaderClass shader,int pass)
{
	ShaderClass * shaders = Get_Shader_Array(pass,true);
	shaders[pidx] = shader;
}

// ?Set_Texture@MeshMatDescClass@@QAEXHPAVTextureClass@@HH@Z present-unmatched
void MeshMatDescClass::Set_Texture(int pidx,TextureClass * tex,int pass,int stage)
{
	TexBufferClass * textures = Get_Texture_Array(pass,stage,true);
	textures->Set_Element(pidx,tex);
}

// ?Get_Material@MeshMatDescClass@@QBEPAVVertexMaterialClass@@HH@Z present-unmatched
VertexMaterialClass * MeshMatDescClass::Get_Material(int vidx,int pass) const
{
	if (MaterialArray[pass]) {

		return MaterialArray[pass]->Get_Element(vidx);

	} else if (Material[pass] != NULL) {

		Material[pass]->Add_Ref();
		return Material[pass];

	}
	return NULL;
}

ShaderClass	MeshMatDescClass::Get_Shader(int pidx,int pass) const
{
	if (ShaderArray[pass]) {
		return ShaderArray[pass]->Get_Element(pidx);
	}
	return Shader[pass];
}

// ?Get_Texture@MeshMatDescClass@@QBEPAVTextureClass@@HHH@Z present-unmatched
TextureClass * MeshMatDescClass::Get_Texture(int pidx,int pass,int stage) const
{
	if (TextureArray[pass][stage]) {

		return TextureArray[pass][stage]->Get_Element(pidx);

	} else if (Texture[pass][stage] != NULL) {

		Texture[pass][stage]->Add_Ref();
		return Texture[pass][stage];

	}
	return NULL;
}

VertexMaterialClass * MeshMatDescClass::Peek_Material(int vidx,int pass) const
{
	if (MaterialArray[pass]) {
		// BFME reads ShareBufferClass::RawBuffer (+0x08) here rather than Array
		// (+0x0C) -- the same choice the MatBufferClass copy ctor above makes.
		// It is not an inlined Peek_Element: that body still stands at 0x006BCB60
		// reading [ecx+0x0c]. RawBuffer is protected and MeshMatDescClass is not a
		// subclass, so reach it by its verified offset (ctor 0x005F3BE0 stores the
		// raw allocation at +0x08, the aligned view at +0x0C; this instantiation is
		// always unaligned, so the two hold the same pointer).
		return (*(VertexMaterialClass ***)((char *)MaterialArray[pass] + 0x08))[vidx];
	}
	return Material[pass];
}

// ?Peek_Texture@MeshMatDescClass@@QBEPAVTextureClass@@HHH@Z present-unmatched
TextureClass * MeshMatDescClass::Peek_Texture(int pidx,int pass,int stage) const
{
	if (TextureArray[pass][stage]) {
		return TextureArray[pass][stage]->Peek_Element(pidx);
	}
	return Texture[pass][stage];
}

TexBufferClass * MeshMatDescClass::Get_Texture_Array(int pass,int stage,bool create)
{
	if (create && TextureArray[pass][stage] == NULL) {
		TextureArray[pass][stage] = NEW_REF(TexBufferClass,(PolyCount, "MeshMatDescClass::TextureArray"));
	}
	return TextureArray[pass][stage];
}

MatBufferClass * MeshMatDescClass::Get_Material_Array(int pass,bool create)
{
	if (create && MaterialArray[pass] == NULL) {
		MaterialArray[pass] = NEW_REF(MatBufferClass,(VertexCount, "MeshMatDescClass::MaterialArray"));
	}
	return MaterialArray[pass];
}

ShaderClass * MeshMatDescClass::Get_Shader_Array(int pass,bool create)
{
	if (create && ShaderArray[pass] == NULL) {
		ShaderArray[pass] = NEW_REF(ShareBufferClass<ShaderClass>,(PolyCount, "MeshMatDescClass::ShaderArray"));
		ShaderArray[pass]->Clear();
	}
	if (ShaderArray[pass]) {
		return ShaderArray[pass]->Get_Array();
	}
	return NULL;
}

void MeshMatDescClass::Make_UV_Array_Unique(int pass,int stage)
{
	int uvindex = UVSource[pass][stage];
	if (UV[uvindex]->Num_Refs() > 1) {
		UVBufferClass * unique_uv = NEW_REF(UVBufferClass,(*UV[uvindex]));
		UV[uvindex]->Release_Ref();
		UV[uvindex] = unique_uv;
	}
}

void MeshMatDescClass::Make_Color_Array_Unique(int array)
{
	if ((ColorArray[array] != NULL) && (ColorArray[array]->Num_Refs() > 1)) {
		ShareBufferClass<unsigned> * unique_color_array = NEW_REF(ShareBufferClass<unsigned>,(*ColorArray[array]));
		ColorArray[array]->Release_Ref();
		ColorArray[array] = unique_color_array;
	}
}

// MeshMatDescClass::Install_UV_Array: defined in MeshMatDescInstallUVArray.cpp (its row's unit).


// BFME2 adds a pass skip for the two per-pass buffers at +0xB8 and +0x108 and
// keeps the lighting flag inverted (retail zero-initialises it and sets it when
// PassCount != 1). Convert_Color comes from the bfmelight dx8wrapper.h, whose
// col=0 initialiser retail stores before each inline x87 conversion.
void MeshMatDescClass::Post_Load_Process(bool lighting_enabled,MeshModelClass * parent)
{
	/*
	** Configure all vertex materials to source the uv coordinates and colors from the correct arrays
	** Pre-multiply the vertex color arrays.
	*/
	bool keep_lighting=false;
	for (int pass=0; pass<PassCount; pass++) {

		if ((OpaquePassBuffers[pass] != NULL) || (OpaqueTailBuffers[pass] != NULL)) continue;

		/*
		** If this pass doesn't have a vertex material, create one
		*/
		if ((Material[pass] == NULL) && (MaterialArray[pass] == NULL)) {
			Material[pass] = NEW_REF(VertexMaterialClass,());
		}

		/*
		** Configure the materials to source the uv coordinates and colors
		*/
		if (Material[pass] != NULL) {

			Configure_Material(Material[pass],pass,lighting_enabled);

		} else {
			VertexMaterialClass * prev_mtl = NULL;
			VertexMaterialClass * mtl = Peek_Material(pass,0);

			for (int vidx=0; vidx<VertexCount; vidx++) {

				mtl = Peek_Material(vidx,pass);
				if ((mtl != prev_mtl) && (mtl != NULL)) {
					Configure_Material(mtl,pass,lighting_enabled);
					prev_mtl = mtl;
				}
			}
		}

		// Analyze material array types and apply hacks for supporting SR-lighting pipeline if possible.

		if (!ColorArray[0] && !ColorArray[1]) continue;	// If no color arrays, we don't have a problem

		Vector3 single_diffuse(0.0f,0.0f,0.0f);
		Vector3 single_ambient(0.0f,0.0f,0.0f);
		Vector3 single_emissive(0.0f,0.0f,0.0f);
		float single_opacity=1.0f;
		bool single_diffuse_used=true;
		bool single_ambient_used=true;
		bool single_emissive_used=true;
		bool single_opacity_used=true;
		bool diffuse_used=false;
		bool ambient_used=false;
		bool emissive_used=false;
		bool opacity_used=false;

		Vector3 mtl_diffuse;
		Vector3 mtl_ambient;
		Vector3 mtl_emissive;
		float mtl_opacity = 1.0f;

		VertexMaterialClass * prev_mtl = NULL;
		VertexMaterialClass * mtl = Peek_Material(0, pass);
		if (mtl) {
			mtl->Get_Diffuse(&single_diffuse);
			single_opacity = mtl->Get_Opacity();
			mtl->Get_Ambient(&single_ambient);
			mtl->Get_Emissive(&single_emissive);

			if (single_diffuse.X || single_diffuse.Y || single_diffuse.Z) diffuse_used=true;
			if (single_ambient.X || single_ambient.Y || single_ambient.Z) ambient_used=true;
			if (single_emissive.X || single_emissive.Y || single_emissive.Z) emissive_used=true;
			if (single_opacity!=1.0f) opacity_used=true;
		}

		for (int vidx=0; vidx<VertexCount; vidx++) {
			mtl = Peek_Material(vidx,pass);
			if (mtl != prev_mtl) {
				prev_mtl = mtl;
				mtl->Get_Diffuse(&mtl_diffuse);
				mtl_opacity = mtl->Get_Opacity();
				mtl->Get_Ambient(&mtl_ambient);
				mtl->Get_Emissive(&mtl_emissive);
			}

			if (mtl_diffuse.X!=single_diffuse.X || mtl_diffuse.Y!=single_diffuse.Y || mtl_diffuse.Z!=single_diffuse.Z) {
				single_diffuse_used=false;
			}
			if (mtl_ambient.X!=single_ambient.X || mtl_ambient.Y!=single_ambient.Y || mtl_ambient.Z!=single_ambient.Z) {
				single_ambient_used=false;
			}
			if (mtl_emissive.X!=single_emissive.X || mtl_emissive.Y!=single_emissive.Y || mtl_emissive.Z!=single_emissive.Z) {
				single_emissive_used=false;
			}
			if (mtl_opacity!=single_opacity) {
				single_opacity_used=false;
			}

			if (mtl_diffuse.X || mtl_diffuse.Y || mtl_diffuse.Z) diffuse_used=true;
			if (mtl_ambient.X || mtl_ambient.Y || mtl_ambient.Z) ambient_used=true;
			if (mtl_emissive.X || mtl_emissive.Y || mtl_emissive.Z) emissive_used=true;
			if (mtl_opacity!=1.0f) opacity_used=true;

		}

		// If both DCG and DIG arrays are submitted, multiply them together to DCG channel
		if ((DCGSource[pass] != VertexMaterialClass::MATERIAL) && (ColorArray[0] != NULL) &&
			 (DIGSource[pass] != VertexMaterialClass::MATERIAL) && (ColorArray[1] != NULL)) {
			unsigned * diffuse_array = ColorArray[0]->Get_Array();
			unsigned * emissive_array = ColorArray[1]->Get_Array();

			for (int vidx=0; vidx<VertexCount; vidx++) {
				Vector4 diffuse=DX8Wrapper::Convert_Color(diffuse_array[vidx]);
				Vector4 emissive=DX8Wrapper::Convert_Color(emissive_array[vidx]);
				diffuse.X *= emissive.X;
				diffuse.Y *= emissive.Y;
				diffuse.Z *= emissive.Z;
				diffuse_array[vidx]=DX8Wrapper::Convert_Color(diffuse);
			}
		}
		DIGSource[pass]=VertexMaterialClass::MATERIAL;	// DIG channel no more

		if ((DCGSource[pass] != VertexMaterialClass::MATERIAL) && (ColorArray[0] != NULL)) {
			unsigned * diffuse_array = ColorArray[0]->Get_Array();
			Vector3 mtl_diffuse;
			float mtl_opacity = 1.0f;

			VertexMaterialClass * prev_mtl = NULL;
			VertexMaterialClass * mtl = Peek_Material(0,pass);

			for (int vidx=0; vidx<VertexCount; vidx++) {

				mtl = Peek_Material(vidx,pass);
				if (mtl != prev_mtl) {
					prev_mtl = mtl;
					mtl->Get_Diffuse(&mtl_diffuse);
					mtl_opacity = mtl->Get_Opacity();
				}

				// If only diffuse is used apply diffuse to color channel and set diffuse source to color 1
				if (diffuse_used && !ambient_used && !emissive_used) {
					Vector4 diffuse=DX8Wrapper::Convert_Color(diffuse_array[vidx]);
					diffuse.X *= mtl_diffuse.X;
					diffuse.Y *= mtl_diffuse.Y;
					diffuse.Z *= mtl_diffuse.Z;
					diffuse.W *= mtl_opacity;
					diffuse_array[vidx]=DX8Wrapper::Convert_Color(diffuse);

					mtl->Set_Ambient_Color_Source(VertexMaterialClass::MATERIAL);
					mtl->Set_Diffuse_Color_Source(VertexMaterialClass::COLOR1);
					mtl->Set_Emissive_Color_Source(VertexMaterialClass::MATERIAL);
				}

				// If diffuse and ambient are used, apply diffuse to color channel and set diffuse
				// and ambient sources to color 1. (this is not completely correct if diffuse and
				// ambient are different but is probably the most reasonable thing to do. Why set
				// diffuse and ambient differently anyway?)
				if (diffuse_used && ambient_used && !emissive_used) {
					Vector4 diffuse=DX8Wrapper::Convert_Color(diffuse_array[vidx]);
					diffuse.X *= mtl_diffuse.X;
					diffuse.Y *= mtl_diffuse.Y;
					diffuse.Z *= mtl_diffuse.Z;
					diffuse.W *= mtl_opacity;
					diffuse_array[vidx]=DX8Wrapper::Convert_Color(diffuse);

					mtl->Set_Ambient_Color_Source(VertexMaterialClass::COLOR1);
					mtl->Set_Diffuse_Color_Source(VertexMaterialClass::COLOR1);
					mtl->Set_Emissive_Color_Source(VertexMaterialClass::MATERIAL);
				}

				// If only ambient is used apply ambient to color channel and set ambient source to color 1
				if (!diffuse_used && ambient_used && !emissive_used) {
					Vector4 diffuse=DX8Wrapper::Convert_Color(diffuse_array[vidx]);
					diffuse.X *= mtl_ambient.X;
					diffuse.Y *= mtl_ambient.Y;
					diffuse.Z *= mtl_ambient.Z;
					diffuse.W *= mtl_opacity;
					diffuse_array[vidx]=DX8Wrapper::Convert_Color(diffuse);

					mtl->Set_Ambient_Color_Source(VertexMaterialClass::COLOR1);
					mtl->Set_Diffuse_Color_Source(VertexMaterialClass::MATERIAL);
					mtl->Set_Emissive_Color_Source(VertexMaterialClass::MATERIAL);
				}

				// If only emissive is used apply emissive to color channel, set diffuse source to color 1, and turn off lighting
				if (!diffuse_used && !ambient_used && emissive_used) {
					Vector4 diffuse=DX8Wrapper::Convert_Color(diffuse_array[vidx]);
					diffuse.X *= mtl_emissive.X;
					diffuse.Y *= mtl_emissive.Y;
					diffuse.Z *= mtl_emissive.Z;
					diffuse.W *= mtl_opacity;
					diffuse_array[vidx]=DX8Wrapper::Convert_Color(diffuse);

					mtl->Set_Ambient_Color_Source(VertexMaterialClass::MATERIAL);
					mtl->Set_Diffuse_Color_Source(VertexMaterialClass::COLOR1);
					mtl->Set_Emissive_Color_Source(VertexMaterialClass::MATERIAL);
//					mtl->Set_Lighting(false);
				}
				else {
					if (PassCount!=1) {
						keep_lighting=true;		// Lighting can only be set to false if ALL passes and ALL materials are requesting it
					}
				}
			}
		}
	}


	/*
	** HACK: Kill BUMPENV passes on hardware that doesn't support BUMPENV
	** HACK: Set lighting to false on all passes if all passes are of type NO DIFFUSE, NO AMBIENT, YES EMISSIVE
	*/
	for (pass=0; pass<PassCount; pass++) {
		bool kill_pass = false;

		/*
		// HY: Earth and beyond uses a different fallback from Renegade with regards to bump environment maps
		// we keep the pass but change it to an unbumped environment
		if ( (Shader[pass].Get_Primary_Gradient() == ShaderClass::GRADIENT_BUMPENVMAP) &&
			  (!DX8Wrapper::Is_Initted() || DX8Wrapper::Get_Current_Caps()->Support_Bump_Envmap() == false) )
		{
			kill_pass = true;
		}

		if ( (Shader[pass].Get_Primary_Gradient() == ShaderClass::GRADIENT_BUMPENVMAPLUMINANCE) &&
			  (!DX8Wrapper::Is_Initted() || DX8Wrapper::Get_Current_Caps()->Support_Bump_Envmap_Luminance() == false) )
		{
			kill_pass = true;
		}
		*/

		if (kill_pass) {
			if (Material[pass] != NULL) {
				Material[pass]->Set_Ambient(0,0,0);
				Material[pass]->Set_Diffuse(0,0,0);
				Material[pass]->Set_Emissive(0,0,0);
				Material[pass]->Set_Specular(0,0,0);
			}

			Shader[pass].Set_Texturing(ShaderClass::TEXTURING_DISABLE);
			Shader[pass].Set_Post_Detail_Color_Func(ShaderClass::DETAILCOLOR_DISABLE);
			Shader[pass].Set_Post_Detail_Alpha_Func(ShaderClass::DETAILALPHA_DISABLE);
		}
		// Set lighting to false if requested in all passes...
		else if (!keep_lighting) {
			Vector3 single_diffuse(0.0f,0.0f,0.0f);
			Vector3 single_ambient(0.0f,0.0f,0.0f);
			Vector3 single_emissive(0.0f,0.0f,0.0f);
			bool diffuse_used=false;
			bool ambient_used=false;
			bool emissive_used=false;

			Vector3 mtl_diffuse;
			Vector3 mtl_ambient;
			Vector3 mtl_emissive;

			VertexMaterialClass * prev_mtl = NULL;
			VertexMaterialClass * mtl = Peek_Material(0, pass);
			if (mtl) {
				mtl->Get_Diffuse(&single_diffuse);
				mtl->Get_Ambient(&single_ambient);
				mtl->Get_Emissive(&single_emissive);

				if (single_diffuse.X || single_diffuse.Y || single_diffuse.Z) diffuse_used=true;
				if (single_ambient.X || single_ambient.Y || single_ambient.Z) ambient_used=true;
				if (single_emissive.X || single_emissive.Y || single_emissive.Z) emissive_used=true;
			}

			for (int vidx=0; vidx<VertexCount; vidx++) {
				mtl = Peek_Material(vidx,pass);
				if (mtl != prev_mtl) {
					prev_mtl = mtl;
					mtl->Get_Diffuse(&mtl_diffuse);
					mtl->Get_Ambient(&mtl_ambient);
					mtl->Get_Emissive(&mtl_emissive);
				}

				if (mtl_diffuse.X || mtl_diffuse.Y || mtl_diffuse.Z) diffuse_used=true;
				if (mtl_ambient.X || mtl_ambient.Y || mtl_ambient.Z) ambient_used=true;
				if (mtl_emissive.X || mtl_emissive.Y || mtl_emissive.Z) emissive_used=true;
			}

			if ((DCGSource[pass] != VertexMaterialClass::MATERIAL) && (ColorArray[0] != NULL)) {
				VertexMaterialClass * prev_mtl = NULL;
				VertexMaterialClass * mtl = Peek_Material(0,pass);
				for (int vidx=0; vidx<VertexCount; vidx++) {
					mtl = Peek_Material(vidx,pass);
					if (mtl != prev_mtl) {
						prev_mtl = mtl;
						// If only emissive is used apply emissive to color channel, set diffuse source to color 1, and turn off lighting
						if (!diffuse_used && !ambient_used && emissive_used) {
							mtl->Set_Lighting(false);
						}
					}
				}
			}
		}
	}	
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp
struct Bfme2MeshMatDescConfigureView {
	char PaddingToUV[0x30];
	int UVSource[2][2];
	char PaddingToColorSources[0x18];
	VertexMaterialClass::ColorSourceType DCGSource[4];
	VertexMaterialClass::ColorSourceType DIGSource[4];
};

void MeshMatDescClass::Configure_Material(VertexMaterialClass * mtl,int pass,bool lighting_enabled)
{
	mtl->Set_Diffuse_Color_Source(reinterpret_cast<Bfme2MeshMatDescConfigureView *>(this)->DCGSource[pass]);
	mtl->Set_Emissive_Color_Source(reinterpret_cast<Bfme2MeshMatDescConfigureView *>(this)->DIGSource[pass]);

	mtl->Set_Lighting(lighting_enabled);

	for (int stage=0; stage<MAX_TEX_STAGES; stage++) {
		int src = reinterpret_cast<Bfme2MeshMatDescConfigureView *>(this)->UVSource[pass][stage];
		if (src == -1) {
			src = 0;
		}
		mtl->Set_UV_Source(stage,src);
	}
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/MeshMatDescClass_Do_Mappers_Need_Normals_Thunk.cpp
// Retail DX8Caps carries 0x5c more bytes ahead of the NPatches support flag
// than this TU's headers (retail tests caps+0x13b, headers place
// SupportNPatches at +0xdf). TU-local view in this TU's Bfme2*View idiom.
struct Bfme2DX8CapsNPatchesView {
	char PaddingToNPatches[0x13b];
	bool SupportNPatches;
};

bool MeshMatDescClass::Do_Mappers_Need_Normals(void)
{
	if (DX8Wrapper::Is_Initted() && reinterpret_cast<const Bfme2DX8CapsNPatchesView *>(DX8Wrapper::Get_Current_Caps())->SupportNPatches && WW3D::Get_NPatches_Level()>1) return true;

	for (int pass=0; pass<PassCount; pass++) {
		/*
		** Check the materials on this pass to see if any have mappers which require normals
		*/
		if (Material[pass] != NULL) {

			if (Material[pass]->Do_Mappers_Need_Normals()) return true;

		} else {
			VertexMaterialClass * prev_mtl = NULL;
			VertexMaterialClass * mtl = Peek_Material(pass,0);

			for (int vidx=0; vidx<VertexCount; vidx++) {

				mtl = Peek_Material(vidx,pass);
				if ((mtl != prev_mtl) && (mtl != NULL)) {

					if (mtl->Do_Mappers_Need_Normals()) return true;
					prev_mtl = mtl;
				}
			}
		}
	}

	return false;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeUVBufferClassInlineAnchor@@YAXPAVUVBufferClass@@@Z absent-from-retail
void _bfmeUVBufferClassInlineAnchor(UVBufferClass *p)
{
    p->Update_CRC();
}
#pragma inline_depth()
