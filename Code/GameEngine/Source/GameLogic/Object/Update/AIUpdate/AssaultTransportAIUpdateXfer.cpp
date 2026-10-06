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


// AssaultTransportAIUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). It is slot 3
// of the vftable whose name getter returns "AssaultTransportAIUpdate".
//
// BFME 2 order: the AIUpdateInterface base (0x00267EDD) first, then the
// light-CRC gate and Version1, then ZH's fields at +0x3E8..+0x441 and one more
// BFME 2 flag (+0x442).

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

enum AssaultStateTypes
{
	IDLE
};

enum { MAX_TRANSPORT_SLOTS = 10 };

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3E8 - 0x04 ];
};

class AssaultTransportAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	ObjectID m_memberIDs[ MAX_TRANSPORT_SLOTS ];															///< 0x3E8
	Bool m_memberHealing[ MAX_TRANSPORT_SLOTS ];															///< 0x410
	char m_unrecovered41A[ 0x424 - 0x41A ];
	Coord3DBase m_attackMoveGoalPos;																					///< 0x424
	ObjectID m_designatedTarget;																							///< 0x430
	AssaultStateTypes m_state;																								///< 0x434
	UnsignedInt m_framesRemaining;																						///< 0x438
	Int m_currentMembers;																											///< 0x43C
	Bool m_isAttackMove;																											///< 0x440
	Bool m_isAttackObject;																										///< 0x441
	Bool m_bfmeFlag442;																												///< 0x442
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AssaultTransportAIUpdate::xfer( Xfer *xfer )
{

 // extend base class
	AIUpdateInterface::xfer(xfer);

	if( xfer->IsLightCRC() )
		return;

  // version
	xfer->Version1();

	*xfer == m_currentMembers;

	for( int i = 0; i < m_currentMembers; i++ )
	{
		XferObjectID( xfer, &(m_memberIDs[ i ]) );
		*xfer == m_memberHealing[ i ];
	}

	*xfer == m_attackMoveGoalPos;
	XferObjectID( xfer, &m_designatedTarget );

	Int state = (Int)m_state;
	*xfer == state;
	m_state = (AssaultStateTypes)state;

	*xfer == m_framesRemaining;
	*xfer == m_isAttackMove;
	*xfer == m_isAttackObject;
	*xfer == m_bfmeFlag442;

}  // end xfer
