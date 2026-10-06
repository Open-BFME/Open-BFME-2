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

// Snapshot xfer methods of the Zero Hour AIGuard.cpp states (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference) in BFME 2's Xfer
// spelling. Each is slot 3 of its state's vftable, identified by the
// slot-2 name getter. BFME 2 additions: the inner and outer states CRC
// their attack-state snapshot (+0x3C), the inner state gains a version-2
// UnsignedInt (+0x44), and the idle state keeps a Coord3D (+0x24) after
// ZH's scan time. Fields with no ZH counterpart keep offset names.

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

// ------------------------------------------------------------------------------------------------
class AIGuardInnerState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
	Snapshot *m_attackState;																									///< 0x3C
	char m_unrecovered40[ 0x44 - 0x40 ];
	UnsignedInt m_bfmeTime44;																									///< 0x44
};

// ------------------------------------------------------------------------------------------------
class AIGuardOuterState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];
	Snapshot *m_attackState;																									///< 0x3C
};

// ------------------------------------------------------------------------------------------------
class AIGuardReturnState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
	UnsignedInt m_nextReturnScanTime;																					///< 0x4C
};

// ------------------------------------------------------------------------------------------------
class AIGuardIdleState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x20 - 0x04 ];
	UnsignedInt m_nextEnemyScanTime;																					///< 0x20
	Coord3DBase m_bfmePosition24;																							///< 0x24
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGuardInnerState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 2 );
	*xfer == version;

	if( xfer->IsCRC() && m_attackState )
		*xfer == *m_attackState;

	if( version.m_minimum >= 2 )
		*xfer == m_bfmeTime44;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGuardOuterState::xfer( Xfer *xfer )
{
	xfer->Version1();

	if( xfer->IsCRC() && m_attackState )
		*xfer == *m_attackState;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGuardReturnState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_nextReturnScanTime;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGuardIdleState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_nextEnemyScanTime;
	*xfer == m_bfmePosition24;
}  // end xfer
