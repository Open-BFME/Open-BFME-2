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

#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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

class Object;

enum ObjectID { INVALID_ID = 0 };

enum NameKeyType { NK_UNKNOWN = 0 };

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

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

// One garrison point record: 40 of them at +0x100, 0x14 bytes each (the
// constructor 0x00477F06 zeroes five dwords per record, the matched
// put/remove bodies store the object and target IDs and the place frame).
struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	int effect;
};

enum
{
	MAX_GARRISON_POINTS = 40,
	MAX_GARRISON_POINT_CONDITIONS = 3
};

// OpenContain's nine vftable-bearing bases, positional. The GarrisonContain
// constructor 0x00477F06 (and the destructor 0x00478067, which restores the
// same tables) stores nine vftables: +0x00 0x00C461F8 (28 slots), +0x0C
// 0x00C43528 (47), +0x10 0x00C46560 (3), +0x20 0x00C46080 (94), +0x24
// 0x00C46064 (6), +0x28 0x00C46F78 (1), +0x2C 0x00C463D8 (4), +0x30
// 0x00C46034 (12) and +0x34 0x00C48B28 (4), and its first own member is
// +0xFC. B0 holds the module's data and object pointers (+0x04, +0x08); B2
// the 12 update bytes before +0x20; B8 OpenContain's data to +0xFC. Only the
// slots a body of this TU needs are declared. The +0x20 table's slot 76 is
// calcBestGarrisonPosition (0x00478547), so B3 introduces it and its
// override is entered with the +0x20 this.
class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };

class B1 { public: virtual void b1(); };

class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };

class B3 { public: virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *); };

class B4 { public: virtual void b4(); };

class B5 { public: virtual void b5(); };

class B6 { public: virtual void b6(); };

class B7 { public: virtual void b7(); };

class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class Xfer;

// OpenContain's own virtuals as the bodies call them by name: xfer (primary
// slot 3) and loadPostProcess through explicit OpenContain:: calls, and
// removeAllContained, which the matched 0x00478231 calls on its +0x20
// receiver unchanged.
class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
    friend class Rva004697E1Contain;
public:
    virtual ~OpenContain();
    virtual void removeAllContained(bool exposeStealthUnits);
    Object *getObject() const { return m_object; }
protected:
    virtual void xfer(Xfer *xfer);
    virtual void loadPostProcess();
};

// GarrisonContain over the 0xFC-byte OpenContain. Offsets from the matched
// bodies: +0xFC original team id (xfer 0x00478260), +0x100 point records,
// +0x420 points in use, +0x424 the 3x40 garrison points (put 0x00477DA1,
// remove 0x00477E82, calcBestGarrisonPosition 0x00478547), +0x9C4 the
// per-condition point counts (findClosestFreeGarrisonPointIndex 0x00478445),
// +0x9D0 the exit rally point and the +0x9DC/+0x9DD/+0x9DE flags (xfer,
// validateRallyPoint 0x00478141). The primary table 0x00C461F8 holds the
// pool key at slot 4 (0x0047801C).
class GarrisonContain : public OpenContain
{
    friend class Rva00478231;
public:
    virtual NameKeyType getModuleNameKey() const;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    virtual void xfer(Xfer *xfer);
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
    void validateRallyPoint();
private:
    unsigned int m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
    int m_numGarrisonPoints[MAX_GARRISON_POINT_CONDITIONS]; // +0x9C4
    Coord3D m_exitRallyPoint; // +0x9D0
    bool m_garrisonPointsInitialized; // +0x9DC
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
    bool m_rallyValid; // +0x9DE
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
	if( TheTeamFactory->findTeamByID( m_originalTeamID ) == 0 )
		m_originalTeamID = 0;
	*xfer == m_originalTeamID;
	if( xfer->IsLoading() )
	{

		if( m_originalTeamID != 0 && TheTeamFactory->findTeamByID( m_originalTeamID ) == 0 )
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
		XferDrawableID( xfer, &m_garrisonPointData[ i ].effect );
	}  // end for i

	// garrison points in use
	*xfer == m_garrisonPointsInUse;

	// garrison points
	for( i = 0; i < MAX_GARRISON_POINT_CONDITIONS; ++i )
		for( Int j = 0; j < MAX_GARRISON_POINTS; ++j )
			*xfer == (Coord3DBase &)m_garrisonPoint[ i ][ j ];

	// garrison points initialized
	*xfer == m_garrisonPointsInitialized;

	// rally valid
	*xfer == m_rallyValid;

	// exit rally point
	*xfer == (Coord3DBase &)m_exitRallyPoint;

}  // end xfer
