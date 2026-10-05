// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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


// BuildListInfo::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Map/SidesList.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter (0x00329EE3) returns "BuildListInfo". The layout is the one
// established by the matched assignment (BuildListInfoAssign.cpp, 0x003299AD).
//
// BFME 2 opens with the light-CRC gate and Version1, and drops ZH's version-2
// check on m_currentGatherers. It writes the resource gatherers one ObjectID
// at a time instead of ZH's xferUser block.

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
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class Coord2D
{
public:
	float x;
	float y;
};

class BuildListInfo
{
public:
	enum { MAX_RESOURCE_GATHERERS = 10 };
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	AsciiString m_buildingName;																								///< 0x04
	AsciiString m_templateName;																								///< 0x08
	Coord3DBase m_location;																										///< 0x0C
	Coord2D m_rallyPointOffset;																								///< 0x18
	Real m_angle;																															///< 0x20
	Bool m_isInitiallyBuilt;																									///< 0x24
	UnsignedInt m_numRebuilds;																								///< 0x28
	BuildListInfo *m_nextBuildList;																						///< 0x2C
	AsciiString m_script;																											///< 0x30
	Int m_health;																															///< 0x34
	Bool m_whiner;																														///< 0x38
	Bool m_unsellable;																												///< 0x39
	Bool m_repairable;																												///< 0x3A
	Bool m_automaticallyBuild;																								///< 0x3B
	void *m_renderObj;																												///< 0x3C
	void *m_shadowObj;																												///< 0x40
	Bool m_selected;																													///< 0x44
	Bool m_underConstruction;																									///< 0x45
	Bool m_isSupplyBuilding;																									///< 0x46
	Bool m_priorityBuild;																											///< 0x47
	ObjectID m_objectID;																											///< 0x48
	UnsignedInt m_objectTimestamp;																						///< 0x4C
	ObjectID m_resourceGatherers[ MAX_RESOURCE_GATHERERS ];										///< 0x50
	Int m_desiredGatherers;																										///< 0x78
	Int m_currentGatherers;																										///< 0x7C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BuildListInfo::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();
	*xfer == m_buildingName;
	*xfer == m_templateName;
	*xfer == m_location;
	*xfer == m_rallyPointOffset;
	*xfer == m_angle;
	*xfer == m_isInitiallyBuilt;
	*xfer == m_numRebuilds;
	*xfer == m_script;
	*xfer == m_health;
	*xfer == m_whiner;
	*xfer == m_unsellable;
	*xfer == m_repairable;
	*xfer == m_automaticallyBuild;
	// m_renderObj we don't need to xfer this, its for the editor only
	// m_shadowObj we don't need to xfer this, its for the editor only
	// m_selected we don't need to xfer this, its for the editor only
	XferObjectID( xfer, &m_objectID );
	*xfer == m_objectTimestamp;
	*xfer == m_underConstruction;
	for( Int i = 0; i < MAX_RESOURCE_GATHERERS; ++i )
		XferObjectID( xfer, &m_resourceGatherers[ i ] );
	*xfer == m_isSupplyBuilding;
	*xfer == m_desiredGatherers;
	*xfer == m_priorityBuild;
	*xfer == m_currentGatherers;
}  // end xfer
