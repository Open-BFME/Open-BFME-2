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


// PhysicsBehavior::xfer, from the slot-3 xfer of the vftable whose name
// getter returns "PhysicsBehavior". Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/PhysicsUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) gives the shape: version, the
// UpdateModule base (0x0044DF9F), then the motion state.
//
// BFME 2's field set and order differ from ZH's. The names below are neutral
// offsets because only the transfer kinds are known: two Coord3Ds, two Reals,
// four Ints and four flags. Version 2 adds a Coord3D vector at +0x20. Loading
// clears it first (the vector erase 0x002A133B, already viewed as
// AICommandCoordVector), and the shared vector transfer 0x00390911 does the
// rest.

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
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct AICommandCoordVector
{
	Coord3D *erase( Coord3D *first, Coord3D *last );
	void clear( void ) { erase( m_start, m_finish ); }
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_endOfStorage;
};

void Rva00390911XferCoordVector( Xfer *xfer, AICommandCoordVector *coords );

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x20 - 0x04 ];
};

class PhysicsBehavior : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AICommandCoordVector m_bfmeCoords20;																			///< 0x20
	Coord3DBase m_bfmeCoord2C;																								///< 0x2C
	Coord3DBase m_bfmeCoord38;																								///< 0x38
	Real m_bfmeReal44;																												///< 0x44
	Real m_bfmeReal48;																												///< 0x48
	Int m_bfmeInt4C;																													///< 0x4C
	Int m_bfmeInt50;																													///< 0x50
	Int m_bfmeInt54;																													///< 0x54
	Int m_bfmeInt58;																													///< 0x58
	Bool m_bfmeFlag5C;																												///< 0x5C
	Bool m_bfmeFlag5D;																												///< 0x5D
	Bool m_bfmeFlag5E;																												///< 0x5E
	Bool m_bfmeFlag5F;																												///< 0x5F
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: coordinate vector at +0x20 */
// ------------------------------------------------------------------------------------------------
void PhysicsBehavior::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 2 );
	*xfer == version;

	// extend base class
	UpdateModule::xfer( xfer );

	*xfer == m_bfmeInt4C;
	*xfer == m_bfmeReal44;
	*xfer == m_bfmeReal48;
	*xfer == m_bfmeCoord2C;
	*xfer == m_bfmeCoord38;
	*xfer == m_bfmeInt58;
	*xfer == m_bfmeFlag5C;
	*xfer == m_bfmeFlag5D;
	*xfer == m_bfmeInt54;
	*xfer == m_bfmeFlag5E;
	*xfer == m_bfmeFlag5F;
	*xfer == m_bfmeInt50;

	if( version.m_minimum >= 2 )
	{
		if( xfer->IsLoading() )
			m_bfmeCoords20.clear();
		Rva00390911XferCoordVector( xfer, &m_bfmeCoords20 );
	}

}  // end xfer
