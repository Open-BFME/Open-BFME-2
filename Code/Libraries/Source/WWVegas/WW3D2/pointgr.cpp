// cl: /I. /Ireference/shims/banked_segline /Ireference/shims/bfmestages /DBFME_WWSTRING_CTOR_BUFFER_RELOAD /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/banked_segline  /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4; neutralize the old name in this TU
// so mapper.h (forward-decls class Matrix4x4) and camera.h agree. No matched
// function mangles Matrix4x4 (verified), so this is a pure rename.
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
#define Matrix4x4 Matrix4

#define BFME_POINT_MATRIX4_TRANSFORM_INLINE
#include "reference/shims/bfme_vector3_len_link/vector3_len_link.h"
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#define BFME_MATRIX4_INCLASS_DEFAULT_CTOR
#include "reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
// Preload headers that reset optimization before selecting the standalone DX8 copies.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "wwstring.h"
#include "shader.h"
#pragma optimize("s", on)
#include "reference/shims/banked_segline/dx8wrapper.h"
#pragma optimize("", on)


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
 *                 Project Name : G                                        * 
 *                                                                         * 
 *                     $Archive:: /VSS_Sync/ww3d2/pointgr.cpp             $* 
 *                                                                         * 
 *                    Org Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 38                                      $* 
 *                                                                         * 
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 *   PointGroupClass::PointGroupClass -- PointGroupClass CTor.             * 
 *   PointGroupClass::~PointGroupClass -- PointGroupClass DTor.            * 
 *   PointGroupClass::operator = -- PointGroupClass assignment operator.   * 
 *   PointGroupClass::Set_Arrays -- Set point location/color/enable arrays.* 
 *   PointGroupClass::Set_Point_Size -- Set default point size.            * 
 *   PointGroupClass::Get_Point_Size -- Get default point size.            * 
 *   PointGroupClass::Set_Point_Color -- Set default point color.          * 
 *   PointGroupClass::Get_Point_Color -- Get default point color.          * 
 *   PointGroupClass::Set_Point_Alpha -- Set default point alpha.          * 
 *   PointGroupClass::Get_Point_Alpha -- Get default point alpha.          * 
 *   PointGroupClass::Set_Point_Orientation -- Set default point orientatio* 
 *   PointGroupClass::Get_Point_Orientation -- Get default point orientatio* 
 *   PointGroupClass::Set_Point_Frame -- Set default point frame.          * 
 *   PointGroupClass::Get_Point_Frame -- Get default point frame.          * 
 *   PointGroupClass::Set_Point_Mode -- Set point rendering method.        * 
 *   PointGroupClass::Get_Point_Mode -- Get point rendering method.        * 
 *   PointGroupClass::Set_Flag -- Set given flag to on or off.             * 
 *   PointGroupClass::Get_Flag -- Get current value (on/off) of given flag.* 
 *   PointGroupClass::Set_Texture -- Set texture used.                     * 
 *   PointGroupClass::Get_Texture -- Get texture used.                     * 
 *   PointGroupClass::Set_Shader -- Set shader used.                       * 
 *   PointGroupClass::Get_Shader -- Get shader used.                       * 
 *   PointGroupClass::Set_Billboard -- Set whether to billboard.           *
 *   PointGroupClass::Get_Billboard -- Get whether to billboard.           *
 *   PointGroupClass::Get_Discrete_Orientation_Count_Log2 -- what it says  * 
 *   PointGroupClass::Set_Discrete_Orientation_Count_Log2 -- what it says. * 
 *   PointGroupClass::Get_Frame_Row_Column_Count_Log2 -- what it says      * 
 *   PointGroupClass::Set_Frame_Row_Column_Count_Log2 -- what it says.     * 
 *   PointGroupClass::Get_Polygon_Count -- Get estimated polygon count.    * 
 *   PointGroupClass::Render -- draw point group.                          * 
 *   PointGroupClass::vInstance -- Create instance of class.               * 
 *   PointGroupClass::sGetClassName -- Get name of class.                  * 
 *   PointGroupClass::Update_Arrays -- Update all arrays used in rendering *
 *   PointGroupClass::Peek_Texture -- Peeks texture                        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "vector.h"
#include "vector2.h"
template <> bool VectorClass<Vector2>::Resize(int, Vector2 const *);
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
template <> bool VectorClass<Vector4>::Resize(int, Vector4 const *);
extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector4> VertexDiffuse;
void Rva00912CF0();
// TU-scoped PointGroup declaration from the committed BFME1 pointgr.h;
// BFME2 helper declarations added without changing the measured 0x5C layout.
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
 *                 Project Name : G                                        *
 *                                                                         *
 *                     $Archive:: /Commando/Code/ww3d2/pointgr.h          $*
 *                                                                         *
 *                      $Author:: Naty_h                                  $*
 *                                                                         *
 *                     $Modtime:: 8/02/01 8:34p                           $*
 *                                                                         *
 *                    $Revision:: 10                                      $*
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef POINTGR_H
#define POINTGR_H

#include "sharebuf.h"
#include "shader.h"
#include "vector4.h"
#include "vector3.h"
#include "vector2.h"
#include "vector.h"

class VertexMaterialClass;
class RenderInfoClass;
class TextureClass;

/*
** PointGroupClass -- a custom object for rendering
** groups of points (such as particle systems).
** It is possible to change mode/number of points/shader/etc. but these
** changes tend to be expensive if done often. Expected usage is to set the
** point location/color/active arrays each frame the object is visible (with
** the same number of points) and perform other changes relatively rarely.
** NOTE: Currently it is implemented using general triangles (1 or 2 per
** point), so it is probably suboptimal for software rasterization devices
** (which would probably perform better with some kind of blit/sprite code).
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
class PointGroupClass
{
public:

	enum PointModeEnum {
		TRIS,			// each point is a triangle
		QUADS,		// each point is a quad formed out of two triangles
		SCREENSPACE	// each point is a tri placed to affect certain pixels (should be used with 2D camera)
	};

	enum FlagsType {
		TRANSFORM,	// transform points w. modelview matrix (worldspace points)
		// BFME drift: a second flag exists; the ParticleBufferClass ctor sets it
		// unconditionally right after TRANSFORM (0x989130 pushes 1,1). Presumed to
		// be the billboard toggle that replaced the removed Billboard member.
		BILLBOARD,
	};

	PointGroupClass(void);

 friend void ::Rva00912CF0();
 void rva00916CD0(unsigned char *,int,int);
 void prepare_shader();
 __declspec(noinline) inline void rva00917920(Vector3 **,Vector4 **,float **,unsigned char **,unsigned char **);
 void rva009148C0(Vector3 *,float *,unsigned char *,int);
 void rva00912880(Vector4 *,int);
 void RenderVolumeParticle(RenderInfoClass &,unsigned int,void *);

 void rva00914860(int,int,int *);
 void rva00917B10(Vector3 *,Vector4 *,float *,unsigned char *,unsigned char *,
                  int,int,int *,int);

	virtual ~PointGroupClass(void);
	PointGroupClass & operator = (const PointGroupClass & that);

	// PointGroupClass interface:
	void						Set_Arrays(ShareBufferClass<Vector3> *locs,
									ShareBufferClass<Vector4> *diffuse = NULL,
									ShareBufferClass<unsigned int> *apt = NULL,
									ShareBufferClass<float> *sizes = NULL,
									ShareBufferClass<unsigned char> *orientations = NULL,
									ShareBufferClass<unsigned char> *frames = NULL,
									int active_point_count = -1,
									float vpxmin = 0.0f, float vpymin = 0.0f,
									float vpxmax = 0.0f, float vpymax = 0.0f);
	void						Set_Point_Size(float size);
	float						Get_Point_Size(void);
	void						Set_Point_Color(Vector3 color);
	Vector3					Get_Point_Color(void);
	void						Set_Point_Alpha(float alpha);
	float						Get_Point_Alpha(void);
	void						Set_Point_Orientation(unsigned char orientation);
	unsigned char		Get_Point_Orientation(void);
	void						Set_Point_Frame(unsigned char frame);
	unsigned char		Get_Point_Frame(void);
	void						Set_Point_Mode(PointModeEnum mode);
	PointModeEnum		Get_Point_Mode(void);
	void						Set_Flag(FlagsType flag, bool onoff);
	int							Get_Flag(FlagsType flag);
	void						Set_Texture(TextureClass* texture);
	TextureClass * 	Get_Texture(void);
	TextureClass * 	Peek_Texture(void);
	void						Set_Shader(ShaderClass shader);
	ShaderClass			Get_Shader(void);
	// BFME drift: no Billboard member — retail PointGroupClass is 0x5C bytes and
	// its ctor (0x912580) initializes VPYMax at +0x58 as the last member.

	// The frame property is taken from a set of possible frames. The rows/columns in the frame
	// texture determine the number of possible frames. Since it must be a power of 2, we represent
	// it as its log base 2. This number cannot be greater than 4 (which corresponds to a 16x16
	// square of frames, i.e. 256 frames).
	unsigned char			Get_Frame_Row_Column_Count_Log2(void);
	void						Set_Frame_Row_Column_Count_Log2(unsigned char frccl2);

	int						Get_Polygon_Count(void);

	// BFME drift: Render grew a second parameter (Render_Particles at 0x98B800
	// pushes an extra 0 before rinfo).
	void						Render(RenderInfoClass &rinfo, int unknown);
	void						RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth);
	void						rva00913AF0(int vnum, bool no_diffuse);

protected:
	// Update arrays.
	void						Update_Arrays(Vector3 *point_loc,
									Vector4 *point_diffuse,
									float *point_size,
									unsigned char *point_orientation,
									unsigned char *point_frame,
									int active_points,
									int total_points,
									int &vnum,
									int &pnum);

	// These shared buffers are used for communication to the point group - to
	// pass point locations, colors and enables. The location and color arrays
	// are 'compressed' using the active point table (if present) and then
	// are processed into other arrays which are passed to the GERD.
	// SR rather than WWMath types are used so Vector Processors can be used.
	// The arrays override the default value if present.
	// The orientation and frame properties are "index properties": they select one out of a small
	// group of possibilities for each point.
	// Orientation: this is the 2D rotation of the point about its center. There are 256 discrete
	// orientations. The unit circle is evenly subdivided 256 times to create the set of
	// orientations. The reason we discretize orientation is for performance: this way we can
	// precalculate vertex offsets.
	// Frame: the texture is divided into a 2D square grid, and each point uses one grid square
	// instead of the whole texture. The number of possible frames is not invariant - it depends
	// on the number of rows / columns in the grid. The reason we do this instead of having
	// different textures is to avoid texture state changes. Also for performance reasons, the
	// number of possible frames must be a power of two - for this reason the number of frame rows
	// and columns, orientations, etc. are represented as the log base 2 of the actual number.
	ShareBufferClass<Vector3> *			PointLoc;	// World/cameraspace point locs
	ShareBufferClass<Vector4> *			PointDiffuse; // (NULL if not used) RGBA values
	ShareBufferClass<unsigned int> *		APT;			// (NULL if not used) active point table
	ShareBufferClass<float> *				PointSize;	// (NULL if not used) size override table
	ShareBufferClass<unsigned char> *	PointOrientation; // (NULL if not used) orientation indices
	ShareBufferClass<unsigned char> *	PointFrame; // (NULL if not used) frame indices
	int											PointCount;	// Active (if APT) or total point count

	// See comments for Get/Set_Frame_Row_Column_Count_Log2 above
	unsigned char			FrameRowColumnCountLog2;		// MUST be equal or lesser than 4

	// These parameters are passed to the GERD:
	TextureClass*			Texture;
	ShaderClass				Shader;					// (default created in CTor)

	// Internal state:
	PointModeEnum			PointMode;					// are points tris or quads?
	unsigned int			Flags;						// operation control flags
	float						DefaultPointSize;			// point size (size array overrides if present)
	Vector3					DefaultPointColor;		// point color (color array overrides if present)
	float						DefaultPointAlpha;		// point alpha (alpha array overrides if present)
	unsigned char			DefaultPointOrientation;// point orientation (orientation array overrides if present)
	unsigned char			DefaultPointFrame;		// point texture frame (frame array overrides if present)

	// View plane rectangle (only used in SCREENSPACE mode - set by Set_Arrays
	// and used in Update_GERD_Arrays).
	float						VPXMin;
	float						VPYMin;
	float						VPXMax;
	float						VPYMax;


	// Static stuff:
	// For performance / memory reasons we prepare vertex location and UV
	// arrays for various orientations and texture frames, as static data
	// members of this class. This avoids the need to create such arrays over
	// again for each object. The values in the UV arrays are used as-is, the
	// values in the location arrays normally need to be scaled to the point
	// sizes and added to the point location before use. We have distinct sets
	// of arrays for each point mode.
	// There are tables of vertex positions for each of triangle and quad mode
	// with 256 discrete orientations. Each entry contains 3 (for triangle
	// mode) or 4 (for quad mode) Vector3s.
	// There are five tables of texture UVs for each of triangle and quad mode:
	// with 1x1(1), 2x2(4), 4x4(16), 8x8(64) and 16x16(256) frames. Each entry
	// contains 3 (for triangle mode) or 4 (for quad mode) Vector2s.
	// In addition, there is one array of vertex positions for screenspace mode
	// with 2 entries (for size 1 and size 2). Each entry contains 3 Vector3s.
	// the Init function (which is called by WW3D::Init()) creates these
	// arrays, and the Shutdown function (which is called by WW3D::Shutdown()
	// releases them.
public:
	static void				_Init(void);
	static void				_Shutdown(void);

private:
	static Vector3 _TriVertexLocationOrientationTable[256][3];
	static Vector3 _QuadVertexLocationOrientationTable[256][4];
	static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
	static Vector2 *_TriVertexUVFrameTable[5];
	static Vector2 *_QuadVertexUVFrameTable[5];
	static VertexMaterialClass *PointMaterial;

	// Static arrays for intermediate calcs (never resized down, just up):
	static VectorClass<Vector3>		compressed_loc;		// point locations 'compressed' by APT
	static VectorClass<Vector4>		compressed_diffuse;	// point colors 'compressed' by APT
	static VectorClass<float>			compressed_size;		// point sizes 'compressed' by APT
	static VectorClass<unsigned char>	compressed_orient;	// point orientations 'compressed' by APT
	static VectorClass<unsigned char>	compressed_frame;		// point frames 'compressed' by APT
	static VectorClass<Vector3>		transformed_loc;		// transformed point locations
};


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
class SegmentGroupClass : public PointGroupClass
{
public:
	SegmentGroupClass(void);
	virtual ~SegmentGroupClass(void);

};



#endif

#include "vertmaterial.h"
#include "ww3d.h"
#include "aabox.h"
#include "statistics.h"
#include "simplevec.h"
#include "vector.h"
#include "vp.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
class CameraClass;
#include "rinfo.h"
#include "camera.h"
#include "dx8fvf.h"
#include "D3dx8math.h"
#include "sortingrenderer.h"
// bfme link decl-only begin
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
template <> bool VectorClass<float>::operator==(VectorClass<float> const &) const;
template <> bool VectorClass<Vector2>::operator==(VectorClass<Vector2> const &) const;
template <> int VectorClass<float>::ID(float const &);
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
// Declaring the dtor only stops cl synthesizing this unit's scalar deleting
// destructor copy, which inlines Clear; retail's, 0x000F1CF7 (rowed in
// vector_class_vector3_ctor.cpp), calls it. Clear stays inline for
// Rva00912CF0, which retail expands it in.
template <> VectorClass<Vector3>::~VectorClass();
// bfme link decl-only end
// The table's operator== and both IDs are retail's /O1 bodies 0x000F1C16,
// 0x000F0DC5 and 0x000F0E20, emitted with the vtable by
// vector_class_vector3_ctor.cpp.
template <> int VectorClass<Vector3>::ID(Vector3 const *);
template <> int VectorClass<Vector3>::ID(Vector3 const &);
template <> bool VectorClass<Vector3>::operator==(VectorClass<Vector3> const &) const;

// Retail Vector2/Vector4 resize bodies belong to Vector2Resize.cpp.
// Declare their specializations so this consumer references those owners.
template <> bool VectorClass<Vector2>::Resize(int newsize, Vector2 const *array);
template <> bool VectorClass<Vector4>::Resize(int newsize, Vector4 const *array);

// Upgraded to DX8 2/2/01 HY

// static data members
Vector3 PointGroupClass::_TriVertexLocationOrientationTable[256][3];
Vector3 PointGroupClass::_QuadVertexLocationOrientationTable[256][4];
Vector2 *PointGroupClass::_TriVertexUVFrameTable[5] = { NULL, NULL, NULL, NULL, NULL};
Vector2 *PointGroupClass::_QuadVertexUVFrameTable[5] = { NULL, NULL, NULL, NULL, NULL};
VertexMaterialClass *PointGroupClass::PointMaterial=NULL;

// Static arrays for intermediate calcs (never resized down, just up):
VectorClass<Vector3>		PointGroupClass::compressed_loc;		// point locations 'compressed' by APT
VectorClass<Vector4>		PointGroupClass::compressed_diffuse;	// point colors 'compressed' by APT
VectorClass<float>			PointGroupClass::compressed_size;		// point sizes 'compressed' by APT
VectorClass<unsigned char>	PointGroupClass::compressed_orient;	// point orientations 'compressed' by APT
VectorClass<unsigned char>	PointGroupClass::compressed_frame;		// point frames 'compressed' by APT
VectorClass<Vector3>		PointGroupClass::transformed_loc;		// transformed point locations

// This array has vertex locations for screenspace mode - calculated to cover exactly 1x1 and 2x2 pixels.
Vector3 PointGroupClass::_ScreenspaceVertexLocationSizeTable[2][3] =
{
	Vector3(0.5f, 0.0f, -1.0f), 
	Vector3(1.0f, 1.0f, -1.0f),
	Vector3(0.0f, 1.0f, -1.0f), 
	Vector3(1.0f, -0.5f, -1.0f),
	Vector3(2.7f, 2.0f, -1.0f), 
	Vector3(-0.7f, 2.0f, -1.0f)
};

// useful for particles that aren't aligned with the screen.
static Vector3 GroundMultiplierX(1.0f, 0.0f, 0.0f);
static Vector3 GroundMultiplierY(0.0f, 1.0f, 0.0f);

// Some internal variables
VectorClass<Vector3>			VertexLoc;		// camera-space vertex locations
VectorClass<Vector4>			VertexDiffuse;	// vertex diffuse/alpha colors
static VectorClass<Vector2>			VertexUV;		// vertex texture coords

// Some DX 8 variables
#define MAX_VB_SIZE			2048
#define MAX_TRI_POINTS		MAX_VB_SIZE/3
#define MAX_TRI_IB_SIZE		3*MAX_TRI_POINTS
#define MAX_QUAD_POINTS		MAX_VB_SIZE/4
#define MAX_QUAD_IB_SIZE	6*MAX_QUAD_POINTS

DX8IndexBufferClass			*Tris, *Quads;						// Index buffers.
SortingIndexBufferClass		*SortingTris, *SortingQuads;	// Sorting index buffers.

/************************************************************************** 
 * PointGroupClass::PointGroupClass -- PointGroupClass CTor.              * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
PointGroupClass::PointGroupClass(void) :
	PointLoc(NULL),
	PointDiffuse(NULL),	
	APT(NULL),
	PointSize(NULL),
	PointOrientation(NULL),
	PointFrame(NULL),
	PointCount(0),
	FrameRowColumnCountLog2(0),
	Texture(NULL),
	Flags(0),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	PointMode(TRIS),
	DefaultPointSize(0.0f),
	DefaultPointColor(1.0f, 1.0f, 1.0f),
	DefaultPointAlpha(1.0f),	
	DefaultPointOrientation(0),
	DefaultPointFrame(0),
	VPXMin(0.0f),
	VPYMin(0.0f),
	VPXMax(0.0f),
	VPYMax(0.0f)
{
}

/************************************************************************** 
 * PointGroupClass::~PointGroupClass -- PointGroupClass DTor.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// PointGroupClass::~PointGroupClass: defined in PointGroupClassDestructor.cpp (its row's unit).

/************************************************************************** 
 * PointGroupClass::operator = -- PointGroupClass assignment operator.    * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::operator= present-unmatched
PointGroupClass & PointGroupClass::operator = (const PointGroupClass & that)
{
	if (this != &that) {
		WWASSERT(0);	// If you hit this assert implement the function!
	}
	return *this;
}


/************************************************************************** 
 * PointGroupClass::Set_Arrays -- Set point location/color/enable arrays. * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * NOTES:	colors, alphas, APT, sizes, orientations and frames are       *
 *          optional. active_point_count can also be used with a NULL apt.*
 *          In this case active_point_count is ignored if it is -1        *
 *          (default value) and otherwise it indicates the first N active *
 *          points in the arrays.                                         * 
 *          The view plane rectangle may optionally be passed as well -   * 
 *				this is only used in SCREENSPACE mode.                        * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *   08/25/1999 NH  : Alphas added.                                       * 
 *   06/28/2000 NH  : Orientations and frames added.                      * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
void PointGroupClass::Set_Arrays(
	ShareBufferClass<Vector3> *locs,
	ShareBufferClass<Vector4> *diffuse,		
	ShareBufferClass<unsigned int> *apt,
	ShareBufferClass<float> *sizes,
	ShareBufferClass<unsigned char> *orientations,
	ShareBufferClass<unsigned char> *frames, 
	int active_point_count,
	float vpxmin, 
	float vpymin, 
	float vpxmax, 
	float vpymax)
{
	// The point locations array is NOT optional!
	WWASSERT(locs);

	// Ensure lengths of all arrays are the same:
	WWASSERT(!diffuse || locs->Get_Count() == diffuse->Get_Count());
	WWASSERT(!apt || locs->Get_Count() == apt->Get_Count());
	WWASSERT(!sizes || locs->Get_Count() == sizes->Get_Count());
	WWASSERT(!orientations || locs->Get_Count() == orientations->Get_Count());
	WWASSERT(!frames || locs->Get_Count() == frames->Get_Count());

	REF_PTR_SET(PointLoc,locs);
	REF_PTR_SET(PointDiffuse,diffuse);
	REF_PTR_SET(APT,apt);
	REF_PTR_SET(PointSize,sizes);
	REF_PTR_SET(PointOrientation,orientations);
	REF_PTR_SET(PointFrame,frames);

	if (APT) {
		PointCount = active_point_count;
	} else {
		PointCount = (active_point_count >= 0) ? active_point_count : PointLoc->Get_Count();
	}

	// Store view plane rectangle (only used in SCREENSPACE mode)
	VPXMin = vpxmin;
	VPYMin = vpymin;
	VPXMax = vpxmax;
	VPYMax = vpymax;
}

/************************************************************************** 
 * PointGroupClass::Set_Point_Size -- Set default point size.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This size is ignored if a size array is present.             * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Size present-unmatched
void PointGroupClass::Set_Point_Size(float size)
{
	DefaultPointSize = size;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Size -- Get default point size.             * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This size is ignored if a size array is present.             * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Size present-unmatched
float PointGroupClass::Get_Point_Size(void)
{
	return DefaultPointSize;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Color -- Set default point color.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This color is ignored if a color array is present.           * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/20/1999 NH  : Created.                                            * 
 *========================================================================*/
void PointGroupClass::Set_Point_Color(Vector3 color)
{
	DefaultPointColor = color;
}

/************************************************************************** 
 * PointGroupClass::Get_Point_Color -- Get default point color.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This color is ignored if a color array is present.           * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/20/1999 NH  : Created.                                            * 
 *========================================================================*/
Vector3 PointGroupClass::Get_Point_Color(void)
{
	return DefaultPointColor;
}

/************************************************************************** 
 * PointGroupClass::Set_Point_Alpha -- Set default point alpha.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This alpha is ignored if an alpha array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   08/25/1999 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Alpha present-unmatched
void PointGroupClass::Set_Point_Alpha(float alpha)
{
	DefaultPointAlpha = alpha;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Alpha -- Get default point alpha.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This alpha is ignored if an alpha array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   08/25/1999 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Alpha present-unmatched
float PointGroupClass::Get_Point_Alpha(void)
{
	return DefaultPointAlpha;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Orientation -- Set default point orientation* 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This is ignored if an orientation array is present.          * 
 *                                                                        * 
 * NOTE: No need to ensure value in valid range - it will be masked later.*
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Orientation present-unmatched
void PointGroupClass::Set_Point_Orientation(unsigned char orientation)
{
	DefaultPointOrientation = orientation;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Orientation -- Get default point orientation* 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This is ignored if an orientation array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Orientation present-unmatched
unsigned char PointGroupClass::Get_Point_Orientation(void)
{
	return DefaultPointOrientation;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Frame -- Set default point frame.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This frame is ignored if an frame array is present.          * 
 *                                                                        * 
 * NOTE: No need to ensure value in valid range - it will be masked later.*
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Frame present-unmatched
void PointGroupClass::Set_Point_Frame(unsigned char frame)
{
	DefaultPointFrame = frame;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Frame -- Get default point frame.           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS: This frame is ignored if an frame array is present.          * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Frame present-unmatched
unsigned char PointGroupClass::Get_Point_Frame(void)
{
	return DefaultPointFrame;
}


/************************************************************************** 
 * PointGroupClass::Set_Point_Mode -- Set point rendering method.         * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Set_Point_Mode present-unmatched
void PointGroupClass::Set_Point_Mode(PointModeEnum mode)
{
	PointMode = mode;
}


/************************************************************************** 
 * PointGroupClass::Get_Point_Mode -- Get point rendering method.         * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// ?PointGroupClass::Get_Point_Mode present-unmatched
PointGroupClass::PointModeEnum PointGroupClass::Get_Point_Mode(void)
{
	return PointMode;
}


/************************************************************************** 
 * Set_Flag -- PointGroupClass::Set given flag to on or off.              * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
void PointGroupClass::Set_Flag(FlagsType flag, bool onoff)
{
	if (onoff) Flags|=1<<flag; 
	else 
		Flags&=~(1<<flag);
}

/************************************************************************** 
 * PointGroupClass::Get_Flag -- Get current value (on/off) of given flag. *
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *========================================================================*/
// Get_Flag is owned here with the consolidated render helpers.
inline int PointGroupClass::Get_Flag(FlagsType flag)
{
	return (Flags>>flag) & 0x1;
}

/************************************************************************** 
 * PointGroupClass::Set_Texture -- Set texture used.                      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Texture present-unmatched
void PointGroupClass::Set_Texture(TextureClass* texture)
{
	TextureClass **next = reinterpret_cast<TextureClass **>(texture);
	if (*next)
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(*next) + 4);
	if (Texture) {
		Texture->Release_Ref();
		Texture = *next;
	} else {
		Texture = *next;
	}
}

/************************************************************************** 
 * PointGroupClass::Get_Texture -- Get texture used.                      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Get_Texture present-unmatched
TextureClass * PointGroupClass::Get_Texture(void)
{
	if (Texture) Texture->Add_Ref();
	return Texture;
}


/***********************************************************************************************
 * PointGroupClass::Peek_Texture -- Peeks texture                                              *
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
 *   4/12/2001  hy : Created.                                                                  *
 *=============================================================================================*/
// ?PointGroupClass::Peek_Texture present-unmatched
TextureClass * PointGroupClass::Peek_Texture(void)
{
	return Texture;
}

/************************************************************************** 
 * PointGroupClass::Set_Shader -- Set shader used.                        * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:	the primary gradient will be set to MODULATE/DISABLE in    *
 * 				the shader depending on whether a color or alpha array was *
 * 				passed in Set_Point_Arrays. also, texturing will be        *
 * 				enabled or disabled dependent on whether a non-NULL        *
 * 				texture was set.                                           *
 *					these will override the primary gradient/texturing         *
 *					settings in the given shader.                              *
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Shader present-unmatched
void PointGroupClass::Set_Shader(ShaderClass shader)
{
	Shader = shader;
}


/************************************************************************** 
 * PointGroupClass::Get_Shader -- Get shader used.                        * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/17/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Get_Shader present-unmatched
ShaderClass PointGroupClass::Get_Shader(void)
{
	return Shader;
}

/************************************************************************** 
 * PointGroupClass::Set_Billboard -- Set whether to Billboard.            * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/25/2002 JM  : Created.                                            *
 *========================================================================*/
// BFME drift: PointGroupClass has no Billboard member (a BILLBOARD flag replaced
// it — see the ctor's Set_Flag usage), so Set_Billboard/Get_Billboard are absent.

/************************************************************************** 
 * PointGroupClass::Get_Billboard -- Get whether to Billboard.            * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   04/25/2002 JM  : Created.                                            *
 *========================================================================*/


/************************************************************************** 
 * PointGroupClass::Get_Frame_Row_Column_Count_Log2 -- what it says       * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     * 
 *========================================================================*/
// ?PointGroupClass::Get_Frame_Row_Column_Count_Log2 present-unmatched
unsigned char PointGroupClass::Get_Frame_Row_Column_Count_Log2(void)
{
	return FrameRowColumnCountLog2;
}


/************************************************************************** 
 * PointGroupClass::Set_Frame_Row_Column_Count_Log2 -- what it says.      * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   06/28/2000 NH  : Created.                                            *
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
// ?PointGroupClass::Set_Frame_Row_Column_Count_Log2 present-unmatched
void PointGroupClass::Set_Frame_Row_Column_Count_Log2(unsigned char frccl2)
{
	FrameRowColumnCountLog2 = MIN(frccl2, 4);
}

/************************************************************************** 
 * PointGroupClass::Get_Polygon_Count -- Get estimated polygon count.     * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   11/18/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
int PointGroupClass::Get_Polygon_Count(void)
{
	switch (PointMode) {
		case TRIS:
		case SCREENSPACE:
			return PointCount;
			break;
		case QUADS:
			return PointCount * 2;
			break;
	}
	WWASSERT(0);
	return 0;
}

/************************************************************************** 
 * PointGroupClass::Render -- draw point group.                           * 
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:                                                              * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   12/10/1998 NH  : Created.                                            * 
 *   02/08/2001 HY  : Upgraded to DX8                                     *
 *========================================================================*/
static SimpleVecClass<unsigned long> remap;
// PointGroupClass::Render is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRender.cpp (0x0017F400).






/************************************************************************** 
 * PointGroupClass::RenderVolumeParticles -- draw a point group.sandwich  * 
 *                                                                        * 
 *	This is a specialized renderer. It will draw the particle repeatedly  * 
 *  while attenuating opacity appropriately, and bumping the z-position.  *
 *  This is actually done by cloning the particle over and over at        * 
 *  successively closer positions to the camera. Very Slow!               *
 *                                                                        * 
 * INPUT:                                                                 * 
 *                                                                        * 
 * OUTPUT:                                                                * 
 *                                                                        * 
 * WARNINGS:      USE SPARINGLY, IT IS EXPENSIVE!!!!!                     * 
 *                                                                        * 
 * HISTORY:                                                               * 
 *   12/03/2002	Mark Lorenzen		Created.                                  * 
 *																		                                    *
 *========================================================================*/
#define MAX_VOLUME_PARTICLE_DEPTH ( 16 )
// ?PointGroupClass::RenderVolumeParticle present-unmatched
void PointGroupClass::RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth )
{
	// BFME match note: RenderVolumeParticle is the DX8/Direct3D render path — not reproducible
	// with the byte-match toolchain, so its body is stubbed to let the other
	// PointGroupClass methods compile and locate.
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
inline void PointGroupClass::rva00914860(int active_points,int total_points,int *vnum) {
  int verts_per_point = PointMode == QUADS ? 4 : 3;
  int total_vnum = verts_per_point * total_points;
  *vnum = verts_per_point * active_points;
  if (VertexLoc.Length() < total_vnum) {
   VertexLoc.Resize(total_vnum * 2, false);
   VertexUV.Resize(total_vnum * 2, false);
   VertexDiffuse.Resize(total_vnum * 2, false);
  }
 }
template <class T, class S>
static inline T *rva00917920_compress(VectorClass<T> &buffer, S *source, unsigned int *apt, int count)
{
	if (source) {
		if (buffer.Length() < count) {
			buffer.Resize(count * 2);
		}
		VectorProcessorClass::CopyIndexed(&buffer[0], source->Get_Array(), apt, count);
		return &buffer[0];
	}
	return NULL;
}

void PointGroupClass::rva00917920(Vector3 **point_loc, Vector4 **point_diffuse, float **point_size,
	unsigned char **point_orientation, unsigned char **point_frame)
{
	if (APT) {
		unsigned int *apt = APT->Get_Array();
		*point_loc = rva00917920_compress(compressed_loc, PointLoc, apt, PointCount);
		*point_diffuse = rva00917920_compress(compressed_diffuse, PointDiffuse, apt, PointCount);
		*point_size = rva00917920_compress(compressed_size, PointSize, apt, PointCount);
		*point_orientation = rva00917920_compress(compressed_orient, PointOrientation, apt, PointCount);
		*point_frame = rva00917920_compress(compressed_frame, PointFrame, apt, PointCount);
	} else {
		*point_loc = PointLoc->Get_Array();
		if (PointDiffuse) {
			*point_diffuse = PointDiffuse->Get_Array();
		}
		if (PointSize) {
			*point_size = PointSize->Get_Array();
		}
		if (PointOrientation) {
			*point_orientation = PointOrientation->Get_Array();
		}
		if (PointFrame) {
			*point_frame = PointFrame->Get_Array();
		}
	}
}


void PointGroupClass::Render(RenderInfoClass &rinfo, int unknown)
{
	if (PointCount == 0) return;

	prepare_shader();

	Vector3 *current_loc = NULL;
	Vector4 *current_diffuse = NULL;
	float *current_size = NULL;
	unsigned char *current_orient = NULL;
	unsigned char *current_frame = NULL;
	rva00917920(&current_loc, &current_diffuse, &current_size, &current_orient, &current_frame);

	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	if (Get_Flag(TRANSFORM) && Get_Flag(BILLBOARD)) {
		if (compressed_loc.Length() < PointCount) {
			compressed_loc.Resize(PointCount * 2);
		}
		Vector4 result;
		for (int i = 0; i < PointCount; i++) {
			result = view * current_loc[i];
			compressed_loc[i][0] = result[0];
			compressed_loc[i][1] = result[1];
			compressed_loc[i][2] = result[2];
		}
		current_loc = &compressed_loc[0];
	}

	int count = PointCount;
	int vnum;
	rva00914860(count, PointLoc->Get_Count(), &vnum);
	rva009148C0(current_loc, current_size, current_orient, count);
	rva00916CD0(current_frame, count, unknown);
	rva00912880(current_diffuse, count);
	rva00913AF0(vnum, current_diffuse == NULL);
}

void PointGroupClass::RenderVolumeParticle(RenderInfoClass &rinfo, unsigned int depth, void *unknown)
{
	if (depth <= 1 || !Get_Flag(TRANSFORM) || !Get_Flag(BILLBOARD)) {
		Render(rinfo, (int)unknown);
		return;
	}

	if (depth > 16)
		depth = 16;

	if (PointCount == 0)
		return;

	prepare_shader();

	Vector3 *current_loc = NULL;
	Vector4 *current_diffuse = NULL;
	float *current_size = NULL;
	unsigned char *current_orient = NULL;
	unsigned char *current_frame = NULL;
	rva00917920(&current_loc, &current_diffuse, &current_size, &current_orient, &current_frame);

	Vector3 *source_loc = current_loc;
	int vnum;
	rva00914860(PointCount, PointLoc->Get_Count(), &vnum);
	rva00912880(current_diffuse, PointCount);
	rva00916CD0(current_frame, PointCount, (int)unknown);

	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	if (transformed_loc.Length() < PointCount) {
		transformed_loc.Resize(PointCount * 2);
	}

	for (int t = 0; t < (int)depth; ++t) {
		float shiftInc = (float)t * 0.1f / (float)depth;
		Vector3 cameraPosition = ((RenderObjClass &)rinfo.Camera).Get_Position();
		for (int i = 0; i < PointCount; i++) {
			Vector3 cameraToPointDelta;
			Vector3::Subtract(cameraPosition, source_loc[i], &cameraToPointDelta);
			float len = cameraToPointDelta.Length();
			float scale = current_size[i] * shiftInc;
			scale /= len;
			cameraToPointDelta.X *= scale;
			cameraToPointDelta.Y *= scale;
			cameraToPointDelta.Z *= scale;
			Vector3 temp;
			temp.X = source_loc[i].X + cameraToPointDelta.X;
			temp.Y = source_loc[i].Y + cameraToPointDelta.Y;
			temp.Z = source_loc[i].Z + cameraToPointDelta.Z;
			Vector4 result;
			result = Vector4(
                ((view[0][2] * temp.Z) + (view[0][1] * temp.Y)) + (view[0][0] * temp.X) + view[0][3],
                (view[1][0] * temp.X) + ((view[1][1] * temp.Y) + (view[1][2] * temp.Z)) + view[1][3],
                (view[2][0] * temp.X) + ((view[2][1] * temp.Y) + (view[2][2] * temp.Z)) + view[2][3],
                0.0f);
			transformed_loc[i][0] = result[0];
			transformed_loc[i][1] = result[1];
			transformed_loc[i][2] = result[2];
		}
		// Separate the two actual pointer captures to retain native EBX/EDI reload order.
        float *sizes = current_size;
        _ReadWriteBarrier();
        unsigned char *orient = current_orient;
        current_loc = &transformed_loc[0];
        rva009148C0(current_loc, sizes, orient, PointCount);
		rva00913AF0(vnum, current_diffuse == NULL);
	}
}

extern unsigned char g_Va00DB5F7D;

// BFME2's FVF record: the stride, location, first texture-coordinate and
// diffuse offsets read here sit at +0x0C/+0x10/+0x24/+0x44 (retail 0x0017A2C5..
// 0x0017A2CE; Line3DClassRender.cpp reads the same stride/location/diffuse).
class PointGroupTargetFVF {
	char beforeStride[12];
	unsigned stride;
	unsigned location;
	char beforeTex[0x24 - 0x14];
	unsigned tex0;
	char beforeDiffuse[0x44 - 0x28];
	unsigned diffuse;

public:
	unsigned Get_FVF_Size() const { return stride; }
	unsigned Get_Location_Offset() const { return location; }
	unsigned Get_Tex_Offset(unsigned) const { return tex0; }
	unsigned Get_Diffuse_Offset() const { return diffuse; }
};

struct BfmeSortingVBAccess {
	const PointGroupTargetFVF &FVFInfo;
	unsigned Type;
	unsigned formatIndex;
	unsigned unused_0x0C;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass *VertexBuffer;

	BfmeSortingVBAccess(unsigned type, unsigned format_index,
		unsigned short vertex_count, unsigned buffer);
	~BfmeSortingVBAccess();

	const PointGroupTargetFVF &FVF_Info() const { return FVFInfo; }

	class WriteLock {
		BfmeSortingVBAccess *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingVBAccess *vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

// Retail 0x0012FE00 takes an xyz center and four 32-bit ranges (the view
// DX8DrawTrianglesDispatch.cpp pins).
struct TargetCenter3 { float x, y, z; TargetCenter3(float a,float b,float c):x(a),y(b),z(c){} };
class BfmeSortingDispatchAt0012FE00 {
public:
	static void Insert(const TargetCenter3& center, unsigned start,
		unsigned polygons, unsigned minimum, unsigned vertices);
};

static __forceinline void InsertPointTriangles(
	unsigned a, unsigned b, unsigned c, unsigned d)
{
	TargetCenter3 center(0.0f, 0.0f, 0.0f);
	BfmeSortingDispatchAt0012FE00::Insert(center, a, b, c, d);
}

static __forceinline void ClampPointColor(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	// Retain the donor's bounded 94-byte CMOV implementation: VC7.1 emits
	// branches for the equivalent integer clamp expressions. The independently
	// matched BFME1 Clamp_Color at 0x0090F310 and its point-submit evidence
	// establish this codegen blocker; the surrounding algorithm is C++.
	__asm
	{
		mov esi, dword ptr color
		mov edx, 0x3f800000

		mov edi, dword ptr [esi]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi], edi

		mov edi, dword ptr [esi+4]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+4], edi

		mov edi, dword ptr [esi+8]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+8], edi

		mov edi, dword ptr [esi+12]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+12], edi
	}
}

static __forceinline unsigned ConvertPointColor(Vector4 clamped_color)
{
	ClampPointColor(clamped_color);
	return DX8Wrapper::Convert_Color(
		reinterpret_cast<const Vector3 &>(clamped_color), clamped_color[3]);
}

static __forceinline unsigned ConvertDefaultPointColor(Vector4 color)
{
	ClampPointColor(color);
	return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3 &>(color), color.W);
}

void PointGroupClass::rva00913AF0(int vnum, bool no_diffuse)
{
	Matrix4 world, view;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Matrix4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);
	DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	DX8Wrapper::Set_Material(PointMaterial);
	DX8Wrapper::Set_Shader(Shader);
	BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(Texture));
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
		&& (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE)
		&& WW3D::Is_Sorting_Enabled() && g_Va00DB5F7D;
	IndexBufferClass *indexbuffer;
	int verticesperprimitive;
	if (PointMode == QUADS) {
		verticesperprimitive = 2;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingQuads)
			: static_cast<IndexBufferClass *>(Quads);
	} else {
		verticesperprimitive = 3;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingTris)
			: static_cast<IndexBufferClass *>(Tris);
	}
	unsigned default_color = ConvertDefaultPointColor(Vector4(
		DefaultPointColor.X, DefaultPointColor.Y, DefaultPointColor.Z, DefaultPointAlpha));
	int current = 0;
	while (current < vnum) {
		int delta = MIN(vnum - current, 2048);
		BfmeSortingVBAccess PointVerts(
			sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8, 5, delta, 0);
		{
			BfmeSortingVBAccess::WriteLock Lock(&PointVerts);
			unsigned char *vb = (unsigned char *)Lock.Get_Formatted_Vertex_Array();
			const PointGroupTargetFVF &fvfinfo = PointVerts.FVF_Info();
			unsigned stride = fvfinfo.Get_FVF_Size();
			unsigned char *position = vb + fvfinfo.Get_Location_Offset();
			unsigned char *uv = vb + fvfinfo.Get_Tex_Offset(0);
			unsigned char *color = vb + fvfinfo.Get_Diffuse_Offset();
			if (no_diffuse) {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = default_color;
					position += stride;
					uv += stride;
					color += stride;
				}
			} else {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = ConvertPointColor(VertexDiffuse[i]);
					position += stride;
					uv += stride;
					color += stride;
				}
			}
		}
		DX8Wrapper::Set_Index_Buffer(indexbuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&PointVerts));
		if (sort) {
			InsertPointTriangles(0, delta / verticesperprimitive, 0, delta);
		} else {
			DX8Wrapper::Draw_Triangles(0, delta / verticesperprimitive, 0, delta);
		}
		current += delta;
	}
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, world);
}

void Rva00912CF0(void)
{
	for (int i = 0; i < 5; i++) {
		delete [] PointGroupClass::_TriVertexUVFrameTable[i];
		delete [] PointGroupClass::_QuadVertexUVFrameTable[i];
	}
	if (PointGroupClass::PointMaterial) {
		PointGroupClass::PointMaterial->Release_Ref();
		PointGroupClass::PointMaterial = NULL;
	}
	_ReadWriteBarrier();
	SortingIndexBufferClass *sorting_quads = SortingQuads;
	if (sorting_quads) {
		RefCountClass *object = sorting_quads;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		SortingQuads = NULL;
	}
	_ReadWriteBarrier();
	SortingIndexBufferClass *sorting_tris = SortingTris;
	if (sorting_tris) {
		RefCountClass *object = sorting_tris;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		SortingTris = NULL;
	}
	_ReadWriteBarrier();
	DX8IndexBufferClass *quads = Quads;
	if (quads) {
		RefCountClass *object = quads;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		Quads = NULL;
	}
	_ReadWriteBarrier();
	DX8IndexBufferClass *tris = Tris;
	if (tris) {
		RefCountClass *object = tris;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		Tris = NULL;
	}
	PointGroupClass::transformed_loc.Clear();
	VertexLoc.Clear();
	VertexDiffuse.Clear();
	VertexUV.Clear();
}

class Rva00914860Sizer
{
public:
	void updatePoolSizes(int active_points, int total_points, int *vnum);
};

// Defined by the matched pointgr.cpp at the target's own addresses
// (VertexLoc 0x00DF708C, VertexUV 0x00DF94C0, VertexDiffuse 0x00DFC4E0).
extern VectorClass<Vector3> VertexLoc;

extern VectorClass<Vector4> VertexDiffuse;

void Rva00914860Sizer::updatePoolSizes(int active_points, int total_points, int *vnum)
{
	int verts_per_point = *(int *)((char *)this + 0x2C) == 1 ? 4 : 3;
	int total_vnum = verts_per_point * total_points;
	*vnum = verts_per_point * active_points;
	if (VertexLoc.Length() < total_vnum) {
		int count = total_vnum * 2;
		VertexLoc.VectorClass<Vector3>::Resize(count, 0);
		VertexUV.VectorClass<Vector2>::Resize(count, 0);
		VertexDiffuse.VectorClass<Vector4>::Resize(count, 0);
	}
}

void PointGroupClass::rva00916CD0(unsigned char *point_frame, int active_points,
                                  int bounds_address) {
  unsigned int frame_mask = ~(0xFFFFFFFF << (FrameRowColumnCountLog2 + FrameRowColumnCountLog2));
  if (point_frame) {
    Vector2 *vertex_uv = &VertexUV[0];
    if (PointMode != QUADS) {
      Vector2 *uv_ptr = _TriVertexUVFrameTable[FrameRowColumnCountLog2];
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv += 3;
      }
    } else {
      Vector2 *uv_ptr = _QuadVertexUVFrameTable[FrameRowColumnCountLog2];
      for (int i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv[3] = uv_ptr[3];
        vertex_uv += 4;
      }
    }
  } else {
    Vector2 *vertex_uv;
    const float *bounds;
    int i;
    if (PointMode != QUADS) {
      vertex_uv = &VertexUV[0];
      Vector2 *uv_ptr = _TriVertexUVFrameTable[FrameRowColumnCountLog2] + ((DefaultPointFrame & frame_mask) * 3);
      if (bounds_address) {
        bounds = (const float *)bounds_address;
        float u0 = bounds[0], v0 = bounds[1], du = bounds[2] - u0, dv = bounds[3] - v0;
        for (int j = 0; j < 3; j++) {
          uv_ptr[j].X = u0 + uv_ptr[j].X * du;
          uv_ptr[j].Y = v0 + uv_ptr[j].Y * dv;
        }
      }
      for (i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv += 3;
      }
    } else {
      vertex_uv = &VertexUV[0];
      Vector2 *uv_ptr = _QuadVertexUVFrameTable[FrameRowColumnCountLog2] + ((DefaultPointFrame & frame_mask) * 4);
      if (bounds_address) {
        bounds = (const float *)bounds_address;
        float u0 = bounds[0], v0 = bounds[1], du = bounds[2] - u0, dv = bounds[3] - v0;
        for (int j = 0; j < 4; j++) {
          uv_ptr[j].X = u0 + uv_ptr[j].X * du;
          uv_ptr[j].Y = v0 + uv_ptr[j].Y * dv;
        }
      }
      for (i = 0; i < active_points; i++) {
        vertex_uv[0] = uv_ptr[0];
        vertex_uv[1] = uv_ptr[1];
        vertex_uv[2] = uv_ptr[2];
        vertex_uv[3] = uv_ptr[3];
        vertex_uv += 4;
      }
    }
  }
}

// VertexUV has one internal definition in this consolidated unit.
