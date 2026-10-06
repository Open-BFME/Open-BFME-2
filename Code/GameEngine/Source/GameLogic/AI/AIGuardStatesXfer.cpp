// cl: /Ireference/shims/moduledata /DNDEBUG /MD /GX
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


// AIGuardRetaliateState::xfer and AITunnelNetworkGuardState::xfer, ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Each is slot 3 of
// the vftable whose name getter returns its class: 0x00C117F0
// (0x0033F745, "AIGuardRetaliateState"; the ledger's Rva00341E70) and
// 0x00C11850 (0x0033F76C, "AITunnelNetworkGuardState"; Rva00341F99).
//
// BFME 2 opens with the light-CRC gate and Version1. The machine member sits
// at +0x20, and the owner comes from the state's machine (+0x18) at +0x14. The
// sub-machines are allocated by plain operator new: AIGuardRetaliateMachine
// (0x4C bytes, ctor 0x0054551F) and AITNGuardMachine (0x50 bytes, ctor
// 0x00546001).

#include "Common/Snapshot.h"

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

class Object;

class AIGuardRetaliateMachine : public Snapshot
{
public:
	AIGuardRetaliateMachine( Object *owner );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
};

class AITNGuardMachine : public Snapshot
{
public:
	AITNGuardMachine( Object *owner );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x50 - 0x04 ];
};

class StateMachine
{
public:
	Object *getOwner( void ) const { return m_owner; }
private:
	char m_unrecovered00[ 0x14 ];
	Object *m_owner;																													///< 0x14
};

// The state base: only its virtual table and machine matter to these bodies.
class State
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	Object *getMachineOwner( void ) const { return m_machine->getOwner(); }
private:
	char m_unrecovered04[ 0x18 - 0x04 ];
	StateMachine *m_machine;																									///< 0x18
	char m_unrecovered1C[ 0x20 - 0x1C ];
};

// ------------------------------------------------------------------------------------------------
class AIGuardRetaliateState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AIGuardRetaliateMachine *m_guardRetaliateMachine;													///< 0x20
};

// ------------------------------------------------------------------------------------------------
class AITunnelNetworkGuardState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AITNGuardMachine *m_guardMachine;																					///< 0x20
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AIGuardRetaliateState::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	Bool hasMachine = m_guardRetaliateMachine!=0;

	*xfer == hasMachine;

	if (hasMachine && m_guardRetaliateMachine==0)
	{
		// create new state machine for guard behavior
		m_guardRetaliateMachine = new AIGuardRetaliateMachine( getMachineOwner() );
	}
	if (hasMachine)
	{
		*xfer == *m_guardRetaliateMachine;
	}

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AITunnelNetworkGuardState::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	Bool hasMachine = m_guardMachine!=0;

	*xfer == hasMachine;

	if (hasMachine && m_guardMachine==0)	{
		// create new state machine for guard behavior
		m_guardMachine = new AITNGuardMachine( getMachineOwner() );
	}
	if (hasMachine) {
		*xfer == *m_guardMachine;
	}

}  // end xfer
