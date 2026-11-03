// cl: /Ireference/shims/bfme2ray /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp); this unit had no counterpart under Code/.
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

// FILE: W3DTerrainVisual.cpp /////////////////////////////////////////////////////////////////////
// W3D implementation details for visual aspects of terrain
// Author: Colin Day, April 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/ThingTemplate.h"
#include "Common/WellKnownKeys.h"
#include "Common/TerrainTypes.h"
#include "Common/Xfer.h"
#include "Common/UnitTimings.h" //Contains the DO_UNIT_TIMINGS define jba.		 
#include "Common/QuickTrig.h"

#include "GameClient/Drawable.h"
#include "GameClient/ClientRandomValue.h"

#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"

#include "coltest.h" // BFME2 RayCollisionTestClass (reference/shims/bfme2ray): out-of-line ctors as retail calls them
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DTerrainVisual.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/W3DWater.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DDebugIcons.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/heightmap.h"
#include "W3DDevice/GameClient/FlatHeightmap.h"
#include "W3DDevice/GameClient/W3DSmudge.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "WW3D2/Light.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/ColType.h"
#include "WW3D2/ColTest.h"
#include "WW3D2/assetmgr.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_Unchecked_set@?$bitset@$0HF@@_STL@@QAEAAV12@IH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bitset<117> & bitset<117>::_Unchecked_set(unsigned int,int); }

// placement unverified: no rowed DIR32 site yet; ZH asset-manager singleton starts null.
WW3DAssetManager *WW3DAssetManager::TheInstance = 0;
// placement unverified: no rowed DIR32 site yet; ZH W3D shadow singleton starts null.
W3DShadowManager *TheW3DShadowManager = 0;


class TestSeismicFilter : public SeismicSimulationFilterBase
{

  virtual SeismicSimStatusCode filterCallback( WorldHeightMapInterfaceClass *heightMap, const SeismicSimulationNode *node )
  {


    Int life = node->m_life;

    if ( heightMap == NULL )
      return SEISMIC_STATUS_INVALID;


    if ( life == 0 )
      return SEISMIC_STATUS_ACTIVE;
    if ( life < 15 )
    {
      // ADD HEIGHT BECAUSE THE EXPLOSION IS PUSHING DIRT UP

      Real magnitude = node->m_magnitude;

      Real offsScalar =  magnitude / (Real)life; // real-life, get it?
      Int radius = node->m_radius;
      Int border = heightMap->getBorderSize();
      Int centerX = node->m_center.x + border ;
      Int centerY = node->m_center.y + border ;
  
      UnsignedInt workspaceWidth = radius*2;
      Real *workspace = NEW( Real[ sqr(workspaceWidth) ] );
      Real *workspaceEnd = workspace + sqr(workspaceWidth);


      for ( Real *t = workspace; t < workspaceEnd; ++t ) *t = 0.0f;// clear the workspace

      for (Int x = 0; x < radius; ++x)
      {
        for (Int y = 0; y < radius; ++y)
        {

          Real distance = sqrt( sqr(x) + sqr(y) );//Pythagoras
      
          if ( distance < radius )
          {
            Real distScalar = cos( ( distance / radius * (PI/2) ) );
            Real height = (offsScalar * distScalar); 

            workspace[ (radius + x) +  workspaceWidth * (radius + y) ] = height + heightMap->getBilinearSampleSeismicZVelocity( centerX + x,  centerY + y ) ;//kaleidoscope
            
            if ( x != 0 ) // non-zero test prevents cross-shaped double stamp 
            {
      			  workspace[ (radius - x) + workspaceWidth * (radius + y) ] = height + heightMap->getBilinearSampleSeismicZVelocity( centerX - x,  centerY + y ) ;
              if ( y != 0 )
                workspace[ (radius - x) + workspaceWidth * (radius - y) ] =  height + heightMap->getBilinearSampleSeismicZVelocity( centerX - x,  centerY - y ) ;
            }
            if ( y != 0 )
      			  workspace[ (radius + x) + workspaceWidth * (radius - y) ] = height + heightMap->getBilinearSampleSeismicZVelocity( centerX + x,  centerY - y ) ;
          }
        }
      }

      // stuff the values from the workspace into the heightmap's velocities
      for (x = 0; x < workspaceWidth; ++x)
        for (Int y = 0; y < workspaceWidth; ++y)
    			heightMap->setSeismicZVelocity( centerX - radius + x, centerY - radius + y,  workspace[  x + workspaceWidth * y ]  );

      delete [] workspace;

      return SEISMIC_STATUS_ACTIVE;
    }
    else
      return SEISMIC_STATUS_ZERO_ENERGY;
  }

  virtual Real applyGravityCallback( Real velocityIn )
  {
    Real velocityOut = velocityIn;
    velocityOut -= 1.5f;
    return velocityOut;
  }


};
static TestSeismicFilter testSeismicFilter;


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** init */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** reset */
//-------------------------------------------------------------------------------------------------
// W3DTerrainVisual::reset is rowed with BFME2's body in W3DTerrainVisualInit.cpp;
// the Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** update */
//-------------------------------------------------------------------------------------------------
// W3DTerrainVisual::update (retail 0x00091D0D) is rowed with BFME2's body in
// Rva00091D0DShutdownStep.cpp; the Zero Hour copy here was a second,
// non-retail definition.


#ifdef DO_SEISMIC_SIMULATIONS


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#defined DO_SEISMIC_SIMULATIONS
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
/** load method for W3D visual terrain */
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** intersect the ray with the terrain, if a hit occurs TRUE is returned
	* and the result point on the terrain is returned in "result" */
//-------------------------------------------------------------------------------------------------
// The intersectTerrain body lives under W3DTerrainVisualIntersectTerrain.cpp
// (retail row); this TU keeps only the class declaration so callers bind the
// kept copy and this unit emits no competing COMDAT.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DTerrainVisual::getTerrainColorAt: retail's body is the row at 0x00091D3D
// (Rva00091E83Forwarders.cpp); this unit only declares it, so its vtable binds there.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DTerrainVisual::getTerrainTile: defined in W3DTerrainVisualGetTerrainTile.cpp (its row's unit).
  // end getTerrainTile

// ------------------------------------------------------------------------------------------------
/** set min/max height values allowed in water grid pointed to by waterTable */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** adjust fallof parameters for grid change method */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** set the water table position and orientation in world space */
// ------------------------------------------------------------------------------------------------
// NOTE (link lane): Zero Hour's setWaterTransform(const WaterHandle *, Real,
// Real, Real, Real) was dropped. No row holds it, no other object references
// it, and it called WaterRenderObjClass::setGridTransform(Real, Real, Real,
// Real), which BFME 2 does not provide (its rowed setGridTransform takes a
// Matrix3D, 0x003F7E74). The Matrix3D overload below is the row (LINK-181).

// ------------------------------------------------------------------------------------------------
/** set water table transform by matrix */
// ------------------------------------------------------------------------------------------------
void W3DTerrainVisual::setWaterTransform( const Matrix3D *transform )
{

	if( m_waterRenderObject )
		m_waterRenderObject->setGridTransform( transform );
			
}  // end setWaterTransform

// ------------------------------------------------------------------------------------------------
/** get the water transform matrix */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** water grid resolution spacing */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** get water grid resolution spacing */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** adjust the water grid in world coords by the delta */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// W3DTerrainVisual::addFactionBibDrawable is BFME 2's own body, rowed at
// 0x00092A95 in W3DTerrainVisualAddFactionBibDrawable.cpp (it copies the
// template's GeometryInfo through the out-of-line copy ctor 0x000929E8); the
// Zero Hour copy that stood here duplicated that definition.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// W3DTerrainVisual::addFactionBib is rowed in W3DTerrainVisualAddFactionBibDrawable.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DTerrainVisual::removeAllBibs(void)
{
	if (m_terrainRenderObject) {
		m_terrainRenderObject->removeAllTerrainBibs();
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// W3DTerrainVisual::removeTreesAndPropsForConstruction: retail's body is the row at
// 0x00091E45 (Rva00091E83Forwarders.cpp); this unit only declares it.
 
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/// Replace the skybox texture
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version 
	* 2: Add height map heights.
	* 3: Add client side trees & props. jba.
*/
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------