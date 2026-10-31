// The projectedshadow shim's W3DDevice/GameClient/W3DProjectedShadow.h, verbatim but for
// BFME 2's base, virtual slots, signatures and offsets where retail's rows differ
// (marked "BFME 2:"). Copied from
// reference/open-bfme-1/inputs/reference/shims/projectedshadow/W3DDevice/GameClient/W3DProjectedShadow.h
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

// FILE: W3DProjectedShadow.h ///////////////////////////////////////////////////////////
//
// Real time shadow projection through textures.
//
// Author: Mark Wilczynski, February 2002
//
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __W3D_PROJECTED_SHADOW_H_
#define __W3D_PROJECTED_SHADOW_H_

#include "GameClient/Shadow.h"

class W3DShadowTexture;	//forward reference
class W3DShadowTextureManager;	//forward reference
class Drawable;	//forward reference
class W3DProjectedShadow; //forward reference.
class TexProjectClass;
class Rva00109610;
class BfmeDynamicNativeVB;
class DX8IndexBufferClass;
struct Rva0010C065Info;
struct EmitVtableTag;

// BFME 2: the manager's base. Retail vtable 0x007CF994 is the deleting dtor then five
// __purecall slots, and the rows ??0, ??1 and ??_G of this class (0x00108657, 0x0010846E,
// 0x00108475) install it; Zero Hour's ProjectedShadowManager has two slots after the dtor.
class Rva00108475
{
public:
	Rva00108475();
	Rva00108475(EmitVtableTag *);
	virtual ~Rva00108475();
	virtual void rva0010BE72() = 0;
	virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *) = 0;
	virtual W3DProjectedShadow *rva0010C145(RenderObjClass *, Shadow::ShadowTypeInfo *, bool, bool) = 0;
	virtual void forward(unsigned, unsigned, unsigned) = 0;
	virtual unsigned forwardIf(unsigned, void *, unsigned, unsigned) = 0;
};

class W3DProjectedShadowManager	: public Rva00108475
{
/*	enum ShadowTextureType {
		STT_STATIC	=	0x0001,
		STT_DYNAMIC	= 0x0002,
		STT_SHARED
			};
*/
	public:
		W3DProjectedShadowManager( void );
		// BFME 2: the ??_G row 0x0010C825 calls this destructor (0x0010C785) out of line.
		__declspec(noinline) virtual ~W3DProjectedShadowManager( void );
		Bool init(void);					///<allocate one-time shadow assets for length of entire game.
		void reset(void);					///<free all existing shadows - ready for next map.
		void shutdown(void);			///<free all assets prior to shutdown of entire game.
		Int	 renderShadows(RenderInfoClass & rinfo);	///<iterate over each object and render its shadow onto affected objects.
		void ReleaseResources(void);	///<release device dependent D3D resources.
		Bool ReAcquireResources(void);	///<allocate device dependent D3D resources.
		void invalidateCachedLightPositions(void);	///<forces shadows to update regardless of last lightposition

		// BFME 2: table 0x007CF9C4 after the destructor is 0x0010BE72, 0x0010C065, 0x0010C145, 0x00108790,
		// 0x001087A6 and 0x0010C2D5; the rows' mangled names give these signatures.
		virtual void rva0010BE72( void );
		virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *);
		virtual W3DProjectedShadow *rva0010C145(RenderObjClass *, Shadow::ShadowTypeInfo *, bool, bool);
		virtual void forward(unsigned, unsigned, unsigned);
		virtual unsigned forwardIf(unsigned, void *, unsigned, unsigned);
		virtual W3DProjectedShadow *rva0010C2D5(int, RenderObjClass *, Shadow::ShadowTypeInfo *, Shadow::ShadowTypeInfo *);
		W3DProjectedShadow	*addShadow( RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);	///<add a new shadow with texture of given name or that of robj.
		W3DProjectedShadow	*createDecalShadow( Shadow::ShadowTypeInfo *shadowInfo);	///<add a new shadow with texture of given name or that of robj.
		void removeShadow (W3DProjectedShadow *shadow);
		void removeAllShadows(void); ///< Remove all shadows.
		SpecialRenderInfoClass *getRenderContext(void)	{ return m_shadowContext;}
		void updateRenderTargetTextures(void);	///<render into any textures that need updating.
		void queueDecal(W3DProjectedShadow *shadow);	///<add shadow decal to render list - decal conforms to terrain.
		void queueSimpleDecal(W3DProjectedShadow *shadow);	///< add shadow decal to render list - decal floats on terrain.
		void flushDecals(W3DShadowTexture *texture, ShadowType type);	///<empty queue by rendering all decals with given texture

	private:
		// BFME 2: offsets from the constructor 0x00108D33, the queue 0x001091A8 (+0x04, +0x08, +0x0C,
		// +0x1C), the unlink 0x00109129 (+0x10, +0x250), the factory 0x0010C2D5 (+0x14, +0x18), the
		// init 0x00108DBC (+0x20, +0x24C) and the buffer setup 0x00108660 (+0x254, +0x258).
		W3DProjectedShadow *m_shadowList;
		W3DProjectedShadow *m_decalList;
		W3DProjectedShadow *m_simpleDecalList;
		W3DProjectedShadow *m_freeShadowList;
		W3DProjectedShadow *m_dualDecalList;
		W3DProjectedShadow *m_freeDualList;
		W3DProjectedShadow *m_list1C;
		CameraClass		*m_shadowCamera;					///<camera used to render all shadow textures - configured by projector
		LightEnvironmentClass m_shadowLightEnv;
		// BFME 2: retail's light environment alone fills +0x24 to +0x24C (constructor 0x0013F410, the
		// bfme2lightenv shim); with this TU's Zero Hour lightenvironment.h this member takes its last 4 bytes.
		SpecialRenderInfoClass *m_shadowContext;
		W3DShadowTextureManager *m_W3DShadowTextureManager;
		Int m_numDecalShadows;							///< number of decal shadows in the system.
		BfmeDynamicNativeVB *m_vb;
		DX8IndexBufferClass *m_ib;
		Int m_nShadowDecalVertsInBuf;					// BFME 2: +0x25C, set by the render walk 0x0010DF33
		Int m_260;
		Int m_nShadowDecalIndicesInBuf;					// BFME 2: +0x264, set by the render walk 0x0010DF33
		Int m_268;
		Int m_26C;
		Int m_270;
		Int renderProjectedTerrainShadow(W3DProjectedShadow *shadow, AABoxClass &box);	///<render shadow on map terrain.
};

extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

/** Object for maintaining and updating an object's shadow texture.
*/
class W3DProjectedShadow	: public Shadow
{
	friend class W3DProjectedShadowManager;

	public:
		W3DProjectedShadow(void);
		~W3DProjectedShadow(void);
		void setRenderObject( RenderObjClass	*robj) {m_robj=robj;}
		void setObjPosHistory(Vector3 &pos)	{m_lastObjPosition=pos;}	///<position of object when projection matrix was updated.
		void setTexture(Int lightIndex,W3DShadowTexture *texture)	{m_shadowTexture[lightIndex]=texture;}	///<textur with light's shadow
		void update(void);	///<updates the texture and/or projection parameters when the object or light moves.
		bool init(void);		// BFME 2: ?init@W3DProjectedShadow@@QAE_NXZ, row 0x0010BDF8
		void updateTexture(Vector3 &lightPos);	///<updates the shadow texture image using render object and given light position.
		void updateProjectionParameters(const Matrix3D &cameraXform);	///<recompute projection matrix - needed when light or object moves.
		// BFME 2: rows 0x001088F6, 0x00108931 and 0x00108951
		void rva007AEC10(void);
		void rva00108931(void);
		void rva00108951(void);
		#if defined(_DEBUG) || defined(_INTERNAL)	
		virtual void getRenderCost(RenderCost & rc) const;
		#endif
		W3DShadowTexture *getTexture(Int lightIndex) {return m_shadowTexture[lightIndex];}
		

	// BFME 2: public, because the rowed list helper 0x00109129 walks m_next from outside the class.
	public:
		// BFME 2: this ledger class spans retail's two-texture shadow (0x68 bytes, children at +0x58 and
		// +0x5C, read by init 0x0010BDF8) and the single decal (0x118 bytes, built by 0x0010BB11 and
		// 0x0010BA2C). Offsets: the release 0x001088F6 (+0x68 to +0x70), updateTexture 0x0010930F (+0x70),
		// the factory 0x0010BB11 (+0x74 to +0x85), the reset 0x00108895 (+0x88) and the unlink 0x00109129.
		Rva00109610 *m_projector;		// +0x58
		Rva00109610 *m_secondProjector;	// +0x5C
		char m_pad60[0x68 - 0x60];
		W3DShadowTexture *m_shadowTexture[2];		///<cached shadow data
		RenderObjClass	*m_robj;						///<render object used to cast the shadow.
		Bool	m_allowWorldAlign;	/// wrap shadow around world geometry - else align perpendicular to local z-axis.
		Real	m_decalOffsetU;		/// texture coordinate offset so not centered at object origin.
		Real	m_decalOffsetV;		/// texture coordinate offset so not centered at object origin.
		Int		m_flags;			/// custom rendering flags
		Bool	m_flag84;			// +0x84
		Bool	m_flag85;			// +0x85
		Vector3		m_lastObjPosition;	///<position of  object at time of projection matrix update.
		unsigned m_array94[16];		// +0x94
		unsigned m_arrayD4[16];		// +0xD4
		W3DProjectedShadow *m_next;	/// for the shadow manager list
		virtual void release(void)	{TheW3DProjectedShadowManager->removeShadow(this);}	///<release shadow from manager
};

#endif	//__W3D_PROJECTED_SHADOW_H_
