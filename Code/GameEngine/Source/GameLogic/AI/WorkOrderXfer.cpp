// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
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


// WorkOrder::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIPlayer.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "WorkOrder".
//
// BFME 2 opens with the light-CRC gate and Version1. ZH's inline template-name
// round trip becomes the free helper 0x003063A9: it saves the template name
// (or the empty string) and on load looks it up through the thing factory.
// ZH's fields follow, then BFME 2's Int, AsciiString, UnsignedInt and two
// flags. A last Int (+0x2C) is written from a copy and not read back.

#include "ascii_string.h"

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class ThingTemplate;

void Rva003063A9XferThingTemplate( Xfer *xfer, const ThingTemplate **thing );

class WorkOrder
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	const ThingTemplate *m_thing;																							///< 0x04
	ObjectID m_factoryID;																											///< 0x08
	char m_unrecovered0C[ 0x10 - 0x0C ];
	Int m_numCompleted;																												///< 0x10
	Int m_numRequired;																												///< 0x14
	Bool m_required;																													///< 0x18
	Bool m_isResourceGatherer;																								///< 0x19
	Int m_bfmeInt1C;																													///< 0x1C
	AsciiString m_bfmeString20;																								///< 0x20
	UnsignedInt m_bfmeUnsigned24;																							///< 0x24
	Bool m_bfmeFlag28;																												///< 0x28
	Bool m_bfmeFlag29;																												///< 0x29
	Int m_bfmeInt2C;																													///< 0x2C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void WorkOrder::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// thing template
	Rva003063A9XferThingTemplate( xfer, &m_thing );

	// factory id
	XferObjectID( xfer, &m_factoryID );

	// num completed
	*xfer == m_numCompleted;

	// num required
	*xfer == m_numRequired;

	// is required
	*xfer == m_required;

	// is resource gatherer
	*xfer == m_isResourceGatherer;

	*xfer == m_bfmeInt1C;
	*xfer == m_bfmeString20;
	*xfer == m_bfmeUnsigned24;
	*xfer == m_bfmeFlag28;
	*xfer == m_bfmeFlag29;

	Int value2C = m_bfmeInt2C;
	*xfer == value2C;

}  // end xfer
