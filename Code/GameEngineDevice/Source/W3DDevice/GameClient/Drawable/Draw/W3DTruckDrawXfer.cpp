// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /GX
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

// W3DTruckDraw::xfer, ported from Zero Hour's GameEngineDevice/Source/W3DDevice/
// GameClient/Drawable/Draw/W3DTruckDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "W3DTruckDraw": the version, then the base model draw's
// xfer, W3DScriptedModelDraw in BFME 2 (0x000C5C04).
//
// BFME 2 adds state that ZH does not save. Two flags are saved before the
// base (+0x2E9, +0x2EA). Outside a light CRC, two 0x88-byte audio events
// follow (+0x374, +0x3FC). Their non-virtual xfer is 0x002D9FD9, which also
// runs the Rva002D9608 audio gate on the same object.

#include "Common/BfmeAudioEventPrefix136.h"

class Rva002D9FD9Arg;
#include "../../../../../Include/Rva002D9FD9Owner.h"

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

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../../../GameEngine/Include/Common/XferVersion.h"

class W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
};

class W3DTruckDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x2E9 - 0x04 ];
	bool m_bfmeFlag2E9;																												///< 0x2E9
	bool m_bfmeFlag2EA;																												///< 0x2EA
	char m_unrecovered2EB[ 0x374 - 0x2EB ];
	BfmeAudioEventPrefix136 m_bfmeAudio374;																		///< 0x374
	BfmeAudioEventPrefix136 m_bfmeAudio3FC;																		///< 0x3FC
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTruckDraw::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	*xfer == m_bfmeFlag2E9;
	*xfer == m_bfmeFlag2EA;

	// extend base class
	W3DScriptedModelDraw::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	((Rva002D9FD9Owner *)&m_bfmeAudio374)->rva002D9FD9( (Rva002D9FD9Arg *)xfer );
	((Rva002D9FD9Owner *)&m_bfmeAudio3FC)->rva002D9FD9( (Rva002D9FD9Arg *)xfer );

}  // end xfer
