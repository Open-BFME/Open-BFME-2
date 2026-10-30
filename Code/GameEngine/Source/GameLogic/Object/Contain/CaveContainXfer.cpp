// cl: /DNDEBUG /MD /EHsc
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


// CaveContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/CaveContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "CaveContain".
//
// BFME 2 order: the OpenContain base (0x00465EF1) first, then the light-CRC
// gate and Version1, then ZH's fields (+0x100 flag, +0x104 cave index, +0x108
// original team, saved by its id at Team+0x34). On load the team comes back
// through the team factory lookup 0x0039F761, held in the ledger as
// TeamFactory::findTeamByID. ZH's throw SC_INVALID_DATA becomes BFME 2's
// XferException with tag 5 and no text (constructor 0x0060C36E).

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};


typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

#include "../../../../Include/Common/TeamBFME2.h"

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class OpenContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class CaveContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x100 - 0x04 ];
	Bool m_needToRunOnBuildComplete;																					///< 0x100
	Int m_caveIndex;																													///< 0x104
	Team *m_originalTeam;																											///< 0x108
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void CaveContain::xfer( Xfer *xfer )
{

	// extend base class
	OpenContain::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// need to run on build complete
	*xfer == m_needToRunOnBuildComplete;

	// cave index
	*xfer == m_caveIndex;

	// original team
	UnsignedInt teamID = m_originalTeam ? m_originalTeam->getID() : 0;
	*xfer == teamID;
	if( xfer->IsLoading() )
	{

		if( teamID != 0 )
		{

			m_originalTeam = TheTeamFactory->findTeamByID( teamID );
			if( m_originalTeam == 0 )
				throw XferException( 5, 0 );

		}  // end if
		else
			m_originalTeam = 0;

	}  // end if

}  // end xfer
