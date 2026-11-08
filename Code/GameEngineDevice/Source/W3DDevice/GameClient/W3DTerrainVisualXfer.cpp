// cl: /Ireference/shims/moduledata /O1 /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// stlport
// cl: /O1 /DNDEBUG /MD /GX
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


// W3DTerrainVisual::xfer, ported from Zero Hour's GameEngineDevice/Source/
// W3DDevice/GameClient/W3DTerrainVisual.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "W3DTerrainVisual".
//
// BFME 2 order: the TerrainVisual base first. That base is ZH's version-only
// xfer, the 12-byte body 0x00306A9B (rowed as Rva00306A9BDoXfer). Then come
// the light-CRC gate and Version1, with no further version checks. ZH's
// water-grid flag check is kept. BFME 2 checks the presence of the logic
// height map the same way; both mismatches share one XferException tag 5.
// The height data is 16 bits per cell (x * y * 2 bytes). On load, the
// terrain render object's slot 137 (+0x224, ZH's staticLightingChanged) is
// called with 1. The terrain render object is xferred through its Snapshot
// base at +0xC8, null-checked as a pointer conversion.

#include "Common/Snapshot.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../GameEngine/Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef bool Bool;
typedef unsigned char UnsignedByte;

#include "../../../../GameEngine/Include/Common/XferException.h"

class WorldHeightMap
{
public:
	__declspec(dllimport) __forceinline Int getXExtent( void ) { return m_width; }
	__declspec(dllimport) __forceinline Int getYExtent( void ) { return m_height; }
	__declspec(dllimport) __forceinline UnsignedByte *getDataPtr( void ) { return m_data; }
private:
	char m_unrecovered00[ 0x08 ];
	Int m_width;																															///< 0x08
	Int m_height;																															///< 0x0C
	char m_unrecovered10[ 0x24 - 0x10 ];
	UnsignedByte *m_data;																											///< 0x24
};

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

#include "../../../../GameEngine/Include/GameClient/TerrainVisualClass.h"
#include "../../../Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

// The native base transfer is the shared Version1-only stdcall body.
void __stdcall Rva00306A9BDoXfer(Xfer *xfer);

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTerrainVisual::xfer( Xfer *xfer )
{

	// extend base class
	Rva00306A9BDoXfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// flag for whether or not the water grid is enabled
	Bool gridEnabled = m_isWaterGridRenderingEnabled;
	*xfer == gridEnabled;
	if( gridEnabled != m_isWaterGridRenderingEnabled )
		throw XferException( 5, 0 );

	// xfer grid data if enabled
	if( gridEnabled )
		*xfer == *reinterpret_cast<Snapshot *>(m_waterRenderObject);

	// Write out the terrain height data.
	Bool hasHeightMap = m_logicHeightMap != 0;
	*xfer == hasHeightMap;
	if( hasHeightMap != ( m_logicHeightMap != 0 ) )
		throw XferException( 5, 0 );

	if( hasHeightMap )
	{
		UnsignedByte *data = m_logicHeightMap->getDataPtr();
		Int len = m_logicHeightMap->getXExtent()*m_logicHeightMap->getYExtent()*2;
		Int xferLen = len;
		*xfer == xferLen;
		if (len>xferLen) {
			len = xferLen;
		}
		xfer->XferRawBytes( data, len );
		if( xfer->IsLoading() )
		{
			// Update the display height map.
			m_terrainRenderObject->vslot137( true );
		}
	}

	Snapshot *terrainSnapshot = m_terrainRenderObject;
	*xfer == *terrainSnapshot;

}  // end xfer

// Retail 0x00072988..0x000729CC, RET8; called by 0x00073FFB.
// The two-byte grid cell supplies its low four bits, scaled by the retail
// 17.0f literal at 0x00BC653C. Only observed fields are modeled; the original
// class and method names remain unresolved. This terrain unit already uses
// the verified x87 /O1 /G7 configuration required by the native conversion.
struct Rva00072988Cell
{
	unsigned short level : 4;
	unsigned short rest : 12;
};

#include "../../../Include/W3DDevice/GameClient/W3DShroudClass.h"

unsigned char W3DShroud::getShroudLevel(int x, int y)
{
	if (!m_shroudData)
		return 0;
	if (x >= m_numCellsX || y >= m_numCellsY)
		return 0;
	int value = y * m_numCellsX + x;
	value = reinterpret_cast<Rva00072988Cell *>(m_shroudData)[value].level;
	float scaled = (float)value;
	scaled *= 17.0f;
	return (unsigned char)(int)scaled;
}

// The retail call in this body reads 0x00306A9B, an address the ledger already
// carries as ?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?xfer@TerrainVisual@@MAEXPAVXfer@@@Z=?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z")
