// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
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


// PlayerRelationMap::xfer and TeamRelationMap::xfer, ported from Zero Hour's
// GameEngine/Source/Common/RTS/Player.cpp and Team.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Each is slot 3 of
// the vftable whose name getter returns its class.
//
// BFME 2 opens with the light-CRC gate. PlayerRelationMap versions through
// Xfer +0x28; TeamRelationMap calls Version1. The STLport hash_map at +0x04
// (element count at +0x14) is reached through its out-of-line members. These
// are ICF-shared bodies already rowed under other hash_map spellings:
// begin() 0x00427195 (returned through a hidden pointer), iterator ++
// 0x0041E832, and operator[] 0x0041F4E5. They are viewed here per key type.
// The relationship goes through XferRelationship (0x00305C32).

#include <hash_map>

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

typedef unsigned short UnsignedShort;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

void XferRelationship( Xfer *xfer, Int *value );

typedef _STL::hash_map< Int, Relationship, _STL::hash<Int>, _STL::equal_to<Int> > PlayerRelationMapType;
typedef _STL::hash_map< UnsignedInt, Relationship, _STL::hash<UnsignedInt>, _STL::equal_to<UnsignedInt> > TeamRelationMapType;

// ------------------------------------------------------------------------------------------------
class PlayerRelationMap
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	PlayerRelationMapType m_map;																							///< 0x04
};

// ------------------------------------------------------------------------------------------------
class TeamRelationMap
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	TeamRelationMapType m_map;																								///< 0x04
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void PlayerRelationMap::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	// player relation count
	PlayerRelationMapType::iterator playerRelationIt;
	UnsignedShort playerRelationCount = m_map.size();
	*xfer == playerRelationCount;

	// player relations
	Int playerIndex;
	Int r;
	if( xfer->IsStoring() )
	{

		// go through all player relations
		for( playerRelationIt = m_map.begin(); playerRelationIt != m_map.end(); ++playerRelationIt )
		{

			// write player index
			playerIndex = (*playerRelationIt).first;
			*xfer == playerIndex;

			// write relationship
			r = (*playerRelationIt).second;
			XferRelationship( xfer, &r );

		}  // end for, playerRelationIt

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < playerRelationCount; ++i )
		{

			// read player index
			*xfer == playerIndex;

			// read relationship
			XferRelationship( xfer, &r );

			// assign relationship
			m_map[ playerIndex ] = (Relationship)r;

		}  // end for, i

	}  // end else, load

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TeamRelationMap::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// team relation count
	TeamRelationMapType::iterator teamRelationIt;
	UnsignedShort teamRelationCount = m_map.size();
	*xfer == teamRelationCount;

	// team relations
	UnsignedInt teamID;
	Int r;
	if( xfer->IsStoring() )
	{

		// go through all team relations
		for( teamRelationIt = m_map.begin(); teamRelationIt != m_map.end(); ++teamRelationIt )
		{

			// write team id
			teamID = (*teamRelationIt).first;
			*xfer == teamID;

			// write relationship
			r = (*teamRelationIt).second;
			XferRelationship( xfer, &r );

		}  // end for, teamRelationIt

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < teamRelationCount; ++i )
		{

			// read team id
			*xfer == teamID;

			// read relationship
			XferRelationship( xfer, &r );

			// assign relationship
			m_map[ teamID ] = (Relationship)r;

		}  // end for, i

	}  // end else, load

}  // end xfer
