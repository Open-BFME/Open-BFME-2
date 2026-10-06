// cl: /DNDEBUG /MD /GX
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

// Snapshot xfer methods of Zero Hour AITNGuard.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference) in BFME 2's Xfer spelling,
// identified as slot 3 of the vftables whose slot-2 name getters return
// AITNGuardInnerState, AITNGuardReturnState and AITNGuardMachine.
// BFME 2 differences: the inner state xfers a Bool (+0x28); the return state
// runs AIEnterState's xfer (0x00341930) and the light-CRC early-out before
// its version; the machine runs the StateMachine base first, then the
// light-CRC early-out and Version(1,2), with four version-2 raw bytes
// (+0x4C) after ZH's nemesis and guard position.

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

// The state base: only its virtual table matters to these bodies.
class State
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

class StateMachine
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class AIEnterState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------
class AITNGuardInnerState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x28 - 0x04 ];
	Bool m_bfmeFlag28;																												///< 0x28
};

// ------------------------------------------------------------------------------------------------
class AITNGuardReturnState : public AIEnterState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x54 - 0x04 ];
	UnsignedInt m_nextReturnScanTime;																					///< 0x54
};

// ------------------------------------------------------------------------------------------------
class AITNGuardMachine : public StateMachine
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
	Coord3DBase m_positionToGuard;																						///< 0x3C
	ObjectID m_nemesisToAttack;																								///< 0x48
	UnsignedInt m_bfmeRaw4C;																									///< 0x4C
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardInnerState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_bfmeFlag28;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardReturnState::xfer( Xfer *xfer )
{
	AIEnterState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	xfer->Version1();
	*xfer == m_nextReturnScanTime;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardMachine::xfer( Xfer *xfer )
{
	StateMachine::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	Xfer::Version version( 1, 2 );
	*xfer == version;
	XferObjectID( xfer, &m_nemesisToAttack );
	*xfer == m_positionToGuard;
	if( version.m_minimum >= 2 )
		xfer->XferRawBytes( &m_bfmeRaw4C, 4 );
}  // end xfer
