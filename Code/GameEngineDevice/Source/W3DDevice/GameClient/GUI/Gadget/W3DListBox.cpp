// cl: /O1 /G7 /arch:SSE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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


// FILE: W3DListBox.cpp ///////////////////////////////////////////////////////
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
// File name: W3DListBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the list box control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#define GadgetListBoxGetEnabledSelectedItemColor \
	bfmeZhGadgetListBoxGetEnabledSelectedItemColor
#include <stdlib.h>

#include "../../../../../../../reference/shims/w3ddisplaystring/GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "W3DDevice/GameClient/W3DGadget.h"


class Display
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03(); virtual void pad04(); virtual void pad05();
	virtual void pad06(); virtual void pad07(); virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15(); virtual void pad16(); virtual void pad17();
	virtual void pad18(); virtual void pad19(); virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27(); virtual void pad28(); virtual void pad29();
	virtual void pad30(); virtual void pad31(); virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39(); virtual void pad40(); virtual void pad41();
	virtual void setClipRegion(IRegion2D *region);
	virtual Bool isClippingEnabled();
	virtual void enableClipping(Bool onoff);
};
extern Display *TheDisplay;


#undef GadgetListBoxGetEnabledSelectedItemColor

// The donor inline reads enabledDrawData[1].color at +0x58. Retail's body at
// 0x00698A20 reads [window+0x54], so keep its target-proven access separate
// from the donor layout while retaining the donor identity as provenance.
Color GadgetListBoxGetEnabledSelectedItemColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x54);
}

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

class BfmeListDisplayString
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
	virtual void setWordWrap(Int width);
	virtual void unused09();
	virtual void setTextColor(Color color, Color border);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int x, Int y, Int color, Int border);
 virtual void getSize(Int *width,Int *height);
 virtual void unused16();virtual void unused17();virtual void unused18();virtual void unused19();
 virtual void setClipRegion(IRegion2D *region);
};

// Target-observed list and cell fields; ZH names are semantic provenance.
struct BfmeListEntryCell {
 Int cellType,alignment;Color color;void *data,*userData;Int width,height;
};
struct BfmeListEntryRow {
 Int listHeight,height;BfmeListEntryCell *cell;Int unreconstructed_0c;
};
struct BfmeListboxData {
 Short listLength,columns;Int *columnWidthPercentage;
 Bool autoScroll,autoPurge,scrollBar,multiSelect;
 unsigned char unreconstructed_0c[4];Bool hideSelection;
 unsigned char unreconstructed_11;Bool useAlternate,hasAlternate;
 Int *columnWidth;BfmeListEntryRow *listData;
 GameWindow *upButton,*downButton,*slider;
 Int totalHeight;Short endPos,insertPos;
 Int alternatePos,selectPos;Int *selections;
 Short displayHeight;UnsignedInt doubleClickTime;Short displayPos;
};

inline const Image *bfmeListEnabledImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0x48);
}

inline const Image *bfmeListDisabledImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0xb4);
}

inline const Image *bfmeListHiliteImage(GameWindow *window)
{
	return *(const Image **)((const char *)window + 0x120);
}

inline Color bfmeListEnabledColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x4c);
}

inline Color bfmeListEnabledBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x50);
}

inline Color bfmeListDisabledColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0xb8);
}

inline Color bfmeListDisabledBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0xbc);
}

inline Color bfmeListHiliteColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x124);
}

inline Color bfmeListHiliteBorderColor(GameWindow *window)
{
	return *(const Color *)((const char *)window + 0x128);
}

// Keep the existing inline helper rows emitted while this body reads BFME's shifted data.
static const Image *(*s_bfmeKeepListDisabledImage)(GameWindow *) = GadgetListBoxGetDisabledImage;
static const Image *(*s_bfmeKeepListHiliteImage)(GameWindow *) = GadgetListBoxGetHiliteImage;

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// drawHiliteBar ==============================================================
/** Draw image for the hilite bar */
//=============================================================================
static void drawHiliteBar(const Image *left, const Image *right,
	const Image *center,
	Int startX, Int startY,
	Int endX, Int endY)
{
	ICoord2D barWindowSize;
	Int xOffset = 0, yOffset = 0;
	ICoord2D start, end;
	Int i;
	IRegion2D clipRegion;

	barWindowSize.x = endX - startX;
	barWindowSize.y = endY - startY;

	if (barWindowSize.x < left->getImageWidth() + right->getImageWidth())
		barWindowSize.x = left->getImageWidth() + right->getImageWidth();

	ICoord2D leftSize, rightSize;
	leftSize.x = left->getImageWidth();
	leftSize.y = left->getImageHeight();
	rightSize.x = right->getImageWidth();
	rightSize.y = right->getImageHeight();

	ICoord2D leftEnd, rightStart;
	leftEnd.x = startX + leftSize.x + xOffset;
	leftEnd.y = startY + barWindowSize.y + yOffset;
	rightStart.x = startX + barWindowSize.x - rightSize.x + xOffset;
	rightStart.y = startY + yOffset;

	Int centerWidth, pieces;

	centerWidth = rightStart.x - leftEnd.x;

	pieces = centerWidth / center->getImageWidth();

	start.x = leftEnd.x;
	start.y = startY + yOffset;
	end.y = start.y + barWindowSize.y;
	for (i = 0; i < pieces; i++)
	{
		end.x = start.x + center->getImageWidth();
		TheWindowManager->winDrawImage(center,
			start.x, start.y,
			end.x, end.y);
		start.x += center->getImageWidth();
	}

	clipRegion.lo.x = leftEnd.x;
	clipRegion.lo.y = startY + yOffset;
	clipRegion.hi.x = leftEnd.x + centerWidth;
	clipRegion.hi.y = start.y + barWindowSize.y;
	TheDisplay->setClipRegion(&clipRegion);
	TheDisplay->enableClipping(FALSE);
	start.x = startX + xOffset;
	start.y = startY + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(left, start.x, start.y, end.x, end.y);

	start = rightStart;
	// Preserve the width as a separate value for native LEA operand order.
	end.x = start.x + (rightSize.x ? rightSize.x : rightSize.x);
	end.y = start.y + barWindowSize.y;
	TheWindowManager->winDrawImage(right, start.x, start.y, end.x, end.y);
}

// drawListBoxText ============================================================
/** Draw the text for a listbox */
//=============================================================================
static void drawListBoxText( GameWindow *window, WinInstanceData *instData,
													 Int x, Int y, Int width, Int height,
													 Bool useImages )
{
	Int drawY;
	BfmeListboxData *list = (BfmeListboxData *)window->winGetUserData();
	Int i;
	Bool selected;
	Int listLineHeight;
	Color textColor;
//	W3DGameWindow *w3dWindow = static_cast<W3DGameWindow *>(window);
	IRegion2D clipRegion;
	ICoord2D start, end;

	//
	// save the clipping information region cause we're going to use it here
	// in drawing the text
	//
//	TheWindowManager->winGetClipRegion( &clipRegion );

	// set clip region to inside the outline box.
//	TheWindowManager->winSetClipRegion( x, y, width, height );

	// set the text clip region to the outline of the listbox
	clipRegion.lo.x = x + 1;
	clipRegion.lo.y = y -3;
	clipRegion.hi.x = x + width - 1;
	clipRegion.hi.y = y + height - 1;

	drawY = y - list->displayPos;

	for( i = 0; ; i++ )
	{

		if( i > 0 )
			if( list->listData[(i - 1)].listHeight > 
					(list->displayPos + list->displayHeight) )
				break;

		if( i == list->endPos )
			break;

		if( list->listData[i].listHeight < list->displayPos )
		{
			drawY += (list->listData[i].height + 1);
			continue;
		}

		listLineHeight = list->listData[i].height + 1;
		//textColor =  list->listData[i].textColor;
		selected = FALSE;

		if( list->multiSelect )
		{
			Int j = 0;

			while( list->selections[j] >= 0 )
			{
				if( i == list->selections[j] )
				{
					selected = TRUE;
					break;
				}

				j++;
			}
		}
		else
		{
			if(list->useAlternate && list->hasAlternate) {
                if(i==list->alternatePos)selected=TRUE;
            }else if(i==list->selectPos)selected=TRUE;
		}

		// this item is selected, draw the selection color or image
		if( selected && !list->hideSelection )
		{
			
			if( useImages )
			{
				const Image *left, *right, *center, *smallCenter;

				if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
				{

					left				= *(const Image **)((const char *)window + 0xc0);
					right				= *(const Image **)((const char *)window + 0xcc);
					center			= *(const Image **)((const char *)window + 0xd8);
					smallCenter = *(const Image **)((const char *)window + 0xe4);

				}  // end if
				else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
				{

					left				= *(const Image **)((const char *)window + 0x12c);
					right				= *(const Image **)((const char *)window + 0x138);
					center			= *(const Image **)((const char *)window + 0x144);
					smallCenter = *(const Image **)((const char *)window + 0x150);
				
				}  // end else if
				else
				{

					left				= *(const Image **)((const char *)window + 0x54);
					right				= *(const Image **)((const char *)window + 0x60);
					center			= *(const Image **)((const char *)window + 0x6c);
					smallCenter = *(const Image **)((const char *)window + 0x78);

				}  // end else

				// draw select image across area

				//
				// where are we going to draw ... taking into account the clipping
				// region of the edge of the listbox
				//
				start.x = x;
				start.y = drawY;
				end.x = start.x + width;
				end.y = start.y + listLineHeight;

				if( end.y > clipRegion.hi.y )
					end.y = clipRegion.hi.y;
				if( start.y < clipRegion.lo.y )
					start.y = clipRegion.lo.y;

				if( left && right && center && smallCenter )
					drawHiliteBar( left, right, center, start.x + 1, start.y, end.x , end.y );
                else if(center)
                  TheWindowManager->winDrawImage(center,start.x+1,start.y,end.x,end.y);

			}  // end if, use images
			else
			{
				Color selectColor = WIN_COLOR_UNDEFINED,
							selectBorder = WIN_COLOR_UNDEFINED;

				if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
				{
					selectColor  = *(const Color *)((const char *)window + 0xc4);
					selectBorder = *(const Color *)((const char *)window + 0xc8);
				}  // end if, disabled
				else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
				{
					selectColor  = *(const Color *)((const char *)window + 0x130);
					selectBorder = *(const Color *)((const char *)window + 0x134);
				}  // end else if, hilited
				else
				{
					selectColor  = *(const Color *)((const char *)window + 0x58);
					selectBorder = *(const Color *)((const char *)window + 0x5c);
				}  // end else, enabled

				// draw border

				//
				// where are we going to draw ... taking into account the clipping
				// region of the edge of the listbox
				//
				start.x = x;
				start.y = drawY;
				end.x = start.x + width;
				end.y = start.y + listLineHeight;

				if( end.y > clipRegion.hi.y )
					end.y = clipRegion.hi.y;
				if( start.y < clipRegion.lo.y )
					start.y = clipRegion.lo.y;

				if( selectBorder != WIN_COLOR_UNDEFINED )
					TheWindowManager->winOpenRect( selectBorder,	
																				 WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y,
																				 end.x, end.y );

				// draw filled inner rect

				//
				// where are we going to draw ... taking into account the clipping
				// region of the edge of the listbox
				//
				start.x = x + 1;
				start.y = drawY + 1;
				end.x = start.x + width - 2;
				end.y = start.y + listLineHeight - 2;

				if( end.y > clipRegion.hi.y )
					end.y = clipRegion.hi.y;
				if( start.y < clipRegion.lo.y )
					start.y = clipRegion.lo.y;

				if( selectColor != WIN_COLOR_UNDEFINED )
					TheWindowManager->winFillRect( selectColor,
																				 WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y,
																				 end.x, end.y );

			}  // end else, draw selection with colors

		}  // end if

		

		
		Color dropColor = TheWindowManager->winMakeColor( 0, 0, 0, 255 );
		BfmeListDisplayString *string;

		BfmeListEntryCell *cells = list->listData[i].cell;
		Int columnX = x;
		IRegion2D columnRegion;
		if( cells )
		{
			// loop through all the cells
			for( Int j = 0; j < list->columns; j++ )
			{
				// setup the Clip Region size

				Int cellColumnWidth;
                columnRegion.lo.x = columnX;
				columnRegion.lo.y = drawY;
				if(list->columns == 1 && list->slider && list->slider->winIsHidden())
					cellColumnWidth=width-3;
				else
					cellColumnWidth=list->columnWidth[j];
                columnRegion.hi.x=columnX+cellColumnWidth;
				columnRegion.hi.y = drawY + list->listData[i].height;
				if(columnRegion.lo.y < clipRegion.lo.y )
					columnRegion.lo.y = clipRegion.lo.y;
				if( columnRegion.hi.y > clipRegion.hi.y )
					columnRegion.hi.y = clipRegion.hi.y;
				
				// Display the Text Case;
				if(cells[j].cellType == LISTBOX_TEXT)
				{
					textColor = cells[j].color;
					string = (BfmeListDisplayString *)cells[j].data;
					if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) == TRUE )
                      string->setWordWrap(0);
                    if(string->getFont()!=window->winGetFont())string->setFont(window->winGetFont());
                    string->setClipRegion(&columnRegion);
                    string->setTextColor(textColor,dropColor);
                    Int textWidth,textHeight;
                    string->getSize(&textWidth,&textHeight);
                    Int textX=TEXT_X_OFFSET;
                    switch(cells[j].alignment) {
                    case 1:textX=cellColumnWidth-textWidth-TEXT_X_OFFSET;if(textX<0)textX=TEXT_X_OFFSET;break;
                    case 2:textX=(cellColumnWidth-textWidth)/2;if(textX<0)textX=TEXT_X_OFFSET;break;
                    }
                    Int textY=(list->listData[i].height-textHeight+1)/2;
                    if(textY<0)textY=0;
                    string->draw(columnX+textX,drawY+textY,1,1);
                }// if
				else if(cells[j].cellType == LISTBOX_IMAGE && cells[j].data)
				{
					Int width, height;
					if (cells[j].width > 0)
						width = cells[j].width;
					else
						width = list->columnWidth[j];
					if(cells[j].height > 0)
						height = cells[j].height;
					else
						height = list->listData[i].height;
					if(j == 0)
						width--;
					Int offsetX,offsetY;
					if(width < list->columnWidth[j])
						offsetX = columnX + ((list->columnWidth[j] - width) / 2);
					else
						offsetX = columnX;
					if(height < list->listData[i].height)
						offsetY = drawY + ((list->listData[i].height - height) / 2);
					else
						offsetY = drawY;

					
					if(offsetX <x+1)
						offsetX = x+1;
					TheDisplay->setClipRegion( &columnRegion );					
					if(columnRegion.lo.y<columnRegion.hi.y)TheWindowManager->winDrawImage( (const Image *)cells[j].data, 
																offsetX, offsetY,
																offsetX + width, offsetY + height,cells[j].color );

				}//else
				columnX = columnX + list->columnWidth[j];
			}// for
		}//if
		

		drawY += listLineHeight;
		TheDisplay->enableClipping(FALSE);
	}

//	TheWindowManager->winSetClipRegion( clipRegion.lo.x, clipRegion.lo.y,
//																			clipRegion.hi.x, clipRegion.hi.y );

}  // end drawListBoxText

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetListBoxDraw =======================================================
/** Draw colored list box using standard graphics */
//=============================================================================
void W3DGadgetListBoxDraw( GameWindow *window, WinInstanceData *instData )
{
	Int width, height, fontHeight, x, y;
	Color background, border, titleColor, titleBorder;
	BfmeListboxData *list = (BfmeListboxData *)window->winGetUserData();
	ICoord2D size;
	BfmeListDisplayString *title = (BfmeListDisplayString *)instData->getTextDisplayString();

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
		background		= bfmeListDisabledColor( window );
		border				= bfmeListDisabledBorderColor( window );
		titleColor		= window->winGetDisabledTextColor();
		titleBorder		= window->winGetDisabledTextBorderColor();
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		background		= bfmeListHiliteColor( window );
		border				= bfmeListHiliteBorderColor( window );
		titleColor		= window->winGetHiliteTextColor();
		titleBorder		= window->winGetHiliteTextBorderColor();
	}  // end else if, hilited
	else
	{
		background		= bfmeListEnabledColor( window );
		border				= bfmeListEnabledBorderColor( window );
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

	// If ScrollBar was requested ... adjust width.
	if( list->slider  && !list->slider->winIsHidden())
	{
		ICoord2D sliderSize;

		list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
		width -= (sliderSize.x +3);

	}  // end if

	// draw the text
	drawListBoxText( window, instData, x, y + 4 , width, height-4, TRUE );

	

}  // end W3DGadgetListBoxDraw

// W3DGadgetListBoxImageDraw ==================================================
/** Draw list box with user supplied images */
//=============================================================================
void W3DGadgetListBoxImageDraw( GameWindow *window, WinInstanceData *instData )
{
	Int width, height, x, y;
	const Image *image;
	BfmeListboxData *list = (BfmeListboxData *)window->winGetUserData();
	ICoord2D size;
	Color titleColor, titleBorder;
	BfmeListDisplayString *title = (BfmeListDisplayString *)instData->getTextDisplayString();

	// get window position and size
	window->winGetScreenPosition( &x, &y );
	window->winGetSize( &size.x, &size.y );

	// save off width and height so we can change them
	width = size.x;
	height = size.y;

	// If ScrollBar was requested ... adjust width.
	if( list->slider )
	{
		ICoord2D sliderSize;

		list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
		width -= sliderSize.x;

	}  // end if

	// get the image
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		image				= bfmeListDisabledImage( window );
		titleColor	= window->winGetDisabledTextColor();
		titleBorder = window->winGetDisabledTextBorderColor();
	}
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		image				= bfmeListHiliteImage( window );
		titleColor	= window->winGetHiliteTextColor();
		titleBorder = window->winGetHiliteTextBorderColor();
	}
	else
	{
		image				= bfmeListEnabledImage( window );
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

	// draw the listbox text
	drawListBoxText( window, instData, x, y+4, width, height-4, TRUE );

	

}  // end W3DGadgetListBoxImageDraw
