// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// drawRadioButtonText 0x000A3E4F (274B), W3DGadgetRadioButtonDraw 0x000A3F61
// (472B) and W3DGadgetRadioButtonImageDraw 0x000A4139 (495B): Zero Hour's
// W3DRadioButton.cpp through BFME1's W3DRadioButtonText.cpp donor (Open-BFME-1
// game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/), built /O1 like
// the matched W3DComboBox.cpp sibling.
//
// Target evidence: the function lexicon names both draw callbacks; both end in
// WinInstanceData::getTextLength (0x000A3DCC) and a same-TU call to 0x000A3E4F
// with the window in ECX and instData in EAX, the register convention VC7.1
// gives a static beside its callers, so the helper keeps the ZH name. BFME2
// deltas from the BFME1 donor: GameWindow's draw data is not shifted against
// the bfme2gwm header (colors read +0x4C/+0xB8/+0x124 directly), Display's clip
// slots are +0xA8/+0xB0, and the helper's ICoord2D locals carry an empty default
// constructor (it fixes the operand order of the centering math and of the
// image draw's end points).
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

// FILE: W3DRadioButton.cpp ///////////////////////////////////////////////////
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
// File name: W3DRadioButtonText.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D methods needed to implement the RadioButton UI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
// Use the verified checkbox donor view: getTextLength is virtual slot 3.
#include "../../../../../../../reference/open-bfme-1/inputs/reference/shims/w3ddisplaystring/GameClient/DisplayString.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetRadioButton.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// This body also uses BFME's separate text-color setter and four-argument
// draw overload. Keep those measured virtual slots local; length and font
// agree with the shared donor DisplayString view included above.
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

// BFME's Display vtable places setClipRegion at +0xA8 and enableClipping at
// +0xB0, past the Zero Hour header's slots.
class BFMEClipDisplay
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33();
	virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37();
	virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41();
	virtual void setClipRegion( IRegion2D *region );
	virtual void unused43();
	virtual void enableClipping( Bool onoff );
};

// Coordinates with an empty default constructor; see the header note.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

// drawRadioButtonText ========================================================
/** Draw the text for a RadioButton. */
//=============================================================================
static void drawRadioButtonText( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	DisplayString *text = instData->getTextDisplayString();
	BFMEDisplayString *bfmeText = (BFMEDisplayString *)text;

	// sanity
	if( text == NULL || bfmeText->getTextLength() == 0 )
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
	if( bfmeText->getFont() != window->winGetFont() )
		bfmeText->setFont( window->winGetFont() );

	// get text size
	bfmeText->getSize( &width, &height );

	// set the location for our text
	textPos.x = origin.x + (size.x / 2) - (width / 2);
	textPos.y = origin.y + (size.y / 2) - (height / 2);

	// draw it
	bfmeText->setTextColor( textColor, dropColor );
	bfmeText->draw( textPos.x, textPos.y, 1, 1 );

}  // end drawRadioButtonText

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetRadioButtonDraw ===================================================
/** Draw colored check box using standard graphics */
//=============================================================================
void W3DGadgetRadioButtonDraw( GameWindow *window, WinInstanceData *instData )
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
	// get the colors we should be using to draw, see GadgetRadioButton.h
	// draw appropriate state, see GadgetRadioButton.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		// disabled background
		backColor			= GadgetRadioGetDisabledColor( window );
		backBorder		= GadgetRadioGetDisabledBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
				boxColor		= GadgetRadioGetDisabledCheckedBoxColor( window );
				boxBorder		= GadgetRadioGetDisabledCheckedBoxBorderColor( window );
		}
		else
		{
				boxColor		= GadgetRadioGetDisabledUncheckedBoxColor( window );
				boxBorder		= GadgetRadioGetDisabledUncheckedBoxBorderColor( window );
		}

	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		// hilited background 
		backColor			= GadgetRadioGetHiliteColor( window );
		backBorder		= GadgetRadioGetHiliteBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetRadioGetHiliteCheckedBoxColor( window );
			boxBorder		= GadgetRadioGetHiliteCheckedBoxBorderColor( window );
		}
		else
		{
			boxColor		= GadgetRadioGetHiliteUncheckedBoxColor( window );
			boxBorder		= GadgetRadioGetHiliteUncheckedBoxBorderColor( window );
		}

	}  // end else if
	else
	{

		// enabled background 
		backColor			= GadgetRadioGetEnabledColor( window );
		backBorder		= GadgetRadioGetEnabledBorderColor( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetRadioGetEnabledCheckedBoxColor( window );
			boxBorder		= GadgetRadioGetEnabledCheckedBoxBorderColor( window );
		}
		else
		{
			boxColor		= GadgetRadioGetEnabledUncheckedBoxColor( window );
			boxBorder		= GadgetRadioGetEnabledUncheckedBoxBorderColor( window );
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
	start.x = origin.x + size.y;
	start.y = origin.y;
	end.x = start.x;
	end.y = start.y + size.y;
	TheWindowManager->winDrawLine( backBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw box for button
	start.x = origin.x + 1;
	start.y = origin.y + 1;
	end.x	= origin.x + size.y -1;
	end.y = origin.y + size.y -1;
	TheWindowManager->winFillRect( boxColor, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw box border
	start.x = origin.x + size.x - size.y;
	start.y = origin.y;
	end.x = start.x;
	end.y = start.y + size.y;
	TheWindowManager->winDrawLine( backBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw box for button
	start.x = origin.x + size.x - size.y;
	start.y = origin.y + 1;
	end.x	= origin.x + size.x -1;
	end.y = origin.y + size.y -1;
	TheWindowManager->winFillRect( boxColor, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );
	// draw the button text
	if( instData->getTextLength() )
		drawRadioButtonText( window, instData );

	

}  // end W3DGadgetRadioButtonDraw


void W3DGadgetRadioButtonImageDraw( GameWindow *window, 
																	WinInstanceData *instData )
{
	const Image *leftImage, *rightImage, *centerImage;
	CtorCoord origin, size, start, end;
	Int xOffset, yOffset;
	Int i;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	IRegion2D clipLeft;

	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
	{
		//backgroundImage	= GadgetRadioGetEnabledCheckedBoxImage( window );
		leftImage					= GadgetRadioGetSelectedImage( window );
		centerImage				= GadgetRadioGetSelectedUncheckedBoxImage( window );
		rightImage				= GadgetRadioGetSelectedCheckedBoxImage( window );
		
	}
	else if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		// disabled background
		leftImage					= GadgetRadioGetDisabledImage( window );
		centerImage				= GadgetRadioGetDisabledUncheckedBoxImage( window );
		rightImage				= GadgetRadioGetDisabledCheckedBoxImage( window );
		
	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		// hilited background 
		leftImage					= GadgetRadioGetHiliteImage( window );
		centerImage				= GadgetRadioGetHiliteUncheckedBoxImage( window );
		rightImage				= GadgetRadioGetHiliteCheckedBoxImage( window );
		
	}  // end else if
	else
	{
		// enabled background 
		leftImage					= GadgetRadioGetEnabledImage( window );
		centerImage				= GadgetRadioGetEnabledUncheckedBoxImage( window );
		rightImage				= GadgetRadioGetEnabledCheckedBoxImage( window );
		
	}  // end else

	// sanity, we need to have these images to make it look right
	if( leftImage == NULL || centerImage == NULL || 
			rightImage == NULL )
		return;

	// get image sizes for the ends
	ICoord2D leftSize, rightSize;
	leftSize.x = leftImage->getImageWidth();
	leftSize.y = leftImage->getImageHeight();
	rightSize.x = rightImage->getImageWidth();
	rightSize.y = rightImage->getImageHeight();

	// get two key points used in the end drawing
	CtorCoord leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y  + size.y + yOffset;



	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;

	// how many whole repeating pieces will fit in that width
	pieces = centerWidth / centerImage->getImageWidth();
	pieces++;
	// draw the pieces
	start.x = leftEnd.x;
	start.y = origin.y + yOffset;
	end.y =origin.y + size.y + yOffset;
	
	clipLeft.lo.x = leftEnd.x;
	clipLeft.lo.y = origin.y;
	clipLeft.hi.y = leftEnd.y;
	clipLeft.hi.x = rightStart.x	;


	((BFMEClipDisplay *)TheDisplay)->setClipRegion(&clipLeft);
	
	for( i = 0; i < pieces; i++ )
	{
		end.x = start.x + centerImage->getImageWidth();
		TheWindowManager->winDrawImage( centerImage, 
																		start.x, start.y,
																		end.x, end.y );	
		start.x += centerImage->getImageWidth();
	}  // end for i
	
	((BFMEClipDisplay *)TheDisplay)->enableClipping(FALSE);	
	// draw left end
	start.x = origin.x + xOffset;
	start.y = origin.y + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(leftImage, start.x, start.y, end.x, end.y);
	// draw right end
	start.x = rightStart.x;
	start.y = origin.y + yOffset;
	end.x = origin.x + size.x;
	end.y = leftEnd.y;
	TheWindowManager->winDrawImage(rightImage, start.x, start.y, end.x, end.y);

	// draw the text
	if( instData->getTextLength() )
		drawRadioButtonText( window, instData );

	
}  // end W3DGadgetHorizontalSliderImageDraw
