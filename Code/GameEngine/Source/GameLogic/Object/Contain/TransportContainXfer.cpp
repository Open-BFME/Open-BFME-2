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

// TransportContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/TransportContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Slot 3 of ??_7TransportContain.
// BFME 2 writes the version before the OpenContain base xfer (slot 3 of
// OpenContain's vftable, 0x00465EF1) and has no light-CRC early-out. Its
// fields are m_extraSlotsInUse +0x100 (int), m_frameExitNotBusy +0x104
// (UnsignedInt) and m_payloadCreated +0x10C (Bool), transferred in that
// order. Offsets come from the bodies; the names are ZH's for the same
// three fields.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/ScalarTypes.h"



class OpenContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x100 - 0x04 ];
};

class TransportContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_extraSlotsInUse;																										///< 0x100
	UnsignedInt m_frameExitNotBusy;																						///< 0x104
	char m_unrecovered108[ 0x10C - 0x108 ];
	Bool m_payloadCreated;																										///< 0x10C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TransportContain::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// extend base class
	OpenContain::xfer( xfer );

	// extra slots in use
	*xfer == m_extraSlotsInUse;

	// frame exit not busy
	*xfer == m_frameExitNotBusy;

	// payload created
	*xfer == m_payloadCreated;

}  // end xfer
