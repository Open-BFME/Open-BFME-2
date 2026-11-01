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


// RadarObject::xfer, ported from Zero Hour's GameEngine/Source/Common/System/
// Radar.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "RadarObject".
//
// BFME 2 puts the light-CRC gate ahead of ZH's version. ZH's throw
// SC_INVALID_DATA becomes XferException tag 5 (constructor 0x0060C36E). The
// object keeps its radar data at +0x260 and its id at +0x74.

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

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

typedef int Color;

#include "../GameLogicObjectLookupView.h"

void XferObjectID( Xfer *xfer, ObjectID *value );

#include "../../../Include/Common/XferException.h"

class RadarObject;

class Object
{
public:
	ObjectID getID( void ) const { return m_id; }
	void friend_setRadarData( RadarObject *rd ) { m_radarData = rd; }
private:
	char m_unrecovered00[ 0x74 ];
	ObjectID m_id;																														///< 0x74
	char m_unrecovered78[ 0x260 - 0x78 ];
	RadarObject *m_radarData;																									///< 0x260
};

extern GameLogic *TheGameLogic;

class RadarObject
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	Object *m_object;																													///< 0x04
	RadarObject *m_next;																											///< 0x08
	Color m_color;																														///< 0x0C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void RadarObject::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	// object id
	ObjectID objectID = m_object ? m_object->getID() : INVALID_OBJECT_ID;
	XferObjectID( xfer, &objectID );
	if( xfer->IsLoading() )
	{

		// find the object and save
		m_object = TheGameLogic->findObjectByID( objectID );
		if( m_object == 0 )
			throw XferException( 5, 0 );

		// tell the object we now have some radar data
		m_object->friend_setRadarData( this );

	}  // end if

	// color
	*xfer == m_color;

}  // end xfer
