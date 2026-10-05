// cl: /O1 /DNDEBUG /MD
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


// Anim2D::xfer, ported from Zero Hour's GameEngine/Source/GameClient/System/
// Anim2D.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) onto the BFME 2 layout. It is slot 3
// of the vftable whose name getter returns "Anim2D".
//
// BFME 2 bumps the version to (1, 2). Version 2 adds an ICoord2D at +0x2C
// after ZH's fields.

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


typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef float Real;

class ICoord2D
{
public:
	int x;
	int y;
};

class Anim2D
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	UnsignedShort m_currentFrame;																							///< 0x04
	UnsignedInt m_lastUpdateFrame;																						///< 0x08
	char m_unrecovered0C[ 0x10 - 0x0C ];
	UnsignedByte m_status;																										///< 0x10
	UnsignedShort m_minFrame;																									///< 0x12
	UnsignedShort m_maxFrame;																									///< 0x14
	UnsignedInt m_framesBetweenUpdates;																				///< 0x18
	Real m_alpha;																															///< 0x1C
	char m_unrecovered20[ 0x2C - 0x20 ];
	ICoord2D m_bfmeOffset2C;																									///< 0x2C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: BFME 2 ICoord2D at +0x2C */
// ------------------------------------------------------------------------------------------------
void Anim2D::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 2 );
	*xfer == version;

	// current frame
	*xfer == m_currentFrame;

	// last update frame
	*xfer == m_lastUpdateFrame;

	// status
	*xfer == m_status;

	// min frame
	*xfer == m_minFrame;

	// max frame
	*xfer == m_maxFrame;

	// frames between updates
	*xfer == m_framesBetweenUpdates;

	// alpha
	*xfer == m_alpha;

	if( version.m_minimum >= 2 )
		*xfer == m_bfmeOffset2C;

}  // end xfer
