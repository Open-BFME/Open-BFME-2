// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: W3DComboBox.cpp ///////////////////////////////////////////////////////
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
// File name: W3DComboBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the Combo box control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "../../../../../../../reference/shims/w3ddisplaystring/GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// BFME calls setTextColor at vtable +0x28 and draw at vtable +0x38.
class BfmeComboDisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont();
	virtual void unused08();
	virtual void unused09();
	virtual void setTextColor(Color color, Color border);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int x, Int y, Int color, Int border);
};

inline const Image *bfmeComboEnabledImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0x48);
}

inline const Image *bfmeComboDisabledImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0xb4);
}

inline const Image *bfmeComboHiliteImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0x120);
}

inline Color bfmeComboEnabledColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x4c);
}

inline Color bfmeComboEnabledBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x50);
}

inline Color bfmeComboDisabledColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0xb8);
}

inline Color bfmeComboDisabledBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0xbc);
}

inline Color bfmeComboHiliteColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x124);
}

inline Color bfmeComboHiliteBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x128);
}

// Keep the existing inline helper rows emitted while this body reads BFME's shifted data.
static const Image *(*s_bfmeKeepComboDisabledImage)(GameWindow *) = GadgetComboBoxGetDisabledImage;
static const Image *(*s_bfmeKeepComboHiliteImage)(GameWindow *) = GadgetComboBoxGetHiliteImage;
static Color (*s_bfmeKeepComboEnabledColor)(GameWindow *) = GadgetComboBoxGetEnabledColor;
static Color (*s_bfmeKeepComboEnabledBorderColor)(GameWindow *) = GadgetComboBoxGetEnabledBorderColor;
static Color (*s_bfmeKeepComboDisabledColor)(GameWindow *) = GadgetComboBoxGetDisabledColor;
static Color (*s_bfmeKeepComboDisabledBorderColor)(GameWindow *) = GadgetComboBoxGetDisabledBorderColor;
static Color (*s_bfmeKeepComboHiliteColor)(GameWindow *) = GadgetComboBoxGetHiliteColor;
static Color (*s_bfmeKeepComboHiliteBorderColor)(GameWindow *) = GadgetComboBoxGetHiliteBorderColor;

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetComboBoxDraw =======================================================
/** Draw colored list box using standard graphics */
//=============================================================================
void W3DGadgetComboBoxDraw( GameWindow *window, WinInstanceData *instData )
{
	Int width, height, fontHeight, x, y;
	Color background, border, titleColor, titleBorder;
//	ComboBoxData *combo = (ComboBoxData *)window->winGetUserData();
	ICoord2D size;
	BfmeComboDisplayString *title = (BfmeComboDisplayString *)instData->getTextDisplayString();

	// get window position and size
	window->winGetScreenPosition( &x, &y );
	window->winGetSize( &size.x, &size.y );

	// get font height
	fontHeight = TheWindowManager->winFontHeight( instData->getFont() );

	// alias width and height from size
	width = size.x;
	height = size.y;

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		background		= bfmeComboDisabledColor( window );
		border				= bfmeComboDisabledBorderColor( window );
		titleColor		= window->winGetDisabledTextColor();
		titleBorder		= window->winGetDisabledTextBorderColor();
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		background		= bfmeComboHiliteColor( window );
		border				= bfmeComboHiliteBorderColor( window );
		titleColor		= window->winGetHiliteTextColor();
		titleBorder		= window->winGetHiliteTextBorderColor();
	}  // end else if, hilited
	else
	{
		background		= bfmeComboEnabledColor( window );
		border				= bfmeComboEnabledBorderColor( window );
		titleColor		= window->winGetEnabledTextColor();
		titleBorder		= window->winGetEnabledTextBorderColor();
	}  // end else, enabled

	// Draw the title
	if( title && title->getTextLength() )
	{
	
		// set the font of this text to that of the window if not already
		if( title->getFont() != window->winGetFont() )
			title->setFont( window->winGetFont() );
			
		// draw the text
		title->setTextColor( titleColor, titleBorder );
		title->draw( x + 1, y, 1, 1 );

		y += fontHeight + 1;
		height -= fontHeight + 1;

	}  // end if

	// draw the back border
	if( border != WIN_COLOR_UNDEFINED )
		TheWindowManager->winOpenRect( border, WIN_DRAW_LINE_WIDTH,
																	 x, y, x + width, y + height );

	// draw background
	if( background != WIN_COLOR_UNDEFINED )
		TheWindowManager->winFillRect( background, WIN_DRAW_LINE_WIDTH,
																	 x + 1, y + 1, 
																	 x + width - 1, y + height - 1 );

}  // end W3DGadgetComboBoxDraw

// W3DGadgetComboBoxImageDraw ==================================================
/** Draw combo box with user supplied images */
//=============================================================================
void W3DGadgetComboBoxImageDraw( GameWindow *window, WinInstanceData *instData )
{
	Int width, height, x, y;
	const Image *image;
	ICoord2D size;
	Color titleColor, titleBorder;
	BfmeComboDisplayString *title = (BfmeComboDisplayString *)instData->getTextDisplayString();

	// get window position and size
	window->winGetScreenPosition( &x, &y );
	window->winGetSize( &size.x, &size.y );

	// save off width and height so we can change them
	width = size.x;
	height = size.y;

	// get the image
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		image				= bfmeComboDisabledImage( window );
		titleColor	= window->winGetDisabledTextColor();
		titleBorder = window->winGetDisabledTextBorderColor();
	}
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		image				= bfmeComboHiliteImage( window );
		titleColor	= window->winGetHiliteTextColor();
		titleBorder = window->winGetHiliteTextBorderColor();
	}
	else
	{
		image				= bfmeComboEnabledImage( window );
		titleColor	= window->winGetEnabledTextColor();
		titleBorder = window->winGetEnabledTextBorderColor();
	}

	// draw the back image
	if( image )
	{
		ICoord2D start, end;

		start.x = x + instData->m_imageOffset.x;
		start.y = y + instData->m_imageOffset.y;
		end.x = start.x + width;
		end.y = start.y + height;
		TheWindowManager->winDrawImage( image, 
																		start.x, start.y, 
																		end.x, end.y );

	}  // end if

	// Draw the title
	if( title && title->getTextLength() )
	{

		// set font to font of the window if not already
		if( title->getFont() != window->winGetFont() )
			title->setFont( window->winGetFont() );

		// draw the text
		title->setTextColor( titleColor, titleBorder );
		title->draw( x + 1, y, 1, 1 );

		y += TheWindowManager->winFontHeight( instData->getFont() );
		height -= TheWindowManager->winFontHeight( instData->getFont() ) + 1;

	}  // end if


}  // end W3DGadgetComboBoxImageDraw

// BFME's image combo box keeps its drop-down button at user data +4 and its
// list box at +8 (GadgetImageComboBox.cpp).
struct BfmeImageComboBoxData
{
	Int maxListHeight;
	GameWindow *dropDownButton;
	GameWindow *listBox;
};

// BFME's list box rows are 16 bytes with the cells at +8; a cell holds its
// color at +8, its image at +0xC and its size overrides at +0x14/+0x18.
struct BfmeListEntryCell
{
	Int cellType;
	Int unknown04;
	Color color;
	void *data;
	void *userData;
	Int width;
	Int height;
};

struct BfmeListEntryRow
{
	Int listHeight;
	Int height;
	BfmeListEntryCell *cell;
	Int unknown0C;
};

struct BfmeListboxData
{
	char unknown00[ 0x18 ];
	BfmeListEntryRow *listData;
};

// The one-pointer combo box wrapper of MpGameSetupSlots.cpp, under its
// address name. Its constructor is the ICF-folded pointer store 0x0007B719
// and its destructor the shared empty 0x000B3FD0, both pinned by address;
// the user data accessors are inline (each call reads the user data again).
class Rva00323674
{
public:
	Rva00323674( GameWindow *window );
	~Rva00323674();
	Int rva00323674() const;  // the selected list position
	GameWindow *getDropDownButton() const { return ((BfmeImageComboBoxData *)m_window->winGetUserData())->dropDownButton; }
	GameWindow *getListBox() const { return ((BfmeImageComboBoxData *)m_window->winGetUserData())->listBox; }

	GameWindow *m_window;
};

// W3DGadgetImageComboBoxDraw =================================================
/** Draw the selected entry's image of an image combo box */
//=============================================================================
// 0x000A24BA (336B), BFME's own callback: the W3D function lexicon pairs its
// name (0x00BC4AD8) with it at 0x009B3DA0. It centers the selected list row's
// first cell image in the box left of the drop-down button, leaving out an
// open list's height. It needs /O1 (the EH prolog helper), which the unit's
// two Zero Hour draws compile to the same bytes under.
void W3DGadgetImageComboBoxDraw( GameWindow *window, WinInstanceData *instData )
{
	ICoord2D origin, size;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	Rva00323674 combo( window );
	Int selected = combo.rva00323674();
	if( selected >= 0 )
	{
		GameWindow *listBox = combo.getListBox();
		BfmeListEntryRow *row = &((BfmeListboxData *)combo.getListBox()->winGetUserData())->listData[ selected ];
		const Image *image = (const Image *)row->cell->data;
		Int width = row->cell->width;
		Int height = row->cell->height;
		if( width < 0 )
			width = image->getImageWidth();
		if( height < 0 )
			height = image->getImageHeight();

		// an open drop down list counts in the window's size
		if( BitTest( listBox->winGetStatus(), WIN_STATUS_HIDDEN ) == FALSE )
		{
			Int listWidth, listHeight;
			listBox->winGetSize( &listWidth, &listHeight );
			size.y -= listHeight;
		}

		ICoord2D buttonSize;
		buttonSize.x = 0;
		buttonSize.y = 0;
		if( !combo.getDropDownButton()->winIsHidden() )
			combo.getDropDownButton()->winGetSize( &buttonSize.x, &buttonSize.y );

		Int y = origin.y + (size.y - height) / 2;
		Int x = (origin.x + origin.x + size.x - buttonSize.x - width) / 2;
		Color color = row->cell->color;
		TheWindowManager->winDrawImage( image, x, y, x + width, y + height, color );
	}  // end if

}  // end W3DGadgetImageComboBoxDraw
