// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/System/SaveGame/GameState.cpp); this unit had no counterpart under Code/.
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

// FILE: GameState.cpp ////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2002
// Desc:   Game state singleton from which to load and save the game state
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"
#include <list>

// The native Snapshot-pointer list bodies are owned by GameStatePostProcess.
// Keep this unmatched ZH donor from supplying competing COMDAT definitions.
class Snapshot;
namespace _STL {
template<> void _List_base<Snapshot *, allocator<Snapshot *> >::clear();
template<> _List_base<Snapshot *, allocator<Snapshot *> >::~_List_base();
template<> void list<Snapshot *>::push_front(Snapshot *const &);
template<> void list<Snapshot *>::push_back(Snapshot *const &);
template<> list<Snapshot *>::iterator list<Snapshot *>::insert(iterator, Snapshot *const &);
template<> void allocator<_List_node<Snapshot *> >::deallocate(_List_node<Snapshot *> *, size_t) const;
template<> void _STLP_alloc_proxy<_List_node<Snapshot *> *, _List_node<Snapshot *>, allocator<_List_node<Snapshot *> > >::deallocate(_List_node<Snapshot *> *, size_t);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "Common/GameStateMap.h"
#include "Common/LatchRestore.h"
#include "Common/MapObject.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/WellKnownKeys.h"
#include "Common/XferLoad.h"
#include "Common/XferSave.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "GameClient/MessageBox.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/TerrainVisual.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/GhostObject.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/TerrainLogic.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
GameState *TheGameState = NULL;

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
#define GAME_STATE_BLOCK_STRING "CHUNK_GameState"  // block of save game data with game info data
#define CAMPAIGN_BLOCK_STRING "CHUNK_Campaign"		 // block of game data that has campaign info

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0SaveGameInfo@@ present-unmatched
SaveGameInfo::SaveGameInfo( void )
{

	date.day					= 0;
	date.dayOfWeek		= 0;
	date.hour					= 0;
	date.milliseconds = 0;
	date.minute				= 0;
	date.month				= 0;
	date.second				= 0;
	date.year					= 0;
	missionNumber			= 0;
	saveFileType			= SAVE_FILE_TYPE_NORMAL;

}  // end SaveGameInfo

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Is this date newer than the other one passed in? */
// ------------------------------------------------------------------------------------------------
Bool SaveDate::isNewerThan( SaveDate *other )
{

	// year
	if( year > other->year )
		return TRUE;
	else if( year < other->year )
		return FALSE;
	else
	{

		// month
		if( month > other->month )
			return TRUE;
		else if( month < other->month )
			return FALSE;
		else
		{
			
			// day
			if( day > other->day )
				return TRUE;
			else if( day < other->day )
				return FALSE;
			else
			{

				// hour
				if( hour > other->hour )
					return TRUE;
				else if( hour < other->hour )
					return FALSE;
				else
				{

					// minute
					if( minute > other->minute )
						return TRUE;
					else if( minute < other->minute )
						return FALSE;
					else
					{

						// second
						if( second > other->second )
							return TRUE;
						else if( second < other->second )
							return FALSE;
						else
						{

							// millisecond
							if( milliseconds > other->milliseconds )
								return TRUE;
							else
								return FALSE;

						}  // end else

					}  // end else

				}  // end else

			}  // end else

		}  // end else

	}  // end else

}  // end isNewerThan

// ------------------------------------------------------------------------------------------------
/** Find a snapshot block info that matches the token passed in */
// ------------------------------------------------------------------------------------------------
// Token lookup is provided by verified GameStateAddSnapshotBlock.cpp.

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Constructor is provided by verified GameStateConstructor.cpp.


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Destructor is provided by verified GameStateDtor.cpp.

// ------------------------------------------------------------------------------------------------
/** Init the game state subsystem */
// ------------------------------------------------------------------------------------------------
// init is provided by the verified GameStateInit.cpp unit.


// ------------------------------------------------------------------------------------------------
/** Reset */
// ------------------------------------------------------------------------------------------------a
// GameState::reset is retail 0x002DEE9A (rowed in Rva002DEE9AClear.cpp): BFME2
// clears two lists, runs 0x002DE311 and zeroes +0xE18. The Zero Hour body that
// stood here is not retail's and would be the copy the link keeps.

// ------------------------------------------------------------------------------------------------
/** Clear any available games entries */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Add a snapshot and block name pair to the systems used to load and save */
// ------------------------------------------------------------------------------------------------
// addSnapshotBlock is provided by the verified GameStateAddSnapshotBlock.cpp unit.


// ------------------------------------------------------------------------------------------------
/** Given the filename of a save file, find the highest filename number */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Given the save files on disk, find the "next" filename to use when saving a game */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Save the current state of the engine in a save file
	* NOTE: filename is a *filename only* */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** A mission save */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Load the save game pointed to by filename */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// GameState::realMapPathToPortableMapPath is defined with its retail-matched body in Code/GameEngine/Source/Common/System/SaveGame/GameStateRealMapPathToPortable.cpp (0x002DC833).

// GameState::portableMapPathToRealMapPath is defined with its retail-matched
// body in Code/GameEngine/Source/Common/System/SaveGame/GameStatePortableMapPathToReal.cpp
// (0x002DC9F7, 421B). The donor-derived duplicate that stood here missed
// retail's bytes (notably the 4th LivingWorldScripts branch) and lost the
// link to the rowed copy, so it is deleted rather than kept.

// ------------------------------------------------------------------------------------------------
/** Does the save game file exist */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Get save game info from the filename specified */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Create game info and add to available list */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Populate the listbox passed in with a list of the save games present on the hard drive */
// ------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** Iterate the save game files */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Save game to xfer or load game using xfer */
// ------------------------------------------------------------------------------------------------
// GameState::friend_xferSaveDataForCRC is defined with its retail-matched body in Code/GameEngine/Source/Common/System/SaveGame/GameStateFriend.cpp (0x002DDD0B).

// ------------------------------------------------------------------------------------------------
/** Save game to xfer or load game using xfer */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Add a snapshot to the post process list for later */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Post process entry point after all game data has been xferd from disk */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer method for the game state itself 
	* Version Info:
	* 1: Initial version 
	* 2: Added save file type and mission map name (regular save vs automatic mission save) */
// ------------------------------------------------------------------------------------------------
// GameState::xfer is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva002DBCCAForward.cpp (0x002DBCCA).

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
