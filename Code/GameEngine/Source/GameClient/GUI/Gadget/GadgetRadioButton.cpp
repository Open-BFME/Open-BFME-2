// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: RadioButton.cpp //////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: RadioButton.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Radio button GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "Gameclient/GameWindowManager.h"
#include "GameClient/Gadget.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// doRadioUnselect ============================================================
/** Do the unselect of matching group not including exception window */
//=============================================================================
static void doRadioUnselect( GameWindow *window, Int group, Int screen,
												GameWindow *except )
{

	//
	// if this is a radio button we have something to consider, but we
	// will ignore the except window
	//
	if( window != except && BitTest( window->winGetStyle(), GWS_RADIO_BUTTON ) )
	{
		RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();

		if( radioData->group == group && radioData->screen == screen )
		{
			WinInstanceData *instData = window->winGetInstanceData();

			BitClear( instData->m_state, WIN_STATE_SELECTED );

		}  // end if

	}  // end if

	// recursively call on all my children
	GameWindow *child;

	for( child = window->winGetChild(); child; child = child->winGetNext() )
		doRadioUnselect( child, group, screen, except );

}  // end doRadioUnselect

// winGetWindowList is at BFME's retail manager slot 0x94.
class BfmeRadioWindowListManager
{
public:
#define RADIO_LIST_SLOT(n) virtual void slot##n() = 0;
	RADIO_LIST_SLOT(0) RADIO_LIST_SLOT(1) RADIO_LIST_SLOT(2) RADIO_LIST_SLOT(3)
	RADIO_LIST_SLOT(4) RADIO_LIST_SLOT(5) RADIO_LIST_SLOT(6) RADIO_LIST_SLOT(7)
	RADIO_LIST_SLOT(8) RADIO_LIST_SLOT(9) RADIO_LIST_SLOT(10) RADIO_LIST_SLOT(11)
	RADIO_LIST_SLOT(12) RADIO_LIST_SLOT(13) RADIO_LIST_SLOT(14) RADIO_LIST_SLOT(15)
	RADIO_LIST_SLOT(16) RADIO_LIST_SLOT(17) RADIO_LIST_SLOT(18) RADIO_LIST_SLOT(19)
	RADIO_LIST_SLOT(20) RADIO_LIST_SLOT(21) RADIO_LIST_SLOT(22) RADIO_LIST_SLOT(23)
	RADIO_LIST_SLOT(24) RADIO_LIST_SLOT(25) RADIO_LIST_SLOT(26) RADIO_LIST_SLOT(27)
	RADIO_LIST_SLOT(28) RADIO_LIST_SLOT(29) RADIO_LIST_SLOT(30) RADIO_LIST_SLOT(31)
	RADIO_LIST_SLOT(32) RADIO_LIST_SLOT(33) RADIO_LIST_SLOT(34) RADIO_LIST_SLOT(35)
	RADIO_LIST_SLOT(36)
#undef RADIO_LIST_SLOT
	virtual GameWindow *winGetWindowList() = 0;
};

// unselectOtherRadioOfGroup ==================================================
/** Go through the entire window system, including child windows and
	* unselect any radio buttons of the specified group, but not the
	* window specified */
//=============================================================================
	__declspec(noinline) static void unselectOtherRadioOfGroup( Int group, Int screen,
																			 GameWindow *except )
{
	GameWindow *window = ((BfmeRadioWindowListManager *)TheWindowManager)->winGetWindowList();

	for( window = ((BfmeRadioWindowListManager *)TheWindowManager)->winGetWindowList();
			 window;
			 window = window->winGetNext() )
		doRadioUnselect( window, group, screen, except );

}  // end unselectOtherRadioOfGroup

//-------------------------------------------------------------------------------------------------
// BFME's radio input keeps only TAB for focus navigation and uses the keyboard
// shift flag to choose the direction.  The manager owns these callbacks at
// vtable slots 0xA8 and 0xAC in the retail layout.
//-------------------------------------------------------------------------------------------------
class BfmeVirtualTabWindowManager
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual GameWindow *winGetWindowList() = 0;           // slot 0x94
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void winNextTab( GameWindow *window ) = 0;   // slot 0xA8
	virtual void winPrevTab( GameWindow *window ) = 0;   // slot 0xAC
};

// BFME's GameWindowManager has five more virtuals before winSendSystemMsg
// than the BFME1 header exposes (retail slot 0xE8 versus donor slot 0xD4).
class Bfme2RadioWindowManager
{
public:
#define RADIO_SLOT(n) virtual void slot##n() = 0;
	RADIO_SLOT(0) RADIO_SLOT(1) RADIO_SLOT(2) RADIO_SLOT(3)
	RADIO_SLOT(4) RADIO_SLOT(5) RADIO_SLOT(6) RADIO_SLOT(7)
	RADIO_SLOT(8) RADIO_SLOT(9) RADIO_SLOT(10) RADIO_SLOT(11)
	RADIO_SLOT(12) RADIO_SLOT(13) RADIO_SLOT(14) RADIO_SLOT(15)
	RADIO_SLOT(16) RADIO_SLOT(17) RADIO_SLOT(18) RADIO_SLOT(19)
	RADIO_SLOT(20) RADIO_SLOT(21) RADIO_SLOT(22) RADIO_SLOT(23)
	RADIO_SLOT(24) RADIO_SLOT(25) RADIO_SLOT(26) RADIO_SLOT(27)
	RADIO_SLOT(28) RADIO_SLOT(29) RADIO_SLOT(30) RADIO_SLOT(31)
	RADIO_SLOT(32) RADIO_SLOT(33) RADIO_SLOT(34) RADIO_SLOT(35)
	RADIO_SLOT(36) RADIO_SLOT(37) RADIO_SLOT(38) RADIO_SLOT(39)
	RADIO_SLOT(40) RADIO_SLOT(41) RADIO_SLOT(42) RADIO_SLOT(43)
	RADIO_SLOT(44) RADIO_SLOT(45) RADIO_SLOT(46) RADIO_SLOT(47)
	RADIO_SLOT(48) RADIO_SLOT(49) RADIO_SLOT(50) RADIO_SLOT(51)
	RADIO_SLOT(52) RADIO_SLOT(53) RADIO_SLOT(54) RADIO_SLOT(55)
	RADIO_SLOT(56) RADIO_SLOT(57)
#undef RADIO_SLOT
	virtual Int winSendSystemMsg( GameWindow *window, unsigned int message,
		unsigned int data1, unsigned int data2 ) = 0;
};

class BfmeKeyboardModifiers
{
public:
	char m_pad[0x0c];
	unsigned char m_flagsAt0C;
};

extern BfmeKeyboardModifiers *TheBfmeKeyboardModifiers;

static Bool bfmeShiftHeld( void )
{
	return BitTest( TheBfmeKeyboardModifiers->m_flagsAt0C, 0x10 );
}

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////

// GadgetRadioButtonInput =====================================================
/** Handle input for radio button */
//=============================================================================
WindowMsgHandledType GadgetRadioButtonInput( GameWindow *window, UnsignedInt msg,
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg )
	{

		// ------------------------------------------------------------------------
		case GWM_MOUSE_ENTERING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{

				BitSet( instData->m_state, WIN_STATE_HILITED );
				((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( instData->getOwner(),
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window,
																						mData1 );
				//TheWindowManager->winSetFocus( window );

			}  // end if

			break;

		}  // end mouse enter

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( instData->getOwner(),
																						GBM_MOUSE_LEAVING,
																					  (WindowMsgData)window,
																						mData1 );
			}  // end if

			break;

		}  // end mouse leaving

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:
		{

			((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( instData->getOwner(), GGM_LEFT_DRAG,
																					(WindowMsgData)window, mData1 );
			break;

		}  // end left drag

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
		{

			break;

		}  // end down

		// ------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{

			if( BitTest( instData->getState(), WIN_STATE_SELECTED ) == FALSE )
			{
				RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();

				((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( window->winGetOwner(),
																						GBM_SELECTED,
																						(WindowMsgData)window,
																						mData1 );

				//
				// unselect any windows in the system (including children) that
				// are radio buttons with this same group and screen ID
				//
				if( radioData->group != 0 )
					unselectOtherRadioOfGroup(radioData->group, radioData->screen, window );

				// this button is now selected
				BitSet( instData->m_state, WIN_STATE_SELECTED );

			}  // end if, not selected
			else if( BitTest( instData->getState(), WIN_STATE_HILITED ) == FALSE )
			{

				// this up click was not meant for this button
				return MSG_IGNORED;

			}  // end else if

			break;

		}  // end left up or click

		// ------------------------------------------------------------------------
		case GWM_CHAR:
		{

			switch( mData1 )
			{

				// --------------------------------------------------------------------
				case KEY_ENTER:
				case KEY_SPACE:
				{

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{

						if( BitTest( instData->getState(), WIN_STATE_SELECTED ) == FALSE )
						{
							RadioButtonData *radioData = (RadioButtonData *)window->winGetUserData();

							((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( window->winGetOwner(),
																																	GBM_SELECTED,
																																					(WindowMsgData)window,
																																					mData1 );

								//
								// unselect any windows in the system (including children) that
								// are radio buttons with this same group and screen ID
								//
								if( radioData->group != 0 )
									unselectOtherRadioOfGroup(radioData->group, radioData->screen, window );

								// this button is now selected
								BitSet( instData->m_state, WIN_STATE_SELECTED );

						}  // end if, not selected

					}  // end key down

					break;

				}  // end enter/space

				// --------------------------------------------------------------------
				case KEY_TAB:
				{

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( bfmeShiftHeld() )
							((BfmeVirtualTabWindowManager *)TheWindowManager)->winPrevTab(window);
						else
							((BfmeVirtualTabWindowManager *)TheWindowManager)->winNextTab(window);
					}
					break;

				}  // end tab

				// --------------------------------------------------------------------
				default:
				{

					return MSG_IGNORED;

				}  // end default

			}  // end switch( mData1 )

			break;

		}  // end char messsage

		// ------------------------------------------------------------------------
		default:
		{

			return MSG_IGNORED;

		}  // end default

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetRadioButtonInput

// GadgetRadioButtonSystem ====================================================
// Retail provides the system handler; this TU only declares it so calls
// reach the retail copy (its body here did not match retail).
WindowMsgHandledType GadgetRadioButtonSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2);

// GadgetRadioSetText =========================================================
/** Set the text for the control */
//=============================================================================
void GadgetRadioSetText( GameWindow *g, UnicodeString text )
{

	// sanity
	if( g == NULL )
		return;

	((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( g, GGM_SET_LABEL, (WindowMsgData)&text, 0 );

}  // end GadgetRadioSetText

// GadgetRadioSetGroup ========================================================
/** Set the group number for a radio button, only one radio button of
	* a group can be selected at any given time */
//=============================================================================
void GadgetRadioSetGroup( GameWindow *g, Int group, Int screen )
{
	RadioButtonData *radioData = (RadioButtonData *)g->winGetUserData();

	radioData->group = group;
	radioData->screen = screen;

}  // end GadgetRadioSetGroup


// GadgetRadioSetText =========================================================
/** Set the text for the control */
//=============================================================================
void GadgetRadioSetSelection( GameWindow *g, Bool sendMsg )
{

	// sanity
	if( g == NULL )
		return;

	((Bfme2RadioWindowManager *)TheWindowManager)->winSendSystemMsg( g, GBM_SET_SELECTION, (WindowMsgData)&sendMsg, 0 );

}  // end GadgetRadioSetText

// ?TheBfmeKeyboardModifiers@@3PAVBfmeKeyboardModifiers@@A: the global at this VA is ?TheKeyboard@@3PAVKeyboard@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?TheBfmeKeyboardModifiers@@3PAVBfmeKeyboardModifiers@@A=?TheKeyboard@@3PAVKeyboard@@A")
#pragma comment(linker, "/alternatename:?g_009FE720@@3PAVRva0025CEEFHost@@A=?TheKeyboard@@3PAVKeyboard@@A")
#pragma comment(linker, "/alternatename:?InputLockSubsystem@@3PAVClientSubsystem@@A=?TheKeyboard@@3PAVKeyboard@@A")
// ?TheBfmeKeyboardModifiers@@3PAVBfmeKeyboardModifiers@@A: the global at VA 0xdfe720 is ?TheKeyboard@@3PAVKeyboard@@A.
#pragma comment(linker, "/alternatename:?TheBfmeKeyboardModifiers@@3PAVBfmeKeyboardModifiers@@A=?TheKeyboard@@3PAVKeyboard@@A")
