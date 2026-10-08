// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/projectedshadow /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x001094E2 (92B).
extern class Gen0003AC38 *g_shadowManager;
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

;////////////////////////////////////////////////////////////////////////////////
;//																																						 //
;//  (c) 2001-2003 Electronic Arts Inc.																				 //
;//																																						 //
;////////////////////////////////////////////////////////////////////////////////

// FILE: W3DTextureShadow.cpp ///////////////////////////////////////////////////////////
//
// Texture based shadow representation.
//
// Author: Mark Wilczynski, February 2002
//
//
///////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "always.h"
// Pull in the shim RenderObjClass (BFME vtable layout stubs) before any WW3D2
// header grabs the ZH reference rendobj.h; both share include guard RENDOBJ_H.
#include "rendobj.h"
#include "GameClient/View.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Light.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/HLod.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmdl.h"
#include "WW3D2/assetmgr.h"
#include "WW3D2/texproject.h"
#include "WW3D2/dx8renderer.h"
#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/Heightmap.h"
#include "D3dx8math.h"
#include "common/GlobalData.h"
#include "W3DDevice/GameClient/W3DProjectedShadow.h"
#include "WW3D2/statistics.h"
#include "Common/Debug.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameClient/drawable.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/Heightmap.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

/** @todo: We're going to have a pool of a couple rendertargets to use
in rare cases when dynamic shadows need to be generated.  Maybe we can
even get away with a single one that gets used immediatly to render, then
recycled.  For most of the objects, we need to have a static texture that
is reused for all instances on the level.

Need to add support for loading textures from disk instead of generating them in
code.  Could allow for a single non-distinct blob to be used for everything.

Instead of projecting onto arbitrary geometry, could allow for terrain only.
Maybe project onto a deformed terrain patch that molds to trays/bibs.
*/

#define DEFAULT_RENDER_TARGET_WIDTH			512
#define DEFAULT_RENDER_TARGET_HEIGHT		512

extern class W3DProjectedShadowManager *TheW3DProjectedShadowManager;	//global singleton
ProjectedShadowManager	*TheProjectedShadowManager;				//global singleton with simpler interface.
extern const FrustumClass *shadowCameraFrustum;	//defined in W3DShadow.
///@todo: Externs from volumetric shadow renderer - these need to be moved into W3DBufferManager
extern LPDIRECT3DVERTEXBUFFER8 shadowVertexBufferD3D;		///<D3D vertex buffer
extern LPDIRECT3DINDEXBUFFER8	shadowIndexBufferD3D;	///<D3D index buffer
extern int nShadowVertsInBuf;	//model vetices in vertex buffer
extern int nShadowStartBatchVertex;
extern int nShadowIndicesInBuf;	//model vetices in vertex buffer
extern int nShadowStartBatchIndex;
extern int SHADOW_VERTEX_SIZE;
extern int SHADOW_INDEX_SIZE;

//Bounding rectangle around rendered portion of terrain.
static Int drawEdgeX=0;
static Int drawEdgeY=0;
static Int drawStartX=0;
static Int drawStartY=0;

//Global streaming vertex buffer with x,y,z,u,v type.
struct SHADOW_DECAL_VERTEX	//vertex structure passed to D3D
{
		float x,y,z;
		DWORD diffuse;
		float u,v;
}; 

#define SHADOW_DECAL_FVF	D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE

LPDIRECT3DVERTEXBUFFER8 shadowDecalVertexBufferD3D=NULL;		///<D3D vertex buffer
LPDIRECT3DINDEXBUFFER8	shadowDecalIndexBufferD3D=NULL;	///<D3D index buffer
int nShadowDecalVertsInBuf=0;	//model vetices in vertex buffer
int nShadowDecalStartBatchVertex=0;
int nShadowDecalIndicesInBuf=0;	//model vetices in vertex buffer
int nShadowDecalStartBatchIndex=0;
int	nShadowDecalPolysInBatch=0;
int	nShadowDecalVertsInBatch=0;
int SHADOW_DECAL_VERTEX_SIZE=32768;
int SHADOW_DECAL_INDEX_SIZE=65536;


class W3DShadowTexture;	//forward reference
class W3DShadowTextureManager;	//forward reference


/** This class will manage shadow textures for each render object.  Shadow textures may
be based on render geometry but don't need to be.  This allows lower detail 'blob' textures
to be substituted to improve performance.*/
class W3DShadowTextureManager
{
public:
	W3DShadowTextureManager(void);
	~W3DShadowTextureManager(void);

	int			 		createTexture(RenderObjClass *robj, const char *name);
	W3DShadowTexture *		getTexture(const char * name);
	W3DShadowTexture *		peekTexture(const char * name);
	Bool					addTexture(W3DShadowTexture *new_texture);
	void			 		freeAllTextures(void);
	void					invalidateCachedLightPositions(void);

	void					registerMissing( const char * name );
	Bool					isMissing( const char * name );
	void					resetMissing( void );

private:

	HashTableClass	*	texturePtrTable;
	HashTableClass	*	missingTextureTable;

	friend	class		W3DShadowTextureManagerIterator;
};

class W3DShadowTexture : public RefCountClass, public	HashableClass
{

	public:

		W3DShadowTexture( void )
		{	m_lastLightPosition.Set(0,0,0); m_lastObjectOrientation.Make_Identity();
			m_shadowUV[0].Set(1.0f,0.0f,0.0f);	//u runs along world x axis
			m_shadowUV[1].Set(0.0f,-1.0f,0.0f);	//v runs along world -y axis
		}
		~W3DShadowTexture( void ) { REF_PTR_RELEASE(m_texture);}

		virtual	const char * Get_Key( void )	{ return m_namebuf;	}

		Int init (RenderObjClass *robj);

		const char *		Get_Name(void) const	{ return m_namebuf;}
		void				Set_Name(const char *name)
		{	memset(m_namebuf,0,sizeof(m_namebuf));	//pad with zero so always ends with null character.
			strncpy(m_namebuf,name,sizeof(m_namebuf)-1);
		}
		TextureClass	*getTexture(void)	{ return m_texture;}
		void					 setTexture(TextureClass *texture)	{m_texture = texture;}
		void					 setLightPosHistory(Vector3 &pos) {m_lastLightPosition=pos;}	///<updates the last position of light
		Vector3&			 getLightPosHistory(void) {return m_lastLightPosition;}
		void					 setObjectOrientationHistory(Matrix3x3 &mat) {m_lastObjectOrientation=mat;}	///<updates the last position of light
		Matrix3x3&			 getObjectOrientationHistory(void) {return m_lastObjectOrientation;}
		SphereClass&	 getBoundingSphere(void)	{return m_areaEffectSphere;}
		AABoxClass&		 getBoundingBox(void)		{return m_areaEffectBox;}
		void	 setBoundingSphere(SphereClass &sphere)	{m_areaEffectSphere=sphere;}
		void	 setBoundingBox(AABoxClass &box)		{m_areaEffectBox=box;}
		void	 updateBounds(Vector3 &lightPos, RenderObjClass *robj);	///<update extent of shadow
		void	 setDecalUVAxis(Vector3 &u, Vector3 &v)	{ m_shadowUV[0]=u; m_shadowUV[1]=v;}
		void	 getDecalUVAxis(Vector3 *u, Vector3 *v)	{ *u=m_shadowUV[0]; *v=m_shadowUV[1];}

	private:

		char m_namebuf[2*W3D_NAME_LEN];	///<name of model hierarchy

		TextureClass *m_texture; ///<texture holding the shadow for this renderobject
		Vector3		m_lastLightPosition;		///<position of light source at time of last texture update.
		Matrix3x3	m_lastObjectOrientation;	///<orientation of shadow casting object when texture was generated.
		AABoxClass	m_areaEffectBox;			///<boundary defining object-space volume affected by shadow.
		SphereClass	m_areaEffectSphere;			///<boundary defining object-space volume affected by shadow.
		Vector3		m_shadowUV[2];		///world-space vectors defining the u and v texture coordinate axis.
};

/*
** An Iterator to get to all loaded W3DShadowGeometries in a W3DShadowGeometryManager
*/
class W3DShadowTextureManagerIterator : public HashTableIteratorClass {
public:
	W3DShadowTextureManagerIterator( W3DShadowTextureManager & manager ) : HashTableIteratorClass( *manager.texturePtrTable ) {}
	W3DShadowTexture * getCurrentTexture( void ) { 	return (W3DShadowTexture *)Get_Current();}
};


/******************** Start of W3DProjectedShadowManager implementation ***********************/
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowManagerConstructor.cpp
// ??0W3DProjectedShadowManager@@QAE@XZ present-unmatched


// ??1W3DProjectedShadowManager@@UAE@XZ present-unmatched


// ?reset@W3DProjectedShadowManager@@QAEXXZ present-unmatched
  // end Reset




// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowReAcquireResources.cpp
// ?ReAcquireResources@W3DProjectedShadowManager@@QAE_NXZ present-unmatched


// byte-exact reconstruction: game/GameEngine/Source/Common/promoted_ReleaseResources_W3DProjectedShadowManager_QAEXXZ_007B1450.cpp
// ?ReleaseResources@W3DProjectedShadowManager@@QAEXXZ present-unmatched


// ?invalidateCachedLightPositions@W3DProjectedShadowManager@@QAEXXZ present-unmatched


// ?updateRenderTargetTextures@W3DProjectedShadowManager@@QAEXXZ present-unmatched


///Renders shadow on part of terrain covered by world-space bounding box.
// ?renderProjectedTerrainShadow@W3DProjectedShadowManager@@ present-unmatched


#if 0

TextureClass *snow=NULL;
TextureClass *grass=NULL;
TextureClass *ground=NULL;

#define V_COUNT  (4*4)	//4 vertices per cell
#define I_COUNT  (4*6)	//6 indices per cell
#define TILE_HEIGHT	10.1f
#define TILE_DIFFUSE 0x00b4b0a5

enum BlendDirection
{	B_A,	//visible on all sides
	B_R,	//visible on right
	B_L,	//visible on left
	B_T,	//visible on top
	B_B,	//visble on bottom
	B_TL,	//visible on top/left
	B_BR,	//visible on bottom/right
	B_TR,	//visible on top/right 
	B_BL	//visilbe on bottom/left
};

//Vertex alpha values for each blend direction assuming tile vertices
//start at top left corner and continue counter-clockwise
DWORD BDToVA[9][4]=
{
	{0xff000000,0xff000000,0xff000000,0xff000000},
	{0,0,0xff000000,0xff000000},
	{0xff000000,0xff000000,0,0},
	{0xff000000,0,0,0xff000000},
	{0,0xff000000,0xff000000,0},
	{0xff000000,0,0,0},
	{0,0,0xff000000,0},
	{0,0,0,0xff000000},
	{0,0xff000000,0,0}
};



//Debug code used to draw some dummy polygons.

#endif

// ?flushDecals@W3DProjectedShadowManager@@ present-unmatched


/*

*/

#define BRIDGE_OFFSET_FACTOR 1.5f
/**Decals have a low poly count so its better to render large numbers at once.  This system will queue them


/**Simpler/faster decal system that always uses 2 triangles that are roughly oriented
to terrain.  Since they are not projected onto terrain, there may be clipping
artifacts in certain situations.
TODO: Too much clipping.  Need to check terrain heights at all 4 corners and adjust tilt to match*/
///@todo: We should have a pre-made static filled index buffer since we always send down 2 triangles.
// ?queueSimpleDecal@W3DProjectedShadowManager@@QAEXPAVW3DProjectedShadow@@@Z present-unmatched


// renderShadows is implemented in W3DProjectedShadowRenderShadows.cpp.


/** Generic function which can be used to create arbitrary decals that don't have to be used for shadows.
Some examples: Scorch marks, blood, stains, selection/status indicators, etc.*/
struct BFMEShadowTypeInfo
{
	Char name[128];
	ShadowType type;
	Bool allowUpdates;
	Bool allowWorldAlign;
	Char pad[2];
	Real sizeX;
	Real sizeY;
	Real offsetX;
	Real offsetY;
	Int unused98;
	Int flags;
	Bool force;
};

extern void j_000193bc();

class BFMEShadowManagerLayout
{
public:
	W3DShadowTexture *getTexture(const Char *name);
	W3DProjectedShadow *addShadowCore(
		W3DShadowTexture *texture,
		RenderObjClass *robj,
		ShadowType type,
		Bool allowWorldAlign,
		Real sizeX,
		Real sizeY,
		Int flags,
		Real offsetX,
		Real offsetY,
		W3DProjectedShadow **list,
		Bool simple,
		Drawable *draw,
		Bool projected);
};


/** Generic function which can be used to create arbitrary decals that follow the renderObject but don't have to be used for shadows.
Some examples: Scorch marks, blood, stains, selection/status indicators, etc.*/
// ?addDecal@W3DProjectedShadowManager@@UAEPAVShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@2@@Z present-unmatched




// ?createDecalShadow@W3DProjectedShadowManager@@ present-unmatched


// ?removeShadow@W3DProjectedShadowManager@@QAEXPAVW3DProjectedShadow@@@Z present-unmatched


// byte-exact reconstruction: game/GameEngine/Source/Common/promoted__removeAllShadows_W3DProjectedShadowManager_QAEXXZ_007AEA90.cpp
// ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ present-unmatched


#if defined(_DEBUG) || defined(_INTERNAL)	
// ?getRenderCost@W3DProjectedShadow@@ present-unmatched

#endif

// ??0W3DProjectedShadow@@QAE@XZ present-unmatched


// ??1W3DProjectedShadow@@QAE@XZ present-unmatched


// ?init@W3DProjectedShadow@@QAEXXZ present-unmatched


#define DECAL_TEXELS_PER_WORLD_UNIT	(64.0f/20.0f)	//64 texels per 2 terrain cells (20 units)

// ?updateProjectionParameters@W3DProjectedShadow@@QAEXABVMatrix3D@@@Z present-unmatched


void W3DProjectedShadow::update(void)
{
	//retail W3DProjectedShadow stores m_shadowTexture[0] at +0x68; the reference
	//layout shim (BFMEShadowManagerLayout) carries the same offsets.
	W3DShadowTexture *texture = *(W3DShadowTexture **)((char *)this + 0x68);
	Vector3 &lastPos = texture->getLightPosHistory();
	if (lastPos != (*(W3DShadowManager **)&g_shadowManager)->getLightPosWorld(0))
	{	//light has moved since last time this shadow was calculated. Need update
		updateTexture((*(W3DShadowManager **)&g_shadowManager)->getLightPosWorld(0));
	}
}

// ?init@W3DShadowTexture@@QAEHPAVRenderObjClass@@@Z present-unmatched








/** Release all loaded textures */


/** Find texture in cache */


/** Get texture from cache and increment its reference count */


/** Add texture to cache */




/*
** An entry for a table of textures not found, so we can quickly determine their loss
*/
class MissingTextureClass : public HashableClass {

public:
	MissingTextureClass( const char * name );
	virtual	~MissingTextureClass( void );

	virtual	const char * Get_Key( void )	{ return Name;	}

private:
	StringClass	Name;

};



/*
** Missing Textures
**
** The idea here, allow the system to register which textures are determined to be missing
** so that if they are asked for again, we can quickly return NULL, without searching again.
*/




/** Create shadow geometry from a reference W3D RenderObject*/
// ?createTexture@W3DShadowTextureManager@@QAEHPAVRenderObjClass@@PBD@Z present-unmatched

