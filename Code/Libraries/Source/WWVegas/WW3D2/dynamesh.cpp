// cl: /Ireference/shims/dynamesh_material /Ireference/shims/bfmestages /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Bind the UV accessor to the separately matched native D1F40 owner.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define BFME_MESHMATDESC_UV_ARRAY_EXTERNAL
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// stlport
// Use the verified out-of-line material getter; the ordinary /O2 header copy
// differs from retail and otherwise wins COMDAT selection for new consumers.
// readable body of ?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
// Link view: Matrix4(Vector4 x4), Transpose and the Matrix3D overloads stay inline without emitting
// non-/O1 copies that lose to retail's owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_zh_rows_link.h"
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

/*************************************************************************** 
 ***    C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S     *** 
 *************************************************************************** 
 *                                                                         * 
 *                 Project Name : Commando                                 * 
 *                                                                         * 
 *                     $Archive:: /Commando/Code/ww3d2/dynamesh.cpp       $* 
 *                                                                         * 
 *                      $Author:: Greg_h                                  $* 
 *                                                                         * 
 *                     $Modtime:: 12/03/01 4:50p                          $* 
 *                                                                         * 
 *                    $Revision:: 25                                      $* 
 *                                                                         * 
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// ZH meshgeometry.h's Get_Flag and Set_Flag use Flags at +0x14; BFME2's MeshGeometryClass keeps it at
// +0x18 (retail 0x000D1AA1, 0x001494B0). Every use here is inlined, so
// TU-local names keep this unit's copies, first in link order, from displacing retail's.
#define Get_Flag Get_Flag_Zh
#define Set_Flag Set_Flag_Zh
#include "matinfo.h" // load the declaration-only TU shim before sibling includes
#include "dx8wrapper.h" // the bfmestages shim has to win the include guard over the ZH sibling
// Keep the native shader accessor at 0x00143370: its Shader array is
// +0x98, whereas this legacy donor view places it at +0x94.
#define BFME_MESHMATDESC_SINGLE_SHADER_EXTERNAL
// Preserve this TU's ZH layout while binding color-array calls to the native owner.
#include "../../../../../reference/shims/dynamesh_color_link/meshmatdesc.h"
// Retail's RenderObjClass::Set_Force_Visible is BFME's out-of-line body
// (0x0013B720, RenderObjSetForceVisible.cpp) and Set_Additive the /O1 one at
// 0x0006CF8C (RenderObjAccessors.cpp). The ZH rendobj.h this header pulls in
// defines both inline, and the vtables this unit emits would make those copies
// the first ones in link order; the macros leave the virtuals declared only and
// move the ZH bodies to unreferenced non-virtual members.
#define Set_Force_Visible(onoff) Set_Force_Visible(onoff); void Zh_Inline_Set_Force_Visible(onoff)
#define Set_Additive(onoff) Set_Additive(onoff); void Zh_Inline_Set_Additive(onoff)
#include "dynamesh.h"
#undef Set_Additive
#undef Set_Force_Visible
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "rinfo.h"
#include "camera.h"
#include "dx8fvf.h"


// ?Render@DynamicMeshModel@@ present-unmatched
void DynamicMeshModel::Render(RenderInfoClass & rinfo)
{
	// Process texture reductions:
//	MatInfo->Process_Texture_Reduction();

	unsigned buffer_type=(Get_Flag(MeshGeometryClass::SORT)&& WW3D::Is_Sorting_Enabled()) ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8;

	/*
	** Write the vertex data to the vertex buffer. We assume the FVF contains positions, normals,
	** one texture channel, and the diffuse color channel (color0). If it does not contain all
	** these components, the code will fail.
	*/
	DynamicVBAccessClass dynamic_vb(buffer_type,dynamic_fvf_type,DynamicMeshVNum);
	const FVFInfoClass &fvf_info = dynamic_vb.FVF_Info();
	
	{ // scope for lock

		DynamicVBAccessClass::WriteLockClass lock(&dynamic_vb);
		unsigned char *vertices = (unsigned char*)lock.Get_Formatted_Vertex_Array();			
		const Vector3 *locs = Get_Vertex_Array();
		const Vector3 *normals = Get_Vertex_Normal_Array();
		const Vector2 *uvs = MatDesc->Get_UV_Array_By_Index(0, false);
		const Vector2 *uv1s = MatDesc->Get_UV_Array_By_Index(1, false);
		const unsigned *colors = MatDesc->Get_Color_Array(0, false);
		const static Vector3 default_normal(0.0f, 0.0f, 0.0f);
		const static Vector2 default_uv(0.0f, 0.0f);
		const unsigned int default_color = 0xFFFFFFFF;
		for (int i=0; i < DynamicMeshVNum; i++)
		{
			*(Vector3 *)(vertices + fvf_info.Get_Location_Offset()) = locs[i];
			*(Vector3 *)(vertices + fvf_info.Get_Normal_Offset()) = normals[i];
			if (uvs) {
				*(Vector2 *)(vertices + fvf_info.Get_Tex_Offset(0)) = uvs[i];
			} else {
				*(Vector2 *)(vertices + fvf_info.Get_Tex_Offset(0)) = default_uv;
			}
			if (uv1s) {
				*(Vector2 *)(vertices + fvf_info.Get_Tex_Offset(1)) = uv1s[i];
			} else {
				*(Vector2 *)(vertices + fvf_info.Get_Tex_Offset(1)) = default_uv;
			}

			if (colors) {
				*(unsigned int *)(vertices + fvf_info.Get_Diffuse_Offset()) = colors[i];
			} else {
				*(unsigned int *)(vertices + fvf_info.Get_Diffuse_Offset()) = default_color;
			}
			vertices += fvf_info.Get_FVF_Size();
		}			

	} // end scope for lock

	/*
	** Write index data to index buffers
	*/
	DynamicIBAccessClass dynamic_ib(buffer_type,DynamicMeshPNum * 3);
	const TriIndex *tris = Get_Polygon_Array();

	{ // scope for lock

		DynamicIBAccessClass::WriteLockClass lock(&dynamic_ib);
		unsigned short * indices = lock.Get_Index_Array();
		for (int i=0; i < DynamicMeshPNum; i++)
		{
			indices[i*3 + 0] = (unsigned short)tris[i][0];
			indices[i*3 + 1] = (unsigned short)tris[i][1];
			indices[i*3 + 2] = (unsigned short)tris[i][2];
		}

	} // end scope for lock

	/*
	** Set vertex and index buffers
	*/
	DX8Wrapper::Set_Vertex_Buffer(dynamic_vb);
	DX8Wrapper::Set_Index_Buffer(dynamic_ib,0);

	/*
	** Draw dynamesh, one pass at a time
	*/
	unsigned int pass_count = Get_Pass_Count();
	for (unsigned int pass = 0; pass < pass_count; pass++) {

		/*
		** Set current render states (texture, vertex material, shader). Scan triangles until one
		** of these changes, and then draw.
		*/

		// The vertex index range used
		unsigned short min_vert_idx = DynamicMeshVNum - 1;
		unsigned short max_vert_idx = 0;
		unsigned short start_tri_idx = 0;
		unsigned short cur_tri_idx = 0;

		bool done = false;
		bool texture_changed = false;
		bool texture1_changed = false;
		bool material_changed = false;
		bool shader_changed = false;

		TextureClass **texture_array0 = NULL;
		TexBufferClass * tex_buf = MatDesc->Get_Texture_Array(pass, 0, false);
		if (tex_buf) {
			texture_array0 = tex_buf->Get_Array();
		} else {
			texture_array0 = NULL;
		}

		TextureClass **texture_array1 = NULL;
		TexBufferClass * tex_buf1 = MatDesc->Get_Texture_Array(pass, 1, false);
		if (tex_buf1) {
			texture_array1 = tex_buf1->Get_Array();
		} else {
			texture_array1 = NULL;
		}
		
		VertexMaterialClass **material_array = NULL;
		MatBufferClass * mat_buf = MatDesc->Get_Material_Array(pass, false);
		if (mat_buf) {
			material_array = mat_buf->Get_Array();
		} else {
			material_array = NULL;
		}
		ShaderClass *shader_array = MatDesc->Get_Shader_Array(pass, false);

		// Set the DX8 state to the first triangle's state
		if (texture_array0) {
			DX8Wrapper::Set_Texture(0,texture_array0[0]);
		} else {
			DX8Wrapper::Set_Texture(0,MatDesc->Peek_Single_Texture(pass, 0));
		}

		if (texture_array1) {
			DX8Wrapper::Set_Texture(1,texture_array1[0]);
		} else {
			DX8Wrapper::Set_Texture(1,MatDesc->Peek_Single_Texture(pass, 1));
		}

		if (material_array) {
			DX8Wrapper::Set_Material(material_array[tris[0].I]);
		} else {
			DX8Wrapper::Set_Material(MatDesc->Peek_Single_Material(pass));
		}
		if (shader_array) {
			DX8Wrapper::Set_Shader(shader_array[0]);
		} else {
			DX8Wrapper::Set_Shader(MatDesc->Get_Single_Shader(pass));
		}

		SphereClass sphere(Vector3(0.0f,0.0f,0.0f),0.0f);
		Get_Bounding_Sphere(&sphere); 

		// If no texture, shader or material arrays for this pass just draw and go to next pass
		if (!texture_array0 && !texture_array1 && !material_array && !shader_array) {
			if (buffer_type==BUFFER_TYPE_DYNAMIC_SORTING) {
				SortingRendererClass::Insert_Triangles(sphere,0, DynamicMeshPNum, 0, DynamicMeshVNum);
			}
			else {
				DX8Wrapper::Draw_Triangles(0, DynamicMeshPNum, 0, DynamicMeshVNum);
			}
			continue;
		}

		while (!done) {

			// Add vertex indices of tri[cur_tri_idx] to min_vert_idx, max_vert_idx
			const TriIndex &tri = tris[cur_tri_idx];
			unsigned short min_idx = (unsigned short)MIN(MIN(tri.I, tri.J), tri.K);
			unsigned short max_idx = (unsigned short)MAX(MAX(tri.I, tri.J), tri.K);
			min_vert_idx = MIN(min_vert_idx, min_idx);
			max_vert_idx = MAX(max_vert_idx, max_idx);

			// Check the next triangle to see if the current run has ended.
			unsigned short next_tri_idx = cur_tri_idx + 1;
			done = next_tri_idx >= DynamicMeshPNum;
			if (done) {
				texture_changed = false;
				texture1_changed = false;
				material_changed = false;
				shader_changed = false;
			} else {
				texture_changed = texture_array0 && texture_array0[cur_tri_idx] != texture_array0[next_tri_idx];
				texture1_changed = texture_array1 && texture_array1[cur_tri_idx] != texture_array1[next_tri_idx];
				material_changed = material_array && material_array[tris[cur_tri_idx].I] != material_array[tris[next_tri_idx].I];
				shader_changed = shader_array && shader_array[cur_tri_idx] != shader_array[next_tri_idx];
			}

			// If run ends (mesh ends or state changes) draw, reset indices, set state for next run.
			if (done || texture_changed || material_changed || shader_changed) {
				if (buffer_type==BUFFER_TYPE_DYNAMIC_SORTING) {
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/SortingRendererInsertTrianglesThunk.cpp
					SortingRendererClass::Insert_Triangles(
						sphere,
						(start_tri_idx * 3),
						(1 + cur_tri_idx - start_tri_idx), 
						min_vert_idx, 
						1 + max_vert_idx - min_vert_idx);
				}
				else {
					DX8Wrapper::Draw_Triangles(
						(start_tri_idx * 3),
						(1 + cur_tri_idx - start_tri_idx), 
						min_vert_idx, 
						1 + max_vert_idx - min_vert_idx);
				}
				start_tri_idx = next_tri_idx;
				min_vert_idx = DynamicMeshVNum - 1;
				max_vert_idx = 0;
				if (texture_changed) DX8Wrapper::Set_Texture(0,texture_array0[next_tri_idx]);
				if (texture1_changed) DX8Wrapper::Set_Texture(1,texture_array1[next_tri_idx]);
				if (material_changed) DX8Wrapper::Set_Material(material_array[tris[next_tri_idx].I]);
				if (shader_changed) DX8Wrapper::Set_Shader(shader_array[next_tri_idx]);
			}

			cur_tri_idx = next_tri_idx;

		}	// while (!done)

	}	// for (pass)

}

/******************************************************************
**
** DynamicMeshClass
**
*******************************************************************/
// ??0DynamicMeshClass@@ present-unmatched
DynamicMeshClass::DynamicMeshClass(int max_poly, int max_vert) :
	Model(NULL),
	PolyCount(0),
	VertCount(0),
	TriVertexCount(0),
	FanVertex(0),
	TriMode(TRI_MODE_STRIPS),
	SortLevel(SORT_LEVEL_NONE)
{
	int pass = MAX_PASSES;
	while (pass--) {
		MultiTexture[pass] = false;
		TextureIdx[pass] = -1;

		MultiVertexMaterial[pass] = false;
		VertexMaterialIdx[pass] = -1;
	}

	for (int color_array_index = 0; color_array_index < MAX_COLOR_ARRAYS; color_array_index++) {
		MultiVertexColor[color_array_index] = false;
		CurVertexColor[color_array_index].Set(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Model = NEW_REF(DynamicMeshModel, (max_poly, max_vert));
}


// ?Set_Vertex_Material@DynamicMeshClass@@ present-unmatched
int DynamicMeshClass::Set_Vertex_Material(VertexMaterialClass *material, bool dont_search, int pass)
{
	// Check if same as the last vertex material
	if (Peek_Material_Info()->Vertex_Material_Count() && (VertexMaterialIdx[pass] != -1) && Peek_Material_Info()->Peek_Vertex_Material(VertexMaterialIdx[pass]) == material) {
		return VertexMaterialIdx[pass];
	}

	// if there are vertex materials in the list then we may have just jumped
	// to becoming a multi-vertex-material object.  Take care of that here.
	if ((!MultiVertexMaterial[pass]) && Peek_Material_Info()->Vertex_Material_Count() && (VertexMaterialIdx[pass] != -1) && Peek_Material_Info()->Peek_Vertex_Material(VertexMaterialIdx[pass]) != material) {

		// allocate the array of per-vertex vertex material overrides
		VertexMaterialClass *mat = Peek_Material_Info()->Get_Vertex_Material(VertexMaterialIdx[pass]);
		Model->Initialize_Material_Array(pass, mat);
		mat->Release_Ref();

		// flag that we need to write the per -vertex vertex material override array
		MultiVertexMaterial[pass] = true;
	}

	// add the material to the material info class if we cant find it in the 
	// list.  if we are not supposed to search the list for it then just add
	// it.
	if (!dont_search) {
		for (int lp = 0, found = 0; lp < Peek_Material_Info()->Vertex_Material_Count(); lp ++) {
			VertexMaterialClass *mat = Peek_Material_Info()->Get_Vertex_Material(lp);
			if (material == mat) {
				VertexMaterialIdx[pass] = lp;
				found = true;
				mat->Release_Ref();
				break;
			}
			mat->Release_Ref();
		}
		if (!found) {
			Peek_Material_Info()->Add_Vertex_Material(material);
			VertexMaterialIdx[pass] = Peek_Material_Info()->Vertex_Material_Count() - 1;
		}
	} else {
		Peek_Material_Info()->Add_Vertex_Material(material);
		VertexMaterialIdx[pass] = Peek_Material_Info()->Vertex_Material_Count() - 1;
	}

	if (!MultiVertexMaterial[pass]) {
		Model->Set_Single_Material(Peek_Material_Info()->Peek_Vertex_Material(VertexMaterialIdx[pass]), pass);
	}
	return(VertexMaterialIdx[pass]);
}

/*
**
*/
// Remap locations to match a screen
// For moving a vertex after the DynaMesh has already been created.
// Set position

