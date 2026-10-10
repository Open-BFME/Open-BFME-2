// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /arch:SSE /G7 /Ireference/shims/bfme2renderobj /Ireference/shims/bfmelight /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/boxrobj.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"	// the bfme2renderobj shim has to win the include guard
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
 *                     $Archive:: /Commando/Code/ww3d2/boxrobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/19/02 12:57p                                              $*
 *                                                                                             *
 *                    $Revision:: 35                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   BoxRenderObjClass::BoxRenderObjClass -- Constructor                                       *
 *   BoxRenderObjClass::BoxRenderObjClass -- Constructor - init from a definition              *
 *   BoxRenderObjClass::BoxRenderObjClass -- Copy constructor                                  *
 *   BoxRenderObjClass::operator -- assignment operator                                        *
 *   BoxRenderObjClass::Get_Num_Polys -- returns number of polygons                            *
 *   BoxRenderObjClass::Get_Name -- returns name                                               *
 *   BoxRenderObjClass::Set_Name -- sets the name                                              *
 *   BoxRenderObjClass::Set_Color -- Sets the color of the box                                 *
 *   BoxRenderObjClass::Init_Box_Render_System -- global initialization needed for boxes to wo *
 *   BoxRenderObjClass::Shutdown_Box_Render_System -- cleanup box render system                *
 *   BoxRenderObjClass::Set_Box_Display_Mask -- Sets global display mask for all boxes         *
 *   BoxRenderObjClass::Get_Box_Display_Mask -- returns the display mask                       *
 *   BoxRenderObjClass::render_box -- submits the box to the GERD                              *
 *   BoxRenderObjClass::vis_render_box -- submits box to the GERD for VIS                      *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- constructor                                   *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- Constructor - init from a definition          *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- copy constructor                              *
 *   AABoxRenderObjClass::AABoxRenderObjClass -- Constructor from a wwmath aabox               *
 *   AABoxRenderObjClass::operator -- assignment operator                                      *
 *   AABoxRenderObjClass::Clone -- clones the box                                              *
 *   AABoxRenderObjClass::Class_ID -- returns the class-id for AABox's                         *
 *   AABoxRenderObjClass::Render -- render this box                                            *
 *   AABoxRenderObjClass::Special_Render -- special render this box (vis)                      *
 *   AABoxRenderObjClass::Set_Transform -- set the transform for this box                      *
 *   AABoxRenderObjClass::Set_Position -- Set the position of this box                         *
 *   AABoxRenderObjClass::update_cached_box -- update the world-space version of this box      *
 *   AABoxRenderObjClass::Cast_Ray -- cast a ray against this box                              *
 *   AABoxRenderObjClass::Cast_AABox -- cast an AABox against this box                         *
 *   AABoxRenderObjClass::Cast_OBBox -- cast an OBBox against this box                         *
 *   AABoxRenderObjClass::Intersect_AABox -- intersect this box with an AABox                  *
 *   AABoxRenderObjClass::Intersect_OBBox -- Intersect this box with an OBBox                  *
 *   AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sp *
 *   AABoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box     *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor                                   *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor - initiallize from a definition   *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- copy constructor                              *
 *   OBBoxRenderObjClass::OBBoxRenderObjClass -- constructor - initialize from a wwmath obbox  *
 *   OBBoxRenderObjClass::operator -- assignment operator                                      *
 *   OBBoxRenderObjClass::Clone -- clone this obbox                                            *
 *   OBBoxRenderObjClass::Class_ID -- returns the class ID of OBBoxRenderObjClass              *
 *   OBBoxRenderObjClass::Render -- render this obbox                                          *
 *   OBBoxRenderObjClass::Special_Render -- special render (vis)                               *
 *   OBBoxRenderObjClass::Set_Transform -- set the transform for this box                      *
 *   OBBoxRenderObjClass::Set_Position -- set the position of this box                         *
 *   OBBoxRenderObjClass::update_cached_box -- update the cached world-space box               *
 *   OBBoxRenderObjClass::Cast_Ray -- cast a ray against this box                              *
 *   OBBoxRenderObjClass::Cast_AABox -- cast a swept aabox against this box                    *
 *   OBBoxRenderObjClass::Cast_OBBox -- cast a swept obbox against this bo                     *
 *   OBBoxRenderObjClass::Intersect_AABox -- test this box for intersection with an AAbox      *
 *   OBBoxRenderObjClass::Intersect_OBBox -- test this box for intersection with an OBBox      *
 *   OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the obj-space bounding spher *
 *   OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box     *
 *   OBBoxRenderObjClass::Get_Box -- returns the cached world-space box                        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "boxrobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"
#include "sortingrenderer.h"
#include "visrasterizer.h"
#include "meshgeometry.h"


#define NUM_BOX_VERTS	8
#define NUM_BOX_FACES	12

// Face Connectivity
static TriIndex					_BoxFaces[NUM_BOX_FACES] = 
{
	TriIndex( 0,1,2 ),		// +z faces
	TriIndex( 0,2,3 ),		
	TriIndex( 4,7,6 ),		// -z faces
	TriIndex( 4,6,5 ),
	TriIndex( 0,3,7 ),		// +x faces
	TriIndex( 0,7,4 ),
	TriIndex( 1,5,6 ),		// -x faces
	TriIndex( 1,6,2 ),
	TriIndex( 4,5,1 ),		// +y faces
	TriIndex( 4,1,0 ),
	TriIndex( 3,2,6 ),		// -y faces
	TriIndex( 3,6,7 )
};

// Vertex Positions as a function of the box extents
static Vector3						_BoxVerts[NUM_BOX_VERTS] = 
{
	Vector3(  1.0f, 1.0f, 1.0f ),		// +z ring of 4 verts
	Vector3( -1.0f, 1.0f, 1.0f ),
	Vector3( -1.0f,-1.0f, 1.0f ),
	Vector3(  1.0f,-1.0f, 1.0f ),

	Vector3(  1.0f, 1.0f,-1.0f ),		// -z ring of 4 verts;
	Vector3( -1.0f, 1.0f,-1.0f ),
	Vector3( -1.0f,-1.0f,-1.0f ),
	Vector3(  1.0f,-1.0f,-1.0f ),
};

// Vertex Normals
static Vector3						_BoxVertexNormals[NUM_BOX_VERTS] =
{
	Vector3( WWMATH_OOSQRT3, WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3, WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3,-WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),
	Vector3( WWMATH_OOSQRT3,-WWMATH_OOSQRT3, WWMATH_OOSQRT3 ),

	Vector3( WWMATH_OOSQRT3, WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3, WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3(-WWMATH_OOSQRT3,-WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
	Vector3( WWMATH_OOSQRT3,-WWMATH_OOSQRT3,-WWMATH_OOSQRT3 ),
};



bool										BoxRenderObjClass::IsInitted			= false;
int										BoxRenderObjClass::DisplayMask		= 0;
static VertexMaterialClass *		_BoxMaterial								= NULL;
static ShaderClass					_BoxShader;

// BFME 2's dynamic vertex access takes a format index and a buffer argument
// (render_box passes 2,5,8,0 to the matched constructor at 0x0013B040) and
// is 24 bytes, its write lock 12; the layout follows the BfmeSortingVBAccess
// view used by Line3DClassRender.cpp, whose members are pinned to the matched
// bodies at 0x0013B040/0x0013A780/0x0013AA00/0x0013AB00.
class BoxVertexBufferClass;

struct BfmeSortingVBAccess {
	const FVFInfoClass& FVFInfo;
	unsigned Type;
	unsigned formatIndex;
	unsigned unused_0x0C;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	BoxVertexBufferClass* VertexBuffer;

	BfmeSortingVBAccess(unsigned type, unsigned format_index,
		unsigned short vertex_count, unsigned buffer);
	~BfmeSortingVBAccess();

	class WriteLock {
		BfmeSortingVBAccess* DynamicVBAccess;
		VertexFormatXYZNDUV2* Vertices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingVBAccess* vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2* Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

// The dynamic index access is the same 12-byte object as DynamicIBAccessClass,
// but BFME 2's write lock carries a device guard at +8 (12 bytes); pinned to
// the matched bodies at 0x00139240/0x00138BE0/0x00138CA0/0x00138D80.
struct BfmeSortingIBAccess {
	unsigned Type;
	unsigned short IndexCount;
	unsigned short IndexBufferOffset;
	IndexBufferClass* IndexBuffer;

	BfmeSortingIBAccess(unsigned short type, unsigned short index_count);
	~BfmeSortingIBAccess();

	class WriteLock {
		BfmeSortingIBAccess* DynamicIBAccess;
		unsigned short* Indices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingIBAccess* ib_access);
		~WriteLock();
		unsigned short* Get_Index_Array() { return Indices; }
	};
};

// Retail binds stage 0 through a by-reference texture slot that the caller
// releases afterwards (BFME 1 boxrobj.cpp donor).
extern void BoxSetTexture(unsigned stage, TextureBaseClass*& texture);

class BoxTextureRef {
	TextureBaseClass* Texture;

public:
	BoxTextureRef() : Texture(NULL) {}
	~BoxTextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass*&() { return Texture; }
};


/*
** BoxRenderObjClass Implementation
*/


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Constructor                                         *
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
BoxRenderObjClass::BoxRenderObjClass(void)
{
	memset(Name,0,sizeof(Name));
	Color.Set(1,1,1);
	Opacity = 0.25f;
	ObjSpaceCenter.Set(0,0,0);
	ObjSpaceExtent.Set(1,1,1);
}


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Constructor - init from a definition                *
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
// BoxRenderObjClass(const W3dBoxStruct&): BFME 2's body is the row 0x00175A40 in BoxRenderObjClassCtor.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * BoxRenderObjClass::BoxRenderObjClass -- Copy constructor                                    *
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
BoxRenderObjClass::BoxRenderObjClass(const BoxRenderObjClass & src)
{
	*this = src;
}


/***********************************************************************************************
 * BoxRenderObjClass::operator -- assignment operator                                          *
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
BoxRenderObjClass & BoxRenderObjClass::operator = (const BoxRenderObjClass & that)
{
	if (this != &that) {
		RenderObjClass::operator = (that);
		Set_Name(that.Get_Name());
		Color.Set(that.Color);
		ObjSpaceCenter.Set(that.ObjSpaceCenter);
		ObjSpaceExtent.Set(that.ObjSpaceExtent);
	}
	return *this;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Num_Polys -- returns number of polygons                              *
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
// ?BoxRenderObjClass::Get_Num_Polys present-unmatched
int BoxRenderObjClass::Get_Num_Polys(void) const
{
	return 12;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Name -- returns name                                                 *
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
const char * BoxRenderObjClass::Get_Name(void) const
{
	return Name;
}


/***********************************************************************************************
 * BoxRenderObjClass::Set_Name -- sets the name                                                *
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
// BoxRenderObjClass::Set_Name: defined in BoxRenderObjClassCtor.cpp (its row's unit).


/***********************************************************************************************
 * BoxRenderObjClass::Set_Color -- Sets the color of the box                                   *
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
// ?BoxRenderObjClass::Set_Color present-unmatched
void BoxRenderObjClass::Set_Color(const Vector3 & color)
{
	Color = color;
}


/***********************************************************************************************
 * BoxRenderObjClass::Init_Box_Render_System -- global initialization needed for boxes to work *
 *                                                                                             *
 * Allocates materials which all boxes share.  Initializes vertex tables, etc                  *
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
// BoxRenderObjClass::Init: defined in BoxRenderObjInit.cpp (its row's unit).


/***********************************************************************************************
 * BoxRenderObjClass::Shutdown -- cleanup box render system                                    *
 *                                                                                             *
 * Releases resources allocated in Init                                                        *
 * NOTE: this is a static function that should only be called by the system                    *
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
// BoxRenderObjClass::Shutdown: defined in BoxRenderObjInit.cpp (its row's unit).


/***********************************************************************************************
 * BoxRenderObjClass::Set_Box_Display_Mask -- Sets global display mask for all boxes           *
 *                                                                                             *
 * Boxes are debug objects and usually used for collision.  This mask is 'AND'ed with each     *
 * box's collision type to determine whether the box should be rendered.                       *
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
// ?BoxRenderObjClass::Set_Box_Display_Mask present-unmatched
void BoxRenderObjClass::Set_Box_Display_Mask(int mask)
{
	DisplayMask = mask;
}


/***********************************************************************************************
 * BoxRenderObjClass::Get_Box_Display_Mask -- returns the display mask                         *
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
// ?BoxRenderObjClass::Get_Box_Display_Mask present-unmatched
int BoxRenderObjClass::Get_Box_Display_Mask(void)
{
	return DisplayMask;
}


/***********************************************************************************************
 * BoxRenderObjClass::render_box -- submits the box to the GERD                                *
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
void BoxRenderObjClass::render_box(RenderInfoClass & rinfo,const Vector3 & center,const Vector3 & extent)
{
	if (!IsInitted) return;
	if (DisplayMask & Get_Collision_Type()) {

		static Vector3 verts[NUM_BOX_VERTS];

		// compute the vertex positions
		for (int ivert=0; ivert<NUM_BOX_VERTS; ivert++) {
			verts[ivert].X = center.X + _BoxVerts[ivert][0] * extent.X;
			verts[ivert].Y = center.Y + _BoxVerts[ivert][1] * extent.Y;
			verts[ivert].Z = center.Z + _BoxVerts[ivert][2] * extent.Z;
		}

		/*
		** Dump the box vertices into the sorting dynamic vertex buffer. 
		*/
		DWORD color = DX8Wrapper::Convert_Color(Color,Opacity);
		
		int buffer_type = BUFFER_TYPE_DYNAMIC_DX8;

		BfmeSortingVBAccess vbaccess(buffer_type,5,NUM_BOX_VERTS,0);
		{
			BfmeSortingVBAccess::WriteLock lock(&vbaccess);
			//unsigned char *vb=(unsigned char *) lock.Get_Vertex_Array();
			VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

			for (int i=0; i<NUM_BOX_VERTS; i++) {

				// Locations
				vb->x=verts[i][0];
				vb->y=verts[i][1];
				vb->z=verts[i][2];
				
				// Normals
				vb->nx=_BoxVertexNormals[i][0];
				vb->ny=_BoxVertexNormals[i][1];
				vb->nz=_BoxVertexNormals[i][2];

				// Colors
				vb->diffuse=color;

				vb++;
			}
		}

		/*
		** Dump the faces into the sorting dynamic index buffer.
		*/
		BfmeSortingIBAccess ibaccess(buffer_type,NUM_BOX_FACES*3);
		{
			BfmeSortingIBAccess::WriteLock lock(&ibaccess);
			unsigned short * indices = lock.Get_Index_Array();
			for (int i=0; i<NUM_BOX_FACES; i++) {
				indices[3*i] = _BoxFaces[i][0];
				indices[3*i+1] = _BoxFaces[i][1];
				indices[3*i+2] = _BoxFaces[i][2];
			}
		}

		/*
		** Apply the shader and material
		*/
		DX8Wrapper::Set_Material(_BoxMaterial);
		DX8Wrapper::Set_Shader(_BoxShader);
		{
			BoxTextureRef texture;
			BoxSetTexture(0,texture);
		}
		
		DX8Wrapper::Set_Index_Buffer(*reinterpret_cast<DynamicIBAccessClass *>(&ibaccess),0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vbaccess));

		SphereClass sphere;
		Get_Obj_Space_Bounding_Sphere(sphere); 

		DX8Wrapper::Draw_Triangles(buffer_type,0,NUM_BOX_FACES,0,NUM_BOX_VERTS);
	}
}


/***********************************************************************************************
 * BoxRenderObjClass::vis_render_box -- submits box to the GERD for VIS                        *
 *                                                                                             *
 * this renders the box with the specified VIS-ID.                                             *
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
// ?BoxRenderObjClass::vis_render_box present-unmatched
void BoxRenderObjClass::vis_render_box(SpecialRenderInfoClass & rinfo,const Vector3 & center,const Vector3 & extent)
{
	if (!IsInitted) return;
	
	static Vector3 verts[NUM_BOX_VERTS];

	// compute the vertex positions
	for (int ivert=0; ivert<NUM_BOX_VERTS; ivert++) {
		verts[ivert].X = center.X + _BoxVerts[ivert][0] * extent.X;
		verts[ivert].Y = center.Y + _BoxVerts[ivert][1] * extent.Y;
		verts[ivert].Z = center.Z + _BoxVerts[ivert][2] * extent.Z;
	}

	// render!
	rinfo.VisRasterizer->Render_Triangles(verts,NUM_BOX_VERTS,_BoxFaces,NUM_BOX_FACES,Get_Bounding_Box());
}

/*
** AABoxRenderObjClass Implementation
*/

/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- constructor                                     *
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
// AABoxRenderObjClass(): BFME 2's body is the row 0x00175BB0 in AABoxRenderObjDefaultCtor.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- Constructor - init from a definition            *
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
// AABoxRenderObjClass(const W3dBoxStruct&): BFME 2's body is the row 0x00175C40 in AABoxRenderObjFromDef.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- copy constructor                                *
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
AABoxRenderObjClass::AABoxRenderObjClass(const AABoxRenderObjClass & src)
{
	*this = src;
}


/***********************************************************************************************
 * AABoxRenderObjClass::AABoxRenderObjClass -- Constructor from a wwmath aabox                 *
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
// AABoxRenderObjClass(const AABoxClass&): BFME 2's body is the row 0x00175CD0 in AABoxRenderObjFromAABox.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * AABoxRenderObjClass::operator -- assignment operator                                        *
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
AABoxRenderObjClass & AABoxRenderObjClass::operator = (const AABoxRenderObjClass & that)
{
	if (this != &that) {
		BoxRenderObjClass::operator = (that);
		CachedBox = that.CachedBox;
	}
	return *this;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Clone -- clones the box                                                *
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
// AABoxRenderObjClass::Clone: defined in AABoxRenderObjClone.cpp (its row's unit).


/***********************************************************************************************
 * AABoxRenderObjClass::Class_ID -- returns the class-id for AABox's                           *
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
// ?AABoxRenderObjClass::Class_ID present-unmatched
int AABoxRenderObjClass::Class_ID(void) const
{
	return RenderObjClass::CLASSID_AABOX;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Render -- render this box                                              *
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
// ?AABoxRenderObjClass::Render present-unmatched
void AABoxRenderObjClass::Render(RenderInfoClass & rinfo)
{
	Matrix3D temp(1);
	temp.Translate(Transform.Get_Translation());
	DX8Wrapper::Set_Transform(D3DTS_WORLD,temp);
	render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * AABoxRenderObjClass::Special_Render -- special render this box (vis)                        *
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
// ?AABoxRenderObjClass::Special_Render present-unmatched
void AABoxRenderObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	if (rinfo.RenderType == SpecialRenderInfoClass::RENDER_VIS) {
		WWASSERT(rinfo.VisRasterizer != NULL);
		Matrix3D temp(1);
		temp.Translate(Transform.Get_Translation());
		rinfo.VisRasterizer->Set_Model_Transform(temp);
		vis_render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
	}
}


/***********************************************************************************************
 * AABoxRenderObjClass::Set_Transform -- set the transform for this box                        *
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
void AABoxRenderObjClass::Set_Transform(const Matrix3D &m)
{
	RenderObjClass::Set_Transform(m);
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::Set_Position -- Set the position of this box                           *
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
inline void AABoxRenderObjClass::Set_Position(const Vector3 &v)
{
	RenderObjClass::Set_Position(v);
	update_cached_box();
}


/***********************************************************************************************
 * AABoxRenderObjClass::update_cached_box -- update the world-space version of this box        *
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
// AABoxRenderObjClass::update_cached_box: defined in AABoxUpdateCachedBox.cpp (its row's unit).


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_Ray -- cast a ray against this box                                *
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
bool AABoxRenderObjClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	if (Is_Animation_Hidden()) return false;
	if (raytest.Result->StartBad) return false;

	if (CollisionMath::Collide(raytest.Ray,CachedBox,raytest.Result)) {
		raytest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_AABox -- cast an AABox against this box                           *
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
// ?AABoxRenderObjClass::Cast_AABox present-unmatched
bool AABoxRenderObjClass::Cast_AABox(AABoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Cast_OBBox -- cast an OBBox against this box                           *
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
// ?AABoxRenderObjClass::Cast_OBBox present-unmatched
bool AABoxRenderObjClass::Cast_OBBox(OBBoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * AABoxRenderObjClass::Intersect_AABox -- intersect this box with an AABox                    *
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
// ?AABoxRenderObjClass::Intersect_AABox present-unmatched
bool AABoxRenderObjClass::Intersect_AABox(AABoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);	
}


/***********************************************************************************************
 * AABoxRenderObjClass::Intersect_OBBox -- Intersect this box with an OBBox                    *
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
// ?AABoxRenderObjClass::Intersect_OBBox present-unmatched
bool AABoxRenderObjClass::Intersect_OBBox(OBBoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);
}


/***********************************************************************************************
 * AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sphe *
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
// AABoxRenderObjClass::Get_Obj_Space_Bounding_Sphere: defined in AABoxBoundingSphere.cpp (its row's unit).


/***********************************************************************************************
 * AABoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box       *
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
void AABoxRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Init(ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor                                     *
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
OBBoxRenderObjClass::OBBoxRenderObjClass(void)
{
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- Constructor - initiallize from a definition     *
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
OBBoxRenderObjClass::OBBoxRenderObjClass(const W3dBoxStruct & def) :
	BoxRenderObjClass(def)
{
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- copy constructor                                *
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
OBBoxRenderObjClass::OBBoxRenderObjClass(const OBBoxRenderObjClass & that)
{
	*this = that;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::OBBoxRenderObjClass -- constructor - initialize from a wwmath obbox    *
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
// OBBoxRenderObjClass(const OBBoxClass&): BFME 2's body is the row 0x00176000 in OBBoxRenderObjFromOBBox.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * OBBoxRenderObjClass::operator -- assignment operator                                        *
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
OBBoxRenderObjClass & OBBoxRenderObjClass::operator = (const OBBoxRenderObjClass & that)
{
	if (this != &that) {
		BoxRenderObjClass::operator = (that);
		CachedBox = that.CachedBox;
	}
	return *this;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Clone -- clone this obbox                                              *
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
// OBBoxRenderObjClass::Clone: defined in OBBoxRenderObjClone.cpp (its row's unit).


/***********************************************************************************************
 * OBBoxRenderObjClass::Class_ID -- returns the class ID of OBBoxRenderObjClass                *
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
// ?OBBoxRenderObjClass::Class_ID present-unmatched
int OBBoxRenderObjClass::Class_ID(void) const
{
	return RenderObjClass::CLASSID_OBBOX;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Render -- render this obbox                                            *
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
void OBBoxRenderObjClass::Render(RenderInfoClass & rinfo)
{
	DX8Wrapper::Set_Transform(D3DTS_WORLD,Transform);
	render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Special_Render -- special render (vis)                                 *
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
// ?OBBoxRenderObjClass::Special_Render present-unmatched
void OBBoxRenderObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	if (rinfo.RenderType == SpecialRenderInfoClass::RENDER_VIS) {
		WWASSERT(rinfo.VisRasterizer != NULL);
		rinfo.VisRasterizer->Set_Model_Transform(Transform);
		vis_render_box(rinfo,ObjSpaceCenter,ObjSpaceExtent);
	}
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Set_Transform -- set the transform for this box                        *
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
// ?OBBoxRenderObjClass::Set_Transform present-unmatched
inline void OBBoxRenderObjClass::Set_Transform(const Matrix3D &m)
{
	RenderObjClass::Set_Transform(m);
	update_cached_box();
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Set_Position -- set the position of this box                           *
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
// ?OBBoxRenderObjClass::Set_Position present-unmatched
void OBBoxRenderObjClass::Set_Position(const Vector3 &v)
{
	RenderObjClass::Set_Position(v);
	update_cached_box();
}


// Set_Position is a header inline in its copier units; the anchor retains this
// unit's row copy and is not retail code.
#pragma inline_depth(0)
// ?_bfmeAABoxRenderObjSetPositionInlineAnchor@@YAXXZ absent-from-retail
void _bfmeAABoxRenderObjSetPositionInlineAnchor()
{
	static_cast<AABoxRenderObjClass *>(0)->AABoxRenderObjClass::Set_Position(
		*static_cast<const Vector3 *>(0));
}
#pragma inline_depth()


/***********************************************************************************************
 * OBBoxRenderObjClass::update_cached_box -- update the cached world-space box                 *
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
// OBBoxRenderObjClass::update_cached_box: defined in OBBoxUpdateCachedBox.cpp (its row's unit).


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_Ray -- cast a ray against this box                                *
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
bool OBBoxRenderObjClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;
	if (Is_Animation_Hidden()) return false;
	if (raytest.Result->StartBad) return false;

	if (CollisionMath::Collide(raytest.Ray,CachedBox,raytest.Result)) {
		raytest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_AABox -- cast a swept aabox against this box                      *
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
// ?OBBoxRenderObjClass::Cast_AABox present-unmatched
bool OBBoxRenderObjClass::Cast_AABox(AABoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Cast_OBBox -- cast a swept obbox against this bo                       *
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
// ?OBBoxRenderObjClass::Cast_OBBox present-unmatched
bool OBBoxRenderObjClass::Cast_OBBox(OBBoxCollisionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	if (boxtest.Result->StartBad) return false;

	if (CollisionMath::Collide(boxtest.Box,boxtest.Move,CachedBox,Vector3(0,0,0),boxtest.Result)) {
		boxtest.CollidedRenderObj = this;
		return true;
	}
	return false;
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Intersect_AABox -- test this box for intersection with an AAbox        *
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
// ?OBBoxRenderObjClass::Intersect_AABox present-unmatched
bool OBBoxRenderObjClass::Intersect_AABox(AABoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);	
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Intersect_OBBox -- test this box for intersection with an OBBox        *
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
// ?OBBoxRenderObjClass::Intersect_OBBox present-unmatched
bool OBBoxRenderObjClass::Intersect_OBBox(OBBoxIntersectionTestClass & boxtest)
{
	if ((Get_Collision_Type() & boxtest.CollisionType) == 0) return false;
	return CollisionMath::Intersection_Test(CachedBox,boxtest.Box);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the obj-space bounding sphere  *
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
// ?OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere present-unmatched
void OBBoxRenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Init(ObjSpaceCenter,ObjSpaceExtent.Length());
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box       *
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
// ?OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box present-unmatched
void OBBoxRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Init(ObjSpaceCenter,ObjSpaceExtent);
}


/***********************************************************************************************
 * OBBoxRenderObjClass::Get_Box -- returns the cached world-space box                          *
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
OBBoxClass & OBBoxRenderObjClass::Get_Box(void)
{
	Validate_Transform();
	update_cached_box();
	return CachedBox;
}

/*
** BoxLoaderClass Implementation
*/
// ?BoxLoaderClass::Load_W3D present-unmatched
PrototypeClass * BoxLoaderClass::Load_W3D(ChunkLoadClass & cload)
{
	W3dBoxStruct box;
	cload.Read(&box,sizeof(box));
	return W3DNEW BoxPrototypeClass(box);
}

/*
** BoxPrototypeClass Implementation
*/
// ?BoxPrototypeClass::BoxPrototypeClass present-unmatched
BoxPrototypeClass::BoxPrototypeClass(W3dBoxStruct box)
{
	Definition = box;
}

// ?BoxPrototypeClass::Get_Name present-unmatched
const char * BoxPrototypeClass::Get_Name(void) const
{
	return Definition.Name;
}

// ?BoxPrototypeClass::Get_Class_ID present-unmatched
int BoxPrototypeClass::Get_Class_ID(void) const
{
	if (Definition.Attributes & W3D_BOX_ATTRIBUTE_ORIENTED) {
		return RenderObjClass::CLASSID_OBBOX;
	} else {
		return RenderObjClass::CLASSID_AABOX;
	}
}
	
// ?BoxPrototypeClass::Create present-unmatched
RenderObjClass * BoxPrototypeClass::Create(void)
{
	if (Definition.Attributes & W3D_BOX_ATTRIBUTE_ORIENTED) {
		return NEW_REF( OBBoxRenderObjClass, (Definition) );
	} else {
		return NEW_REF( AABoxRenderObjClass, (Definition) );
	}
}

/*
** Global instance of the box loader
*/
BoxLoaderClass _BoxLoader;
