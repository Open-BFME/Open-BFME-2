// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport
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

// WorldHeightMap.cpp
// Class to encapsulate height map.
// Author: John Ahlquist, April 2001

// The TheKey_* instances are defined once, by WorldHeightMap.cpp (INSTANTIATE_WELL_KNOWN_KEYS).

#include "../../../../../reference/shims/bfme2_ascii_zh/zh_ascii.h"
#include "windows.h"
#include "stdlib.h"
#include <string.h>
#include "Common/STLTypedefs.h"

#include "Common/DataChunk.h"
//#include "Common/GameFileSystem.h"
#include "Common/FileSystem.h" // for LOAD_TEST_ASSETS
#include "Common/GlobalData.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/TerrainTypes.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/WellKnownKeys.h"

#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/SidesList.h"

#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/W3DShadow.h"

#include "Common/file.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define K_OBSOLETE_HEIGHT_MAP_VERSION 8

#define PATHFIND_CLIFF_SLOPE_LIMIT_F	9.8f	

// -----------------------------------------------------------
class BfmeMapObjectListEntry
{
public:
	virtual void bfmeDeleteThis(int freeIt) = 0;		///< vtable slot 0
	BfmeMapObjectListEntry *m_next;
	char m_pad08[0x1c];
	Dict m_properties;
	Dict *getProperties() { return &m_properties; }
};

#include "../../../Include/W3DDevice/GameClient/BfmeMapObjectListHolder.h"

class BfmeMapObjectExtra
{
public:
	void bfmeReset(void);					///< retail 0x00033F46
};

extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;	///< retail [0x012ED5DC]
extern BfmeMapObjectExtra BfmeTheMapObjectExtra;		///< retail 0x012ED5E0

/*static */ Int MapObject::countMapObjectsWithOwner(const AsciiString& asciiString)
{
	Int count = 0;
	BfmeMapObjectListEntry *pMapObj = reinterpret_cast<BfmeMapObjectListEntry *>(BfmeTheMapObjectListHolder->m_head);
	for (; pMapObj; pMapObj = pMapObj->m_next)
	{
		if (pMapObj->getProperties()->getAsciiString(TheKey_originalOwner.key(), 0) == asciiString)
			++count;
	}
	return count;
}
