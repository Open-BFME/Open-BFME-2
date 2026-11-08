// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
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
#include "Vector.H"
#include "vector3.h"
// Retail keeps one VectorClass<Vector3>::Resize (0x000F0BF1); this unit calls it.
template <> bool VectorClass<Vector3>::Resize(int newsize, Vector3 const * array);
// Declaring the dtor only stops cl synthesizing this unit's /G7 copy of the
// scalar deleting destructor; retail's is 0x000F1CF7.
template <> VectorClass<Vector3>::~VectorClass();
// Native 0x000F1C7A is supplied by FXShaderRendererSkin.cpp.
template <> DynamicVectorClass<Vector3>::DynamicVectorClass(unsigned, Vector3 const *);
template <> bool DynamicVectorClass<Vector3>::Resize(int, Vector3 const *);
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
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

/* $Header: /Commando/Code/ww3d2/mesh.cpp 69    1/19/02 1:01p Greg_h $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D engine                                       * 
 *                                                                                             * 
 *                    File Name : MESH.CPP                                                     * 
 *                                                                                             * 
 *                   Programmer : Greg Hjelstrom                                               * 
 *                                                                                             * 
 *                   Start Date : 06/11/97                                                     * 
 *                                                                                             * 
 *                  Last Update : June 12, 1997 [GH]                                           * 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   MeshClass::MeshClass -- Constructor for MeshClass                                         *
 *   MeshClass::MeshClass -- Copy Constructor for MeshClass                                    *
 *	  MeshClass::operator == -- assignment operator for MeshClass                               *
 *   MeshClass::~MeshClass -- destructor                                                       *
 *   MeshClass::Contains -- Determines whether mesh contains a (worldspace) point.             *
 *   MeshClass::Free -- Releases all memory/assets in use by this mesh                         *
 *   MeshClass::Clone -- Creates a clone of this mesh                                          *
 *   MeshClass::Get_Name -- returns the name of the mesh                                       *
 *   MeshClass::Set_Name -- sets the name of this mesh                                         *
 *   MeshClass::Get_W3D_Flags -- access to the W3D flags                                       *
 *   MeshClass::Get_User_Text -- access to the text buffer                                     *
 *   MeshClass::Scale -- Scales the mesh                                                       *
 *   MeshClass::Scale -- Scales the mesh                                                       *
 *   MeshClass::Init -- Init the mesh from a MeshBuilder object                                *
 *   MeshClass::Load -- creates a mesh out of a mesh chunk in a .w3d file                      * 
 *   MeshClass::Cast_Ray -- compute a ray intersection with this mesh                          *
 *   MeshClass::Cast_AABox -- cast an AABox against this mesh                                  *
 *   MeshClass::Cast_OBBox -- Cast an obbox against this mesh                                  *
 *   MeshClass::Intersect_AABox -- test for intersection with given AABox                      *
 *   MeshClass::Intersect_OBBox -- test for intersection with the given OBBox                  *
 *   MeshClass::Generate_Culling_Tree -- Generates a hierarchical culling tree for the mesh    *
 *   MeshClass::Direct_Load -- read the w3d file directly into this mesh object                *
 *   MeshClass::read_chunks -- read all of the chunks from the .wtm file                       * 
 *	  MeshClass::read_vertices -- reads the vertex chunk                                        * 
 *   MeshClass::read_texcoords -- read in the texture coordinates chunk                        *
 *   MeshClass::install_texture_coordinates -- installs the given u-v's in each channel that is*
 *   MeshClass::read_vertex_normals -- reads a surrender normal chunk from the wtm file        * 
 *   MeshClass::read_v3_materials -- Reads in version 3 materials.                             *
 *   MeshClass::read_map -- Reads definition of a texture map from the file                    *
 *   MeshClass::read_triangles -- read the triangles chunk                                     *
 *   MeshClass::read_per_tri_materials -- read the material indices for each triangle          *
 *   MeshClass::read_user_text -- read in the user text chunk                                  * 
 *   MeshClass::read_vertex_colors -- read in the vertex colors chunk                          * 
 *   MeshClass::read_vertex_influences -- read in the vertex influences chunk                  * 
 *   MeshClass::Get_Material_Info -- returns a pointer to the material info                    *
 *   MeshClass::Create_Decal -- creates a decal on this mesh                                   *
 *   MeshClass::Delete_Decal -- removes a decal from this mesh                                 *
 *   MeshClass::Get_Num_Polys -- returns the number of polys (tris) in this mesh               *
 *   MeshClass::Render -- renders this mesh                                                    *
 *   MeshClass::Special_Render -- special render function for meshes                           *
 *   MeshClass::update_skin -- deforms the mesh                                                *
 *   MeshClass::clone_materials -- clone the materials for this mesh                           *
 *   MeshClass::install_materials -- transfers the materials into the mesh                     *
 *   MeshClass::Get_Model -- user access to the mesh model                                     *
 *   MeshClass::Get_Obj_Space_Bounding_Sphere -- returns obj-space bounding sphere             *
 *   MeshClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box               *
 *   MeshClass::Get_Deformed_Vertices -- Gets the deformed vertices for a skin                 *
 *   MeshClass::Get_Deformed_Vertices -- Gets the deformed vertices for a skin                 *
 *   MeshClass::Render_Material_Pass -- Render a procedural material pass for this mesh        *
 *   MeshClass::Replace_VertexMaterial -- Replaces existing vertex material with a new one. Wi *
 *   MeshClass::Make_Unique -- Makes mesh unique in the renderer, but still shares system ram  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "mesh.h"
#include <assert.h>
#include <string.h>
#include "w3d_file.h"
#include "assetmgr.h"
#include "w3derr.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "shader.h"
#include "matinfo.h"
#include "htree.h"
#include "meshbuild.h"
#include "tri.h"
#include "aaplane.h"
#include "aabtree.h"
#include "chunkio.h"
#include "w3d_util.h"
#include "meshmdl.h"
#include "meshgeometry.h"
#include "ww3d.h"
#include "camera.h"
#include "texture.h"
class CameraClass;
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "decalmsh.h"
#include "decalsys.h"
#include "dx8polygonrenderer.h"
#include "dx8indexbuffer.h"
#include "dx8renderer.h"
#include "visrasterizer.h"
#include "wwmemlog.h"
#include "dx8rendererdebugger.h"
#include <stdio.h>
#include "wwprofile.h"
// bfme link decl-only begin
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
// Retail keeps the nothrow-delete[] copies 0x001A7C80 and 0x001A7DE0; this unit's would carry an EH frame.
template <> bool SimpleVecClass<Vector4>::Resize(int);
template <> SimpleDynVecClass<Vector4>::~SimpleDynVecClass();
template <> bool SimpleVecClass<Vector4>::Uninitialised_Grow(int);
// bfme link decl-only end


bool MeshClass::Legacy_Meshes_Fogged = true;
static SimpleDynVecClass<Vector4> temp_apt;	// retail 0x001AC680 loads the Vector4 tables 0x7D71C8/0x7D71D4

/*
** This #define causes the collision code to always recompute the triangle normals rather
** than using the ones in the model. 
** TODO: ensure that the models have unit normals and start re-using them again or write
** collision code to handle non-unit normals!
*/
#if (OPTIMIZE_PLANEEQ_RAM)
#define COMPUTE_NORMALS
#endif




/***********************************************************************************************
 * MeshClass::MeshClass -- Constructor for MeshClass                                           *
 *                                                                                             *
 *    Initializes an empty mesh class                                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassLifetime.cpp (retail 0x001495A0); it needs the BFME2
// MeshClass layout, which the shared header used here does not carry.


/***********************************************************************************************
 * MeshClass::MeshClass -- Copy Constructor for MeshClass                                      *
 *                                                                                             *
 *    Creates a mesh which is a copy of the given mesh                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
// BFME2's body is in MeshClassLifetime.cpp (retail 0x00149680); it needs the BFME2
// MeshClass layout, which the shared header used here does not carry.


/***********************************************************************************************
 * operator == -- assignment operator for MeshClass                                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// MeshClass::operator= defined in MeshClassLifetime.cpp


/***********************************************************************************************
 * MeshClass::~MeshClass -- destructor                                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassLifetime.cpp (retail 0x0014A5B0); it needs the BFME2
// MeshClass layout, which the shared header used here does not carry.


/***********************************************************************************************
 * MeshClass::Contains -- Determines whether mesh contains a (worldspace) point.               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS: Assumes mesh is a closed manifold - results are undefined otherwise               *
 *           This function will NOT work for skins                                             *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   8/30/00     NH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Contains present-unmatched
bool MeshClass::Contains(const Vector3 &point)
{
	// Transform point to object space and pass on to model
	Vector3 obj_point;
	Matrix3D::Inverse_Transform_Vector(Transform, point, &obj_point);
	return Model->Contains(obj_point);
}


/***********************************************************************************************
 * MeshClass::Free -- Releases all memory/assets in use by this mesh                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Free present-unmatched
void MeshClass::Free(void)
{
	REF_PTR_RELEASE(Model);
	REF_PTR_RELEASE(DecalMesh);
}


/***********************************************************************************************
 * MeshClass::Clone -- Creates a clone of this mesh                                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassLifetime.cpp (retail 0x001498E0); it needs the BFME2
// MeshClass layout, which the shared header used here does not carry.


/***********************************************************************************************
 * MeshClass::Get_Name -- returns the name of the mesh                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/15/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Get_Name present-unmatched
const char * MeshClass::Get_Name(void) const
{ 
	return Model->Get_Name(); 
}


/***********************************************************************************************
 * MeshClass::Set_Name -- sets the name of this mesh                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/9/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Set_Name present-unmatched
void MeshClass::Set_Name(const char * name)
{
	Model->Set_Name(name);
}

/***********************************************************************************************
 * MeshClass::Get_W3D_Flags -- access to the W3D flags                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/15/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Get_W3D_Flags present-unmatched
uint32 MeshClass::Get_W3D_Flags(void)
{ 
	return Model->W3dAttributes; 
}


/***********************************************************************************************
 * MeshClass::Get_User_Text -- access to the text buffer                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/15/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Get_User_Text present-unmatched
const char * MeshClass::Get_User_Text(void) const
{ 
	return Model->Get_User_Text(); 
}		


/***********************************************************************************************
 * MeshClass::Get_Material_Info -- returns a pointer to the material info                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/20/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassCollision.cpp (retail 0x00149980); it needs the BFME2
// MeshModelClass layout (MatInfo at +0x98), which the shared header does not carry.


/***********************************************************************************************
 * MeshClass::Get_Model -- user access to the mesh model                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/4/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Get_Model present-unmatched
inline MeshModelClass * MeshClass::Get_Model(void)
{
	if (Model != NULL) {
		Model->Add_Ref();
	}
	return Model;
}

/***********************************************************************************************
 * MeshClass::Scale -- Scales the mesh                                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
// ?MeshClass::Scale
// ?MeshClass::Scale present-unmatched
void MeshClass::Scale(float scale)
{
	if (scale==1.0f) return;

	Vector3 sc;
	sc.X = sc.Y = sc.Z = scale;
	Make_Unique();
	Model->Make_Geometry_Unique();
	Model->Scale(sc);
	
   Invalidate_Cached_Bounding_Volumes();

   // Now update the object space bounding volumes of this object's container:
   // Retail stores Container at +0x7c and calls Update_Obj_Space_Bounding_Volumes at vtable +0x114.
   RenderObjClass *container = *reinterpret_cast<RenderObjClass **>(reinterpret_cast<char *>(this) + 0x7c);
   if (container) {
      typedef void (__fastcall *UpdateBoundingVolumes)(RenderObjClass *);
      void **vtable = *reinterpret_cast<void ***>(container);
      reinterpret_cast<UpdateBoundingVolumes>(vtable[0x45])(container);
   }
}


/***********************************************************************************************
 * MeshClass::Scale -- Scales the mesh                                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *   12/8/98    GTH : Modified the box scaling to use the non-uniform parameters               *
 *=============================================================================================*/
// ?MeshClass::Scale present-unmatched
void MeshClass::Scale(float scalex, float scaley, float scalez)
{
	// scale the surrender mesh model
	Vector3 sc;
	sc.X = scalex;
	sc.Y = scaley;
	sc.Z = scalez;
	Make_Unique();
	Model->Make_Geometry_Unique();
	Model->Scale(sc);
	
   Invalidate_Cached_Bounding_Volumes();

   // Now update the object space bounding volumes of this object's container:
   // Retail stores Container at +0x7c and calls Update_Obj_Space_Bounding_Volumes at vtable +0x114.
   RenderObjClass *container = *reinterpret_cast<RenderObjClass **>(reinterpret_cast<char *>(this) + 0x7c);
   if (container) {
      typedef void (__fastcall *UpdateBoundingVolumes)(RenderObjClass *);
      void **vtable = *reinterpret_cast<void ***>(container);
      reinterpret_cast<UpdateBoundingVolumes>(vtable[0x45])(container);
   }
}


/***********************************************************************************************
 * MeshClass::Get_Deformed_Vertices -- Gets the deformed vertices for a skin                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/4/2001   gth : Created.                                                                 *
 *=============================================================================================*/
// MeshClass::Get_Deformed_Vertices(Vector3 *, Vector3 *) is defined with its retail-matched body in Rva001499D0Cluster.cpp (0x001499D0).


/***********************************************************************************************
 * MeshClass::Get_Deformed_Vertices -- Gets the deformed vertices for a skin                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/4/2001   gth : Created.                                                                 *
 *=============================================================================================*/
// MeshClass::Get_Deformed_Vertices(Vector3 *) is defined with its retail-matched body in Rva001499D0Cluster.cpp (0x00149A10).

/***********************************************************************************************
 * MeshClass::Create_Decal -- creates a decal on this mesh                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/26/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Create_Decal present-unmatched
void MeshClass::Create_Decal(DecalGeneratorClass * generator, bool unk)
{
	// BFME: DX8 render path stubbed to compile the rest of the TU.
}


/***********************************************************************************************
 * MeshClass::Delete_Decal -- removes a decal from this mesh                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/26/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Delete_Decal present-unmatched
void MeshClass::Delete_Decal(uint32 decal_id)
{
	if (DecalMesh != NULL) {
		DecalMesh->Delete_Decal(decal_id);
	}
}


/***********************************************************************************************
 * MeshClass::Get_Num_Polys -- returns the number of polys (tris) in this mesh                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/6/98     GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassCollision.cpp (retail 0x00149A50); it needs the BFME2
// RenderObjClass view, which the shared header used here does not carry.


/***********************************************************************************************
 * MeshClass::Render -- renders this mesh                                                      *
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
// MeshClass::Render is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/MeshClassRender.cpp (0x0014BB90).


/***********************************************************************************************
 * MeshClass::Render_Material_Pass -- Render a procedural material pass for this mesh          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/4/2001   gth : Created.                                                                 *
 *=============================================================================================*/
// MeshClass::Render_Material_Pass: defined in bfme2_mesh_material_pass.cpp (its row's unit).


// MeshClass::Special_Render: Zero Hour visibility body removed; it is not retail's (no VisRasterizer path in BFME 2's MeshClass).



/***********************************************************************************************
 * MeshClass::Replace_VertexMaterial -- Replaces existing vertex material with a new one. Will *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/2/2001   hy : Created.                                                                  *
 *=============================================================================================*/
// ?MeshClass::Replace_VertexMaterial present-unmatched
void MeshClass::Replace_VertexMaterial(VertexMaterialClass* vmat,VertexMaterialClass* new_vmat)
{
	Model->Replace_VertexMaterial(vmat,new_vmat);
}


/***********************************************************************************************
 * MeshClass::Make_Unique -- Makes mesh unique in the renderer, but still shares system ram ge *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/2/2001   hy : Created.                                                                  *
 *=============================================================================================*/
// MeshClass::Make_Unique: defined in MeshClassMakeUnique.cpp (its row's unit).

/*********************************************************************************************** 
 * MeshClass::Load -- creates a mesh out of a mesh chunk in a .w3d file                        * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 * 																														  * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   06/12/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/


/***********************************************************************************************
 * MeshClass::Cast_Ray -- compute a ray intersection with this mesh                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   6/17/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// MeshClass::Cast_Ray defined in MeshClassCastRay.cpp


/***********************************************************************************************
 * MeshClass::Cast_AABox -- cast an AABox against this mesh                                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   6/17/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Cast_AABox present-unmatched
bool MeshClass::Cast_AABox(AABoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	WWASSERT(Model);

	// This function analyses the tranform to call optimized functions in certain cases
	bool hit = Model->Cast_World_Space_AABox(boxtest, Get_Transform());

	if (hit) {
		boxtest.CollidedRenderObj = this;
	}

	return hit;
}


/***********************************************************************************************
 * Cast_OBBox -- Cast an obbox against this mesh                                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   6/17/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Cast_OBBox present-unmatched
bool MeshClass::Cast_OBBox(OBBoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	/*
	** transform into the local coordinate system of the mesh.
	*/
	const Matrix3D & tm = Get_Transform();
	Matrix3D world_to_obj;
	tm.Get_Orthogonal_Inverse(world_to_obj);
	OBBoxCollisionTestClass localtest(boxtest,world_to_obj);

	WWASSERT(Model);

	bool hit = Model->Cast_OBBox(localtest);

	/*
	** If we hit, transform the result of the test back to the original coordinate system.
	*/
	if (hit) {
		boxtest.CollidedRenderObj = this;
		Matrix3D::Rotate_Vector(tm,boxtest.Result->Normal, &(boxtest.Result->Normal));
		if (boxtest.Result->ComputeContactPoint) {
			Matrix3D::Transform_Vector(tm,boxtest.Result->ContactPoint, &(boxtest.Result->ContactPoint));
		}
	}

	return hit;
}


/***********************************************************************************************
 * MeshClass::Intersect_AABox -- test for intersection with given AABox                        *
 *                                                                                             *
 * The AAbox given is assumed to be in world space.  Since meshes aren't generally in world    *
 * space, the test must be transformed into our local coordinate system (which turns it into   *
 * an OBBox...)                                                                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// BFME2's body is in MeshClassCollision.cpp (retail 0x0014B5E0); it needs the BFME2
// RenderObjClass vtable, which the shared header used here does not carry.


/***********************************************************************************************
 * MeshClass::Intersect_OBBox -- test for intersection with the given OBBox                    *
 *                                                                                             *
 * The given OBBox is assumed to be in world space so we need to transform it into the mesh's  *
 * local coordinate system.                                                                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Intersect_OBBox present-unmatched
bool MeshClass::Intersect_OBBox(OBBoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;

	Matrix3D inv_tm;
	Get_Transform().Get_Orthogonal_Inverse(inv_tm);
	OBBoxIntersectionTestClass local_test(boxtest,inv_tm);
	WWASSERT(Model);
	return Model->Intersect_OBBox(local_test);
}


/***********************************************************************************************
 * MeshClass::Get_Obj_Space_Bounding_Sphere -- returns obj-space bounding sphere               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void MeshClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	if (Model) {
		Model->Get_Bounding_Sphere(&sphere);
	} else {
		sphere.Center.Set(0,0,0);
		sphere.Radius = 1.0f;
	}
}


/***********************************************************************************************
 * MeshClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void MeshClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	if (Model) {
		Model->Get_Bounding_Box(&box);
	} else {
		box.Init(Vector3(0,0,0),Vector3(1,1,1));
	}
}


/***********************************************************************************************
 * MeshClass::Generate_Culling_Tree -- Generates a hierarchical culling tree for the mesh      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   6/18/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?MeshClass::Generate_Culling_Tree present-unmatched
void MeshClass::Generate_Culling_Tree(void)
{
	Model->Generate_Culling_Tree();
}


// MeshClass::Add_Dependencies_To_List: Zero Hour override removed; retail MeshClass has none.


/***********************************************************************************************
 * MeshClass::Update_Cached_Bounding_Volumes -- default collision sphere.                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/14/2001    NH : Created.                                                                *
 *=============================================================================================*/
// BFME2's body is in MeshClassCollision.cpp (retail 0x0014B650); it needs the BFME2
// RenderObjClass view, which the shared header used here does not carry.

namespace BfmeMeshBoundsAnchor
{
class Access : public MeshClass
{
public:
	static void _bfmeMeshBoundsInlineAnchor(void *storage, Vector3 & center);
};
}

// The Zero Hour Update_Cached_Bounding_Volumes kept these header inlines out
// of line in this unit (rows 0x00102559 and 0x0013B180). The anchor retains
// those bodies here now that the BFME2 caller lives elsewhere; it is not
// retail code.
#pragma inline_depth(0)
// ?_bfmeMeshBoundsInlineAnchor@Access@BfmeMeshBoundsAnchor@@SAXPAXAAVVector3@@@Z absent-from-retail
void BfmeMeshBoundsAnchor::Access::_bfmeMeshBoundsInlineAnchor(void *storage, Vector3 & center)
{
	Access *mesh = (Access *)storage;
	mesh->Get_Transform().mulVector3(center);
	mesh->Validate_Cached_Bounding_Volumes();
}
#pragma inline_depth()


// This utility function recurses throughout the subobjects of a renderobject, and for each
// MeshClass it finds it sets the given MeshModel flag on its model. This is useful for stuff
// like making a RenderObjects' polys sort.
void Set_MeshModel_Flag(RenderObjClass *robj, int flag, int onoff)
{
	if (robj->Class_ID() == RenderObjClass::CLASSID_MESH) {
		// Set flag on model (the assumption is that meshes don't have subobjects)
		MeshClass *mesh = (MeshClass *)robj;
		MeshModelClass *model = mesh->Get_Model();
		model->Set_Flag((MeshModelClass::FlagsType)flag, onoff != 0);
		model->Release_Ref();
	} else {
		// Recurse to subobjects (if any)
		int num_obj = robj->Get_Num_Sub_Objects();
		RenderObjClass *sub_obj;
		for (int i = 0; i < num_obj; i++) {
			sub_obj = robj->Get_Sub_Object(i);
			if (sub_obj) {
				Set_MeshModel_Flag(sub_obj, flag, onoff);
				sub_obj->Release_Ref();
			}
		}
	}
}

// BFME2's body is in MeshClassCollision.cpp (retail 0x0014A070); it needs the BFME2
// RenderObjClass view, which the shared header used here does not carry.

// BFME2's Set_Sort_Level is there too (retail 0x0014A090): this unit's layout puts the byte 4 too high.

// ?MeshClass::Get_Draw_Call_Count present-unmatched
struct Bfme2MeshModelDrawCountView {
	char Padding[0x98];
	MaterialInfoClass *MatInfo;
	DX8PolygonRendererList PolygonRendererList;
};

int MeshClass::Get_Draw_Call_Count(void) const
{
	if (Model != NULL) {
		// Prefer to return the number of polygon renderers
		int prcount = reinterpret_cast<Bfme2MeshModelDrawCountView *>(Model)->PolygonRendererList.Count();
		if (prcount > 0) {
			return prcount;
		}
		
		// Otherwise if we have textures, return the number of textures (e.g. dont have prs when sorting)
		if ((reinterpret_cast<Bfme2MeshModelDrawCountView *>(Model)->MatInfo != NULL) &&
			(reinterpret_cast<Bfme2MeshModelDrawCountView *>(Model)->MatInfo->Texture_Count() > 0)) {
			return reinterpret_cast<Bfme2MeshModelDrawCountView *>(Model)->MatInfo->Texture_Count();
		}

		// Otherwise, return 1
		return 1;

	} else {
		return 0;
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeMeshClassInlineAnchor@@YAXPAVMeshClass@@@Z absent-from-retail
void _bfmeMeshClassInlineAnchor(MeshClass *mesh)
{
    mesh->Get_Model();
}
#pragma inline_depth()

// The two-sided-rendering setters' rows (0x00355C2F, 0x005BE1D8) were emitted
// only by the removed visibility bodies; keep them emitted as header inlines.
#pragma inline_depth(0)
// ?_bfmeVisTwoSidedInlineAnchor@@YAXPAVVisRasterizerClass@@PAVIDBufferClass@@_N@Z absent-from-retail
void _bfmeVisTwoSidedInlineAnchor(VisRasterizerClass *v, IDBufferClass *idb, bool b)
{
    v->Enable_Two_Sided_Rendering(b);
    idb->Enable_Two_Sided_Rendering(b);
}
#pragma inline_depth()

// ?bfmeEmitLineSegClassCtor@@YAXPAVLineSegClass@@ABV0@ABVMatrix3D@@@Z present-unmatched
void bfmeEmitLineSegClassCtor(LineSegClass *lineSeg, const LineSegClass &src, const Matrix3D &tm)
{
    new (lineSeg) LineSegClass(src, tm);
}

