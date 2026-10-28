// cl: /Ireference/shims/bfmeshader /FIshader.h /Ireference/shims/meshmatdesclayout /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/meshgeom /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// platformsdk
// dxsdk
// Keep native color-array calls bound to the separately matched D1FBD owner.
#define BFME_MESHMATDESC_COLOR_ARRAY_EXTERNAL
// Link view first: Vector3 operator== (and Length/Normalize/ctor/operator*) stay inline without emitting
// COMDAT copies that disagree with the first copy in link order.
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_vector3_eq_link/vector3_eq_link.h"
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp); this unit had no counterpart under Code/.
// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/meshmdlio.cpp                          $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/18/02 3:09p                                               $*
 *                                                                                             *
 *                    $Revision:: 27                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   MeshModelClass::Load_W3D -- Load a mesh from a W3D file                                   *
 *   MeshModelClass::read_chunks -- read all of the chunks for a mesh                          *
 *   MeshModelClass::read_vertices -- reads the vertex chunk                                   * 
 *   MeshModelClass::read_texcoords -- read in the texture coordinates chunk                   *
 *   MeshModelClass::read_vertex_normals -- reads a vertex normal chunk from the w3d file      * 
 *   MeshModelClass::read_v3_materials -- Reads in version 3 materials.                        *
 *   MeshModelClass::read_triangles -- read the triangles chunk                                *
 *   MeshModelClass::read_per_tri_materials -- read the material indices for each triangle     *
 *   MeshModelClass::read_user_text -- read in the user text chunk                             * 
 *   MeshModelClass::read_vertex_colors -- read in the vertex colors chunk                     * 
 *   MeshModelClass::read_vertex_influences -- read in the vertex influences chunk             * 
 *   MeshModelClass::read_vertex_shade_indices -- read the shade index chunk                   *
 *   MeshModelClass::read_material_info -- read the material info chunk                        *
 *   MeshModelClass::read_shaders -- read the shaders chunk                                    *
 *   MeshModelClass::read_vertex_materials -- read the vertex materials chunk                  *
 *   MeshModelClass::read_textures -- read the textures chunk                                  *
 *   MeshModelClass::read_material_pass -- read a material pass chunk                          *
 *   MeshModelClass::read_vertex_material_ids -- read the vmat ids for a pass                  *
 *   MeshModelClass::read_shader_ids -- read the shader indexes for a pass                     *
 *   MeshModelClass::read_dcg -- read the per-vertex diffuse color for a pass                  *
 *   MeshModelClass::read_dig -- read the per-vertex diffuse illumination for a pass           *
 *   MeshModelClass::read_scg -- read the specular color for a pass                            *
 *   MeshModelClass::read_texture_stage -- read texture stage chunks                           *
 *   MeshModelClass::read_texture_ids -- read the texture ids for a pass,stage                 *
 *   MeshModelClass::read_stage_texcoords -- read the texcoords for a pass,stage               *
 *	  MeshModelClass::read_per_face_texcoord_ids -- read uv indices for given (pass,stage).	  *
 *	  MeshModelClass::read_prelit_material -- read prelit material chunks.							  *
 *   MeshModelClass::read_aabtree -- loads the aabtree chunk                                   *
 *   MeshModelClass::Save -- Save this mesh model!                                             *
 *   MeshLoadContextClass::MeshLoadContextClass -- constructor for MeshLoadContextClass        *
 *   MeshLoadContextClass::~MeshLoadContextClass -- destructor                                 *
 *   MeshLoadContextClass::Get_Texcoord_Array -- returns the texture coordinates array         *
 *   MeshLoadContextClass::Add_Shader -- adds a shader to the array                            *
 *   MeshLoadContextClass::Add_Vertex_Materail -- adds a vertex material                       *
 *   MeshLoadContextClass::Add_Texture -- adds a texture                                       *
 *   MeshLoadContextClass::Add_Legacy_Material -- adds a legacy material                       *
 *   MeshLoadContextClass::Peek_Legacy_Shader -- returns a legacy shader                       *
 *   MeshLoadContextClass::Peek_Legacy_Vertex_Material -- returns a pointer to a legacy vmat   *
 *   MeshLoadContextClass::Peek_Legacy_Texture -- returns a pointer to a texture               *
 *   MeshSaveContextClass::MeshSaveContextClass -- constructor                                 *
 *   MeshSaveContextClass::~MeshSaveContextClass -- destructor                                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <meshmatdesc.h> // establish the BFME2 layout before sibling quoted includes
#include "meshgeometry.h"	// the meshgeom shim has to win the include guard before meshmdl.h reaches the reference copy
#include "meshmdl.h"
#include "aabtree.h"
#include "matinfo.h"
#include "vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "chunkio.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "w3d_util.h"
#include "assetmgr.h"
#include "simplevec.h"
#include "realcrc.h"
#include "dx8wrapper.h"

#include <stdio.h>

#ifdef _UNIX
#include "osdep/osdep.h"
#endif

// bfme link decl-only begin
template <> ShareBufferClass<unsigned short>::~ShareBufferClass();
// bfme link decl-only end

#define MESH_SINGLE_MATERIAL_HACK		0		// (gth) forces all multi-material meshes to use their first material only. (NOT RECOMMENDED, TESTING ONLY!)
#define MESH_FORCE_STATIC_SORT_HACK	0		// (gth) forces all sorting meshes to use static sort level 1 instead.
/**
** MeshLoadContextClass
** This class is just used as a temporary scratchpad while a mesh is being
** loaded.  In some cases, a chunk will be encountered before I have a place
** to plug it into the mesh model, etc.  It is also used to convert from the
** old material format to the new one (detecting duplicated materials in the
** process).
**
** This object will hold refs to all of the unique material objects.  These
** objects will later be transferred into the MaterialInfo for the mesh and it
** will own the refs for the mesh.  The load context object is destroyed once
** loading is complete...
*/
class MeshLoadContextClass : public W3DMPO
{
	W3DMPO_GLUE(MeshLoadContextClass)
private:
	MeshLoadContextClass(void);
	~MeshLoadContextClass(void);
	
	W3dTexCoordStruct *		Get_Texcoord_Array(void);

	int							Add_Shader(ShaderClass shader);
	int							Add_Vertex_Material(VertexMaterialClass * vmat);
	int							Add_Texture(TextureClass* tex);

	ShaderClass					Peek_Shader(int index)											{ return Shaders[index]; }
	VertexMaterialClass *	Peek_Vertex_Material(int index)								{ return VertexMaterials[index]; }
	TextureClass *				Peek_Texture(int index)											{ return Textures[index]; }
	
	int							Shader_Count(void)												{ return Shaders.Count(); }
	int							Vertex_Material_Count(void)									{ return VertexMaterials.Count(); }
	int							Texture_Count(void)												{ return Textures.Count(); }

	/*
	** Legacy material support.  
	*/
	void							Add_Legacy_Material(ShaderClass shader,VertexMaterialClass * vmat,TextureClass * tex);
	ShaderClass					Peek_Legacy_Shader(int legacy_material_index);
	VertexMaterialClass *	Peek_Legacy_Vertex_Material(int legacy_material_index);
	TextureClass *				Peek_Legacy_Texture(int legacy_material_index);

	/*
	** Redundant UV detection support.  The context provides a temporary buffer to
	** load the uv coordinates into.
	*/
	Vector2 *					Get_Temporary_UV_Array(int elementcount);


	/*
	** Currently, the only tool that creates DIG chunks is the lightmap tool.  Since DX8 support
	** for linking the emissive material color to an array seems poor, We're just going to multiply
	** the DIG array into the DCG array (or make it the DCG array).  Now, to properly support the
	** "alternate material set", we have to know whether we've already encountered a DIG chunk so
	** these flags provide that functionality. 
	*/
	void							Notify_Loaded_DIG_Chunk(bool onoff = true)				{ LoadedDIG = onoff; }
	bool							Already_Loaded_DIG(void)										{ return LoadedDIG; }

private:

	struct LegacyMaterialClass
	{
		LegacyMaterialClass(void) : VertexMaterialIdx(0),ShaderIdx(0),TextureIdx(0)	{ }
		~LegacyMaterialClass(void)	{ }		
		void		Set_Name(const char * name) { Name=name; }
		
		StringClass Name;
		int		VertexMaterialIdx;
		int		ShaderIdx;
		int		TextureIdx;
	};
	
	
	W3dMeshHeader3Struct		Header;
	W3dTexCoordStruct *		TexCoords;
	W3dMaterialInfoStruct	MatInfo;

	uint32						PrelitChunkID;

	int							CurPass;
	int							CurTexStage;

	DynamicVectorClass < LegacyMaterialClass * >		LegacyMaterials;
	DynamicVectorClass < ShaderClass >					Shaders;
	DynamicVectorClass < VertexMaterialClass * >		VertexMaterials;
	DynamicVectorClass < unsigned long >				VertexMaterialCrcs;
	DynamicVectorClass < TextureClass * >				Textures;			

	/*
	** Alternate material data.  Any alternate material data will be loaded into 
	** this MeshMatDescClass object.  When loading is finished, an alternate MeshMatDescClass 
	** will be allocated in the mesh model.  This MeshMatDescClass will be initialized to be
	** identical to the default MeshMatDescClass and then any data contained in this
	** MeshMatDescClass will replace the relevant arrays.
	*/
	MeshMatDescClass											AlternateMatDesc;

	SimpleVecClass<Vector2>									TempUVArray;

	/*
	** Record when we load the DIG chunk
	*/
	bool															LoadedDIG;

	friend class MeshClass;
	friend class MeshModelClass;
};


/*
** MeshSaveContextClass
** This class is used to pass information between the saving code in a mesh
*/
class MeshSaveContextClass
{
public:
	MeshSaveContextClass(void);
	~MeshSaveContextClass(void);

	int								CurPass;
	int								CurStage;
	MaterialCollectorClass		Materials;
};


/***********************************************************************************************
 * MeshModelClass::Load_W3D -- Load a mesh from a W3D file                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/16/99    GTH : Created.                                                                 *
 *=============================================================================================*/


/***********************************************************************************************
 * MeshModelClass::read_chunks -- read all of the chunks for a mesh                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/16/99    GTH : Created.                                                                 *
 *=============================================================================================*/


// MeshModelClass::read_texcoords: BFME's bool-returning reader is the row in MeshModelReadTexcoords.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).

/***********************************************************************************************
 * MeshModelClass::read_v3_materials -- Reads in version 3 materials.                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/2/98     GTH : Created.                                                                 *
 *   2/16/99    GTH : Moved into MeshModelClass                                                *
 *=============================================================================================*/


// MeshModelClass::read_per_tri_materials: BFME's bool-returning reader is the row in MeshModelLegacyMaterials.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_vertex_colors: BFME's bool-returning reader is the row in MeshModelReadVertexColors.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


/***********************************************************************************************
 * MeshModelClass::read_material_info -- read the material info chunk                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/16/99    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshModelClass::read_material_info present-unmatched
WW3DErrorType MeshModelClass::read_material_info(ChunkLoadClass & cload,MeshLoadContextClass * context)
{
	if (cload.Read(&(context->MatInfo),sizeof(W3dMaterialInfoStruct)) != sizeof(W3dMaterialInfoStruct)) {
		return WW3D_ERROR_LOAD_FAILED;
	}
	Set_Pass_Count(context->MatInfo.PassCount);
	return WW3D_ERROR_OK;
}


// MeshModelClass::read_shaders: BFME's bool-returning reader is the row in MeshModelReadShaders.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_vertex_materials: BFME's bool-returning reader is the row in MeshModelReadVertexMaterials.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_textures: BFME's bool-returning reader is the row in MeshModelReadTextures.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_material_pass: BFME's bool-returning reader is the row in MeshModelReadMaterialPass.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_vertex_material_ids: BFME's bool-returning reader is the row in MeshModelReadVertexMaterialIds.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_shader_ids: BFME's bool-returning reader is the row in MeshModelReadShaderIds.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


/***********************************************************************************************
 * MeshModelClass::read_dcg -- read the per-vertex diffuse color for a pass                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/16/99    GTH : Created.                                                                 *
 *   9/1/2000   gth : Added alternate material desc support                                    *
 *   2/9/2001   gth : converted to handle dx8 limitations                                      *
 *=============================================================================================*/
WW3DErrorType MeshModelClass::read_dcg(ChunkLoadClass & cload,MeshLoadContextClass * context)
{
	/*
	** Determine whether this chunk should be read into the default or alternate material description
	*/
	MeshMatDescClass * matdesc = DefMatDesc;
	if (DefMatDesc->Get_DCG_Source(context->CurPass) != VertexMaterialClass::MATERIAL) {
		matdesc = &(context->AlternateMatDesc);
	}

	/*
	** The W3D file format supports arbitrary vertex color arrays for each pass; however since
	** our conversion to hardware T&L, we only support two unique color arrays.  So here is 
	** what is happening in this function:
	**
	** 1 - If this is the first diffuse color array we've encountered, load the values.
	** 2 - Otherwise, if we are in PRELIT_VERTEX mode, put the alpha from this array into the color array.
	** 3 - Always set the DCG source for this pass to the array.
	**
	** Our tools *currently* will only generate two color arrays in the case where one of them
	** is being used for alpha and the other is used for precomputed vertex lighting...  This will
	** break if our tools change.  The file format isn't restricting you from defining something
	** we can't render right now...
	*/
	if (matdesc->Has_Color_Array(0) == false) {
		W3dRGBAStruct color;
		unsigned * dcg = matdesc->Get_Color_Array(0);

		for (int i=0; i<Get_Vertex_Count(); i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col;
			W3dUtilityClass::Convert_Color(color,&col);
			dcg[i]=DX8Wrapper::Convert_Color(col);
		}
	} else if (context->PrelitChunkID==W3D_CHUNK_PRELIT_VERTEX) {
		
		W3dRGBAStruct color;
		unsigned * dcg = matdesc->Get_Color_Array(0);

		for (int i=0; i<Get_Vertex_Count(); i++) {
			cload.Read(&color,sizeof(color));
			Vector4 col;
			col=DX8Wrapper::Convert_Color(dcg[i]);
			col.W = float(color.A)/255.0f;
			dcg[i]=DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->Set_DCG_Source(context->CurPass,VertexMaterialClass::COLOR1);

	return WW3D_ERROR_OK;
}


// MeshModelClass::read_dig: BFME's bool-returning reader is the row in MeshModelReadDig.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


/***********************************************************************************************
 * MeshModelClass::read_scg -- read the specular color for a pass                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/16/99    GTH : Created.                                                                 *
 *   9/1/2000   gth : Added alternate material desc support                                    *
 *   2/9/2001   gth : new dx8 code no longer supports this chunk                               *
 *=============================================================================================*/
// ?MeshModelClass::read_scg present-unmatched
WW3DErrorType MeshModelClass::read_scg(ChunkLoadClass & cload,MeshLoadContextClass * context)
{
	return WW3D_ERROR_OK;
}


// MeshModelClass::read_texture_stage: BFME's bool-returning reader is the row in MeshModelReadTextureStage.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_texture_ids: BFME's bool-returning reader is the row in MeshModelReadTextureIds.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_stage_texcoords: BFME's bool-returning reader is the row in MeshModelReadTexcoords.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).

	
// MeshModelClass::read_per_face_texcoord_ids: BFME's bool-returning reader is the row in MeshModelVertexColors.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


// MeshModelClass::read_prelit_material: BFME's bool-returning reader is the row in MeshModelReadPrelitMaterial.cpp;
// Zero Hour's WW3DErrorType copy is not retail's and was dropped (it called ZH-only APIs).


/***********************************************************************************************
 * MeshModelClass::post_process -- post loading, perform any processing on this model.			  *			
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/02/00   IML : Created.                                                                 *
 *   7/13/2001  hy : Added static sort postprocessing                                          *
 *=============================================================================================*/
// MeshModelClass::post_process: defined in MeshModelPostProcess.cpp (its row's unit).

inline void MeshModelClass::post_process_fog(void)
{
	// If two pass...
	if (DefMatDesc->Get_Pass_Count() == 2) {

		// If single shader on both passes...
		if (!DefMatDesc->ShaderArray[0] && !DefMatDesc->ShaderArray[1]) {

			ShaderClass &shader0 = DefMatDesc->Shader [0];
			ShaderClass &shader1 = DefMatDesc->Shader [1];

			// Analyze the mesh to determine if it is the emissive map effect and if it is, fix it up appropriately.
			bool emissive_map_effect = DefMatDesc->PassCount == 2 &&
												shader0.Get_Texturing() == ShaderClass::TEXTURING_DISABLE &&
												shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
												shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
												shader0.Get_Primary_Gradient() == ShaderClass::GRADIENT_MODULATE &&
												shader0.Get_Secondary_Gradient() == ShaderClass::SECONDARY_GRADIENT_DISABLE &&
												shader1.Get_Texturing() == ShaderClass::TEXTURING_ENABLE &&
												shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_SRC_ALPHA &&
												shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_COLOR;

			if (emissive_map_effect) {

				// Change the shader/texture setting into an equivalent one which will enable setting fog
				// correctly: Note that we are setting up pass 0 to have a texture now.
				shader0.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
				shader1.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
				shader0.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				shader1.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);

				// Copy pass 1 texture/texture array to pass 0.
				REF_PTR_SET (DefMatDesc->Texture[0][0], DefMatDesc->Texture [1][0]);
				if (DefMatDesc->TextureArray [1][0]) {
					if (!DefMatDesc->TextureArray [0][0]) {
						DefMatDesc->TextureArray [0][0] = NEW_REF (TexBufferClass, (PolyCount, "MeshModelClass::DefMatDesc::TextureArray"));
						for (int i = 0; i < PolyCount; i++) {
							DefMatDesc->TextureArray [0][0]->Set_Element (i, DefMatDesc->TextureArray [1][0]->Peek_Element (i));
						}
					}
				}

				// Make pass 0 point to the same UV array as pass 1. If pass 1 has a vertex material
				// array, we only take the first one for determining UV source. The UV source is
				// used to set the UV source of all the vertex materials in pass 0.
				int uv_source = 0;
				if (DefMatDesc->MaterialArray[1]) {
					uv_source = DefMatDesc->MaterialArray[1]->Peek_Element(0)->Get_UV_Source(0);
				} else {
					DefMatDesc->Material[1]->Get_UV_Source(0);
				}
				if (DefMatDesc->MaterialArray[0]) {
					for (int i = 0; i < VertexCount; i++) {
						DefMatDesc->MaterialArray[0]->Peek_Element(i)->Set_UV_Source(0, uv_source);
					}
				} else {
					DefMatDesc->Material[0]->Set_UV_Source(0, uv_source);
				}

				return;
			}
				
			// Analyze the mesh to determine if it is the shiny mask effect and if it is, fix it up appropriately.
			bool shiny_mask_effect = shader0.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											 shader0.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ZERO &&
											 shader1.Get_Src_Blend_Func() == ShaderClass::SRCBLEND_ONE &&
											(shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_ALPHA ||
											 shader1.Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);

			if (shiny_mask_effect) {
				shader0.Set_Fog_Func(ShaderClass::FOG_SCALE_FRAGMENT);
				shader1.Set_Fog_Func(ShaderClass::FOG_ENABLE);
				return;
			}
		}
	}
		
	// Mesh is not one of the special two-pass combinations. Apply a per-pass generic fix-up.
	for (int pass = 0; pass < DefMatDesc->PassCount; pass++) {
		DefMatDesc->Shader [pass].Enable_Fog (Get_Name());
		if (DefMatDesc->ShaderArray [pass]) {
			for (int tri = 0; tri < DefMatDesc->ShaderArray [pass]->Get_Count(); tri++) {
				DefMatDesc->ShaderArray [pass]->Get_Element (tri).Enable_Fog (Get_Name());
			}
		}
	}
}

// MeshModelClass::get_sort_flags(int): defined in MeshModelClassGetSortFlagsPass.cpp (its row's unit).

unsigned int MeshModelClass::get_sort_flags(void) const
{
	unsigned int flags = 0;
	for (int pass = 0; pass < Get_Pass_Count(); pass++) {
		flags |= get_sort_flags(pass);
	}
	return flags;
}

void MeshModelClass::compute_static_sort_levels(void)
{
	enum StaticSortCategoryBitFieldType
	{
		SSCAT_OPAQUE_BF		= (1 << ShaderClass::SSCAT_OPAQUE),
		SSCAT_ALPHA_TEST_BF	= (1 << ShaderClass::SSCAT_ALPHA_TEST),
		SSCAT_ADDITIVE_BF		= (1 << ShaderClass::SSCAT_ADDITIVE),
		SSCAT_SCREEN_BF		= (1 << ShaderClass::SSCAT_SCREEN),
		SSCAT_OTHER_BF			= (1 << ShaderClass::SSCAT_OTHER)
	};

	if (get_sort_flags(0) == SSCAT_OPAQUE_BF) {
		SortLevel = SORT_LEVEL_NONE;
		return;
	}

	switch (get_sort_flags())
	{
	case (SSCAT_OPAQUE_BF | SSCAT_ALPHA_TEST_BF):
		SortLevel = SORT_LEVEL_NONE;
		break;

	case SSCAT_ADDITIVE_BF:
		SortLevel = SORT_LEVEL_BIN3;
		break;

	case SSCAT_SCREEN_BF:
		SortLevel = SORT_LEVEL_BIN2;
		break;
		
	default:
		SortLevel = SORT_LEVEL_BIN1;
		break;
	};
}

// ?MeshModelClass::modify_for_overbright present-unmatched
void MeshModelClass::modify_for_overbright(void)
{
	// Iterate over all passes
	int pass_cnt = Get_Pass_Count();
	for (int pass_idx = 0; pass_idx < pass_cnt; pass_idx++) {

		// First do single shader
		ShaderClass shader = Get_Single_Shader(pass_idx);
		if (shader.Get_Primary_Gradient() == ShaderClass::GRADIENT_MODULATE) {
			shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE2X);
			Set_Single_Shader(shader, pass_idx);
		}

		// Now do all other shaders
		if (Has_Shader_Array(pass_idx)) {
			int p_cnt = Get_Polygon_Count();
			for (int p_idx = 0; p_idx < p_cnt; p_idx++) {
				shader = Get_Shader(p_idx, pass_idx);
				if (shader.Get_Primary_Gradient() == ShaderClass::GRADIENT_MODULATE) {
					shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE2X);
					Set_Shader(p_idx, shader, pass_idx);
				}
			}
		}
	}

}

// MeshModelClass::install_materials: defined in MeshModelInstallMaterials.cpp (its row's unit).
// MeshModelClass::install_alternate_material_desc: defined in MeshModelInstallAlternate.cpp (its row's unit).

/***********************************************************************************************
 * MeshLoadContextClass::MeshLoadContextClass -- constructor for MeshLoadContextClass          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// MeshLoadContextClass constructor: use the verified body in MeshLoadContextCtor.cpp.


/***********************************************************************************************
 * MeshLoadContextClass::~MeshLoadContextClass -- destructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// MeshLoadContextClass destructor: use the verified body in MeshLoadContextCtor.cpp.


/***********************************************************************************************
 * MeshLoadContextClass::Get_Texcoord_Array -- returns the texture coordinates array           *
 *                                                                                             *
 * This function mainly exists to support the obsolete version 3.0 w3d files                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
W3dTexCoordStruct * MeshLoadContextClass::Get_Texcoord_Array(void)
{
	if (TexCoords == NULL) {
		TexCoords = W3DNEWARRAY W3dTexCoordStruct[Header.NumVertices];
	}
	return TexCoords;
}


/***********************************************************************************************
 * MeshLoadContextClass::Add_Shader -- adds a shader to the array                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
inline int MeshLoadContextClass::Add_Shader(ShaderClass shader)
{ 
	int index = Shaders.Count();
	Shaders.Add(shader); 
	return index;
}


/***********************************************************************************************
 * MeshLoadContextClass::Add_Vertex_Materail -- adds a vertex material                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
inline int MeshLoadContextClass::Add_Vertex_Material(VertexMaterialClass * vmat)
{ 
	WWASSERT(vmat != NULL);
	vmat->Add_Ref();
	int index = VertexMaterials.Count();
	VertexMaterials.Add(vmat); 
	return index;
}


/***********************************************************************************************
 * MeshLoadContextClass::Add_Texture -- adds a texture                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
int MeshLoadContextClass::Add_Texture(TextureClass * tex)							
{ 
	WWASSERT(tex != NULL);
	tex->Add_Ref();
	int index = Textures.Count();
	Textures.Add(tex); 
	return index;
}


/***********************************************************************************************
 * MeshLoadContextClass::Add_Legacy_Material -- adds a legacy material                         *
 *                                                                                             *
 * This function will check to see if the parameters of any of the parts of the material are   *
 * duplicated.  Only unique shaders/vertexmaterials will be actually added.                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
void MeshLoadContextClass::Add_Legacy_Material(ShaderClass shader,VertexMaterialClass * vmat,TextureClass * tex)
{
	// create a new legacy material
	LegacyMaterialClass * mat = W3DNEW LegacyMaterialClass;

	// add the shader if it is unique
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) break;
	}
	if (si == Shaders.Count()) {
		mat->ShaderIdx = Add_Shader(shader);
	} else {
		mat->ShaderIdx = si;
	}

	// add the vertex material if it is unique
	if (vmat == NULL) {
		mat->VertexMaterialIdx = -1;
	} else {
		unsigned long crc = vmat->Get_CRC();	
		for (int vi=0; vi<VertexMaterialCrcs.Count(); vi++) {
			if (VertexMaterialCrcs[vi] == crc) break;
		}
		if (vi == VertexMaterials.Count()) {
			mat->VertexMaterialIdx = Add_Vertex_Material(vmat);
			VertexMaterialCrcs.Add(crc);
			WWASSERT(VertexMaterialCrcs.Count() == VertexMaterials.Count());
		} else {
			mat->VertexMaterialIdx = vi;
		}
	}

	// add the texture if it is unique
	if (tex == NULL) {
		mat->TextureIdx = -1;
	} else {
		for (int ti=0; ti<Textures.Count(); ti++) {
			if (Textures[ti] == tex) break;
			if (_strcmpi(Textures[ti]->Get_Texture_Name(),tex->Get_Texture_Name()) == 0) break;
		}
		if (ti == Textures.Count()) {
			mat->TextureIdx = Add_Texture(tex);
		} else {
			mat->TextureIdx = ti;
		}
	}

	LegacyMaterials.Add(mat);
}


/***********************************************************************************************
 * MeshLoadContextClass::Peek_Legacy_Shader -- returns a legacy shader								  *		
 *                                                                                             *
 * This function does the re-indexing to go from the legacy shader index to the actual shader  *
 * index and then returns that shader                                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
inline ShaderClass MeshLoadContextClass::Peek_Legacy_Shader(int legacy_material_index)
{
	WWASSERT(legacy_material_index >= 0);
	WWASSERT(legacy_material_index < LegacyMaterials.Count());
	int si = LegacyMaterials[legacy_material_index]->ShaderIdx;
	return Peek_Shader(si);
}


/***********************************************************************************************
 * MeshLoadContextClass::Peek_Legacy_Vertex_Material -- returns a pointer to a legacy vertex ma*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
inline VertexMaterialClass * MeshLoadContextClass::Peek_Legacy_Vertex_Material(int legacy_material_index)
{
	WWASSERT(legacy_material_index >= 0);
	WWASSERT(legacy_material_index < LegacyMaterials.Count());
	int vi = LegacyMaterials[legacy_material_index]->VertexMaterialIdx;
	if (vi != -1) {
		return Peek_Vertex_Material(vi);
	} else {
		return NULL;
	}
}


/***********************************************************************************************
 * MeshLoadContextClass::Peek_Legacy_Texture -- returns a pointer to a texture                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
TextureClass * MeshLoadContextClass::Peek_Legacy_Texture(int legacy_material_index)
{
	WWASSERT(legacy_material_index >= 0);
	WWASSERT(legacy_material_index < LegacyMaterials.Count());
	int ti = LegacyMaterials[legacy_material_index]->TextureIdx;
	if (ti != -1) {
		return Peek_Texture(ti);
	} else {
		return NULL;
	}
}


// ?MeshLoadContextClass::Get_Temporary_UV_Array present-unmatched
Vector2 * MeshLoadContextClass::Get_Temporary_UV_Array(int elementcount)
{
	TempUVArray.Uninitialised_Grow(elementcount);
	return &(TempUVArray[0]);
}



/***********************************************************************************************
 * MeshSaveContextClass::MeshSaveContextClass -- constructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
MeshSaveContextClass::MeshSaveContextClass(void) :
	CurPass(0),
	CurStage(0)
{
}


/***********************************************************************************************
 * MeshSaveContextClass::~MeshSaveContextClass -- destructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
MeshSaveContextClass::~MeshSaveContextClass(void)
{
}
