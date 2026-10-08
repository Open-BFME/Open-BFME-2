// cl: -DNDEBUG -DWIN32 -D_WINDOWS -DIN_ADDR=in_addr -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// stlport
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

// FILE: wolscreens.cpp //////////////////////////////////////////////////////
// Westwood Online screen setup/teardown
// Author: Matthew D. Campbell, November 2001

// This TU supplies the retail-sized AudioEventRTS declaration below.  Several
// GUI headers include the Zero Hour AudioEventRTS header transitively, so keep
// that smaller declaration out without changing the shared headers.
#define _H_AUDIOEVENTRTS_

class AsciiString;
enum ObjectID;
enum DrawableID;
class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS( const AsciiString &eventName );
	AudioEventRTS( const AsciiString &eventName, ObjectID extra );
	AudioEventRTS( const AsciiString &eventName, DrawableID extra );
	~AudioEventRTS();
	AudioEventRTS( const AudioEventRTS &other );
	AudioEventRTS &operator=( const AudioEventRTS &other );

private:
	unsigned char m_data[0x70];
};

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/GadgetListBox.h"
#include "GameClient/GameText.h"
#include "GameClient/MessageBox.h"
#include "GameClient/ShellHooks.h"
//#include "GameNetwork/GameSpy.h"
//#include "GameNetwork/GameSpyGP.h"

#include "GameNetwork/GameSpyOverlay.h"
//#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"

class BFMERetailAsciiString;

template <typename T> class StringBase
{
friend class BFMERetailAsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	friend class UnicodeString;
	void *m_data;
};

void b_00042a50( void );
static void raiseOverlays( void );

// BFME WindowLayout vtable order (see game/.../window_layout.h):
// slot0 runInit, slot1 dtor, slot2 runUpdate (+0x08), slot3 runShutdown (+0x0c),
// slot4 hide (+0x10), slot5 bringForward (+0x14), slot8 destroyWindows (+0x20).
// Retail raiseOverlays/RaiseGSMessageBox and CloseAll use this slot map.
class BFMEOverlayLayoutCloseView
{
public:
	virtual void runInit( void *userData ) {}
	virtual ~BFMEOverlayLayoutCloseView() {}
	virtual void runUpdate( void *userData ) {}
	virtual void runShutdown( void *userData ) {}
	virtual void hide( int hide ) {}
	virtual void bringForward( void ) {}
	virtual void addWindow( void *window ) {}
	virtual void removeWindow( void *window ) {}
	virtual void destroyWindows( void ) {}
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other )
		: StringBase<char>( other ) {}
	~BFMERetailAsciiString() {}
};

class AudioManager;
extern AudioManager *TheAudio;

class BFMEOverlayAudioManagerView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void addAudioEvent( AudioEventRTS *event ) = 0;
};

// GameWindowManager::winCreateLayout is the retail virtual at +0x6c.  The
// parameter is a BFME AsciiString by value, so a local view is needed to keep
// the temporary's construction ABI without changing the shared header.
class BFMEOverlayWindowManagerView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual WindowLayout *winCreateLayout( BFMERetailAsciiString filename ) = 0;
};

// Message boxes -------------------------------------
static GameWinMsgBoxFunc okFunc = NULL;
static GameWinMsgBoxFunc cancelFunc = NULL;
static volatile Bool reOpenPlayerInfoFlag = FALSE;

/**
	* gsOverlays holds a list of the .wnd files used in GS overlays.
	* The entries *MUST* be in the same order as the GSOverlayType enum.
	*/
static const char * gsOverlays[GSOVERLAY_MAX] =
{
	"Menus/PopupPlayerInfo.wnd",	// Player info (right-click)
	"Menus/WOLMapSelectMenu.wnd",	// Map select
	"Menus/WOLBuddyOverlay.wnd",	// Buddy list
	"Menus/WOLPageOverlay.wnd",		// Find/page
	"Menus/PopupHostGame.wnd",		// Hosting options (game name, password, etc)
	"Menus/PopupJoinGame.wnd",		// Joining options (password, etc)
	"Menus/PopupLadderSelect.wnd",// LadderSelect
	"Menus/PopupLocaleSelect.wnd",// Prompt for user's locale
	"Menus/OptionsMenu.wnd",			// popup options
};

// Shared nine-slot storage owned by Rva00548B97Free.cpp. Native indexed
// references identify the same table, including the options slot at +32.
class Rva00548B97Helper;
extern Rva00548B97Helper *G00A05F88[GSOVERLAY_MAX];

// ?raiseOverlays present-unmatched  static emitter inlined into RaiseGSMessageBox
void raiseOverlays( void )
{
	// Double-load of G00A05F88[i] yields retail mov eax,[esi]/mov ecx,eax
	// thiscall shape (single local would load straight into ecx, 30B miss).
	for (int i=0; i<GSOVERLAY_MAX; ++i)
	{
		if (G00A05F88[i])
			((BFMEOverlayLayoutCloseView *)G00A05F88[i])->bringForward();
	}
}

/**
	* If the screen transitions underneath the dialog box, we
	* need to raise it to keep it visible.
	*
	* Retail (0x627C50, 32B): only the overlay bringForward loop. The ZH
	* messageBoxWindow->winBringToTop() tail is absent from the standalone body.
	*/
void RaiseGSMessageBox( void )
{
	raiseOverlays();
}
