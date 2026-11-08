// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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


// BaseHeightMapRenderObjClass::xfer, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). It is slot 3
// of the vftable whose name getter returns "BaseHeightMapRenderObjClass".
//
// BFME 2 puts the light-CRC gate first and versions (1, 4). Versions before 3
// are refused by throwing XferException's unnamed-enum value 2, the same tag
// Xfer::operator==(Version&) uses for "older than supported". ZH's two buffer
// snapshots become three (+0x3788, +0x378C, +0x3790). Version 2 adds a fourth
// (+0x3798). Version 4 adds a counted array of 0x1C-byte snapshot records
// from +0x18 (count at +0x36C8) and an Int at +0x36D0. These offsets are
// relative to the Snapshot base at +0xC8; they fall on the canonical header's
// m_treeBuffer, m_shrubBuffer, m_propBuffer, field3860, the records at +0xE0,
// m_numScorches and field3798.

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

#include "../../../../GameEngine/Include/Common/XferException.h"

// A 0x1C-byte snapshot record kept in an array at +0x18.
class BaseHeightMapSnapshotRecord : public Snapshot
{
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x1C - 0x04 ];
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// xfer overrides the Snapshot base at +0xC8, so retail addresses these
// fields 0xC8 lower: the 0x1C-byte records at +0xE0 (count +0x3790, Int
// +0x3798) and the buffers at +0x3850/+0x3854/+0x3858/+0x3860.
static __forceinline BaseHeightMapSnapshotRecord *snapshotRecords(BaseHeightMapRenderObjClass *self)
{
	return reinterpret_cast<BaseHeightMapSnapshotRecord *>(self->unknown00E0);
}
static __forceinline Snapshot *bufferSnapshot(void *buffer)
{
	return reinterpret_cast<Snapshot *>(buffer);
}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: fourth buffer snapshot
	* 3: oldest version still accepted
	* 4: snapshot records and +0x36D0 */
// ------------------------------------------------------------------------------------------------
void BaseHeightMapRenderObjClass::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 4 );
	*xfer == version;
	if( version.m_minimum < 3 )
		throw XferException::XFER_EXCEPTION_BFME_2;

	*xfer == *bufferSnapshot(m_treeBuffer);
	*xfer == *bufferSnapshot(m_shrubBuffer);
	*xfer == *bufferSnapshot(m_propBuffer);

	if( version.m_minimum >= 2 )
		*xfer == *bufferSnapshot(field3860);

	if( version.m_minimum >= 4 )
	{
		*xfer == m_numScorches;
		for( Int i = 0; i < m_numScorches; ++i )
			*xfer == snapshotRecords(this)[ i ];
		*xfer == field3798;
	}

}  // end xfer
