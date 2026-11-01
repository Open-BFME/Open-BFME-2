// cl: /DNDEBUG /MD /GX
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

// Script::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// ScriptEngine/Scripts.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose slot-2
// name getter returns Script. ZH's active flag (+0x40) goes through a local
// copy as in ZH. BFME 2 is at version 2 and adds an UnsignedInt (+0x3C).

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


typedef unsigned int UnsignedInt;

class Script
{
public:
	__declspec(dllimport) __forceinline Bool isActive( void ) const { return m_isActive; }
	__declspec(dllimport) __forceinline void setActive( Bool active ) { m_isActive = active; }
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
	UnsignedInt m_bfmeValue3C;																								///< 0x3C
	Bool m_isActive;																													///< 0x40
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: BFME 2 */
// ------------------------------------------------------------------------------------------------
void Script::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 2 );
	*xfer == version;

	// active
	Bool active = isActive();
	*xfer == active;
	setActive( active );

	if( version.m_minimum >= 2 )
		*xfer == m_bfmeValue3C;

}  // end xfer
