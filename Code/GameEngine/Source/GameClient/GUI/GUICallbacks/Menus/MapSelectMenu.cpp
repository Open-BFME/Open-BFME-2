// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /O1
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: shutdownCompleteMapSelectMenu 0x0050CE92 (25B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
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
// Bind the existing target-owned Shell pop method spelling in this TU.
#define pop rva0035BEC7
#include "GameClient/Shell.h"
#undef pop
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
Bool mapSelectIsShuttingDown = false;
Bool mapSelectStartGame = false;
static Bool buttonPushed = false;
extern int g_00DD12D8; // Shared difficulty storage defined by the radio-button helper.


class BFMERetailScriptEngineView
{
public:
	unsigned char m_unreconstructed_00000[0x17620];
	GameDifficulty m_globalDifficulty;

	GameDifficulty getGlobalDifficulty() const { return m_globalDifficulty; }
};


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
// BFME2 native 0x0050CE92: shared shutdown flag followed by Shell completion.
// ?shutdownCompleteMapSelectMenu@@YAXPAVWindowLayout@@@Z
void shutdownCompleteMapSelectMenu( WindowLayout *layout )
{

	mapSelectIsShuttingDown = false;

	// our shutdown is complete
	TheShell->shutdownComplete( layout );

}


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
  // end MapSelectMenuInit

//-------------------------------------------------------------------------------------------------
/** MapSelect menu shutdown method */
//-------------------------------------------------------------------------------------------------
  // end MapSelectMenuInput

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
static Int mapSelectHeadlessCount = 0;
  // end MapSelectMenuSystem

// Zero Hour setupGameStart semantics, BFME1 6c1e0b51 donor menu.
// Native 50CEDE..50CF3C and WB144EF60 prove pendingFile at +AC0,
// the shared startGame flag, reverseAnimatewindow and optional Apt hide.
// Keep the menu suffix because setupGameStart is a source-local helper.
class Rva00222A8BTarget {public:void rva00222F55(bool);};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct MapSelectGlobalDataView {char pad[0xAC0];AsciiString pendingFile;};
void setupGameStartMapSelectMenu(AsciiString label)
{
 mapSelectStartGame=true;
 ((MapSelectGlobalDataView *)TheWritableGlobalData)->pendingFile=label;
 TheShell->reverseAnimatewindow();
 if(g_bfmeAptWindowManager)((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(false);
}

// Native system callback uses window-manager slots58/60 and message slot18.
class MapSelectWindowManagerView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual int winSendSystemMsg(GameWindow *,unsigned,unsigned,unsigned);
virtual void slot59();
virtual GameWindow *winGetWindowFromId(GameWindow *,NameKeyType);
};
class MapSelectMessageStreamView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual GameMessage *appendMessage(GameMessage::Type);
};

int Rva00304BCDPopulate(GameWindow *,bool,bool,const AsciiString &);
// BFME1 6c1e0b51 MapSelectMenuSystem plus WB144E530 and native50D672..50DBAA.
// BFME2 clears game state through message0x22 and uses direct string setters.
WindowMsgHandledType MapSelectMenuSystem( GameWindow *window, UnsignedInt msg,
																				  WindowMsgData mData1, WindowMsgData mData2 )
{
	static NameKeyType buttonBack = NAMEKEY_INVALID;
	static NameKeyType buttonOK = NAMEKEY_INVALID;
	static NameKeyType listboxMap = NAMEKEY_INVALID;
	static NameKeyType radioButtonEasyAI = NAMEKEY_INVALID;
	static NameKeyType radioButtonMediumAI = NAMEKEY_INVALID;
	static NameKeyType radioButtonHardAI = NAMEKEY_INVALID;
	switch( msg )
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CREATE:
		{

			// get ids for our children controls
			buttonBack = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonBack") );
			buttonOK = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonOK") );
			listboxMap = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ListboxMap") );
			radioButtonEasyAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonEasyAI") );
			radioButtonMediumAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonMediumAI") );
			radioButtonHardAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonHardAI") );
			break;

		}  // end create

		//---------------------------------------------------------------------------------------------
		case GWM_DESTROY:
		{

			break;

		}  // end case

		// --------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{

			// if we're givin the opportunity to take the keyboard focus we must say we want it
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;

			return MSG_HANDLED;

		}  // end input

		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			if (buttonPushed)
				break;

			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			static NameKeyType singlePlayerID = NAMEKEY("MapSelectMenu.wnd:ButtonSinglePlayer");
			static NameKeyType multiplayerID = NAMEKEY("MapSelectMenu.wnd:ButtonMultiplayer");
			if ( controlID == singlePlayerID )
			{
				showSoloMaps = true;
				OptionPreferences pref;
				Rva00304BCDPopulate( mapList, pref.usesSystemMapDir(), !showSoloMaps, AsciiString::TheEmptyString );
			}
			else if ( controlID == multiplayerID )
			{
				showSoloMaps = false;
				OptionPreferences pref;
				Rva00304BCDPopulate( mapList, pref.usesSystemMapDir(), !showSoloMaps, AsciiString::TheEmptyString );
			}
			else if ( controlID == radioButtonSystemMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				Rva00304BCDPopulate( mapList, TRUE, !showSoloMaps, AsciiString::TheEmptyString );
				OptionPreferences pref;
				pref["UseSystemMapDir"].set("yes");
				pref.write();
			}
			else if ( controlID == radioButtonUserMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				Rva00304BCDPopulate( mapList, FALSE, !showSoloMaps, AsciiString::TheEmptyString );
				OptionPreferences pref;
				pref["UseSystemMapDir"].set("no");
				pref.write();
			}
			else if( controlID == buttonBack )
			{

				// go back one screen
				TheShell->rva0035BEC7();
				buttonPushed = true;

			}  // end if
			else if( controlID == buttonOK )
			{

				Int selected;
				UnicodeString map;
				GameWindow *mapWindow = ((MapSelectWindowManagerView *)TheWindowManager)->winGetWindowFromId( NULL, listboxMap );

				// get the selected index
				GadgetListBoxGetSelected( mapWindow, &selected );

				if( selected != -1 )
				{
					buttonPushed = true;
					// reset the campaign manager to empty
					((MapSelectMessageStreamView *)TheMessageStream)->appendMessage((GameMessage::Type)0x22);
					// get text of the map to load
					const char *mapFname = (const char *)GadgetListBoxGetItemData( mapWindow, selected );
					DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
					if (mapFname)
					{
						GameWindow *headlessCount = ((MapSelectWindowManagerView *)TheWindowManager)->winGetWindowFromId( NULL,
							NAMEKEY("MapSelectMenu.wnd:HeadlessCount") );
						GadgetComboBoxGetSelectedPos( headlessCount, &mapSelectHeadlessCount );
						setupGameStartMapSelectMenu( mapFname );
					}
				}  // end if

			}  // end else if
			else if( controlID == radioButtonEasyAI)
			{
				g_00DD12D8 = DIFFICULTY_EASY;
			}
			else if( controlID == radioButtonMediumAI)
			{
				g_00DD12D8 = DIFFICULTY_NORMAL;
			}
			else if( controlID == radioButtonHardAI)
			{
				g_00DD12D8 = DIFFICULTY_HARD;
			}
			break;

		}  // end selected
		// BFME's list box double-click message is 0x4015 (GBM_SELECTED + 0xD).
		case 0x4015:
			{
				if (buttonPushed)
					break;

				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				if( controlID == listboxMap )
				{
					int rowSelected = mData2;

					if (rowSelected >= 0)
					{
						//buttonPushed = true;
						GadgetListBoxSetSelected( control, rowSelected );
						NameKeyType buttonOKID = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonOK") );
						GameWindow *buttonOK = ((MapSelectWindowManagerView *)TheWindowManager)->winGetWindowFromId( NULL, buttonOKID );

						((MapSelectWindowManagerView *)TheWindowManager)->winSendSystemMsg( window, GBM_SELECTED,
																								(WindowMsgData)buttonOK, buttonOKID );
					}
				}
				break;
			}
		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}  // end MapSelectMenuSystem
