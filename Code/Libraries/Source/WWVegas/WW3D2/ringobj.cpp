// cl: /DBFME_WWSTRING_NATIVE_COPY_ASSIGN /DBFME_WWSTRING_NATIVE_COPY_CTOR /DBFME_WWSTRING_NATIVE_LENGTH /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/shims/sweep
// Bind Get_Length to the already matched native 48-byte provider at 0x0011FB10.
// This /G6 unit emits a 46-byte copy; changing it to /G7 also changes refcount helpers.
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
// This /Od unit emits an out-of-line copy of every inline it calls, so its
// Matrix3D::Translate(Vector3) COMDAT is not retail's 0x0007B3C6 body and,
// as the first copy in link order, blocks ObjectGetSingleLogicalBonePosition.
// TU-local rename (same device as the ShaderClass setters below) keeps the
// row's call byte-identical while no ?Translate@Matrix3D copy competes here.
#define Translate Translate_Ringobj
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#undef Translate
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// Link view: Matrix4(Matrix3D), Init(Matrix3D), Matrix4(Vector4 x4) and Transpose stay inline without
// emitting copies that, first in link order, displace retail's owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
// This unit has no /O1 /arch:SSE, so the ShaderClass setters it inlines are emitted here as COMDATs that are not
// the /O1 bodies retail keeps (rowed in the units that do compile with them); every use is inlined, so
// TU-local names keep them from competing with those copies.
#define Set_Primary_Gradient Set_Primary_Gradient_RV
#define Set_Secondary_Gradient Set_Secondary_Gradient_RV
#define Set_Depth_Compare Set_Depth_Compare_RV
#define Set_Depth_Mask Set_Depth_Mask_RV
#define Set_Color_Mask Set_Color_Mask_RV
#define Set_Dst_Blend_Func Set_Dst_Blend_Func_RV
#define Set_Src_Blend_Func Set_Src_Blend_Func_RV
#define Set_Fog_Func Set_Fog_Func_RV
// stlport
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
 *                     $Archive:: /Commando/Code/ww3d2/ringobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 11/24/01 6:17p                                              $*
 *                                                                                             *
 *                    $Revision:: 27                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor                                     *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor - init from a definition            *
 *   RingRenderObjClass::RingRenderObjClass -- Copy constructor                                *
 *   RingRenderObjClass::~RingRenderObjClass -- destructor                                     *
 *   RingRenderObjClass::operator -- assignment operator												     *
 *   RingRenderObjClass::Get_Num_Polys -- returns number of polygons									  *
 *   RingRenderObjClass::Get_Name -- returns name															  *
 *   RingRenderObjClass::Set_Name -- sets the name                                             *
 *   RingRenderObjClass::Set_Color -- Sets the color of the Ring                               *
 *   RingRenderObjClass::Init_Ring_Render_System -- global initialization needed for Ring		  *
 *   RingRenderObjClass::Shutdown_Ring_Render_System -- cleanup Ring render system				  *
 *   RingRenderObjClass::Set_Ring_Display_Mask -- Sets global display mask for all Ringes		  *
 *   RingRenderObjClass::Get_Ring_Display_Mask -- returns the display mask							  *
 *   RingRenderObjClass::update_mesh_data -- Updates vertex positions, etc                     *
 *   RingRenderObjClass::render_Ring -- submits the Ring to the GERD									  *
 *   RingRenderObjClass::vis_render_Ring -- submits Ring to the GERD for VIS						  *
 *   RingRenderObjClass::RingRenderObjClass -- constructor												  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor - init from a definition				  *
 *   RingRenderObjClass::RingRenderObjClass -- copy constructor										  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor from a wwmath aaRing					  *
 *   RingRenderObjClass::operator -- assignment operator                                       *
 *   RingRenderObjClass::Clone -- clones the Ring															  *
 *   RingRenderObjClass::Class_ID -- returns the class-id for AARing's								  *
 *   RingRenderObjClass::Render -- render this Ring														  *
 *   RingRenderObjClass::Special_Render -- special render this Ring (vis)							  *
 *   RingRenderObjClass::Set_Transform -- set the transform for this Ring							  *
 *   RingRenderObjClass::Set_Position -- Set the position of this Ring								  *
 *   RingRenderObjClass::update_cached_Ring -- update the world-space version of this Ring	  *
 *   RingRenderObjClass::Cast_Ray -- cast a ray against this Ring										  *
 *   RingRenderObjClass::Cast_AARing -- cast an AARing against this Ring							  *
 *   RingRenderObjClass::Cast_OBRing -- cast an OBRing against this Ring							  *
 *   RingRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sper*
 *   RingRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box      *
 *   RingRenderObjClass::Scale -- scales ring uniformly.                                       *
 *   RingRenderObjClass::Scale -- scales ring non-uniformly.                                   *
 *   RingRenderObjClass::Update_Cached_Bounding_Volumes -- Updates world-space bounding volum  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "ringobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include	"matrix3.h"
#include	"wwmath.h"
#include "assetmgr.h"
#include "wwstring.h"
#include "bound.h"
#include "camera.h"
#include "statistics.h"
#include "predlod.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"
#include "vector3i.h"
#include "visrasterizer.h"


static bool Ring_Array_Valid = false;


/**
** RingMeshClass
** A set of LODs of RingMeshes are re-used by all RingRenderObjClasses.
*/
class RingMeshClass
{
friend class RingRenderObjClass;

public:
	// Constructor
	RingMeshClass(void);
	RingMeshClass(float radius, int slices);
	// Destructor
	~RingMeshClass(void);

	void Generate(float radius, int slices);

	int	Get_Num_Polys(void) { return face_ct; };

	void	Scale (const Vector2 &inner_scale, const Vector2 &outer_scale);
	void	Set_Tiling (int count);

private:

	void	Free(void);

	float	Radius;
	int	Slices;
	int	face_ct;			//# of faces
	
	int		TileCount;
	Vector2	InnerScale;
	Vector2	OuterScale;

	int		Vertex_ct;		// vertex count
	Vector3	*vtx;				// array of vertices
	Vector2	*orig_vtx;		// array of vertices representing a 'unit' ring
	Vector3	*vtx_normal;	// array of vertex normals
	Vector2	*vtx_uv;			// array of vertex uv coordinates

	TriIndex	*tri_poly;	// array of triangle polys, vertex indices (can be discard if switch to fan renderer)
};


RingMeshClass RingMeshArray[RING_NUM_LOD];
float RingLODCosts[RING_NUM_LOD + 1];	// RING_NUM_LOD doesn't include the null LOD


/*
** RingRenderObjClass Implementation
*/


/***********************************************************************************************
 * RingRenderObjClass::RingRenderObjClass -- Constructor                                   *
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
// [provider-fix: suppressed unmatched ctor/dtor to avoid emitting vtable with Od RenderObjClass virtuals]

/***********************************************************************************************
 * RingRenderObjClass::RingRenderObjClass -- Constructor - init from a definition          *
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
// [provider-fix: suppressed unmatched ctor/dtor to avoid emitting vtable with Od RenderObjClass virtuals]


/***********************************************************************************************
 * RingRenderObjClass::RingRenderObjClass -- Copy constructor                              *
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
// [provider-fix: suppressed unmatched ctor/dtor to avoid emitting vtable with Od RenderObjClass virtuals]


/***********************************************************************************************
 * RingRenderObjClass::~RingRenderObjClass -- destructor                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/7/2001   gth : Created.                                                                 *
 *=============================================================================================*/
// [provider-fix: suppressed unmatched ctor/dtor to avoid emitting vtable with Od RenderObjClass virtuals]


// This is used both by Prepare_LOD and Calculate_Cost_Value_Arrays.


/***********************************************************************************************
 * RingRenderObjClass::Get_Name -- returns name                                              *
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
const char * RingRenderObjClass::Get_Name(void) const
{
	return Name;
}


/***********************************************************************************************
 * RingRenderObjClass::Get_Default_Alpha - get the default (or first frame) value				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/13/2000    pds : Created.                                                               *
 *=============================================================================================*/
// ?Get_Default_Alpha@RingRenderObjClass@@QBEMXZ present-unmatched
float RingRenderObjClass::Get_Default_Alpha(void) const
{
	float  value;
	
	if (AlphaChannel.Get_Key_Count () > 0) {
		value = AlphaChannel.Get_Key (0).Get_Value ();
	} else {
		value = Alpha;
	}

	return value;
}


// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/RingRenderObjPrepareLOD.cpp
// RingRenderObjClass::Get_Cost is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/ringobj_Get_Cost_RingRenderObjClass_UBEMXZ.cpp (0x00167F48).

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/RingRenderObjPrepareLOD.cpp
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/RingRenderObjPrepareLOD.cpp
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWSaveLoad/parameter.cpp


// ??0RingPrototypeClass@@ present-unmatched
RingPrototypeClass::RingPrototypeClass(RingRenderObjClass *ring)
{
	::memset (&Definition, 0, sizeof (Definition));	
	::strcpy (Definition.Name, ring->Get_Name ());
	
	Definition.AnimDuration			= ring->AnimDuration;
	Definition.Attributes			= ring->Get_Flags ();
	Definition.DefaultAlpha			= ring->Get_Default_Alpha ();
	Definition.DefaultInnerScale	= ring->Get_Default_Inner_Scale ();
	Definition.DefaultOuterScale	= ring->Get_Default_Outer_Scale ();
	Definition.TextureTileCount	= ring->Get_Texture_Tiling ();

	Definition.InnerExtent			= ring->Get_Inner_Extent ();
	Definition.OuterExtent			= ring->Get_Outer_Extent ();
	
	Vector3 def_color = ring->Get_Default_Color ();
	W3dUtilityClass::Convert_Vector (def_color, &Definition.DefaultColor);
	
	W3dUtilityClass::Convert_Vector (ring->Get_Box ().Center, &Definition.Center);
	W3dUtilityClass::Convert_Vector (ring->Get_Box ().Extent, &Definition.Extent);	
	W3dUtilityClass::Convert_Shader (ring->RingShader, &Definition.Shader);	

	//
	//	Determine the texture name for this ring
	//
	if (ring->RingTexture != NULL) {
		StringClass name = ring->RingTexture->Get_Full_Path();
		const char *filename = ::strrchr (name, '\\');
		if (filename != NULL) {
			filename ++;
		} else {
			filename = name;
		}

		::strcpy (Definition.TextureName, filename);
	}

	//
	//	Save the animateable channels
	//
	ColorChannel		= ring->Peek_Color_Channel ();
	AlphaChannel		= ring->Peek_Alpha_Channel ();
	InnerScaleChannel	= ring->Peek_Inner_Scale_Channel ();
	OuterScaleChannel	= ring->Peek_Outer_Scale_Channel ();
	return ;
}

enum
{
	CHUNKID_RING_DEF						= 1,
	CHUNKID_COLOR_CHANNEL,
	CHUNKID_ALPHA_CHANNEL,
	CHUNKID_INNER_SCALE_CHANNEL,
	CHUNKID_OUTER_SCALE_CHANNEL
};

/*
** Global instance of the box loader
*/
RingLoaderClass _RingLoader;


//
// Vertices are ordered as such
//  center, followed by outer ring
//


// EOF - ringobj.cpp
