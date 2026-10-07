// cl: /O1 /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/GUI/GameWindowManager.cpp); this unit had no counterpart under Code/.
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

// FILE: GameWindowManager.cpp ////////////////////////////////////////////////////////////////////
// Created:   Colin Day, June 2001
//						Dean Iverson, March 1998 (Original window code)
// Desc:      The game window manager is the singleton class that we interface
//						with to interact with the game windowing system.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Debug.h"
#include "Common/Language.h"
#include "GameClient/Display.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Mouse.h"
#include "GameClient/DisplayStringManager.h"
#include "Gameclient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTabControl.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/GameWindowTransitions.h"
#include "Common/NameKeyGenerator.h"

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
GameWindowManager *TheWindowManager = NULL;
UnsignedInt WindowLayoutCurrentVersion = 2;

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//
// with this statis set to true, the window system will propogate mouse position
// messages to windows.  You may want to disable this if you feel the mouse position
// messages are "spamming" your window and making a particular debuggin situation
// difficult.  Make sure you do enable this before you check in again tho because
// it is necessary for any code that needs to look at objects or anything under
// the radar cursor
//
static Bool sendMousePosMessages = TRUE;

//-------------------------------------------------------------------------------------------------
/** Process windows waiting to be destroyed */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::processDestroyList: defined in GameWindowManager_processDestroyList.cpp (its row's unit).
  // end processDestroyList

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// BFME's window manager carries winSendSystemMsg at vtable slot 58 (+0xE8);
// the shared Zero Hour header places it earlier.
class BfmeWindowManagerSendView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57();
	virtual WindowMsgHandledType winSendSystemMsg( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
};

//-------------------------------------------------------------------------------------------------
/** Generic function to simply propagate only button press messages to parent and let it deal with it */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType PassSelectedButtonsToParentSystem( GameWindow *window, UnsignedInt msg,
																												WindowMsgData mData1, WindowMsgData mData2 )
{

	// sanity
	if( window == NULL )
		return MSG_IGNORED;

	// BFME renumbered the later gadget messages: retail tests 0x4031 where the
	// shared Zero Hour enum puts GEM_EDIT_DONE at 0x402F, and adds 0x400B.
	if( (msg == GBM_SELECTED)  ||  (msg == GBM_SELECTED_RIGHT) || (msg == GBM_MOUSE_ENTERING) || (msg == GBM_MOUSE_LEAVING) || (msg == 0x4031) || (msg == 0x400B))
	{
		GameWindow *parent = window->winGetParent();

		if( parent )
			return ((BfmeWindowManagerSendView *)TheWindowManager)->winSendSystemMsg( parent, msg, mData1, mData2 );

	}  // end if
	
	return MSG_IGNORED;

}  // end PassSelectedButtonsToParentSystem

//-------------------------------------------------------------------------------------------------
/** Generic function to simply propagate only button press messages to parent and let it deal with it */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType PassMessagesToParentSystem( GameWindow *window, UnsignedInt msg,
																												WindowMsgData mData1, WindowMsgData mData2 )
{

	// sanity
	if( window == NULL )
		return MSG_IGNORED;


	GameWindow *parent = window->winGetParent();

	if( parent )
		return TheWindowManager->winSendSystemMsg( parent, msg, mData1, mData2 );
	
	return MSG_IGNORED;

}  // end PassSelectedButtonsToParentSystem


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::GameWindowManager present-unmatched
GameWindowManager::GameWindowManager( void )
{

	m_windowList = NULL;			// list of all top level windows
	m_windowTail = NULL;			// last in windowList

	m_destroyList = NULL;			// list of windows to destroy

	m_currMouseRgn = NULL;		// window that mouse is over
	m_mouseCaptor = NULL;			// window that captured mouse
	m_keyboardFocus = NULL;		// window that has input focus
	m_modalHead = NULL;			// top of windows in the modal stack
	m_grabWindow = NULL;			// window that grabbed the last down event
	m_loneWindow = NULL;		// Set if we just opened a combo box

	m_cursorBitmap = NULL;
	m_captureFlags = 0;

}  // end GameWindowManger

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::~GameWindowManager present-unmatched
GameWindowManager::~GameWindowManager( void )
{

	// destroy all windows
	winDestroyAll();
	freeStaticStrings();
	if(TheTransitionHandler)
		delete TheTransitionHandler;
	TheTransitionHandler = NULL;
}  // end ~GameWindowManager

//-------------------------------------------------------------------------------------------------
/** Initialize the game window manager system */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::init is defined with its retail-matched body in Code/GameEngine/Source/GameClient/GUI/GameWindowManager_init.cpp (0x002C0A0F).

//-------------------------------------------------------------------------------------------------
/** Reset window system */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::reset: defined in GameWindowManagerModal.cpp (its row's unit).
  // end reset

//-------------------------------------------------------------------------------------------------
/** Update cycle for game widnow manager */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::update: defined in GameWindowManagerModal.cpp (its row's unit).
  // end update

//-------------------------------------------------------------------------------------------------
/** Puts a window at the head of the window list */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::linkWindow: defined in GameWindowManager_linkWindow.cpp (its row's unit).
  // end linkWindow

//-------------------------------------------------------------------------------------------------
/** Insert the window ahead of the the 'aheadOf' window.  'aheadOf' can
	* be a window in the master list or a child of any window in that master
	* list */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::insertWindowAheadOf present-unmatched
void GameWindowManager::insertWindowAheadOf( GameWindow *window, 
																						 GameWindow *aheadOf )
{
	
	// sanity
	if( window == NULL )
		return;

	// we'll say that an aheadOf window means at the head of the list
	if( aheadOf == NULL )	
	{

		linkWindow( window );
		return;

	}  // end if

	// get parent of aheadOf
	GameWindow *aheadOfParent = aheadOf->winGetParent();

	//
	// if ahead of has no parent insert it in the master list just before
	// ahead of
	//
	if( aheadOfParent == NULL )
	{

		window->m_prev = aheadOf->m_prev;

		if( aheadOf->m_prev )
			aheadOf->m_prev->m_next = window;
		else
			m_windowList = window;

		aheadOf->m_prev = window;
		window->m_next = aheadOf;

	}  // end if
	else
	{

		window->m_prev = aheadOf->m_prev;

		if( aheadOf->m_prev )
			aheadOf->m_prev->m_next = window;
		else
			aheadOfParent->m_child = window;

		aheadOf->m_prev = window;
		window->m_next = aheadOf;

		window->m_parent = aheadOfParent;

	}  // end else

}  // end insertWindowAheadOf

//-------------------------------------------------------------------------------------------------
/** Takes a window off the window list */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::unlinkWindow: defined in GameWindowManager_linkWindow.cpp (its row's unit).
  // end unlinkWindow

//-------------------------------------------------------------------------------------------------
/** Takes a child window off its parent's window list */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::unlinkChildWindow: defined in GameWindowManager_linkWindow.cpp (its row's unit).
  // end unlinkChildWindow

//-------------------------------------------------------------------------------------------------
/** Check window and parents to see if this window is enabled */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::isEnabled is defined in GameWindowManagerParentLinks.cpp.


//-------------------------------------------------------------------------------------------------
/** Check window and parents to see if this window is hidden */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::isHidden is defined in GameWindowManagerParentLinks.cpp.


//-------------------------------------------------------------------------------------------------
// Adds a child window to its parent.
//-------------------------------------------------------------------------------------------------
// GameWindowManager::addWindowToParent is defined in GameWindowManagerParentLinks.cpp.


//-------------------------------------------------------------------------------------------------
/** Add a child window to the parent, put place it at the end of the 
	* parent window child list */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::addWindowToParentAtEnd: defined in GameWindowManager_enableWindowsInRange.cpp (its row's unit).
  // end addWindowToParentAtEnd

//-------------------------------------------------------------------------------------------------
/** this gets called from winHide() when a window hides itself */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::windowHiding: defined in GameWindowManagerModal.cpp (its row's unit).
  // end windowHiding

//-------------------------------------------------------------------------------------------------
/** Hide all windows in a certain range of id's (inclusive) */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::hideWindowsInRange: defined in GameWindowManager_enableWindowsInRange.cpp (its row's unit).
  // end hideWindowsInRange

//-------------------------------------------------------------------------------------------------
// Enable all windows in a certain range of id's (inclusive)
//-------------------------------------------------------------------------------------------------
// GameWindowManager::enableWindowsInRange: defined in GameWindowManager_enableWindowsInRange.cpp (its row's unit).
  // end enableWindowsInRange

//-------------------------------------------------------------------------------------------------
/** Captures the mouse capture. */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winCapture: defined in GameWindowManagerModal.cpp (its row's unit).
  // end WinCapture

//-------------------------------------------------------------------------------------------------
/** Releases the mouse capture. */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winRelease: defined in GameWindowManagerModal.cpp (its row's unit).
  // end WinRelease

//-------------------------------------------------------------------------------------------------
/** Returns the current mouse captor. */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winGetCapture present-unmatched
GameWindow *GameWindowManager::winGetCapture( void )
{

	return m_mouseCaptor;

}  // end WinGetCapture

//-------------------------------------------------------------------------------------------------
/** Gets the window pointer from its id */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winGetWindowFromId: defined in GameWindowManager_enableWindowsInRange.cpp (its row's unit).
  // end WinGetWindowFromId

//-------------------------------------------------------------------------------------------------
/** Gets the Window List Pointer */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winGetWindowList present-unmatched
GameWindow *GameWindowManager::winGetWindowList( void )
{

	return m_windowList;

}  // end winGetWindowList

//-------------------------------------------------------------------------------------------------
/** Send a system message to the specified window */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winSendSystemMsg / winSendInputMsg: BFME 2 sends through
// GameWindow members instead of the m_system / m_input callbacks; the matched
// bodies live in GameWindowManagerSendMsg.cpp.

//-------------------------------------------------------------------------------------------------
/** Get the current input focus */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winGetFocus present-unmatched
GameWindow *GameWindowManager::winGetFocus( void )
{

	return m_keyboardFocus;

}  // end WinGetFocus

//-------------------------------------------------------------------------------------------------
/** Set the current input focus */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winSetFocus: defined in GameWindowManager_winSetFocus.cpp (its row's unit).
  // end WinSetFocus

//-------------------------------------------------------------------------------------------------
/** Process key press through the GUI. */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winProcessKey present-unmatched
WinInputReturnCode GameWindowManager::winProcessKey( UnsignedByte key, 
																										 UnsignedByte state )
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;

	// Check for keyboard focus and a legal key for sanity
	if( m_keyboardFocus && (key != KEY_NONE) )
	{
		GameWindow *win = m_keyboardFocus;
			
		returnCode = WIN_INPUT_USED;  // assume input will be used

		//
		// Pass the keystroke up the window hierarchy until it is
		// processed or we reach the top level window
		//
		while( winSendInputMsg( win, GWM_CHAR, key, state ) == MSG_IGNORED )
		{

			win = win->winGetParent();
			if( win == NULL )
			{

				returnCode = WIN_INPUT_NOT_USED;  // oops, it wasn't used after all
				break;

			}  // end if

		}  // end while

	}  // end if

	return returnCode;

}  // end winProcessKey

//-------------------------------------------------------------------------------------------------
/** Process a single mouse event through the window system */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winProcessMouseEvent present-unmatched
WinInputReturnCode GameWindowManager::winProcessMouseEvent( GameWindowMessage msg,
																														ICoord2D *mousePos,
																														void *data )
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	Bool objectTooltip = FALSE;
	UnsignedInt packedMouseCoords;
	GameWindow *window = NULL;
	GameWindow *toolTipWindow = NULL;
	GameWindow *childWindow;
	Int dx, dy;
	Bool clearGrabWindow = FALSE;

	// pack mouse coords into one entity for message passing
	packedMouseCoords = SHORTTOLONG( mousePos->x, mousePos->y );

	// clear tooltip ... it will be reset if necessary
	TheMouse->setCursorTooltip( UnicodeString::TheEmptyString );

	// Check for mouse capture
	if( m_mouseCaptor )
	{

		// no window grabbed as of yet
		m_grabWindow = NULL;

		// what what window within the captured window are we in
		window = m_mouseCaptor->winPointInChild( mousePos->x, mousePos->y );

		//
		// send buttons, drags, wheels to the windows, we don't continually
		// send mouse positions
		//
		if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
		{
			GameWindow *win = window;

			if( win )
			{
				while( win != NULL )
				{

					if( winSendInputMsg( win, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					{

						// if used clear the event
						returnCode = WIN_INPUT_USED;
						break;

					}

					// if we just tested mouseCaptor don't go any higher in the chain
					if( win == m_mouseCaptor )
						break;

					win = win->winGetParent();

				}  // end while

			}  // end if
			else
			{

				// if used clear the event
				if(	winSendInputMsg( m_mouseCaptor, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					returnCode = WIN_INPUT_USED;

			}  // end else

		}  // end if

	}  // end if, mouse captor window present
	else
	{

		if( m_grabWindow )
		{
			GameWindow *parent;

			switch( msg )
			{

				// --------------------------------------------------------------------
				case GWM_LEFT_UP:
				{
					//Play a beep sound if the window is disabled.
					m_grabWindow->winPointInChild( mousePos->x, mousePos->y, FALSE, TRUE );

					BitClear( m_grabWindow->m_status, WIN_STATUS_ACTIVE );
					if( m_grabWindow->winPointInWindow( mousePos->x, mousePos->y ) )
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					else if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ))
					{
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					}

					clearGrabWindow = TRUE;
					break;

				}  // end left up

				// --------------------------------------------------------------------
				case MOUSE_EVENT_NONE:
				case GWM_LEFT_DRAG:
				{

					if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ) )
					{
						ICoord2D *mouseDelta = (ICoord2D *)data;
						dx = mouseDelta->x;
						dy = mouseDelta->y;

						// Clip window to parent
						if( m_grabWindow->winGetParent() )
						{

							parent = m_grabWindow->winGetParent();

							if( m_grabWindow->m_region.lo.x + dx < 0 )
								dx = 0 - m_grabWindow->m_region.lo.x;
							else if( m_grabWindow->m_region.hi.x + dx > parent->m_size.x )
								dx = parent->m_size.x - m_grabWindow->m_region.hi.x;

							if( m_grabWindow->m_region.lo.y + dy < 0 )
								dy = 0 - m_grabWindow->m_region.lo.y;
							else if( m_grabWindow->m_region.hi.y + dy > parent->m_size.y )
								dy = parent->m_size.y - m_grabWindow->m_region.hi.y;
						}

						// Move the window, but keep it completely visible within screen boundaries
						IRegion2D newRegion;
						ICoord2D grabSize;

						m_grabWindow->winGetPosition( &newRegion.lo.x, &newRegion.lo.y );
						m_grabWindow->winGetSize( &grabSize.x, &grabSize.y );

						newRegion.lo.x += dx;
						newRegion.lo.y += dy;
						if( newRegion.lo.x < 0 )
							newRegion.lo.x = 0;
						if( newRegion.lo.y < 0 )
							newRegion.lo.y = 0;
						
						newRegion.hi.x = newRegion.lo.x + grabSize.x;
						newRegion.hi.y = newRegion.lo.y + grabSize.y;
						if( newRegion.hi.x > (Int)TheDisplay->getWidth() )
							newRegion.hi.x = (Int)TheDisplay->getWidth();
						if( newRegion.hi.y > (Int)TheDisplay->getHeight() )
							newRegion.hi.y = (Int)TheDisplay->getHeight();
						
						newRegion.lo.x = newRegion.hi.x - grabSize.x;
						newRegion.lo.y = newRegion.hi.y - grabSize.y;

						m_grabWindow->winSetPosition( newRegion.lo.x, newRegion.lo.y );

					}  // end if, draggable window

					// Send mouse drag message
					winSendInputMsg( m_grabWindow, msg, packedMouseCoords, 0 );
					break;

				}  // end mouse event none or left drag

			}  // end switch

			// mark event handled
			returnCode = WIN_INPUT_USED;

		}  // end if, m_grabWindow
		else
		{

			if( m_modalHead && m_modalHead->window )
			{
				window = m_modalHead->window->winPointInChild( mousePos->x, mousePos->y );
			}
			else
			{
			
				/**@todo Colin, there are 3 cases here that are nearly identical code,
				break them up into functions with parameters */

				// search for top-level window which contains pointer
				for( window = m_windowList; window; window = window->m_next )
				{

					if( BitTest( window->m_status, WIN_STATUS_ABOVE ) &&
							!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
							mousePos->x >= window->m_region.lo.x &&
							mousePos->x <= window->m_region.hi.x &&
							mousePos->y >= window->m_region.lo.y &&
							mousePos->y <= window->m_region.hi.y)
					{

						childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
						if( toolTipWindow == NULL )
						{
							if( childWindow->m_tooltip || 
									childWindow->m_instData.getTooltipTextLength() )
							{
								toolTipWindow = childWindow;
							}
						}
						if( BitTest( window->m_status, WIN_STATUS_ENABLED ) )
						{
							// determine which child window the mouse is in
							window = window->winPointInChild( mousePos->x, mousePos->y );
							break;  // exit for
						}
						
					}  // end if

				}  // end for window

				// check !above, below and hidden
				if( window == NULL )
				{

					for( window = m_windowList; window; window = window->m_next )
					{

						if( !BitTest( window->m_status, WIN_STATUS_ABOVE | 
																						WIN_STATUS_BELOW | 
																						WIN_STATUS_HIDDEN ) &&
								mousePos->x >= window->m_region.lo.x &&
								mousePos->x <= window->m_region.hi.x &&
								mousePos->y >= window->m_region.lo.y &&
								mousePos->y <= window->m_region.hi.y)
						{

							childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
							if( toolTipWindow == NULL )
							{
								if( childWindow->m_tooltip || 
										childWindow->m_instData.getTooltipTextLength() )
								{
									toolTipWindow = childWindow;
								}
							}
							if( BitTest( window->m_status, WIN_STATUS_ENABLED ))
							{								
								// determine which child window the mouse is in
								window = window->winPointInChild( mousePos->x, mousePos->y );
								break;  // exit for
							}
						}
					}
				}  // end if, window == NULL

				// check below and !hidden
				if( window == NULL )
				{

					for( window = m_windowList; window; window = window->m_next )
					{

						if( BitTest( window->m_status, WIN_STATUS_BELOW ) &&
								!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
								mousePos->x >= window->m_region.lo.x &&
								mousePos->x <= window->m_region.hi.x &&
								mousePos->y >= window->m_region.lo.y &&
								mousePos->y <= window->m_region.hi.y)
						{

							childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
							if( toolTipWindow == NULL )
							{
								if( childWindow->m_tooltip || 
										childWindow->m_instData.getTooltipTextLength() )
								{
									toolTipWindow = childWindow;
								}
							}
							if( BitTest( window->m_status, WIN_STATUS_ENABLED ))
							{
								// determine which child window the mouse is in
								window = window->winPointInChild( mousePos->x, mousePos->y );
								break;  // exit for
							}
						}
					}
				}  // end if

			}  // end else, no modal head

			if( window )
				if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ) )
				{
					if(window->winGetParent() && BitTest( window->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
						window = window->winGetParent();
					else
						window = NULL;
				}

			if( window )
			{
				GameWindow *tempWin;

				//
				// only send messages for button states, wheel states, we do not
				// continually send messages for mouse positions
				//
				if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
				{

					tempWin = window;
	
					// Give everyone a chance to do something with the clicks
					GameWindow *oldLoneWindow = m_loneWindow;
					while( winSendInputMsg( tempWin, msg, packedMouseCoords, 0 ) == MSG_IGNORED )
					{

						tempWin = tempWin->m_parent;
						if( tempWin == NULL )
							break;

					}  // end while

						
					// First check to see if m_loneWindow is set if so, close the window
					if( m_loneWindow && m_loneWindow == oldLoneWindow 
					&&( msg == GWM_LEFT_UP || msg == GWM_MIDDLE_UP || msg == GWM_RIGHT_UP || tempWin))
					{
						if(!m_loneWindow->winIsChild(tempWin))
							winSetLoneWindow( NULL );
						/*
								ComboBoxData *cData = (ComboBoxData *)m_comboBoxOpen->winGetUserData();
															// verify that the window that ate the message wasn't one of our own
															if(cData->dropDownButton != tempWin &&
																cData->editBox != tempWin &&
																cData->listBox != tempWin &&
																cData->listboxData->upButton != tempWin &&
																cData->listboxData->downButton != tempWin &&
																cData->listboxData->slider != tempWin &&
																cData->listboxData->slider != tempWin->winGetParent())
																	winSetOpenComboBoxWindow( NULL );*/
								
					}
					if( tempWin )
					{
					
						//
						// Someone cares, if this is a left button down event
						// it should get "grabbed"
						/// @todo should allow for left handed mouse configs here?
						//
						if( msg == GWM_LEFT_DOWN )
						{

//						if( tempWin != windowList ) 
//							WinActivate( tempWin );
							m_grabWindow = tempWin;

						}  // end if

						// event is used
						returnCode = WIN_INPUT_USED;

					}  // end if, tempWin

				}  // end if

			}  // end if( window ) 

			if( toolTipWindow == NULL )
			{

				if( isHidden( window ) == FALSE )
					toolTipWindow = window;

			}  // end if

			// if tooltips are on set them into the window
			Bool tooltipsOn = TRUE;
			if( tooltipsOn )
			{
//				if( toolTipWindow && toolTipWindow->winGetParent() && BitTest( toolTipWindow->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
//					toolTipWindow = toolTipWindow->winGetParent();
				if( toolTipWindow )
				{
					// do we have a callback to call for the tooltip
					if( toolTipWindow->m_tooltip )
						toolTipWindow->m_tooltip( toolTipWindow, 
																			&toolTipWindow->m_instData, 
																			packedMouseCoords );

					// else, do we have a normal tooltip to set
					else if( toolTipWindow->m_instData.getTooltipTextLength() )
						TheMouse->setCursorTooltip( toolTipWindow->m_instData.getTooltipText(), toolTipWindow->m_instData.m_tooltipDelay );

				}  // end if
				else
				{

					//
					// not pointing at a window... perhaps we are pointing at a valid
					// tooltip-able object in the game world ... let's set a flag so 
					// during the object testing we can set the tooltip, we can do
					// whatever we like now that we know no other tooltip was set from
					// a window
					//
					objectTooltip = TRUE;

				}  // end else

			}  // end if

		}  // end if grabWindow not present

	}  // end else (mouseCaptor) 

	//
	// check if new current window is different from the last
	// but only if both windows fall within the mouseCaptor if one exists
	//
	if( (m_grabWindow == NULL) && (window != m_currMouseRgn) )
	{
		if( m_mouseCaptor )
		{
			if( m_mouseCaptor->winIsChild( m_currMouseRgn ) )
				winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );
		}
		else if( m_currMouseRgn )
			winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );

		if( window )
			winSendInputMsg( window, GWM_MOUSE_ENTERING, packedMouseCoords, 0 );

		m_currMouseRgn = window;

	}  // end if

	// clear grabWindow if necessary
	if( clearGrabWindow == TRUE )
	{

		m_grabWindow = NULL;
		clearGrabWindow = FALSE;

	}  // end if

	return returnCode;

}  // end winProcessMouseEvent

//-------------------------------------------------------------------------------------------------
/** Draw a window and its children, in parent-first order.
	* Children's coordinates are relative to their parents.
	* Note that hidden windows automatically will not draw any
	* of their children ... but see-thru windows only will not 
	* draw themselves, but will give their children an
	* opportunity to draw */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::drawWindow: defined in GameWindowManager_drawWindow_Thunk.cpp (its row's unit).
  // end drawWindow

//-------------------------------------------------------------------------------------------------
/** Draw the GUI in reverse order to correlate with clicking priority */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winRepaint present-unmatched
void GameWindowManager::winRepaint( void )
{
	GameWindow *window, *next;

	// draw below windows
	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;

		if( BitTest( window->m_status, WIN_STATUS_BELOW ) )
			drawWindow( window );
	}

	// draw non-above and non-below windows
	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;

		if (BitTest( window->m_status, WIN_STATUS_ABOVE | 
																	 WIN_STATUS_BELOW ) == FALSE)
			drawWindow( window );
	}

	// draw above windows
	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;

		if( BitTest( window->m_status, WIN_STATUS_ABOVE ) )
			drawWindow( window );
	}

	if(TheTransitionHandler)
		TheTransitionHandler->draw();
}  // end WinRepaint

//-------------------------------------------------------------------------------------------------
/** Dump information about all the windows for resource problems */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::dumpWindow: defined in GameWindowManager_dumpWindow.cpp (its row's unit).
  // end dumpWindow

//-------------------------------------------------------------------------------------------------
/** Create a new window by setting up its parameters and callbacks. */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winCreate present-unmatched
GameWindow *GameWindowManager::winCreate( GameWindow *parent, 
																				  UnsignedInt status, 
																				  Int x, Int y,
																				  Int width, Int height,
																					GameWinSystemFunc system,
																					WinInstanceData *instData )
{
	GameWindow *window;

	// allocate new window
	window = allocateNewWindow();
	if( window == NULL )
	{

		DEBUG_LOG(( "WinCreate error: Could not allocate new window\n" ));
#ifndef FINAL
		{
			GameWindow *win;

			for( win = m_windowList; win; win = win->m_next )
				dumpWindow( win );
		}
#endif

		return NULL;

	}  // endif

	// If this is a child window add it to the parent's window list
	if( parent )
		addWindowToParent( window, parent );
	else
		linkWindow( window );

	window->m_status = status;
	window->m_size.x = width;
	window->m_size.y = height;

	window->m_region.lo.x = x;
	window->m_region.lo.y = y;
	window->m_region.hi.x = x + width;
	window->m_region.hi.y = y + height;

	window->normalizeWindowRegion();

	// set the system function and send a create message to window
	window->winSetSystemFunc( system );
	winSendSystemMsg( window, GWM_CREATE, 0, 0 );

	// copy over instance data if present
	if( instData )
		window->winSetInstanceData( instData );

	// set default font
	if (TheGlobalLanguageData && TheGlobalLanguageData->m_defaultWindowFont.name.isNotEmpty())
	{		window->winSetFont( winFindFont(
			TheGlobalLanguageData->m_defaultWindowFont.name,
			TheGlobalLanguageData->m_defaultWindowFont.size,
			TheGlobalLanguageData->m_defaultWindowFont.bold) );
	}
	else
		window->winSetFont( winFindFont( AsciiString("Times New Roman"), 14, FALSE ) );

	return window;

}  // end WinCreate

//-------------------------------------------------------------------------------------------------
/** Take a window and its children off the top level list and free
	* their allocation class data. */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winDestroy: defined in GameWindowManagerModal.cpp (its row's unit).
  // winDestroy

//-------------------------------------------------------------------------------------------------
/** Destroy all windows on the window list IMMEDIATELY */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winDestroyAll: defined in GameWindowManager_winDestroyAll.cpp (its row's unit).
  // end WinDestroyAll

//-------------------------------------------------------------------------------------------------
/** Sets selected window into a modal state.  This window will get
	* put at the top of a modal stack */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winSetModal: defined in GameWindowManagerModal.cpp (its row's unit).
  // end WinSetModal

//-------------------------------------------------------------------------------------------------
/** pops window off of the modal stack.  If this window is not the top
	* of the modal stack an error will occur. */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winUnsetModal: defined in GameWindowManagerModal.cpp (its row's unit).
  // end WinUnsetModal

//-------------------------------------------------------------------------------------------------
/** Get the grabbed window */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winGetGrabWindow present-unmatched
GameWindow *GameWindowManager::winGetGrabWindow( void )
{

	return m_grabWindow;

}  // end WinGetGrabWindow

//-------------------------------------------------------------------------------------------------
/** Explicitly set the grab window */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::winSetGrabWindow present-unmatched
void GameWindowManager::winSetGrabWindow( GameWindow *window )
{

	m_grabWindow = window;

}  // end winSetGrabWindow

//-------------------------------------------------------------------------------------------------
/** Explicitly set the grab window */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winSetLoneWindow: defined in GameWindowManager_winSetLoneWindow.cpp (its row's unit).
  // end winSetGrabWindow

//-------------------------------------------------------------------------------------------------
/** Create a Modal Message Box */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::gogoMessageBox is defined with its retail-matched body in Code/GameEngine/Source/GameClient/GUI/GameWindowManager_gogoMessageBox.cpp (0x002C187D).

// The 12-argument implementation is in GameWindowManagerMessageBox.cpp.

//-------------------------------------------------------------------------------------------------
/** Create a button GUI control */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetPushButton present-unmatched
GameWindow *GameWindowManager::gogoGadgetPushButton( GameWindow *parent,
																										 UnsignedInt status,
																										 Int x, Int y,
																										 Int width, Int height,
																										 WinInstanceData *instData,
																										 GameFont *defaultFont,
																										 Bool defaultVisual )
{
	GameWindow *button;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_PUSH_BUTTON ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create button gadget, instance data not button type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the button window
	button = TheWindowManager->winCreate( parent, status, 
																				x, y, width, height, 
																				GadgetPushButtonSystem,
																				instData );
	if( button == NULL )
	{
	
		DEBUG_LOG(( "Unable to create button for push button gadget\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// assign input function
	button->winSetInputFunc( GadgetPushButtonInput );

	//
	// assign draw function, the draw functions must actually be implemented
	// on the device level of the engine
	//
	if( BitTest( button->winGetStatus(), WIN_STATUS_IMAGE ) )
		button->winSetDrawFunc( getPushButtonImageDrawFunc() );
	else
		button->winSetDrawFunc( getPushButtonDrawFunc() );

	// set the owner to the parent, or if no parent it will be itself
	button->winSetOwner( parent );
	
	// Init the userdata to NULL
	button->winSetUserData(NULL);

	// assign the default images/colors
	assignDefaultGadgetLook( button, defaultFont, defaultVisual );

	// assign text from label
	UnicodeString text = winTextLabelToText( instData->m_textLabelString );
	if( text.getLength() )
		GadgetButtonSetText( button, text );
	
	return button;

}  // end gogoGadgetPushButton

//-------------------------------------------------------------------------------------------------
/** Create a checkbox UI element */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetCheckbox present-unmatched
GameWindow *GameWindowManager::gogoGadgetCheckbox( GameWindow *parent, 
																									 UnsignedInt status,
																									 Int x, Int y, 
																									 Int width, Int height, 
																									 WinInstanceData *instData,
																									 GameFont *defaultFont,
																									 Bool defaultVisual )

{
	GameWindow *checkbox;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_CHECK_BOX ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create checkbox gadget, instance data not checkbox type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the button window
	checkbox = TheWindowManager->winCreate( parent, status, 
																					x, y, width, height, 
																					GadgetCheckBoxSystem,
																					instData );
	if( checkbox == NULL )
	{
	
		DEBUG_LOG(( "Unable to create checkbox window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// assign input function
	checkbox->winSetInputFunc( GadgetCheckBoxInput );

	//
	// assign draw function, the draw functions must actually be implemented
	// on the device level of the engine
	//
	if( BitTest( checkbox->winGetStatus(), WIN_STATUS_IMAGE ) )
		checkbox->winSetDrawFunc( getCheckBoxImageDrawFunc() );
	else
		checkbox->winSetDrawFunc( getCheckBoxDrawFunc() );

	// set the owner to the parent, or if no parent it will be itself
	checkbox->winSetOwner( parent );

	// assign the default images/colors
	assignDefaultGadgetLook( checkbox, defaultFont, defaultVisual );

	// assign text from label
	UnicodeString text = winTextLabelToText( instData->m_textLabelString );
	if( text.getLength() )
		GadgetCheckBoxSetText( checkbox, text );

	return checkbox;

}  // end gogoGadgetCheckbox

//-------------------------------------------------------------------------------------------------
/** Create a radio button GUI element */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetRadioButton present-unmatched
GameWindow *GameWindowManager::gogoGadgetRadioButton( GameWindow *parent, 
																										  UnsignedInt status,
																										  Int x, Int y, 
																										  Int width, Int height, 
																										  WinInstanceData *instData,
																											RadioButtonData *rData,
																										  GameFont *defaultFont,
																										  Bool defaultVisual )

{
	GameWindow *radioButton;
	RadioButtonData *radioData;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_RADIO_BUTTON ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create radioButton gadget, instance data not radioButton type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the button window
	radioButton = TheWindowManager->winCreate( parent, status, 
																					   x, y, width, height, 
																						 GadgetRadioButtonSystem,
																						 instData );
	if( radioButton == NULL )
	{
	
		DEBUG_LOG(( "Unable to create radio button window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// allocate and store the radio button user data
	radioData = NEW RadioButtonData;
	memcpy( radioData, rData, sizeof( RadioButtonData ) );
	radioButton->winSetUserData( radioData );

	// assign input function
	radioButton->winSetInputFunc( GadgetRadioButtonInput );

	//
	// assign draw function, the draw functions must actually be implemented
	// on the device level of the engine
	//
	if( BitTest( radioButton->winGetStatus(), WIN_STATUS_IMAGE ) )
		radioButton->winSetDrawFunc( getRadioButtonImageDrawFunc() );
	else
		radioButton->winSetDrawFunc( getRadioButtonDrawFunc() );

	// set the owner to the parent, or if no parent it will be itself
	radioButton->winSetOwner( parent );

	// assign the default images/colors
	assignDefaultGadgetLook( radioButton, defaultFont, defaultVisual );

	// assign text from label
	UnicodeString text = winTextLabelToText( instData->m_textLabelString );
	if( text.getLength() )
		GadgetRadioSetText( radioButton, text );

	return radioButton;

}  // end gogoGadgetRadioButton

//-------------------------------------------------------------------------------------------------
/** Create a tab control GUI element */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetTabControl present-unmatched
GameWindow *GameWindowManager::gogoGadgetTabControl( GameWindow *parent, 
																										  UnsignedInt status,
																										  Int x, Int y, 
																										  Int width, Int height, 
																										  WinInstanceData *instData,
																											TabControlData *tData,
																										  GameFont *defaultFont,
																										  Bool defaultVisual )

{
	GameWindow *tabControl;
	TabControlData *tabData;

	// we MUST have a tab control style window to do this
	if( BitTest( instData->getStyle(), GWS_TAB_CONTROL ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create tabControl gadget, instance data not tabControl type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the tab control window
	tabControl = TheWindowManager->winCreate( parent, status, 
																					   x, y, width, height, 
																						 GadgetTabControlSystem,
																						 instData );
	if( tabControl == NULL )
	{
	
		DEBUG_LOG(( "Unable to create tab control window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// allocate and store the tab control user data
	tabData = NEW TabControlData;
	memcpy( tabData, tData, sizeof( TabControlData ) );
	tabControl->winSetUserData( tabData );

	GadgetTabControlComputeTabRegion( tabControl );
	GadgetTabControlCreateSubPanes( tabControl );
	GadgetTabControlShowSubPane( tabControl, 0 );

	// assign input function
	tabControl->winSetInputFunc( GadgetTabControlInput );

	//
	// assign draw function, the draw functions must actually be implemented
	// on the device level of the engine
	//
	if( BitTest( tabControl->winGetStatus(), WIN_STATUS_IMAGE ) )
		tabControl->winSetDrawFunc( getTabControlImageDrawFunc() );
	else
		tabControl->winSetDrawFunc( getTabControlDrawFunc() );

	// set the owner to the parent, or if no parent it will be itself
	tabControl->winSetOwner( parent );

	// assign the default images/colors
	assignDefaultGadgetLook( tabControl, defaultFont, defaultVisual );

	return tabControl;

}  // end gogoGadgetTabControl

//-------------------------------------------------------------------------------------------------
/** Create a list box GUI control */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetListBox present-unmatched
GameWindow *GameWindowManager::gogoGadgetListBox( GameWindow *parent, 
																									UnsignedInt status,
										                              Int x, Int y, 
																									Int width, Int height,
																									WinInstanceData *instData, 
																									ListboxData *listboxDataTemplate,
																								  GameFont *defaultFont,
																								  Bool defaultVisual )

{
  GameWindow *listbox;
  ListboxData *listboxData;
	Bool title = FALSE;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_SCROLL_LISTBOX ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create listbox gadget, instance data not listbox type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the listbox
  listbox = winCreate( parent, status, x, y, width, height, 
											 GadgetListBoxSystem, instData );
	
	if( listbox == NULL )
	{

		DEBUG_LOG(( "Unable to create listbox window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// allocate the listbox data, copy template data over and set it into box
	listboxData = NEW ListboxData;
	DEBUG_ASSERTCRASH(listboxDataTemplate, ("listboxDataTemplate not initialized"));
	memcpy( listboxData, listboxDataTemplate, sizeof( ListboxData ) );

  // Add the list box data struct to the window's class data
  listbox->winSetUserData( listboxData );

	// set the owner to the parent, or if no parent it will be itself
	listbox->winSetOwner( parent );

	// Adjust for list title if present
	if( instData->getTextLength() )
		title = TRUE;

	// Set up list box redraw callbacks
	if( BitTest( listbox->winGetStatus(), WIN_STATUS_IMAGE ))
		listbox->winSetDrawFunc( getListBoxImageDrawFunc() );
	else
		listbox->winSetDrawFunc( getListBoxDrawFunc() );

	// Set up list box input callbacks
	if( listboxData->multiSelect )
		listbox->winSetInputFunc( GadgetListBoxMultiInput );
	else
		listbox->winSetInputFunc( GadgetListBoxInput );


	
	//
	// allocate and set the list length, note that setting the list length will
	// automatically allocate the selection entries that are needed for multi
	// select list boxes etc.
	//
	Int length = listboxData->listLength;
	listboxData->listLength = 0;  // hacky!
	GadgetListBoxSetListLength( listbox, length );

	// store display height
	listboxData->displayHeight = height;

	if( title )
		listboxData->displayHeight -= winFontHeight( instData->getFont() );

  // Set display position to the top of the list
  listboxData->displayPos = 0;
  listboxData->selectPos = -1;
	listboxData->doubleClickTime = 0;
  listboxData->insertPos = 0;
  listboxData->endPos = 0;
	listboxData->totalHeight = 0;

	// if this listbox has multiple selections prep it
	//if( listboxData->multiSelect )
	//	GadgetListBoxAddMultiSelect( listbox );

	// If ScrollBar was requested ... create it.
	if( listboxData->scrollBar )
		GadgetListboxCreateScrollbar( listbox );
	//
	// Setup listbox Columns
	//
	if( listboxData->columns == 1 )
	{
		listboxData->columnWidth = NEW Int;
		listboxData->columnWidth[0] = width;
		if( listboxData->slider )
		{
			ICoord2D sliderSize;

			listboxData->slider->winGetSize( &sliderSize.x, &sliderSize.y );
			listboxData->columnWidth[0] -= (sliderSize.x + 2);

		}  // end if
	}// if
	else
	{
		if( !listboxData->columnWidthPercentage )
			return NULL;
		listboxData->columnWidth = NEW Int[listboxData->columns];
		if(!listboxData->columnWidth)
			return NULL;

		Int totalWidth = width;
		if( listboxData->slider )
		{
			ICoord2D sliderSize;

			listboxData->slider->winGetSize( &sliderSize.x, &sliderSize.y );
			totalWidth -= (sliderSize.x + 2);

		}  // end if
		for(Int i = 0; i < listboxData->columns; i++ )
		{
			listboxData->columnWidth[i] = listboxData->columnWidthPercentage[i] * totalWidth / 100;
		}// for
	}// else
	// assign the default images/colors
	assignDefaultGadgetLook( listbox, defaultFont, defaultVisual );

  return listbox;

}  // end gogoGadgetListBox

//-------------------------------------------------------------------------------------------------
/** Does all generic window creation, calls appropriate slider create
	* function to set up slider-specific data */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetSlider present-unmatched
GameWindow *GameWindowManager::gogoGadgetSlider( GameWindow *parent, 
																								 UnsignedInt status,
																								 Int x, Int y, 
																								 Int width, Int height,
																								 WinInstanceData *instData, 
																								 SliderData *sliderData,
																								 GameFont *defaultFont,
																								 Bool defaultVisual )

{
	GameWindow *slider;
	GameWindow *button;
	SliderData *data;

	//
	// All sliders need to have the tab stop status in order for
	// the focus chain to work correctly.
	//
	BitSet( status, WIN_STATUS_TAB_STOP );

	if( BitTest( instData->getStyle(), GWS_HORZ_SLIDER ) ) 
	{

		slider = winCreate( parent, status, x, y, width, height, 
												GadgetHorizontalSliderSystem, instData );

		// Set up horizontal slider callbacks
		slider->winSetInputFunc( GadgetHorizontalSliderInput );
		if( BitTest( slider->winGetStatus(), WIN_STATUS_IMAGE ) )
			slider->winSetDrawFunc( getHorizontalSliderImageDrawFunc() );
		else
			slider->winSetDrawFunc( getHorizontalSliderDrawFunc() );

	}  // end if
	else if ( BitTest( instData->getStyle(), GWS_VERT_SLIDER ) ) 
	{

		slider = winCreate( parent, status, x, y, width, height, 
												GadgetVerticalSliderSystem, instData );

		// Set up vertical slider callbacks
		slider->winSetInputFunc( GadgetVerticalSliderInput );
		
		if( BitTest( slider->winGetStatus(), WIN_STATUS_IMAGE ) && !(parent && BitTest(parent->winGetStyle(), GWS_SCROLL_LISTBOX)))
			slider->winSetDrawFunc( getVerticalSliderImageDrawFunc() );
		else
			slider->winSetDrawFunc( getVerticalSliderDrawFunc() );

	}  // end else if
	else 
	{

		DEBUG_LOG(( "gogoGadgetSlider warning: unrecognized slider style.\n" ));
		assert( 0 );
		return NULL;
		
	}  // end else

	// sanity
	if( slider == NULL )
	{

		DEBUG_LOG(( "Unable to create slider control window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// set the owner to the parent, or if no parent it will be itself
	slider->winSetOwner( parent );

	// create the slider thumb button
	WinInstanceData buttonInstData;
	UnsignedInt statusFlags = status | WIN_STATUS_ENABLED | WIN_STATUS_DRAGABLE;

	buttonInstData.init();

	// if parent is hidden we don't need to be.
	BitClear( statusFlags, WIN_STATUS_HIDDEN );

	buttonInstData.m_owner = slider;
	buttonInstData.m_style = GWS_PUSH_BUTTON;

	// if slider tracks, so will this sub control
	if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
		BitSet( buttonInstData.m_style, GWS_MOUSE_TRACK );

	if( BitTest( instData->getStyle(), GWS_HORZ_SLIDER ) )
		button = gogoGadgetPushButton( slider, statusFlags, 0, HORIZONTAL_SLIDER_THUMB_POSITION,
											 						 HORIZONTAL_SLIDER_THUMB_WIDTH, HORIZONTAL_SLIDER_THUMB_HEIGHT, &buttonInstData, NULL, TRUE );
	else
		button = gogoGadgetPushButton( slider, statusFlags, 0, 0,
																	 width, width+1, &buttonInstData, NULL, TRUE );

	// Protect against divide by zero
	if( sliderData->maxVal == sliderData->minVal )
		sliderData->maxVal = sliderData->minVal + 1;

	if( BitTest( instData->getStyle(), GWS_HORZ_SLIDER ) ) 
	{
		sliderData->numTicks = (float)(width - HORIZONTAL_SLIDER_THUMB_WIDTH) /
													 (float)(sliderData->maxVal - sliderData->minVal);
	} else 
	{
		sliderData->numTicks = (float)(height - GADGET_SIZE) /
													 (float)(sliderData->maxVal - sliderData->minVal);
	}

	data = NEW SliderData;
	memcpy( data, sliderData, sizeof(SliderData) );

	// Add the slider data struct to the window's class data
	slider->winSetUserData( data );

	// assign the default images/colors
	assignDefaultGadgetLook( slider, defaultFont, defaultVisual );

	return slider;

}  // end gogoGadgetSlider

//-------------------------------------------------------------------------------------------------
/** Create a Combo Box GUI element */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetComboBox present-unmatched
GameWindow *GameWindowManager::gogoGadgetComboBox( GameWindow *parent, 
																									UnsignedInt status,
										                              Int x, Int y, 
																									Int width, Int height,
																									WinInstanceData *instData, 
																									ComboBoxData *comboBoxDataTemplate,
																								  GameFont *defaultFont,
																								  Bool defaultVisual )
{
  GameWindow *comboBox;
  ComboBoxData *comboBoxData;
	Bool title = FALSE;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_COMBO_BOX) == FALSE )
	{

		DEBUG_LOG(( "Cann't create ComboBox gadget, instance data not ComboBox type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the listbox
  comboBox = winCreate( parent, status, x, y, width, height, 
											 GadgetComboBoxSystem, instData );
	
	if( comboBox == NULL )
	{

		DEBUG_LOG(( "Unable to create ComboBox window\n" ));
		assert( 0 );
		return NULL;

	}  // end if


// begin here
	// allocate the listbox data, copy template data over and set it into box
	comboBoxData = NEW ComboBoxData;
	memcpy( comboBoxData, comboBoxDataTemplate, sizeof( ComboBoxData ) );

  // Add the list box data struct to the window's class data
  comboBox->winSetUserData( comboBoxData );

	// set the owner to the parent, or if no parent it will be itself
	comboBox->winSetOwner( parent );

	// Adjust for list title if present
	if( instData->getTextLength() )
		title = TRUE;

	// Set up list box redraw callbacks
	if( BitTest( comboBox->winGetStatus(), WIN_STATUS_IMAGE ))
		comboBox->winSetDrawFunc( getComboBoxImageDrawFunc() );
	else
		comboBox->winSetDrawFunc( getComboBoxDrawFunc() );

	// Set up list box input callbacks
	comboBox->winSetInputFunc( GadgetComboBoxInput );

	//Create the windows that make up 


	WinInstanceData winInstData;
	Int buttonWidth, buttonHeight;
	Int fontHeight;
	Int top;
	Int bottom;


	// do we have a title
	if( comboBox->winGetTextLength() )
		title = TRUE;

	// remove unwanted status bits.
	status &= ~(WIN_STATUS_BORDER | WIN_STATUS_HIDDEN);

	fontHeight = TheWindowManager->winFontHeight( comboBox->winGetFont() );
	top = title ? (fontHeight + 1):0;
	bottom = title ? (height - (fontHeight + 1)):height;

	// intialize instData
	winInstData.init();

	// size of button
	buttonWidth = 21;
	buttonHeight = 22;

	// ----------------------------------------------------------------------
	// Create Drop Down Button
	// ----------------------------------------------------------------------

	winInstData.m_owner = comboBox;
	winInstData.m_style = GWS_PUSH_BUTTON;

	// if listbox tracks, so will this sub control
	if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	
	comboBoxData->dropDownButton =
		 TheWindowManager->gogoGadgetPushButton( comboBox,
																						 status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED,
																						 width - buttonWidth, 0,
																						 buttonWidth, height,
																						 &winInstData, NULL, TRUE );
	comboBoxData->dropDownButton->winSetTooltipFunc(comboBox->winGetTooltipFunc());
	comboBoxData->dropDownButton->winSetTooltip(instData->getTooltipText());
	comboBoxData->dropDownButton->setTooltipDelay(comboBox->getTooltipDelay());
	// ----------------------------------------------------------------------
	// Create text entry
	// ----------------------------------------------------------------------
	UnsignedInt statusTextEntry;
	winInstData.init();
	
	winInstData.m_owner = comboBox;
  winInstData.m_style |= GWS_ENTRY_FIELD;
	winInstData.m_textLabelString = "Entry";
	if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	if( comboBoxData->isEditable)
	{
		statusTextEntry = status;
	}
	else
	{
		statusTextEntry = status | WIN_STATUS_NO_INPUT ;//| WIN_STATUS_NO_FOCUS;
		comboBoxData->entryData->drawTextFromStart = TRUE;
	}
  comboBoxData->editBox = TheWindowManager->gogoGadgetTextEntry( comboBox, statusTextEntry ,
																										 0,0 , 
																										width - buttonWidth , height ,
																										&winInstData, comboBoxData->entryData, 
																										winInstData.m_font, FALSE );
	comboBoxData->editBox->winSetTooltipFunc(comboBox->winGetTooltipFunc());
	comboBoxData->editBox->winSetTooltip(instData->getTooltipText());
	comboBoxData->editBox->setTooltipDelay(comboBox->getTooltipDelay());

	delete (comboBoxData->entryData);
	comboBoxData->entryData = (EntryData *)comboBoxData->editBox->winGetUserData();
	// ----------------------------------------------------------------------
	// Create list box
	// ----------------------------------------------------------------------
	winInstData.init();
	
	winInstData.m_owner = comboBox;
  if( BitTest( comboBox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	BitSet( winInstData.m_style, WIN_STATUS_HIDDEN );
  winInstData.m_style |= GWS_SCROLL_LISTBOX; 
	status &= ~(WIN_STATUS_IMAGE);
  comboBoxData->listBox = TheWindowManager->gogoGadgetListBox( comboBox, status | WIN_STATUS_ABOVE | WIN_STATUS_ONE_LINE, 0, height, 
																								width, height,
																								&winInstData, comboBoxData->listboxData, 
																								winInstData.m_font, FALSE );
	comboBoxData->listBox->winHide(TRUE);
	delete(comboBoxData->listboxData);
	comboBoxData->listboxData = (ListboxData *)comboBoxData->listBox->winGetUserData();

	comboBoxData->listBox->winSetTooltipFunc(comboBox->winGetTooltipFunc());
	comboBoxData->listBox->winSetTooltip(instData->getTooltipText());
	comboBoxData->listBox->setTooltipDelay(comboBox->getTooltipDelay());
	GadgetListBoxSetAudioFeedback(comboBoxData->listBox, TRUE);

	// Initialize the ComboBox's variables and the controls with them
	GadgetComboBoxSetIsEditable(comboBox, comboBoxData->isEditable);
	GadgetComboBoxSetMaxChars( comboBox, comboBoxData->maxChars );
	GadgetComboBoxSetMaxDisplay( comboBox, comboBoxData->maxDisplay );

	//Initialize the control's text colors
	Color color, border;

	color = comboBox->winGetEnabledTextColor();
	border = comboBox->winGetEnabledTextBorderColor();
	if(comboBoxData->listBox)
		comboBoxData->listBox->winSetEnabledTextColors( color,border);
	if(comboBoxData->editBox)
		comboBoxData->editBox->winSetEnabledTextColors(color,border);

	color = comboBox->winGetDisabledTextColor();
	border = comboBox->winGetDisabledTextBorderColor();
	if(comboBoxData->listBox)
		comboBoxData->listBox->winSetDisabledTextColors( color,border);
	if(comboBoxData->editBox)
		comboBoxData->editBox->winSetDisabledTextColors(color,border);


	color = comboBox->winGetHiliteTextColor();
	border = comboBox->winGetHiliteTextBorderColor();
	if(comboBoxData->listBox)
		comboBoxData->listBox->winSetHiliteTextColors( color,border);
	if(comboBoxData->editBox)
		comboBoxData->editBox->winSetHiliteTextColors(color,border);

	comboBoxData->dontHide = FALSE;

	// assign the default images/colors
	assignDefaultGadgetLook( comboBox, defaultFont, defaultVisual );

  return comboBox;

}

//-------------------------------------------------------------------------------------------------
/** Create a progress bar GUI element */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetProgressBar present-unmatched
GameWindow *GameWindowManager::gogoGadgetProgressBar( GameWindow *parent, 
																										  UnsignedInt status,
																										  Int x, Int y, 
																										  Int width, Int height, 
																										  WinInstanceData *instData,
																										  GameFont *defaultFont,
																										  Bool defaultVisual )

{
	GameWindow *progressBar;

	// we MUST have a push button style window to do this
	if( BitTest( instData->getStyle(), GWS_PROGRESS_BAR ) == FALSE )
	{

		DEBUG_LOG(( "Cann't create progressBar gadget, instance data not progressBar type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the button window
	progressBar = TheWindowManager->winCreate( parent, status, 
																					   x, y, width, height, 
																						 GadgetProgressBarSystem,
																						 instData );
	if( progressBar == NULL )
	{

		DEBUG_LOG(( "Unable to create progress bar control\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	//
	// assign draw function, the draw functions must actually be implemented
	// on the device level of the engine
	//
	if( BitTest( progressBar->winGetStatus(), WIN_STATUS_IMAGE ) )
		progressBar->winSetDrawFunc( getProgressBarImageDrawFunc() );
	else
		progressBar->winSetDrawFunc( getProgressBarDrawFunc() );

	// set the owner to the parent, or if no parent it will be itself
	progressBar->winSetOwner( parent );

	// assign the default images/colors
	assignDefaultGadgetLook( progressBar, defaultFont, defaultVisual );

	return progressBar;

}  // end gogoGadgetProgressBar

//-------------------------------------------------------------------------------------------------
/** Does all generic window creation, calls appropriate text field create
	* function to set up specific data */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetStaticText present-unmatched
GameWindow *GameWindowManager::gogoGadgetStaticText( GameWindow *parent, 
																										 UnsignedInt status,
																										 Int x, Int y, 
																										 Int width, Int height,
																										 WinInstanceData *instData, 
																										 TextData *textData,
																										 GameFont *defaultFont,
																										 Bool defaultVisual )

{
  GameWindow *textWin;
  TextData *data;

	// Static Text can not be a Tab Stop
	BitClear( instData->m_style, GWS_TAB_STOP );

  if( BitTest( instData->getStyle(), GWS_STATIC_TEXT ) ) 
	{
    textWin = winCreate( parent, status, x, y, width, height, 
												 GadgetStaticTextSystem, instData );
  } 
	else 
	{
    DEBUG_LOG(( "gogoGadgetText warning: unrecognized text style.\n" ));
    return NULL;
  }
  
  if( textWin != NULL )
	{

		// set the owner to the parent, or if no parent it will be itself
		textWin->winSetOwner( parent );

		// assign callbacks
		textWin->winSetInputFunc( GadgetStaticTextInput );
		if( BitTest( textWin->winGetStatus(), WIN_STATUS_IMAGE ) )
			textWin->winSetDrawFunc( getStaticTextImageDrawFunc() );
		else
			textWin->winSetDrawFunc( getStaticTextDrawFunc() );

    data = NEW TextData;
		assert( textData != NULL );
    memcpy( data, textData, sizeof(TextData) );

		// allocate a display string for the tet
		data->text = TheDisplayStringManager->newDisplayString();
		// set whether or not we center the wrapped text
		data->text->setWordWrapCentered( BitTest( instData->getStatus(), WIN_STATUS_WRAP_CENTERED ));
    // Add the entry field data struct to the window's class data
    textWin->winSetUserData( data );

		// assign the default images/colors
		assignDefaultGadgetLook( textWin, defaultFont, defaultVisual );

		// assign text from label
		UnicodeString text = winTextLabelToText( instData->m_textLabelString );
		if( text.getLength() )
			GadgetStaticTextSetText( textWin, text );

  }  // end if

  return textWin;

}  // end gogoGadetStaticText

//-------------------------------------------------------------------------------------------------
/** Does all generic window creation, calls appropriate entry field create
	* function to set up specific data */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::gogoGadgetTextEntry present-unmatched
GameWindow *GameWindowManager::gogoGadgetTextEntry( GameWindow *parent, 
																										UnsignedInt status,
																										Int x, Int y, 
																										Int width, Int height,
																										WinInstanceData *instData, 
																										EntryData *entryData,
																										GameFont *defaultFont,
																										Bool defaultVisual )

{
	GameWindow *entry;
	EntryData *data;

	if( BitTest( instData->getStyle(), GWS_ENTRY_FIELD ) == FALSE )
	{

		DEBUG_LOG(( "Unable to create text entry, style not entry type\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// create the window
	entry = winCreate( parent, status, x, y, width, height, 
										 GadgetTextEntrySystem, instData );
	if( entry == NULL )
	{

		DEBUG_LOG(( "Unable to create text entry window\n" ));
		assert( 0 );
		return NULL;

	}  // end if

	// set owner of this control
	entry->winSetOwner( parent );

	// assign callbacks
	entry->winSetInputFunc( GadgetTextEntryInput );
	if( BitTest( entry->winGetStatus(), WIN_STATUS_IMAGE ) )
		entry->winSetDrawFunc( getTextEntryImageDrawFunc() );
	else
		entry->winSetDrawFunc( getTextEntryDrawFunc() );

	// zero entry data
//	memset( entryData->text, 0, ENTRY_TEXT_LEN );
//	memset( entryData->constructText, 0, ENTRY_TEXT_LEN );

	// initialize character positions, legths etc
	if( entryData->text )
		entryData->charPos = entryData->text->getTextLength();
	else
		entryData->charPos = 0;
	entryData->conCharPos = 0;
	entryData->receivedUnichar = FALSE;
	if( entryData->maxTextLen >= ENTRY_TEXT_LEN )
		entryData->maxTextLen = ENTRY_TEXT_LEN;

	// allocate entry data
	data = NEW EntryData;

	// copy over data control
	memcpy( data, entryData, sizeof(EntryData) );

	// allocate new text display string
	data->text = TheDisplayStringManager->newDisplayString();
	data->sText = TheDisplayStringManager->newDisplayString();
	data->constructText = TheDisplayStringManager->newDisplayString();

	// set the max for the text lengths
//	data->text->allocateFixed( ENTRY_TEXT_LEN );
//	data->sText->allocateFixed( ENTRY_TEXT_LEN );

	// do any real display string copies
	if( entryData->text )
		data->text->setText( entryData->text->getText() );
	if( entryData->sText )
		data->sText->setText( entryData->sText->getText() );

	// set data into window
	entry->winSetUserData( data );

	// asian languages get to have list box kanji character completion
	data->constructList = NULL;
	if( OurLanguage == LANGUAGE_ID_KOREAN || 
			OurLanguage == LANGUAGE_ID_JAPANESE )
	{
		// we need to create the construct listbox
		WinInstanceData boxInstData;
		ListboxData lData;

			// intialize instData
		boxInstData.init();

		// define display region
		memset( &lData, 0, sizeof(ListboxData) );
		lData.listLength = 128;
		lData.autoScroll = FALSE;
		lData.scrollIfAtEnd = FALSE;
		lData.autoPurge = TRUE;
		lData.scrollBar = TRUE;
		lData.multiSelect = FALSE;
		lData.columns = 1;
		lData.columnWidth = NULL;

		boxInstData.m_style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;

		data->constructList = gogoGadgetListBox( NULL, 
																						 WIN_STATUS_ABOVE | 
																						 WIN_STATUS_HIDDEN |
																						 WIN_STATUS_NO_FOCUS | 
																						 WIN_STATUS_ONE_LINE,
																						 0, height, 
																						 110, 119, 
																						 &boxInstData, 
																						 &lData, 
																						 NULL, 
																						 TRUE );

		if( data->constructList == NULL )
		{

			DEBUG_LOG(( "gogoGadgetEntry warning: Failed to create listbox.\n" ));
			assert( 0 );
			winDestroy( entry );
			return NULL;

		}  // end if

	}  // end, korean or japanese

	// assign the default images/colors
	assignDefaultGadgetLook( entry, defaultFont, defaultVisual );

	// assign text from label
	UnicodeString text = winTextLabelToText( instData->m_textLabelString );
	if( text.getLength() )
		GadgetTextEntrySetText( entry, text );

	return entry;

}  // end gogoGadgetTextEntry

//-------------------------------------------------------------------------------------------------
/** Use this method to assign the default images/colors to gadgets as 
	* they area created */
//-------------------------------------------------------------------------------------------------
// assignDefaultGadgetLook is recovered in GameWindowManagerAssignDefaultGadgetLook.cpp.


//-------------------------------------------------------------------------------------------------
/** Given a text label, retreive the real localized text associated
	* with that label */
//-------------------------------------------------------------------------------------------------
// GameWindowManager::winTextLabelToText: defined in GameWindowManager_winTextLabelToText.cpp (its row's unit).
  // end winTextLabelToText

//-------------------------------------------------------------------------------------------------
/** find the top window at the given coordinates */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::getWindowUnderCursor present-unmatched
GameWindow *GameWindowManager::getWindowUnderCursor( Int x, Int y, Bool ignoreEnabled )
{
	if( m_mouseCaptor )
	{
		// in what what window within the captured window are we?
		return m_mouseCaptor->winPointInChild( x, y, ignoreEnabled );
	}

	if( m_grabWindow )
	{
		// in what what window within the grabbed window are we?
		return m_grabWindow->winPointInChild( x, y, ignoreEnabled );
	}

	GameWindow *window = NULL;
	if( m_modalHead && m_modalHead->window )
	{
		return m_modalHead->window->winPointInChild( x, y, ignoreEnabled );
	}
	else
	{
		// search for top-level window which contains pointer
		for( window = m_windowList; window; window = window->m_next )
		{

			if( BitTest( window->m_status, WIN_STATUS_ABOVE ) &&
					!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
					x >= window->m_region.lo.x &&
					x <= window->m_region.hi.x &&
					y >= window->m_region.lo.y &&
					y <= window->m_region.hi.y)
			{
				if( BitTest( window->m_status, WIN_STATUS_ENABLED ) || ignoreEnabled )
				{
					// determine which child window the mouse is in
					window = window->winPointInChild( x, y, ignoreEnabled );
					break;  // exit for
				}
			}  // end if
		}  // end for window

		// check !above, below and hidden
		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( !BitTest( window->m_status, WIN_STATUS_ABOVE | 
																				WIN_STATUS_BELOW | 
																				WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y)
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED )|| ignoreEnabled)
					{								
						// determine which child window the mouse is in
						window = window->winPointInChild( x, y, ignoreEnabled );
						break;  // exit for
					}
				}
			}
		}  // end if, window == NULL

		// check below and !hidden
		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( BitTest( window->m_status, WIN_STATUS_BELOW ) &&
						!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y)
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED )|| ignoreEnabled)
					{
						// determine which child window the mouse is in
						window = window->winPointInChild( x, y, ignoreEnabled );
						break;  // exit for
					}
				}
			}
		}  // end if
	}  // end else, no modal head

	if( window )
	{
		if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ))
		{
			// this window does not accept input, discard
			window = NULL;
		}
		else if( ignoreEnabled && !( BitTest( window->m_status, WIN_STATUS_ENABLED ) ))
		{
			window = NULL;
		}
	}

	return window;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static WindowMsgHandledType testGrab( GameWindow *window, UnsignedInt msg,
											WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg )
	{

		case GWM_LEFT_DOWN:  return MSG_HANDLED;  // use it

	}

	return MSG_IGNORED;

}

//-------------------------------------------------------------------------------------------------
/** Just for testing */
//-------------------------------------------------------------------------------------------------
// ?GameWindowManager::initTestGUI present-unmatched
Bool GameWindowManager::initTestGUI( void )
{

//	winCreateFromScript( "_ATest.wnd" );
	return TRUE;

//	UnsignedByte alpha = 200;
	GameWindow *window;
	UnsignedInt statusFlags = WIN_STATUS_ENABLED | WIN_STATUS_DRAGABLE | WIN_STATUS_IMAGE;
	WinInstanceData instData;

	// make some windows inside each other in the upper left
	window = TheWindowManager->winCreate( NULL, statusFlags, 0, 0, 100, 100, NULL, NULL );
	window->winSetInputFunc( testGrab );
	window->winSetEnabledColor( 0, TheWindowManager->winMakeColor( 255, 254, 255, 255 ) );
	window->winSetEnabledBorderColor( 0 , TheWindowManager->winMakeColor( 0, 0, 0, 255 ) );
	window = TheWindowManager->winCreate( window, statusFlags, 10, 10, 50, 50, NULL, NULL );
	window->winSetInputFunc( testGrab );
	window->winSetEnabledColor( 0, TheWindowManager->winMakeColor( 128, 128, 128, 255 ) );
	window->winSetEnabledBorderColor( 0 , TheWindowManager->winMakeColor( 0, 0, 0, 255 ) );

	// make a push button
	instData.init();
	BitSet( instData.m_style, GWS_PUSH_BUTTON | GWS_MOUSE_TRACK );
	instData.m_textLabelString = "What Up?";
	window = TheWindowManager->gogoGadgetPushButton( NULL, 
																									 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE, 
																									 200, 100, 
																									 100, 30, 
																									 &instData, NULL, TRUE );

	// make a push button
	instData.init();
	BitSet( instData.m_style, GWS_PUSH_BUTTON | GWS_MOUSE_TRACK );
	instData.m_textLabelString = "Enabled";
	window = TheWindowManager->gogoGadgetPushButton( NULL, 
																									 WIN_STATUS_ENABLED, 
																									 330, 100, 
																									 100, 30, 
																									 &instData, NULL, TRUE );

	// make a push button
	instData.init();
	BitSet( instData.m_style, GWS_PUSH_BUTTON | GWS_MOUSE_TRACK );
	instData.m_textLabelString = "Disabled";
	window = TheWindowManager->gogoGadgetPushButton( NULL, 
																									 0, 
																									 450, 100, 
																									 100, 30, 
																									 &instData, NULL, TRUE );

	// make a check box
	instData.init();
	instData.m_style = GWS_CHECK_BOX | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Check";
	window = TheWindowManager->gogoGadgetCheckbox( NULL,
																								 WIN_STATUS_ENABLED | 
																								 WIN_STATUS_IMAGE,
																								 200, 150,
																								 100, 30,
																								 &instData, NULL, TRUE );

	// make a check box
	instData.init();
	instData.m_style = GWS_CHECK_BOX | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Check";
	window = TheWindowManager->gogoGadgetCheckbox( NULL,
																								 WIN_STATUS_ENABLED,
																								 330, 150,
																								 100, 30,
																								 &instData, NULL, TRUE );

	// make window to hold radio buttons
	window = TheWindowManager->winCreate( NULL, WIN_STATUS_ENABLED | WIN_STATUS_DRAGABLE,
																				200, 200, 250, 45, NULL );
	window->winSetInputFunc( testGrab );
	window->winSetEnabledColor( 0, TheWindowManager->winMakeColor( 50, 50, 50, 200 ) );
	window->winSetEnabledBorderColor( 0, TheWindowManager->winMakeColor( 254, 254, 254, 255 ) );

	// make a radio button
	GameWindow *radio;
	RadioButtonData rData;
	instData.init();
	instData.m_style = GWS_RADIO_BUTTON | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Mama Said!";
	rData.group = 1;
	radio = TheWindowManager->gogoGadgetRadioButton( window,
																									 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																									 10, 10,
																									 100, 30,
																									 &instData,
																									 &rData, NULL, TRUE );

	// make a radio button
	instData.init();
	instData.m_style = GWS_RADIO_BUTTON | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "On the Run";
	radio = TheWindowManager->gogoGadgetRadioButton( window,
																									 WIN_STATUS_ENABLED,
																									 130, 10,
																									 100, 30,
																									 &instData,
																									 &rData, NULL, TRUE );
	GadgetRadioSetEnabledColor( radio, GameMakeColor( 0, 0, 255, 255 ) );
	GadgetRadioSetEnabledBorderColor( radio, GameMakeColor( 0, 0, 255, 255 ) );

	// make a listbox
	ListboxData listData;
	memset( &listData, 0, sizeof( ListboxData ) );
	listData.listLength = 8;
	listData.autoScroll = 1;
	listData.scrollIfAtEnd = FALSE;
	listData.autoPurge = 1;
	listData.scrollBar = 1;
	listData.multiSelect = 1;
	listData.forceSelect = 0;
	listData.columns = 1;
	listData.columnWidth = NULL;
	instData.init();
	instData.m_style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetListBox( NULL,
																								WIN_STATUS_ENABLED,
																								200, 250,
																								100, 100,
																								&instData,
																								&listData, NULL, TRUE );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Listbox text"), 
												 TheWindowManager->winMakeColor( 255, 255, 255, 255 ), -1, 0 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"More text"), 
												 TheWindowManager->winMakeColor( 105, 105, 255, 255 ), -1, 0 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Nothing"), 
												 TheWindowManager->winMakeColor( 105, 105, 255, 255 ), -1, 0 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Seasons"), 
												 TheWindowManager->winMakeColor( 105, 205, 255, 255 ), -1, 0 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Misery"), 
												 TheWindowManager->winMakeColor( 235, 105, 255, 255 ), -1, 0 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Natural"), 
												 TheWindowManager->winMakeColor( 105, 205, 45, 255 ), -1, 0 );
	window->winSetFont( TheFontLibrary->getFont( AsciiString("Times New Roman"), 12, FALSE ) );

	// make a listbox
	memset( &listData, 0, sizeof( ListboxData ) );
	listData.listLength = 8;
	listData.autoScroll = 1;
	listData.scrollIfAtEnd = FALSE;
	listData.autoPurge = 1;
	listData.scrollBar = 1;
	listData.multiSelect = 0;
	listData.forceSelect = 0;
	listData.columns = 1;
	listData.columnWidth = NULL;
	instData.init();
	instData.m_style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetListBox( NULL,
																								WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																								75, 250,
																								100, 100,
																								&instData,
																								&listData, NULL, TRUE );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Listbox text"), 
												 TheWindowManager->winMakeColor( 255, 255, 255, 255 ), -1, -1 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"More text"), 
												 TheWindowManager->winMakeColor( 105, 105, 255, 255 ), -1, -1 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Nothing"), 
												 TheWindowManager->winMakeColor( 105, 105, 255, 255 ), -1, -1 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Seasons"), 
												 TheWindowManager->winMakeColor( 105, 205, 255, 255 ), -1, -1 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Misery"), 
												 TheWindowManager->winMakeColor( 235, 105, 255, 255 ), -1, -1 );
	GadgetListBoxAddEntryText( window, UnicodeString(L"Natural"), 
												 TheWindowManager->winMakeColor( 105, 205, 45, 255 ), -1, -1 );

	// make a vert slider
	SliderData sliderData;
	memset( &sliderData, 0, sizeof( sliderData ) );
	sliderData.maxVal = 100;
	sliderData.minVal = 0;
	sliderData.numTicks = 100;
	sliderData.position = 0;
	instData.init();
	instData.m_style = GWS_VERT_SLIDER | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetSlider( NULL,
																							 WIN_STATUS_ENABLED,
																							 360, 250,
																							 11, 100,
																							 &instData,
																							 &sliderData, NULL, TRUE );

	// make a vert slider
	memset( &sliderData, 0, sizeof( sliderData ) );
	sliderData.maxVal = 100;
	sliderData.minVal = 0;
	sliderData.numTicks = 100;
	sliderData.position = 0;
	instData.init();
	instData.m_style = GWS_VERT_SLIDER | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetSlider( NULL,
																							 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																							 400, 250,
																							 11, 100,
																							 &instData,
																							 &sliderData, NULL, TRUE );

	// make a horizontal slider
	memset( &sliderData, 0, sizeof( sliderData ) );
	sliderData.maxVal = 100;
	sliderData.minVal = 0;
	sliderData.numTicks = 100;
	sliderData.position = 0;
	instData.init();
	instData.m_style = GWS_HORZ_SLIDER | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetSlider( NULL,
																							 WIN_STATUS_ENABLED,
																							 200, 400,
																							 200, 11,
																							 &instData,
																							 &sliderData, NULL, TRUE );

	// make a horizontal slider
	memset( &sliderData, 0, sizeof( sliderData ) );
	sliderData.maxVal = 100;
	sliderData.minVal = 0;
	sliderData.numTicks = 100;
	sliderData.position = 0;
	instData.init();
	instData.m_style = GWS_HORZ_SLIDER | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetSlider( NULL,
																							 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																							 200, 420,
																							 200, 11,
																							 &instData,
																							 &sliderData, NULL, TRUE );

	// make a progress bar
	instData.init();
	instData.m_style = GWS_PROGRESS_BAR | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetProgressBar( NULL,
																									 WIN_STATUS_ENABLED,
																									 200, 450,
																									 250, 15,
																									 &instData, NULL, TRUE );

	// make a progress bar
	instData.init();
	instData.m_style = GWS_PROGRESS_BAR | GWS_MOUSE_TRACK;
	window = TheWindowManager->gogoGadgetProgressBar( NULL,
																									 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																									 200, 470,
																									 250, 15,
																									 &instData, NULL, TRUE );

	// make some static text
	TextData textData;
	textData.centered = 1;
	instData.init();
	instData.m_style = GWS_STATIC_TEXT | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Centered Static Text";
	window = TheWindowManager->gogoGadgetStaticText( NULL,
																									 WIN_STATUS_ENABLED,
																									 200, 490,
																									 300, 25,
																									 &instData,
																									 &textData, NULL, TRUE );

	// make some static text
	textData.centered = 0;
	instData.init();
	instData.m_style = GWS_STATIC_TEXT | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Not Centered Static Text";
	window = TheWindowManager->gogoGadgetStaticText( NULL,
																									 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																									 200, 520,
																									 300, 25,
																									 &instData,
																									 &textData, NULL, TRUE );
	window->winSetEnabledTextColors( TheWindowManager->winMakeColor( 128, 128, 255, 255 ),
																	 TheWindowManager->winMakeColor( 255, 255, 255, 255 ) );

	// make some entry text
	EntryData entryData;
	memset( &entryData, 0, sizeof( entryData ) );
	entryData.maxTextLen = 30;
	instData.init();
	instData.m_style = GWS_ENTRY_FIELD | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Entry";
	window = TheWindowManager->gogoGadgetTextEntry( NULL,
																									 WIN_STATUS_ENABLED,
																									 450, 270,
																									 400, 30,
																									 &instData,
																									 &entryData, NULL, TRUE );

	// make some entry text
	memset( &entryData, 0, sizeof( entryData ) );
	entryData.maxTextLen = 30;
	instData.init();
	instData.m_style = GWS_ENTRY_FIELD | GWS_MOUSE_TRACK;
	instData.m_textLabelString = "Entry";
	window = TheWindowManager->gogoGadgetTextEntry( NULL,
																									 WIN_STATUS_ENABLED | WIN_STATUS_IMAGE,
																									 450, 310,
																									 400, 30,
																									 &instData,
																									 &entryData, NULL, TRUE );

	return TRUE;

}  // end initTestGUI


// GameWindowManager::winNextTab: defined in GameWindowManager_winPrevTab.cpp (its row's unit).

// GameWindowManager::winPrevTab: defined in GameWindowManager_winPrevTab.cpp (its row's unit).

// GameWindowManager::registerTabList: defined in GameWindowManager_registerTabList.cpp (its row's unit).

// ?GameWindowManager::clearTabList present-unmatched
void GameWindowManager::clearTabList( void )
{
	m_tabList.clear();
}
