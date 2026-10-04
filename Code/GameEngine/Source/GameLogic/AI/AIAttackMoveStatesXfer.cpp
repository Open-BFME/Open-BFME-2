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


// AIAttackApproachTargetState::xfer and AIAttackPursueTargetState::xfer,
// ported from Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
// Slot 3 of vftables 0x00C12610 (name getter 0x00342972,
// "AIAttackApproachTargetState") and 0x00C12730 (0x00342A4A,
// "AIAttackPursueTargetState"). A second vftable (0x00C12678) shares the
// approach name getter with a different 128-byte xfer (0x00340623); it is a
// BFME 2 variant, AIAttackApproachTargetState00C12678 (address-derived name,
// see AIAttackApproachTargetStateOnExit.cpp), whose fields are named here by
// offset and xfer type only: of them only +0x61 (the initial-approach flag
// its onExit clears) has a known meaning.
//
// Both run the AIInternalMoveToState base (0x0033FF76), then the light-CRC
// gate, then ZH's fields. BFME 2 adds fields after them. The approach state
// versions through Xfer +0x28; the pursue state calls Version1 ahead of its
// base.

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

class AIInternalMoveToState
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
};

// ------------------------------------------------------------------------------------------------
class AIAttackApproachTargetState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Coord3DBase m_prevVictimPos;																							///< 0x4C
	Coord3DBase m_bfmePosition58;																							///< 0x58
	UnsignedInt m_approachTimestamp;																					///< 0x64
	UnsignedInt m_bfmeFrame68;																								///< 0x68
	Bool m_follow;																														///< 0x6C
	Bool m_isAttackingObject;																									///< 0x6D
	Bool m_stopIfInRange;																											///< 0x6E
	Bool m_isInitialApproach;																									///< 0x6F
	Bool m_bfmeFlag70;																												///< 0x70
	Bool m_bfmeFlag71;																												///< 0x71
};

// ------------------------------------------------------------------------------------------------
class AIAttackPursueTargetState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Coord3DBase m_prevVictimPos;																							///< 0x4C
	UnsignedInt m_approachTimestamp;																					///< 0x58
	Bool m_follow;																														///< 0x5C
	Bool m_isAttackingObject;																									///< 0x5D
	Bool m_stopIfInRange;																											///< 0x5E
	Bool m_isInitialApproach;																									///< 0x5F
	Bool m_bfmeFlag60;																												///< 0x60
};

// ------------------------------------------------------------------------------------------------
class AIAttackApproachTargetState00C12678 : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Coord3DBase m_bfmePosition4C;																							///< 0x4C
	UnsignedInt m_bfmeFrame58;																								///< 0x58
	UnsignedInt m_bfmeFrame5C;																								///< 0x5C
	Bool m_bfmeFlag60;																												///< 0x60
	Bool m_isInitialApproach;																									///< 0x61
	Bool m_bfmeFlag62;																												///< 0x62
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AIAttackApproachTargetState::xfer( Xfer *xfer )
{
  // version
	Xfer::Version version( 1, 1 );
	*xfer == version;

 // extend base class
  AIInternalMoveToState::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	*xfer == m_prevVictimPos;
	*xfer == m_approachTimestamp;
	*xfer == m_follow;
	*xfer == m_isAttackingObject;
	*xfer == m_stopIfInRange;
	*xfer == m_isInitialApproach;
	*xfer == m_bfmePosition58;
	*xfer == m_bfmeFrame68;
	*xfer == m_bfmeFlag71;
	*xfer == m_bfmeFlag70;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AIAttackPursueTargetState::xfer( Xfer *xfer )
{
  // version
	xfer->Version1();

 // extend base class
  AIInternalMoveToState::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	*xfer == m_prevVictimPos;
	*xfer == m_approachTimestamp;
	*xfer == m_follow;
	*xfer == m_isAttackingObject;
	*xfer == m_stopIfInRange;
	*xfer == m_isInitialApproach;
	*xfer == m_bfmeFlag60;
}  // end xfer

// ------------------------------------------------------------------------------------------------
void AIAttackApproachTargetState00C12678::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;

	AIInternalMoveToState::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	*xfer == m_bfmeFrame58;
	*xfer == m_bfmeFlag60;
	*xfer == m_isInitialApproach;
	*xfer == m_bfmePosition4C;
	*xfer == m_bfmeFrame5C;
	*xfer == m_bfmeFlag62;
}  // end xfer
