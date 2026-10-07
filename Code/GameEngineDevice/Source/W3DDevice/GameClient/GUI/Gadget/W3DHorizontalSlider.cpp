// cl: /O1 /arch:SSE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// W3DGadgetHorizontalSliderDraw 0x000A166A (221B) and
// W3DGadgetHorizontalSliderImageDraw 0x000A1747 (603B): Zero Hour's
// W3DHorizontalSlider.cpp through BFME1's donor of the same name (Open-BFME-1
// game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/), built
// /O1 /arch:SSE.
//
// Target evidence: the function lexicon names both callbacks (0x000A166A also
// carries the folded vertical draw); gadget vtables 0x00BC8D5C and 0x00BC8DE0
// slot 3 call them. The draw is the donor's. BFME2's image draw adds a
// resolution scale: unless status bit 0x08000000 is set, x and y multipliers
// come from the display's +0x40/+0x44 size over 800x600; the boxes are 0.6 of
// the scaled fill image wide and the scaled window height tall, the padding is
// one pixel, the highlight row starts 0.8 box heights down, and the integer
// conversions truncate rather than round. The ICoord2D locals carry an empty
// default constructor (it fixes the operand order).
//
// W3DGadgetHorizontalSliderImageDrawA 0x000A19A2 (857B) is Zero Hour's body of
// that name; it follows the image draw in retail and nothing in BFME2 calls
// it, so the name is carried from the donor, not proven. The disabled branch
// clears the center images (Zero Hour leaves them unset), and the clip calls
// go through the BFME Display slots.
//
// W3DGadgetHorizontalSliderImageDrawB 0x000A1D1F (997B), the tooltip debug
// draw, is likewise uncalled and carries the donor's name. BFME1's donor body
// already holds the 0x08000000 unscaled test; its UnicodeString is BFME2's
// shared one (bfme2_ascii_common), whose StringBase copy constructor builds
// the by-value tooltip argument.
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

// FILE: .cpp /////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   
//
// File name: .cpp
//
// Created:   
//
// Desc:      
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetSlider.h"
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
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// BFME's Display vtable returns the screen size from +0x40/+0x44 and places
// setClipRegion at +0xA8 and enableClipping at +0xB0.
class BFMESliderDisplay
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
	virtual UnsignedInt getWidth( void );
	virtual UnsignedInt getHeight( void );
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

// BFME status bit that keeps the slider at its authored 800x600 size.
enum { WIN_STATUS_BFME_UNSCALED = 0x08000000 };

// Coordinates with an empty default constructor; see the header note.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

// W3DGadgetHorizontalSliderDraw ==============================================
/** Draw colored horizontal slider using standard graphics */
//=============================================================================
void W3DGadgetHorizontalSliderDraw( GameWindow *window, WinInstanceData *instData )
{
	Color backBorder, backColor;
	CtorCoord origin, size, start, end;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		backBorder		= GadgetSliderGetDisabledBorderColor( window );
		backColor			= GadgetSliderGetDisabledColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		backBorder		= GadgetSliderGetHiliteBorderColor( window );
		backColor			= GadgetSliderGetHiliteColor( window );

	}  // end else if, hilited
	else
	{

		backBorder		= GadgetSliderGetEnabledBorderColor( window );
		backColor			= GadgetSliderGetEnabledColor( window );

	}  // end else, enabled

	// draw background border and rect over whole control
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if


}  // end W3DGadgetHorizontalSliderDraw

// W3DGadgetHorizontalSliderImageDraw =========================================
/** Draw horizontal slider with user supplied images */
//=============================================================================
void W3DGadgetHorizontalSliderImageDraw( GameWindow *window, 
																				 WinInstanceData *instData )
{
	const Image *fillSquare, *blankSquare, *highlightSquare;
	CtorCoord origin, size, start, end, highlightOffset;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	highlightSquare = GadgetSliderGetHiliteImageLeft( window );
	blankSquare	= GadgetSliderGetDisabledImageRight( window );
	fillSquare = GadgetSliderGetDisabledImageLeft( window );

	SliderData *s = (SliderData *)window->winGetUserData();
	
	Real xMulti = 1.0f;
	Real yMulti = 1.0f;
	if( BitTest( window->winGetStatus(), WIN_STATUS_BFME_UNSCALED ) == FALSE )
	{
		xMulti = INT_TO_REAL(((BFMESliderDisplay *)TheDisplay)->getWidth()) / 800;
		yMulti = INT_TO_REAL(((BFMESliderDisplay *)TheDisplay)->getHeight()) / 600;
	}

	// figure out how many boxes we draw for this slider
	Int numBoxes = 0;
	Int numSelectedBoxes = 0;
	Int numHighlightBoxes = 0;
	Int boxWidth = fillSquare->getImageWidth() * xMulti * 0.6;
	Int boxHeight = size.y * yMulti;
	Int boxPadding = 1;
	start.x = origin.x;
	end.x	= start.x + boxWidth;
	Real selectedPercent = (s->position - s->minVal)/INT_TO_REAL((s->maxVal - s->minVal));
	Int maxSelectedX = origin.x + (Int)(selectedPercent * size.x);
	while(end.x < origin.x + size.x )
	{
		if (start.x <= maxSelectedX && end.x < origin.x + size.x && s->position != s->minVal)
			++numSelectedBoxes;
		start.x = end.x + boxPadding;
		end.x	= start.x + boxWidth;
		++numBoxes;
	}
	numHighlightBoxes = numBoxes + 1;
	Int distanceCovered = end.x - origin.x - boxWidth;
	highlightOffset.x = -(boxWidth + boxPadding)/2;
	highlightOffset.y = boxHeight * 0.8;
	Int blankness = size.x - distanceCovered;
	origin.x += blankness/2;

	Int i;
	if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		ICoord2D backgroundStart, backgroundEnd;
		backgroundStart.y = origin.y + highlightOffset.y;
		backgroundEnd.y = backgroundStart.y + boxWidth + boxPadding;
		for (i=0; i<numHighlightBoxes; ++i)
		{
			backgroundStart.x = origin.x + highlightOffset.x + i*(boxWidth+boxPadding);
			backgroundEnd.x = backgroundStart.x + boxWidth + boxPadding;
			TheWindowManager->winDrawImage( highlightSquare, 
																		backgroundStart.x, backgroundStart.y,
																		backgroundEnd.x, backgroundEnd.y );
		}
	}

	start.y = origin.y;
	end.y = start.y + boxHeight;
	for (i=0; i<numSelectedBoxes; ++i)
	{
		start.x = origin.x + i*(boxWidth+boxPadding);
		end.x = start.x + boxWidth;
		TheWindowManager->winDrawImage( fillSquare, 
																	start.x, start.y,
																	end.x, end.y );
	}
	for (i=numSelectedBoxes; i<numBoxes; ++i)
	{
		start.x = origin.x + i*(boxWidth+boxPadding);
		end.x = start.x + boxWidth;
		TheWindowManager->winDrawImage( blankSquare, 
																	start.x, start.y,
																	end.x, end.y );
	}
}


// W3DGadgetHorizontalSliderImageDraw =========================================
/** Draw horizontal slider with user supplied images */
//=============================================================================
void W3DGadgetHorizontalSliderImageDrawA( GameWindow *window, 
																				 WinInstanceData *instData )
{
	const Image *leftImageLeft, *rightImageLeft, *centerImageLeft, *smallCenterImageLeft;
	const Image *leftImageRight, *rightImageRight, *centerImageRight, *smallCenterImageRight;
	CtorCoord origin, size, start, end;
	Int xOffset, yOffset;
	Int i;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	SliderData *s = (SliderData *)window->winGetUserData();
	Int transPos = (s->numTicks * (s->position - s->minVal)) + HORIZONTAL_SLIDER_THUMB_WIDTH/2;
	IRegion2D clipLeft, clipRight;

	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	// get the right images
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		leftImageRight = leftImageLeft					= GadgetSliderGetDisabledImageLeft( window );
		rightImageRight = rightImageLeft				= GadgetSliderGetDisabledImageRight( window );
		centerImageRight = centerImageLeft				= NULL;
		smallCenterImageRight = smallCenterImageLeft	= NULL;

	}  // end if, disabled
	else
	{

		leftImageLeft					= GadgetSliderGetHiliteImageLeft( window );
		rightImageLeft				= GadgetSliderGetHiliteImageRight( window );
		centerImageLeft				= GadgetSliderGetHiliteImageCenter( window );
		smallCenterImageLeft	= GadgetSliderGetHiliteImageSmallCenter( window );

		leftImageRight					= GadgetSliderGetEnabledImageLeft( window );
		rightImageRight				= GadgetSliderGetEnabledImageRight( window );
		centerImageRight				= GadgetSliderGetEnabledImageCenter( window );
		smallCenterImageRight	= GadgetSliderGetEnabledImageSmallCenter( window );

	}  // end else, enabled

	// sanity, we need to have these images to make it look right
	if( leftImageLeft == NULL || rightImageLeft == NULL || 
			centerImageLeft == NULL || smallCenterImageLeft == NULL ||
			leftImageRight == NULL || rightImageRight == NULL || 
			centerImageRight == NULL || smallCenterImageRight == NULL )
		return;

	// get image sizes for the ends
	CtorCoord leftSize, rightSize;
	leftSize.x = leftImageLeft->getImageWidth();
	leftSize.y = leftImageLeft->getImageHeight();
	rightSize.x = rightImageLeft->getImageWidth();
	rightSize.y = rightImageLeft->getImageHeight();

	// get two key points used in the end drawing
	CtorCoord leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y  + size.y - leftSize.y + yOffset;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;

	// how many whole repeating pieces will fit in that width
	pieces = centerWidth / centerImageLeft->getImageWidth();

	// draw the pieces
	start.x = leftEnd.x;
	start.y = origin.y + size.y - leftSize.y + yOffset;
	end.y =origin.y + size.y + yOffset;
	
	clipLeft.lo.x = origin.x;
	clipLeft.lo.y = rightStart.y;
	clipLeft.hi.y = leftEnd.y;
	clipLeft.hi.x = origin.x + transPos;
	clipRight.lo.x = origin.x + transPos;
	clipRight.lo.y = rightStart.y;
	clipRight.hi.y = leftEnd.y;
	clipRight.hi.x = origin.x + size.x;

	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + centerImageLeft->getImageWidth();
		((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipLeft);
		TheWindowManager->winDrawImage( centerImageLeft, 
																		start.x, start.y,
																		end.x, end.y );
		((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipRight);
		TheWindowManager->winDrawImage( centerImageRight, 
																		start.x, start.y,
																		end.x, end.y );
		start.x += centerImageLeft->getImageWidth();

	}  // end for i
	
	//
	// how many small repeating pieces will fit in the gap from where the
	// center repeating bar stopped and the right image, draw them
	// and overlapping underneath where the right end will go
	//
	centerWidth = rightStart.x - start.x;
	pieces = centerWidth / smallCenterImageLeft->getImageWidth() + 1;
	end.y = leftEnd.y;
	for( i = 0; i < pieces; i++ )
	{

		end.x = start.x + smallCenterImageLeft->getImageWidth();
		((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipLeft);
		TheWindowManager->winDrawImage( smallCenterImageLeft,
																		start.x, start.y,
																		end.x, end.y );
		((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipRight);
		TheWindowManager->winDrawImage( smallCenterImageRight,
																		start.x, start.y,
																		end.x, end.y );
		start.x += smallCenterImageLeft->getImageWidth();

	}  // end for i
	
	// draw left end
	start.x = origin.x + xOffset;
	start.y = rightStart.y;
	end = leftEnd;
	((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipLeft);
	TheWindowManager->winDrawImage(leftImageLeft, start.x, start.y, end.x, end.y);
	((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipRight);
	TheWindowManager->winDrawImage(leftImageRight, start.x, start.y, end.x, end.y);
	// draw right end
	start = rightStart;
	end.x = start.x + rightSize.x;
	end.y = leftEnd.y;
	((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipLeft);
	TheWindowManager->winDrawImage(rightImageLeft, start.x, start.y, end.x, end.y);
	((BFMESliderDisplay *)TheDisplay)->setClipRegion(&clipRight);
	TheWindowManager->winDrawImage(rightImageRight, start.x, start.y, end.x, end.y);

	((BFMESliderDisplay *)TheDisplay)->enableClipping(FALSE);
}  // end W3DGadgetHorizontalSliderImageDrawA

// W3DGadgetHorizontalSliderImageDraw =========================================
/** Draw horizontal slider with user supplied images */
//=============================================================================
void W3DGadgetHorizontalSliderImageDrawB( GameWindow *window, 
																				 WinInstanceData *instData )
{
	const Image *fillSquare, *blankSquare, *highlightSquare;//, *progressArrow;
	CtorCoord origin, size, start, end;
	Int xOffset, yOffset;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	SliderData *s = (SliderData *)window->winGetUserData();
	
	Real xMulti = 1.0f;
	Real yMulti = 1.0f;
	if( BitTest( window->winGetStatus(), WIN_STATUS_BFME_UNSCALED ) == FALSE )
	{
		xMulti = INT_TO_REAL(((BFMESliderDisplay *)TheDisplay)->getWidth()) / 800;
		yMulti = INT_TO_REAL(((BFMESliderDisplay *)TheDisplay)->getHeight()) / 600;
	}
	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	UnicodeString tooltip, tmp;
	tooltip.format(L"mult:%g/%g, img offset:%d,%d", xMulti, yMulti, xOffset, yOffset);

	tmp.format(L"\norigin: %d,%d size:%d,%d", origin.x, origin.y, size.x, size.y);
	tooltip.concat(tmp);

	tmp.format(L"\ns= %d <--> %d, numTicks=%g, pos = %d", s->minVal, s->maxVal, s->numTicks, s->position);
	tooltip.concat(tmp);

	if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		highlightSquare					= GadgetSliderGetHiliteImageLeft( window );
		CtorCoord backgroundStart, backgroundEnd;
		backgroundStart.x = origin.x - (highlightSquare->getImageWidth() * xMulti)/2;
		backgroundStart.y = origin.y + (highlightSquare->getImageHeight() *yMulti)/3;
		backgroundEnd.y = backgroundStart.y + highlightSquare->getImageHeight()* yMulti;
		backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;

		tmp.format(L"\nHighlighted: (%d,%d) -> (%d,%d), step %d/%g, full %d/%d", backgroundStart.x, backgroundStart.y,
			backgroundEnd.x, backgroundEnd.y, highlightSquare->getImageWidth(), highlightSquare->getImageWidth() * xMulti,
			origin.x, size.x);
		tooltip.concat(tmp);

		while(backgroundStart.x < origin.x + size.x)
		{
			TheWindowManager->winDrawImage( highlightSquare, 
																		backgroundStart.x, backgroundStart.y,
																		backgroundEnd.x, backgroundEnd.y );
			backgroundStart.x = backgroundEnd.x;
			backgroundEnd.x = backgroundStart.x + highlightSquare->getImageWidth() * xMulti;
		}		
		tmp.format(L"\n  bsX = %d, beX = %d (%d < %d+%d or %d?)", backgroundStart.x, backgroundEnd.x,
			backgroundStart.x, origin.x, size.x, origin.x + size.x);
		tooltip.concat(tmp);
	}

	fillSquare = GadgetSliderGetDisabledImageLeft( window );
	start.x = origin.x;
	start.y = origin.y;
	end.y = start.y + fillSquare->getImageHeight() * yMulti;
	end.x	= start.x + fillSquare->getImageWidth()* xMulti;

	tmp.format(L"\ntop: start=%d,%d, end=%d,%d", start.x, start.y, end.x, end.y);
	tooltip.concat(tmp);

	while(start.x <= origin.x + (s->numTicks * (s->position - s->minVal)) && end.x < origin.x + size.x && s->position != s->minVal)
	{
		TheWindowManager->winDrawImage( fillSquare, 
																		start.x, start.y,
																		end.x, end.y );
		start.x = end.x + 2;
		end.x	= start.x + fillSquare->getImageWidth()* xMulti;

	}

	blankSquare	= GadgetSliderGetDisabledImageRight( window );
	end.x	= start.x + blankSquare->getImageWidth()* xMulti;

	while(end.x < origin.x + size.x )
	{
		TheWindowManager->winDrawImage( blankSquare, 
																		start.x, start.y,
																		end.x, end.y );
		start.x = end.x + 2;
		end.x	= start.x + blankSquare->getImageWidth()* xMulti;
	}

	instData->setTooltipText(tooltip);

}  // end W3DGadgetHorizontalSliderImageDrawB
