// cl: /DNDEBUG /MD
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


// TAiData::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/AI.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference). It
// is slot 3 of the vftable whose name getter returns "TAiData".
//
// ZH's xfer is only a version, and the fields go through crc(). BFME 2 folds
// the two together: under IsCRC (Xfer +0x0C) it transfers ZH's crc() field
// list; otherwise it runs Version1. The field layout skips +0x48 and +0x58.
// ZH's last three distances map onto two Reals here (+0x5C, +0x60), so those
// two keep neutral names. BFME 2 appends four Ints (+0x104..+0x110).

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

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef bool Bool;
typedef float Real;

#include "../../../Include/GameLogic/TAiData.h"

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TAiData::xfer( Xfer *xfer )
{
	if( xfer->IsCRC() )
	{
		*xfer == m_structureSeconds;
		*xfer == m_teamSeconds;
		*xfer == m_resourcesWealthy;
		*xfer == m_resourcesPoor;
		*xfer == m_forceIdleFramesCount;
		*xfer == m_structuresWealthyMod;
		*xfer == m_teamWealthyMod;
		*xfer == m_structuresPoorMod;
		*xfer == m_teamPoorMod;
		*xfer == m_teamResourcesToBuild;
		*xfer == m_guardInnerModifierAI;
		*xfer == m_guardOuterModifierAI;
		*xfer == m_guardInnerModifierHuman;
		*xfer == m_guardOuterModifierHuman;
		*xfer == m_guardChaseUnitFrames;
		*xfer == m_guardEnemyScanRate;
		*xfer == m_guardEnemyReturnScanRate;
		*xfer == m_alertRangeModifier;
		*xfer == m_aggressiveRangeModifier;
		*xfer == m_attackPriorityDistanceModifier;
		*xfer == m_maxRecruitDistance;
		*xfer == m_repulsedDistance;
		*xfer == m_enableRepulsors;
		*xfer == m_buildPhase1PerSecondPriorityModifier;
		*xfer == m_buildPhase2PerSecondPriorityModifier;
		*xfer == m_buildPhase3PerSecondPriorityModifier;
		*xfer == m_buildPhaseNPerSecondPriorityModifier;
	}
	else
	{
		// version
		xfer->Version1();
	}

}  // end xfer

// BF1 9cbfb551fe Common/Rva14AAD0RangeCount.cpp is the clean semantic guide.
// Complete native 002FDF11..002FDF1C RET leaf proves: receiver0 range pointer; end4 minus begin0 divided by element stride8.
// Original owner and complete bounds unresolved; independent address-owned view.
struct Rva002FDF11Element { unsigned char bytes[8]; };
struct Rva002FDF11Range { Rva002FDF11Element *begin; Rva002FDF11Element *end; };
class Rva002FDF11Fields {
public: int count();
private: Rva002FDF11Range *range;
};
int Rva002FDF11Fields::count() { return range->end - range->begin; }
