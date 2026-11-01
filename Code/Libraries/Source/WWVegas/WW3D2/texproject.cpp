// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/texproject.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "vector3.h"
// Retain inline indexing without a competing external Matrix3 helper.
#include "../../../../../reference/shims/bfme_matrix3_owner_link/matrix3.h"
#include "matrix3d.h"
#include "wwmath.h"
#include "castres.h"
#include "obbox.h"
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
 *                     $Archive:: /Commando/Code/ww3d2/texproject.cpp                         $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *								$Modtime:: 08/05/02 10:03a                                             $*
 *                                                                                             *
 *                    $Revision:: 22                                                          $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 * 06/27/02 KM Render to shadow buffer texture support														*
 * 08/05/02 KM Texture class redesign 
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   TexProjectClass::TexProjectClass -- Constructor                                           *
 *   TexProjectClass::~TexProjectClass -- Destructor                                           *
 *   TexProjectClass::Set_Texture_Size -- Set the size of texture to use                       *
 *   TexProjectClass::Get_Texture_Size -- Returns the stored texture size                      *
 *   TexProjectClass::Set_Flag -- Turn specified flag on or off                                *
 *   TexProjectClass::Get_Flag -- Get the current state of specified flag                      *
 *   TexProjectClass::Set_Intensity -- Set the intensity of this projector                     *
 *   TexProjectClass::Get_Intensity -- returns the current "desired" intensity                 *
 *   TexProjectClass::Set_Attenuation -- Set the attenuation factor                            *
 *   TexProjectClass::Get_Attenuation -- Returns the attenuation value                         *
 *   TexProjectClass::Enable_Attenuation -- Set the state of the ATTENUATE flag                *
 *   TexProjectClass::Is_Attenuation_Enabled -- Get the state of the ATTENUATE flag            *
 *   TexProjectClass::Is_Depth_Gradient_Enabled -- returns whether the depth gradient is enabl *
 *   TexProjectClass::Enable_Depth_Gradient -- enable/disable depth gradient                   *
 *   TexProjectClass::Init_Multiplicative -- Initialize this to be a multiplicative texture pr *
 *   TexProjectClass::Is_Intensity_Zero -- check if we can eliminate this projector            *
 *   TexProjectClass::Init_Additive -- Set up the projector to be additive                     *
 *   TexProjectClass::Set_Perspective_Projection -- Set up a perspective projection            *
 *   TexProjectClass::Set_Ortho_Projection -- Set up an orthographic projection                *
 *   TexProjectClass::Set_Texture -- Set the texture to be projected                           *
 *   TexProjectClass::Get_Texture -- Returns the texture being projected                       *
 *   TexProjectClass::Peek_Texture -- Returns the texture being projected                      *
 *   TexProjectClass::Peek_Material_Pass -- Returns the material pass object                   *
 *   TexProjectClass::Compute_Perspective_Projection -- Set up a perspective projection of an  *
 *   TexProjectClass::Compute_Perspective_Projection -- Set up a perspective projection of an  *
 *   TexProjectClass::Compute_Ortho_Projection -- Automatic Orthographic projection            *
 *   TexProjectClass::Compute_Ortho_Projection -- Automatic Orthographic projection            *
 *   TexProjectClass::Compute_Texture -- Generates texture by rendering an object              *
 *   TexProjectClass::Configure_Camera -- setup a camera to match this projector               *
 *   TexProjectClass::Pre_Render_Update -- Prepare the projector for rendering                 *
 *   TexProjectClass::Update_WS_Bounding_Volume -- Recalculate the world-space bounding box    *
 *   TexProjectClass::Get_Surface -- Returns pointer to the texture surface                    *
 *   TexProjectClass::Set_Render_Target -- Install a render target for this projector to use   *
 *   TexProjectClass::Needs_Render_Target -- returns wheter this projector needs a render targ *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "texproject.h"
// Set_Mapper calls bind to vertmaterial.cpp's row instead of emitting a local copy.
#include "../../../../../reference/shims/bfme_vertmaterial_mapper_link/vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "rendobj.h"
#include "rinfo.h"
#include "camera.h"
#include "matpass.h"
#include "bwrender.h"
#include "assetmgr.h"
#include "dx8wrapper.h"


// DEBUG DEBUG
#include "mpu.h"

#define DEBUG_SHADOW_RENDERING					0
//#define DEFAULT_TEXTURE_SIZE						64

const float INTENSITY_RATE_OF_CHANGE			= 1.0f;			// change in intensity per second


/*
** 
** Shadow mapping:  from pre-projected view coordinates back to world space
** then to shadow space
**
** (1) Vshadow = PShadow * Mwrld-shadow * Vwrld
** 
** (2) Vview = Mwrld-camera * Vwrld
**
** Using (2) to solve for Vwrld in terms of Vview
**                -1
** (3) Mwrld-camera  * Vview = Vwrld
**
** Substituting (3) into (1)
**                                                   -1
** (4) Vshadow = Pshadow * Mwrld-shadow * Mwrld-camera * Vview
**
** ---------------------------------------------------------------------------------
** 
** Shadow mapping: from pre-projected view space to world space, to shadow space, 
** then projecting.
** 
** (1) Vshadow = Mwrld-shadow * Vwrld
**
** (2) Vview = Mwrld-camera * Vwrld
**
** solving (2) for Vwrld:
**                -1
** (3) Mwrld-camera * Vview = Vwrld
**
** substitute into (1)
**                                         -1
** (4) Vshadow = Mwrld-shadow * Mwrld-camera * Vview
**
** project shadow
**                                                         -1
** (5) Vproj-shadow = Pshadow * (Mwrld-shadow * Mwrld-camera ) * Vview
**
** aaah! same thing :-)
**
** ---------------------------------------------------------------------------------
**
** Shadow mapping:  from pre-projected view coordinates back to obj space
** then to shadow space
** 
** (1) Vshadow = PShadow * Mwrld-shadow * Mobj-wrld * Vobj
** 
** (2) Vview = Mwrld-camera * Mobj-wrld * Vobj
**             -1             -1
** (3) Mobj-wrld * Mwrld-camera * Vview = Vobj
**                                                            -1             -1
** (4) Vshadow = PShadow * Mwrld-shadow * Mobj-wrld * Mobj-wrld * Mwrld-camera * Vview
**                                                   -1
** (5) Vshadow = PShadow * Mwrld-shadow * Mvrld-camera * Vview
**
**
** Ideas:
** - Use Texture Projectors to implement spot lights and stained glass windows
** - Attenuate texture projections with distance from the projector
** - Should be able to handle lots of pre-calculated static texture projectors.  They
**   should cull well and we can pre-generate the textures. 
**
** Ideas maybe used in conjunction with texture projections:
** - Light volumes: the problem is when the volume is cliped it looks funny, we can
**   fill in the clipped face of a non-translucent object by rendering the backfaces
** - Use the backface-fill to make the camera slicing through the commando look like
**   its *really* slicing through the commando :-)
** - The back-face-fill trick might be able to use el-cheapo screen mapping!
**  
*/


/***********************************************************************************************
 * TexProjectClass::TexProjectClass -- Constructor                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/4/00     gth : Created.                                                                 *
 *=============================================================================================*/
// ?TexProjectClass::TexProjectClass present-unmatched
TexProjectClass::TexProjectClass(void) :
	Flags(DEFAULT_FLAGS),
	DesiredIntensity(1.0f),
	Intensity(1.0f),
	Attenuation(1.0f),
	MaterialPass(NULL),
	Mapper1(NULL),
	RenderTarget(NULL),
	DepthStencilTarget(NULL),
	HFov(90.0f),
	VFov(90.0f),
	XMin(-10.0f),
	XMax(10.0f),
	YMin(-10.0f),
	YMax(10.0f),
	ZNear(1.0f),
	ZFar(1000.0f)
{
	// create a material pass class
	MaterialPass = NEW_REF(MaterialPassClass,()); 
	MaterialPass->Set_Cull_Volume(&WorldBoundingVolume);

	// create a vertex material
	VertexMaterialClass * vmtl = NEW_REF(VertexMaterialClass,());
	WWASSERT(vmtl != NULL);
	
	// Plug our parent's mapper into our vertex material
	// the mapper for stage1 will be allocated as needed
	vmtl->Set_Mapper(Mapper);

	MaterialPass->Set_Material(vmtl);
	vmtl->Release_Ref();
	vmtl = NULL;

	// by default init our material pass to be multiplicative (shadow)
	Init_Multiplicative();
}


/***********************************************************************************************
 * TexProjectClass::Compute_Perspective_Projection -- Set up a perspective projection of an ob *
 *                                                                                             *
 * This function automates the process of generating the perspective parameters needed to      *
 * tightly bound the projection of an object.                                                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 * model - object which we are created a projection of                                         *
 * lightpos - positional light source                                                          *
 * znear - distance to near clipping plane for the projection (if -1.0, will be generated)     *
 * zfar - distance to far clipping plane for the projection (if -1.0, will be generated)       *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/11/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool TexProjectClass::Compute_Perspective_Projection
(
	RenderObjClass *	model,
	const Vector3 &	lightpos,
	float					znear,
	float					zfar
)
{
	if (model == NULL) {
		WWDEBUG_SAY(("Attempting to generate projection for a NULL model\r\n"));
		return false;
	}

	AABoxClass box;
	model->Get_Obj_Space_Bounding_Box(box);
	const Matrix3D & tm = model->Get_Transform();
	
	return Compute_Perspective_Projection(box,tm,lightpos,znear,zfar);
}


/***********************************************************************************************
 * TexProjectClass::Compute_Perspective_Projection -- Set up a perspective projection of an ob *
 *                                                                                             *
 * This function automates the process of generating the perspective parameters needed to      *
 * tightly bound the projection of an object.                                                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 * obj_box - object space bounding box of the object we are projecting                         *
 * tm - transform of the object we are projecting                                              *
 * lightpos - positional light source                                                          *
 * user_znear - distance to near clipping plane for the projection (if -1.0, will be generated)*
 * user_zfar - distance to far clipping plane for the projection (if -1.0, will be generated)  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/11/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool TexProjectClass::Compute_Perspective_Projection
(
	const AABoxClass & obj_box,
	const Matrix3D & tm,
	const Vector3 & lightpos,
	float user_znear,
	float user_zfar
)
{
	/*
	** Compute the center of the box in world-space
	*/
	Vector3 wrld_center;
	Matrix3D::Transform_Vector(tm,obj_box.Center,&wrld_center);

	/*
	** Create a camera transform looking at the object.
	** Set this as our transform later in this routine.
	*/
	Matrix3D texture_tm,texture_tm_inv;
	texture_tm.Look_At(lightpos,wrld_center,0.0f);
	texture_tm.Get_Orthogonal_Inverse(texture_tm_inv);

	/*
	** Calculate the axis-aligned bounding box of the model in the camera's coordinate system.
	*/
	AABoxClass box = obj_box;
	Matrix3D obj_to_world = tm;
	Matrix3D obj_to_texture;
	Matrix3D::Multiply(texture_tm_inv,obj_to_world,&obj_to_texture);
	box.Transform(obj_to_texture);

	/*
	** If the box is behind the viewpoint or the viewpoint is inside the box
	** our FOV will be > 180 degrees. Have to give up
	*/
	if ((box.Center.Z > 0.0f) || (box.Extent.Z > WWMath::Fabs(box.Center.Z))) {
		return false;
	}
	
	/*
	** Compute the frustum parameters. Remember that our z coordinates are negative but the
	** projection code needs positive z distances.
	*/
	float znear = -box.Center.Z; //-(box.Center.Z + obj_box.Extent.Quick_Length());
	float zfar = -(box.Center.Z - obj_box.Extent.Quick_Length()) * 2.0f;

	if (user_znear != -1.0f) {
		znear = box.Center.Z + user_znear;
	}
	if (user_zfar != -1.0f) {
		zfar = box.Center.Z + user_zfar;
	}

	float tan_hfov2 = WWMath::Fabs(box.Extent.X / (box.Center.Z + box.Extent.Z));
	float tan_vfov2 = WWMath::Fabs(box.Extent.Y / (box.Center.Z + box.Extent.Z));
	float hfov = 2.0f * WWMath::Atan(tan_hfov2);
	float vfov = 2.0f * WWMath::Atan(tan_vfov2);

	/*
	** Plug in the results.  
	*/
	Set_Perspective_Projection(hfov,vfov,znear,zfar);
	Set_Transform(texture_tm);
	return true;
}


/***********************************************************************************************
 * TexProjectClass::Compute_Ortho_Projection -- Automatic Orthographic projection              *
 *                                                                                             *
 * Generates the orthographic projection parameters to tightly bound an object                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 * model - object which we are created a projection of                                         *
 * lightdir - directional light source                                                         *
 * znear - distance to near clipping plane for the projection (if -1.0, will be generated)     *
 * zfar - distance to far clipping plane for the projection (if -1.0, will be generated)       *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/11/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool TexProjectClass::Compute_Ortho_Projection
(
	RenderObjClass *	model,
	const Vector3 &	lightdir,
	float					znear,
	float					zfar
)
{
	if (model == NULL) {
		WWDEBUG_SAY(("Attempting to generate projection for a NULL model\r\n"));
		return false;
	}

	AABoxClass box;
	model->Get_Obj_Space_Bounding_Box(box);
	const Matrix3D & tm = model->Get_Transform();

	return Compute_Ortho_Projection(box,tm,lightdir,znear,zfar);
}


/***********************************************************************************************
 * TexProjectClass::Compute_Ortho_Projection -- Automatic Orthographic projection              *
 *                                                                                             *
 * Generates the orthographic projection parameters to tightly bound an object                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 * obj_box - object space bounding box of the object we are projecting                         *
 * tm - transform of the object we are projecting                                              *
 * lightdir - directional light                                                                *
 * user_znear - distance to near clipping plane for the projection (if -1.0, will be generated)*
 * user_zfar - distance to far clipping plane for the projection (if -1.0, will be generated)  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/11/00    gth : Created.                                                                 *
 *=============================================================================================*/
bool TexProjectClass::Compute_Ortho_Projection
(
	const AABoxClass & obj_box,
	const Matrix3D & tm,
	const Vector3 & lightdir,
	float user_znear,
	float user_zfar
)
{
	/*
	** Compute the center of the box in world-space
	*/
	AABoxClass wrldbox = obj_box;
	wrldbox.Transform(tm);

	/*
	** Create a camera transform looking at the object.
	** Set this as our transform later in this routine.
	*/
	Vector3 camera_target = wrldbox.Center;
	Vector3 camera_position = camera_target - 2.0f * wrldbox.Extent.Length() * lightdir;

	Matrix3D texture_tm,texture_tm_inv;
	texture_tm.Look_At(camera_position,camera_target,0.0f);
	texture_tm.Get_Orthogonal_Inverse(texture_tm_inv);

	/*
	** Calculate the axis-aligned bounding box of the model in the camera's coordinate system.
	*/
	AABoxClass box = obj_box;
	Matrix3D obj_to_world = tm;
	Matrix3D obj_to_texture;
	Matrix3D::Multiply(texture_tm_inv,obj_to_world,&obj_to_texture);
	box.Transform(obj_to_texture);

	/*
	** Expand the box to help with bounding box errors
	*/
	box.Extent *= 1.0f;

	/*
	** Compute the frustum parameters.  Note that znear and zfar are supposed to
	** be positive distances for the projection code.
	*/
	float znear = -box.Center.Z; //-(box.Center.Z + obj_box.Extent.Quick_Length());
	float zfar = -(box.Center.Z - obj_box.Extent.Quick_Length()) * 2.0f;

	if (user_znear != -1.0f) {
		znear = -box.Center.Z + user_znear;
	}
	if (user_zfar != -1.0f) {
		zfar = -box.Center.Z + user_zfar;
	}

	/*
	** All done!
	*/
	Set_Ortho_Projection(	box.Center.X - box.Extent.X,
									box.Center.X + box.Extent.X,
									box.Center.Y - box.Extent.Y,
									box.Center.Y + box.Extent.Y,
									znear,
									zfar	);
	Set_Transform(texture_tm);
	return true;
}

/***********************************************************************************************
 * TexProjectClass::Compute_Texture -- Generates texture by rendering an object                *
 *                                                                                             *
 * INPUT:                                                                                      *
 * model - pointer to the render object to generate a shadow texture for                       *
 * context - shadow render context which has been initialized to <TextureSize> resolution      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/11/00    gth : Created.                                                                 *
 *   5/16/02    kjm : Added optional custom depth/stencil target										  *
 *=============================================================================================*/
bool TexProjectClass::Compute_Texture
(
	RenderObjClass * model,
	SpecialRenderInfoClass * context
)
{
	if ((model == NULL) || (context == NULL)) 
	{
		return false;
	}
	/*
	** Render to texture
	*/
	TextureClass * rtarget=NULL;
	ZTextureClass* ztarget=NULL;

	Peek_Render_Target(&rtarget,&ztarget);

	if (rtarget != NULL) 
	{
		// set projector for render context KJM
		context->Texture_Projector=this;

		/*
		** Set the render target
		*/
		DX8Wrapper::Set_Render_Target_With_Z (rtarget,ztarget);

		/*
		** Set up the camera
		*/
		Configure_Camera(context->Camera);
		
		/*
		** Render the object
		*/
		Vector3 color(0.0f,0.0f,0.0f);
		if (Get_Flag(ADDITIVE) == false) {
			color.Set(1.0f,1.0f,1.0f);
		}

		bool zclear=ztarget!=NULL;

		bool snapshot=WW3D::Is_Snapshot_Activated();
		SNAPSHOT_SAY(("TexProjectCLass::Begin_Render()\n"));
		WW3D::Begin_Render(true,zclear,color);	// false to zclear as we don't have z-buffer
		WW3D::Render(*model,*context);
		SNAPSHOT_SAY(("TexProjectCLass::End_Render()\n"));
		WW3D::End_Render(false);
		WW3D::Activate_Snapshot(snapshot);	// End_Render() ends the shapsnot, so restore the state

		DX8Wrapper::Set_Render_Target((IDirect3DSurface8 *)NULL);

	}

#if 0

	/*
	** Render the object with the BW Renderer into our color surface
	*/
	BWRenderClass bwr((unsigned char*)shadow_surface->getDataPtr(),tex_size);
	bwr.Fill(0xff);
	context->BWRenderer = &bwr;
	model->Special_Render(*context);
	context->BWRenderer = NULL;
#endif
	return true;
}


/***********************************************************************************************
 * TexProjectClass::Set_Render_Target -- Install a render target for this projector to use     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/16/2001  gth : Created.                                                                 *
 *=============================================================================================*/
void TexProjectClass::Set_Render_Target
(
	TextureClass* render_target,
	ZTextureClass* zbuffer
)
{
	REF_PTR_SET(RenderTarget,render_target);
	Set_Texture(RenderTarget);
	REF_PTR_SET(DepthStencilTarget,zbuffer);
}

/***********************************************************************************************
 * TexProjectClass::Peek_Render_Target -- Returns pointer to the render target if we have one  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/5/2001   gth : Created.                                                                 *
 *   5/16/2002  kjm : Added optional custom zbuffer                                            *
 *=============================================================================================*/
TextureClass* TexProjectClass::Peek_Render_Target
(
	TextureClass** rtarget, 
	ZTextureClass** ztarget
)
{
	// some uses of this function just want to know if a render target exists
	if (rtarget==NULL) return RenderTarget;
	
	*rtarget=RenderTarget;

	// don't set if pointer isn't supplied
	if (ztarget!=NULL)
		*ztarget=DepthStencilTarget;

	return RenderTarget;
}

