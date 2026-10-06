// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// drawCheckBoxText 0x000A43CD (261B), W3DGadgetCheckBoxDraw 0x000A44D2 (485B)
// and W3DGadgetCheckBoxImageDraw 0x000A46B7 (204B): Zero Hour's W3DCheckBox.cpp
// through BFME1's donor of the same name (Open-BFME-1 game/GameEngineDevice/
// Source/W3DDevice/GameClient/GUI/Gadget/), built /O1 like the matched
// W3DRadioButton.cpp and W3DComboBox.cpp siblings.
//
// Target evidence: the function lexicon names both draw callbacks; both end in
// WinInstanceData::getTextLength (0x000A3DCC) and a same-TU call to 0x000A43CD
// with the window in ECX and instData in EAX, which symbols.csv already pins as
// the file-static drawCheckBoxText. BFME2 deltas: the text goes through BFME's
// DisplayString slots (setTextColor, then draw with a 1,1 drop offset), the
// image getters read the bfme2gwm draw data directly, and the ICoord2D locals
// carry an empty default constructor (it fixes the operand order of the
// rectangle and box arithmetic).
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

// FILE: W3DCheckBox.cpp //////////////////////////////////////////////////////
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
// File name: W3DCheckBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D methods needed to implement the checkbox UI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "../../../../../../../inputs/reference/shims/w3ddisplaystring/GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// BFME's DisplayString vtable: no virtual destructor slot, a separate
// text-color setter at +0x28, draw at +0x38 and getSize at +0x3C.
class BFMEDisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont( GameFont *font );
	virtual GameFont *getFont();
	virtual void unused08();
	virtual void unused09();
	virtual void setTextColor( Color color, Color dropColor );
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw( Int x, Int y, Int xDrop, Int yDrop );
	virtual void getSize( Int *width, Int *height );
};

// Coordinates with an empty default constructor; see the header note.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

// drawCheckBoxText ===========================================================
/** Draw the text for a checkbox */
//=============================================================================
static void drawCheckBoxText( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	BFMEDisplayString *text = (BFMEDisplayString *)instData->getTextDisplayString();

	// sanity
	if( text == NULL || text->getTextLength() == 0 )
		return;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right text color
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		textColor = window->winGetDisabledTextColor();
		dropColor = window->winGetDisabledTextBorderColor();
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		textColor = window->winGetHiliteTextColor();
		dropColor = window->winGetHiliteTextBorderColor();
	}  // end else if, hilited
	else
	{
		textColor = window->winGetEnabledTextColor();
		dropColor = window->winGetEnabledTextBorderColor();
	}  // end enabled only

	// set our font to that of our parent if not the same
	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );

	// get text size
	text->getSize( &width, &height );

	// where to draw
	textPos.x = origin.x + size.y;//(size.x / 2) - (width / 2);
	textPos.y = origin.y + (size.y / 2) - (height / 2);

	// draw it
	text->setTextColor( textColor, dropColor );
	text->draw( textPos.x, textPos.y, 1, 1 );

}  // end drawCheckBoxText

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetCheckBoxDraw ======================================================
/** Draw colored check box using standard graphics */
//=============================================================================
void W3DGadgetCheckBoxDraw( GameWindow *window, WinInstanceData *instData )
{
	Int checkOffsetFromLeft;
	Color backColor,
				backBorder,
				boxColor,
				boxBorder;
	CtorCoord origin, size, start, end;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// compute start of check offset
	checkOffsetFromLeft = size.x / 16;

	//
	// get the colors we should be using to draw, see GadgetCheckBox.h
	// draw appropriate state, see GadgetCheckBox.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		// disabled background
		backColor			= GadgetCheckBoxGetDisabledColor( window );
		backBorder		= GadgetCheckBoxGetDisabledBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
				boxColor		= GadgetCheckBoxGetDisabledCheckedBoxColor( window );
				boxBorder		= GadgetCheckBoxGetDisabledCheckedBoxBorderColor( window );
		}
		else
		{
				boxColor		= GadgetCheckBoxGetDisabledUncheckedBoxColor( window );
				boxBorder		= GadgetCheckBoxGetDisabledUncheckedBoxBorderColor( window );
		}

	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		// hilited background 
		backColor			= GadgetCheckBoxGetHiliteColor( window );
		backBorder		= GadgetCheckBoxGetHiliteBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetCheckBoxGetHiliteCheckedBoxColor( window );
			boxBorder		= GadgetCheckBoxGetHiliteCheckedBoxBorderColor( window );
		}
		else
		{
			boxColor		= GadgetCheckBoxGetHiliteUncheckedBoxColor( window );
			boxBorder		= GadgetCheckBoxGetHiliteUncheckedBoxBorderColor( window );
		}

	}  // end else if
	else
	{

		// enabled background 
		backColor			= GadgetCheckBoxGetEnabledColor( window );
		backBorder		= GadgetCheckBoxGetEnabledBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetCheckBoxGetEnabledCheckedBoxColor( window );
			boxBorder		= GadgetCheckBoxGetEnabledCheckedBoxBorderColor( window );
		}
		else
		{
			boxColor		= GadgetCheckBoxGetEnabledUncheckedBoxColor( window );
			boxBorder		= GadgetCheckBoxGetEnabledUncheckedBoxBorderColor( window );
		}

	}  // end else

	// draw background border
	start.x = origin.x;
	start.y = origin.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;
	TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw the background
	start.x++;
	start.y++;
	end.x--;
	end.y--;
	TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw box border
	start.x = origin.x + checkOffsetFromLeft;
	start.y = origin.y + (size.y / 3);
	end.x = start.x + (size.y / 3);
	end.y = start.y + (size.y / 3);
	TheWindowManager->winOpenRect( boxBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw "x" for button
	if( boxColor != WIN_COLOR_UNDEFINED )
	{

		TheWindowManager->winDrawLine( boxColor, WIN_DRAW_LINE_WIDTH, 
																	 start.x, start.y, end.x, end.y );
		TheWindowManager->winDrawLine( boxColor, WIN_DRAW_LINE_WIDTH, 
																	 start.x, end.y, end.x, start.y );

	}  // end if

	// draw the button text
	if( instData->getTextLength() )
		drawCheckBoxText( window, instData );

}  // end W3DGadgetCheckBoxDraw

// W3DGadgetCheckBoxImageDraw =================================================
/** Draw check box with user supplied images */
//=============================================================================
void W3DGadgetCheckBoxImageDraw( GameWindow *window, WinInstanceData *instData )
{
	Int checkOffsetFromLeft;
	const Image  *boxImage = NULL;//*backgroundImage = NULL,
	CtorCoord origin, start, end, size;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// compute screen coords
	start.x = origin.x + instData->m_imageOffset.x;
	start.y = origin.y + instData->m_imageOffset.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;

	// compute start of check offset
	checkOffsetFromLeft =  0;

	//
	// get the colors we should be using to draw, see GadgetCheckBoxButton.h
	// draw appropriate state, see GadgetCheckBoxButton.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		// disabled background
//		backgroundImage	= GadgetCheckBoxGetDisabledImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
				boxImage		= GadgetCheckBoxGetDisabledCheckedBoxImage( window );
		else
				boxImage		= GadgetCheckBoxGetDisabledUncheckedBoxImage( window );

	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		// hilited background 
//		backgroundImage	= GadgetCheckBoxGetHiliteImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			boxImage		= GadgetCheckBoxGetHiliteCheckedBoxImage( window );
		else
			boxImage		= GadgetCheckBoxGetHiliteUncheckedBoxImage( window );

	}  // end else if
	else
	{

		// enabled background 
//		backgroundImage	= GadgetCheckBoxGetEnabledImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			boxImage		= GadgetCheckBoxGetEnabledCheckedBoxImage( window );
		else
			boxImage		= GadgetCheckBoxGetEnabledUncheckedBoxImage( window );

	}  // end else

	// draw background image
//	if( backgroundImage )
//		TheWindowManager->winDrawImage( backgroundImage, start.x, start.y, 
//																		end.x, end.y );

	// draw the box image
	if( boxImage )
	{

		start.x = origin.x + instData->m_imageOffset.x + checkOffsetFromLeft;
		start.y = origin.y +  3;
		end.x = (size.y - 6) + start.x;
		end.y = start.y + (size.y - 6);
		TheWindowManager->winDrawImage( boxImage, start.x, start.y, 
																	  end.x, end.y );

	}  // end if
		
	// draw the text
	if( instData->getTextLength() )
		drawCheckBoxText( window, instData );

}  // end W3DGadgetCheckBoxImageDraw
