// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -DBFME_VOLUMETRIC_DELETE_LAYOUT -Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
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

struct Rva007BDB70Record
{
	unsigned char bytes[22];
};

class Rva007BDB70ArrayOwner
{
public:
	Rva007BDB70Record *lookup(int index);
	void ensureStorage(void);

private:
	unsigned char m_prefix[0x24];
	Rva007BDB70Record *m_records;
	int m_count;
};

Rva007BDB70Record *Rva007BDB70ArrayOwner::lookup(int index)
{
	if (!m_records)
		ensureStorage();

	if (index >= 0 && index < m_count)
		return &m_records[index];

	return 0;
}
