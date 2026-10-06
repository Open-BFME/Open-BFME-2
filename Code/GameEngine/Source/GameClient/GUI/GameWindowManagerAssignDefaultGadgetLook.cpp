// cl: /Ireference/shims/gamewindow /O1 /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
#define Matrix4x4 Matrix4
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

// Reference: Open-BFME-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngine/Source/GameClient/GUI/GameWindowManagerAssignDefaultGadgetLook.cpp.
// That clean C++ recovery supplies gadget semantics and the full branch structure.
// BFME 2 target: RVA 0x002C2EDF..0x002C5265, 9,094 bytes, complete CFG through ret12.
// Existing GUI factories call assignDefaultGadgetLook at manager slot30 (+0x78).
// Target instructions independently establish winMakeColor at slot70 (+0x118),
// winFindImage at slot71 (+0x11C), winFindFont at slot76 (+0x130), language font
// at +0xA4 and listbox children at +0x1C/+0x20/+0x24. The local views declare
// only these observed ABI details; they are not additional object definitions.
// Helper calls reuse existing ledger owners, including historically misnamed
// folded child accessors. Donor role alone must not rename those owners.
// All image literals, static color initialization and helper relocations are
// checked by the normal byte gate. No raw image addresses are used as globals.

#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTabControl.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GlobalLanguage.h"

// Native language accesses use this target-specific offset.
struct GadgetAppearanceLanguageView
{
    char prefix[0xa4];
    FontDesc m_defaultWindowFont;
};
// Declaration-only view for the observed virtual calls.
class GadgetAppearanceManagerView { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual Color winMakeColor(UnsignedByte,UnsignedByte,UnsignedByte,UnsignedByte);
 virtual const Image *winFindImage(const char *);
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual GameFont *winFindFont(AsciiString,Int,Bool);
};


class Rva003140C8DwordField;
class BfmeKeyLC;
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *,const Image *);
void GadgetButtonSetEnabledImage123_Rva002C045D(GameWindow *,const Image *);
void GadgetButtonSetDisabledImage_Rva002C0487(GameWindow *,const Image *);
void GadgetButtonSetDisabledImage123_Rva002C04B1(GameWindow *,const Image *);
void GadgetButtonSetHiliteImage_Rva002C04DB(GameWindow *,const Image *);
void GadgetButtonSetHiliteImage123_Rva002C0505(GameWindow *,const Image *);
void Rva002C055FSet(Rva003140C8DwordField *,const Image *);
void Rva002C0579Set(Rva003140C8DwordField *,int);
void Rva002C0594Set(Rva003140C8DwordField *,int);
void Rva002C05AFSet(Rva003140C8DwordField *,const Image *);
void Rva002C05C9Set(Rva003140C8DwordField *,int);
void Rva002C05E4Set(Rva003140C8DwordField *,int);
void Rva002C05FFSet(Rva003140C8DwordField *,const Image *);
void Rva002C0619Set(Rva003140C8DwordField *,int);
void Rva002C0634Set(Rva003140C8DwordField *,int);
void Rva002C064FSet(Rva003140C8DwordField *,const Image *);
void Rva002C0669Set(Rva003140C8DwordField *,int);
void Rva002C0684Set(Rva003140C8DwordField *,int);
void Rva002C069FSet(Rva003140C8DwordField *,const Image *);
void Rva002C06B9Set(Rva003140C8DwordField *,int);
void Rva002C06D4Set(Rva003140C8DwordField *,int);
void Rva002C06EFSet(Rva003140C8DwordField *,const Image *);
void Rva002C0709Set(Rva003140C8DwordField *,int);
void Rva002C0724Set(Rva003140C8DwordField *,int);
GameWindow *GadgetComboBoxGetEditBox(GameWindow *);
GameWindow *GadgetComboBoxGetListBox(GameWindow *);
void *bfmeGo925A(BfmeKeyLC *);
GameWindow *GadgetListBoxGetDownButton(GameWindow *);
GameWindow *GadgetListBoxGetSlider(GameWindow *);
struct GadgetAppearanceListView { unsigned char prefix[0x1c]; GameWindow *upButton; GameWindow *downButton; GameWindow *slider; };

void GameWindowManager::assignDefaultGadgetLook( GameWindow *gadget,
																								 GameFont *defaultFont,
																								 Bool assignVisual )
{
	UnsignedByte alpha = 255;
	static Color red				= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255,   0,   0, alpha );
	static Color darkRed		= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128,   0,   0, alpha );
	static Color lightRed		= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255, 128, 128, alpha );
	static Color green			= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0, 255,   0, alpha );
	static Color darkGreen	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0, 128,   0, alpha );
	static Color lightGreen	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128, 255, 128, alpha );
	static Color blue				= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0,   0, 255, alpha );
	static Color darkBlue		= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0,   0, 128, alpha );
	static Color lightBlue	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128, 128, 255, alpha );
	static Color purple			= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255,   0, 255, alpha );
	static Color darkPurple	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128,   0, 128, alpha );
	static Color lightPurple= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255, 128, 255, alpha );
	static Color yellow			= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255, 255,   0, alpha );
	static Color darkYellow	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128, 128,   0, alpha );
	static Color lightYellow= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255, 255, 128, alpha );
	static Color cyan				= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0, 255, 255, alpha );
	static Color darkCyan		= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(  64, 128, 128, alpha );
	static Color lightCyan	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128, 255, 255, alpha );
	static Color gray				= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 128, 128, 128, alpha );
	static Color darkGray		= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(  64,  64,  64, alpha );
	static Color lightGray	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 192, 192, 192, alpha );
	static Color black			= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor(   0,   0,   0, alpha );
	static Color white			= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 254, 254, 254, alpha );
	static Color enabledText					= white;
	static Color enabledTextBorder		= darkGray;
	static Color disabledText					= darkGray;
	static Color disabledTextBorder		= black;
	static Color hiliteText						= lightBlue;
	static Color hiliteTextBorder			= blue;
	static Color imeCompositeText				= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 255, 255, 255, alpha );
	static Color imeCompositeTextBorder	= reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winMakeColor( 205, 136, 60, alpha );
	WinInstanceData *instData;

	// sanity
	if( gadget == NULL )
		return;

	// get instance data
	instData = gadget->winGetInstanceData();

	// set default font
	if( defaultFont )
		gadget->GameWindow::winSetFont( defaultFont );
	else
	{
		GadgetAppearanceLanguageView *language = reinterpret_cast<GadgetAppearanceLanguageView *>(TheGlobalLanguageData);
		if (language && !language->m_defaultWindowFont.name.isEmpty())
		{		gadget->GameWindow::winSetFont( reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winFindFont(
				language->m_defaultWindowFont.name,
				language->m_defaultWindowFont.size,
				language->m_defaultWindowFont.bold) );
		}
		else
			gadget->GameWindow::winSetFont( reinterpret_cast<GadgetAppearanceManagerView *>(TheWindowManager)->winFindFont( AsciiString("Times New Roman"), 14, FALSE ) );
	}

	gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	// if we don't want to assign default colors/images get out of here
	if( assignVisual == FALSE )
		return;

	// create images for the correct gadget type
	if( BitTest( instData->getStyle(), GWS_PUSH_BUTTON ) )
	{

		// enabled background
		GadgetButtonSetEnabledImage_Rva002C0433(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonEnabled" ) );
		GadgetButtonSetEnabledColor( gadget, red );
		GadgetButtonSetEnabledBorderColor( gadget, lightRed );
		// enabled selected button
		GadgetButtonSetEnabledImage123_Rva002C045D(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonEnabledSelected" ) );
		GadgetButtonSetEnabledSelectedColor( gadget, yellow );
		GadgetButtonSetEnabledSelectedBorderColor( gadget, white );

		// Disabled background
		GadgetButtonSetDisabledImage_Rva002C0487(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonDisabled" ) );
		GadgetButtonSetDisabledColor( gadget, gray );
		GadgetButtonSetDisabledBorderColor( gadget, lightGray );
		// Disabled selected button
		GadgetButtonSetDisabledImage123_Rva002C04B1(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonDisabledSelected" ) );
		GadgetButtonSetDisabledSelectedColor( gadget, lightGray );
		GadgetButtonSetDisabledSelectedBorderColor( gadget, gray );

		// Hilite background
		GadgetButtonSetHiliteImage_Rva002C04DB(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonHilite" ) );
		GadgetButtonSetHiliteColor( gadget, green );
		GadgetButtonSetHiliteBorderColor( gadget, darkGreen );
		// Hilite selected button
		GadgetButtonSetHiliteImage123_Rva002C0505(gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonHiliteSelected" ) );
		GadgetButtonSetHiliteSelectedColor( gadget, yellow );
		GadgetButtonSetHiliteSelectedBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end if
	else if( BitTest( instData->getStyle(), GWS_CHECK_BOX ) )
	{

		// enabled background
		GadgetCheckBoxSetEnabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxEnabled" ) );
		GadgetCheckBoxSetEnabledColor( gadget, red );
		GadgetCheckBoxSetEnabledBorderColor( gadget, lightRed );
		// enabled CheckBox unselected
		GadgetCheckBoxSetEnabledUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxEnabledBoxUnselected" ) );
		GadgetCheckBoxSetEnabledUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetEnabledUncheckedBoxBorderColor( gadget, lightBlue );
		// enabled CheckBox selected
		GadgetCheckBoxSetEnabledCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxEnabledBoxSelected" ) );
		GadgetCheckBoxSetEnabledCheckedBoxColor( gadget, blue );
		GadgetCheckBoxSetEnabledCheckedBoxBorderColor( gadget, lightBlue );

		// disabled background
		GadgetCheckBoxSetDisabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxDisabled" ) );
		GadgetCheckBoxSetDisabledColor( gadget, gray );
		GadgetCheckBoxSetDisabledBorderColor( gadget, lightGray );
		// Disabled CheckBox unselected
		GadgetCheckBoxSetDisabledUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxDisabledBoxUnselected" ) );
		GadgetCheckBoxSetDisabledUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetDisabledUncheckedBoxBorderColor( gadget, lightGray );
		// Disabled CheckBox selected
		GadgetCheckBoxSetDisabledCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxDisabledBoxSelected" ) );
		GadgetCheckBoxSetDisabledCheckedBoxColor( gadget, darkGray );
		GadgetCheckBoxSetDisabledCheckedBoxBorderColor( gadget, white );

		// Hilite background
		GadgetCheckBoxSetHiliteImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxHilite" ) );
		GadgetCheckBoxSetHiliteColor( gadget, green );
		GadgetCheckBoxSetHiliteBorderColor( gadget, lightGreen );
		// Hilite CheckBox unselected
		GadgetCheckBoxSetHiliteUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxHiliteBoxUnselected" ) );
		GadgetCheckBoxSetHiliteUncheckedBoxColor( gadget, WIN_COLOR_UNDEFINED );
		GadgetCheckBoxSetHiliteUncheckedBoxBorderColor( gadget, lightBlue );
		// Hilite CheckBox selected
		GadgetCheckBoxSetHiliteCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "CheckBoxHiliteBoxSelected" ) );
		GadgetCheckBoxSetHiliteCheckedBoxColor( gadget, yellow );
		GadgetCheckBoxSetHiliteCheckedBoxBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_RADIO_BUTTON ) )
	{

		// enabled background
		GadgetRadioSetEnabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonEnabled" ) );
		GadgetRadioSetEnabledColor( gadget, red );
		GadgetRadioSetEnabledBorderColor( gadget, lightRed );
		// enabled radio unselected
		GadgetRadioSetEnabledUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonEnabledBoxUnselected" ) );
		GadgetRadioSetEnabledUncheckedBoxColor( gadget, darkRed );
		GadgetRadioSetEnabledUncheckedBoxBorderColor( gadget, black );
		// enabled radio selected
		GadgetRadioSetEnabledCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonEnabledBoxSelected" ) );
		GadgetRadioSetEnabledCheckedBoxColor( gadget, blue );
		GadgetRadioSetEnabledCheckedBoxBorderColor( gadget, lightBlue );

		// disabled background
		GadgetRadioSetDisabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonDisabled" ) );
		GadgetRadioSetDisabledColor( gadget, gray );
		GadgetRadioSetDisabledBorderColor( gadget, lightGray );
		// Disabled radio unselected
		GadgetRadioSetDisabledUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonDisabledBoxUnselected" ) );
		GadgetRadioSetDisabledUncheckedBoxColor( gadget, gray );
		GadgetRadioSetDisabledUncheckedBoxBorderColor( gadget, lightGray );
		// Disabled radio selected
		GadgetRadioSetDisabledCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonDisabledBoxSelected" ) );
		GadgetRadioSetDisabledCheckedBoxColor( gadget, darkGray );
		GadgetRadioSetDisabledCheckedBoxBorderColor( gadget, white );

		// Hilite background
		GadgetRadioSetHiliteImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonHilite" ) );
		GadgetRadioSetHiliteColor( gadget, green );
		GadgetRadioSetHiliteBorderColor( gadget, lightGreen );
		// Hilite radio unselected
		GadgetRadioSetHiliteUncheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonHiliteBoxUnselected" ) );
		GadgetRadioSetHiliteUncheckedBoxColor( gadget, darkGreen );
		GadgetRadioSetHiliteUncheckedBoxBorderColor( gadget, lightGreen );
		// Hilite radio selected
		GadgetRadioSetHiliteCheckedBoxImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "RadioButtonHiliteBoxSelected" ) );
		GadgetRadioSetHiliteCheckedBoxColor( gadget, yellow );
		GadgetRadioSetHiliteCheckedBoxBorderColor( gadget, white );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_HORZ_SLIDER ) )
	{

		// enabled
		GadgetSliderSetEnabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderEnabledLeftEnd" ) );
		GadgetSliderSetEnabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderEnabledRightEnd" ) );
		GadgetSliderSetEnabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderEnabledRepeatingCenter" ) );
		GadgetSliderSetEnabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderEnabledSmallRepeatingCenter" ) );
		GadgetSliderSetEnabledColor( gadget, red );
		GadgetSliderSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetSliderSetDisabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderDisabledLeftEnd" ) );
		GadgetSliderSetDisabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderDisabledRightEnd" ) );
		GadgetSliderSetDisabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderDisabledRepeatingCenter" ) );
		GadgetSliderSetDisabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderDisabledSmallRepeatingCenter" ) );
		GadgetSliderSetDisabledColor( gadget, red );
		GadgetSliderSetDisabledBorderColor( gadget, lightRed );

		// hilite
		GadgetSliderSetHiliteImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderHiliteLeftEnd" ) );
		GadgetSliderSetHiliteImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderHiliteRightEnd" ) );
		GadgetSliderSetHiliteImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderHiliteRepeatingCenter" ) );
		GadgetSliderSetHiliteImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderHiliteSmallRepeatingCenter" ) );
		GadgetSliderSetHiliteColor( gadget, red );
		GadgetSliderSetHiliteBorderColor( gadget, lightRed );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		//
		// set the default colors and images for the slider thumb
		//
		// enabled
		Rva002C055FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbEnabled" ) );
		Rva002C0579Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledColor(0) );
		Rva002C0594Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledBorderColor(0) );
		Rva002C05AFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbEnabled" ) );
		Rva002C05C9Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledBorderColor(0) );
		Rva002C05E4Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledColor(0) );

		// disabled
		Rva002C05FFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbDisabled" ) );
		Rva002C0619Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledColor(0) );
		Rva002C0634Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledBorderColor(0) );
		Rva002C064FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbDisabled" ) );
		Rva002C0669Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledBorderColor(0) );
		Rva002C0684Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledColor(0) );

		// hilite
		Rva002C069FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbHilite" ) );
		Rva002C06B9Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteColor(0) );
		Rva002C06D4Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteBorderColor(0) );
		Rva002C06EFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "HSliderThumbHiliteSelected" ) );
		Rva002C0709Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteBorderColor(0) );
		Rva002C0724Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteColor(0) );


	}  // end if
	else if( BitTest( instData->getStyle(), GWS_VERT_SLIDER ) )
	{
		// enabled
		GadgetSliderSetEnabledImageTop( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderEnabledTopEnd" ) );
		GadgetSliderSetEnabledImageBottom( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderEnabledBottomEnd" ) );
		GadgetSliderSetEnabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderEnabledRepeatingCenter" ) );
		GadgetSliderSetEnabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderEnabledSmallRepeatingCenter" ) );
		GadgetSliderSetEnabledColor( gadget, red );
		GadgetSliderSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetSliderSetDisabledImageTop( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderDisabledTopEnd" ) );
		GadgetSliderSetDisabledImageBottom( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderDisabledBottomEnd" ) );
		GadgetSliderSetDisabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderDisabledRepeatingCenter" ) );
		GadgetSliderSetDisabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderDisabledSmallRepeatingCenter" ) );
		GadgetSliderSetDisabledColor( gadget, red );
		GadgetSliderSetDisabledBorderColor( gadget, lightRed );

		// hilite
		GadgetSliderSetHiliteImageTop( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderHiliteTopEnd" ) );
		GadgetSliderSetHiliteImageBottom( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderHiliteBottomEnd" ) );
		GadgetSliderSetHiliteImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderHiliteRepeatingCenter" ) );
		GadgetSliderSetHiliteImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderHiliteSmallRepeatingCenter" ) );
		GadgetSliderSetHiliteColor( gadget, red );
		GadgetSliderSetHiliteBorderColor( gadget, lightRed );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		//
		// set the default colors and images for the slider thumb
		//
		// enabled
		Rva002C055FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbEnabled" ) );
		Rva002C0579Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledColor(0) );
		Rva002C0594Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledBorderColor(0) );
		Rva002C05AFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbEnabled" ) );
		Rva002C05C9Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledBorderColor(0) );
		Rva002C05E4Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetEnabledColor(0) );

		// disabled
		Rva002C05FFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbDisabled" ) );
		Rva002C0619Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledColor(0) );
		Rva002C0634Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledBorderColor(0) );
		Rva002C064FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbDisabled" ) );
		Rva002C0669Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledBorderColor(0) );
		Rva002C0684Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetDisabledColor(0) );

		// hilite
		Rva002C069FSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbHilite" ) );
		Rva002C06B9Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteColor(0) );
		Rva002C06D4Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteBorderColor(0) );
		Rva002C06EFSet(reinterpret_cast<Rva003140C8DwordField *>(gadget), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderThumbHiliteSelected" ) );
		Rva002C0709Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteBorderColor(0) );
		Rva002C0724Set(reinterpret_cast<Rva003140C8DwordField *>(gadget), gadget->winGetHiliteColor(0) );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_SCROLL_LISTBOX ) )
	{
		GadgetAppearanceListView *listboxData = (GadgetAppearanceListView *)gadget->winGetUserData();

		// set the colors
		GadgetListBoxSetColors( gadget,
														red,							// enabled
														lightRed,					// enabled border
														yellow,						// enabled selected item
														white,						// enabled selected item border
														gray,							// disabled
														lightGray,				// disabled border
														lightGray,				// disabled selected item
														white,						// disabled selected item border
														green,						// hilite
														darkGreen,				// hilite border
														white,						// hilite selected item
														darkGreen );			// hilite selected item border

		// now set the images

		// enabled
		GadgetListBoxSetEnabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabled" ) );
		GadgetListBoxSetEnabledSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
		GadgetListBoxSetEnabledSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
		GadgetListBoxSetEnabledSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetEnabledSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

		// disabled
		GadgetListBoxSetDisabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabled" ) );
		GadgetListBoxSetDisabledSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
		GadgetListBoxSetDisabledSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
		GadgetListBoxSetDisabledSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetDisabledSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


		// hilited
		GadgetListBoxSetHiliteImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHilite" ) );
		GadgetListBoxSetHiliteSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
		GadgetListBoxSetHiliteSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
		GadgetListBoxSetHiliteSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
		GadgetListBoxSetHiliteSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

		// assign default slider colors and images as part of the list box
		GameWindow *slider = listboxData->slider;
		if( slider )
		{
			GameWindow *upButton = listboxData->upButton;
			GameWindow *downButton = listboxData->downButton;

			// slider and slider thumb ----------------------------------------------

			// enabled
			GadgetSliderSetEnabledImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledTopEnd" ) );
			GadgetSliderSetEnabledImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledBottomEnd" ) );
			GadgetSliderSetEnabledImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledRepeatingCenter" ) );
			GadgetSliderSetEnabledImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledSmallRepeatingCenter" ) );
			Rva002C055FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbEnabled" ) );
			Rva002C05AFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbEnabled" ) );

			// disabled
			GadgetSliderSetDisabledImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledTopEnd" ) );
			GadgetSliderSetDisabledImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledBottomEnd" ) );
			GadgetSliderSetDisabledImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledRepeatingCenter" ) );
			GadgetSliderSetDisabledImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledSmallRepeatingCenter" ) );
			Rva002C05FFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbDisabled" ) );
			Rva002C064FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbDisabled" ) );

			// hilite
			GadgetSliderSetHiliteImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteTopEnd" ) );
			GadgetSliderSetHiliteImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteBottomEnd" ) );
			GadgetSliderSetHiliteImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteRepeatingCenter" ) );
			GadgetSliderSetHiliteImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteSmallRepeatingCenter" ) );
			Rva002C069FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbHilite" ) );
			Rva002C06EFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbHilite" ) );

			// up button ------------------------------------------------------------

			// enabled
			GadgetButtonSetEnabledImage_Rva002C0433(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonEnabled" ) );
			GadgetButtonSetEnabledImage123_Rva002C045D(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonEnabled" ) );

			// disabled
			GadgetButtonSetDisabledImage_Rva002C0487(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonDisabled" ) );
			GadgetButtonSetDisabledImage123_Rva002C04B1(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonDisabled" ) );

			// hilite
			GadgetButtonSetHiliteImage_Rva002C04DB(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonHilite" ) );
			GadgetButtonSetHiliteImage123_Rva002C0505(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonHiliteSelected" ) );

			// down button ----------------------------------------------------------

			// enabled
			GadgetButtonSetEnabledImage_Rva002C0433(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonEnabled" ) );
			GadgetButtonSetEnabledImage123_Rva002C045D(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonEnabled" ) );

			// disabled
			GadgetButtonSetDisabledImage_Rva002C0487(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonDisabled" ) );
			GadgetButtonSetDisabledImage123_Rva002C04B1(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonDisabled" ) );

			// hilite
			GadgetButtonSetHiliteImage_Rva002C04DB(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonHilite" ) );
			GadgetButtonSetHiliteImage123_Rva002C0505(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonHiliteSelected" ) );

		}  // end if

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_COMBO_BOX ) )
	{
//		ComboBoxData *comboBoxData = (ComboBoxData *)gadget->winGetUserData();

		GadgetComboBoxSetColors( gadget,
														red,							// enabled
														lightRed,					// enabled border
														yellow,						// enabled selected item
														white,						// enabled selected item border
														gray,							// disabled
														lightGray,				// disabled border
														lightGray,				// disabled selected item
														white,						// disabled selected item border
														green,						// hilite
														darkGreen,				// hilite border
														white,						// hilite selected item
														darkGreen );			// hilite selected item border

		// enabled
		GadgetComboBoxSetEnabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabled" ) );
		GadgetComboBoxSetEnabledSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
		GadgetComboBoxSetEnabledSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
		GadgetComboBoxSetEnabledSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetEnabledSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

		// disabled
		GadgetComboBoxSetDisabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabled" ) );
		GadgetComboBoxSetDisabledSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
		GadgetComboBoxSetDisabledSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
		GadgetComboBoxSetDisabledSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetDisabledSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


		// hilited
		GadgetComboBoxSetHiliteImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHilite" ) );
		GadgetComboBoxSetHiliteSelectedItemImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
		GadgetComboBoxSetHiliteSelectedItemImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
		GadgetComboBoxSetHiliteSelectedItemImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
		GadgetComboBoxSetHiliteSelectedItemImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

		GameWindow *dropDownButton = GadgetComboBoxGetEditBox(gadget );
		if ( dropDownButton )
		{
			// enabled background
			GadgetButtonSetEnabledImage_Rva002C0433(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonEnabled" ) );
			// enabled selected button
			GadgetButtonSetEnabledImage123_Rva002C045D(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonEnabledSelected" ) );

			// Disabled background
			GadgetButtonSetDisabledImage_Rva002C0487(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonDisabled" ) );
			// Disabled selected button
			GadgetButtonSetDisabledImage123_Rva002C04B1(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonDisabledSelected" ) );

			// Hilite background
			GadgetButtonSetHiliteImage_Rva002C04DB(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonHilite" ) );
			// Hilite selected button
			GadgetButtonSetHiliteImage123_Rva002C0505(dropDownButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "PushButtonHiliteSelected" ) );

		}

		GameWindow *editBox = GadgetComboBoxGetListBox(gadget );
		if ( editBox )
		{
			// enabled
			GadgetTextEntrySetEnabledImageLeft( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledLeftEnd" ) );
			GadgetTextEntrySetEnabledImageRight( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledRightEnd" ) );
			GadgetTextEntrySetEnabledImageCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledRepeatingCenter" ) );
			GadgetTextEntrySetEnabledImageSmallCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledSmallRepeatingCenter" ) );

			// disabled
			GadgetTextEntrySetDisabledImageLeft( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledLeftEnd" ) );
			GadgetTextEntrySetDisabledImageRight( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledRightEnd" ) );
			GadgetTextEntrySetDisabledImageCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledRepeatingCenter" ) );
			GadgetTextEntrySetDisabledImageSmallCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledSmallRepeatingCenter" ) );

			// hilited
			GadgetTextEntrySetHiliteImageLeft( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteLeftEnd" ) );
			GadgetTextEntrySetHiliteImageRight( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteRightEnd" ) );
			GadgetTextEntrySetHiliteImageCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteRepeatingCenter" ) );
			GadgetTextEntrySetHiliteImageSmallCenter( editBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteSmallRepeatingCenter" ) );

		}

		GameWindow * listBox = reinterpret_cast<GameWindow *>(bfmeGo925A(reinterpret_cast<BfmeKeyLC *>(gadget) ));
		if ( listBox )
		{

			// now set the images

			// enabled
			GadgetListBoxSetEnabledImage( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabled" ) );
			GadgetListBoxSetEnabledSelectedItemImageLeft( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemLeftEnd" ) );
			GadgetListBoxSetEnabledSelectedItemImageRight( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRightEnd" ) );
			GadgetListBoxSetEnabledSelectedItemImageCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetEnabledSelectedItemImageSmallCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxEnabledSelectedItemSmallRepeatingCenter" ) );

			// disabled
			GadgetListBoxSetDisabledImage( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabled" ) );
			GadgetListBoxSetDisabledSelectedItemImageLeft( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemLeftEnd" ) );
			GadgetListBoxSetDisabledSelectedItemImageRight( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRightEnd" ) );
			GadgetListBoxSetDisabledSelectedItemImageCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetDisabledSelectedItemImageSmallCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxDisabledSelectedItemSmallRepeatingCenter" ) );


			// hilited
			GadgetListBoxSetHiliteImage( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHilite" ) );
			GadgetListBoxSetHiliteSelectedItemImageLeft( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemLeftEnd" ) );
			GadgetListBoxSetHiliteSelectedItemImageRight( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRightEnd" ) );
			GadgetListBoxSetHiliteSelectedItemImageCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemRepeatingCenter" ) );
			GadgetListBoxSetHiliteSelectedItemImageSmallCenter( listBox, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ListBoxHiliteSelectedItemSmallRepeatingCenter" ) );

			// assign default slider colors and images as part of the list box
			GameWindow *slider = GadgetComboBoxGetEditBox(listBox );
			if( slider )
			{
				GameWindow *upButton = GadgetListBoxGetDownButton(listBox );
				GameWindow *downButton = GadgetListBoxGetSlider(listBox );

				// slider and slider thumb ----------------------------------------------

				// enabled
				GadgetSliderSetEnabledImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledTopEnd" ) );
				GadgetSliderSetEnabledImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledBottomEnd" ) );
				GadgetSliderSetEnabledImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledRepeatingCenter" ) );
				GadgetSliderSetEnabledImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeEnabledSmallRepeatingCenter" ) );
				Rva002C055FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbEnabled" ) );
				Rva002C05AFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbEnabled" ) );

				// disabled
				GadgetSliderSetDisabledImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledTopEnd" ) );
				GadgetSliderSetDisabledImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledBottomEnd" ) );
				GadgetSliderSetDisabledImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledRepeatingCenter" ) );
				GadgetSliderSetDisabledImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDisabledSmallRepeatingCenter" ) );
				Rva002C05FFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbDisabled" ) );
				Rva002C064FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbDisabled" ) );

				// hilite
				GadgetSliderSetHiliteImageTop( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteTopEnd" ) );
				GadgetSliderSetHiliteImageBottom( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteBottomEnd" ) );
				GadgetSliderSetHiliteImageCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteRepeatingCenter" ) );
				GadgetSliderSetHiliteImageSmallCenter( slider, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeHiliteSmallRepeatingCenter" ) );
				Rva002C069FSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbHilite" ) );
				Rva002C06EFSet(reinterpret_cast<Rva003140C8DwordField *>(slider), reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeThumbHilite" ) );

				// up button ------------------------------------------------------------

				// enabled
				GadgetButtonSetEnabledImage_Rva002C0433(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonEnabled" ) );
				GadgetButtonSetEnabledImage123_Rva002C045D(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonEnabled" ) );

				// disabled
				GadgetButtonSetDisabledImage_Rva002C0487(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonDisabled" ) );
				GadgetButtonSetDisabledImage123_Rva002C04B1(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonDisabled" ) );

				// hilite
				GadgetButtonSetHiliteImage_Rva002C04DB(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonHilite" ) );
				GadgetButtonSetHiliteImage123_Rva002C0505(upButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeUpButtonHiliteSelected" ) );

				// down button ----------------------------------------------------------

				// enabled
				GadgetButtonSetEnabledImage_Rva002C0433(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonEnabled" ) );
				GadgetButtonSetEnabledImage123_Rva002C045D(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonEnabled" ) );

				// disabled
				GadgetButtonSetDisabledImage_Rva002C0487(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonDisabled" ) );
				GadgetButtonSetDisabledImage123_Rva002C04B1(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonDisabled" ) );

				// hilite
				GadgetButtonSetHiliteImage_Rva002C04DB(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonHilite" ) );
				GadgetButtonSetHiliteImage123_Rva002C0505(downButton, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "VSliderLargeDownButtonHiliteSelected" ) );

			}  // end if
		}
	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_PROGRESS_BAR ) )
	{

		// enabled
		GadgetProgressBarSetEnabledColor( gadget, red );
		GadgetProgressBarSetEnabledBorderColor( gadget, lightRed );
		GadgetProgressBarSetEnabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledLeftEnd" ) );
		GadgetProgressBarSetEnabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledRightEnd" ) );
		GadgetProgressBarSetEnabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledRepeatingCenter" ) );
		GadgetProgressBarSetEnabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledSmallRepeatingCenter" ) );
		GadgetProgressBarSetEnabledBarColor( gadget, yellow );
		GadgetProgressBarSetEnabledBarBorderColor( gadget, white );
		GadgetProgressBarSetEnabledBarImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledBarLeftEnd" ) );
		GadgetProgressBarSetEnabledBarImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledBarRightEnd" ) );
		GadgetProgressBarSetEnabledBarImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledBarRepeatingCenter" ) );
		GadgetProgressBarSetEnabledBarImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarEnabledBarSmallRepeatingCenter" ) );

		// disabled
		GadgetProgressBarSetDisabledColor( gadget, darkGray );
		GadgetProgressBarSetDisabledBorderColor( gadget, lightGray );
		GadgetProgressBarSetDisabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledLeftEnd" ) );
		GadgetProgressBarSetDisabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledRightEnd" ) );
		GadgetProgressBarSetDisabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledRepeatingCenter" ) );
		GadgetProgressBarSetDisabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledSmallRepeatingCenter" ) );
		GadgetProgressBarSetDisabledBarColor( gadget, lightGray );
		GadgetProgressBarSetDisabledBarBorderColor( gadget, white );
		GadgetProgressBarSetDisabledBarImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledBarLeftEnd" ) );
		GadgetProgressBarSetDisabledBarImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledBarRightEnd" ) );
		GadgetProgressBarSetDisabledBarImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledBarRepeatingCenter" ) );
		GadgetProgressBarSetDisabledBarImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarDisabledBarSmallRepeatingCenter" ) );

		// Hilite
		GadgetProgressBarSetHiliteColor( gadget, green );
		GadgetProgressBarSetHiliteBorderColor( gadget, darkGreen );
		GadgetProgressBarSetHiliteImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteLeftEnd" ) );
		GadgetProgressBarSetHiliteImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteRightEnd" ) );
		GadgetProgressBarSetHiliteImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteRepeatingCenter" ) );
		GadgetProgressBarSetHiliteImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteSmallRepeatingCenter" ) );
		GadgetProgressBarSetHiliteBarColor( gadget, yellow );
		GadgetProgressBarSetHiliteBarBorderColor( gadget, white );
		GadgetProgressBarSetHiliteBarImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteBarLeftEnd" ) );
		GadgetProgressBarSetHiliteBarImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteBarRightEnd" ) );
		GadgetProgressBarSetHiliteBarImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteBarRepeatingCenter" ) );
		GadgetProgressBarSetHiliteBarImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "ProgressBarHiliteBarSmallRepeatingCenter" ) );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_STATIC_TEXT ) )
	{

		// enabled
		GadgetStaticTextSetEnabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "StaticTextEnabled" ) );
		GadgetStaticTextSetEnabledColor( gadget, red );
		GadgetStaticTextSetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetStaticTextSetDisabledImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "StaticTextDisabled" ) );
		GadgetStaticTextSetDisabledColor( gadget, darkGray );
		GadgetStaticTextSetDisabledBorderColor( gadget, lightGray );

		// hilite
		GadgetStaticTextSetHiliteImage( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "StaticTextHilite" ) );
		GadgetStaticTextSetHiliteColor( gadget, darkGreen );
		GadgetStaticTextSetHiliteBorderColor( gadget, lightGreen );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if
	else if( BitTest( instData->getStyle(), GWS_ENTRY_FIELD ) )
	{

		// enabled
		GadgetTextEntrySetEnabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledLeftEnd" ) );
		GadgetTextEntrySetEnabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledRightEnd" ) );
		GadgetTextEntrySetEnabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledRepeatingCenter" ) );
		GadgetTextEntrySetEnabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryEnabledSmallRepeatingCenter" ) );
		GadgetTextEntrySetEnabledColor( gadget, red );
		GadgetTextEntrySetEnabledBorderColor( gadget, lightRed );

		// disabled
		GadgetTextEntrySetDisabledImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledLeftEnd" ) );
		GadgetTextEntrySetDisabledImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledRightEnd" ) );
		GadgetTextEntrySetDisabledImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledRepeatingCenter" ) );
		GadgetTextEntrySetDisabledImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryDisabledSmallRepeatingCenter" ) );
		GadgetTextEntrySetDisabledColor( gadget, gray );
		GadgetTextEntrySetDisabledBorderColor( gadget, black );

		// hilited
		GadgetTextEntrySetHiliteImageLeft( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteLeftEnd" ) );
		GadgetTextEntrySetHiliteImageRight( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteRightEnd" ) );
		GadgetTextEntrySetHiliteImageCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteRepeatingCenter" ) );
		GadgetTextEntrySetHiliteImageSmallCenter( gadget, reinterpret_cast<GadgetAppearanceManagerView *>(this)->winFindImage( "TextEntryHiliteSmallRepeatingCenter" ) );
		GadgetTextEntrySetHiliteColor( gadget, green );
		GadgetTextEntrySetHiliteBorderColor( gadget, darkGreen );

		// set default text colors for the gadget
		gadget->winSetEnabledTextColors( enabledText, enabledTextBorder );
		gadget->winSetDisabledTextColors( disabledText, disabledTextBorder );
		gadget->winSetHiliteTextColors( hiliteText, hiliteTextBorder );
		gadget->winSetIMECompositeTextColors( imeCompositeText, imeCompositeTextBorder );

	}  // end else if

}  // end assignDefaultGadgetLook
