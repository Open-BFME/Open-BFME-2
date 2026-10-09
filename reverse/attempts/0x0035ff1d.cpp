// ?draw@TextTypeTransition@@UAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii /Ireference/open-bfme-1/inputs/reference/shims/asciistringsetoutofline /Ireference/open-bfme-1/inputs/reference/shims/fullfade /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// Window-transition bodies ported from Open-BFME-1's
// GameClient/GUI/GameWindowTransitionsStyles.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// TextTypeTransition::update 0x0035FE72 (171B),
// MainMenuSmallScaleDownTransition::update 0x0035DA10 (143B),
// FadeTransition::update 0x0035F43D (97B), ReverseSoundTransition::update
// 0x0035D4E6 (44B), ControlBarArrowTransition::update 0x0035D75D (36B) and
// CountUpTransition::reverse 0x0035F618 (35B). They sit among the rowed
// init/draw/update bodies of the same classes. Only the placed bodies are
// carried; the donor's other definitions are omitted.
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

// FILE: GameWindowTransitionsStyles.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Dec 2002
//
//	Filename: 	GameWindowTransitionsStyles.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The Actual Styles that can fire off.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/AudioEventRTS.h"
#include "Common/GameAudio.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/Controlbar.h"
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/string_base.h"

// Visible genuine lifetime body: owned UnicodeString5B804E is exactly the
// five-byte tailcall to wide releaseBuffer. This permits the compiler to
// inline cleanup instead of relying on the legacy destructor pin at36E70.
inline UnicodeString::~UnicodeString()
{
 ((StringBase<WideChar>*)this)->~StringBase<WideChar>();
}

// BFME stores ControlBar::m_genArrow at this offset. The ZH header places it
// at +0x2fc, so this transition keeps the corrected view local to its one
// direct field read.
class BfmeControlBarArrowImageView
{
public:
	char m_padding[0x2bc];
	const Image *m_genArrow;
};

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
static void drawTypeText( GameWindow *window, DisplayString *str);


void FadeTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < FADETRANSITION_START || frame > FADETRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("FadeTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case FADETRANSITION_START:
		{
			
			if(m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case FADETRANSITION_FADE_IN_1:
	case FADETRANSITION_FADE_IN_2:
	case FADETRANSITION_FADE_IN_3:
	case FADETRANSITION_FADE_IN_4:
	case FADETRANSITION_FADE_IN_5:
	case FADETRANSITION_FADE_IN_6:
	case FADETRANSITION_FADE_IN_7:
	case FADETRANSITION_FADE_IN_8:
	case FADETRANSITION_FADE_IN_9:
		m_win->winHide(TRUE);

		m_drawState = frame;
		break;
	case FADETRANSITION_END:
		{
			if(!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}


// BFME parameterises the frame bounds: retail compares against this+0x10 and
// this+0x14 where the reference uses the MAINMENUSCALEUPTRANSITION_START/_END
// constants. That has a knock-on effect -- a switch needs constant cases, so the
// two frame tests become an if/else-if chain rather than a switch.
//
// The reference's `frame == 1' block builds an AudioEventRTS and plays
// GUILogoSelect. Retail has no trace of it and could not have: that temporary
// has a destructor and would have forced an SEH frame onto a function that has
// none. So BFME does not play that click here at all.
struct BfmeScaleUpTransitionFields
{
	unsigned char m_unreconstructed_00[ 0x08 ];		///< vtable pointer at +0x00
	Bool m_isFinished;					///< retail this+0x08
	Bool m_isForward;					///< retail this+0x09
	unsigned char m_unreconstructed_0a[ 2 ];
	GameWindow *m_win;					///< retail this+0x0c
	Int m_startFrame;					///< retail this+0x10
	Int m_endFrame;						///< retail this+0x14
	ICoord2D m_pos;						///< retail this+0x18
	ICoord2D m_size;					///< retail this+0x20
	Int m_drawState;					///< retail this+0x28
	ICoord2D m_growPos;					///< retail this+0x2c
	ICoord2D m_growSize;					///< retail this+0x34
	ICoord2D m_incrementPos;				///< retail this+0x3c
	ICoord2D m_incrementSize;				///< retail this+0x44
	GameWindow *m_growWin;					///< retail this+0x4c
};

// winGetDisabledImage does NOT survive as a call: retail reads the image straight
// out of the window at win+0xb4, so it is an inline read over an array rather
// than the out-of-line accessor the other two window calls use.
struct BfmeTransitionWindowImages
{
	unsigned char m_unreconstructed_00[ 0xb4 ];
	const Image *m_disabledImage[ 1 ];			///< retail this+0xb4
};


// The medium variant is the same shape as MainMenuScaleUpTransition::update
// above, with two differences of its own: its grow window is at +0x44 rather than
// +0x4c, and it opens the start case by SHOWING m_win where the plain variant has
// that call commented out. It drops an audio block too -- the reference plays
// GUILogoMouseOver on the first forward frame and retail has no trace of it.
struct BfmeMediumScaleUpTransitionFields
{
	unsigned char m_unreconstructed_00[ 0x08 ];		///< vtable pointer at +0x00
	Bool m_isFinished;					///< retail this+0x08
	Bool m_isForward;					///< retail this+0x09
	unsigned char m_unreconstructed_0a[ 2 ];
	GameWindow *m_win;					///< retail this+0x0c
	Int m_startFrame;					///< retail this+0x10
	Int m_endFrame;						///< retail this+0x14
	unsigned char m_unreconstructed_18[ 0x28 - 0x18 ];
	Int m_drawState;					///< retail this+0x28
	unsigned char m_unreconstructed_2c[ 0x44 - 0x2c ];
	GameWindow *m_growWin;					///< retail this+0x44
};


// This transition's own layout: the base ends at +0x10, so position lands at
// +0x10, size at +0x18, draw state at +0x20, the grow window's position and size
// at +0x24 and +0x2c, the single increment at +0x34 and the grow window at +0x3c.
// Unlike the scale-up pair, its bounds really are constants here.
struct BfmeSmallScaleDownFields
{
	unsigned char m_unreconstructed_00[ 0x08 ];		///< vtable pointer and frame length
	Bool m_isFinished;					///< retail this+0x08
	Bool m_isForward;					///< retail this+0x09
	unsigned char m_pad0a[ 2 ];
	GameWindow *m_win;					///< retail this+0x0c
	ICoord2D m_pos;						///< retail this+0x10
	ICoord2D m_size;					///< retail this+0x18
	Int m_drawState;					///< retail this+0x20
	ICoord2D m_growPos;					///< retail this+0x24
	ICoord2D m_growSize;					///< retail this+0x2c
	ICoord2D m_incrementSize;				///< retail this+0x34
	GameWindow *m_growWin;					///< retail this+0x3c
};

// concat takes an explicit LENGTH in BFME, and str() reads the payload at
// m_data+8 -- the eight-byte string header again.
struct BfmeSmallScaleDownString
{
	void *m_data;

	// Declared, never defined: retail CALLS the copy-assignment where this tree's
	// AsciiString expands it inline with its null and refcount tests.
	BfmeSmallScaleDownString &operator=( const BfmeSmallScaleDownString &other );
	void concat( const char *text, Int length );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}
};

struct BfmeSmallScaleDownInstanceData
{
	unsigned char m_pad00[ 0x18c ];
	BfmeSmallScaleDownString m_decoratedNameString;		///< retail this+0x18c
};

// winGetEnabledImage takes NO index in BFME: retail reads the image straight out
// of the window at +0x48.
struct BfmeSmallScaleDownWindow
{
	unsigned char m_pad00[ 0x48 ];
	const Image *m_enabledImage;				///< retail this+0x48
};

// winGetWindowFromId is vtable slot 55 (+0xdc) on the window manager.
class BfmeSmallScaleDownWindowManager
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, Int id);	///< vtable +0xdc
};


void MainMenuSmallScaleDownTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < MAINMENUSMALLSCALEDOWNTRANSITION_START || frame > MAINMENUSMALLSCALEDOWNTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("MainMenuSmallScaleDownTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case MAINMENUSMALLSCALEDOWNTRANSITION_START:
		{
			
			if(m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(FALSE);
			m_growWin->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case MAINMENUSMALLSCALEDOWNTRANSITION_1:
	case MAINMENUSMALLSCALEDOWNTRANSITION_2:
	case MAINMENUSMALLSCALEDOWNTRANSITION_3:
	case MAINMENUSMALLSCALEDOWNTRANSITION_4:
	case MAINMENUSMALLSCALEDOWNTRANSITION_5:
		if(m_win)
			m_win->winHide(TRUE);
		if(m_growWin)
			m_growWin->winHide(TRUE);
		m_drawState = frame;
		break;
	case MAINMENUSMALLSCALEDOWNTRANSITION_END:
		{
			if(!m_isForward || !m_win || !m_growWin)
				break;
			m_win->winHide(TRUE);
			m_growWin->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}	
}


// Same parameterisation as the scale-up transitions: the frame handed to update
// and the clamp on the text length come from members at this+0x10 and this+0x14,
// not from the TEXTTYPETRANSITION_START/_END constants. The clamp is written as
// the ternary retail emits rather than through MIN.
struct BfmeTextTypeTransitionFields
{
	unsigned char m_unreconstructed_00[ 0x04 ];		///< vtable pointer at +0x00
	Int m_frameLength;					///< retail this+0x04
	Bool m_isFinished;					///< retail this+0x08
	Bool m_isForward;					///< retail this+0x09
	unsigned char m_pad0a[ 2 ];
	GameWindow *m_win;					///< retail this+0x0c
	Int m_startFrame;					///< retail this+0x10
	Int m_endFrame;						///< retail this+0x14
	ICoord2D m_pos;						///< retail this+0x18
	ICoord2D m_size;					///< retail this+0x20
	Int m_drawState;					///< retail this+0x28
	UnicodeString m_fullText;				///< retail this+0x2c
	UnicodeString m_partialText;				///< retail this+0x30
	DisplayString *m_dStr;					///< retail this+0x34
};

// The two strings are one pointer each; if that ever stops being true the
// offsets above silently shift, so say it out loud.
typedef char BfmeTextTypeTransitionStringWidth[
		(sizeof(UnicodeString) == 4) ? 1 : -1];

// CountUpTransition's retail object keeps the same transition prefix as the
// text style, then stores its integer counter after the two string slots.
// The shipped C++ base is eight bytes shorter than BFME's transition base, so
// this view is required for the member accesses in the retail body.
struct BfmeCountUpTransitionFields
{
	unsigned char m_unreconstructed_00[ 0x04 ];
	Int m_frameLength;
	Bool m_isFinished;
	Bool m_isForward;
	unsigned char m_pad0a[ 2 ];
	GameWindow *m_win;
	Int m_startFrame;
	Int m_endFrame;
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_drawState;
	UnicodeString m_fullText;
	UnicodeString m_unusedText;
	Int m_intValue;
	Int m_currentValue;
	Int m_countState;
};

typedef char BfmeCountUpTransitionStringWidth[
		(sizeof(UnicodeString) == 4) ? 1 : -1];

// Native BFME2 init35FDCA reads newDisplayString through slot14 (+38).
// BF1 used slot9 (+24); the vendored ZH manager has another layout.
class BfmeTransitionDisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual DisplayString *newDisplayString();		///< target vtable +0x38
};

// getLength inlines to a 16-bit read of the length in the string header at
// m_data+4; this tree's UnicodeString calls out of line for it instead.
struct BfmeTransitionUnicodeString
{
	const unsigned char *m_data;

	Int getLength() const
	{
		return m_data ? *(const unsigned short *)(m_data + 4) : 0;
	}
};


// Open-BFME5: convert TextTypeTransition::update from retail ASM to clean C++.
void TextTypeTransition::update( Int frame )
{
	BfmeTextTypeTransitionFields *self = (BfmeTextTypeTransitionFields *)this;

	self->m_drawState = -1;
	if(frame < self->m_startFrame || frame > self->m_endFrame)
	{
		return;
	}
	if(frame == self->m_startFrame)
		{
			if(!self->m_isForward && self->m_win )
			{
				self->m_win->winHide(TRUE);
				self->m_isFinished = TRUE;
			}
		}
	else if(frame == self->m_endFrame)
		{
			if(self->m_isForward && self->m_win )
			{
				self->m_win->winHide(FALSE);
				self->m_isFinished = TRUE;
			}
	}
	if(frame >= self->m_frameLength)
	{
		self->m_win->winHide(FALSE);

	}
	if(frame > self->m_startFrame && frame < self->m_frameLength)
	{
		self->m_win->winHide(TRUE);
		self->m_drawState = frame;
		if(self->m_isForward)
		{
			WideChar character = ((StringBase<WideChar> *)&self->m_fullText)->getCharAt(frame - 1);
			((StringBase<WideChar> *)&self->m_partialText)->concat(&character, 1);
		}
		else
		{
			((StringBase<WideChar> *)&self->m_partialText)->removeLastChar();
		}
	}
}


void CountUpTransition::reverse( void )
{
	if( m_win->winIsHidden() )
	{
		m_isForward = FALSE;
		m_isFinished = TRUE;
		m_frameLength = 0;
		return;
	}
	m_isFinished = FALSE;
	m_isForward = FALSE;

}


void ControlBarArrowTransition::update( Int frame )
{
	m_drawState = -1;
	if(frame < CONTROLBARARROWTRANSITION_START || frame > CONTROLBARARROWTRANSITION_END)
	{
		DEBUG_ASSERTCRASH(FALSE, ("ControlBarArrowTransition::update - Frame is out of the range the this update can handle %d", frame));
		return;
	}
	switch (frame) {
	case CONTROLBARARROWTRANSITION_START:
		{
			m_isFinished = TRUE;
		}
		break;
	case CONTROLBARARROWTRANSITION_END:
		{
			m_isFinished = TRUE;
		}
	}	
	m_drawState = frame;	
}


// BFME removed the Zero Hour audio-event body from the fire-sound case but
// retains the transition's original fall-through state machine.
void ReverseSoundTransition::update( Int frame )
{
	if(frame < REVERSESOUNDTRANSITION_START || frame > REVERSESOUNDTRANSITION_END)
		return;
	switch(frame) {
	case REVERSESOUNDTRANSITION_START:
		if(m_isForward)
			break;
		m_isFinished = TRUE;
		break;
	case REVERSESOUNDTRANSITION_FIRESOUND:
		if(m_isForward)
			m_isFinished = TRUE;
		break;
	case REVERSESOUNDTRANSITION_END:
		if(m_isForward)
			m_isFinished = TRUE;
		break;
	}
}


  // end drawStaticTextText

// Direct BF1 f989 clean init; target WB F11D80 corroborates the calls.
// ?init@TextTypeTransition@@UAEXPAVGameWindow@@@Z
void TextTypeTransition::init( GameWindow *win )
{
	BfmeTextTypeTransitionFields *self = (BfmeTextTypeTransitionFields *)this;

	if(win)
	{
		self->m_win = win;
		self->m_win->winGetSize(&self->m_size.x, &self->m_size.y);
		self->m_win->winGetScreenPosition(&self->m_pos.x, &self->m_pos.y );
	}
	self->m_isForward = FALSE;
	update(self->m_startFrame);
	self->m_isFinished = FALSE;
	self->m_isForward = TRUE;
	self->m_dStr = ((BfmeTransitionDisplayStringManager *)TheDisplayStringManager)->newDisplayString();
	self->m_fullText = GadgetStaticTextGetText(self->m_win);		
	Int length = ((const BfmeTransitionUnicodeString *)&self->m_fullText)->getLength();
	self->m_frameLength = length < self->m_endFrame ? length : self->m_endFrame;
}


// Target display-string virtual slots from native35FB6A. The four-word
// draw slot takes two observed flags after x/y; colors are a separate slot.
class BfmeTransitionTextDrawString
{
public:
 virtual void slot00(); virtual void setText(UnicodeString);
 virtual void slot08(); virtual Int getTextLength();
 virtual void slot10(); virtual void slot14();
 virtual void setFont(GameFont *); virtual GameFont *getFont();
 virtual void setWordWrap(Int); virtual void setWordWrapCentered(Bool);
 virtual void setColors(Int,Int);
 virtual void slot2c(); virtual void slot30(); virtual void slot34();
 virtual void draw(Int,Int,Int,Int);
 virtual void getSize(Int*,Int*);
 virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
 virtual void setClipRegion(IRegion2D*);
};

// Reference-first: BF1 f989 and ZH drawTypeText; target364 retains the
// whole position/clip/wrap/color purpose and the two centered branches.
static void drawTypeText(GameWindow *window,DisplayString *drawString)
{
 TextData *tData=(TextData*)window->winGetUserData();
 Int textColor=window->winGetEnabledTextColor();
 Int textDropColor=window->winGetEnabledTextBorderColor();
 Int textWidth,textHeight,wordWrap;
 BfmeTransitionTextDrawString *text=(BfmeTransitionTextDrawString*)tData->text;
 BfmeTransitionTextDrawString *str=(BfmeTransitionTextDrawString*)drawString;
 ICoord2D origin,size,textPos;
 IRegion2D clipRegion;
 if(text==NULL || text->getTextLength()==0) return;
 GameFont *font=text->getFont();
 str->setFont(font);
 window->winGetScreenPosition(&origin.x,&origin.y);
 window->winGetSize(&size.x,&size.y);
 wordWrap=size.x-10;
 text->setWordWrap(wordWrap);
 str->setWordWrap(wordWrap);
 if(BitTest(window->winGetStatus(),WIN_STATUS_WRAP_CENTERED)) {
  str->setWordWrapCentered(TRUE);text->setWordWrapCentered(TRUE);
 } else {
  text->setWordWrapCentered(FALSE);str->setWordWrapCentered(FALSE);
 }
 text->getSize(&textWidth,&textHeight);
 clipRegion.lo.x=origin.x;clipRegion.lo.y=origin.y;
 clipRegion.hi.x=size.x;clipRegion.hi.x+=origin.x;clipRegion.hi.y=origin.y+size.y;
 if(tData->centered) {
  textPos.x=origin.x+(size.x/2)-(textWidth/2);
  textPos.y=origin.y+(size.y/2)-(textHeight/2);
 } else {
  textPos.x=origin.x+7;
  textPos.y=origin.y+(size.y/2)-(textHeight/2);
 }
 str->setClipRegion(&clipRegion);
 str->setColors(textColor,textDropColor);
 str->draw(textPos.x,textPos.y,1,1);
}

void TextTypeTransition::draw()
{
 BfmeTextTypeTransitionFields *self=(BfmeTextTypeTransitionFields*)this;
 if(self->m_drawState>self->m_startFrame && self->m_drawState<self->m_frameLength) {
  ((BfmeTransitionTextDrawString*)self->m_dStr)->setText(self->m_partialText);
  drawTypeText(self->m_win,self->m_dStr);
 }
}
