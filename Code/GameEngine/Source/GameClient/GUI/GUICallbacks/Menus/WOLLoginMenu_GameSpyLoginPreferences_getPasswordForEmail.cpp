// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z
// retail 0x005CA70E, 114 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenu.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: WOLLoginMenu.cpp
// Author: Chris Huybregts, November 2001
// Description: Lan Lobby Menu
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

class WOLLoginAsciiStringLess
{
public:
	bool operator()(const AsciiString& lhs, const AsciiString& rhs) const
	{
		// strcmp directly: the donor header's inline AsciiString::compare
		// would be emitted here as an out-of-line COMDAT that is not retail's
		// compare (0x69D6), and other units' references would bind to it.
		return strcmp(lhs.str(), rhs.str()) < 0;
	}
};

namespace _STL
{
	template <>
	struct less<AsciiString> : public WOLLoginAsciiStringLess
	{
	};
}

#include "Common/STLTypedefs.h"

#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/QuotedPrintable.h"
#include "Common/Registry.h"
#include "Common/UserPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameText.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/MessageBox.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/GameWindowTransitions.h"

#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"

#include "GameNetwork/GameSpyOverlay.h"

#include "GameNetwork/WOLBrowser/WebBrowser.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#ifdef ALLOW_NON_PROFILED_LOGIN
Bool GameSpyUseProfiles = false;
#endif // ALLOW_NON_PROFILED_LOGIN

static Bool webBrowserActive = FALSE;
static Bool useWebBrowserForTOS = FALSE;

static Bool isShuttingDown = false;
static Bool buttonPushed = false;
static char *nextScreen = NULL;

static const UnsignedInt loginTimeoutInMS = 10000;
static UnsignedInt loginAttemptTime = 0;

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences() { m_emailPasswordMap.clear(); m_emailNickMap.clear(); }
	virtual ~GameSpyLoginPreferences() {}

	virtual Bool load(AsciiString fname);
	virtual Bool write(void);

	AsciiString getPasswordForEmail( AsciiString email );
	AsciiString getDateForEmail( AsciiString email, AsciiString &month, AsciiString &date, AsciiString &year  );
	AsciiStringList getNicksForEmail( AsciiString email );
	void addLogin( AsciiString email, AsciiString nick, AsciiString password, AsciiString date );
	void forgetLogin( AsciiString email );
	AsciiStringList getEmails( void );

private:
	typedef std::map<AsciiString, AsciiString> PassMap;
	typedef std::map<AsciiString, AsciiString> DateMap;
	typedef std::map<AsciiString, AsciiStringList> NickMap;
	PassMap m_emailPasswordMap;
	NickMap m_emailNickMap;
	DateMap m_emailDateMap;
};

static AsciiString obfuscate( AsciiString in )
{
	char *buf = NEW char[in.getLength() + 1];
	strcpy(buf, in.str());
	static const char *xor = "1337Munkee";
	char *c = buf;
	const char *c2 = xor;
	while (*c)
	{
		if (!*c2)
			c2 = xor;
		if (*c != *c2)
			*c = *c++ ^ *c2++;
		else
			c++, c2++;
	}
	AsciiString out = buf;
	delete buf;
	return out;
}

// byte-exact reconstruction: game/GameEngine/Source/Common/GameSpyLoginPreferences_getPasswordForEmail_Thunk.cpp
AsciiString GameSpyLoginPreferences::getPasswordForEmail( AsciiString email )
{
	if ( m_emailPasswordMap.find(email) == m_emailPasswordMap.end() )
		return AsciiString::TheEmptyString;
	return m_emailPasswordMap[email];
}

#pragma inline_depth(0)

#pragma inline_depth()

static const char *PREF_FILENAME = "GameSpyLogin.ini";
static GameSpyLoginPreferences *loginPref = NULL;

static void startPings( void )
{
	std::list<AsciiString> pingServers = TheGameSpyConfig->getPingServers();
	Int timeout = TheGameSpyConfig->getPingTimeoutInMs();
	Int reps = TheGameSpyConfig->getNumPingRepetitions();

	for (std::list<AsciiString>::const_iterator it = pingServers.begin(); it != pingServers.end(); ++it)
	{
		AsciiString pingServer = *it;
		PingRequest req;
		req.hostname = pingServer.str();
		req.repetitions = reps;
		req.timeout = timeout;
		ThePinger->addRequest(req);
	}
}

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
		if (loginPref)
		{
			loginPref->write();
			delete loginPref;
			loginPref = NULL;
		}
		TheShell->push(nextScreen);
	}
	else
	{
		DEBUG_ASSERTCRASH(loginPref != NULL, ("loginPref == NULL"));
		if (loginPref)
		{
			loginPref->write();
			delete loginPref;
			loginPref = NULL;
		}
	}

	nextScreen = NULL;

}  // end if

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
// window ids ------------------------------------------------------------------------------
static NameKeyType parentWOLLoginID =						NAMEKEY_INVALID;
static NameKeyType buttonBackID =								NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonLoginID =							NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonCreateAccountID =			NAMEKEY_INVALID;	// profile, quick
static NameKeyType buttonUseAccountID =					NAMEKEY_INVALID;	// quick
static NameKeyType buttonDontUseAccountID =			NAMEKEY_INVALID;	// profile
static NameKeyType buttonTOSID =								NAMEKEY_INVALID;	// TOS
static NameKeyType parentTOSID =								NAMEKEY_INVALID;	// TOS Parent
static NameKeyType buttonTOSOKID =							NAMEKEY_INVALID;	// TOS
static NameKeyType listboxTOSID =								NAMEKEY_INVALID;	// TOS
static NameKeyType comboBoxEmailID =						NAMEKEY_INVALID;	// profile
static NameKeyType comboBoxLoginNameID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryLoginNameID =				NAMEKEY_INVALID;	// quick
static NameKeyType textEntryPasswordID =				NAMEKEY_INVALID;	// profile
static NameKeyType checkBoxRememberPasswordID =	NAMEKEY_INVALID;	// checkbox to remember information or not
static NameKeyType textEntryMonthID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryDayID =				NAMEKEY_INVALID;	// profile
static NameKeyType textEntryYearID =				NAMEKEY_INVALID;	// profile

// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentWOLLogin =						NULL;
static GameWindow *buttonBack =								NULL;
static GameWindow *buttonLogin =							NULL;
static GameWindow *buttonCreateAccount =			NULL;
static GameWindow *buttonUseAccount =					NULL;
static GameWindow *buttonDontUseAccount =			NULL;
static GameWindow *buttonTOS						=			NULL;
static GameWindow *parentTOS						=			NULL;
static GameWindow *buttonTOSOK					=			NULL;
static GameWindow *listboxTOS						=			NULL;
static GameWindow *comboBoxEmail =						NULL;
static GameWindow *comboBoxLoginName =				NULL;
static GameWindow *textEntryLoginName =				NULL;
static GameWindow *textEntryPassword =				NULL;
static GameWindow *checkBoxRememberPassword =	NULL;
static GameWindow *textEntryMonth =				NULL;
static GameWindow *textEntryDay =				NULL;
static GameWindow *textEntryYear =				NULL;

 // WOLLoginMenuInit

//-------------------------------------------------------------------------------------------------
/** WOL Login Menu shutdown method */
//-------------------------------------------------------------------------------------------------
static Bool loggedInOK = false;
  // WOLLoginMenuShutdown

// this is used to check if we've got all the pings
static void checkLogin( void )
{
	if (loggedInOK && ThePinger && !ThePinger->arePingsInProgress())
	{
		// save off our ping string, and end those threads
		AsciiString pingStr = ThePinger->getPingString( 1000 );
		DEBUG_LOG(("Ping string is %s\n", pingStr.str()));
		TheGameSpyInfo->setPingString(pingStr);
		//delete ThePinger;
		//ThePinger = NULL;

		buttonPushed = true;
		loggedInOK = false; // don't try this again

		loginAttemptTime = 0;

		// start looking for group rooms
		TheGameSpyInfo->clearGroupRoomList();

		SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_LOGIN);
		nextScreen = "Menus/WOLWelcomeMenu.wnd";
		TheShell->pop();
		
		// read in some cached data
		GameSpyMiscPreferences mPref;
		PSPlayerStats localPSStats = GameSpyPSMessageQueueInterface::parsePlayerKVPairs(mPref.getCachedStats().str());
		localPSStats.id = TheGameSpyInfo->getLocalProfileID();
		TheGameSpyInfo->setCachedLocalPlayerStats(localPSStats);
//		TheGameSpyPSMessageQueue->trackPlayerStats(localPSStats);

		// and push the info around to other players
//		PSResponse newResp;
//		newResp.responseType = PSResponse::PSRESPONSE_PLAYERSTATS;
//		newResp.player = localPSStats;
//		TheGameSpyPSMessageQueue->addResponse(newResp);
	}
}

// WOLLoginMenuUpdate

// WOLLoginMenuInput

static Bool isNickOkay(UnicodeString nick)
{
	static const WideChar * legalIRCChars = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]`_^{|}-";

	Int len = nick.getLength();
	if (len == 0)
		return TRUE;

	if (len == 1 && nick.getCharAt(0) == L'-')
		return FALSE;

	WideChar newChar = nick.getCharAt(len-1);
	if (wcschr(legalIRCChars, newChar) == NULL)
		return FALSE;

	return TRUE;
}

static Bool isAgeOkay(AsciiString &month, AsciiString &day, AsciiString year)
{
	if(month.isEmpty() || day.isEmpty() || year.isEmpty() || year.getLength() != 4)
		return FALSE;

	Int monthInt = atoi(month.str());
	Int dayInt = atoi(day.str());

	if(monthInt > 12 || dayInt > 31)
		return FALSE;
		// setup date buffer for local region date format
	month.format("%02.2d",monthInt);
	day.format("%02.2d",dayInt);

	// test the year first
	#define DATE_BUFFER_SIZE 256
	char dateBuffer[ DATE_BUFFER_SIZE ];
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
								 0, NULL,
								 "yyyy",
								 dateBuffer, DATE_BUFFER_SIZE );
	Int sysVal = atoi(dateBuffer);
	Int userVal = atoi(year.str());
	if(sysVal - userVal >= 14)
		return TRUE;
	else if( sysVal - userVal <= 12)
		return FALSE;

	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
								 0, NULL,
								 "MM",
								 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(month.str());
	if(sysVal - userVal >0 )
		return TRUE;
	else if( sysVal -userVal < 0 )
		return FALSE;
//	month.format("%02.2d",userVal);
	GetDateFormat( LOCALE_SYSTEM_DEFAULT,
								 0, NULL,
								 "dd",
								 dateBuffer, DATE_BUFFER_SIZE );
	sysVal = atoi(dateBuffer);
	userVal = atoi(day.str());
	if(sysVal - userVal< 0)
		return FALSE;
//	day.format("%02.2d",userVal);
	return TRUE;
}

// WOLLoginMenuSystem

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?TheEmptyString@AsciiString@@2V1@A=?TheEmptyString@AsciiString@@2V1@B")
