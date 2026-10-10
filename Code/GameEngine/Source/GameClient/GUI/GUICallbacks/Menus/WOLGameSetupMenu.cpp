// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: WOLGameSetupMenu.cpp
// Author: Matt Campbell, December 2001
// Description: WOL Game Options Menu
///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "GameClient/GameText.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "Common/CustomMatchPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Mouse.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/MapUtil.h"
#include "GameClient/EstablishConnectionsMenu.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"

#include "GameNetwork/GameSpy/BuddyDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/GUIUtil.h"
#include "GameNetwork/GameSpy/GSConfig.h"

void WOLDisplaySlotList( void );

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

extern std::list<PeerResponse> TheLobbyQueuedUTMs;
extern void MapSelectorTooltip(GameWindow *window, WinInstanceData *instData,	UnsignedInt mouse);


#if defined(_DEBUG) || defined(_INTERNAL)
extern Bool g_debugSlots;
void slotListDebugLog(const char *fmt, ...)
{
	static char buf[1024];
	va_list va;
	va_start( va, fmt );
	_vsnprintf(buf, 1024, fmt, va );
	va_end( va );
	buf[1023] = 0;

	DEBUG_LOG(("%s", buf));
	if (g_debugSlots)
	{
		UnicodeString msg;
		msg.translate(buf);
		TheGameSpyInfo->addText(msg, GameSpyColor[GSCOLOR_DEFAULT], NULL);
	}
}
#define SLOTLIST_DEBUG_LOG(x) slotListDebugLog x
#else
#define SLOTLIST_DEBUG_LOG(x) DEBUG_LOG(x)
#endif

void SendStatsToOtherPlayers(const GameInfo *game)
{
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
	req.UTM.isStagingRoom = TRUE;
	req.id = "STATS/";
	AsciiString fullStr;
	PSPlayerStats fullStats = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
	PSPlayerStats subStats;
	subStats.id = fullStats.id;
	subStats.wins = fullStats.wins;
	subStats.losses = fullStats.losses;
	subStats.discons = fullStats.discons;
	subStats.desyncs = fullStats.desyncs;
	subStats.games = fullStats.games;
	subStats.locale = fullStats.locale;
	subStats.gamesAsRandom = fullStats.gamesAsRandom;
	GetAdditionalDisconnectsFromUserFile(&subStats);
	fullStr.format("%d %s", TheGameSpyInfo->getLocalProfileID(), TheGameSpyPSMessageQueue->formatPlayerKVPairs( subStats ));
	req.options = fullStr.str();

	Int localIndex = game->getLocalSlotNum();
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = game->getConstSlot(i);
		if (slot->isHuman() && i != localIndex)
		{
			AsciiString hostName;
			hostName.translate(slot->getName());
			req.nick = hostName.str();
			DEBUG_LOG(("SendStatsToOtherPlayers() - sending to '%s', data of\n\t'%s'\n", hostName.str(), req.options.c_str()));
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
static Bool isShuttingDown = false;
static Bool buttonPushed = false;
static char *nextScreen = NULL;
static Bool raiseMessageBoxes = false;
static Bool launchGameNext = FALSE;

// window ids ------------------------------------------------------------------------------
static NameKeyType parentWOLGameSetupID = NAMEKEY_INVALID;

static NameKeyType comboBoxPlayerID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType staticTextPlayerID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType buttonAcceptID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxColorID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxPlayerTemplateID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxTeamID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };
//static NameKeyType buttonStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType buttonMapStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };
static NameKeyType genericPingWindowID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType textEntryChatID = NAMEKEY_INVALID;
static NameKeyType textEntryMapDisplayID = NAMEKEY_INVALID;
static NameKeyType buttonBackID = NAMEKEY_INVALID;
static NameKeyType buttonStartID = NAMEKEY_INVALID;
static NameKeyType buttonEmoteID = NAMEKEY_INVALID;
static NameKeyType buttonSelectMapID = NAMEKEY_INVALID;
static NameKeyType windowMapID = NAMEKEY_INVALID;

static NameKeyType windowMapSelectMapID = NAMEKEY_INVALID;
static NameKeyType checkBoxUseStatsID = NAMEKEY_INVALID;
static NameKeyType checkBoxLimitSuperweaponsID = NAMEKEY_INVALID;
static NameKeyType comboBoxStartingCashID = NAMEKEY_INVALID;
static NameKeyType checkBoxLimitArmiesID = NAMEKEY_INVALID;

// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentWOLGameSetup = NULL;
static GameWindow *buttonBack = NULL;
static GameWindow *buttonStart = NULL;
static GameWindow *buttonSelectMap = NULL;
static GameWindow *buttonEmote = NULL;
static GameWindow *textEntryChat = NULL;
static GameWindow *textEntryMapDisplay = NULL;
static GameWindow *windowMap = NULL;
static GameWindow *checkBoxUseStats = NULL;
static GameWindow *checkBoxLimitSuperweapons = NULL;
static GameWindow *comboBoxStartingCash = NULL;
static GameWindow *checkBoxLimitArmies = NULL;

static GameWindow *comboBoxPlayer[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																									 NULL,NULL,NULL,NULL };
static GameWindow *staticTextPlayer[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																									 NULL,NULL,NULL,NULL };
static GameWindow *buttonAccept[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxColor[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxPlayerTemplate[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxTeam[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

//static GameWindow *buttonStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
//																								NULL,NULL,NULL,NULL };
//
static GameWindow *buttonMapStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *genericPingWindow[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static const Image *pingImages[3] = { NULL, NULL, NULL };

WindowLayout *WOLMapSelectLayout = NULL;

// PopBackToLobby is the matched row 0x004FDA72 in
// GameNetwork/GameSpy/GameSpyStagingRoomSlotInit.cpp (BFME 2 places Zero Hour's
// function in that unit); this unit's Zero Hour copy was a duplicate definition.

void updateMapStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], Bool onLoadScreen = FALSE );
void positionStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow);
void positionStartSpots(AsciiString mapName, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow);
void WOLPositionStartSpots( void )
{
	GameWindow *win = windowMap;
	if (WOLMapSelectLayout != NULL) {
		win = TheWindowManager->winGetWindowFromId(NULL, windowMapSelectMapID);

		// get the controls.
		NameKeyType listboxMapID = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:ListboxMap") );
		GameWindow *listboxMap = TheWindowManager->winGetWindowFromId( NULL, listboxMapID );

		if (listboxMap != NULL) {
			Int selected;
			UnicodeString map;
			
			// get the selected index
			GadgetListBoxGetSelected( listboxMap, &selected );

			if( selected != -1 )
			{

				// get text of the map to load
				map = GadgetListBoxGetText( listboxMap, selected, 0 );
				
				
				// set the map name in the global data map name
				AsciiString asciiMap;
				const char *mapFname = (const char *)GadgetListBoxGetItemData( listboxMap, selected );
				DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
				if (mapFname) {
					asciiMap = mapFname;
				} else {
					asciiMap.translate( map );
				}

				positionStartSpots(asciiMap, buttonMapStartPosition, win);
			}			
		}

	} else {
		DEBUG_ASSERTCRASH(win != NULL, ("no map preview window"));
		positionStartSpots( TheGameSpyInfo->getCurrentStagingRoom(), buttonMapStartPosition, win);
	}
}
static void savePlayerInfo( void )
{
	if (TheGameSpyGame)
	{
		Int slotNum = TheGameSpyGame->getLocalSlotNum();
		if (slotNum >= 0)
		{
			GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(slotNum);
			if (slot)
			{
				// save off some prefs
				CustomMatchPreferences pref;
				pref.setPreferredColor(slot->getColor());
				pref.setPreferredFaction(slot->getPlayerTemplate());
				if (TheGameSpyGame->amIHost())
				{
					pref.setPreferredMap(TheGameSpyGame->getMap());
          pref.setSuperweaponRestricted( TheGameSpyGame->getSuperweaponRestriction() != 0 );
          pref.setStartingCash( TheGameSpyGame->getStartingCash() );
        }
				pref.write();
			}
		}
	}
}

// Tooltips -------------------------------------------------------------------------------

static void playerTooltip(GameWindow *window,
													WinInstanceData *instData,
													UnsignedInt mouse)
{
	Int slotIdx = -1;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if (window == comboBoxPlayer[i] || window == staticTextPlayer[i])
		{
			slotIdx = i;
			break;
		}
	}
	if (slotIdx < 0)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	if (!game)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	GameSpyGameSlot *slot = game->getGameSpySlot(slotIdx);
	if (!slot || !slot->isHuman())
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	// for tooltip, we want:
	// * player name
	// * ping
	// * locale
	// * win/loss history
	// * discons/desyncs as one var
	// * favorite army
	// in that order.  got it?  good.

	UnicodeString uName = slot->getName();

	AsciiString aName;
	aName.translate(uName);
	PlayerInfoMap::iterator pmIt = TheGameSpyInfo->getPlayerInfoMap()->find(aName);
	if (pmIt == TheGameSpyInfo->getPlayerInfoMap()->end())
	{
		TheMouse->setCursorTooltip( uName, -1, NULL, 1.5f );
		return;
	}
	Int profileID = pmIt->second.m_profileID;

	PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(profileID);
	if (stats.id == 0)
	{
		TheMouse->setCursorTooltip( uName, -1, NULL, 1.5f );
		return;
	}

	Bool isLocalPlayer = slot == game->getGameSpySlot(game->getLocalSlotNum());

	AsciiString localeIdentifier;
	localeIdentifier.format("WOL:Locale%2.2d", stats.locale);
	UnicodeString	playerInfo;
	Int totalWins = 0, totalLosses = 0, totalDiscons = 0;
	PerGeneralMap::iterator it;

	for (it = stats.wins.begin(); it != stats.wins.end(); ++it)
	{
		totalWins += it->second;
	}
	for (it = stats.losses.begin(); it != stats.losses.end(); ++it)
	{
		totalLosses += it->second;
	}
	for (it = stats.discons.begin(); it != stats.discons.end(); ++it)
	{
		totalDiscons += it->second;
	}
	for (it = stats.desyncs.begin(); it != stats.desyncs.end(); ++it)
	{
		totalDiscons += it->second;
	}
	UnicodeString favoriteSide;
	Int numGames = 0;
	Int favorite = 0;
	for(it = stats.games.begin(); it != stats.games.end(); ++it)
	{
		if(it->second >= numGames)
		{
			numGames = it->second;
			favorite = it->first;
		}
	}
	if(numGames == 0)
		favoriteSide = TheGameText->fetch("GUI:None");
	else if( stats.gamesAsRandom >= numGames )
		favoriteSide = TheGameText->fetch("GUI:Random");
	else
	{		
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(favorite);
		if (fac)
		{
			AsciiString side;
			side.format("SIDE:%s", fac->getSide().str());

			favoriteSide = TheGameText->fetch(side);
		}
	}

	playerInfo.format(TheGameText->fetch("TOOLTIP:StagingPlayerInfo"),
		TheGameText->fetch(localeIdentifier).str(),
		slot->getPingAsInt(),
		totalWins, totalLosses, totalDiscons,
		favoriteSide.str());

	UnicodeString tooltip = UnicodeString::TheEmptyString;
	if (isLocalPlayer)
	{
		tooltip.format(TheGameText->fetch("TOOLTIP:LocalPlayer"), uName.str());
	}
	else
	{
		// not us
		if (TheGameSpyInfo->getBuddyMap()->find(profileID) != TheGameSpyInfo->getBuddyMap()->end())
		{
			// buddy
			tooltip.format(TheGameText->fetch("TOOLTIP:BuddyPlayer"), uName.str());
		}
		else
		{
			if (profileID)
			{
				// non-buddy profiled player
				tooltip.format(TheGameText->fetch("TOOLTIP:ProfiledPlayer"), uName.str());
			}
			else
			{
				// non-profiled player
				tooltip.format(TheGameText->fetch("TOOLTIP:GenericPlayer"), uName.str());
			}
		}
	}

	tooltip.concat(playerInfo);

	TheMouse->setCursorTooltip( tooltip, -1, NULL, 1.5f ); // the text and width are the only params used.  the others are the default values.
}

void gameAcceptTooltip(GameWindow *window, WinInstanceData *instData, UnsignedInt mouse)
{
	Int x, y;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	Int winPosX, winPosY, winWidth, winHeight;

	window->winGetScreenPosition(&winPosX, &winPosY);

	window->winGetSize(&winWidth, &winHeight);

	if ((x > winPosX && x < (winPosX + winWidth)) && (y > winPosY && y < (winPosY + winHeight)))
	{
		TheMouse->setCursorTooltip(TheGameText->fetch("TOOLTIP:GameAcceptance"), -1, NULL);
	}
}

void pingTooltip(GameWindow *window, WinInstanceData *instData, UnsignedInt mouse)
{
	Int x, y;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	
	Int winPosX, winPosY, winWidth, winHeight;

	window->winGetScreenPosition(&winPosX, &winPosY);

	window->winGetSize(&winWidth, &winHeight);

	if ((x > winPosX && x < (winPosX + winWidth)) && (y > winPosY && y < (winPosY + winHeight)))
	{
		TheMouse->setCursorTooltip(TheGameText->fetch("TOOLTIP:ConnectionSpeed"), -1, NULL);
	}
}

//external declarations of the Gadgets the callbacks can use
GameWindow *listboxGameSetupChat = NULL;
NameKeyType listboxGameSetupChatID = NAMEKEY_INVALID;

static void handleColorSelection(int index)
{
	GameWindow *combo = comboBoxColor[index];
	Int color, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	color = (Int)GadgetComboBoxGetItemData(combo, selIndex);

	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (color == slot->getColor())
			return;

		if (color >= -1 && color < TheMultiplayerSettings->getNumColors())
		{
			Bool colorAvailable = TRUE;
			if(color != -1 )
			{
				for(Int i=0; i <MAX_SLOTS; i++)
				{
					GameSlot *checkSlot = myGame->getSlot(i);
					if(color == checkSlot->getColor() && slot != checkSlot)
					{
						colorAvailable = FALSE;
						break;
					}
				}
			}
			if(!colorAvailable)
				return;
		}

		slot->setColor(color);

		if (TheGameSpyInfo->amIHost())
		{
			// send around a new slotlist
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the color from the host
			if (!slot->isPlayer(TheGameSpyInfo->getLocalName()))
				return;

			AsciiString options;
			options.format("Color=%d", color);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = hostName.str();
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

static void handlePlayerTemplateSelection(int index)
{
	GameWindow *combo = comboBoxPlayerTemplate[index];
	Int playerTemplate, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	playerTemplate = (Int)GadgetComboBoxGetItemData(combo, selIndex);
	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (playerTemplate == slot->getPlayerTemplate())
			return;

		Int oldTemplate = slot->getPlayerTemplate();
		slot->setPlayerTemplate(playerTemplate);

		if (oldTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			// was observer, so populate color & team with all, and enable
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}
		else if (playerTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			// is becoming observer, so populate color & team with random only, and disable
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}


		if (TheGameSpyInfo->amIHost())
		{
			// send around a new slotlist
			myGame->resetAccepted();
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the playerTemplate from the host
			AsciiString options;
			options.format("PlayerTemplate=%d", playerTemplate);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = hostName.str();
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}


static void handleStartPositionSelection(Int player, int startPos)
{
	GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
	
	if (myGame)
	{
		GameSpyGameSlot * slot = myGame->getGameSpySlot(player);
		if (!slot)
			return;

		if (startPos == slot->getStartPos())
			return;
		Bool skip = FALSE;
		if (startPos < 0)
		{
			skip = TRUE;
		}

		if(!skip)
		{	
			Bool isAvailable = TRUE;
			for(Int i = 0; i < MAX_SLOTS; ++i)
			{
				if(i != player && myGame->getSlot(i)->getStartPos() == startPos)
				{
					isAvailable = FALSE;
					break;
				}
			}
			if( !isAvailable )
				return;
		}
		slot->setStartPos(startPos);

		if (myGame->amIHost())
		{
			// send around a new slotlist
			myGame->resetAccepted();
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the color from the host
			if (AreSlotListUpdatesEnabled())
			{
				// request the playerTemplate from the host
				AsciiString options;
				options.format("StartPos=%d", slot->getStartPos());
				AsciiString hostName;
				hostName.translate(myGame->getSlot(0)->getName());
				PeerRequest req;
				req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
				req.UTM.isStagingRoom = TRUE;
				req.id = "REQ/";
				req.nick = hostName.str();
				req.options = options.str();
				TheGameSpyPeerMessageQueue->addRequest(req);

			}
		}
	}
}



static void handleTeamSelection(int index)
{
	GameWindow *combo = comboBoxTeam[index];
	Int team, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	team = (Int)GadgetComboBoxGetItemData(combo, selIndex);
	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (team == slot->getTeamNumber())
			return;

		slot->setTeamNumber(team);

		if (TheGameSpyInfo->amIHost())
		{
			// send around a new slotlist
			myGame->resetAccepted();
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the team from the host
			AsciiString options;
			options.format("Team=%d", team);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = hostName.str();
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

static void handleStartingCashSelection()
{
  GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
  
  if (myGame)
  {
    Int selIndex;
    GadgetComboBoxGetSelectedPos(comboBoxStartingCash, &selIndex);
    
    Money startingCash;
    startingCash.deposit( (UnsignedInt)GadgetComboBoxGetItemData( comboBoxStartingCash, selIndex ), FALSE );
    myGame->setStartingCash( startingCash );
    myGame->resetAccepted();
    
    if (myGame->amIHost())
    {
      // send around the new data
      TheGameSpyInfo->setGameOptions();
      WOLDisplaySlotList();// Update the accepted button UI
    }
  }
}

static void handleLimitSuperweaponsClick()
{
  GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
  
  if (myGame)
  {
    // At the moment, 1 and 0 are the only choices supported in the GUI, though the system could
    // support more.
    if ( GadgetCheckBoxIsChecked( checkBoxLimitSuperweapons ) )
    {
      myGame->setSuperweaponRestriction( 1 );
    }
    else
    {
      myGame->setSuperweaponRestriction( 0 );
    }
    myGame->resetAccepted();
    
    if (myGame->amIHost())
    {
      // send around a new slotlist
      TheGameSpyInfo->setGameOptions();
      WOLDisplaySlotList();// Update the accepted button UI
    }
  }
}


static void StartPressed(void)
{
	Bool isReady = TRUE;
	Bool allHaveMap = TRUE;
	Int playerCount = 0;
	Int humanCount = 0;
	GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
	if (!myGame)
		return;

	// see if everyone's accepted and count the number of players in the game
	UnicodeString mapDisplayName;
	const MapMetaData *mapData = TheMapCache->findMap( myGame->getMap() );
	Bool willTransfer = TRUE;
	if (mapData)
	{
		mapDisplayName.format(L"%ls", mapData->m_displayName.str());
		willTransfer = !mapData->m_isOfficial;
	}
	else
	{
		mapDisplayName.format(L"%hs", myGame->getMap().str());
		willTransfer = WouldMapTransfer(myGame->getMap());
	}
	for( int i = 0; i < MAX_SLOTS; i++ )
	{
		if ((myGame->getSlot(i)->isAccepted() == FALSE) && (myGame->getSlot(i)->isHuman() == TRUE))
		{
			isReady = FALSE;
			if (!myGame->getSlot(i)->hasMap() && !willTransfer)
			{
				UnicodeString msg;
				msg.format(TheGameText->fetch("GUI:PlayerNoMap"), myGame->getSlot(i)->getName().str(), mapDisplayName.str());
				TheGameSpyInfo->addText(msg, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
				allHaveMap = FALSE;
			}
		}
		if(myGame->getSlot(i)->isOccupied() && myGame->getSlot(i)->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (myGame->getSlot(i)->isHuman())
				humanCount++;
			playerCount++;
		}
	}

	// Check for too many players
	const MapMetaData *md = TheMapCache->findMap( myGame->getMap() );
	if (!md || md->m_numPlayers < playerCount)
	{
		if (myGame->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:TooManyPlayers"), (md)?md->m_numPlayers:0);
			TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for observer + AI players
	if (TheGlobalData->m_netMinPlayers && !humanCount)
	{
		if (myGame->amIHost())
		{
			UnicodeString text = TheGameText->fetch("GUI:NeedHumanPlayers");
			TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for too few players
	if (playerCount < TheGlobalData->m_netMinPlayers)
	{
		if (myGame->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMorePlayers"),playerCount);
			TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for too few teams
	int numRandom = 0;
	std::set<Int> teams; 
	for (i=0; i<MAX_SLOTS; ++i)
	{
		GameSlot *slot = myGame->getSlot(i);
		if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (slot->getTeamNumber() >= 0)
			{
				teams.insert(slot->getTeamNumber());
			}
			else
			{
				++numRandom;
			}
		}
	}
	if (numRandom + teams.size() < TheGlobalData->m_netMinPlayers)
	{
		if (myGame->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMoreTeams"));
			TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	if (numRandom + teams.size() < 2)
	{
		UnicodeString text;
		text.format(TheGameText->fetch("GUI:SandboxMode"));
		TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
	}

	if(isReady)
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_STARTGAME;
		TheGameSpyPeerMessageQueue->addRequest(req);

		SendStatsToOtherPlayers(myGame);

		// we've started, there's no going back
		// i.e. disable the back button.
		buttonBack->winEnable(FALSE);
		GameWindow *buttonBuddy = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator"));
		if (buttonBuddy)
			buttonBuddy->winEnable(FALSE);
		GameSpyCloseOverlay(GSOVERLAY_BUDDY);

		*TheGameSpyGame = *myGame;
		TheGameSpyGame->startGame(0);
	}
	else if (allHaveMap)
	{
		TheGameSpyInfo->addText(TheGameText->fetch("GUI:NotifiedStartIntent"), GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_UTMROOM;
		req.UTM.isStagingRoom = TRUE;
		req.id = "HWS/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
	}

}//void StartPressed(void)

//-------------------------------------------------------------------------------------------------
/** Update options on screen */
//-------------------------------------------------------------------------------------------------
void WOLDisplayGameOptions( void )
{
	GameSpyStagingRoom *theGame = TheGameSpyInfo->getCurrentStagingRoom();
	if (!parentWOLGameSetup || !theGame)
		return;

	const GameSlot *localSlot = NULL;
	if (theGame->getLocalSlotNum() >= 0)
		localSlot = theGame->getConstSlot(theGame->getLocalSlotNum());

	const MapMetaData *md = TheMapCache->findMap(TheGameSpyInfo->getCurrentStagingRoom()->getMap());
	if (md && localSlot && localSlot->hasMap())
	{
		GadgetStaticTextSetText(textEntryMapDisplay, md->m_displayName);
	}
	else
	{
		AsciiString s = TheGameSpyInfo->getCurrentStagingRoom()->getMap();
		if (s.reverseFind('\\'))
		{
			s = s.reverseFind('\\') + 1;
		}
		UnicodeString mapDisplay;
		mapDisplay.translate(s);
		GadgetStaticTextSetText(textEntryMapDisplay, mapDisplay);
	}
	WOLPositionStartSpots();
	updateMapStartSpots(TheGameSpyInfo->getCurrentStagingRoom(), buttonMapStartPosition);

  //If our display does not match the current state of game settings, update the checkbox.
  Bool isUsingStats = TheGameSpyInfo->getCurrentStagingRoom()->getUseStats() ? TRUE : FALSE;
  if (GadgetCheckBoxIsChecked(checkBoxUseStats) != isUsingStats)
  {
  	GadgetCheckBoxSetChecked(checkBoxUseStats, isUsingStats);
    checkBoxUseStats->winSetTooltip( TheGameText->fetch( isUsingStats ? "TOOLTIP:UseStatsOn" : "TOOLTIP:UseStatsOff" ) );
  }

  Bool oldFactionsOnly = theGame->oldFactionsOnly();
  if (GadgetCheckBoxIsChecked(checkBoxLimitArmies) != oldFactionsOnly)
  {
    GadgetCheckBoxSetChecked(checkBoxLimitArmies, oldFactionsOnly);
    // Repopulate the lists of available armies, since the old list is now wrong
    for (Int i = 0; i < MAX_SLOTS; i++)
    {
      PopulatePlayerTemplateComboBox(i, comboBoxPlayerTemplate, theGame, theGame->getAllowObservers() );      

      // Make sure selections are up to date on all machines
      handlePlayerTemplateSelection(i) ;
    }
  }

  // Note: must check if checkbox is already correct to avoid infinite recursion
  Bool limitSuperweapons = (theGame->getSuperweaponRestriction() != 0);
  if ( limitSuperweapons != GadgetCheckBoxIsChecked(checkBoxLimitSuperweapons))
    GadgetCheckBoxSetChecked( checkBoxLimitSuperweapons, limitSuperweapons );
  
  Int itemCount = GadgetComboBoxGetLength(comboBoxStartingCash);
  for ( Int index = 0; index < itemCount; index++ )
  {
    Int value  = (Int)GadgetComboBoxGetItemData(comboBoxStartingCash, index);
    if ( value == theGame->getStartingCash().countMoney() )
    {
      // Note: must check if combobox is already correct to avoid infinite recursion
      Int selectedIndex;
      GadgetComboBoxGetSelectedPos( comboBoxStartingCash, &selectedIndex );
      if ( index != selectedIndex )
        GadgetComboBoxSetSelectedPos(comboBoxStartingCash, index, TRUE);

      break;
    }
  }
  
  DEBUG_ASSERTCRASH( index < itemCount, ("Could not find new starting cash amount %d in list", theGame->getStartingCash().countMoney() ) );
}


//  -----------------------------------------------------------------------------------------
// The Bad munkee slot list displaying function
//-------------------------------------------------------------------------------------------------
void WOLDisplaySlotList( void )
{
	if (!parentWOLGameSetup || !TheGameSpyInfo->getCurrentStagingRoom())
		return;

	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	if (!game->isInGame())
		return;

	DEBUG_ASSERTCRASH(!game->getConstSlot(0)->isOpen(), ("Open host!"));

	UpdateSlotList( game, comboBoxPlayer, comboBoxColor,
		comboBoxPlayerTemplate, comboBoxTeam, buttonAccept, buttonStart, buttonMapStartPosition );

	WOLDisplayGameOptions();

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = game->getGameSpySlot(i);
		if (slot && slot->isHuman())
		{
			if (i == game->getLocalSlotNum())
			{
				// set up my own ping...
				slot->setPingString(TheGameSpyInfo->getPingString());
			}

			if (genericPingWindow[i])
			{
				genericPingWindow[i]->winHide(FALSE);
				Int ping = slot->getPingAsInt();
				if (ping < TheGameSpyConfig->getPingCutoffGood())
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[0]);
				}
				else if (ping < TheGameSpyConfig->getPingCutoffBad())
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[1]);
				}
				else
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[2]);
				}
			}
		}
		else
		{
			if (genericPingWindow[i])
				genericPingWindow[i]->winHide(TRUE);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** Initialize the Gadgets Options Menu */
//-------------------------------------------------------------------------------------------------
void InitWOLGameGadgets( void )
{
	GameSpyStagingRoom *theGameInfo = TheGameSpyInfo->getCurrentStagingRoom();
	pingImages[0] = TheMappedImageCollection->findImageByName("Ping03");
	pingImages[1] = TheMappedImageCollection->findImageByName("Ping02");
	pingImages[2] = TheMappedImageCollection->findImageByName("Ping01");
	DEBUG_ASSERTCRASH(pingImages[0], ("Can't find ping image!"));
	DEBUG_ASSERTCRASH(pingImages[1], ("Can't find ping image!"));
	DEBUG_ASSERTCRASH(pingImages[2], ("Can't find ping image!"));

	//Initialize the gadget IDs
	parentWOLGameSetupID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:GameSpyGameOptionsMenuParent" ) );
	buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonBack" ) );
	buttonStartID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonStart" ) );
	textEntryChatID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:TextEntryChat" ) );
	textEntryMapDisplayID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:TextEntryMapDisplay" ) );
	listboxGameSetupChatID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ListboxChatWindowGameSpyGameSetup" ) );
	buttonEmoteID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonEmote" ) );
	buttonSelectMapID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonSelectMap" ) );
	checkBoxUseStatsID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:CheckBoxUseStats" ) );
	windowMapID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:MapWindow" ) );
  checkBoxLimitSuperweaponsID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:CheckboxLimitSuperweapons"));
  comboBoxStartingCashID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:ComboBoxStartingCash"));
  checkBoxLimitArmiesID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:CheckBoxLimitArmies"));
	windowMapSelectMapID = TheNameKeyGenerator->nameToKey(AsciiString("WOLMapSelectMenu.wnd:WinMapPreview"));

	NameKeyType staticTextTitleID = NAMEKEY("GameSpyGameOptionsMenu.wnd:StaticTextGameName");

	// Initialize the pointers to our gadgets
	parentWOLGameSetup = TheWindowManager->winGetWindowFromId( NULL, parentWOLGameSetupID );
	buttonEmote = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonEmoteID  );
	buttonSelectMap = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonSelectMapID  );
	checkBoxUseStats = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxUseStatsID );
	buttonStart = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonStartID  );
	buttonBack = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,  buttonBackID);
	listboxGameSetupChat = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, listboxGameSetupChatID );
	textEntryChat = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, textEntryChatID );
	textEntryMapDisplay = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, textEntryMapDisplayID );
	windowMap = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,windowMapID  );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the parentWOLGameSetup.wnd:MapWindow" ));

  checkBoxLimitSuperweapons = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxLimitSuperweaponsID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:CheckboxLimitSuperweapons" ));
  comboBoxStartingCash = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxStartingCashID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:ComboBoxStartingCash" ));
  PopulateStartingCashComboBox( comboBoxStartingCash, TheGameSpyGame );
  checkBoxLimitArmies = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxLimitArmiesID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:CheckBoxLimitArmies" ));

  // Limit Armies can ONLY be set in the Host Game window (PopupHostGame.wnd)
  checkBoxLimitArmies->winEnable( false );
  // Ditto use stats
  checkBoxUseStats->winEnable( false );
	Int isUsingStats = TheGameSpyGame->getUseStats();
  GadgetCheckBoxSetChecked(checkBoxUseStats, isUsingStats );
  checkBoxUseStats->winSetTooltip( TheGameText->fetch( isUsingStats ? "TOOLTIP:UseStatsOn" : "TOOLTIP:UseStatsOff" ) );

  if ( !TheGameSpyGame->amIHost() )
  {
    checkBoxLimitSuperweapons->winEnable( false );
    comboBoxStartingCash->winEnable( false );
		NameKeyType labelID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:StartingCashLabel"));
		TheWindowManager->winGetWindowFromId(parentWOLGameSetup, labelID)->winEnable( FALSE );
  }

	if (isUsingStats)
	{
		// Recorded stats games can never limit superweapons, limit armies, or have inflated starting cash.
		// This should probably be enforced at the gamespy level as well, to prevent expoits.
		checkBoxLimitSuperweapons->winEnable( FALSE );
		comboBoxStartingCash->winEnable( FALSE );
		checkBoxLimitArmies->winEnable( FALSE );
		NameKeyType labelID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:StartingCashLabel"));
		TheWindowManager->winGetWindowFromId(parentWOLGameSetup, labelID)->winEnable( FALSE );
	}

	//Added By Sadullah Nader
	//Tooltip Function set 
	windowMap->winSetTooltipFunc(MapSelectorTooltip);
	//
	
	GameWindow *staticTextTitle = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, staticTextTitleID );
	if (staticTextTitle)
	{
		GadgetStaticTextSetText(staticTextTitle, TheGameSpyGame->getGameName());
	}

	if (!theGameInfo)
	{
		DEBUG_CRASH(("No staging room!"));
		return;
	}

	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		AsciiString tmpString;
		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxPlayer%d", i);
		comboBoxPlayerID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxPlayer[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxPlayerID[i] );
		GadgetComboBoxReset(comboBoxPlayer[i]);
		comboBoxPlayer[i]->winSetTooltipFunc(playerTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:StaticTextPlayer%d", i);
		staticTextPlayerID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		staticTextPlayer[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, staticTextPlayerID[i] );
		staticTextPlayer[i]->winSetTooltipFunc(playerTooltip);
		if (TheGameSpyInfo->amIHost())
			staticTextPlayer[i]->winHide(TRUE);

		if(i==0 && TheGameSpyInfo->amIHost())
		{
			UnicodeString uName;
			uName.translate(TheGameSpyInfo->getLocalName());
			GadgetComboBoxAddEntry(comboBoxPlayer[i],uName,GameSpyColor[GSCOLOR_PLAYER_OWNER]);
			GadgetComboBoxSetSelectedPos(comboBoxPlayer[0],0);
		}
		else
		{
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:Open"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:Closed"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:EasyAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:MediumAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:HardAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxSetSelectedPos(comboBoxPlayer[i],0);
		}

		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxColor%d", i);
		comboBoxColorID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxColor[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxColorID[i] );
		DEBUG_ASSERTCRASH(comboBoxColor[i], ("Could not find the comboBoxColor[%d]",i ));
		PopulateColorComboBox(i, comboBoxColor, theGameInfo);
		GadgetComboBoxSetSelectedPos(comboBoxColor[i], 0);
		
		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxPlayerTemplate%d", i);
		comboBoxPlayerTemplateID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxPlayerTemplate[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxPlayerTemplateID[i] );
		DEBUG_ASSERTCRASH(comboBoxPlayerTemplate[i], ("Could not find the comboBoxPlayerTemplate[%d]",i ));
		PopulatePlayerTemplateComboBox(i, comboBoxPlayerTemplate, theGameInfo, theGameInfo->getAllowObservers() );

		// add tooltips to the player template combobox and listbox
		comboBoxPlayerTemplate[i]->winSetTooltipFunc(playerTemplateComboBoxTooltip);
		GadgetComboBoxGetListBox(comboBoxPlayerTemplate[i])->winSetTooltipFunc(playerTemplateListBoxTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxTeam%d", i);
		comboBoxTeamID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxTeam[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxTeamID[i] );
		DEBUG_ASSERTCRASH(comboBoxTeam[i], ("Could not find the comboBoxTeam[%d]",i ));
		PopulateTeamComboBox(i, comboBoxTeam, theGameInfo);

		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonAccept%d", i); 
		buttonAcceptID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonAccept[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonAcceptID[i] );
		DEBUG_ASSERTCRASH(buttonAccept[i], ("Could not find the buttonAccept[%d]",i ));
		buttonAccept[i]->winSetTooltipFunc(gameAcceptTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:GenericPing%d", i); 
		genericPingWindowID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		genericPingWindow[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, genericPingWindowID[i] );
		DEBUG_ASSERTCRASH(genericPingWindow[i], ("Could not find the genericPingWindow[%d]",i ));
		genericPingWindow[i]->winSetTooltipFunc(pingTooltip);

//		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonStartPosition%d", i);
//		buttonStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
//		buttonStartPosition[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonStartPositionID[i] );
//		DEBUG_ASSERTCRASH(buttonStartPosition[i], ("Could not find the ButtonStartPosition[%d]",i ));

		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonMapStartPosition%d", i);
		buttonMapStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonMapStartPosition[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonMapStartPositionID[i] );
		DEBUG_ASSERTCRASH(buttonMapStartPosition[i], ("Could not find the ButtonMapStartPosition[%d]",i ));

//		if (buttonStartPosition[i])
//			buttonStartPosition[i]->winHide(TRUE);

		if(i !=0 && buttonAccept[i])
			buttonAccept[i]->winHide(TRUE);
	}

	if( buttonAccept[0] )
		buttonAccept[0]->winEnable(TRUE);

	if (buttonBack != NULL)
	{
		buttonBack->winEnable(TRUE);
	}
		//GadgetButtonSetEnabledColor(buttonAccept[0], GameSpyColor[GSCOLOR_ACCEPT_TRUE]);
}

void DeinitWOLGameGadgets( void )
{
	parentWOLGameSetup = NULL;
	buttonEmote = NULL;
	buttonSelectMap = NULL;
	buttonStart = NULL;
	buttonBack = NULL;
	listboxGameSetupChat = NULL;
	textEntryChat = NULL;
	textEntryMapDisplay = NULL;
	windowMap = NULL;
	checkBoxUseStats = NULL;
  checkBoxLimitSuperweapons = NULL;
  comboBoxStartingCash = NULL;
  
//	GameWindow *staticTextTitle = NULL;
	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		comboBoxPlayer[i] = NULL;
		staticTextPlayer[i] = NULL;
		comboBoxColor[i] = NULL;
		comboBoxPlayerTemplate[i] = NULL;
		comboBoxTeam[i] = NULL;
		buttonAccept[i] = NULL;
//		buttonStartPosition[i] = NULL;
		buttonMapStartPosition[i] = NULL;
		genericPingWindow[i] = NULL;
	}
}

static Bool initDone = false;
UnsignedInt lastSlotlistTime = 0;
UnsignedInt enterTime = 0;
Bool initialAcceptEnable = FALSE;
//-------------------------------------------------------------------------------------------------
/** Initialize the Lan Game Options Menu */
//-------------------------------------------------------------------------------------------------
void WOLGameSetupMenuInit( WindowLayout *layout, void *userData )
{
	if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
	{
		TheGameSpyGame->setGameInProgress(FALSE);

		// check if we were disconnected
		Int disconReason;
		if (TheGameSpyInfo->isDisconnectedAfterGameStart(&disconReason))
		{
			AsciiString disconMunkee;
			disconMunkee.format("GUI:GSDisconReason%d", disconReason);
			UnicodeString title, body;
			title = TheGameText->fetch( "GUI:GSErrorTitle" );
			body = TheGameText->fetch( disconMunkee );
			GameSpyCloseAllOverlays();
			GSMessageBoxOk( title, body );
			TheGameSpyInfo->reset();
			DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, and we were disconnected, so pop immediate back to main menu\n"));
			TheShell->popImmediate();
			return;
		}

		// If we init while the game is in progress, we are really returning to the menu
		// after the game.  So, we pop the menu and go back to the lobby.  Whee!
		DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, so pop immediate back to lobby\n"));
		TheShell->popImmediate();
		if (TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->isConnected())
		{
			DEBUG_LOG(("We're still connected, so pushing back on the lobby\n"));
			TheShell->push("Menus/WOLCustomLobby.wnd", TRUE);
		}
		return;
	}
	TheGameSpyInfo->setCurrentGroupRoom(0);

	if (TheNAT != NULL) {
		delete TheNAT;
		TheNAT = NULL;
	}

	nextScreen = NULL;
	buttonPushed = false;
	isShuttingDown = false;
	launchGameNext = FALSE;

	//initialize the gadgets
	EnableSlotListUpdates(FALSE);
	InitWOLGameGadgets();
	EnableSlotListUpdates(TRUE);
	TheGameSpyInfo->registerTextWindow(listboxGameSetupChat);

	//The dialog needs to react differently depending on whether it's the host or not.
	TheMapCache->updateCache();
	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	GameSpyGameSlot *hostSlot = game->getGameSpySlot(0);
	hostSlot->setAccept();
	if (TheGameSpyInfo->amIHost())
	{
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		hostSlot->setColor( customPref.getPreferredColor() );
		hostSlot->setPlayerTemplate( customPref.getPreferredFaction() );
		hostSlot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)natPref.getFirewallBehavior());
		hostSlot->setPingString(TheGameSpyInfo->getPingString());
		game->setMap(customPref.getPreferredMap());

		// Recorded stats games can never limit superweapons, limit armies, or have inflated starting cash.
		// This should probably be enforced at the gamespy level as well, to prevent expoits.
		Int isUsingStats = TheGameSpyGame->getUseStats();
		game->setStartingCash( isUsingStats? TheMultiplayerSettings->getDefaultStartingMoney() : customPref.getStartingCash() );
		game->setSuperweaponRestriction( isUsingStats? 0 : customPref.getSuperweaponRestricted() ? 1 : 0 );
		if (isUsingStats)
			game->setOldFactionsOnly( 0 );

		//game->setOldFactionsOnly( customPref.getFactionsLimited() );
    if ( game->oldFactionsOnly() )
    {
      // Make sure host follows the old factions only restrictions!
      const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(hostSlot->getPlayerTemplate());

      if ( fac != NULL && !fac->isOldFaction() )
      {
        hostSlot->setPlayerTemplate( PLAYERTEMPLATE_RANDOM );
      }
    }

		for (Int i=1; i<MAX_SLOTS; ++i)
		{
			GameSpyGameSlot *slot = game->getGameSpySlot(i);
			slot->setState( SLOT_OPEN );
		}

		AsciiString lowerMap = customPref.getPreferredMap();
		lowerMap.toLower();
		std::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it != TheMapCache->end())
		{
			hostSlot->setMapAvailability(TRUE);
			game->setMapCRC( it->second.m_CRC );
			game->setMapSize( it->second.m_filesize );

			game->adjustSlotsForMap(); // BGC- adjust the slots for the new map.
		}


		WOLDisplaySlotList();
		WOLDisplayGameOptions();
	}
	else
	{
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		AsciiString options;
		PeerRequest req;
		UnicodeString uName = hostSlot->getName();
		AsciiString aName;
		aName.translate(uName);
		req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
		req.UTM.isStagingRoom = TRUE;
		req.id = "REQ/";
		req.nick = aName.str();
		options.format("PlayerTemplate=%d", customPref.getPreferredFaction());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Color=%d", customPref.getPreferredColor());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("NAT=%d", natPref.getFirewallBehavior());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Ping=%s", TheGameSpyInfo->getPingString().str());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
   
		game->setMapCRC( game->getMapCRC() );		// force a recheck
		game->setMapSize( game->getMapSize() ); // of if we have the map

		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			//I'm a client, disable the controls I can't touch.
			comboBoxPlayer[i]->winEnable(FALSE);

			comboBoxColor[i]->winEnable(FALSE);
			comboBoxPlayerTemplate[i]->winEnable(FALSE);
			comboBoxTeam[i]->winEnable(FALSE);
//			buttonStartPosition[i]->winEnable(FALSE);
			buttonMapStartPosition[i]->winEnable(FALSE);

		}
		buttonStart->winSetText(TheGameText->fetch("GUI:Accept"));
		buttonStart->winEnable( FALSE );
		buttonSelectMap->winEnable( FALSE );
    checkBoxLimitSuperweapons->winEnable( FALSE ); // Can look but only host can touch
    comboBoxStartingCash->winEnable( FALSE );      // Ditto
		initialAcceptEnable = FALSE;
	}

	// Show the Menu
	layout->hide( FALSE );
	
	// Make sure the text fields are clear
	GadgetListBoxReset( listboxGameSetupChat );
	GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);	

	initDone = true;
	TheGameSpyInfo->setGameOptions();
	//TheShell->registerWithAnimateManager(parentWOLGameSetup, WIN_ANIMATION_SLIDE_TOP, TRUE);
	WOLPositionStartSpots();

	lastSlotlistTime = 0;
	enterTime = timeGetTime();

	// Set Keyboard to chat entry
	TheWindowManager->winSetFocus( textEntryChat );
	raiseMessageBoxes = true;
	TheTransitionHandler->setGroup("GameSpyGameOptionsMenuFade");
}// void WOLGameSetupMenuInit( WindowLayout *layout, void *userData )

//-------------------------------------------------------------------------------------------------
/** This is called when a shutdown is complete for this menu */
//-------------------------------------------------------------------------------------------------
static void shutdownComplete( WindowLayout *layout )
{

	isShuttingDown = false;

	// hide the layout
	layout->hide( TRUE );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, (nextScreen != NULL) );

	if (nextScreen != NULL)
	{
		if (!TheGameSpyPeerMessageQueue || !TheGameSpyPeerMessageQueue->isConnected())
		{
			DEBUG_LOG(("GameSetup shutdownComplete() - skipping push because we're disconnected\n"));
		}
		else
		{
			TheShell->push(nextScreen);
		}
	}

	/*
	if (launchGameNext)
	{
		TheGameSpyGame->launchGame();
		TheGameSpyInfo->leaveStagingRoom();
	}
	*/

	nextScreen = NULL;

}  // end if

//-------------------------------------------------------------------------------------------------
/** GameSpy Game Options menu shutdown method */
//-------------------------------------------------------------------------------------------------
void WOLGameSetupMenuShutdown( WindowLayout *layout, void *userData )
{
	TheGameSpyInfo->unregisterTextWindow(listboxGameSetupChat);

	if( WOLMapSelectLayout )
	{
		WOLMapSelectLayout->destroyWindows();
		WOLMapSelectLayout->deleteInstance();
		WOLMapSelectLayout = NULL;
	}
	parentWOLGameSetup = NULL;
	EnableSlotListUpdates(FALSE);
	DeinitWOLGameGadgets();
	if (TheEstablishConnectionsMenu != NULL)
	{
		TheEstablishConnectionsMenu->endMenu();
	}
	initDone = false;

	isShuttingDown = true;

	// if we are shutting down for an immediate pop, skip the animations
	Bool popImmediate = *(Bool *)userData;
	if( popImmediate )
	{

		shutdownComplete( layout );
		return;

	}  //end if

	TheShell->reverseAnimatewindow();

	RaiseGSMessageBox();
	TheTransitionHandler->reverse("GameSpyGameOptionsMenuFade");
}  // void WOLGameSetupMenuShutdown( WindowLayout *layout, void *userData )

// Zero Hour's WOLGameSetupMenuUpdate (and its fillPlayerInfo helper) is not
// part of this unit's retail rows and nothing else references it. Its local
// PlayerInfo values instantiated Zero Hour's PlayerInfo default ctor, copy ctor
// and dtor (and PeerResponse's ctor, dtor and assignment) under the retail names;
// the link kept them over the matched rows (default ctor 0x003822C4 in
// Open2Rec4F1280.cpp, copy ctor 0x001EF485, PeerResponse 0x00389F77 / 0x0038A063 /
// 0x0038B383). Removed as Chat.cpp's GameSpyInfo::addChat bodies were.

//-------------------------------------------------------------------------------------------------
/** Lan Game Options menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLGameSetupMenuInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{
	/*
	switch( msg ) 
	{

		//-------------------------------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{
			if (buttonPushed)
				break;

			GameWindow *control = (GameWindow *)mData1;
			NameKeyType controlID = (NameKeyType)control->winGetWindowId();
			DEBUG_LOG(("GWM_RIGHT_UP for control %d(%s)\n", controlID, TheNameKeyGenerator->keyToName(controlID).str()));
			break;
		}

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;
			if (buttonPushed)
				break;

			switch( key )
			{
				// ----------------------------------------------------------------------------------------
				case KEY_ESC:
				{
					//
					// send a simulated selected event to the parent window of the
					// back/exit button
					//
					if( BitTest( state, KEY_STATE_UP ) )
					{
						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																							(WindowMsgData)buttonBack, buttonBackID );
					}  // end if
					// don't let key fall through anywhere else
					return MSG_HANDLED;
				}  // end escape
			}  // end switch( key )
		}  // end char
	}  // end switch( msg )
	*/
	return MSG_IGNORED;
}//WindowMsgHandledType WOLGameSetupMenuInput( GameWindow *window, UnsignedInt msg,


// Slash commands -------------------------------------------------------------------------
extern "C" {
int getQR2HostingStatus(void);
}
extern int isThreadHosting;

Bool handleGameSetupSlashCommands(UnicodeString uText)
{
	AsciiString message;
	message.translate(uText);

	if (message.getCharAt(0) != '/')
	{
		return FALSE; // not a slash command
	}

	AsciiString remainder = message.str() + 1;
	AsciiString token;
	remainder.nextToken(&token);
	token.toLower();

	if (token == "host")
	{
		UnicodeString s;
		s.format(L"Hosting qr2:%d thread:%d", getQR2HostingStatus(), isThreadHosting);
		TheGameSpyInfo->addText(s, GameSpyColor[GSCOLOR_DEFAULT], NULL);
		return TRUE; // was a slash command
	}
	else if (token == "me" && uText.getLength()>4)
	{
		TheGameSpyInfo->sendChat(UnicodeString(uText.str()+4), TRUE, NULL);
		return TRUE; // was a slash command
	}
#if defined(_DEBUG) || defined(_INTERNAL)
	else if (token == "slots")
	{
		g_debugSlots = !g_debugSlots;
		TheGameSpyInfo->addText(UnicodeString(L"Toggled SlotList debug"), GameSpyColor[GSCOLOR_DEFAULT], NULL);
		return TRUE; // was a slash command
	}
	else if (token == "discon")
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_LOGOUT;
		TheGameSpyPeerMessageQueue->addRequest( req );
		return TRUE;
	}
#endif // defined(_DEBUG) || defined(_INTERNAL)

	return FALSE; // not a slash command
}

static Int getNextSelectablePlayer(Int start)
{
	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	if (!game->amIHost())
		return -1;
	for (Int j=start; j<MAX_SLOTS; ++j)
	{
		GameSpyGameSlot *slot = game->getGameSpySlot(j);
		if (slot && slot->getStartPos() == -1 &&
			( (j==game->getLocalSlotNum() && game->getConstSlot(j)->getPlayerTemplate()!=PLAYERTEMPLATE_OBSERVER)
			|| slot->isAI()))
		{
			return j;
		}
	}
	return -1;
}

static Int getFirstSelectablePlayer(const GameInfo *game)
{
	const GameSlot *slot = game->getConstSlot(game->getLocalSlotNum());
	if (!game->amIHost() || slot && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		return game->getLocalSlotNum();

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		slot = game->getConstSlot(i);
		if (slot && slot->isAI())
			return i;
	}

	return game->getLocalSlotNum();
}

//-------------------------------------------------------------------------------------------------
/** WOL Game Options menu window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLGameSetupMenuSystem( GameWindow *window, UnsignedInt msg, 
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;
	static buttonCommunicatorID = NAMEKEY_INVALID;
	switch( msg )
	{
		//-------------------------------------------------------------------------------------------------	
		case GWM_CREATE:
			{
				buttonCommunicatorID = NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator");
				break;
			} // case GWM_DESTROY:
		//-------------------------------------------------------------------------------------------------
		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:
		//-------------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
			{	
				// if we're givin the opportunity to take the keyboard focus we must say we want it
				if( mData1 == TRUE )
					*(Bool *)mData2 = TRUE;

				return MSG_HANDLED;
			}//case GWM_INPUT_FOCUS:
		//-------------------------------------------------------------------------------------------------
		case GCM_SELECTED:
			{
				if (!initDone)
					break;
				if (buttonPushed)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
        if ( controlID == comboBoxStartingCashID )
        {
          handleStartingCashSelection();
        }
        else
        {
				  GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
				  for (Int i = 0; i < MAX_SLOTS; i++)
				  {
					  if (controlID == comboBoxColorID[i])
					  {
						  handleColorSelection(i);
					  }
					  else if (controlID == comboBoxPlayerTemplateID[i])
					  {
						  handlePlayerTemplateSelection(i);
					  }
					  else if (controlID == comboBoxTeamID[i])
					  {
						  handleTeamSelection(i);
					  }
					  else if( controlID == comboBoxPlayerID[i] && TheGameSpyInfo->amIHost() )
					  {
						  // We don't have anything that'll happen if we click on ourselves
						  if(i == myGame->getLocalSlotNum())
						   break;
						  // Get
						  Int pos = -1;
						  GadgetComboBoxGetSelectedPos(comboBoxPlayer[i], &pos);
						  if( pos != SLOT_PLAYER && pos >= 0)
						  {
							  if( myGame->getSlot(i)->getState() == SLOT_PLAYER )
							  {
								  PeerRequest req;
								  req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
								  req.UTM.isStagingRoom = TRUE;
								  AsciiString aName;
								  aName.translate(myGame->getSlot(i)->getName());
								  req.nick = aName.str();
								  req.id = "KICK/";
								  req.options = "true";
								  TheGameSpyPeerMessageQueue->addRequest(req);

								  UnicodeString name = myGame->getSlot(i)->getName();
								  myGame->getSlot(i)->setState(SlotState(pos));
								  myGame->resetAccepted();
								  TheGameSpyInfo->setGameOptions();
								  WOLDisplaySlotList();
								  //TheLAN->OnPlayerLeave(name);
							  }
							  else if( myGame->getSlot(i)->getState() != pos )
							  {
								  Bool wasAI = (myGame->getSlot(i)->isAI());
								  myGame->getSlot(i)->setState(SlotState(pos));
								  Bool isAI = (myGame->getSlot(i)->isAI());
								  myGame->resetAccepted();
								  if (wasAI ^ isAI)
									  PopulatePlayerTemplateComboBox(i, comboBoxPlayerTemplate, myGame, wasAI && myGame->getAllowObservers());
								  TheGameSpyInfo->setGameOptions();
								  WOLDisplaySlotList();
							  }
						  }
						  break;
					  }
				  }
        }
        break;
			}// case GCM_SELECTED:
		//-------------------------------------------------------------------------------------------------
		case GBM_SELECTED:
			{
				if (buttonPushed)
					break;

				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				static buttonCommunicatorID = NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator");
				if ( controlID == buttonBackID )
				{
					savePlayerInfo();
					if( WOLMapSelectLayout )
					{
						WOLMapSelectLayout->destroyWindows();
						WOLMapSelectLayout->deleteInstance();
						WOLMapSelectLayout = NULL;
					}

					TheGameSpyInfo->getCurrentStagingRoom()->reset();
					//peerLeaveRoom(TheGameSpyChat->getPeer(), StagingRoom, NULL);
					TheGameSpyInfo->leaveStagingRoom();
					buttonPushed = true;
					nextScreen = "Menus/WOLCustomLobby.wnd";
					TheShell->pop();

				} //if ( controlID == buttonBack )
				else if ( controlID == buttonCommunicatorID )
				{
					GameSpyToggleOverlay( GSOVERLAY_BUDDY );

				}
				else if ( controlID == buttonEmoteID )
				{
					// read the user's input
					txtInput.set(GadgetTextEntryGetText( textEntryChat ));
					// Clear the text entry line
					GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
					// Clean up the text (remove leading/trailing chars, etc)
					txtInput.trim();
					// Echo the user's input to the chat window
					if (!txtInput.isEmpty())
						TheGameSpyInfo->sendChat(txtInput, FALSE, NULL); // 'emote' button is now carriage-return
				} //if ( controlID == buttonEmote )
				else if ( controlID == buttonSelectMapID )
				{
					WOLMapSelectLayout = TheWindowManager->winCreateLayout( "Menus/WOLMapSelectMenu.wnd" );
					WOLMapSelectLayout->runInit();
					WOLMapSelectLayout->hide( FALSE );
					WOLMapSelectLayout->bringForward();
				}
				else if ( controlID == buttonStartID )
				{
					savePlayerInfo();
					if (TheGameSpyInfo->amIHost())
					{
						StartPressed();
					}
					else
					{
						//I'm the Client... send an accept message to the host.
						GameSlot *localSlot = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(TheGameSpyInfo->getCurrentStagingRoom()->getLocalSlotNum());
						if (localSlot)
						{
							localSlot->setAccept();
						}
						UnicodeString hostName = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(0)->getName();
						AsciiString asciiName;
						asciiName.translate(hostName);
						PeerRequest req;
						req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
						req.UTM.isStagingRoom = TRUE;
						req.id = "accept";
						req.nick = asciiName.str();
						req.options = "true";
						TheGameSpyPeerMessageQueue->addRequest(req);
						//peerSetReady( PEER, PEERTrue );
						WOLDisplaySlotList();
					}
				}
        else if ( controlID == checkBoxLimitSuperweaponsID )
        {
          handleLimitSuperweaponsClick();
        }
				else
				{
					for (Int i = 0; i < MAX_SLOTS; i++)
					{
						if (controlID == buttonMapStartPositionID[i])
						{
							GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
							Int playerIdxInPos = -1;
							for (Int j=0; j<MAX_SLOTS; ++j)
							{
								GameSpyGameSlot *slot = game->getGameSpySlot(j);
								if (slot && slot->getStartPos() == i)
								{
									playerIdxInPos = j;
									break;
								}
							}
							if (playerIdxInPos >= 0)
							{
								GameSpyGameSlot *slot = game->getGameSpySlot(playerIdxInPos);
								if (playerIdxInPos == game->getLocalSlotNum() || (game->amIHost() && slot && slot->isAI()))
								{
									// it's one of my type.  Try to change it.
									Int nextPlayer = getNextSelectablePlayer(playerIdxInPos+1);
									handleStartPositionSelection(playerIdxInPos, -1);
									if (nextPlayer >= 0)
									{
										handleStartPositionSelection(nextPlayer, i);
									}
								}
							}
							else
							{
								// nobody in the slot - put us in
								Int nextPlayer = getNextSelectablePlayer(0);
								if (nextPlayer < 0)
									nextPlayer = getFirstSelectablePlayer(game);
								handleStartPositionSelection(nextPlayer, i);
							}
						}
					}
				}


				break;
			}// case GBM_SELECTED:
		//-------------------------------------------------------------------------------------------------
		case GBM_SELECTED_RIGHT:
   		{
   			if (buttonPushed)
   				break;
   
   			GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				for (Int i = 0; i < MAX_SLOTS; i++)
				{
					if (controlID == buttonMapStartPositionID[i])
					{
						GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
						Int playerIdxInPos = -1;
						for (Int j=0; j<MAX_SLOTS; ++j)
						{
							GameSpyGameSlot *slot = game->getGameSpySlot(j);
							if (slot && slot->getStartPos() == i)
							{
								playerIdxInPos = j;
								break;
							}
						}
						if (playerIdxInPos >= 0)
						{
							GameSpyGameSlot *slot = game->getGameSpySlot(playerIdxInPos);
							if (playerIdxInPos == game->getLocalSlotNum() || (game->amIHost() && slot && slot->isAI()))
							{
								// it's one of my type.  Remove it.
								handleStartPositionSelection(playerIdxInPos, -1);
							}
						}
					}
				}
				break;
			}

		//-------------------------------------------------------------------------------------------------
		case GEM_EDIT_DONE:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				// Take the user's input and echo it into the chat window as well as
				// send it to the other clients on the lan
				if ( controlID == textEntryChatID )
				{
					
					// read the user's input
					txtInput.set(GadgetTextEntryGetText( textEntryChat ));
					// Clear the text entry line
					GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
					// Clean up the text (remove leading/trailing chars, etc)
					txtInput.trim();
					// Echo the user's input to the chat window
					if (!txtInput.isEmpty())
					{
						if (!handleGameSetupSlashCommands(txtInput))
						{
							TheGameSpyInfo->sendChat(txtInput, false, NULL);
						}
					}

				}// if ( controlID == textEntryChatID )
				break;
			}
		//-------------------------------------------------------------------------------------------------
		default:
			return MSG_IGNORED;
	}//Switch
	return MSG_HANDLED;
}//WindowMsgHandledType WOLGameSetupMenuSystem( GameWindow *window, UnsignedInt msg, 


