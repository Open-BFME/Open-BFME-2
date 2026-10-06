// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// W3DGadgetProgressBarDraw 0x000A0D5E (493B), W3DGadgetProgressBarImageDrawA
// 0x000A0F4B (169B) and W3DGadgetProgressBarImageDrawLocalCopy 0x000A0FF4
// (754B): Zero Hour's W3DProgressBar.cpp through BFME1's donor of the same
// name (Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/
// Gadget/), built /O1 like the matched W3DRadioButton.cpp and W3DCheckBox.cpp
// siblings.
//
// Target evidence: the function lexicon entry at 0x009B3DE4 names
// W3DGadgetProgressBarDraw and points at 0x000A0D5E, which progress-bar gadget
// vtable 0x00BC8D04 slot 3 also calls. The lexicon's
// W3DGadgetProgressBarImageDraw is the shared empty RET 0x000B3FD0, as in
// BFME1. 0x000A0F4B and 0x000A0FF4 have no call or pointer reference in retail;
// their names are carried from the BFME1 donor (ImageDrawA is pinned there by
// its ILT thunk; LocalCopy is the donor's name for Zero Hour's image draw
// body) and stay donor names, not target facts. BFME2 deltas: the clip calls
// go through BFME's Display slots, and the ICoord2D locals carry an empty
// default constructor (it fixes the operand order of the bar arithmetic).
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

// FILE: W3DProgressBar.cpp ///////////////////////////////////////////////////
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
// File name: W3DProgressBar.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the progress bar GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetProgressBar.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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

// W3DGadgetProgressBarDraw ===================================================
/** Draw colored Progress Bar using standard graphics */
//=============================================================================
void W3DGadgetProgressBarDraw( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, start, end;
	Color backColor, backBorder, barColor, barBorder;
	Int progress = (Int)window->winGetUserData();

	// get window size and position
  window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors to use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		backColor		= GadgetProgressBarGetDisabledColor( window );
		backBorder	= GadgetProgressBarGetDisabledBorderColor( window );
		barColor		= GadgetProgressBarGetDisabledBarColor( window );
		barBorder		= GadgetProgressBarGetDisabledBarBorderColor( window );
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		backColor		= GadgetProgressBarGetHiliteColor( window );
		backBorder	= GadgetProgressBarGetHiliteBorderColor( window );
		barColor		= GadgetProgressBarGetHiliteBarColor( window );
		barBorder		= GadgetProgressBarGetHiliteBarBorderColor( window );
	}  // end else if, hilited
	else
	{
		backColor		= GadgetProgressBarGetEnabledColor( window );
		backBorder	= GadgetProgressBarGetEnabledBorderColor( window );
		barColor		= GadgetProgressBarGetEnabledBarColor( window );
		barBorder		= GadgetProgressBarGetEnabledBarBorderColor( window );
	}  // end else, enabled

	// draw background border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw background fill
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the progress so far
	if( progress )
	{

		// draw bar border
		if( barBorder != WIN_COLOR_UNDEFINED )
		{

			start.x = origin.x;
			start.y = origin.y;
			end.x = start.x + (size.x * progress) / 100;
			end.y = start.y + size.y;
			if(end.x- start.x > 1  )
			{
				TheWindowManager->winOpenRect( barBorder, WIN_DRAW_LINE_WIDTH,
																		 start.x, start.y, end.x, end.y );
			}

		}  // end if

		// draw bar fill
		if( barColor != WIN_COLOR_UNDEFINED )
		{

			start.x = origin.x + 1;
			start.y = origin.y + 1;
			end.x = start.x + (size.x * progress) / 100 - 2;
			end.y = start.y + size.y - 2;
//			TheWindowManager->winOpenRect( barColor, WIN_DRAW_LINE_WIDTH,
//																		 start.x, start.y, end.x, end.y );
			
			if(end.x- start.x > 1  )
			{
				TheWindowManager->winFillRect( barColor,WIN_DRAW_LINE_WIDTH,
																		 start.x, start.y, end.x, end.y );
			
				TheWindowManager->winDrawLine(GameMakeColor(255,255,255,255),WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, start.y);
				TheWindowManager->winDrawLine(GameMakeColor(200,200,200,255),WIN_DRAW_LINE_WIDTH, start.x, start.y, start.x, end.y);
			}

		}  // end if

	}  // end if

  

}  // end W3DGadgetProgressBarDraw

// W3DGadgetProgressBarImageDraw ==============================================
/** Draw Progress Bar with user supplied images */
//=============================================================================
void W3DGadgetProgressBarImageDrawA( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size;
	const Image *barCenter, *barRight, *left, *right, *center;
	Int progress = (Int)window->winGetUserData();
	Int xOffset, yOffset;
	Int i;
	// get window size and position
  window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	barCenter				= GadgetProgressBarGetEnabledBarImageCenter( window );
	barRight				= GadgetProgressBarGetEnabledBarImageRight( window );
	left						= GadgetProgressBarGetEnabledImageLeft( window );
	right						= GadgetProgressBarGetEnabledImageRight( window );
	center					= GadgetProgressBarGetEnabledImageCenter( window );

	if(!barCenter || !barRight || !left || !right || !center)
		return;

	Int width = barCenter->getImageWidth();
//	Int height = barCenter->getImageHeight();

	Int drawWidth = (size.x * progress) / 100;
	Int pieces = drawWidth / width;
	Int x = origin.x;
	for( i = 0; i < pieces; i ++)
	{
				
				TheWindowManager->winDrawImage( barCenter,
																				x, origin.y,
																				x + width, origin.y + size.y );
				x += width;
	}


}

void W3DGadgetProgressBarImageDrawLocalCopy( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, start, end;
	const Image *backLeft, *backRight, *backCenter, 
				 *barRight, *barCenter;//*backSmallCenter,*barLeft,, *barSmallCenter;
	Int progress = (Int)window->winGetUserData();
	Int xOffset, yOffset;
	Int i;

	// get window size and position
  window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	// get the right images to use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		backLeft				= GadgetProgressBarGetDisabledImageLeft( window );
		//barLeft					= GadgetProgressBarGetDisabledBarImageLeft( window );
		backRight				= GadgetProgressBarGetDisabledImageRight( window );
		barRight				= GadgetProgressBarGetDisabledBarImageRight( window );
		backCenter			= GadgetProgressBarGetDisabledImageCenter( window );
		barCenter				= GadgetProgressBarGetDisabledBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetDisabledImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetDisabledBarImageSmallCenter( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		backLeft				= GadgetProgressBarGetHiliteImageLeft( window );
		//barLeft					= GadgetProgressBarGetHiliteBarImageLeft( window );
		backRight				= GadgetProgressBarGetHiliteImageRight( window );
		barRight				= GadgetProgressBarGetHiliteBarImageRight( window );
		backCenter			= GadgetProgressBarGetHiliteImageCenter( window );
		barCenter				= GadgetProgressBarGetHiliteBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetHiliteImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetHiliteBarImageSmallCenter( window );

	}  // end else if, hilited
	else
	{

		backLeft				= GadgetProgressBarGetEnabledImageLeft( window );
		//barLeft					= GadgetProgressBarGetEnabledBarImageLeft( window );
		backRight				= GadgetProgressBarGetEnabledImageRight( window );
		barRight				= GadgetProgressBarGetEnabledBarImageRight( window );
		backCenter			= GadgetProgressBarGetEnabledImageCenter( window );
		barCenter				= GadgetProgressBarGetEnabledBarImageCenter( window );
		//backSmallCenter	= GadgetProgressBarGetEnabledImageSmallCenter( window );
		//barSmallCenter	= GadgetProgressBarGetEnabledBarImageSmallCenter( window );

	}  // end else, enabled

	// sanity
	if( backLeft == NULL || backRight == NULL ||
			backCenter == NULL ||
			barRight == NULL)
			// backSmallCenter == NULL ||barLeft == NULL ||barCenter == NULL || barSmallCenter == NULL )
		return;

	// get image sizes for the ends
	CtorCoord leftSize, rightSize;
	leftSize.x = backLeft->getImageWidth();
	leftSize.y = backLeft->getImageHeight();
	rightSize.x = backRight->getImageWidth();
	rightSize.y = backRight->getImageHeight();

	// get two key points used in the end drawing
	CtorCoord leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y + yOffset;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;

	// how many whole repeating pieces will fit in that width
	pieces = centerWidth / backCenter->getImageWidth();

	// draw the pieces
	start.x = leftEnd.x;
	start.y = origin.y + yOffset;
	end.y = start.y + size.y;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + backCenter->getImageWidth();
		TheWindowManager->winDrawImage( backCenter, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += backCenter->getImageWidth();

	}  // end for i

	//
	// how many small repeating pieces will fit in the gap from where the
	// center repeating bar stopped and the right image, draw them
	// and overlapping underneath where the right end will go
	//
//	centerWidth = rightStart.x - start.x;
//	pieces = centerWidth / backCenter->getImageWidth() + 1;
//	end.y = start.y + size.y;
//	IRegion2D clipRegion;
//	
//	TheDisplay->setClipRegion()
//	for( i = 0; i < pieces; i++ )
//	{
//
//		end.x = start.x + backCenter->getImageWidth();
//		TheWindowManager->winDrawImage( backCenter,
//																		start.x, start.y,
//																		end.x, end.y );
//		start.x += backCenter->getImageWidth();
//
//	}  // end for i
//
	IRegion2D reg;
	reg.lo.x = start.x;
	reg.lo.y = start.y;
	reg.hi.x = rightStart.x;
	reg.hi.y = end.y;
	centerWidth = rightStart.x - start.x;
	if( centerWidth > 0)
	{
		((BFMEClipDisplay *)TheDisplay)->setClipRegion(&reg);
		end.x = start.x + backCenter->getImageWidth();
		TheWindowManager->winDrawImage( backCenter,
																		start.x, start.y,
																		end.x, end.y );
		((BFMEClipDisplay *)TheDisplay)->enableClipping(FALSE);
	}


	// draw left end
	start.x = origin.x + xOffset;
	start.y = origin.y + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(backLeft, start.x, start.y, end.x, end.y);

	// draw right end
	start = rightStart;
	end.x = start.x + rightSize.x;
	end.y = start.y + size.y;
	TheWindowManager->winDrawImage(backRight, start.x, start.y, end.x, end.y);

	
	CtorCoord barWindowSize;  // end point of bar from window origin

	barWindowSize.x = ((size.x - 20) * progress) / 100;
	barWindowSize.y = size.y;
		
	pieces = barWindowSize.x / barCenter->getImageWidth();
 	// draw the pieces
	start.x = origin.x +10;
	start.y = origin.y + yOffset +5;
	end.y = start.y + size.y - 10;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + barCenter->getImageWidth();
		TheWindowManager->winDrawImage( barCenter, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += barCenter->getImageWidth();

	}  // end for i
	start.x = origin.x + 10 + barCenter->getImageWidth() * pieces;
	//pieces = (size.x - barWindowSize.x -20) / barRight->getImageWidth();
	//Changed By Saad for flashing grey piece
	pieces = ((size.x - 20) / barCenter->getImageWidth()) - pieces;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + barRight->getImageWidth();
		TheWindowManager->winDrawImage( barRight, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += barRight->getImageWidth();

	}  // end for i

}  // end W3DGadgetProgressBarImageDraw
