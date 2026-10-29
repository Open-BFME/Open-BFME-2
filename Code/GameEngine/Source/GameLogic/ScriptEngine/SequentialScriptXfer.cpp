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


// SequentialScript::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/ScriptEngine/ScriptEngine.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "SequentialScript".
//
// BFME 2 skips the body under IsCRC (Xfer +0x0C), then runs Version1 and ZH's
// team round trip (Team id at +0x34; team factory lookup 0x0039F761;
// XferException tag 5 on a miss). BFME 2 keeps the script's two names as
// members (+0x0C, +0x10) and xfers them directly. On load it resolves the
// script through the ScriptEngine lookup 0x003573C4 (two names and a zero
// flag) in place of ZH's findScriptByName. ZH's instruction, loop, wait and
// advance fields follow.

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

#include "../../../Include/Common/BfmeXfer.h"

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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Team
{
public:
	UnsignedInt getID( void ) const { return m_id; }
private:
	char m_unrecovered00[ 0x34 ];
	UnsignedInt m_id;																													///< 0x34
};

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class Script;

class BfmeRoomZC;
class Rva003573C4Owner
{
public:
	void *rva003573C4( const AsciiString &scope, const BfmeRoomZC &name, void *arg );	// rowed 0x003573C4
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class SequentialScript
{
public:
	virtual ~SequentialScript();
protected:
	virtual void loadPostProcess();
public:
	virtual const char *GetSnapshotName();
protected:
	virtual void xfer(Xfer *xfer);
private:
	Team *m_teamToExecOn;																											///< 0x04
	ObjectID m_objectID;																											///< 0x08
	AsciiString m_bfmeScriptScope;																						///< 0x0C
	AsciiString m_bfmeScriptName;																							///< 0x10
	Script *m_scriptToExecuteSequentially;																		///< 0x14
	Int m_currentInstruction;																									///< 0x18
	Int m_timesToLoop;																												///< 0x1C
	Int m_framesToWait;																												///< 0x20
	Bool m_dontAdvanceInstruction;																						///< 0x24
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void SequentialScript::xfer( Xfer *xfer )
{
	if( xfer->IsCRC() )
		return;

	// version
	xfer->Version1();

	// team
	UnsignedInt teamID = m_teamToExecOn ? m_teamToExecOn->getID() : 0;
	*xfer == teamID;
	if( xfer->IsLoading() )
	{

		// tie up pointer
		m_teamToExecOn = TheTeamFactory->findTeamByID( teamID );

		// sanity
		if( teamID != 0 && m_teamToExecOn == 0 )
			throw XferException( 5, 0 );

	}  // end if

	// object id
	XferObjectID( xfer, &m_objectID );

	// script names
	*xfer == m_bfmeScriptScope;
	*xfer == m_bfmeScriptName;
	if( !xfer->IsStoring() )
		m_scriptToExecuteSequentially = (Script *)((Rva003573C4Owner *)TheScriptEngine)->rva003573C4( m_bfmeScriptScope, reinterpret_cast<const BfmeRoomZC &>(m_bfmeScriptName), 0 );

	// current instruction
	*xfer == m_currentInstruction;

	// times to loop
	*xfer == m_timesToLoop;

	// frames to wait
	*xfer == m_framesToWait;

	// dont advance instruction
	*xfer == m_dontAdvanceInstruction;

}  // end xfer

// ?SequentialScript::loadPostProcess present-unmatched
void SequentialScript::loadPostProcess()
{
}
