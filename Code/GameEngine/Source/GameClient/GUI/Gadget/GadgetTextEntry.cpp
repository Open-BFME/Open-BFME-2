// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Clean Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76 reference transfer.
// Native font dispatcher313D73 and helper boundaries establish target operation/ABI.
// Target field and call facts are distinct from donor names: row16/cell28/payload0C,
// instance display pointers19C/1A0, virtual slot18, font1B4 and style3C are measured.
// Font-sink pointer+04 / slot10 has an observed ABI; its original type remains unknown.
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
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define GameDarkenColor Rva002D2B9ADarken
#include "Common/Language.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/IMEManager.h"
#include "GameClient/LookAtXlat.h"

// Clean BFME1 6d943426 font helper; target99B and virtual slot18 independently examined.
void GadgetTextEntrySetFont( GameWindow *g, GameFont *font )
{
	EntryData *entryData = (EntryData *)g->winGetUserData();
	DisplayString *dString;
	typedef void (DisplayString::*BFMESetFontFn)( GameFont * );

	// set the font for the display strings all windows have
	dString = g->winGetInstanceData()->getTextDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
	dString = g->winGetInstanceData()->getTooltipDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );

	// text entry specific
	if( entryData )
	{

		dString = entryData->text;
		if( dString )
			(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
		dString = entryData->sText;
		if( dString )
			(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );

	}  // end if

}  // end GadgetTextEntrySetFont

extern int Rva002D2B9ADarken(int, int);
#include "GameClient/GadgetTextEntry.h"
void (*GadgetTextEntry_retain_TextColor)(GameWindow *, Color)=&GadgetTextEntrySetTextColor;
