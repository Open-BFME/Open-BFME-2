// cl: /Ireference/shims/bfme2_vector3 /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/water /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Water
// stlport
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x0007E829 (60B). Only Get_Obj_Space_Bounding_Sphere is
// carried; the donor's own directory stays on the include path for its
// relative game/ WW3D2 includes.
// readable body of ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
#define Matrix4x4 Matrix4  // BFME renamed it

#include <string.h>
#pragma intrinsic(memcpy)
#include "vector3.h" // use the verified BFME2 three-word constructor
#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"  // game/ WW3D2 BFME RenderObjClass must win over the reference tree's same-directory copy
#include "../../../../../Libraries/Source/WWVegas/WW3D2/vertmaterial.h"  // game/ copy: retail VertexMaterialClass has no W3D pool, the reference copy emits getClassMemoryPool
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
struct ID3DXBuffer {
    virtual long __stdcall QueryInterface(const void *, void **) = 0;
    virtual unsigned long __stdcall AddRef(void) = 0;
    virtual unsigned long __stdcall Release(void) = 0;
    virtual void * __stdcall GetBufferPointer(void) = 0;
    virtual unsigned long __stdcall GetBufferSize(void) = 0;
};
extern "C" __declspec(dllimport) long __stdcall D3DXAssembleShader(const char *, unsigned int, const void *, void *, ID3DXBuffer **, ID3DXBuffer **);
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DWater.cpp /////////////////////////////////////////////////////////////////////////////
// Created:   Mark Wilczynski, June 2001
// Desc:      Draw reflective water surface.  Also handles drawing of waves/ripples
//			  on the surface.
///////////////////////////////////////////////////////////////////////////////////////////////////

#define SCROLL_UV
										 
// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
// The BFME texture ABI hides the upstream inline ref-count release behind the retail out-of-line call.
#include "../../../../../Libraries/Source/WWVegas/WW3D2/texture.h"
#include "W3DDevice/GameClient/W3DWater.h"
#include "W3DDevice/GameClient/heightmap.h"
// BFME's W3DShroud hands out a counted TextureHandle (0x006D2630), not the upstream raw pointer.
class TextureHandle
{
public:
	TextureHandle(void) : m_ptr(0) { }
	TextureHandle(const TextureHandle &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr != 0)
			m_ptr->Add_Ref();
	}
	~TextureHandle(void)
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}
	TextureHandle &operator=(const TextureHandle &that)
	{
		if (that.m_ptr != 0)
			that.m_ptr->Add_Ref();
		if (m_ptr != 0)
			m_ptr->Release_Ref();
		m_ptr = that.m_ptr;
		return *this;
	}

	TextureBaseClass *get(void) const { return m_ptr; }
	operator TextureClass *(void) const { return (TextureClass *)m_ptr; }

	TextureBaseClass *m_ptr;
};

class W3DShroud
{
public:
	TextureHandle getShroudTexture(void);
};
#include "W3DDevice/GameClient/W3DWaterTracks.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "assetmgr.h"
#include "rinfo.h"
#include "camera.h"
#include "scene.h"
#include "dx8wrapper.h"
#include "light.h"
#include "D3dx8math.h"
#include "simplevec.h"
#include "mesh.h"
#include "matinfo.h"

#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/Xfer.h"
#include "Common/GameLOD.h"

#include "GameClient/Water.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DPoly.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define MIPMAP_BUMP_TEXTURE

// DEFINES ////////////////////////////////////////////////////////////////////////////////////////
#define SKYPLANE_SIZE	(384.0f*MAP_XY_FACTOR)
#define SKYPLANE_HEIGHT	(30.0f)

#define SKYBODY_TEXTURE	"TSMoonLarg.tga"
#define SKYBODY_SIZE	45.0f		//extent or radius of sky body

#define SKYBODY_X	150.0f	//location of skybody
#define SKYBODY_Y	550.0f	//location of skybody

/* in the bay
#define SKYBODY_X	120.0f			//location of skybody
#define SKYBODY_Y	75.0f			//location of skybody
*/

#define SKYBODY_HEIGHT	SKYPLANE_HEIGHT	//altitude of sky body (z-buffer disabled, so can equal sky height).

//GeForce3 water system defines
#define PATCH_SIZE 15		//number of vertices on patch edge.  Large patches may waste vertices off edge of screen.
#define PATCH_UV_TILES	42	//number of times the bump map texture is tiled across patch (must be integer!).
#define PATCH_SCALE (4.0f * MAP_XY_FACTOR)	//horizontal scale factor. Adjust this and size to get desired vertex density.
#define SEA_REFLECTION_SIZE 256		//dimensions of reflection texture

#define SEA_BUMP_SCALE		(0.06f)		//scales the du/dv offsets stored in bump map (~ amount to perturb)
#define BUMP_SIZE (50.f)
#define REFLECTION_FACTOR 0.1f

#define PATCH_WIDTH (PATCH_SIZE-1)	//internal defines
#define PATCH_UV_SCALE	((Real)PATCH_UV_TILES/(Real)PATCH_WIDTH)	

//3D Grid Mesh Water defines.
#define WATER_MESH_OPACITY		0.5f
#define WATER_MESH_X_VERTICES	128
#define WATER_MESH_Y_VERTICES	128
#define WATER_MESH_SPACING	MAP_XY_FACTOR	//same as terrain

#ifdef USE_MESH_NORMALS
#define WATER_MESH_FVF	DX8_FVF_XYZNDUV2
typedef VertexFormatXYZNDUV2 MaterMeshVertexFormat;
#else
#define WATER_MESH_FVF	DX8_FVF_XYZDUV2
typedef VertexFormatXYZDUV2 MaterMeshVertexFormat;
#endif

// Converts a FLOAT to a DWORD for use in SetRenderState() calls
static inline DWORD F2DW( FLOAT f ) { return *((DWORD*)&f); }

#define DRAW_WATER_WAKES
/// @todo: Fix clipping of objects that intersect the mirror surface
//#define CLIP_GEOMETRY_TO_PLANE	// this enables clipping of objects that intersect the mirror surfaces

// Some shader combinations that can be useful in rendering water:

// Modulate stage0 with stage1 texture.  Also modulate stage 0 with vertex color.
#define SC_DETAIL_BLEND ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE,\
	ShaderClass::SRCBLEND_SRC_ALPHA,ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_ENABLE, 	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, ShaderClass::DETAILCOLOR_DETAILBLEND, ShaderClass::DETAILALPHA_DISABLE) )

// Just a z-buffer fill, nothing is written to the color buffer.
#define SC_ZFILL_BLEND ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_DISABLE, ShaderClass::SRCBLEND_ZERO, \
	ShaderClass::DSTBLEND_ONE, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::DETAILCOLOR_SCALE, ShaderClass::DETAILALPHA_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_SCALE, ShaderClass::DETAILALPHA_DISABLE) )

// No texturing, just vertex color with vertex alpha
#define SC_ZFILL_BLENDx ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, \
	ShaderClass::SRCBLEND_ZERO, ShaderClass::DSTBLEND_SRC_COLOR, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Modulate blended with vertex alpha modulation
#define SC_ZFILL_MODULATE_TEX ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE,\
	ShaderClass::SRCBLEND_ZERO, ShaderClass::DSTBLEND_SRC_COLOR, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_ENABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Alpha blended with vertex alpha modulation
#define SC_ZFILL_ALPHA_TEX ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE,\
	ShaderClass::SRCBLEND_SRC_ALPHA, ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_DISABLE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_ENABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Alpha blended with vertex alpha modulation
#define SC_OPAQUE_TEXONLY ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE,\
	ShaderClass::SRCBLEND_ONE, ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_DISABLE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_ENABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Alpha blended with vertex alpha modulation
#define SC_ZFILL_BLEND3 ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE,\
	ShaderClass::SRCBLEND_SRC_ALPHA, ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_ENABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )


WaterRenderObjClass *TheWaterRenderObj=NULL; ///<global water rendering object

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }




#define DONUT_SIDES	90
#define INNER_RADIUS 200.0f
#define OUTER_RADIUS 250.0f
#define TEXTURE_REPEAT_COUNT 16
#define DONUT_HEIGHT	15.0f
//#define DO_FLAT_DONUT
#define AMP_SCALE	(30.0f/120.0f)
#define WAVE_FREQ	0.3f
#define AMP_SCALE2	(10.0f/120.0f)
#define NOISE_FREQ	(2.0f*PI/WAVE_FREQ)

#define NOISE_REPEAT_FACTOR ((float)(1.0f/(16.0f)))

					
static Bool wireframeForDebug = 0;

// ?setupJbaWaterShader@WaterRenderObjClass@@IAEXXZ present-unmatched





//-------------------------------------------------------------------------------------------------
/** Destructor. Releases w3d assets. */
//-------------------------------------------------------------------------------------------------
// ??1WaterRenderObjClass@@UAE@XZ present-unmatched


//-------------------------------------------------------------------------------------------------
/** Constructor. Just nulls out some variables. */
//-------------------------------------------------------------------------------------------------
// ??0WaterRenderObjClass@@QAE@XZ present-unmatched


//-------------------------------------------------------------------------------------------------
/** WW3D method that returns object bounding sphere used in frustum culling*/
//-------------------------------------------------------------------------------------------------
void WaterRenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	//Since this object is more of a system (containing lots of water pieces),
	//let's disable culling by making bounds huge.  Let each piece do it's own cull.
	Vector3 ObjSpaceCenter; ObjSpaceCenter.Set(0,0,0);
//	Vector3 ObjSpaceRadius; ObjSpaceRadius.Set(m_dx,m_dy,0);
	Vector3 ObjSpaceRadius; ObjSpaceRadius.Set(50000,50000,0);

	sphere.Init(ObjSpaceCenter,ObjSpaceRadius.Length());
}

//-------------------------------------------------------------------------------------------------
/** WW3D method that returns object bounding box used in collision detection*/
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** returns the class id, so the scene can tell what kind of render object it has. */
//-------------------------------------------------------------------------------------------------
// ?Class_ID@WaterRenderObjClass@@UBEHXZ present-unmatched


//-------------------------------------------------------------------------------------------------
/** Not used, but required virtual method. */
//-------------------------------------------------------------------------------------------------
// ?Clone@WaterRenderObjClass@@UBEPAVRenderObjClass@@XZ present-unmatched


//-------------------------------------------------------------------------------------------------
/** Copies raw bits from pBumpSrc (a regular grayscale texture) into a D3D
	*   bump-map format. */
//-------------------------------------------------------------------------------------------------
// ?initBumpMap@WaterRenderObjClass@@IAEJPAPAUIDirect3DTexture8@@PAVTextureClass@@@Z present-unmatched


//-------------------------------------------------------------------------------------------------
/** Create and fill a D3D vertex buffer with water surface vertices */
//-------------------------------------------------------------------------------------------------
// ?generateVertexBuffer@WaterRenderObjClass@@IAEJHHH_N@Z exact retail body is emitted by
// WaterRenderObjGenerateVertexBuffer.cpp.
//-------------------------------------------------------------------------------------------------
/** Create and fill a D3D index buffer with water surface strip indices */
//-------------------------------------------------------------------------------------------------
// BFME creates the index buffer through a GLOBAL device at 0x01340534, not the
// m_pDev member the reference uses, and its CreateIndexBuffer takes SIX
// arguments -- the five the reference passes plus a trailing null. The buffer
// pointer is at this+0x128 and the index count at this+0x140.
class BfmeRetailIndexBuffer
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0;
	virtual HRESULT __stdcall Lock(unsigned int, unsigned int, BYTE **, unsigned int) = 0;
	virtual HRESULT __stdcall Unlock() = 0;
};

class BfmeRetailDevice
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual HRESULT __stdcall CreateIndexBuffer(unsigned int, unsigned int, unsigned int,
		unsigned int, BfmeRetailIndexBuffer **, void *) = 0;
};


struct BfmeWaterIndexLayout
{
	unsigned char gap0[0x128];
	BfmeRetailIndexBuffer *indexBufferD3D;				///< retail this+0x128
	unsigned char gap1[0x14];
	Int numIndices;										///< retail this+0x140
};



//-------------------------------------------------------------------------------------------------
/** Releases all w3d assets, to prepare for Reset device call. */
//-------------------------------------------------------------------------------------------------
// ?ReleaseResources@WaterRenderObjClass@@QAEXXZ present-unmatched


//-------------------------------------------------------------------------------------------------
/** (Re)allocates all W3D assets after a reset.. */
//-------------------------------------------------------------------------------------------------
// ?ReAcquireResources@WaterRenderObjClass@@QAEXXZ is a real C++ body in
// Water/WaterRenderObjReAcquireResources.cpp.


//-------------------------------------------------------------------------------------------------
/** Initializes water with dimensions and parent scene.
	* During rendering, we will render a water surface of given dimensions
	* and reflect the parent scene in its surface.  For now, waters are
	* forced to be rectangles. */
//-------------------------------------------------------------------------------------------------
// ?init@WaterRenderObjClass@@QAEHMMMPAVSceneClass@@W4WaterType@1@@Z present-unmatched


// ?updateMapOverrides@WaterRenderObjClass@@QAEXXZ present-unmatched


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReset.cpp
// ?reset@WaterRenderObjClass@@QAEXXZ present-unmatched
 

// enableWaterGrid is defined by UpdateInitializationThunks.cpp; its retail
// implementation is in WaterRenderObjEnableWaterGrid.cpp.

// ------------------------------------------------------------------------------------------------
/** Update phase for water if we need it.  This called once per client frame reguardless
	* of how fast the logic framerate is running */
// ------------------------------------------------------------------------------------------------
// ?update@WaterRenderObjClass@@QAEXXZ is a real C++ body in
// Water/WaterRenderObjUpdate.cpp.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReplaceSkyboxTextureRetail.cpp
// ?replaceSkyboxTexture@WaterRenderObjClass@@QAEXABVAsciiString@@0@Z present-unmatched


//-------------------------------------------------------------------------------------------------
/** Adjusts various water/sky rendering settings that depend on time of day. */
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/**Copies GDF settings dealing with a particular time of day into our own
	* structures.  Also allocates any required W3D assets (textures). */
//-------------------------------------------------------------------------------------------------
// ?loadSetting@WaterRenderObjClass@@IAEXPAUSetting@1@W4TimeOfDay@@@Z present-unmatched


//-------------------------------------------------------------------------------------------------
/** Our water may use effects that require run-time rendered textures.  These
	*	textures need to be updated before we start rendering to the main screen
	* render target because D3D doesn't multiple render targets. */
//-------------------------------------------------------------------------------------------------
// ?updateRenderTargetTextures@WaterRenderObjClass@@QAEXPAVCameraClass@@@Z


//-------------------------------------------------------------------------------------------------
/** Renders the reflected scene into an offscreen texture. */
//-------------------------------------------------------------------------------------------------
// Retail gives the temporary depth target ref-counted ownership; the upstream
// one-argument call loses that lifetime and selects a different overload shape.
// Retail reads +0x400 here, while the shared upstream layout places the field elsewhere.
struct BFMEWaterRenderObjOffset400View
{
	char BeforeOffset400[0x400];
	Int Value;
};

class WaterTextureRef
{
public:
	TextureBaseClass *Pointer;

	WaterTextureRef(void) : Pointer(0) {}
	~WaterTextureRef(void)
	{
		if (Pointer != 0)
			Pointer->Release_Ref();
	}
};



//-------------------------------------------------------------------------------------------------
/** Renders (draws) the water.
	*	Algorithm:
	*	Draw reflected scene.
	*	Draw reflected sky layer(s) and bodies.
	*	Clear Zbuffer
	*	Fill Zbuffer by drawing water surface (allows proper sorting into regular scene).
	*	Draw non-reflected scene (done in regular app render loop).
	*
	*	This algorithm doesn't apply to translucent water, which is rendered into a
	*   texture and rendered at end of scene. */
//-------------------------------------------------------------------------------------------------
//DECLARE_PERF_TIMER(Water)
// ?Render@WaterRenderObjClass@@UAEXAAVRenderInfoClass@@@Z present-unmatched


//-------------------------------------------------------------------------------------------------
/** Clips the water plane to the current camera frustum and returns a bounding
	* box enclosing the clipped plane.  Returns false if water plane is not visible. */
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** Draws the water surface using a custom D3D vertex/pixel shader and a
	* reflection texture.  Only tested to work on GeForce3. */
//-------------------------------------------------------------------------------------------------
void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

// Device view in the D3D9 vtable order retail dispatches on; unused slots stay unnamed.
#define SEA_SLOT(n) virtual void __stdcall slot##n() = 0;
struct WaterSeaDevice
{
	SEA_SLOT(00) SEA_SLOT(01) SEA_SLOT(02) SEA_SLOT(03) SEA_SLOT(04) SEA_SLOT(05) SEA_SLOT(06) SEA_SLOT(07)
	SEA_SLOT(08) SEA_SLOT(09) SEA_SLOT(10) SEA_SLOT(11) SEA_SLOT(12) SEA_SLOT(13) SEA_SLOT(14) SEA_SLOT(15)
	SEA_SLOT(16) SEA_SLOT(17) SEA_SLOT(18) SEA_SLOT(19) SEA_SLOT(20) SEA_SLOT(21) SEA_SLOT(22) SEA_SLOT(23)
	SEA_SLOT(24) SEA_SLOT(25) SEA_SLOT(26) SEA_SLOT(27) SEA_SLOT(28) SEA_SLOT(29) SEA_SLOT(30) SEA_SLOT(31)
	SEA_SLOT(32) SEA_SLOT(33) SEA_SLOT(34) SEA_SLOT(35) SEA_SLOT(36) SEA_SLOT(37) SEA_SLOT(38) SEA_SLOT(39)
	SEA_SLOT(40) SEA_SLOT(41) SEA_SLOT(42) SEA_SLOT(43) SEA_SLOT(44) SEA_SLOT(45) SEA_SLOT(46) SEA_SLOT(47)
	SEA_SLOT(48) SEA_SLOT(49) SEA_SLOT(50) SEA_SLOT(51) SEA_SLOT(52) SEA_SLOT(53) SEA_SLOT(54) SEA_SLOT(55)
	SEA_SLOT(56)
	virtual HRESULT __stdcall SetRenderState(DWORD state, DWORD value) = 0;			// 0xe4
	SEA_SLOT(58) SEA_SLOT(59) SEA_SLOT(60) SEA_SLOT(61) SEA_SLOT(62) SEA_SLOT(63) SEA_SLOT(64)
	virtual HRESULT __stdcall SetTexture(DWORD stage, void *texture) = 0;				// 0x104
	SEA_SLOT(66)
	virtual HRESULT __stdcall SetTextureStageState(DWORD stage, DWORD type, DWORD value) = 0;	// 0x10c
	SEA_SLOT(68)
	virtual HRESULT __stdcall SetSamplerState(DWORD sampler, DWORD type, DWORD value) = 0;	// 0x114
	SEA_SLOT(70) SEA_SLOT(71) SEA_SLOT(72) SEA_SLOT(73) SEA_SLOT(74) SEA_SLOT(75) SEA_SLOT(76) SEA_SLOT(77)
	SEA_SLOT(78) SEA_SLOT(79) SEA_SLOT(80) SEA_SLOT(81)
	virtual HRESULT __stdcall DrawIndexedPrimitive(DWORD type, int baseVertex, UINT minIndex,
		UINT numVertices, UINT startIndex, UINT primitiveCount) = 0;						// 0x148
	SEA_SLOT(83) SEA_SLOT(84) SEA_SLOT(85) SEA_SLOT(86)
	virtual HRESULT __stdcall SetVertexDeclaration(DWORD declaration) = 0;				// 0x15c
	SEA_SLOT(88)
	virtual HRESULT __stdcall SetFVF(DWORD fvf) = 0;									// 0x164
	SEA_SLOT(90) SEA_SLOT(91)
	virtual HRESULT __stdcall SetVertexShader(DWORD shader) = 0;						// 0x170
	SEA_SLOT(93)
	virtual HRESULT __stdcall SetVertexShaderConstantF(UINT reg, const void *data, UINT count) = 0;	// 0x178
	SEA_SLOT(95) SEA_SLOT(96) SEA_SLOT(97) SEA_SLOT(98) SEA_SLOT(99)
	virtual HRESULT __stdcall SetStreamSource(UINT stream, void *buffer, UINT offset, UINT stride) = 0;	// 0x190
	SEA_SLOT(101) SEA_SLOT(102) SEA_SLOT(103)
	virtual HRESULT __stdcall SetIndices(void *buffer) = 0;								// 0x1a0
	SEA_SLOT(105) SEA_SLOT(106)
	virtual HRESULT __stdcall SetPixelShader(DWORD shader) = 0;						// 0x1ac

	// Stands in for the real D3DXVECTOR4's conversion to const float *, which the shim lacks.
	HRESULT SetVertexShaderConstantF(UINT reg, const D3DXVECTOR4 &data, UINT count)
	{
		return SetVertexShaderConstantF(reg, (const void *)&data, count);
	}
};
#undef SEA_SLOT

// Retail keeps the sea buffers and shaders at these offsets; BFME drops the upstream m_pDev member.
struct BFMEWaterSeaView
{
	char BeforeOffset124[0x124];
	LPDIRECT3DVERTEXBUFFER8 m_vertexBuffer;			// +0x124
	LPDIRECT3DINDEXBUFFER8 m_indexBuffer;			// +0x128
	DWORD m_12c;
	DWORD m_130;									// pixel shader
	DWORD m_134;									// vertex shader
	DWORD m_138;									// vertex declaration
};

// BaseHeightMapRenderObjClass keeps its W3DShroud at +0x30B8 (BaseHeightMapConstructor.cpp).
struct BFMEWaterTerrainShroudView
{
	W3DShroud *getShroud(void) { return m_shroud; }
	char BeforeOffset30B8[0x30B8];
	W3DShroud *m_shroud;
};

// W3DShaderManager's texture slots (retail 0x012F9D28).
extern TextureHandle g_bfmeTableDU[];





// BFME's _Set_DX8_Transform no longer mirrors the matrix into DX8Transforms.
class WaterSeaTransform : public DX8Wrapper
{
public:
	static __forceinline void Set(D3DTRANSFORMSTATETYPE transform, const Matrix4x4 &m)
	{
		DX8_RECORD_MATRIX_CHANGE();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m));
	}
	static __forceinline void Set_Vertex_Declaration(DWORD declaration)
	{
		((WaterSeaDevice *)_Get_D3D_Device8())->SetVertexDeclaration(declaration);
		number_of_DX8_calls++;
	}
};

// ?drawSea@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@@Z



#define FEATHER_LAYER_COUNT (5.0f)
#define FEATHER_THICKNESS   (4.0f)

//-------------------------------------------------------------------------------------------------
/** Renders (draws) the water surface.*/
//-------------------------------------------------------------------------------------------------
// ?renderWater@WaterRenderObjClass@@QAEXXZ present-unmatched


// Exact BFME renderSky and renderSkyBody are provided by WaterRenderObjSky.cpp.

//Defines for procedural water animation.
#define WATER_FREQ	(2.0*3.2831/4.0)	//2pi (full cycle) cover 4 units
#define WATER_AMP	(1.0f)
#define	WATER_OFFSET (0.1f)

//-------------------------------------------------------------------------------------------------
/** Renders (draws) the water surface mesh geometry.
	*	This is a work-in-progress!  Do not use this code! */
//-------------------------------------------------------------------------------------------------
// ?renderWaterMesh@WaterRenderObjClass@@IAEXXZ present-unmatched


// ?setGridVertexHeight@WaterRenderObjClass@@ present-unmatched






















/**Utility function used to query water heights in a manner that works in both RTS and WB.*/
// ?getWaterHeight@WaterRenderObjClass@@QAEMMM@Z present-unmatched


//-------------------------------------------------------------------------------------------------
//Draw a many sided river polygon.
//-------------------------------------------------------------------------------------------------
// ?drawRiverWater@WaterRenderObjClass@@IAEXPAVPolygonTrigger@@@Z present-unmatched


// ?setupFlatWaterShader@WaterRenderObjClass@@IAEXXZ present-unmatched


//-------------------------------------------------------------------------------------------------
//Draw a 4 sided flat water area.
//-------------------------------------------------------------------------------------------------
// ?drawTrapezoidWater@WaterRenderObjClass@@IAEXQAVVector3@@@Z present-unmatched




//-------------------------------------------------------------------------------------------------
//debug version where moon rotates with the camera	(always upright on screen)
//-------------------------------------------------------------------------------------------------
#if 0
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjRenderSkyBodyRetail.cpp
// ?renderSkyBody@WaterRenderObjClass@@IAEXPAVMatrix3D@@@Z present-unmatched

#endif

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@WaterRenderObjClass@@MAEXPAVXfer@@@Z present-unmatched
  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjXferRetail.cpp
// ?xfer@WaterRenderObjClass@@MAEXPAVXfer@@@Z present-unmatched
  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
  // end loadPostProcess
