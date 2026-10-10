// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
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

// FILE: Chat.cpp //////////////////////////////////////////////////////
// Generals GameSpy chat-related code
// Author: Matthew D. Campbell, July 2002

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "../../../../../reference/shims/peerdefs/GameNetwork/GameSpy/PeerDefs.h"
#include "../../../../../reference/shims/nat/GameNetwork/GameSpy/PeerThread.h"
#include "../../../../../reference/shims/peerdefs/GameNetwork/GameSpy/PeerDefsImplementation.h"

#include "Common/AudioEventRTS.h"
#include "Common/INI.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/LanguageFilter.h"
#include "GameClient/GameWindowManager.h"
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameClient/InGameUI.h"
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define OFFSET(x) (sizeof(Int) * (x))
static const FieldParse GameSpyColorFieldParse[] = 
{

	{ "Default",						INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_DEFAULT) },
	{ "CurrentRoom",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CURRENTROOM) },
	{ "ChatRoom",						INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_ROOM) },
	{ "Game",								INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_GAME) },
	{ "GameFull",						INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_GAME_FULL) },
	{ "GameCRCMismatch",		INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_GAME_CRCMISMATCH) },
	{ "PlayerNormal",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_PLAYER_NORMAL) },
	{ "PlayerOwner",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_PLAYER_OWNER) },
	{ "PlayerBuddy",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_PLAYER_BUDDY) },
	{ "PlayerSelf",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_PLAYER_SELF) },
	{ "PlayerIgnored",			INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_PLAYER_IGNORED) },
	{ "ChatNormal",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_NORMAL) },
	{ "ChatEmote",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_EMOTE) },
	{ "ChatOwner",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_OWNER) },
	{ "ChatOwnerEmote",			INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_OWNER_EMOTE) },
	{ "ChatPriv",						INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_PRIVATE) },
	{ "ChatPrivEmote",			INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_PRIVATE_EMOTE) },
	{ "ChatPrivOwner",			INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_PRIVATE_OWNER) },
	{ "ChatPrivOwnerEmote",	INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE) },
	{ "ChatBuddy",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_BUDDY) },
	{ "ChatSelf",						INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_CHAT_SELF) },
	{ "AcceptTrue",					INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_ACCEPT_TRUE) },
	{ "AcceptFalse",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_ACCEPT_FALSE) },
	{ "MapSelected",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_MAP_SELECTED) },
	{ "MapUnselected",			INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_MAP_UNSELECTED) },
	{ "MOTD",								INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_MOTD) },
	{ "MOTDHeading",				INI::parseColorInt,	NULL,	OFFSET(GSCOLOR_MOTD_HEADING) },

	{ NULL,					NULL,						NULL,						0 }  // keep this last

};

// The "OnlineChatColors" block parser, Zero Hour's body unchanged: the
// block-parse registration at VA 0x00DB918C binds that token to 0x001EF471,
// which hands GameSpyColor (VA 0x00DB9198) and this table (VA 0x00BE0428)
// to INI::initFromINI. Ghidra never started a function there (it is
// reached only through the registration), so no BSim pairing found it.
void INI::parseOnlineChatColorDefinition( INI* ini )
{
	// parse the ini definition
	ini->initFromINI( GameSpyColor, GameSpyColorFieldParse );
}


Color GameSpyColor[GSCOLOR_MAX] =
{
	GameMakeColor(255,255,255,255),	// GSCOLOR_DEFAULT
	GameMakeColor(255,255,  0,255),	// GSCOLOR_CURRENTROOM
	GameMakeColor(255,255,255,255),	// GSCOLOR_ROOM
	GameMakeColor(128,128,0,255),		// GSCOLOR_GAME
	GameMakeColor(128,128,128,255),	// GSCOLOR_GAME_FULL
	GameMakeColor(128,128,128,255),	// GSCOLOR_GAME_CRCMISMATCH
	GameMakeColor(255,255,255,255),	// GSCOLOR_PLAYER_NORMAL
	GameMakeColor(255,  0,255,255),	// GSCOLOR_PLAYER_OWNER
	GameMakeColor(255,  0,128,255),	// GSCOLOR_PLAYER_BUDDY
	GameMakeColor(255,  0,  0,255),	// GSCOLOR_PLAYER_SELF
	GameMakeColor(128,128,128,255),	// GSCOLOR_PLAYER_IGNORED
	GameMakeColor(255,255,255,255),		// GSCOLOR_CHAT_NORMAL
	GameMakeColor(255,128,0,255),		// GSCOLOR_CHAT_EMOTE,
	GameMakeColor(255,255,0,255),		// GSCOLOR_CHAT_OWNER,
	GameMakeColor(128,255,0,255),		// GSCOLOR_CHAT_OWNER_EMOTE,
	GameMakeColor(0,0,255,255),			// GSCOLOR_CHAT_PRIVATE,
	GameMakeColor(0,255,255,255),		// GSCOLOR_CHAT_PRIVATE_EMOTE,
	GameMakeColor(255,0,255,255),		// GSCOLOR_CHAT_PRIVATE_OWNER,
	GameMakeColor(255,128,255,255),	// GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE,
	GameMakeColor(255,  0,255,255),	// GSCOLOR_CHAT_BUDDY,
	GameMakeColor(255,  0,128,255),	// GSCOLOR_CHAT_SELF,
	GameMakeColor(  0,255,  0,255),	// GSCOLOR_ACCEPT_TRUE,
	GameMakeColor(255,  0,  0,255),	// GSCOLOR_ACCEPT_FALSE,
	GameMakeColor(255,255,  0,255),	// GSCOLOR_MAP_SELECTED,
	GameMakeColor(255,255,255,255),	// GSCOLOR_MAP_UNSELECTED,
	GameMakeColor(255,255,255,255),	// GSCOLOR_MOTD,
	GameMakeColor(255,255,  0,255),	// GSCOLOR_MOTD_HEADING,
};

// GameSpyInfo::sendChat is not defined here either. The Zero Hour body built a
// PeerRequest with the shim's Zero Hour layout, so this unit emitted
// ??0PeerRequest@@QAE@XZ and ??1PeerRequest@@QAE@XZ COMDATs that are not
// retail's 492-byte record (ctor 0x001EF661, dtor 0x001EF723) and the link kept
// them. No other unit references sendChat; the body remains in git history.

// GameSpyInfo::addChat (both overloads) is declared in PeerDefsImplementation.h
// and not defined here. The Zero Hour bodies took PlayerInfo by value and
// searched the PlayerInfoMap, so this unit emitted PlayerInfo's copy
// constructor, destructor and map find COMDATs with the shim's Zero Hour
// layout (two strings); retail's PlayerInfo destructor 0x001EF50E releases
// three strings (+8, +4, +0), and the link kept these wrong copies against the
// rowed map units. The bodies remain in git history.

// ?addText@GameSpyInfo@@ present-unmatched
Int GameSpyInfo::addText( UnicodeString message, Color c, GameWindow *win )
{
	if (TheGameSpyGame && TheGameSpyGame->isInGame() && TheGameSpyGame->isGameInProgress())
	{
		static AudioEventRTS messageFromChatSound("GUIMessageReceived");
		TheAudio->addAudioEvent(&messageFromChatSound);

		TheInGameUI->message(message);
	}

	if (!win)
	{
		// try to pick up a registered text window
		if (m_textWindows.empty())
			return -1;

		win = *(m_textWindows.begin());
	}
	Int index = GadgetListBoxAddEntryText(win, message, c, -1, -1);
	GadgetListBoxSetItemData(win, (void *)-1, index);

	return index;
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsRegisterTextWindow.cpp
// ?registerTextWindow@GameSpyInfo@@ present-unmatched
void GameSpyInfo::registerTextWindow( GameWindow *win )
{
	m_textWindows.insert(win);
}

// ?unregisterTextWindow@GameSpyInfo@@ present-unmatched
void GameSpyInfo::unregisterTextWindow( GameWindow *win )
{
	m_textWindows.erase(win);
}
