// cl: -Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -DIN_ADDR=in_addr -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
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

// Use BFME 2's canonical, four-byte UnicodeString and prevent the Zero Hour
// headers below from introducing their older implementation.
#include "unicode_string.h"
#define UNICODESTRING_H
#define __MESSAGEBOX_H_
#include "PreRTS.h"

#include "GameClient/GadgetListBox.h"
#include "GameClient/GameText.h"
#include "GameClient/ShellHooks.h"
//#include "GameNetwork/GameSpy.h"
//#include "GameNetwork/GameSpyGP.h"

#include "GameNetwork/GameSpyOverlay.h"
//#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
// BFME 2's 0x88-byte audio event. The canonical header
// (Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h) pulls in the
// BFME 2 AsciiString shim, which collides with the Zero Hour AsciiString this
// unit is built on, so only the constructor/destructor ABI and the size the
// open-overlay click sound needs are declared here.
// class-gate: allow BfmeAudioEventPrefix136 Zero-Hour-header unit cannot include the shim-based canonical header
struct OpaqueRefElement4;
struct BfmeAudioEventPrefix136
{
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &, int);
	virtual ~BfmeAudioEventPrefix136();
	unsigned char m_data[0x88 - 4];
};

// The two native helpers finish with string teardown and do not preserve a
// GameWindow return value. Keep their BFME 2 void ABI; MessageBoxOk retains
// its existing provider declaration until that separate body is recovered.
GameWindow *MessageBoxOk(UnicodeString, UnicodeString, GameWinMsgBoxFunc);
void MessageBoxOkCancel(UnicodeString, UnicodeString, GameWinMsgBoxFunc, GameWinMsgBoxFunc);
void MessageBoxYesNo(UnicodeString, UnicodeString, GameWinMsgBoxFunc, GameWinMsgBoxFunc);

class BFMERetailAsciiString;

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
// These storage definitions already belong to Rva00627A50Clear.cpp.
extern unsigned char g_rva00627A50Flag;
extern void *g_rva00627A50A;
extern void *g_rva00627A50B;
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

static WindowLayout *overlayLayouts[GSOVERLAY_MAX] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

void GameSpyUpdateOverlays( void )
{
	// Same double-load as raiseOverlays: retail is
	// mov eax,[esi] / test eax,eax / jz / mov ecx,eax / mov eax,[ecx] / push 0 / call [eax+8].
	// A single local loads straight into ecx and misses the 34-byte body at 0x00627C10.
	for (int i=0; i<GSOVERLAY_MAX; ++i)
	{
		if (overlayLayouts[i])
			((BFMEOverlayLayoutCloseView *)overlayLayouts[i])->runUpdate( NULL );
	}
}

void GameSpyOpenOverlay( GSOverlayType overlay );
void GameSpyCloseOverlay( GSOverlayType overlay );

// Zero Hour GameSpyOverlay.cpp bodies; built /O1 they place uniquely at
// 0x00548F76 and 0x00548F93, calling the pinned open/close helpers. Retail
// inlines GameSpyIsOverlayOpen, so the toggle tests the layout slot directly.
void GameSpyToggleOverlay( GSOverlayType overlay )
{
	if (overlayLayouts[overlay] != NULL)
		GameSpyCloseOverlay(overlay);
	else
		GameSpyOpenOverlay(overlay);
}

void CheckReOpenPlayerInfo(void )
{
	if(!reOpenPlayerInfoFlag)
		return;

	GameSpyOpenOverlay(GSOVERLAY_PLAYERINFO);
	reOpenPlayerInfoFlag = FALSE;
}

// Zero Hour GameSpyOverlay.cpp supplies the callback and wrapper identities.
// Native 00548B08/00548B22 clear the one-byte open flag at E05F78 and use
// callback slots E05F7C/E05F80. BFME 2 does not retain a GameWindow pointer.
static void messageBoxOK()
{
	g_rva00627A50Flag = 0;
	if (g_rva00627A50A) {
		((GameWinMsgBoxFunc)g_rva00627A50A)();
		g_rva00627A50A = 0;
	}
}

static void messageBoxCancel()
{
	g_rva00627A50Flag = 0;
	if (g_rva00627A50B) {
		((GameWinMsgBoxFunc)g_rva00627A50B)();
		g_rva00627A50B = 0;
	}
}

void rva00627A50Clear();

void GSMessageBoxOk(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newOkFunc)
{
	rva00627A50Clear();
	MessageBoxOk(title, message, messageBoxOK);
	g_rva00627A50Flag = 1;
	g_rva00627A50A = (void *)newOkFunc;
}

void GSMessageBoxOkCancel(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newOkFunc, GameWinMsgBoxFunc newCancelFunc)
{
	rva00627A50Clear();
	MessageBoxOkCancel(title, message, messageBoxOK, messageBoxCancel);
	g_rva00627A50Flag = 1;
	g_rva00627A50A = (void *)newOkFunc;
	g_rva00627A50B = (void *)newCancelFunc;
}

void GSMessageBoxYesNo(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newYesFunc, GameWinMsgBoxFunc newNoFunc)
{
	rva00627A50Clear();
	MessageBoxYesNo(title, message, messageBoxOK, messageBoxCancel);
	g_rva00627A50Flag = 1;
	g_rva00627A50A = (void *)newYesFunc;
	g_rva00627A50B = (void *)newNoFunc;
}

// GameSpyOpenOverlay, retail 0x00548DED..0x00548F76 (393 bytes, EH), the
// Zero Hour GameSpyOverlay.cpp function. BFME 2 differences the bytes show:
// TheGameText's fetch(const char *) is slot 0x3C, the buddy-overlay click
// sound is the event at +0xC4 of TheAudio's misc audio (slot 78) built with
// 2 rather than the "GUICommunicatorOpen" literal and played through slot
// 25, the layout comes from TheWindowManager slot 0x80, and a new layout's
// +0x08 window gets its +0x1F4 field cleared before runInit. Each
// branch's hide/bringForward pair is the compiler's merged tail.
class GameSpyOverlayTextView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38();
	virtual UnicodeString fetch(const char *label, Bool *exists = NULL);	// +0x3C
};

struct GameSpyOverlayMiscAudioView
{
	unsigned char m_pad00[0xC4];
	unsigned char m_sound0C4[4];	// the event's OpaqueRefElement4
};

class GameSpyOverlayAudioView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);	// slot 25
	virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74();
	virtual void s75(); virtual void s76(); virtual void s77();
	virtual const GameSpyOverlayMiscAudioView *getMiscAudio();	// slot 78
};

struct GameSpyOverlayWindowView
{
	unsigned char m_pad000[0x1F4];
	Int m_field1F4;
};

struct GameSpyOverlayLayoutView
{
	void *m_vtable;
	Int m_field04;
	GameSpyOverlayWindowView *m_window08;
};

// winCreateLayout takes a BFME 2 AsciiString by value, built in its argument
// slot through the inline const-char constructor that calls StringBase<char>'s
// 0x00037BA0. This unit's Zero Hour AsciiString constructor is out of line,
// so the argument uses the existing AsciiStringYU spelling of 0x00037BA0
// behind an inline constructor.
class AsciiStringYU { public: AsciiStringYU(const char *text); AsciiStringYU(const AsciiStringYU &); ~AsciiStringYU(); char *m_data; };
struct GameSpyOverlayLayoutName : public AsciiStringYU { __forceinline GameSpyOverlayLayoutName(const char *s) : AsciiStringYU(s) {} };
class GameSpyOverlayWindowManagerView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7C();
	virtual WindowLayout *winCreateLayout(GameSpyOverlayLayoutName filename);	// +0x80
};

// Zero Hour's buddyTryReconnect, rowed at 0x00548B70 under this name.
void rva00627AA0Call();

void GameSpyOpenOverlay( GSOverlayType overlay )
{
	if (overlay == GSOVERLAY_BUDDY)
	{
		if (!TheGameSpyBuddyMessageQueue->isConnected())
		{
			// not connected - is it because we were disconnected?
			if (TheGameSpyBuddyMessageQueue->getLocalProfileID())
			{
				// used to be connected
				GSMessageBoxYesNo(((GameSpyOverlayTextView *)TheGameText)->fetch("GUI:GPErrorTitle"), ((GameSpyOverlayTextView *)TheGameText)->fetch("GUI:GPDisconnected"), rva00627AA0Call, NULL);
			}
			else
			{
				// no profile
				GSMessageBoxOk(((GameSpyOverlayTextView *)TheGameText)->fetch("GUI:GPErrorTitle"), ((GameSpyOverlayTextView *)TheGameText)->fetch("GUI:GPNoProfile"), NULL);
			}
			return;
		}
		BfmeAudioEventPrefix136 buttonClick(*(const OpaqueRefElement4 *)((GameSpyOverlayAudioView *)TheAudio)->getMiscAudio()->m_sound0C4, 2);

		if( TheAudio )
		{
			((GameSpyOverlayAudioView *)TheAudio)->addAudioEvent( &buttonClick );
		}  // end if
	}
	if (overlayLayouts[overlay])
	{
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->hide( FALSE );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->bringForward();
	}
	else
	{
		overlayLayouts[overlay] = ((GameSpyOverlayWindowManagerView *)TheWindowManager)->winCreateLayout( GameSpyOverlayLayoutName( gsOverlays[overlay] ) );
		if (((GameSpyOverlayLayoutView *)overlayLayouts[overlay])->m_window08)
			((GameSpyOverlayLayoutView *)overlayLayouts[overlay])->m_window08->m_field1F4 = 0;
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->runInit( NULL );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->hide( FALSE );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->bringForward();
	}
}
