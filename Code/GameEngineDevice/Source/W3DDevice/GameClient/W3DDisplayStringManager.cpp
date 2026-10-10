// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
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

// FILE: W3DDisplayStringManager.cpp //////////////////////////////////////////////////////////////
// Created:   Colin Day, July 2001
// Desc:      Access for creating game managed display strings
//
// Ported from Zero Hour's GameEngineDevice/Source/W3DDevice/GameClient/
// W3DDisplayStringManager.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). The classes below are a minimal
// BFME 2 view: member offsets and virtual slots are the ones the retail
// bodies use, and everything they do not touch is left opaque.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define TRUE true
#define FALSE false

// BFME 2 GameClient: getFrame() is virtual (slot 31) rather than ZH's inline.
class GameClient
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30();
	virtual UnsignedInt getFrame( void );
};
extern GameClient *TheGameClient;

// BFME 2 Render2DSentenceClass: Reset() is its first virtual.
class Render2DSentenceClass
{
public:
	virtual void Reset( void );
private:
	char m_opaque[ 0xC4 - 4 ];
};

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont( const AsciiString *name, float pointSize, Bool bold );
};
extern FontLibrary *TheFontLibrary;

struct DrawGroupInfo
{
	AsciiString m_fontName;															///< 0x00
	Int m_fontSize;																			///< 0x04
	Bool m_fontIsBold;																	///< 0x08
};
// VA 0x00E01CD8 (.data, zero-filled in retail): the rowed body loads this pointer
// with mov eax,[0x00E01CD8] and reads m_fontName / m_fontSize / m_fontIsBold through
// it. GameClient's init stores a freshly constructed DrawGroupInfo here at run time,
// so the slot is defined here, in the unit that carries the class, as the zero retail
// holds.
DrawGroupInfo *TheDrawGroupInfo = 0;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void vslot01() = 0; virtual void vslot02() = 0; virtual void vslot03() = 0;
	virtual void vslot04() = 0; virtual void vslot05() = 0; virtual void vslot06() = 0;
	virtual void vslot07() = 0; virtual void vslot08() = 0; virtual void vslot09() = 0;
	virtual void vslot10() = 0; virtual void vslot11() = 0; virtual void vslot12() = 0;
	// cl 7.1 lays overloaded virtuals out in reverse declaration order:
	// fetch(const char *) is slot 13, fetch(const AsciiString &) slot 14.
	virtual UnicodeString fetch( const AsciiString &label, Bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;
};
extern GameTextInterface *TheGameText;

enum { MAX_GROUPS = 10 };

struct FontDesc
{
	AsciiString name;
	Int size;
	Bool bold;
};

class GlobalLanguage
{
public:
	char m_opaque00[ 0xB0 ];
	FontDesc m_defaultDisplayStringFont;								///< 0xB0
};
extern GlobalLanguage *TheGlobalLanguageData;

class DisplayString
{
public:
	virtual ~DisplayString( void );
	virtual void setText( UnicodeString text );
	virtual UnicodeString getText( void );
	virtual Int getTextLength( void );
	virtual void notifyTextChanged( void );
	virtual void reset( void );
	virtual void setFont( GameFont *font );
	DisplayString *next( void ) { return m_next; }
protected:
	void *m_textString;																	///< 0x04
	void *m_font;																				///< 0x08
	DisplayString *m_next;															///< 0x0C
	DisplayString *m_prev;															///< 0x10
};

class W3DDisplayString : public DisplayString
{
	friend class W3DDisplayStringManager;
public:
	W3DDisplayString( void );
protected:
	Render2DSentenceClass m_textRenderer;								///< 0x14
	Render2DSentenceClass m_textRendererHotKey;					///< 0xD8
	char m_opaque19C[ 4 ];
	Bool m_textChanged;																	///< 0x1A0
	char m_opaque1A1[ 0x1F4 - 0x1A1 ];
	UnsignedInt m_lastResourceFrame;										///< 0x1F4
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager( void );
	virtual void init( void );
	virtual void postProcessLoad( void );
	virtual void reset( void );
	virtual void update( void );
	virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10();
	virtual void vslot11(); virtual void vslot12(); virtual void vslot13();
	virtual DisplayString *newDisplayString( void ) = 0;
protected:
	void link( DisplayString *string );
public:
protected:
	char m_opaque04[ 8 ];
	DisplayString *m_stringList;												///< 0x0C
	DisplayString *m_currentCheckpoint;									///< 0x10
};

class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual void postProcessLoad( void );
	virtual void update( void );
	virtual DisplayString *newDisplayString( void );
	virtual DisplayString *getGroupNumeralString( Int numeral );
protected:
	DisplayString *m_groupNumeralStrings[ MAX_GROUPS ];		///< 0x14
	DisplayString *m_formationLetterDisplayString;				///< 0x3C
};

//-------------------------------------------------------------------------------------------------
void W3DDisplayStringManager::postProcessLoad( void )
{
	// Get the font.
	GameFont *font = TheFontLibrary->getFont(
		&TheDrawGroupInfo->m_fontName,
		TheDrawGroupInfo->m_fontSize,
		TheDrawGroupInfo->m_fontIsBold );
	
	for (Int i = 0; i < MAX_GROUPS; ++i) 
	{
		m_groupNumeralStrings[i] = newDisplayString();
		m_groupNumeralStrings[i]->setFont(font);

 		AsciiString displayNumber;
 		displayNumber.format("NUMBER:%d", i);
 		m_groupNumeralStrings[i]->setText(TheGameText->fetch(displayNumber));
	}

	m_formationLetterDisplayString = newDisplayString();
	m_formationLetterDisplayString->setFont(font);
	AsciiString displayLetter;
	displayLetter.format("LABEL:FORMATION");
	m_formationLetterDisplayString->setText(TheGameText->fetch(displayLetter));

}

//-------------------------------------------------------------------------------------------------
/** Update method for our display string Manager ... if it's been too
	* long since the last time a string has been rendered, we will free
	* the rendering resources of the string, if it needs to render again
	* the DisplayString will have to rebuild the rendering data before
	* the draw will work */
//-------------------------------------------------------------------------------------------------
void W3DDisplayStringManager::update( void )
{
	W3DDisplayString *string = static_cast<W3DDisplayString *>(m_stringList);

	// if the m_currentCheckpoint is valid, use it for the starting point for the search
	if (m_currentCheckpoint) {
		string = static_cast<W3DDisplayString *>(m_currentCheckpoint);
	}

	UnsignedInt currFrame = TheGameClient->getFrame();
	const UnsignedInt w3dCleanupTime = 60;  /** any string not rendered after
																					this many frames will have its
																					render resources freed */

	int numStrings = 10;
	// looping through all the strings eats up a lot of ambient time. Instead,
	// loop through 10 (arbitrarily chosen) or till the end is hit.
	while ( numStrings-- && string)
	{

		//
		// has this string "expired" in terms of using resources, a string
		// with a resource frame of zero isn't using any resources at all
		//
		if( string->m_lastResourceFrame != 0 &&
				currFrame - string->m_lastResourceFrame > w3dCleanupTime )
		{

			// free the resources
			string->m_textRenderer.Reset();
			string->m_textRendererHotKey.Reset();
			//
			// mark data in the string as changed so that if it needs to
			// be drawn again it will know to reconstruct the render data
			//
			string->m_textChanged = TRUE;

			//
			// set the last resource frame to zero, this allows us to ignore it
			// in future cleanup passes of this update routine
			//
			string->m_lastResourceFrame = 0;

		}  // end if

		// move to next string
		string = static_cast<W3DDisplayString *>(string->next());

	}  // end while

	// reset the starting point for our next search
	m_currentCheckpoint = string;
}  // end update

//-------------------------------------------------------------------------------------------------
/** Allocate a new display string and tie it to the master list so we
	* can keep track of it */
//-------------------------------------------------------------------------------------------------
DisplayString *W3DDisplayStringManager::newDisplayString( void )
{
	DisplayString *newString = new W3DDisplayString;

	// sanity
	if( newString == 0 )
		return 0;

	// assign a default font
	if (TheGlobalLanguageData && !TheGlobalLanguageData->m_defaultDisplayStringFont.name.isEmpty())
	{
		newString->setFont(TheFontLibrary->getFont(
			&TheGlobalLanguageData->m_defaultDisplayStringFont.name,
			TheGlobalLanguageData->m_defaultDisplayStringFont.size,
			TheGlobalLanguageData->m_defaultDisplayStringFont.bold) );
	}
	else
	{
		AsciiString fontName("Times New Roman");
		newString->setFont( TheFontLibrary->getFont( &fontName, 12, FALSE ) );
	}

	// link string to list
	link( newString );

	// return our new string
	return newString;

}  // end newDisplayString

//-------------------------------------------------------------------------------------------------
DisplayString *W3DDisplayStringManager::getGroupNumeralString( Int numeral )
{
	// BFME 2 falls back to the first numeral where ZH crashed in debug
	if (numeral < 0 || numeral > MAX_GROUPS - 1 )
		return m_groupNumeralStrings[0];

	return m_groupNumeralStrings[numeral];
}
