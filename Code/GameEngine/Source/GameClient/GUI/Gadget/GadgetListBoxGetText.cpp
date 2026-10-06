// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/displaystring /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/GameClient/GUI
// Clean BFME1 6d943426 transfer. Native326FBC-327074 proves listbox/style guards,
// row/column request401A and string/color output. Wrapper327074-327099 proves
// the hidden-return ABI and delegation. Native manager slotE8 follows the same
// observed ABI as rowed listbox reset/selection wrappers. Reuse canonical
// TabWindowManagerView with a typed call to its observed slot58; original
// manager/type identity remains unasserted. Other names follow donor semantics.
// Donor6d943426; full-family scratch preserves the compiler-private static helper context.
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

// FILE: GadgetListBox.cpp ////////////////////////////////////////////////////
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
// File name: ListBox.cpp
//
// Created:   Dean Iverson, March 1998
//						Colin Day, June 2001
//
// Desc:      ListBox GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/AudioEventRTS.h"
#include "Common/Language.h"
#include "Common/Debug.h"
#include "Common/GameAudio.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/Keyboard.h"

// UnicodeString is StringBase<WideChar>, and retail inlined its one-line
// forwarders away: the call sites below encode the StringBase<WideChar> bodies
// directly, not the ZH UnicodeString spellings (which resolve to the NARROW
// StringBase<char> bodies).
#include "string_base.h"

// ??0?$StringBase@G@@AAE@ABV0@@Z at 0x00888400 -- private, which is what
// mangles it AAE.
inline UnicodeString::UnicodeString( const UnicodeString &stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
		*(const StringBase<WideChar> *)&stringSrc );
}


typedef struct _TextAndColor { UnicodeString string; Color color; } TextAndColor;

#include "GameWindowManagerRecordView.h"
typedef int (TabWindowManagerView::*ListBoxRequestFn)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);

UnicodeString GadgetListBoxGetTextAndColor( GameWindow *listbox, Color *color, Int row, Int column)
{
	*color = 0;
	// sanity
	if( listbox == NULL  || row == -1 || column == -1)
		return UnicodeString::TheEmptyString;

	// verify that this is a list box
	if( BitTest( listbox->winGetStyle(), GWS_SCROLL_LISTBOX ) == FALSE )
		return UnicodeString::TheEmptyString;
	TextAndColor tAndC;
	//UnicodeString result;
	ICoord2D pos;
	pos.x = column;
	pos.y = row;
	(((TabWindowManagerView *)TheWindowManager)->*(*(ListBoxRequestFn *)&(*(void ***)TheWindowManager)[58]))( listbox, 0x401A, (WindowMsgData)&pos, (WindowMsgData)&tAndC );
	

		*color = tAndC.color;
		return tAndC.string;
	
	//return UnicodeString::TheEmptyString;

}  // end GadgetListBoxGetText
UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column)
{
	Color color;
	return GadgetListBoxGetTextAndColor( listbox,&color,row,column );
}  // end GadgetListBoxGetText
