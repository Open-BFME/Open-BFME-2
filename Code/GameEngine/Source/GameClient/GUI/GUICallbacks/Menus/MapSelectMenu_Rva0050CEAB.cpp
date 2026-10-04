// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode -Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: MapSelectMenu.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, October 2001
// Description: MapSelect menu window callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/RandomValue.h"
#include "Common/UserPreferences.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptEngine.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
static NameKeyType radioButtonSystemMapsID = NAMEKEY_INVALID;
static NameKeyType radioButtonUserMapsID = NAMEKEY_INVALID;
static GameWindow *mapList = NULL;

static Bool showSoloMaps = true;
static Bool isShuttingDown = false;
static Bool startGame = false;
static Bool buttonPushed = false;
static GameDifficulty s_AIDiff = DIFFICULTY_NORMAL;


class BFMERetailScriptEngineView
{
public:
	unsigned char m_unreconstructed_00000[0x17620];
	GameDifficulty m_globalDifficulty;

	GameDifficulty getGlobalDifficulty() const { return m_globalDifficulty; }
};

// Zero Hour's setupGameStart(AsciiString) is not reconstructed here: retail's
// copy is the out-of-line body at 0x004D1080 (ledger name bfmeCommitYH) that
// MapSelectMenuSystem's OK branch calls; see the declaration above that body.


//-------------------------------------------------------------------------------------------------
// Open-BFME5: BFME made WindowLayout::hide VIRTUAL, at vtable slot 0x10. The
// Zero Hour WindowLayout.h in this tree declares it an ordinary member, so we
// emit a direct call to the right function instead of a dispatch. Correcting
// the declaration would touch every TU that includes WindowLayout.h and force
// the full repo gate, so it is spelled TU-locally: a shim whose fifth virtual
// lands on that slot, and a cast at each call site. Slots 0-3 stay anonymous
// because nothing here needs them. Same shim as NetworkDirectConnect.cpp.
//-------------------------------------------------------------------------------------------------
class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

//-------------------------------------------------------------------------------------------------
/** This is called when a shutdown is complete for this menu */
//-------------------------------------------------------------------------------------------------
// Retail 0x004D1000 (22 B): this menu static over isShuttingDown
// (VA 0x012F3E6C); layout arrives in EAX beside MapSelectMenuUpdate and
// MapSelectMenuShutdown (mov ecx,[TheShell] / push 0 / push eax / clear
// flag / call Shell::shutdownComplete via ILT 0x2F1D). Update/Shutdown
// inline the same sequence; no direct callers, refs=2 abs-ref.
// ?shutdownCompleteMapSelectMenu@@YAXPAVWindowLayout@@@Z

// Retail 0x004D1120 (ILT 0x00019727), called from MapSelectMenuInit. Zero Hour
// names this helper SetDifficultyRadioButton in both MapSelectMenu.cpp and
// DifficultySelect.cpp (static there); the ledger gives that mangled name to
// DifficultySelect's copy at 0x004C6E70, so this copy carries the menu suffix,
// as shutdownCompleteMapSelectMenu does.
// ?SetDifficultyRadioButtonMapSelectMenu@@YAXXZ

// BFME's populateMapListbox call site: see the note above MapSelectMenuSystem.
void __cdecl bfmePopulateMapListFlags( void *listbox, char useSystemMaps, char isMultiplayer, void *mapToSelect );

// BFME clears GameWindow+0x1F4 on the menu parent right after focusing it (the
// same store as ReplayMenuInit, SaveLoadMenuInit and WOLStatusMenu). Only the
// offset is recoverable, so the field keeps its address.
class BfmeMenuParentView
{
public:
	char m_pad[ 0x1F4 ];
	void *m_fieldAt1F4;
};

// BFME calls this helper out of line at retail 0x0050CE92 rather than inlining
// the donor's static copy; that address is its own matched row.
void shutdownCompleteMapSelectMenu( WindowLayout *layout );

//-------------------------------------------------------------------------------------------------
/** MapSelect menu shutdown method */
//-------------------------------------------------------------------------------------------------
void MapSelectMenuShutdown( WindowLayout *layout, void *userData )
{
	if (!startGame)
		isShuttingDown = true;

	// if we are shutting down for an immediate pop, skip the animations
	Bool popImmediate = *(Bool *)userData;
	if( popImmediate )
	{

		shutdownCompleteMapSelectMenu( layout );
		return;

	}  //end if

	if (!startGame)
		TheShell->reverseAnimatewindow();

}  // end MapSelectMenuShutdown

//-------------------------------------------------------------------------------------------------
/** MapSelect menu update method */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Map select menu input callback */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** MapSelect menu window system callback */
//-------------------------------------------------------------------------------------------------
// Retail 0x004D1C40, named by the FunctionLexicon row at 0x00EA94DC
// (MapSelectMenuSystem) whose ILT 0x0002EB81 jumps here.
//
// BFME's populateMapListbox call site is the cdecl four-argument helper at
// 0x00457090 (reached through ILT 0x00029CEE); its last argument is the
// address of AsciiString::TheEmptyString, i.e. taken by reference.
void __cdecl bfmePopulateMapListFlags( void *listbox, char useSystemMaps, char isMultiplayer, void *mapToSelect );

// Retail 0x004D1080 (Zero Hour's setupGameStart shape plus a BFME refresh)
// takes the chosen map name by value. Retail builds that argument in place with
// the out-of-line AsciiString(const char *) copy at 0x0005EE70 (ILT 0x00012C42)
// and the callee releases it through the StringBase<char> dtor 0x00887940, so
// the parameter is the real AsciiString; the landed row spells the same type
// as its alias AsciiStringYH, hence the second pinned spelling.
extern void __cdecl bfmeCommitYH( AsciiString label );

// Retail 0x012F3E70: filled from the HeadlessCount combo box selection.
extern void *g_bfmePtrAAV;
