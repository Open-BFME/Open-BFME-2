// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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


// AIGuardMachine::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// AI/AIGuard.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "AIGuardMachine".
//
// BFME 2 order: the light-CRC gate, then the StateMachine base (0x004D7744)
// unconditionally, then Version(1, 3) and ZH's fields. BFME 2 adds a frame
// (+0x40), a second Coord3D (+0x54) and a flag (+0x60). Version 2 adds a raw
// dword (+0x6C) and an UnsignedInt (+0x70). The trigger area round trip uses
// the area's name at +0x40 and TerrainLogic slot 39 (+0x9C, the area lookup
// by name). Version 3 adds a Real (+0x64).

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
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class PolygonTrigger
{
public:
	const AsciiString &getTriggerName( void ) const { return m_triggerName; }
private:
	char m_unrecovered00[ 0x40 ];
	AsciiString m_triggerName;																								///< 0x40
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38();
	virtual PolygonTrigger *getTriggerAreaByName( const AsciiString &name );	///< slot 39
};
extern TerrainLogic *TheTerrainLogic;

class StateMachine
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
};

class AIGuardMachine : public StateMachine
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	ObjectID m_targetToGuard;																									///< 0x3C
	UnsignedInt m_bfmeFrame40;																								///< 0x40
	PolygonTrigger *m_areaToGuard;																						///< 0x44
	Coord3DBase m_positionToGuard;																						///< 0x48
	Coord3DBase m_bfmePosition54;																							///< 0x54
	Bool m_bfmeFlag60;																												///< 0x60
	Real m_bfmeReal64;																												///< 0x64
	ObjectID m_nemesisToAttack;																								///< 0x68
	UnsignedInt m_bfmeRaw6C;																									///< 0x6C
	UnsignedInt m_bfmeUnsigned70;																							///< 0x70
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: +0x6C and +0x70
	* 3: +0x64 */
// ------------------------------------------------------------------------------------------------
void AIGuardMachine::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	StateMachine::xfer(xfer);

  // version
	Xfer::Version version( 1, 3 );
	*xfer == version;

	XferObjectID( xfer, &m_targetToGuard );
	*xfer == m_bfmeFrame40;
	XferObjectID( xfer, &m_nemesisToAttack );
	*xfer == m_positionToGuard;
	*xfer == m_bfmePosition54;
	*xfer == m_bfmeFlag60;

	if( version.m_minimum >= 2 )
	{
		xfer->XferRawBytes( &m_bfmeRaw6C, 4 );
		*xfer == m_bfmeUnsigned70;
	}

	AsciiString triggerName;
	if (m_areaToGuard) triggerName = m_areaToGuard->getTriggerName();
	*xfer == triggerName;
	if( xfer->IsLoading() )
	{
		if (!triggerName.isEmpty()) {
			m_areaToGuard = TheTerrainLogic->getTriggerAreaByName(triggerName);
		}
	}

	if( version.m_minimum >= 3 )
		*xfer == m_bfmeReal64;

}  // end xfer
