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

class Rva0039F761Owner
{
public:
	Team *findInstance( void *prototypeKey );
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class Script;

class ScriptEngine
{
public:
	Script *rva003573C4( const AsciiString &scope, const AsciiString &name, Int flag );
};
extern ScriptEngine *TheScriptEngine;

class SequentialScript
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
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
		m_teamToExecOn = ((Rva0039F761Owner *)TheTeamFactory)->findInstance( (void *)teamID );

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
		m_scriptToExecuteSequentially = TheScriptEngine->rva003573C4( m_bfmeScriptScope, m_bfmeScriptName, 0 );

	// current instruction
	*xfer == m_currentInstruction;

	// times to loop
	*xfer == m_timesToLoop;

	// frames to wait
	*xfer == m_framesToWait;

	// dont advance instruction
	*xfer == m_dontAdvanceInstruction;

}  // end xfer
