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
// Modified for BFME2: original-binary compiler flags and native entry points.
// platformsdk
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// /EHsc (VC's /GX) lets the extern "C" Win32 imports count as non-throwing.
// Retail initializeAppWindows keeps its title UnicodeString temporary alive
// across CreateWindowExW with no EH frame, which only that setting (or EH off)
// reproduces; the default -EHsc- builds a frame around it.
//
// nextParam is the command-line tokenizer used by the BFME entry point.
// Open-BFME-1's GeneralsMD Code/Main/WinMain.cpp defines the same helper:
// it keeps a static source cursor, treats a run of the first separator as a
// quote-like wrapper, and uses strpbrk for both the opening and closing scan.
// BFME2's caller at 0x00002CFF passes the command-line buffer and the literal
// separator string at 0x00BBB64C.  The retail cursor is at 0x00DDE034 and
// strpbrk is the MSVCR71 import at 0x00BBA6CC.

// The native window helpers use non-strict handle types in their symbols.
#define NO_STRICT
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// trimArgument (0x00001C2E) and its inlined WinMain copy call the
// _mbscpy import thunk at 0x00629176 with E8, not through the IAT.
#undef _CRTIMP
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <new>

char *nextParam(char *newSource, char *seps)
{
    static char *source = 0;
    if (newSource)
    {
        source = newSource;
    }
    if (!source)
    {
        return 0;
    }

    // Find the next token, preserving the first separator as a quote marker.
    char *first = source;
    if (first)
    {
        char *firstSep = strpbrk(first, seps);
        char firstChar[2] = {0, 0};
        if (firstSep == first)
        {
            firstChar[0] = *first;
            while (*first == firstChar[0]) first++;
        }

        char *end;
        if (firstChar[0])
            end = strpbrk(first, firstChar);
        else
            end = strpbrk(first, seps);

        if (end)
        {
            source = end + 1;
            *end = 0;

            if (!*source)
                source = 0;
        }
        else
        {
            source = 0;
        }

        if (first && !*first)
            first = 0;
    }

    return first;
}

//----------------------------------------------------------------------------
// WndProc, the main window procedure, at 0x0000179F.
//
// Zero Hour's Code/Main/WinMain.cpp carries the same body; BFME 2 kept the
// structure and changed the edges.  The retail tells that fix the identity:
// the address is stored into wndClass.lpfnWndProc by initializeAppWindows at
// 0x0000275D, the frame is a __stdcall `ret 0x10`, and every case below lands
// on a Zero Hour case label with the same handler.
//
// What BFME 2 changed:
//   - a Debug gate runs first, and hands the message straight to the default
//     handler when it answers true;
//   - the default handler is chosen at run time by IsWindowUnicode rather than
//     by the A/W build macro;
//   - WM_CLOSE just returns 0 instead of pushing a quit message;
//   - WM_ACTIVATE drops the reference's TheAudio->loseFocus() call;
//   - WM_ACTIVATEAPP notifies two further singletons, and message 0x2707
//     (outside the WM_ range) reaches a handler of its own.
//
// The classes below are TU-scoped models, not headers: each one carries only
// the vtable slots and member offsets this body actually reaches, so that the
// indirect calls land on the retail slot numbers.  Slots whose identity is not
// recovered keep an address- or offset-derived placeholder name rather than an
// invented one.
//----------------------------------------------------------------------------

// The Debug singleton at 0x00DE0880, reached here through vtable slot 0x74 --
// a plain getter for the bool at this+0x9F64.  functions.csv already records
// the same global reaching Command at slot 0x8C.
class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual bool _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c(const char *version, const char *internalVersion,
		const char *buildDate);
	static void SetBuildInfo(const char *version, const char *internalVersion,
		const char *buildDate);
};

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

class IMEManager
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual bool serviceIMEMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT result();
};

IMEManager *TheIMEManager;

class Keyboard
{
public:
	void resetKeys();
};

Keyboard *TheKeyboard;

class Win32Mouse
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void setCursor(int cursor);

	int getMouseCursor() const { return m_currentCursor; }
	void lostFocus(bool state) { m_lostFocus = state; }
	void addWin32Event(UINT msg, WPARAM wParam, LPARAM lParam, DWORD time);

private:
	BYTE m_pad0[0x4FA4 - 4];
	int m_currentCursor;
	BYTE m_pad1[0x6020 - 0x4FA8];
	bool m_lostFocus;
};

Win32Mouse *TheWin32Mouse;

class Mouse
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void setMouseLimits();
};

extern Mouse *TheMouse;  // defined in Mouse.cpp

// Existing five-byte focus forwarder at1DBC0B; this native call encodes
// the forwarder, not the separate AudioManager body at35D2F7.
class Rva001DBAA4
{
public:
	void regainFocus();
};

class GameWindowTransitionsHandler;

// The WM_ACTIVATE singleton at 0x00DFDC14 is TheTransitionHandler, not
// TheAudio (0x00DFE6E8: this body's WM_ACTIVATEAPP focus slots,
// FlammableUpdate/AudioLoopUpgrade sound calls). INI::parseWindowTransitions
// (0x001DC66F) reads this same global and calls getNewGroup on it, and the
// object behind it (ctor 0x001DCBC3, vftable 0x00BDBC30) is the transitions
// handler. The full native focus forwarder at1DBC0B ignores the supplied
// receiver and jumps to the channel-volume restore helper; name the
// actual encoded forwarder rather than giving its address to AudioManager.
GameWindowTransitionsHandler *TheTransitionHandler;

class GameEngine
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void setIsActive(bool active);
};

GameEngine *TheGameEngine;

// The two further singletons WM_ACTIVATEAPP notifies.  Neither identity is
// recovered, so both are named for the retail address of the global.
class BfmeDfe6e8
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
};

// The global at this VA is TheAudio; this name aliases it rather than
// defining a second variable the rest of the game never sees.
extern class AudioManager *TheAudio;

class BfmeDfe6e4
{
public:
	void _M_rva00625476();
	void _M_rva00625699();
};

BfmeDfe6e4 *theBfmeDfe6e4;

class CopyProtect
{
public:
	static void checkForMessage(UINT message, LPARAM lParam);
	static bool isLauncherRunning();
	static bool notifyLauncher();
	static bool validate();
	static void setVerified(bool verified);
	static void shutdown();
};

// Native2CF86 is the existing cdecl no-argument mixer hook. The retail
// message arm still passes its unused WPARAM on the caller-owned stack.
void Rva0002CF86MixerFieldEdit();

void Reset_D3D_Device(bool active);

HWND ApplicationHWnd;
bool ApplicationIsWindowed;
bool isWinMainActive;
bool gInitializing;
bool gDoPaint;
HBITMAP gLoadScreenBitmap;
DWORD TheMessageTime;

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	// Debug takes the window first; when it answers yes the message is not the
	// game's to handle.
	if( theDebug->_M_slot_74() )
		return IsWindowUnicode( hWnd ) ? DefWindowProcW( hWnd, message, wParam, lParam )
		                               : DefWindowProcA( hWnd, message, wParam, lParam );

	// First let the IME manager do it's stuff.
	if( TheIMEManager )
	{
		if( TheIMEManager->serviceIMEMessage( hWnd, message, wParam, lParam ) )
		{
			// The manager intercepted an IME message so return the result
			return TheIMEManager->result();
		}
	}

	// Check for messages from the launcher
	CopyProtect::checkForMessage( message, lParam );

	switch( message )
	{
		//-------------------------------------------------------------------------
		case WM_NCHITTEST:
			// Prevent the user from selecting the menu in fullscreen mode
			if( !ApplicationIsWindowed )
				return HTCLIENT;
			break;

		//-------------------------------------------------------------------------
		case WM_POWERBROADCAST:
			switch( wParam )
			{
				case PBT_APMQUERYSUSPEND:
					return TRUE;

				case PBT_APMRESUMESUSPEND:
					return TRUE;
			}
			break;

		//-------------------------------------------------------------------------
		case WM_SYSCOMMAND:
			// Prevent moving/sizing and power loss in fullscreen mode
			switch( wParam )
			{
				case SC_MOVE:
				case SC_SIZE:
				case SC_MAXIMIZE:
				case SC_KEYMENU:
				case SC_MONITORPOWER:
					if( FALSE == ApplicationIsWindowed )
						return 1;
					break;
			}
			break;

		//-------------------------------------------------------------------------
		case WM_CLOSE:
			return 0;

		//-------------------------------------------------------------------------
		case WM_SETFOCUS:
		{
			//
			// reset the state of our keyboard cause we haven't been paying
			// attention to the keys while focus was away
			//
			if( TheKeyboard )
				TheKeyboard->resetKeys();

			if( TheWin32Mouse )
				TheWin32Mouse->lostFocus( false );

			break;
		}

		//-------------------------------------------------------------------------
		case WM_SIZE:
			// When W3D initializes, it resizes the window.  So stop repainting.
			if( !gInitializing )
				gDoPaint = false;
			break;

		//-------------------------------------------------------------------------
		case WM_KILLFOCUS:
		{
			if( TheKeyboard )
				TheKeyboard->resetKeys();

			if( TheWin32Mouse )
				TheWin32Mouse->lostFocus( true );

			break;
		}

		//-------------------------------------------------------------------------
		case WM_ACTIVATEAPP:
		{
			if( (bool)wParam != isWinMainActive )
			{
				isWinMainActive = (BOOL)wParam;

				if( TheGameEngine )
					TheGameEngine->setIsActive( isWinMainActive );

				Reset_D3D_Device( isWinMainActive );

				if( isWinMainActive )
				{
					//restore mouse cursor to our custom version.
					if( TheWin32Mouse )
						TheWin32Mouse->setCursor( TheWin32Mouse->getMouseCursor() );

					if( ((BfmeDfe6e8 *)TheAudio) )
						((BfmeDfe6e8 *)TheAudio)->_M_slot_4c();

					if( theBfmeDfe6e4 )
						theBfmeDfe6e4->_M_rva00625699();
				}
				else
				{
					if( ((BfmeDfe6e8 *)TheAudio) )
						((BfmeDfe6e8 *)TheAudio)->_M_slot_48();

					if( theBfmeDfe6e4 )
						theBfmeDfe6e4->_M_rva00625476();
				}
			}
			return 0;
		}

		//-------------------------------------------------------------------------
		case WM_ACTIVATE:
		{
			int active = LOWORD( wParam );

			//
			// when window is becoming deactivated we must release mouse cursor
			// locks on our region, otherwise set the mouse limit region again
			// which will clip the cursor to our window
			//
			if( active == WA_INACTIVE )
			{
				ClipCursor( NULL );
			}
			else
			{
				if( TheMouse )
					TheMouse->setMouseLimits();

				if( TheTransitionHandler )
					((Rva001DBAA4 *)TheTransitionHandler)->regainFocus();
			}
			break;
		}

		//-------------------------------------------------------------------------
		case WM_KEYDOWN:
		{
			int key = (int)wParam;

			switch( key )
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					break;
			}

			return 0;
		}

		//-------------------------------------------------------------------------
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:

		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		{
			if( TheWin32Mouse )
				TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

			return 0;
		}

		//-------------------------------------------------------------------------
		case WM_MOUSEWHEEL:
		{
			long x = (long)LOWORD( lParam );
			long y = (long)HIWORD( lParam );
			RECT rect;

			// ignore when outside of client area
			GetWindowRect( ApplicationHWnd, &rect );
			if( x < rect.left || x > rect.right || y < rect.top || y > rect.bottom )
				return 0;

			if( TheWin32Mouse )
				TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

			return 0;
		}

		//-------------------------------------------------------------------------
		case WM_MOUSEMOVE:
		{
			int x = (int)LOWORD( lParam );
			int y = (int)HIWORD( lParam );
			RECT rect;

			// ignore when outside of client area
			GetClientRect( ApplicationHWnd, &rect );
			if( x < rect.left || x > rect.right || y < rect.top || y > rect.bottom )
				return 0;

			if( TheWin32Mouse )
				TheWin32Mouse->addWin32Event( message, wParam, lParam, TheMessageTime );

			return 0;
		}

		//-------------------------------------------------------------------------
		case WM_SETCURSOR:
		{
			if( TheWin32Mouse && (HWND)wParam == ApplicationHWnd )
				TheWin32Mouse->setCursor( TheWin32Mouse->getMouseCursor() );
			return TRUE;	//tell Windows not to reset mouse cursor image to default.
		}

		//-------------------------------------------------------------------------
		case WM_PAINT:
		{
			if( gDoPaint )
			{
				PAINTSTRUCT paint;
				HDC dc = ::BeginPaint( hWnd, &paint );
				if( gLoadScreenBitmap != NULL )
				{
					int savContext = ::SaveDC( dc );
					HDC tmpDC = ::CreateCompatibleDC( dc );
					HBITMAP savBitmap = (HBITMAP)::SelectObject( tmpDC, gLoadScreenBitmap );
					::BitBlt( dc, 0, 0, 800, 600, tmpDC, 0, 0, SRCCOPY );
					::SelectObject( tmpDC, savBitmap );
					::DeleteDC( tmpDC );
					::RestoreDC( dc, savContext );
				}
				::EndPaint( hWnd, &paint );
				return TRUE;
			}
			break;
		}

		//-------------------------------------------------------------------------
		case WM_ERASEBKGND:
		{
			if( !gDoPaint )
				return TRUE;	//we don't need to erase the background because we always draw entire window.
			break;
		}

		//-------------------------------------------------------------------------
		case 0x2707:
			reinterpret_cast<void (__cdecl *)(WPARAM)>(&Rva0002CF86MixerFieldEdit)( wParam );
			break;
	}

	return IsWindowUnicode( hWnd ) ? DefWindowProcW( hWnd, message, wParam, lParam )
	                               : DefWindowProcA( hWnd, message, wParam, lParam );
}

//----------------------------------------------------------------------------
// initializeAppWindows at 0x0000275D.
//
// Zero Hour's body with BFME 2's edges:
//   - the Debug singleton hears whether the game runs windowed before anything
//     else happens;
//   - the icon is lotrbfme.ico through LoadImageA, and the class is registered
//     and the window created through the W entry points, with the class name
//     read from the global at 0x00DA5F10;
//   - the window is centred only while the X/Y globals still hold the -1000000
//     sentinel, and the title is a UnicodeString from the helper at 0x0023484D.
// The style if/else is Zero Hour's own; MSVC folds it into the branchless
// neg/sbb/and/add that retail shows.  WinMain's call at 0x00002FAA is the only
// caller, and it passes hInstance in EDI -- MSVC does that only for a static
// function whose every call it can see.
//----------------------------------------------------------------------------

#define DEFAULT_XRESOLUTION 800
#define DEFAULT_YRESOLUTION 600
#define WINDOW_POS_SENTINEL (-1000000)

void bfmeNotifyDebugWindowed(unsigned runWindowed);

// Only what this body reaches of the engine's reference-counted string:
// str() with its shared empty buffer, and the out-of-line releaseBuffer the
// destructor forwards to.
#include "unicode_string.h"


UnicodeString bfmeGetMainWindowTitle();

HINSTANCE ApplicationHInstance;
const unsigned short *g_windowClassName;
int g_windowPosX;
int g_windowPosY;

static bool initializeAppWindows( HINSTANCE hInstance, int nCmdShow, bool runWindowed )
{
	WNDCLASSW wndClass;
	RECT rect;
	DWORD windowStyle;

	bfmeNotifyDebugWindowed( *(unsigned *)&runWindowed );

	// register the window class
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)LoadImageA( hInstance, "lotrbfme.ico", IMAGE_ICON, 0, 0,
	                                    LR_LOADFROMFILE | LR_DEFAULTSIZE );
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = g_windowClassName;
	RegisterClassW( &wndClass );

	// Create our main window
	windowStyle = WS_POPUP | WS_VISIBLE;
	if( runWindowed )
		windowStyle |= WS_DLGFRAME | WS_CAPTION | WS_SYSMENU;
	else
		windowStyle |= WS_EX_TOPMOST | WS_SYSMENU;

	rect.left = 0;
	rect.top = 0;
	rect.right = DEFAULT_XRESOLUTION;
	rect.bottom = DEFAULT_YRESOLUTION;
	AdjustWindowRect( &rect, windowStyle, FALSE );

	gInitializing = true;

	if( g_windowPosX == WINDOW_POS_SENTINEL )
		g_windowPosX = (GetSystemMetrics( SM_CXSCREEN ) / 2) - 400;
	if( g_windowPosY == WINDOW_POS_SENTINEL )
		g_windowPosY = (GetSystemMetrics( SM_CYSCREEN ) / 2) - 332;

	HWND hWnd = CreateWindowExW( 0,
	                             g_windowClassName,
	                             bfmeGetMainWindowTitle().str(),
	                             windowStyle,
	                             g_windowPosX,
	                             g_windowPosY,
	                             rect.right - rect.left,
	                             rect.bottom - rect.top,
	                             NULL,
	                             NULL,
	                             hInstance,
	                             NULL );

	if( !runWindowed )
		SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
	else
		SetWindowPos( hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );

	SetFocus( hWnd );
	SetForegroundWindow( hWnd );
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	// save our application instance and window handle for future use
	ApplicationHInstance = hInstance;
	ApplicationHWnd = hWnd;
	gInitializing = false;
	if( !runWindowed )
		gDoPaint = false;

	return true;  // success
}

//----------------------------------------------------------------------------
// Debug::SetBuildInfo static forward at 0x00001705 (27B). The Zero Hour
// debug header declares this static next to the virtual of the same name; it
// forwards its three strings to theDebug's virtual slot 0x9C, which the
// WWDebug lane rowed as ?SetBuildInfo@Debug@@UAEXPBD00@Z at 0x00039510.
// WinMain is its only caller. The two neighbouring gap thunklets (0x16F0 and
// 0x16FA) are dead drops with no callers and are not claimed.
//----------------------------------------------------------------------------

// ?SetBuildInfo@Debug@@SAXPBD00@Z @0x1705
void Debug::SetBuildInfo(const char *version, const char *internalVersion,
	const char *buildDate)
{
	theDebug->_M_slot_9c(version, internalVersion, buildDate);
}

//----------------------------------------------------------------------------
// Engine teardown at 0x00225B4A (25B). WinMain calls it once, after GameMain
// returns, to tear down the GameMain-created singleton at TheGameEngine
// (0x00DFE710) and null the global. The body calls vtable slot 0x68, then
// deletes whatever slot 0 hands back for a zero flag. The engine's full
// vtable is unrecovered, so the calls go through a positional view class;
// the cast is free. __fastcall because retail passes the pointer in ecx
// with no stack push. Upgrades the pin of the same name.
//----------------------------------------------------------------------------

struct BfmePostGameItem
{
	unsigned char m_pad[4];
};

class GameEngineTeardownView
{
public:
	virtual BfmePostGameItem *acquirePostGameItem(int flags);
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
};

// ?shutdownGameEngine@@YIXPAVGameEngine@@@Z @0x225b4a
void __fastcall shutdownGameEngine(GameEngine *engine)
{
	GameEngineTeardownView *view = (GameEngineTeardownView *)engine;
	view->_M_slot_68();
	delete view->acquirePostGameItem(0);
}

//----------------------------------------------------------------------------
// GameMain at 0x00237D19 (36B). Zero Hour's GameMain in miniature: create the
// engine, init it with the command line, then tail-run it. BFME 2 moved the
// engine delete out to WinMain, so the run is a bare tail call and WinMain
// pops GameMain's own argument pushes itself. The init virtual is __stdcall
// (callee cleanup, which is why no add esp follows it); execute is a plain
// thiscall tail jump. Only the slots this body reaches are modelled.
//----------------------------------------------------------------------------

class GameEngineInitView
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void init(int argc, char *argv[]);
	virtual void execute();
};

GameEngine *CreateGameEngine();
extern GameEngine *TheGameEngine;

// ?GameMain@@YAXHPAPAD@Z @0x237d19
void GameMain(int argc, char **argv)
{
	GameEngine *engine = CreateGameEngine();
	TheGameEngine = engine;
	((GameEngineInitView *)engine)->init(argc, argv);
	return ((GameEngineInitView *)TheGameEngine)->execute();
}

//----------------------------------------------------------------------------
// WinMain at 0x00002C39 (1382B), with its catch(...) continuation at
// 0x0000319F (matched separately).  Zero Hour's WinMain reshaped for BFME 2:
//   - the command line comes from GetCommandLineW, converted to UTF-8 into a
//     new[] buffer, and argv[0] is the executable token (argc starts at 0);
//   - the working directory is only forced when lotrsec.big is not visible;
//   - a leading 0x96 (en dash) on an argument is rewritten to '-';
//   - -DX resolves each hex address through DebugStackwalk::Signature;
//   - -win/-fullscreen/-xpos/-ypos/-automatch are parsed in a second pass;
//   - the splash is an ATL CImage loaded from <language>Splash.jpg (falling
//     back to .bmp) and published through gLoadScreenBitmap;
//   - the mutex and FindWindow key off the window class name;
//   - the launcher handshake runs before GameMain, and teardown order depends
//     on the TheGlobalData byte at +0xC74.
//----------------------------------------------------------------------------

int BFME2WideToUtf8(const unsigned short *wide, int wideLength, char *utf8, int utf8Size);
void Rva0005D6D0DisableImmTextFrameService();
class WW3D { public: static bool Shutdown(); };

class DebugStackwalk
{
public:
	class Signature
	{
	public:
		static void GetSymbol(unsigned int address, char *buffer, unsigned int bufferSize);
	};
};

// Only the ATL 7.1 atlimage.h members WinMain reaches; the destructor and
// Destroy are inline in the header, as retail shows them expanded here.
struct HBITMAP__;

namespace ATL
{
class CImage
{
	class CInitGDIPlus
	{
	public:
		void DecreaseCImageCount() throw();
	};

public:
	CImage() throw();
	virtual ~CImage() throw()
	{
		Destroy();
		s_initGDIPlus.DecreaseCImageCount();
	}
	void Destroy() throw()
	{
		if (m_hBitmap != 0)
			DeleteObject(Detach());
	}
	HBITMAP__ *Detach() throw();
	long Load(const char *fileName) throw();
	operator HBITMAP() const throw() { return m_hBitmap; }

private:
	HBITMAP m_hBitmap;
	void *m_pBits;
	int m_nWidth;
	int m_nHeight;
	int m_nPitch;
	int m_nBPP;
	bool m_bIsDIBSection;
	bool m_bHasAlphaChannel;
	long m_iTransparentColor;
	HDC m_hDC;
	int m_nDCRefCount;
	HBITMAP m_hOldBitmap;

	static CInitGDIPlus s_initGDIPlus;
};
}

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

AsciiString GetRegistryLanguage();

class Version
{
public:
	Version();
	~Version();
	AsciiString getAsciiVersion();
	AsciiString getAsciiBuildTime();
	AsciiString *getBuildGuid();

private:
	unsigned char m_data[0x30];
};

Version *TheVersion;


// TheGlobalData byte at +0xC74 selects the engine-first teardown below.
class GlobalData
{
public:
	unsigned char m_pad[0xC74];
	bool m_bfmeTeardownEngineFirst;
};

extern class GlobalData *TheWritableGlobalData;

// The two singletons torn down after GameMain; both are released through
// their virtual destructor in slot 0 with a global delete.
class BfmeDfe6ec
{
public:
	virtual ~BfmeDfe6ec();
};

BfmeDfe6ec *theBfmeDfe6ec;

class BfmeDfe6e8Owner
{
public:
	virtual ~BfmeDfe6e8Owner();
};

// Native 0x1C2E..0x1C72 retains a null guard and one common return.
// The real WinMain caller gives this static helper its ESI input convention.
static inline char *trimArgument(char *buffer)
{
	if (buffer)
	{
		char *source = buffer;
		while (*source != 0 && (unsigned char)*source <= ' ')
			source++;
		if (source != buffer)
			_mbscpy((unsigned char *)buffer, (const unsigned char *)source);
		for (int index = strlen(buffer) - 1; index >= 0; index--)
		{
			if (*source != 0 && (unsigned char)buffer[index] <= ' ')
				buffer[index] = 0;
			else
				break;
		}
	}
	return buffer;
}

#define MAX_ARGUMENTS 32

// ?WinMain@@... _WinMain@16 @0x2c39
extern "C" int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	char *lpCmdLine, int nCmdShow )
{
	Rva0005D6D0DisableImmTextFrameService();

	unsigned short *wideCommandLine = GetCommandLineW();
	int commandLineSize = BFME2WideToUtf8(wideCommandLine, -1, 0, 0);
	char *commandLine = new char[commandLineSize];
	BFME2WideToUtf8(wideCommandLine, -1, commandLine, commandLineSize);

	try {

		// Force the working directory to the executable's unless the game
		// archives are already visible from here.
		WIN32_FIND_DATAW findData;
		HANDLE findHandle = FindFirstFileW(L"lotrsec.big", &findData);
		if (findHandle != INVALID_HANDLE_VALUE)
		{
			FindClose(findHandle);
		}
		else
		{
			unsigned short buffer[260];
			GetModuleFileNameW(0, buffer, 260);
			unsigned short *pEnd = buffer + wcslen(buffer);
			while (pEnd != buffer)
			{
				if (*pEnd == '\\')
				{
					*pEnd = 0;
					break;
				}
				pEnd--;
			}
			SetCurrentDirectoryW(buffer);
		}

		int argc = 0;
		char *argv[MAX_ARGUMENTS];
		argv[0] = 0;

		char *token = nextParam(commandLine, "\" ");
		while (argc < MAX_ARGUMENTS && token != 0)
		{
			// Pasted shortcuts can carry an en dash in place of the hyphen.
			if (*token == '\x96')
				*token = '-';
			argv[argc++] = trimArgument(token);
			token = nextParam(0, "\" ");
		}

		if (argc > 2 && strcmp(argv[1], "-DX") == 0)
		{
			for (int i = 2; i < argc; i++)
			{
				unsigned int address = strtoul(argv[i], 0, 16);
				char name[256];
				DebugStackwalk::Signature::GetSymbol(address, name, 256);
			}
			return 0;
		}

		for (int i = 1; i < argc; i++)
		{
			if (_strcmpi(argv[i], "-win") == 0)
			{
				ApplicationIsWindowed = true;
			}
			else if (_strcmpi(argv[i], "-fullscreen") == 0)
			{
				ApplicationIsWindowed = false;
			}
			else if (i + 1 < argc && _strcmpi(argv[i], "-xpos") == 0)
			{
				g_windowPosX = atol(argv[i + 1]);
				i++;
			}
			else if (i + 1 < argc && _strcmpi(argv[i], "-ypos") == 0)
			{
				g_windowPosY = atol(argv[i + 1]);
				i++;
			}
			else if (_strcmpi(argv[i], "-automatch") == 0)
			{
			}
		}

		{
			ATL::CImage splashImage;
			char filePath[260];
			sprintf(filePath, "%sSplash.jpg", GetRegistryLanguage().str());
			if (splashImage.Load(filePath) < 0)
			{
				sprintf(filePath, "%sSplash.bmp", GetRegistryLanguage().str());
				splashImage.Load(filePath);
			}
			gLoadScreenBitmap = splashImage;

			HANDLE gameMutex = CreateMutexW(0, FALSE, g_windowClassName);
			if (GetLastError() == ERROR_ALREADY_EXISTS)
			{
				HWND runningWindow = FindWindowW(g_windowClassName, 0);
				if (runningWindow)
				{
					SetForegroundWindow(runningWindow);
					ShowWindow(runningWindow, SW_RESTORE);
				}
				if (gameMutex != 0)
					CloseHandle(gameMutex);
				delete TheVersion;
				TheVersion = 0;
				return 0;
			}

			if (initializeAppWindows(hInstance, nCmdShow, ApplicationIsWindowed) == false)
				return 0;
		}

		TheVersion = new Version;
		Debug::SetBuildInfo(TheVersion->getAsciiVersion().str(),
			TheVersion->getBuildGuid()->str(),
			TheVersion->getAsciiBuildTime().str());

		if (!CopyProtect::isLauncherRunning())
		{
			delete TheVersion;
			TheVersion = 0;
			return 0;
		}
		if (!CopyProtect::notifyLauncher())
		{
			delete TheVersion;
			TheVersion = 0;
			return 0;
		}

		CopyProtect::setVerified(CopyProtect::validate());
		LoadLibraryA("setupapi.dll");

		GameMain(argc, argv);

		CopyProtect::shutdown();

		delete TheVersion;
		TheVersion = 0;

		if (TheWritableGlobalData->m_bfmeTeardownEngineFirst)
		{
			if (TheGameEngine)
			{
				shutdownGameEngine(TheGameEngine);
				TheGameEngine = 0;
			}
			::delete theBfmeDfe6ec;
		}
		else
		{
			WW3D::Shutdown();
			BfmeDfe6e8Owner *owner = (BfmeDfe6e8Owner *)((BfmeDfe6e8 *)TheAudio);
			if (owner)
			{
				::delete owner;
				(*(BfmeDfe6e8 **)&TheAudio) = 0;
			}
		}
	}
	catch (...)
	{
	}

	return 0;
}
