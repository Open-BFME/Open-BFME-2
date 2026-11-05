// cl: /Ireference/shims/zh_overridable_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// platformsdk
// dxsdk
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GameClient.cpp); this unit had no counterpart under Code/.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

// FILE: GameClient.cpp ////////////////////////////////////////////////////
// Implementation of GameClient singleton
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "GameClient/GameClient.h"

// Existing matched accessor at 0x0055A88B reads the drawable ID at +0x100.
class Rva0055A88BDwordField
{
public:
	int get() const;
};

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/ActionManager.h"
#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "Common/GameLOD.h"
#include "GameClient/Anim2D.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Diplomacy.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/DrawGroupInfo.h"
#include "GameClient/Eva.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/GraphDraw.h"
#include "GameClient/GUICommandTranslator.h"
#include "GameClient/HeaderTemplate.h"
#include "GameClient/HintSpy.h"
#include "GameClient/HotKey.h"
#include "GameClient/IMEManager.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Keyboard.h"
#include "GameClient/LanguageFilter.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/Mouse.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/PlaceEventTranslator.h"
#include "GameClient/RayEffect.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/Shell.h"
#include "GameClient/Snow.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/View.h"
#include "GameClient/VideoPlayer.h"
#include "GameClient/WindowXlat.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/GhostObject.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"		// For TheScriptEngine - jkmcd
// bfme link decl-only begin
namespace _STL { template <> _List_node<Drawable *> * list<Drawable *, allocator<Drawable *> >::_M_create_node(Drawable *const &); }
namespace _STL { template <> void list<Drawable *, allocator<Drawable *> >::push_back(Drawable *const &); }
namespace _STL { template <> list<Drawable *, allocator<Drawable *> >::iterator list<Drawable *, allocator<Drawable *> >::insert(list<Drawable *, allocator<Drawable *> >::iterator, Drawable *const &); }
// bfme link decl-only end

// ?erase@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEPAVAsciiString@@PAV3@0@Z
// is owned by VectorAsciiStringErase.cpp (row at 0x0002CCFC): declare the
// explicit specialization so this TU calls it without emitting a second definition.
namespace _STL
{
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *);
}
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define DRAWABLE_HASH_SIZE	8192

/// The GameClient singleton instance
GameClient *TheGameClient = NULL;

// placement unverified: no rowed DIR32 site yet; ZH ActionManager singleton starts null.
ActionManager *TheActionManager = 0;
// placement unverified: no rowed DIR32 site yet; ZH TerrainVisual singleton starts null.
TerrainVisual *TheTerrainVisual = 0;

// Matched DIR32 sites establish TheWritableGlobalData at VA 0x00DFE758.
// That address is in the PE .data zero-fill tail, so retail starts it null.
GlobalData *TheWritableGlobalData = NULL;

class HotKeyManager;
// Owned here: created in init() below, deleted in shutdown(); retail .data
// starts it at 0 (VA 0x00A01E28).
HotKeyManager *TheHotKeyManager = 0;

class SnowManager;
// Owned here: created in init() below, deleted in shutdown(); retail .data
// starts it at 0 (VA 0x009FE114).
SnowManager *TheSnowManager = 0;

//-------------------------------------------------------------------------------------------------
// ?GameClient::GameClient present-unmatched
//std::vector<std::string>	preloadTextureNamesGlobalHack;
//std::vector<std::string>	preloadTextureNamesGlobalHack2;

//-------------------------------------------------------------------------------------------------
// ?GameClient::~GameClient present-unmatched
//-------------------------------------------------------------------------------------------------
/** Initialize resources for the game client */
//-------------------------------------------------------------------------------------------------
// ?GameClient::init present-unmatched
//-------------------------------------------------------------------------------------------------
/** Reset the game client for a new game */
// ?GameClient::reset present-unmatched
/** -----------------------------------------------------------------------------------------------
 * Return a new unique object id.
 */
DrawableID GameClient::allocDrawableID( void )
{
	/// @todo Find unused value in current set
	DrawableID ret = m_nextDrawableID;
	m_nextDrawableID = (DrawableID)((UnsignedInt)m_nextDrawableID + 1);
	return ret;
}

/** -----------------------------------------------------------------------------------------------
 * Given a drawable, register it with the GameClient and give it a unique ID.
 */

/** -----------------------------------------------------------------------------------------------
 * Redraw all views, update the GUI, play sound effects, etc.
 */
DECLARE_PERF_TIMER(GameClient_update)
DECLARE_PERF_TIMER(GameClient_draw)

/** -----------------------------------------------------------------------------------------------
 * Destroy the drawable immediately.
 */
// GameClient::destroyDrawable is defined with its retail-matched body in Code/GameEngine/Source/GameClient/GameClientDestroyDrawable.cpp (0x00239F40).

// ------------------------------------------------------------------------------------------------
/** Add drawable to lookup table for fast id searching */
// ------------------------------------------------------------------------------------------------
// ?GameClient::addDrawableToLookupTable present-unmatched
void GameClient::addDrawableToLookupTable(Drawable *draw )
{

	// sanity
	if( draw == NULL )
		return;

	// add to lookup
//	m_drawableHash[ draw->getID() ] = draw;
	DrawableID newID = (DrawableID)((const Rva0055A88BDwordField *)draw)->get();
	while( newID >= m_drawableVector.size() ) // Fail case is hella rare, so faster to double up on size() call
		m_drawableVector.resize(m_drawableVector.size() * 2, NULL);

	m_drawableVector[ newID ] = draw;

}  // end addDrawableToLookupTable

// ------------------------------------------------------------------------------------------------
/** Remove drawable from lookup table of fast id searching */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Load a map into the game interface */
// GameClient::loadMap is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva0042F0D0.cpp (0x00239949).

//-------------------------------------------------------------------------------------------------
/** Unload a map from the game interface */

//-------------------------------------------------------------------------------------------------
// ?GameClient::selectDrawablesInGroup present-unmatched
void GameClient::selectDrawablesInGroup( Int group )
{
/*
	Drawable *draw = firstDrawable();

	// create a message that will assign a group ID to all the selected drawables, this
	// way when we do things with this current selected group of units, we only have
	// to refer to the group ID and not each individual object ID
	GameMessage *teamMsg = TheMessageStream->appendMessage( GameMessage::MSG_CREATE_SELECTED_GROUP );

	//We are creating a new group from scratch.
	teamMsg->appendBooleanArgument( true );

	while( draw )
	{
		int counter = 0;
	
		const Object *object = draw->getObject();

		if( object && draw->getDrawableGroup() == group && object->isLocallyControlled() && !object->isContained() )
		{
			//Only select the object if it is locally controlled and not contained by anything.
			TheInGameUI->selectDrawable(draw);
			teamMsg->appendObjectIDArgument( draw->getObject()->getID() );
		}
		else
		{
			TheInGameUI->deselectDrawable(draw);
		}

		draw = draw->getNextDrawable();
		counter++;
	}

*/
}

// ------------------------------------------------------------------------------------------------
// ?GameClient::addTextBearingDrawable present-unmatched
void GameClient::addTextBearingDrawable( Drawable *tbd )
{
	if ( tbd != NULL )
		m_textBearingDrawableList.push_back( tbd );
}
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** remove the drawble from the ray effects sytem if present */

/** frees all shadow resources used by this module - used by Options screen.*/

// ------------------------------------------------------------------------------------------------
/** Given a string name, find the drawable TOC entry (if any) associated with it */
// ------------------------------------------------------------------------------------------------
// ?GameClient::findTOCEntryByName present-unmatched
GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName( AsciiString name )
{

	for( DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it )
		if( (*it).name == name )
			return &(*it);

	return NULL;

}  // end findTOCEntryByname

// ------------------------------------------------------------------------------------------------
/** Given a drawable TOC identifier, find the drawable TOC if any */
// ------------------------------------------------------------------------------------------------
// ?GameClient::findTOCEntryById present-unmatched
GameClient::DrawableTOCEntry *GameClient::findTOCEntryById( UnsignedShort id )
{

	for( DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it )
		if( (*it).id == id )
			return &(*it);

	return NULL;

}  // end findTOCEntryById

// ------------------------------------------------------------------------------------------------
/** Add an drawable TOC entry */
// ------------------------------------------------------------------------------------------------
// ?GameClient::addTOCEntry present-unmatched
void GameClient::addTOCEntry( AsciiString name, UnsignedShort id )
{

	DrawableTOCEntry tocEntry;
	tocEntry.name = name;
	tocEntry.id = id;
	m_drawableTOC.push_back( tocEntry );

}  // end addTOCEntry

// ------------------------------------------------------------------------------------------------
static Bool shouldSaveDrawable(const Drawable* draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == NULL)
		{
			return false;
		}
		else
		{
			DEBUG_CRASH(("You should not ever set DRAWABLE_STATUS_NO_SAVE for a Drawable with an object. (%s)\n",draw->getTemplate()->getName().str()));
		}
	}
	return true;
}

// ------------------------------------------------------------------------------------------------
/** Xfer drawable table of contents */
// ------------------------------------------------------------------------------------------------
// ?GameClient::xferDrawableTOC present-unmatched
void GameClient::xferDrawableTOC( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// clear our current table of contents
	m_drawableTOC.clear();

	// xfer the table
	UnsignedInt tocCount = 0;
	if( xfer->getXferMode() == XFER_SAVE )
	{
		AsciiString templateName;

		// generate a new TOC based on the drawables that are in the map
		for( Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable() )
		{
			if (!shouldSaveDrawable(draw))
				continue;

			// get the name we're working with
			templateName = draw->getTemplate()->getName();

			// if is this drawable name already in the TOC, skip it
			if( findTOCEntryByName( templateName ) != NULL )
				continue;
			
			// add this entry to the TOC
			addTOCEntry( draw->getTemplate()->getName(), ++tocCount );

		}  // end for obj

		// xfer entries in the TOC
		xfer->xferUnsignedInt( &tocCount );

		// xfer each TOC entry
		DrawableTOCListIterator it;
		DrawableTOCEntry *tocEntry;
		for( it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it )
		{

			// get this toc entry
			tocEntry = &(*it);

			// xfer the name
			xfer->xferAsciiString( &tocEntry->name );

			// xfer the paired id
			xfer->xferUnsignedShort( &tocEntry->id );

		}  // end for

	}  // end if
	else
	{
		AsciiString templateName;
		UnsignedShort id;

		// how many entries are we going to read
		xfer->xferUnsignedInt( &tocCount );

		// read all the entries
		for( UnsignedInt i = 0; i < tocCount; ++i )
		{

			// read the name
			xfer->xferAsciiString( &templateName );

			// read the id
			xfer->xferUnsignedShort( &id );
			
			// add this to the TOC
			addTOCEntry( templateName, id );
					
		}  // end for i

	}  // end else

}  // end xferDrawableTOC

// ------------------------------------------------------------------------------------------------
/** Xfer method for Game Client
  * Version History:
  * 1: Initial
  * 2: Adding mission briefing history
	* 3: Added block markers around drawable data, no version checking is done and therefore
	*		 this version breaks compatibility with previous versions. (CBD)
 */
// ------------------------------------------------------------------------------------------------
// GameClient::xfer is rowed in its home unit; this copy was a duplicate definition.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?GameClient::loadPostProcess present-unmatched
void GameClient::loadPostProcess( void )
{

	//
	// due to the fact that during the load process we have called newDrawable for drawables
	// without objects, and then overwrote their ids with data from the save file, our allocater
	// id may be far higher than it needs to be.  We'll pull it back down as low as we can
	//
	Drawable *draw;
	for( draw = getDrawableList(); draw; draw = draw->getNextDrawable() )
		if( (DrawableID)((const Rva0055A88BDwordField *)draw)->get() >= m_nextDrawableID )
			m_nextDrawableID = (DrawableID)((UnsignedInt)((const Rva0055A88BDwordField *)draw)->get() + 1);

}  // end loadPostProcess

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?GameClient::crc present-unmatched
void GameClient::crc( Xfer *xfer )
{

}  // end crc
