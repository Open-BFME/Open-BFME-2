// cl: /Ireference/shims/bfme2_message_stream /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/MessageStream.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// MessageStream.cpp
// Implementation of the message stream
// Author: Michael S. Booth, February 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/MessageStream.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Recorder.h"

#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"

/// The singleton message stream for messages going to TheGameLogic
MessageStream *TheMessageStream = NULL;
CommandList *TheCommandList = NULL;



#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



//------------------------------------------------------------------------------------------------
// GameMessage
//

/**
 * Constructor
 */
// ??0GameMessage@@ present-unmatched
GameMessage::GameMessage( GameMessage::Type type ) 
{ 
	m_playerIndex = ThePlayerList->getLocalPlayer()->getPlayerIndex();
	m_type = type; 
	m_argList = NULL;
	m_argTail = NULL;
	m_argCount = 0; 
	m_list = 0; 
}


/**
 * Destructor
 */
// ??1GameMessage@@ present-unmatched
GameMessage::~GameMessage( ) 
{ 
	// free all arguments
	GameMessageArgument *arg, *nextArg;

	for( arg = m_argList; arg; arg=nextArg )
	{
		nextArg = arg->m_next;
		arg->deleteInstance();
	}

	// detach message from list
	if (m_list)
		m_list->removeMessage( this );
}

/**
 * Return the given argument data type
 */
#pragma optimize("s", on)
GameMessageArgumentDataType GameMessage::getArgumentDataType( Int argIndex )
{
	if (argIndex >= m_argCount) {
		return ARGUMENTDATATYPE_UNKNOWN;
	}
	int i=0;
	for (GameMessageArgument *a = m_argList; a && (i < argIndex); a=a->m_next, ++i );

	if (a != NULL)
	{
		return a->m_type;
	}
	return ARGUMENTDATATYPE_UNKNOWN;
}
#pragma optimize("", on)

/**
 * Append an integer argument
 */
void GameMessage::appendRealArgument( Real arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.real = arg;
	a->m_type = ARGUMENTDATATYPE_REAL;
}

void GameMessage::appendBooleanArgument( Bool arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.boolean = arg;
	a->m_type = ARGUMENTDATATYPE_BOOLEAN;
}

void GameMessage::appendObjectIDArgument( ObjectID arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.objectID = arg;
	a->m_type = ARGUMENTDATATYPE_OBJECTID;
}

void GameMessage::appendDrawableIDArgument( DrawableID arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.drawableID = arg;
	a->m_type = ARGUMENTDATATYPE_DRAWABLEID;
}

void GameMessage::appendTeamIDArgument( UnsignedInt arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.teamID = arg;
	a->m_type = ARGUMENTDATATYPE_TEAMID;
}

void GameMessage::appendPixelArgument( const ICoord2D& arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.pixel = arg;
	a->m_type = ARGUMENTDATATYPE_PIXEL;
}

void GameMessage::appendTimestampArgument( UnsignedInt arg )
{
	GameMessageArgument *a = allocArg();
	a->m_data.timestamp = arg;
	a->m_type = ARGUMENTDATATYPE_TIMESTAMP;
}

// ?getCommandAsAsciiString@GameMessage@@ present-unmatched
AsciiString GameMessage::getCommandAsAsciiString( void )
{
	return getCommandTypeAsAsciiString(m_type);
}

// getCommandTypeAsAsciiString is defined by the verified BFME2 worker in
// System/MessageStreamCommandName.cpp; do not emit the divergent ZH implementation.

//------------------------------------------------------------------------------------------------
// GameMessageList
//

/**
 * Append message to end of message list
 */
// appendMessage and insertMessage use the verified BFME2 definitions in
// MessageStreamListCtors.cpp, including retail null/head insertion handling.

/**
 * Remove given message from the list.
 */
// ?removeMessage@GameMessageList@@ present-unmatched
void GameMessageList::removeMessage( GameMessage *msg )
{
	if (msg->next())
		msg->next()->friend_setPrev(msg->prev());
	else
		m_lastMessage = msg->prev();

	if (msg->prev())
		msg->prev()->friend_setNext(msg->next());
	else
		m_firstMessage = msg->next();

	msg->friend_setList(NULL);
}

/**
 * Return whether or not a message of the given type is in the message list
 */
// ?containsMessageOfType@GameMessageList@@ present-unmatched
Bool GameMessageList::containsMessageOfType( GameMessage::Type type )
{
	GameMessage *msg = getFirstMessage();
	while (msg) {
		if (msg->getType() == type) {
			return true;
		}
		msg = msg->next();
	}
	return false;
}

//------------------------------------------------------------------------------------------------
// MessageStream
//


/**
	* Init
	*/
// ?init@MessageStream@@ present-unmatched
void MessageStream::init( void )
{
	// extend
	GameMessageList::init();
} 

/**
	* Reset
	*/
// ?reset@MessageStream@@ present-unmatched
void MessageStream::reset( void )
{

	/// @todo Reset the MessageStream

	// extend
	GameMessageList::reset();

}

/**
	* Update
	*/
// ?update@MessageStream@@ present-unmatched
void MessageStream::update( void )
{
	// extend
	GameMessageList::update();

}

/**
 * Create a new message of the given message type and append it
 * to this message stream.  Return the message such that any data
 * associated with this message can be attached to it.
 */
#pragma optimize("t", off)
#pragma optimize("s", on)
GameMessage *MessageStream::appendMessage( GameMessage::Type type )
{
	GameMessage *msg = ::new GameMessage( type );

	// add message to list
	GameMessageList::appendMessage( msg );

	return msg;
}
#pragma optimize("", on)

/**
 * Create a new message of the given message type and insert it
 * in the stream after messageToInsertAfter, which must not be NULL.
 */
#pragma optimize("t", off)
#pragma optimize("s", on)
GameMessage *MessageStream::insertMessage( GameMessage::Type type, GameMessage *messageToInsertAfter )
{
	GameMessage *msg = ::new GameMessage(type);

	GameMessageList::insertMessage(msg, messageToInsertAfter);

	return msg;
}
#pragma optimize("", on)

/**
 * Attach the given Translator to the message stream, and return a
 * unique TranslatorID identifying it.
 * Translators are placed on a list, sorted by priority order.  If two
 * Translators share a priority, they are kept in the same order they
 * were attached.
 */
// ?attachTranslator@MessageStream@@ present-unmatched
TranslatorID MessageStream::attachTranslator( GameMessageTranslator *translator, 
																							UnsignedInt priority)
{
	MessageStream::TranslatorData *newSS = NEW MessageStream::TranslatorData;
	MessageStream::TranslatorData *ss;

	newSS->m_translator = translator;
	newSS->m_priority = priority;
	newSS->m_id = m_nextTranslatorID++;

	if (m_firstTranslator == NULL)
	{
		// first Translator to be attached
		newSS->m_prev = NULL;
		newSS->m_next = NULL;
		m_firstTranslator = newSS;
		m_lastTranslator = newSS;
		return newSS->m_id;
	}

	// seach the Translator list for our priority location
	for( ss=m_firstTranslator; ss; ss=ss->m_next )
		if (ss->m_priority > newSS->m_priority)
			break;

	if (ss)
	{
		// insert new Translator just BEFORE this one,
		// therefore, m_lastTranslator cannot be affected
		if (ss->m_prev)
		{
			ss->m_prev->m_next = newSS;
			newSS->m_prev = ss->m_prev;
			newSS->m_next = ss;
			ss->m_prev = newSS;
		}
		else
		{
			// insert at head of list
			newSS->m_prev = NULL;
			newSS->m_next = m_firstTranslator;
			m_firstTranslator->m_prev = newSS;
			m_firstTranslator = newSS;
		}
	}
	else
	{
		// append Translator to end of list
		m_lastTranslator->m_next = newSS;
		newSS->m_prev = m_lastTranslator;
		newSS->m_next = NULL;
		m_lastTranslator = newSS;
	}

	return newSS->m_id;
}

/**
 * Remove a previously attached translator.
 */
// ?removeTranslator@MessageStream@@ present-unmatched
void MessageStream::removeTranslator( TranslatorID id )
{
	MessageStream::TranslatorData *ss;

	for( ss=m_firstTranslator; ss; ss=ss->m_next )
		if (ss->m_id == id)
		{
			// found the translator - remove it
			if (ss->m_prev)
				ss->m_prev->m_next = ss->m_next;
			else
				m_firstTranslator = ss->m_next;

			if (ss->m_next)
				ss->m_next->m_prev = ss->m_prev;
			else
				m_lastTranslator = ss->m_prev;

			// delete the translator data
			delete ss;

			break;
		}
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#if defined(_DEBUG) || defined(_INTERNAL)

Bool isInvalidDebugCommand( GameMessage::Type t )
{
	// see if this is something that should be prevented in multiplayer games
	// Don't reject this stuff in skirmish games.
	if (TheGameLogic && !TheGameLogic->isInSkirmishGame() && 
			(TheRecorder && TheRecorder->isMultiplayer() && TheRecorder->getMode() == RECORDERMODETYPE_RECORD))
	{
		switch (t)
		{
		case GameMessage::MSG_META_DEMO_SWITCH_TEAMS:
		case GameMessage::MSG_META_DEMO_SWITCH_TEAMS_BETWEEN_CHINA_USA:
		case GameMessage::MSG_META_DEMO_KILL_ALL_ENEMIES:
		case GameMessage::MSG_META_DEMO_KILL_SELECTION:
		case GameMessage::MSG_META_DEMO_TOGGLE_HURT_ME_MODE:
		case GameMessage::MSG_META_DEMO_TOGGLE_HAND_OF_GOD_MODE:
		case GameMessage::MSG_META_DEMO_TOGGLE_SPECIAL_POWER_DELAYS:
		case GameMessage::MSG_META_DEMO_TIME_OF_DAY:
		case GameMessage::MSG_META_DEMO_LOCK_CAMERA_TO_PLANES:
		case GameMessage::MSG_META_DEMO_REMOVE_PREREQ:
		case GameMessage::MSG_META_DEMO_INSTANT_BUILD:
		case GameMessage::MSG_META_DEMO_FREE_BUILD:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT1:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT2:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT3:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT4:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT5:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT6:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT7:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT8:
		case GameMessage::MSG_META_DEMO_RUNSCRIPT9:
		case GameMessage::MSG_META_DEMO_ENSHROUD:
		case GameMessage::MSG_META_DEMO_DESHROUD:
		case GameMessage::MSG_META_DEBUG_GIVE_VETERANCY:
		case GameMessage::MSG_META_DEBUG_TAKE_VETERANCY:
//#pragma MESSAGE ("WARNING - DEBUG key in multiplayer!")
		case GameMessage::MSG_META_DEMO_ADD_CASH:
		case GameMessage::MSG_META_DEBUG_INCR_ANIM_SKATE_SPEED:
		case GameMessage::MSG_META_DEBUG_DECR_ANIM_SKATE_SPEED:
		case GameMessage::MSG_META_DEBUG_CYCLE_EXTENT_TYPE:
		case GameMessage::MSG_META_DEMO_TOGGLE_RENDER:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_MAJOR:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_MAJOR_BIG:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_MAJOR:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_MAJOR_BIG:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_MINOR:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_MINOR_BIG:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_MINOR:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_MINOR_BIG:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_HEIGHT:
		case GameMessage::MSG_META_DEBUG_INCREASE_EXTENT_HEIGHT_BIG:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_HEIGHT:
		case GameMessage::MSG_META_DEBUG_DECREASE_EXTENT_HEIGHT_BIG:
		case GameMessage::MSG_META_DEMO_KILL_AREA_SELECTION:
		case GameMessage::MSG_DEBUG_KILL_SELECTION:
		case GameMessage::MSG_DEBUG_HURT_OBJECT:
		case GameMessage::MSG_DEBUG_KILL_OBJECT:
		case GameMessage::MSG_META_DEMO_GIVE_SCIENCEPURCHASEPOINTS:
		case GameMessage::MSG_META_DEMO_GIVE_ALL_SCIENCES:
		case GameMessage::MSG_META_DEMO_GIVE_RANKLEVEL:
		case GameMessage::MSG_META_DEMO_TAKE_RANKLEVEL:
		case GameMessage::MSG_META_DEBUG_WIN:

			return true;
		}
	}
	return false;
}
#endif

//------------------------------------------------------------------------------------------------
// CommandList
//

/**
	* Init
	*/
// ?init@CommandList@@ present-unmatched
void CommandList::init( void )
{

	// extend
	GameMessageList::init();

} 

/**
	* Destroy all messages on the list, and reset list to empty
	*/
// ?reset@CommandList@@ present-unmatched
void CommandList::reset( void )
{

	// extend
	GameMessageList::reset();

	// destroy all messages
	destroyAllMessages();

}

/**
	* Update
	*/
// ?update@CommandList@@ present-unmatched
void CommandList::update( void )
{

	// extend
	GameMessageList::update();

}

/**
	* Destroy all messages on the command list, this will get called from the
	* destructor and reset methods, DO NOT throw exceptions
	*/
void CommandList::destroyAllMessages( void )
{
	GameMessage *msg, *next;

	for( msg=m_firstMessage; msg; msg=next )
	{
		next = msg->next();
		msg->deleteInstance();
	}
	
	m_firstMessage = NULL;
	m_lastMessage = NULL;

}

//-----------------------------------------------------------------------------
/**
 * Given an "anchor" point and the current mouse position (dest),
 * construct a valid 2D bounding region.
 */
#pragma optimize("s", on)
void buildRegion( const ICoord2D *anchor, const ICoord2D *dest, IRegion2D *region )
{
	// build rectangular region defined by the drag selection
	if (anchor->x < dest->x)
	{
		region->lo.x = anchor->x;
		region->hi.x = dest->x;
	}
	else
	{
		region->lo.x = dest->x;
		region->hi.x = anchor->x;
	}

	if (anchor->y < dest->y)
	{
		region->lo.y = anchor->y;
		region->hi.y = dest->y;
	}
	else
	{
		region->lo.y = dest->y;
		region->hi.y = anchor->y;
	}
}
#pragma optimize("", on)
