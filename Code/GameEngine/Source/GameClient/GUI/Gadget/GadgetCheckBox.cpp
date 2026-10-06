// cl: /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/stringbaseunicode /Ireference/open-bfme-1/reference/shims/stringbaseascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: CheckBox.cpp /////////////////////////////////////////////////////////
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
// File name: CheckBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Checkbox GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"

void PlaySound( const char *name );

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// BFME's keyboard keeps its modifier flags at +0x0C; Zero Hour's Keyboard
// class has a different layout, so the shift test reads them through a view.
struct BfmeKeyboardModifiers
{
	char m_pad[0x0C];
	UnsignedInt m_modifiers;
};

// GadgetCheckBoxInput ========================================================
/** Handle input for check box */
//=============================================================================
WindowMsgHandledType GadgetCheckBoxInput( GameWindow *window, UnsignedInt msg,
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
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window,
																						mData1 );
				PlaySound( "Gui_ShellMapMouseOver" );

			}  // end if

			break;

		}  // end mouse entering

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window,
																						mData1 );
				PlaySound( "Gui_ShellMapMouseOut" );

			}  // end if

			break;

		}  // end mouse leaving

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:
		{

			TheWindowManager->winSendSystemMsg( window->winGetOwner(), GGM_LEFT_DRAG,
																					(WindowMsgData)window, mData1 );
			break;

		}  // end left drag

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
		{

			break;

		}  // end left down

		// ------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{

			if( BitTest( instData->getState(), WIN_STATE_HILITED ) == FALSE )
			{
				// this up click was not meant for this button
				return MSG_IGNORED;
			}

			// Toggle the check state
			instData->m_state ^= WIN_STATE_SELECTED;
			TheWindowManager->winSendSystemMsg( window->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)window, mData1 );
			PlaySound( "Gui_ShellMapSelect" );

			break;

		}  // end left up and left click

		// ------------------------------------------------------------------------
		case GWM_RIGHT_DOWN:
		{

			break;

		}  // end right down

		//-------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{

			// Need to be specially marked to care about right mouse events
			if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			{
				TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED_RIGHT,
																						(WindowMsgData)window, mData1 );
				BitClear( instData->m_state, WIN_STATE_SELECTED );
			}
			else
			{
				// this up click was not meant for this button
				return MSG_IGNORED;
			}

			break;

		}  // end right up or right click

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

						// Toggle the check state
						instData->m_state ^= WIN_STATE_SELECTED;
						TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																								GBM_SELECTED,
																								(WindowMsgData)window,
																								0 );

					}  //end if

					break;

				}  // end enter/space

				// --------------------------------------------------------------------
				case KEY_TAB:
				{

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( BitTest( ((BfmeKeyboardModifiers *)TheKeyboard)->m_modifiers, KEY_STATE_LSHIFT ) )
							TheWindowManager->winPrevTab(window);
						else
							TheWindowManager->winNextTab(window);
					}
					break;

				}  // end tab

				// --------------------------------------------------------------------
				default:
				{

					return MSG_IGNORED;

				}  // end default

			}  // end switch

			break;

		}  // end char msg

		// ------------------------------------------------------------------------
		default:
		{

			return MSG_IGNORED;

		}  // end default

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetCheckBoxInput

// GadgetCheckBoxSystem =======================================================
/** Handle system messages for check box */
//=============================================================================
WindowMsgHandledType GadgetCheckBoxSystem( GameWindow *window, UnsignedInt msg,
													 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg ) 
	{
		// ------------------------------------------------------------------------	
		case GGM_SET_LABEL:
		{
			// BFME dispatches this base operation directly; virtual dispatch changes the retail call shape.
			window->GameWindow::winSetText( *(UnicodeString*)mData1 );
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:

			if( mData1 == FALSE )
				BitClear( instData->m_state, WIN_STATE_HILITED );
			else
				BitSet( instData->m_state, WIN_STATE_HILITED );
			TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					GGM_FOCUS_CHANGE,
																					mData1, 
																					window->winGetWindowId() );
			if( mData1 == FALSE )
				*(Bool*)mData2 = FALSE;
			else
				*(Bool*)mData2 = TRUE;
			
			break;

		default: 
			return MSG_IGNORED;

	}  // end switch msg

	return MSG_HANDLED;

}  // end GadgetCheckBoxSystem

// GadgetCheckBoxSetText ======================================================
/** Set the text for the control */
//=============================================================================
void GadgetCheckBoxSetText( GameWindow *g, UnicodeString text )
{

	// sanity
	if( g == NULL )
		return;

	TheWindowManager->winSendSystemMsg( g, GGM_SET_LABEL, (WindowMsgData)&text, 0 );

}  // end GadgetCheckBoxSetText

// GadgetCheckBoxSetChecked ============================================
//=============================================================================
/** Set the check state for the check box */
//=============================================================================
void GadgetCheckBoxSetChecked( GameWindow *g, Bool isChecked)
{
	WinInstanceData *instData = g->winGetInstanceData();
	if (isChecked)
	{
		BitSet(instData->m_state,  WIN_STATE_SELECTED);
	}
	else
	{
		BitClear(instData->m_state,  WIN_STATE_SELECTED);
	}

	TheWindowManager->winSendSystemMsg( g->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)g, 0 );

}

// GadgetCheckBoxToggle ============================================
//=============================================================================
/** Toggle the check state for the check box */
//=============================================================================
void GadgetCheckBoxToggle( GameWindow *g)
{
	WinInstanceData *instData = g->winGetInstanceData();
	Bool isChecked = BitTest(instData->m_state, WIN_STATE_SELECTED);
	if (isChecked)
	{
		BitClear(instData->m_state,  WIN_STATE_SELECTED);
	}
	else
	{
		BitSet(instData->m_state,  WIN_STATE_SELECTED);
	}

	TheWindowManager->winSendSystemMsg( g->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)g, 0 );

}

// GadgetCheckBoxIsChecked ======================================================
/** Check the check state */
//=============================================================================
// GadgetCheckBoxIsChecked: defined in GadgetCheckBoxIsChecked.cpp (its row's unit).
Bool GadgetCheckBoxIsChecked( GameWindow *g );
