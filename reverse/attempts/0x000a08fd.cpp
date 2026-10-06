// ?drawStaticTextText@@YAXPAVGameWindow@@PAVWinInstanceData@@HH@Z
// partial score=0.92 date=2026-10-06
// cl: /O1 /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: W3DStaticText.cpp ////////////////////////////////////////////////////
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
// File name: W3DStaticText.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation of the static text GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/GlobalData.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetStaticText.h"
#include "W3DDevice/GameClient/W3DGameWindow.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////
//enum { DRAW_BUF_LEN = 2048 };
//static WideChar drawBuf[ DRAW_BUF_LEN ];

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// drawStaticTextText =========================================================
// byte-exact reconstruction: ?drawStaticTextText@@YAXPAVGameWindow@@PAVWinInstanceData@@HH@Z 0x000A08FD 341B
// evidence: BFME1 donor W3DStaticTextDraw_Thunk.cpp drawStaticTextText (literal 7, unconditional Y, setTextColor+draw); caller W3DGadgetStaticTextImageDraw 0x000A0B6A; DisplayString slots +0x0C/+0x20/+0x24/+0x28/+0x38/+0x3C/+0x4C/+0x50; GlobalData hotkey at +0xBA0 via TheGlobalData; TextData {text+0 centered+4}
/** Draw the text for a static text window */
// BFME2 retail DisplayString vtable layout (witnessed from 0x000A08FD).
class BfmeStaticDisplayString
{
public:
	virtual void unused00();								///< +0x00
	virtual void unused01();								///< +0x04
	virtual void unused02();								///< +0x08
	virtual Int getTextLength(void);						///< +0x0C
	virtual void unused04();								///< +0x10
	virtual void unused05();								///< +0x14
	virtual void unused06();								///< +0x18
	virtual void unused07();								///< +0x1C
	virtual void setWordWrap(Int wordWrap);					///< +0x20
	virtual void setWordWrapCentered(Bool centered);		///< +0x24
	virtual void setTextColor(Color color, Color drop);		///< +0x28
	virtual void unused11();								///< +0x2C
	virtual void unused12();								///< +0x30
	virtual void unused13();								///< +0x34
	virtual void draw(Int x, Int y, Int a, Int b);			///< +0x38
	virtual void getSize(Int *width, Int *height);			///< +0x3C
	virtual void unused16();								///< +0x40
	virtual void unused17();								///< +0x44
	virtual void unused18();								///< +0x48
	virtual void setUseHotkey(Bool use, Color color);		///< +0x4C
	virtual void setClipRegion(IRegion2D *region);			///< +0x50
};

struct BfmeStaticTextData
{
	BfmeStaticDisplayString *text;							///< +0x00
	Bool centered;											///< +0x04
};

struct BfmeStaticGlobalData
{
	unsigned char pad[0xBA0];								///< retail hotkey offset
	Color hotKeyColor;										///< retail this+0xBA0
};
//=============================================================================
static void drawStaticTextText( GameWindow *window, WinInstanceData *instData,
																Color textColor, Color textDropColor )
{
	Int textHeight, textWidth, wordWrap;
	BfmeStaticDisplayString *text;
	BfmeStaticTextData *tData;
	ICoord2D origin, size, textPos;
	IRegion2D clipRegion;

	tData = (BfmeStaticTextData *)window->winGetUserData();
	text = tData->text;
	// sanity
	if( text == NULL )
		return;
	if( text->getTextLength() == 0 )
		return;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// Set the text Wrap width
	wordWrap = size.x - 10;
	text->setWordWrap(wordWrap);
	if( BitTest(window->winGetStatus(), WIN_STATUS_WRAP_CENTERED)		)
		text->setWordWrapCentered(TRUE);
	else
		text->setWordWrapCentered(FALSE);
	if( BitTest( window->winGetStatus(), WIN_STATUS_HOTKEY_TEXT ) && TheGlobalData)
		text->setUseHotkey(TRUE, ((BfmeStaticGlobalData *)TheGlobalData)->hotKeyColor);
	else
		text->setUseHotkey(FALSE, 0);


	// how much space will this text take up
	text->getSize( &textWidth, &textHeight );

	//Init the clip region
	clipRegion.lo.x = origin.x ;
	clipRegion.lo.y = origin.y ;
	clipRegion.hi.x = origin.x + size.x ;
	clipRegion.hi.y = origin.y + size.y;

	// horizontal centering?
	if( tData->centered )
	{
		textPos.x = origin.x + ((size.x / 2) - (textWidth / 2));
	}
	else
	{
		textPos.x = origin.x + 7;
	}

	// vertical centering is unconditional in BFME
	textPos.y = origin.y + ((size.y / 2) - (textHeight / 2));

	// draw the text
	text->setClipRegion(&clipRegion);
	text->setTextColor(textColor, textDropColor);
	text->draw(textPos.x, textPos.y, 1, 1);

}  // end drawStaticTextText

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetStaticTextDraw ====================================================
/** Draw colored text field using standard graphics */
//=============================================================================
void W3DGadgetStaticTextDraw( GameWindow *window, WinInstanceData *instData )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Color backColor, backBorder, textColor, textOutlineColor;
	ICoord2D size, origin, start, end;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the colors we will use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		backColor					= GadgetStaticTextGetDisabledColor( window );
		backBorder				= GadgetStaticTextGetDisabledBorderColor( window );
		textColor					= window->winGetDisabledTextColor();
		textOutlineColor	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else
	{

		backColor					= GadgetStaticTextGetEnabledColor( window );
		backBorder				= GadgetStaticTextGetEnabledBorderColor( window );
		textColor					= window->winGetEnabledTextColor();
		textOutlineColor	= window->winGetEnabledTextBorderColor();

	}  // end else, enabled

	// draw the back border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH, 
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the back fill area
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );
	}  // end if

	// draw the text
  if( tData->text && (textColor != WIN_COLOR_UNDEFINED) )
		drawStaticTextText( window, instData, textColor, textOutlineColor );

  

}  // end W3DGadgetStaticTextDraw

// W3DGadgetStaticTextImageDraw ===============================================
/** Draw colored text field with user supplied images */
//=============================================================================
void W3DGadgetStaticTextImageDraw( GameWindow *window, WinInstanceData *instData )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Color textColor, textOutlineColor;
	ICoord2D size, origin, start, end;
	const Image *image;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the colors we will use
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		image							= GadgetStaticTextGetDisabledImage( window );
		textColor					= window->winGetDisabledTextColor();
		textOutlineColor	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else
	{

		image							= GadgetStaticTextGetEnabledImage( window );
		textColor					= window->winGetEnabledTextColor();
		textOutlineColor	= window->winGetEnabledTextBorderColor();

	}  // end else, enabled

	// draw the back image
	if( image )
	{

		start.x = origin.x + instData->m_imageOffset.x;
		start.y = origin.y + instData->m_imageOffset.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage( image, start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
  if( tData->text && (textColor != WIN_COLOR_UNDEFINED) )
		drawStaticTextText( window, instData, textColor, textOutlineColor );

  

}  // end W3DGadgetStaticTextImageDraw

