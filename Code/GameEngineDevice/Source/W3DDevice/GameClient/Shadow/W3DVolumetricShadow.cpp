// cl: /O1 /G7 /arch:SSE -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -DBFME_VOLUMETRIC_DELETE_LAYOUT -Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
// stlport
// readable body of ?Fabs@WWMath@@: game/Libraries/Source/WWVegas/WW3D2/coltest.cpp
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DVolumetricShadow.cpp ///////////////////////////////////////////////////////////
//
// Real time shadow volume representations
//
// Author: Colin Day, January 2001
// Adapted for W3D: Mark Wilczynski October 2001
//
//
///////////////////////////////////////////////////////////////////////////////
///@todo: Must cap shadow volumes if we ever allow camera inside the volumes.
///@todo: Find better way to determine when shadow volumes need updating - lights move, objects move.

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <assert.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "always.h"
#include "GameClient/View.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Light.h"
#define MESH_RENDER_SNAPSHOT_ENABLED
// BFME's index_count is a full 32-bit slot and its index-buffer constructor
// takes the count at full width; use the BFME declaration of DX8IndexBufferClass
// rather than the Zero Hour one the include path would otherwise find.
#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#include "../../../../../Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef MESH_RENDER_SNAPSHOT_ENABLED
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/HLod.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmdl.h"
#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/Heightmap.h"
#include "D3dx8math.h"
#include "common/GlobalData.h"
#include "common/drawmodule.h"
#include "W3DDevice/GameClient/W3DVolumetricShadow.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "WW3D2/statistics.h"
#include "GameLogic/TerrainLogic.h"
#include "WW3D2/DX8Caps.h"
#include "GameClient/Drawable.h"
#include "wwshade/shdmesh.h"
#include "wwshade/shdsubmesh.h"

// ?resetSilhouette@W3DVolumetricShadow@@IAEXH@Z
// retail 0x000F0832, 16 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/
// W3DVolumetricShadow.cpp, reference/open-bfme-1) and only this body; the
// donor's other definitions are omitted. Compiled /Os the donor emits it
// byte-identical to retail (unique masked placement on unclaimed .text).
//
// The class layout is the shim header's:
//   Short m_numSilhouetteIndices[MAX_SHADOW_CASTER_MESHES];  // this+0x4400
// A 16-bit element array is what fixes the retail body, which clears a
// *word* at [ecx + meshIndex*2 + 0x4400] rather than a dword.

// resetSilhouette ============================================================
// Resets the silhouette to empty, it does NOT free any of the memory
// allocated for silhouette data
// ============================================================================
void W3DVolumetricShadow::resetSilhouette( Int meshIndex )
{

	m_numSilhouetteIndices[meshIndex] = 0;

}  // end resetSilhouette

// ?SetGeometry@W3DVolumetricShadow@@IAEXPAVW3DShadowGeometry@@@Z
// retail 0x000F16B4, 129 bytes: the donor body verbatim (same preamble and
// BFME_VOLUMETRIC_DELETE_LAYOUT), placed uniquely by recompiling the donor
// unit at /O1. Callees are the rowed allocateSilhouette 0x000F07C3 and
// deleteSilhouette 0x000F0803, reached through their pins.
// setGeometry ================================================================
void W3DVolumetricShadow::SetGeometry( W3DShadowGeometry *geometry )
{
	struct BFMEShadowGeometryMesh
	{
		char m_beforeNumVerts[0x28];
		Int m_numVerts;
		char m_afterNumVerts[0x08];
	};
	struct BFMEShadowGeometry
	{
		BFMEShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	};

#ifdef BFME_VOLUMETRIC_DELETE_LAYOUT
	W3DVolumetricShadow *shadow = this;
	W3DVolumetricShadow *geometryShadow = (W3DVolumetricShadow *)((char *)this + 0x30);
#else
	W3DVolumetricShadow *shadow = (W3DVolumetricShadow *)((char *)this + 0x30);
	W3DVolumetricShadow *geometryShadow = shadow;
#endif
	BFMEShadowGeometry *newGeometry = (BFMEShadowGeometry *)geometry;

	Short numPrevVertices = 0;
	Short numNewVertices = 0;

	//
	// our geometry has changed, we need to allocate enough memory for the
	// silhouette data.  If silhouette data is present it must be reallocated
	// to accomoddate the new size if smaller
	//

	// if we had previous geometry how many vertices did it have

	for (Int i=0; i<MAX_SHADOW_CASTER_MESHES; i++)
	{
		if( geometryShadow->m_geometry )
			numPrevVertices = ((BFMEShadowGeometry *)geometryShadow->m_geometry)->m_meshList[i].m_numVerts;

		// now many vertices does our new geometry have
		if( geometry )
			numNewVertices = newGeometry->m_meshList[i].m_numVerts;

		//
		// TODO: Colin, may want to change this in the future
		// if our new geometry requires more memory allocate it, if it requires
		// less we'll leave it around for future switches in geometry
		//
		if( numNewVertices > numPrevVertices )
		{

			shadow->deleteSilhouette(i);
			if( shadow->allocateSilhouette(i, numNewVertices ) == FALSE )
				return;

		}  // end if
	}

	// assign the new geometry, possible over an old geometry
	geometryShadow->m_geometry = geometry;

}  // end SetGeometry

// Manager destruction: BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// supplies ReleaseResources and the geometry/buffer-manager deletions. WB
// independently identifies the native manager destructor at F2ECB, 143B.
// Retail adds the device-lock scope and shared vector resets. The EH guard
// is inferred from its state and cleanup; isolated EH verification is exact.
// Keep the existing address-derived geometry-dtor binding; its source type
// is not claimed here. Explicit destruction reproduces the non-virtual
// delete sequence without dispatching through that opaque view's vtable.
// Data ledger globals g_00DEBE0C/24 own the shared vector roots. Their
// 12B TCB stand-in is inherited; the original element identity is uncertain.
// Native clears ActiveCount+10 then calls the existing 37B VectorClass<int>
// Clear provider, which frees raw storage and resets base fields without an
// element destructor. No new global or call-target pin is introduced.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
struct VolShadowDeviceLock {
 VolShadowDeviceLock() { BFME_DX8_Thread_Lock(); }
 ~VolShadowDeviceLock() { BFME_DX8_Thread_Assert(); }
};
class Rva000F0912 { public: void rva000F0972(); };
class Rva000F2797 { public: virtual ~Rva000F2797(); };
#include "tcbspline.h"
// Promote the donor's protected nested type for the existing ledger globals;
// this type-only access bridge creates no object or target identity.
struct VolShadowTCBAccess : TCBSpline3DClass { typedef TCBClass Type; };
extern DynamicVectorClass<VolShadowTCBAccess::Type> g_00DEBE0C;
extern DynamicVectorClass<VolShadowTCBAccess::Type> g_00DEBE24;
// ?W3DVolumetricShadowManager::~W3DVolumetricShadowManager present-unmatched
W3DVolumetricShadowManager::~W3DVolumetricShadowManager()
{
 VolShadowDeviceLock guard;
 ((Rva000F0912 *)this)->rva000F0972();
 Rva000F2797 *geometry=(Rva000F2797 *)m_W3DShadowGeometryManager;
 if(geometry) { geometry->Rva000F2797::~Rva000F2797(); ::operator delete(geometry); }
 m_W3DShadowGeometryManager=0;
 delete TheW3DBufferManager;
 TheW3DBufferManager=0;
 *(int *)((char *)&g_00DEBE0C+16)=0;
 ((VectorClass<int> *)&g_00DEBE0C)->VectorClass<int>::Clear();
 *(int *)((char *)&g_00DEBE24+16)=0;
 ((VectorClass<int> *)&g_00DEBE24)->VectorClass<int>::Clear();
}
