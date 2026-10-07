// cl: /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/System/FunctionLexicon.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// FunctionLexicon::winLayoutInitFunc 0x002D23A1 (48B),
// FunctionLexicon::keyToFunc 0x002D2235 (42B).
// findFunction follows donor 968ca36c32 with the target table base +0x0C;
// Ghidra proves its 77-byte boundary, including the complete ret 8.
// The native 12-table traversal also appears independently in validate.
// Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: FunctionLexicon.cpp //////////////////////////////////////////////////////////////////////
// Created:    Colin Day, September 2001
// Desc:       Collection of function pointers to help us in managing
//						 and assign callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/FunctionLexicon.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/Gadget.h"

// Popup Ladder Select --------------------------------------------------------------------------
extern void PopupLadderSelectInit( WindowLayout *layout, void *userData );
extern WindowMsgHandledType PopupLadderSelectSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
extern WindowMsgHandledType PopupLadderSelectInput( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

extern WindowMsgHandledType PopupBuddyNotificationSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

// WOL Buddy Overlay Right Click menu callbacks --------------------------------------------------------------
extern void RCGameDetailsMenuInit( WindowLayout *layout, void *userData );
extern WindowMsgHandledType RCGameDetailsMenuSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

// Beacon control bar callback --------------------------------------------------------------
extern WindowMsgHandledType BeaconWindowInput( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

// Popup Replay Save Menu ----------------------------------------------------------------------------------
extern void PopupReplayInit( WindowLayout *layout, void *userData );
extern void PopupReplayUpdate( WindowLayout *layout, void *userData );
extern void PopupReplayShutdown( WindowLayout *layout, void *userData );
extern WindowMsgHandledType PopupReplaySystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
extern WindowMsgHandledType PopupReplayInput( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

// Extended MessageBox ----------------------------------------------------------------------------------
extern WindowMsgHandledType ExtendedMessageBoxSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

// BFME layout callback tables that live in the retail data image.
extern FunctionLexicon::TableEntry g_012A9308[];
extern FunctionLexicon::TableEntry g_012A9960[];
extern FunctionLexicon::TableEntry g_012A9B10[];
extern FunctionLexicon::TableEntry g_012A9C40[];
extern FunctionLexicon::TableEntry g_012A93D4[];


///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA 
///////////////////////////////////////////////////////////////////////////////////////////////////
extern FunctionLexicon *TheFunctionLexicon;  ///< the function dictionary

// This TU-local StringBase declaration uses the existing WWLib ABI symbols;
// the facade preserves retail's one-pointer temporary and inline data view.
template <typename T>
class StringBase
{
	friend class BFMEFunctionLexiconString;

private:
	StringBase( const T *text );
	~StringBase();

	const T *str() const
	{
		static const T nullCharacter = (T)0;
		return m_data ? (const T *)m_data + 8 : &nullCharacter;
	}

private:
	void *m_data;
};

class BFMEFunctionLexiconString : public StringBase<char>
{
public:
	BFMEFunctionLexiconString( const char *text )
		: StringBase<char>( text ) { }
	~BFMEFunctionLexiconString() { }

	operator const char *() const
	{
		return str();
	}
};
  // end loadTable

//-------------------------------------------------------------------------------------------------
/** Search the provided table for a function matching the key */
//-------------------------------------------------------------------------------------------------
void *FunctionLexicon::keyToFunc( NameKeyType key, TableEntry *table )
{

	// sanity
	if( key == NAMEKEY_INVALID )
		return NULL;

	// search table for key
	TableEntry *entry = table;
	while( entry && entry->key != NAMEKEY_INVALID )
	{

		if( entry->key == key )
			return entry->func;
		entry++;

	}  // end if

	return NULL;  // not found

}
  // end findFunction

#ifdef NOT_IN_USE
  // end funcToName
#endif


void *FunctionLexicon::findFunction( NameKeyType key, TableIndex index )
{
	void *func = NULL;

	// sanity
	if( key == NAMEKEY_INVALID )
		return NULL;

	// search ALL tables for function if the index paramater allows if
	if( index == TABLE_ANY )
	{

		Int i;
		for( i = 0; i < 12; i++ )
		{

			func = keyToFunc( key, m_tables[ i ] );
			if( func )
				break;  // exit for i

		}  // end for i

	}  // end if
	else
	{

		// do NOT search all tables, just the one specified by the parameter
		func = keyToFunc( key, m_tables[ index ] );

	}  // end else

	// return function, if found
	return func;

}  // end findFunction

WindowLayoutInitFunc FunctionLexicon::winLayoutInitFunc( NameKeyType key, TableIndex index )
{
	if ( index == TABLE_ANY )
	{
		// first search the device depended table then the device independent table
		WindowLayoutInitFunc func;

		// BFME places the device-init and init tables at slots 8 and 7.
		func = (WindowLayoutInitFunc)findFunction( key, (TableIndex)8 );
		if ( func == NULL )
		{
			func = (WindowLayoutInitFunc)findFunction( key, (TableIndex)7 );
		}
		return func;
	}
	// search the specified table
	return (WindowLayoutInitFunc)findFunction( key, index );
}
