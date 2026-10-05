// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The camera-shaker bodies of Open-BFME-1's
// GameEngineDevice/Source/W3DDevice/GameClient/camerashakesystem.cpp (donor
// revision 6583b3c1ff21db4a561285717028fdafc780b7db), compiled with the donor's
// own flags plus /O1 /arch:SSE, the settings W3DView.cpp's donor bodies match
// under. Searched by masked whole-.text search, each body places once on
// unclaimed game.dat .text:
// CameraShakerClass::CameraShakerClass 0x00065A39 (208B),
// CameraShakerClass::Compute_Rotations 0x00065B09 (411B),
// CameraShakeSystemClass::Add_Camera_Shake 0x00065DAD (116B, the callee
// W3DView::Add_Camera_Shake reaches), and
// CameraShakeSystemClass::Update_Camera_Shaker 0x00065ED5 (95B). The system's
// constructor, destructor (camerashakesystem.cpp), IsCameraShaking, Timestep
// and the global instance are left out; only placed bodies are defined here.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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
 *                 Project Name : WWPhys                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwphys/camerashakesystem.cpp                 $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 6/12/01 10:25a                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assetmgr.h>
#include <texture.h>
#include <tri.h>
#include <colmath.h>
#include <coltest.h>
#include <rinfo.h>
#include <camera.h>
#include <d3dx8core.h>
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"

#include "GameClient/TerrainVisual.h"
#include "GameClient/View.h"
#include "GameClient/Water.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/TerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/W3DBibBuffer.h"
#include "W3DDevice/GameClient/W3DTreeBuffer.h"
#include "W3DDevice/GameClient/W3DRoadBuffer.h"
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include "W3DDevice/GameClient/W3DWaypointBuffer.h"
#include "W3DDevice/GameClient/W3DCustomEdging.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DWater.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/Light.h"
#include "WW3D2/Scene.h"
#include "W3DDevice/GameClient/W3DPoly.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"

#include "W3DDevice/GameClient/camerashakesystem.h"
#include "WW3D2/Camera.h"

//#include "W3DDevice/GameClient/camera.h"
//#include "W3DDevice/GameClient/wwmemlog.h"

/*
** (gth) According to my "research" the artists say that there are several factors that
** go into a good camera shake.  
** - The motion should be sinusoidal.
** - Camera rotation is more effective than camera motion (good, I won't use any translation)
** - The camera should pitch up and down a lot more than it yaws left and right.
*/

DEFINE_AUTO_POOL(CameraShakeSystemClass::CameraShakerClass,256);

const float MIN_OMEGA			= DEG_TO_RADF(12.5f*360.0f);
const float MAX_OMEGA			= DEG_TO_RADF(15.0f*360.0f);
const float END_OMEGA			= DEG_TO_RADF(360.0f);
const float MIN_PHI				= DEG_TO_RADF(0.0f);
const float MAX_PHI				= DEG_TO_RADF(360.0f);
const Vector3 AXIS_ROTATION	= Vector3(DEG_TO_RADF(7.5f),DEG_TO_RADF(15.0f),DEG_TO_RADF(5.0f));


/************************************************************************************************
**
** CameraShakeSystemClass::CameraShakerClass Implementation
**
************************************************************************************************/
CameraShakeSystemClass::CameraShakerClass::CameraShakerClass
(
	const Vector3 & position,
	float radius,
	float duration,
	float intensity
) :
	Position(position),
	Radius(radius),
	Duration(duration),
	Intensity(intensity),
	ElapsedTime(0.0f)
{
	/*
	** Initialize random sinusoid values
	*/
	Omega.X = WWMath::Random_Float(MIN_OMEGA,MAX_OMEGA);
	Omega.Y = WWMath::Random_Float(MIN_OMEGA,MAX_OMEGA);
	Omega.Z = WWMath::Random_Float(MIN_OMEGA,MAX_OMEGA);
	Phi.X = WWMath::Random_Float(MIN_PHI,MAX_PHI);
	Phi.Y = WWMath::Random_Float(MIN_PHI,MAX_PHI);
	Phi.Z = WWMath::Random_Float(MIN_PHI,MAX_PHI);
}




















