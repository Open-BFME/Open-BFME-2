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


// GarrisonContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/GarrisonContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "GarrisonContain".
//
// BFME 2 order: the OpenContain base (0x00465EF1) first, then the light-CRC
// gate and Version1. BFME 2 keeps the original team as an id at +0xFC rather
// than ZH's Team pointer. An id the team factory (0x0039F761) no longer knows
// is cleared before saving, and on load an unknown id throws XferException
// tag 5 (constructor 0x0060C36E) where ZH throws SC_INVALID_DATA. The
// garrison point records are transferred in place, with no save/load split.
// ZH's raw garrison-point block becomes one Coord3D at a time.

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

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
typedef unsigned short UnsignedShort;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );
void XferDrawableID( Xfer *xfer, Int *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Team;

class Rva0039F761Owner
{
public:
	Team *findInstance( void *prototypeKey );
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

class GarrisonContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	enum { MAX_GARRISON_POINTS = 40 };
	enum { MAX_GARRISON_POINT_CONDITIONS = 3 };

	struct GarrisonPointData
	{
		ObjectID objectID;
		ObjectID targetID;
		UnsignedInt placeFrame;
		UnsignedInt lastEffectFrame;
		Int effectID;
	};

	static Team *findTeamByID( UnsignedInt id )
	{
		return ((Rva0039F761Owner *)TheTeamFactory)->findInstance( (void *)id );
	}

	char m_unrecovered04[ 0xFC - 0x04 ];
	UnsignedInt m_originalTeamID;																							///< 0xFC
	GarrisonPointData m_garrisonPointData[ MAX_GARRISON_POINTS ];							///< 0x100
	Int m_garrisonPointsInUse;																								///< 0x420
	Coord3DBase m_garrisonPoint[ MAX_GARRISON_POINT_CONDITIONS ][ MAX_GARRISON_POINTS ];	///< 0x424
	char m_unrecovered9C4[ 0x9D0 - 0x9C4 ];
	Coord3DBase m_exitRallyPoint;																							///< 0x9D0
	Bool m_garrisonPointsInitialized;																					///< 0x9DC
	Bool m_hideGarrisonedStateFromNonallies;																	///< 0x9DD
	Bool m_rallyValid;																												///< 0x9DE
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void GarrisonContain::xfer( Xfer *xfer )
{
	Int i;

	// extend base class
	OpenContain::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// original team
	if( findTeamByID( m_originalTeamID ) == 0 )
		m_originalTeamID = 0;
	*xfer == m_originalTeamID;
	if( xfer->IsLoading() )
	{

		if( m_originalTeamID != 0 && findTeamByID( m_originalTeamID ) == 0 )
			throw XferException( 5, 0 );

	}  // end if

	*xfer == m_hideGarrisonedStateFromNonallies;

	// garrison point data
	UnsignedShort pointDataCount = MAX_GARRISON_POINTS;
	*xfer == pointDataCount;
	for( i = 0; i < pointDataCount; ++i )
	{
		XferObjectID( xfer, &m_garrisonPointData[ i ].objectID );
		XferObjectID( xfer, &m_garrisonPointData[ i ].targetID );
		*xfer == m_garrisonPointData[ i ].placeFrame;
		*xfer == m_garrisonPointData[ i ].lastEffectFrame;
		XferDrawableID( xfer, &m_garrisonPointData[ i ].effectID );
	}  // end for i

	// garrison points in use
	*xfer == m_garrisonPointsInUse;

	// garrison points
	for( i = 0; i < MAX_GARRISON_POINT_CONDITIONS; ++i )
		for( Int j = 0; j < MAX_GARRISON_POINTS; ++j )
			*xfer == m_garrisonPoint[ i ][ j ];

	// garrison points initialized
	*xfer == m_garrisonPointsInitialized;

	// rally valid
	*xfer == m_rallyValid;

	// exit rally point
	*xfer == m_exitRallyPoint;

}  // end xfer
