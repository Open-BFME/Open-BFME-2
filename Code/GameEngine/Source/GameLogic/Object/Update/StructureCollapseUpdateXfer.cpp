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


// StructureCollapseUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/StructureCollapseUpdate.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). It is slot 3 of the
// vftable whose name getter returns "StructureCollapseUpdate".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's fields and three more BFME 2 Reals
// (+0x38..+0x40).

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

typedef float Real;

enum StructureCollapseStateType
{
	COLLAPSESTATE_STANDING
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x24 - 0x04 ];
};

class StructureCollapseUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_collapseFrame;																							///< 0x24
	UnsignedInt m_burstFrame;																									///< 0x28
	StructureCollapseStateType m_collapseState;																///< 0x2C
	Real m_collapseVelocity;																									///< 0x30
	Real m_currentHeight;																											///< 0x34
	Real m_bfmeReal38;																												///< 0x38
	Real m_bfmeReal3C;																												///< 0x3C
	Real m_bfmeReal40;																												///< 0x40
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void StructureCollapseUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// collapse frame
	*xfer == m_collapseFrame;

	// burst frame
	*xfer == m_burstFrame;

	// collapse state
	xfer->XferRawBytes( &m_collapseState, sizeof( StructureCollapseStateType ) );

	// collapse velocity
	*xfer == m_collapseVelocity;

	// current height
	*xfer == m_currentHeight;

	*xfer == m_bfmeReal38;
	*xfer == m_bfmeReal3C;
	*xfer == m_bfmeReal40;

}  // end xfer
