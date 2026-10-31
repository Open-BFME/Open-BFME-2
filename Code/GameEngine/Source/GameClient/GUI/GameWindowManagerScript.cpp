// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// platformsdk
// dxsdk
// stlport
// Ported from the Generals Zero Hour window-script parser.
// Retail BFME 2 supplies the creation record and parser interfaces.
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

// FILE: GameWindowManagerScript.cpp //////////////////////////////////////////
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
// File name: GameWindowManagerScript.cpp
//
// Created:   Colin Day, June 2001
//						Dean Iverson, May 1998
//
// Desc:      Reading window definition files from disk for the window manager
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
// BFME2's UnicodeString is a StringBase<unsigned short> subclass; skip Zero
// Hour's own class.
#include "unicode_string.h"
#define UNICODESTRING_H
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/File.h"
#include "WindowScriptShims/Common/FileSystem.h"
#include "Common/GameMemory.h"
#include "Common/NameKeyGenerator.h"
#include "Common/FunctionLexicon.h"
#include "GameClient/Display.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "WindowScriptShims/GameClient/GameWindowManager.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTabControl.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameText.h"
#include "GameClient/HeaderTemplate.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


namespace NativeScriptCrt {
extern "C" __declspec(dllimport) char *__cdecl strtok(char *, const char *);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
}
// DEFINES ////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TYPES //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

enum
{
	WIN_BUFFER_LENGTH  = 2048,
	WIN_STACK_DEPTH    = 10,
};

//-------------------------------------------------------------------------------------------------
/** Layout parse structure ... these data items apply to the window file itself,
	* they are not associated with any window, but rather just a block of data in
	* every file */
//-------------------------------------------------------------------------------------------------
struct LayoutScriptParse
{

	char *name;
	Bool (*parse)( char *token, char *buffer, UnsignedInt version, WindowLayoutInfo *info );

};

// GameWindowParse ------------------------------------------------------------
/** used to match database fields to parsing functions */
//-----------------------------------------------------------------------------
struct GameWindowParse
{

	char *name;
	Bool (*parse)( char *token, WinInstanceData *, char *, void * );

};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// window methods and their string representations

#include "GameWindowManagerRecordView.h"
#include "WindowScriptCreateRecord.h"
WindowScriptCreateRecord g_windowScriptCreateRecord;
class ScriptDisplaySlots {
public:
#define DS(n) virtual void slot##n();
DS(0) DS(1) DS(2) DS(3) DS(4) DS(5) DS(6) DS(7)
DS(8) DS(9) DS(10) DS(11) DS(12) DS(13) DS(14) DS(15)
#undef DS
virtual UnsignedInt getWidth();
virtual UnsignedInt getHeight();
};
class ScriptFactoryManagerSlots {
public:
#define MS(n) virtual void slot##n();
MS(0) MS(1) MS(2) MS(3) MS(4) MS(5) MS(6) MS(7) MS(8) MS(9)
MS(10) MS(11) MS(12) MS(13) MS(14) MS(15) MS(16) MS(17) MS(18) MS(19)
MS(20) MS(21) MS(22) MS(23) MS(24) MS(25) MS(26) MS(27) MS(28) MS(29)
MS(30) MS(31) MS(32) MS(33)
virtual GameWindow *createFromView(GadgetCreateView *);
MS(35) MS(36) MS(37) MS(38) MS(39) MS(40) MS(41) MS(42) MS(43) MS(44)
MS(45) MS(46) MS(47) MS(48) MS(49) MS(50) MS(51) MS(52) MS(53) MS(54)
MS(55) MS(56) MS(57) MS(58)
#undef MS
virtual Int send(GameWindow *, UnsignedInt, UnsignedInt, UnsignedInt);
};
GameWindow *createGadget(char *, void *, GadgetCreateView *, GameWindow *);
// The split callback parsers reference the canonical data-ledger names.
// Keep these strings in their original initialization order and expose this
// existing storage: native DIR32 bindings are RVA A01308/A0130C/A01310.
// The compiler-generated initializer/cleanup rows still verify this storage.
// Retail's initializers call the out-of-line AsciiString() at 0x00326BE6
// rather than folding the construction away.
#pragma inline_depth( 0 )
AsciiString g_systemCallbackName;
AsciiString g_inputCallbackName;
AsciiString g_tooltipCallbackName;
// Expose the original fourth string at native RVA A01314, preserving order.
AsciiString g_drawCallbackName;
#pragma inline_depth()

// default visual properties
static Color defEnabledColor		= 0;
static Color defDisabledColor		= 0;
static Color defBackgroundColor	= 0;
static Color defHiliteColor			= 0;
static Color defSelectedColor		= 0;
static Color defTextColor				= 0;
static GameFont  *defFont				= NULL;

//
// These strings must be in the same order as they are in their definitions 
// (see WIN_STATUS_* enums and GWS_* enums).
//
const char *WindowStatusNames[] = { "ACTIVE", "TOGGLE", "DRAGABLE", "ENABLED", "HIDDEN", 
														  "ABOVE", "BELOW", "IMAGE", "TABSTOP", "NOINPUT",
														  "NOFOCUS", "DESTROYED", "BORDER",
														  "SMOOTH_TEXT", "ONE_LINE", "NO_FLUSH", "SEE_THRU", 
															"RIGHT_CLICK", "WRAP_CENTERED", "CHECK_LIKE","HOTKEY_TEXT",
															"USE_OVERLAY_STATES", "NOT_READY", "FLASHING", "ALWAYS_COLOR",
															"ON_MOUSE_DOWN",
															NULL };

const char *WindowStyleNames[] = { "PUSHBUTTON",	"RADIOBUTTON",	"CHECKBOX",
														 "VERTSLIDER",	"HORZSLIDER",		"SCROLLLISTBOX",
														 "ENTRYFIELD",	"STATICTEXT",		"PROGRESSBAR",
														 "USER",				"MOUSETRACK",		"ANIMATED",
														 "TABSTOP",			"TABCONTROL",		"TABPANE",
														 "COMBOBOX",
														 NULL };

// Implement a stack to keep track of parent/child nested window descriptions.
static GameWindow *windowStack[ WIN_STACK_DEPTH ];
static GameWindow **stackPtr;

// for parsing
static char *seps = " =;\n\r\t";
WinDrawData enabledDropDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData disabledDropDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData hiliteDropDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes

WinDrawData enabledEditBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData disabledEditBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData hiliteEditBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes

WinDrawData enabledListBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData disabledListBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes
WinDrawData hiliteListBoxDrawData[ MAX_DRAW_DATA ];  ///< for combo boxes

WinDrawData enabledUpButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData disabledUpButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData hiliteUpButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData enabledDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData disabledDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData hiliteDownButtonDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData enabledSliderDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData disabledSliderDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData hiliteSliderDrawData[ MAX_DRAW_DATA ];  ///< for list boxes and combo boxes
WinDrawData enabledSliderThumbDrawData[ MAX_DRAW_DATA ];  ///< for sliders and list boxes and combo boxes
WinDrawData disabledSliderThumbDrawData[ MAX_DRAW_DATA ];  ///< for sliders and list boxes and combo boxes
WinDrawData hiliteSliderThumbDrawData[ MAX_DRAW_DATA ];  ///< for sliders and list boxes and combo boxes

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
static GameWindow *parseWindow( File *inFile, char *buffer );

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// parseBitFlag ===============================================================
/** Parse one of the "flags" referred to below in the header comment
	* for ParseBitString().  Sets the appropriate bit in the 'bits' arg,
	* if successful.  Returns TRUE on success, else FALSE. */
//=============================================================================
static Bool parseBitFlag( const char *flagString, UnsignedInt *bits, 
													const char **flagList )
{
	const char **c;
	int i;

	for( i = 0, c = flagList; *c; i++, c++ )
	{

		if( !_strcmpi( *c, flagString ) )
		{
			*bits |= (1 << i);
			return TRUE;
		}

	}

	return FALSE;

}  // end parseBitFlag

// parseBitString =============================================================
/** Given a character string of the form 'A+B+C+D', parse the
	* flags separated by the '+' symbols into a bitfield stored in the 'bits'
	* argument.
	* Note that this routine does not clear any bits, only sets them. */
//=============================================================================
static void parseBitString( const char *inBuffer, UnsignedInt *bits, const char **flagList )
{
	char buffer[256];
	char *tok;

	// do not modify the inBuffer argument
	strcpy( buffer, inBuffer );

	if( strncmp( buffer, "NULL", 4 ) )
	{
		for( tok = strtok( buffer, "+" ); tok; tok = strtok( NULL, "+" ) )
		{
			if ( !parseBitFlag( tok, bits, flagList ) )
			{
				DEBUG_LOG(( "ParseBitString: Invalid flag '%s'.\n", tok ));
			}
		}
	}

}  // end parseBitString

// Native File calls use read at slot 3 and scanString at slot 9.
class GoalScriptFileSlots {
public:
 virtual void s0(); virtual void s1(); virtual void close();
 virtual int read(void*,int); virtual int write(const void*,int);
 virtual int seek(int,int); virtual void nextLine(char*,int);
 virtual bool scanInt(int&); virtual bool scanReal(float&);
 virtual bool scanString(AsciiString&);
};

// readUntilSemicolon =========================================================
//=============================================================================
static void readUntilSemicolon( File *fp, char *buffer, int maxBufLen )
{
	int i = 0;
	Bool start = TRUE;

	while( i < maxBufLen ) 
	{

		// get next character
		((GoalScriptFileSlots *)fp)->read(buffer + i, 1);

		// make all whitespace characters spaces
		if( NativeScriptCrt::isspace( buffer[ i ] ) )
		{

			if( start == FALSE )
				buffer[ i++ ] = ' ';

		} 
		else 
		{

			start = FALSE;

			if( buffer[ i ] == ';' ) 
			{

				// found end of data chunk
				buffer[ i ] = '\000';
				return;

			}

			i++;
		}

	}

	DEBUG_LOG(( "ReadUntilSemicolon: ERROR - Read buffer overflow - input truncated.\n" ));

	buffer[ maxBufLen - 1 ] = '\000';

}  // end readUntilSemicolon

// scanBool ===================================================================
//=============================================================================
static Int scanBool( const char *source, Bool& val )
{
	Int temp = 0;
	Int ret = sscanf( source, "%d", &temp );
	val = (Bool)temp;

	return ret;
}  // end scanBool

// scanShort ==================================================================
//=============================================================================
static Int scanShort( const char *source, Short& val )
{
	Int temp = 0;
	Int ret = sscanf( source, "%d", &temp );
	val = (Short)temp;

	return ret;
}  // end scanShort

// scanInt ====================================================================
//=============================================================================
static Int scanInt( const char *source, Int& val )
{
	Int ret = sscanf( source, "%d", &val ); // not strictly necessary to wrap this, but it's more consistent

	return ret;
}  // end scanInt

// scanUnsignedInt ============================================================
//=============================================================================
static Int scanUnsignedInt( const char *source, UnsignedInt& val )
{
	Int ret = sscanf( source, "%d", &val ); // not strictly necessary to wrap this, but it's more consistent

	return ret;
}  // end scanUnsignedInt

// resetWindowStack ===========================================================
//=============================================================================
#pragma optimize("s", on)
void resetWindowStack( void )
{

  memset( windowStack, 0, sizeof( windowStack ) );
  stackPtr = windowStack;

}  // end resetWindowStack
#pragma optimize("", on)

// resetWindowDefaults ========================================================
//=============================================================================
void resetWindowDefaults( void )
{

	defEnabledColor = 0;
	defDisabledColor = 0;
	defBackgroundColor = 0;
	defHiliteColor = 0;
	defSelectedColor = 0;
	defTextColor = 0;
	defFont = 0;

}  // end resetWindowDefaults

// peekWindow =================================================================
//=============================================================================
GameWindow *peekWindow( void )
{
  if (stackPtr == windowStack)
    return NULL;
  
  return *(stackPtr - 1);

}  // end peekWindow

// popWindow ==================================================================
//=============================================================================
static GameWindow *popWindow( void )
{

  if( stackPtr == windowStack )
    return NULL;
  stackPtr--;

  return *stackPtr;

}  // end popWindow

// pushWindow =================================================================
//=============================================================================
static void pushWindow( GameWindow *window )
{

  if( stackPtr == &windowStack[ WIN_STACK_DEPTH - 1 ] ) 
	{

    DEBUG_LOG(( "pushWindow: Warning, stack overflow\n" ));
    return;

  }  // end if

  *stackPtr++ = window;

}  // end pushWindow

// parseColor =================================================================
/** Parse a color entry and store it in the value pointed to by the 
	* 'color' parm. */
//=============================================================================
static Bool parseColor( Color *color, char *buffer )
{
  char *c;
  Byte red, green, blue;

	c = strtok( buffer, " \t\n\r" );
  red = atoi(c);

	c = strtok( NULL, " \t\n\r" );
  green = atoi(c);

	c = strtok( NULL, " \t\n\r" );
  blue = atoi(c);

	*color = TheWindowManager->winMakeColor( red, green, blue, 255 );

  return TRUE;

}  // end parseColor

// parseDefaultColor ==========================================================
/** Parse a default color entry and store it in the value pointed to by 
	* the 'color' parm. */
//=============================================================================
static Bool parseDefaultColor( Color *color, File *inFile, char *buffer )
{
	// eat '=' 
//	fscanf( inFile, "%*s" );
	AsciiString str;
	((GoalScriptFileSlots*)inFile)->scanString(str);

  // Read the rest of the color definition
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

  if (!strcmp( buffer, "TRANSPARENT" ))
	{
		
		*color = WIN_COLOR_UNDEFINED;

	}  // end if
  else
    parseColor( color, buffer );

  return TRUE;

}  // end parseDefaultColor

// parseDefaultFont ===========================================================
/** Parse the default font */
//=============================================================================
static Bool parseDefaultFont( GameFont *font, File *inFile, char *buffer )
{

	// eat '=' 
//	fscanf( inFile, "%*s" );
	AsciiString str;
	((GoalScriptFileSlots*)inFile)->scanString(str);

  // Read the rest of the color definition
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

	/// @todo font parsing for window files work needed here
//	*font = GetFont( buffer );
//	if( *font == NULL )
//		return FALSE;

	return TRUE;

}  // end parseDefaultFont

// parseTooltip ===============================================================
/** Parse the tooltip field */
//=============================================================================
// The retail body is rowed in GameWindowManagerScript_parseTooltip.cpp; call that one.
Bool parseTooltip( char *token, WinInstanceData *instData, char *buffer, void *data );

// parseScreenRect ============================================================
/** Parse the screen rect entry which tells us the position and size
	* of window.  Note we scale for the current resolution if needed
	* and adjust to make the screen rect coords relative to any parent
	* if present */
//=============================================================================
static Bool parseScreenRect( char *token, char *buffer,
														 Int *x, Int *y, Int *width, Int *height )
{
	GameWindow *parent = peekWindow();
	IRegion2D screenRegion;
	ICoord2D createRes;  // creation resolution
	char *seps = " ,:=\n\r\t";
	char *c;

	c = NativeScriptCrt::strtok( NULL, seps );  // UPPERLEFT token
	c = NativeScriptCrt::strtok( NULL, seps );  // x position
	scanInt( c, screenRegion.lo.x );
	c = NativeScriptCrt::strtok( NULL, seps );  // y posotion
	scanInt( c, screenRegion.lo.y );

	c = NativeScriptCrt::strtok( NULL, seps );  // BOTTOMRIGHT token
	c = NativeScriptCrt::strtok( NULL, seps );  // x position
	scanInt( c, screenRegion.hi.x );
	c = NativeScriptCrt::strtok( NULL, seps );  // y posotion
	scanInt( c, screenRegion.hi.y );

	c = NativeScriptCrt::strtok( NULL, seps );  // CREATIONRESOLUTION token
	c = NativeScriptCrt::strtok( NULL, seps );  // x creation resolution
	scanInt( c, createRes.x );
	c = NativeScriptCrt::strtok( NULL, seps );  // y creation resolution
	scanInt( c, createRes.y );

	//
	// shrink or expand the screen region by the ratio of the current
	// resolution divided by the creation resolution
	//
	Real xScale = (Real)((ScriptDisplaySlots *)TheDisplay)->getWidth() / (Real)createRes.x;
	Real yScale = (Real)((ScriptDisplaySlots *)TheDisplay)->getHeight() / (Real)createRes.y;
	screenRegion.lo.x = (Int)((Real)screenRegion.lo.x * xScale);
	screenRegion.lo.y = (Int)((Real)screenRegion.lo.y * yScale);
	screenRegion.hi.x = (Int)((Real)screenRegion.hi.x * xScale);
	screenRegion.hi.y = (Int)((Real)screenRegion.hi.y * yScale);

	//
	// given the screen region upper left compute the upper left that we
	// will give this window, if we have a parent note that the position
	// is relative to the parent client area, if no parent is present
	// we're talking about the screen
	//
	if( parent )
	{
		ICoord2D parentScreenPos;

		// get parent position on screen
		parent->winGetScreenPosition( &parentScreenPos.x, &parentScreenPos.y );

		// save x and y with parent position as relative (0,0) location
		*x = screenRegion.lo.x - parentScreenPos.x;
		*y = screenRegion.lo.y - parentScreenPos.y;

	}  // end if
	else
	{

		*x = screenRegion.lo.x;
		*y = screenRegion.lo.y;

	}  // end else

	// save our width and height from the adjusted screen region locations
	*width = screenRegion.hi.x - screenRegion.lo.x;
	*height = screenRegion.hi.y - screenRegion.lo.y;

	return TRUE;

}  // end parseScreenRect

// parseImageOffset ===========================================================
/** Parse the image draw offset */
//=============================================================================
static Bool parseImageOffset( char *token, WinInstanceData *instData, 
															char *buffer, void *data )
{
  char *c;

	c = strtok( buffer, " \t\n\r" );
	instData->m_imageOffset.x = atoi( c );

	c = strtok( NULL, " \t\n\r" );
	instData->m_imageOffset.y = atoi( c );
  
  return TRUE;

}  // end parseImageOffset

// parseFont ==================================================================
/** Parse the font field */
//=============================================================================
// The retail body is rowed in GameWindowManagerScript_parseFont.cpp; call that one.
Bool parseFont( char *token, WinInstanceData *instData, char *buffer, void *data );

// parseName =================================================================
/** Parse the NAME field */
//=============================================================================
static Bool parseName( char *token, WinInstanceData *instData,
											 char *buffer, void *data )
{
	char *c, *ptr;
//	char *seps = " ,\n\r\t";
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while( *ptr != '"' )
		ptr++;
	ptr++;  // skip the first "
	c = strtok( ptr, stringSeps );  // name value
	instData->m_decoratedNameString = c;

	// given the name assign a window ID from the
	assert( TheNameKeyGenerator );
	if( TheNameKeyGenerator )
		instData->m_id = (Int)TheNameKeyGenerator->nameToKey( instData->m_decoratedNameString );
	
	return TRUE;

}  // end parseName

// parseStatus ================================================================
/** Parse the STATUS field */
//=============================================================================
static Bool parseStatus( char *token, WinInstanceData *instData, 
												 char *buffer, void *data )
{

  instData->m_status = 0;
  parseBitString( buffer, &instData->m_status, WindowStatusNames );

  return TRUE;

}  // end parseStatus

// parseStyle =================================================================
/** Parse the STYLE field */
//=============================================================================
static Bool parseStyle( char *token, WinInstanceData *instData, 
												char *buffer, void *data )
{

  instData->m_style = 0;
  parseBitString( buffer, &instData->m_style, WindowStyleNames );

  return TRUE;

}  // end parseStyle

// parseSystemCallback ========================================================
/** Parse the system method callback for a window */
//=============================================================================
Bool parseSystemCallback( char *token, WinInstanceData *instData,
																 char *buffer, void *data );  // end parseSystemCallback

// parseInputCallback =========================================================
/** Parse the Input method callback for a window */
//=============================================================================
Bool parseInputCallback( char *token, WinInstanceData *instData,
																char *buffer, void *data );  // end parseInputCallback

// parseTooltipCallback =======================================================
/** Parse the Tooltip method callback for a window */
//=============================================================================
Bool parseTooltipCallback( char *token, WinInstanceData *instData,
																  char *buffer, void *data );  // end parseTooltipCallback

// parseDrawCallback ==========================================================
/** Parse the Draw method callback for a window */
//=============================================================================
Bool parseDrawCallback( char *token, WinInstanceData *instData,
															 char *buffer, void *data );  // end parseDrawCallback

// parseHeaderTemplate ==========================================================
/** Parse the Draw method callback for a window */
//=============================================================================
static Bool parseHeaderTemplate( char *token, WinInstanceData *instData,
															 char *buffer, void *data )
{
	char *c, *ptr;
//	char *seps = " ,\n\r\t";
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while( *ptr != '"' )
		ptr++;
	ptr++;  // skip the first "
	c = strtok( ptr, stringSeps );  // name value

	// save a pointer of the function address
	DEBUG_ASSERTCRASH( TheNameKeyGenerator && TheFunctionLexicon, ("Invalid singletons") );
	
	instData->m_headerTemplateName = c;
	
	return TRUE;

}  // end parseDrawCallback

// parseListboxData ===========================================================
/** Parse listbox data entry */
//=============================================================================
// The retail body is rowed in GameWindowManagerScript_parseListboxData.cpp; call that one.
Bool parseListboxData( char *token, WinInstanceData *instData, char *buffer, void *data );

// parseComboBoxData ===========================================================
/** Parse Combo Box data entry */
//=============================================================================
static Bool parseComboBoxData( char *token, WinInstanceData *instData,
															char *buffer, void *data )
{
	ComboBoxData *comboData = (ComboBoxData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );	// value
  scanBool( c, comboData->isEditable );

	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );	// value
  scanInt( c, comboData->maxChars );
	
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );	// value
  scanInt( c, comboData->maxDisplay );
	
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );	// value
  scanBool( c, comboData->asciiOnly );
	
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );	// value
  scanBool( c, comboData->lettersAndNumbersOnly );
	

  return TRUE;
}//parseComboBoxData

// parseSliderData ============================================================
/** Parse slider data entry */
//=============================================================================
static Bool parseSliderData( char *token, WinInstanceData *instData,
														 char *buffer, void *data )
{
	SliderData *sliderData = (SliderData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "MINVALUE"
	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, sliderData->minVal );

	// "MAXVALUE"
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, sliderData->maxVal );

	return TRUE;

}  // end parseSliderData

// parseRadioButtonData =======================================================
/** Parse radio button data entry */
//=============================================================================
static Bool parseRadioButtonData( char *token, WinInstanceData *instData,
																	char *buffer, void *data )
{
	RadioButtonData *radioData = (RadioButtonData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "GROUP"
	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, radioData->group );

	return TRUE;

}  // end parseRadioButtonData


// parseTooltipText ===========================================================
/** Parse the TOOLTIPTEXT field */
//=============================================================================
// The retail body is rowed in GameWindowManagerScript_parseTooltipText.cpp; call that one.
Bool parseTooltipText( char *token, WinInstanceData *instData, char *buffer, void *data );

// parseTooltipDelay =======================================================
/** Parse the tooltip delay */
//=============================================================================
static Bool parseTooltipDelay( char *token, WinInstanceData *instData,
																	char *buffer, void *data )
{
	//RadioButtonData *radioData = (RadioButtonData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "getvalue"
	c = strtok( buffer, seps );  // value
	scanInt( c, instData->m_tooltipDelay );

	return TRUE;

}  // end parseTooltipDelay


// parseText ==================================================================
/** Parse the TEXT field */
//=============================================================================
static Bool parseText( char *token, WinInstanceData *instData, 
											 char *buffer, void *data )
{
	char *ptr = buffer;
	char *c;
	char *stringSeps = "\n\r\t\""; 

	// scan to the first " mark
	while( *ptr != '"' )
		ptr++;
	ptr++;  // skip the "
	c = strtok( ptr, stringSeps );  // value
	if( strlen( c ) >= MAX_TEXT_LABEL )
	{
		
		DEBUG_LOG(( "Text label '%s' is too long, max is '%d'\n", c, MAX_TEXT_LABEL ));
		assert( 0 );
		return FALSE;

	}  // end if
	instData->m_textLabelString = c;
	

  return TRUE;

}  // end parseText

// parseTextColor =============================================================
/** Parse text color entries for enabled, disabled, and hilite with
	* drop shadow colors */
//=============================================================================
static Bool parseTextColor( char *token, WinInstanceData *instData,
														char *buffer, void *data )
{
	char *c;
	char *seps       = " :,\n\r\t";
	UnsignedInt r, g, b, a;
	Int i, states = 3;
	TextDrawData *textData;
	Bool first = TRUE;


	for( i = 0; i < states; i++ )
	{

		if( i == 0 )
			textData = &instData->m_enabledText;
		else if( i == 1 )
			textData = &instData->m_disabledText;
		else if( i == 2 )
			textData = &instData->m_hiliteText;
		else
		{

			DEBUG_LOG(( "Undefined state for text color\n" ));
			assert( 0 );
			return FALSE;

		}  // end else

		// color
		if( first == TRUE )
			c = strtok( buffer, seps );  // label
		else
			c = strtok( NULL, seps );  // label
		first = FALSE;
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		textData->color = GameMakeColor( r, g, b, a );

		// border color
		c = strtok( NULL, seps );  // label
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		textData->borderColor = GameMakeColor( r, g, b, a );

	}  // end if

	return TRUE;

}  // end parseTextColor

// parseStaticTextData ========================================================
/** Parse static text data entry */
//=============================================================================
static Bool parseStaticTextData( char *token, WinInstanceData *instData,
																 char *buffer, void *data )
{
	TextData *textData = (TextData *)data;
	char *c;
	char *seps       = " :,\n\r\t";

	// "CENTERED"
	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );  // value
	scanBool( c, textData->centered );

	// @todo: add these  to GUIEdit options and output
	// These are initialized here because any TextData constructor would never get called.
	// The behavior with these defaults is the same as it was before these members were added.
	textData->centeredVertically = TRUE;
	textData->leftMargin = 7;
	textData->topMargin = 7;

	return TRUE;

}  // end parseStaticTextDAta

// parseTextEntryData =========================================================
/** Parse text entry data entry */
//=============================================================================
static Bool parseTextEntryData( char *token, WinInstanceData *instData,
																char *buffer, void *data )
{
	EntryData *entryData = (EntryData *)data;
	char *c;
	char *seps       = " :,\n\r\t";

	// "MAXLEN"
	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );  // value
	scanShort( c, entryData->maxTextLen );

	// "SECRETTEXT"
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanBool( c, entryData->secretText );

	// "NUMERICALONLY"
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanBool( c, entryData->numericalOnly );

	// "ALPHANUMERICALONLY"
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanBool( c, entryData->alphaNumericalOnly );

	// "ASCIIONLY"
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanBool( c, entryData->aSCIIOnly );

	return TRUE;

}  // end parseStaticTextDAta

// parseTabControlData =========================================================
/** Parse tab control data entry */
//=============================================================================
static Bool parseTabControlData( char *token, WinInstanceData *instData,
																char *buffer, void *data )
{
	TabControlData *tabControlData = (TabControlData *)data;
	char *c;
	char *seps       = " :,\n\r\t";

	//TABORIENTATION
	c = strtok( buffer, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->tabOrientation );

	//TABEDGE
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->tabEdge );

	//TABWIDTH
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->tabWidth );

	//TABHEIGHT
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->tabHeight );

	//TABCOUNT
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->tabCount );

	//PANEBORDER
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, tabControlData->paneBorder );

	//PANEDISABLED
	Int entryCount = 0;
	c = strtok( NULL, seps );  // label
	c = strtok( NULL, seps );  // value
	scanInt( c, entryCount );

	for( Int paneIndex = 0; paneIndex < entryCount; paneIndex ++ )
	{
		c = strtok( NULL, seps );  // value
		scanBool( c, tabControlData->subPaneDisabled[paneIndex] );
	}

	return TRUE;
}

// parseDrawData ==============================================================
/** Parse set of draw data elements */
//=============================================================================
static Bool parseDrawData( char *token, WinInstanceData *instData,
													 char *buffer, void *data )
{
	Int i;
	UnsignedInt r, g, b, a;
	WinDrawData *drawData;
	Bool first = TRUE;
	char *c;
	char *seps       = " :,\n\r\t";

	for( i = 0; i < MAX_DRAW_DATA; i++ )
	{

		// get the right draw data
		if( strcmp( token, "ENABLEDDRAWDATA" ) == 0 )	
			drawData = &instData->m_enabledDrawData[ i ];
		else if( strcmp( token, "DISABLEDDRAWDATA" ) == 0 )	
			drawData = &instData->m_disabledDrawData[ i ];
		else if( strcmp( token, "HILITEDRAWDATA" ) == 0 )	
			drawData = &instData->m_hiliteDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDUPBUTTONDRAWDATA" ) == 0 )
			drawData = &enabledUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDUPBUTTONDRAWDATA" ) == 0 )
			drawData = &disabledUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITEUPBUTTONDRAWDATA" ) == 0 )
			drawData = &hiliteUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &enabledDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &disabledDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITEDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &hiliteDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDSLIDERDRAWDATA" ) == 0 )
			drawData = &enabledSliderDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDSLIDERDRAWDATA" ) == 0 )
			drawData = &disabledSliderDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITESLIDERDRAWDATA" ) == 0 )
			drawData = &hiliteSliderDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledSliderThumbDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledSliderThumbDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteSliderThumbDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledListBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledListBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteListBoxDrawData[ i ];
		else
		{

			DEBUG_LOG(( "ParseDrawData, undefined token '%s'\n", token ));
			assert( 0 );
			return FALSE;

		}  // end else

		// IMAGE: X
		if( first == TRUE )
			c = strtok( buffer, seps );  // label
		else
			c = strtok( NULL, seps );  // label
		first = FALSE;
	
		c = strtok( NULL, seps );  // value
		if( strcmp( c, "NoImage" ) )
			drawData->image = TheMappedImageCollection->findImageByName( AsciiString( c ) );
		else
			drawData->image = NULL;
		// COLOR: R G B A
		c = strtok( NULL, seps );  // label
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		drawData->color = GameMakeColor( r, g, b, a );

		// BORDERCOLOR: R G B A
		c = strtok( NULL, seps );  // label
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		drawData->borderColor = GameMakeColor( r, g, b, a );

	}  // end for i

	return TRUE;

}  // end parseDrawData

// getDataTemplate ============================================================
/** Given a window type style string return the address of a static
	* gadget data type used for the generic data pointers in the
	* GUI gadget contorls */
//=============================================================================
void *getDataTemplate(char *type, Int *sizeOut);

// parseData ==================================================================
//
// Parse the data for gadgets.  For sliders the data is in the format:
// <Minimum Value> <Maximum Value>
//
// For listboxes the data is formatted as:
// <Max number of entries> <Height of an entry> <AutoScroll> <AutoPurge> <ScrollBar> <MultiSelect> <ForceSelect>
//
// For Combo Boxes the data is formatted as:
// <is Editable> <Max Characters> <Max Entries before scroll appaears>
//
// For entry fields the data is as follows:
// <Max text length> <entry box width> <SecretText> <1 = NumericalOnly, 2 = AlphaNumericOnly>
//
// For text the data is as follows:
// <Centered> <Outlined> <StringManagerLabel>
//
// 1/2/2003: THIS FUNCTION IS NEVER REACHED; IT IS OBSOLETE -MDC
//
//=============================================================================
// Retail EntryData uses a flags word at +0x0c and is 0x28 bytes.
struct EntryData004850C0 { void *text,*sText,*constructText; unsigned int field0c; short maxTextLen; bool secretText; char tail[21]; };
struct LocalListboxData : ListboxData { char retailExtra[8]; };
static __declspec(noinline) Bool parseData( void **data, char *type, char *buffer )
{
  char *c;
  static EntryData004850C0 eData;
  static SliderData sData;
  static LocalListboxData lData;
  static TextData tData;
	static RadioButtonData rData;
	static ComboBoxData cData;

  if( !strcmp( type, "VERTSLIDER" ) || !strcmp( type, "HORZSLIDER" ) ) 
	{

    memset( &sData, 0, sizeof( SliderData ) );

	  c = NativeScriptCrt::strtok( buffer, " \t\n\r" );
    sData.minVal = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
    sData.maxVal = atoi(c);

    *data = &sData;

  } 
	else if( !strcmp( type, "SCROLLLISTBOX" ) ) 
	{

    memset( &lData, 0, sizeof( LocalListboxData ) );

	  c = NativeScriptCrt::strtok( buffer, " \t\n\r" );
    lData.listLength = atoi(c);

//	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
//    lData.entryHeight = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
    lData.autoScroll = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
    lData.autoPurge = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
    lData.scrollBar = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
    lData.multiSelect = atoi(c);

		c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
		lData.forceSelect = atoi(c);
		
    *data = &lData;

  } 
	else if( !strcmp( type, "ENTRYFIELD" ) ) 
	{

    memset( &eData, 0, sizeof( EntryData004850C0 ) );

	  c = NativeScriptCrt::strtok( buffer, " \t\n\r" );
    eData.maxTextLen = atoi(c);

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
//    if (c)
//      eData.entryWidth = atoi(c);
//    else
//      eData.entryWidth = -1;

		c = NativeScriptCrt::strtok( NULL, " \t\n\r" );
		if (c)
		{
			eData.secretText = atoi(c);

			if( eData.secretText != FALSE )
				eData.secretText = TRUE;
		}
		else
			eData.secretText = FALSE;

        eData.field0c = 0;
        c = NativeScriptCrt::strtok(NULL, " \t\n\r");
        if (c) {
            if (atoi(c) == 1) eData.field0c |= 0x20;
            if (atoi(c) == 2) eData.field0c |= 0x40;
            if (atoi(c) == 3) eData.field0c |= 0x10;
        }
    *data = &eData;

  } 
	else if( !strcmp( type, "STATICTEXT" ) ) 
	{

	  c = NativeScriptCrt::strtok( buffer, " \t\n\r" );
    tData.centered = atoi(c);
		
		if( tData.centered != FALSE )
			tData.centered = TRUE;

	  c = NativeScriptCrt::strtok( NULL, " \t\n\r" );

		/** @todo need to get a label from the translation manager, uncomment
		the following line and remove the WideChar assignment when
		we have it */
//		text = StringManagerFetch( c );
//		text = L"Need StrManager, Remove me!";
//		TheWindowManager->winStrcpy( tData.text, text );

		*data = &tData;

  }
	else if( !strcmp( type, "RADIOBUTTON" ) ) 
	{ 

		c = NativeScriptCrt::strtok( buffer, " \t\n\r" );
		rData.group = atoi(c);
/// @todo Colin: Why was this here???
//		if( tData.centered != FALSE )
//		{
//			tData.centered = TRUE;
//		}
		*data = &rData;
	}	
	else
    *data = NULL;

  return TRUE;

}  // end parseData

// setWindowText ==============================================================
/** Set the default text for a window or gadget control */
//=============================================================================
static void setWindowText( GameWindow *window, AsciiString textLabel )
{

	// sanity
	if (textLabel.isEmpty())
		return;

	UnicodeString theText, entryText;
	//Translate the text
	theText = TheGameText->fetch( (char *)textLabel.str());
	// set the text in the window based on what it is
	if( BitTest( window->winGetStyle(), GWS_PUSH_BUTTON ) )
		GadgetButtonSetText( window, theText );
	else if( BitTest( window->winGetStyle(), GWS_RADIO_BUTTON ) )
		GadgetRadioSetText( window, theText );
	else if( BitTest( window->winGetStyle(), GWS_CHECK_BOX ) )
		GadgetCheckBoxSetText( window, theText );
	else if( BitTest( window->winGetStyle(), GWS_STATIC_TEXT ) )
		GadgetStaticTextSetText( window, theText );
	else if( BitTest( window->winGetStyle(), GWS_ENTRY_FIELD ) )
	{
		entryText.translate(textLabel);
		GadgetTextEntrySetText( window, entryText );
	}
	else
		window->winSetText( theText );

}  // end setWindowText

// createGadget ===============================================================
/** Create a gadget based on the 'type' parm */
//=============================================================================
static GameWindow *createGadget( char *type, 
																 GameWindow *parent, 
																 Int status,
																 Int x, Int y, 
																 Int width, Int height, 
																 WinInstanceData *instData, 
																 void *data )
{
  GameWindow *window;

  instData->m_owner = parent;

  if( !strcmp( type, "PUSHBUTTON" ) ) 
	{

    instData->m_style |= GWS_PUSH_BUTTON;
    window = TheWindowManager->gogoGadgetPushButton( parent, status, x, y, 
																										 width, height, 
																										 instData, 
																										 instData->m_font, FALSE );

  } 
	else if( !strcmp( type, "RADIOBUTTON" ) ) 
	{
		RadioButtonData *rData = (RadioButtonData *)data;
		char filename[ MAX_WINDOW_NAME_LEN ];
		char *c;

		//
		// assign a screen identifier to the radio button based on the
		// filename the radio button was saved in
		//
		
		strcpy( filename, instData->m_decoratedNameString.str() );
		c = strchr( filename, ':' );
		if( c )
			*c = 0;  // terminate after filename (format is filename:gadgetname)
		assert( TheNameKeyGenerator );
		if( TheNameKeyGenerator )
			rData->screen = (Int)(TheNameKeyGenerator->nameToKey( AsciiString(filename) ));

    instData->m_style |= GWS_RADIO_BUTTON;
    window = TheWindowManager->gogoGadgetRadioButton( parent, status, x, y, 
																											width, height, 
																											instData, rData, 
																											instData->m_font, FALSE );

  } 
	else if( !strcmp( type, "CHECKBOX" ) ) 
	{

    instData->m_style |= GWS_CHECK_BOX;
    window = TheWindowManager->gogoGadgetCheckbox( parent, status, x, y, 
																									 width, height, 
																									 instData, 
																									 instData->m_font, FALSE );

  }
	else if( !strcmp( type, "TABCONTROL" ) ) 
	{
		TabControlData *tcData = (TabControlData *)data;
    instData->m_style |= GWS_TAB_CONTROL;
    window = TheWindowManager->gogoGadgetTabControl( parent, status, x, y, 
																										width, height, 
																										instData, tcData,
																										instData->m_font, FALSE );
	}
	else if( !strcmp( type, "VERTSLIDER" ) ) 
	{
    SliderData *sData = (SliderData *)data;

    instData->m_style |= GWS_VERT_SLIDER;
    window = TheWindowManager->gogoGadgetSlider( parent, status, x, y, 
																								 width, height,
																								 instData, sData, 
																								 instData->m_font, FALSE );

		//
		// we know we've read in the slider thumb data in the definition file
		// (it's guaranteed to be generated by the editor) so place that
		// draw data into the thumb of the slider
		//
		GameWindow *thumb = window->winGetChild();
		if( thumb )
		{
			WinInstanceData *instData = thumb->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledSliderThumbDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledSliderThumbDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteSliderThumbDrawData[ i ];

			}  // end for i

		}  //end if

  }
	else if( !strcmp( type, "HORZSLIDER" ) ) 
	{
    SliderData *sData = (SliderData *)data;

    instData->m_style |= GWS_HORZ_SLIDER;
    window = TheWindowManager->gogoGadgetSlider( parent, status, x, y, 
																								 width, height,
																								 instData, sData, 
																								 instData->m_font, FALSE );

		//
		// we know we've read in the slider thumb data in the definition file
		// (it's guaranteed to be generated by the editor) so place that
		// draw data into the thumb of the slider
		//
		GameWindow *thumb = window->winGetChild();
		if( thumb )
		{
			WinInstanceData *instData = thumb->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledSliderThumbDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledSliderThumbDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteSliderThumbDrawData[ i ];

			}  // end for i

		}  //end if

  }
	else if( !strcmp( type, "SCROLLLISTBOX" ) ) 
	{

    ListboxData *lData = (ListboxData *)data;

    instData->m_style |= GWS_SCROLL_LISTBOX;
    window = TheWindowManager->gogoGadgetListBox( parent, status, x, y, 
																									width, height,
																									instData, lData, 
																									instData->m_font, FALSE );

		//
		// we know that in the file we have read the draw data for the listbox
		// parts (up button, down button, and slider), now that we have those
		// parts actually created we must assign that data to them
		//
		GameWindow *upButton = GadgetListBoxGetUpButton( window );
		if( upButton )
		{
			WinInstanceData *instData = upButton->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledUpButtonDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledUpButtonDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteUpButtonDrawData[ i ];

			}  // end for i

		}  // end if

		GameWindow *downButton = GadgetListBoxGetDownButton( window );
		if( downButton )
		{
			WinInstanceData *instData = downButton->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledDownButtonDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledDownButtonDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteDownButtonDrawData[ i ];

			}  // end for i

		}  // end if

		GameWindow *slider = GadgetListBoxGetSlider( window );
		if( slider )
		{
			WinInstanceData *instData = slider->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledSliderDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledSliderDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteSliderDrawData[ i ];

			}  // end for i

			// do the slider thumb
			GameWindow *thumb = slider->winGetChild();
			if( thumb )
			{
				WinInstanceData *instData = thumb->winGetInstanceData();

				for( Int i = 0; i < MAX_DRAW_DATA; i++ )
				{

					instData->m_enabledDrawData[ i ] = enabledSliderThumbDrawData[ i ];
					instData->m_disabledDrawData[ i ] = disabledSliderThumbDrawData[ i ];
					instData->m_hiliteDrawData[ i ] = hiliteSliderThumbDrawData[ i ];

				}  // end for i

			}  //end if

		}  // end if

  }
	else if( !strcmp( type, "COMBOBOX" ) ) 
	{
		ComboBoxData *cData = (ComboBoxData *)data;
		cData->entryData = NEW EntryData;
		memset ( cData->entryData, 0, sizeof(EntryData));
		cData->listboxData = NEW ListboxData;
		memset ( cData->listboxData, 0, sizeof(ListboxData));
		
		//initialize combo box data
		//cData->isEditable = TRUE;
		//cData->maxChars = 16;
		//cData->maxDisplay = 5;
		cData->entryCount = 0;
		//initialize entry data
		cData->entryData->aSCIIOnly = cData->asciiOnly;
		cData->entryData->alphaNumericalOnly = cData->lettersAndNumbersOnly;
		cData->entryData->maxTextLen = cData->maxChars;
	
		//initialize listbox data
		cData->listboxData->listLength = 10;
		cData->listboxData->autoScroll = 0;
		cData->listboxData->scrollIfAtEnd = FALSE;
		cData->listboxData->autoPurge = 0;
		cData->listboxData->scrollBar = 1;
		cData->listboxData->multiSelect = 0;
		cData->listboxData->forceSelect = 1;
		cData->listboxData->columns = 1;
		cData->listboxData->columnWidth = NULL;
		cData->listboxData->columnWidthPercentage = NULL;

    instData->m_style |= GWS_COMBO_BOX;
    window = TheWindowManager->gogoGadgetComboBox( parent, status, x, y, 
																									width, height,
																									instData, cData, 
																									instData->m_font, FALSE );
		
		GameWindow *dropDownButton = GadgetComboBoxGetDropDownButton( window );
		if( dropDownButton )
		{
			WinInstanceData *instData = dropDownButton->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledDropDownButtonDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledDropDownButtonDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteDropDownButtonDrawData[ i ];

			}  // end for i
		} // end if

		GameWindow *editBox = GadgetComboBoxGetEditBox( window );
		if( editBox )
		{
			WinInstanceData *instData = editBox->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledEditBoxDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledEditBoxDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteEditBoxDrawData[ i ];

			}  // end for i
		} // end if


		GameWindow *listBox = GadgetComboBoxGetListBox( window );
		if( listBox )
		{
			WinInstanceData *instData = listBox->winGetInstanceData();

			for( Int i = 0; i < MAX_DRAW_DATA; i++ )
			{

				instData->m_enabledDrawData[ i ] = enabledListBoxDrawData[ i ];
				instData->m_disabledDrawData[ i ] = disabledListBoxDrawData[ i ];
				instData->m_hiliteDrawData[ i ] = hiliteListBoxDrawData[ i ];

			}  // end for i
			

			GameWindow *upButton = GadgetListBoxGetUpButton( listBox );
			if( upButton )
			{
				WinInstanceData *instData = upButton->winGetInstanceData();

				for( Int i = 0; i < MAX_DRAW_DATA; i++ )
				{

					instData->m_enabledDrawData[ i ] = enabledUpButtonDrawData[ i ];
					instData->m_disabledDrawData[ i ] = disabledUpButtonDrawData[ i ];
					instData->m_hiliteDrawData[ i ] = hiliteUpButtonDrawData[ i ];

				}  // end for i

			}  // end if

			GameWindow *downButton = GadgetListBoxGetDownButton( listBox );
			if( downButton )
			{
				WinInstanceData *instData = downButton->winGetInstanceData();

				for( Int i = 0; i < MAX_DRAW_DATA; i++ )
				{

					instData->m_enabledDrawData[ i ] = enabledDownButtonDrawData[ i ];
					instData->m_disabledDrawData[ i ] = disabledDownButtonDrawData[ i ];
					instData->m_hiliteDrawData[ i ] = hiliteDownButtonDrawData[ i ];

				}  // end for i

			}  // end if

			GameWindow *slider = GadgetListBoxGetSlider( listBox );
			if( slider )
			{
				WinInstanceData *instData = slider->winGetInstanceData();

				for( Int i = 0; i < MAX_DRAW_DATA; i++ )
				{

					instData->m_enabledDrawData[ i ] = enabledSliderDrawData[ i ];
					instData->m_disabledDrawData[ i ] = disabledSliderDrawData[ i ];
					instData->m_hiliteDrawData[ i ] = hiliteSliderDrawData[ i ];

				}  // end for i

				// do the slider thumb
				GameWindow *thumb = slider->winGetChild();
				if( thumb )
				{
					WinInstanceData *instData = thumb->winGetInstanceData();

					for( Int i = 0; i < MAX_DRAW_DATA; i++ )
					{

						instData->m_enabledDrawData[ i ] = enabledSliderThumbDrawData[ i ];
						instData->m_disabledDrawData[ i ] = disabledSliderThumbDrawData[ i ];
						instData->m_hiliteDrawData[ i ] = hiliteSliderThumbDrawData[ i ];

					}  // end for i

				}  //end if

			}  // end if
		}
  }
	else if( !strcmp( type, "ENTRYFIELD" ) ) 
	{
    EntryData *eData = (EntryData *)data;

    instData->m_style |= GWS_ENTRY_FIELD;
    window = TheWindowManager->gogoGadgetTextEntry( parent, status, x, y, 
																										width, height,
																										instData, eData, 
																										instData->m_font, FALSE );

  }
	else if( !strcmp( type, "STATICTEXT" ) ) 
	{
    TextData *tData = (TextData *)data;

    instData->m_style |= GWS_STATIC_TEXT;
    window = TheWindowManager->gogoGadgetStaticText( parent, status, x, y, 
																										 width, height,
																										 instData, tData, 
																										 instData->m_font, FALSE );


  }
	else if( !strcmp( type, "PROGRESSBAR" ) ) 
	{

    instData->m_style |= GWS_PROGRESS_BAR;
    window = TheWindowManager->gogoGadgetProgressBar( parent, status, x, y, 
																											width, height, 
																											instData, 
																											instData->m_font, FALSE );

  }

  return window;

}  // end createGadget

// createWindow ===============================================================
// Create a user window or a gadget depending on the 'type' parm
//=============================================================================
static GameWindow *createWindow(char *type, Int id, void *data, GadgetCreateView *record)
{
	GameWindow *window, *parent;

	// Check to see if this window has a parent
	parent = peekWindow();

	// If this is a regular window just create it
	if (!strcmp(type, "USER"))
	{
		window = ((ScriptFactoryManagerSlots *)TheWindowManager)->createFromView(record);
		if (window)
		{
			record->instance->m_style |= 0x00000200;
			window->winSetWindowId(id);
		}
	}
	else if (!strcmp(type, "TABPANE"))
	{
		window = ((ScriptFactoryManagerSlots *)TheWindowManager)->createFromView(record);
		if (window)
		{
			record->instance->m_style |= 0x00004000;
			window->winSetInstanceData(record->instance);
			window->winSetWindowId(id);
		}
	}
	else
	{
		// Else parse the type and create the gadget
		window = createGadget(type, data, record, 0);
		if (window)
		{
			// set id
			window->winSetWindowId(id);
		}
	}

	if (window)
	{
		// save strings for edit data if present
		GameWindowEditData *editData = window->winGetEditData();
		if (editData)
		{
			editData->systemCallbackString.setCopyInline(g_systemCallbackName);
			editData->inputCallbackString.setCopyInline(g_inputCallbackName);
			editData->tooltipCallbackString.setCopyInline(g_tooltipCallbackName);
			editData->drawCallbackString.setCopyInline(g_drawCallbackName);
		}
	}

	// set any text read from the textLabel
	if (window)
		setWindowText(window, record->instance->m_textLabelString);

	// If there is a parent window, send it the SCRIPT_CREATE message
	if (window && parent)
		((ScriptFactoryManagerSlots *)TheWindowManager)->send(parent, 0x16, id, 0);

	return window;
}  // end createWindow

// parseChildWindows ==========================================================
/** Parse window descriptions until an extra end is encountered indicating
	* the end of this block of child window descriptions. */
//=============================================================================
// Retail's parser destroys children through the existing manager's slot 0x8C.
// Keep this declaration-only view local: the donor manager header has slot 0x78.
class ScriptChildWindowManagerSlots
{
public:
#define SLOT(n) virtual void unusedSlot##n();
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34)
#undef SLOT
	virtual Int winDestroy(GameWindow *window);
};

static Bool parseChildWindows( GameWindow *window, 
															 File *inFile, 
															 char *buffer )
{
  GameWindow *lastWindow;
	AsciiString asciibuf;

	//The gadget with children needs to delete its default created children in favor
	//of the ones from the script file.  So kill them before reading.
	if( BitTest( window->winGetStyle(), GWS_TAB_CONTROL ) )
	{
		GameWindow *nextWindow = NULL;
		for( GameWindow *myChild = window->winGetChild(); myChild; myChild = nextWindow )
		{
			nextWindow = myChild->winGetNext();
			((ScriptChildWindowManagerSlots *)TheWindowManager)->winDestroy( myChild );
		}
	}
		
		// Push the current window onto the stack so we know it's the parent
  pushWindow( window );

	while( TRUE ) 
	{

		if (((GoalScriptFileSlots *)inFile)->scanString(asciibuf) == FALSE) {
			break;
		}

		if (asciibuf.compare("ENDALLCHILDREN") == 0) {
			break;
		}

		if (asciibuf.compare("END") == 0) {
      break;
		}

		if (asciibuf.compare("ENABLEDCOLOR") == 0)
		{

			if( parseDefaultColor( &defEnabledColor, inFile, buffer ) == FALSE ) 
			{
				return FALSE;
			}

		} 
		else if (asciibuf.compare("DISABLEDCOLOR") == 0)
		{

			if( parseDefaultColor( &defDisabledColor, inFile, buffer ) == FALSE ) 
			{
				return FALSE;
			}

		} 
		else if (asciibuf.compare("HILITECOLOR") == 0)
		{

			if( parseDefaultColor( &defHiliteColor, inFile, buffer ) == FALSE ) 
			{
				return FALSE;
			}

		} 
		else if (asciibuf.compare("SELECTEDCOLOR") == 0)
		{

			if( parseDefaultColor( &defSelectedColor, inFile, buffer ) == FALSE ) 
			{
				return FALSE;
			}

		}
		else if (asciibuf.compare("TEXTCOLOR") == 0)
		{

			if( parseDefaultColor( &defTextColor, inFile, buffer ) == FALSE ) 
			{
				return FALSE;
			}

		}
		else if (asciibuf.compare("WINDOW") == 0)
		{

      // Parse window descriptions until the last END is read
			if( parseWindow( inFile, buffer ) == NULL ) 
			{
				return FALSE;
			}

		}

	}  // end while( TRUE )

  // Pop the current window off the stack
  lastWindow = popWindow();

  if( lastWindow != window ) 
	{

    DEBUG_LOG(( "parseChildWindows: unmatched window on stack.  Corrupt stack or bad source\n" ));
    return FALSE;

  }

	if( BitTest( window->winGetStyle(), GWS_TAB_CONTROL ) )
		GadgetTabControlFixupSubPaneList( window );//all children created, so re-fill SubPane array with children

  return TRUE;

}  // end parseChildWindows

// lookup table for parsing functions
Bool parseWinClass(char *, WinInstanceData *, char *, void *);

static GameWindowParse gameWindowFieldList[] = 
{
	{ "NAME", parseName },
	{ "STATUS", parseStatus },
	{ "STYLE", parseStyle },
	{ "SYSTEMCALLBACK", parseSystemCallback },
	{ "WINCLASS", parseWinClass },
	{ "INPUTCALLBACK", parseInputCallback },
	{ "TOOLTIPCALLBACK", parseTooltipCallback },
	{ "DRAWCALLBACK", parseDrawCallback },
	{ "FONT", parseFont },
	{ "HEADERTEMPLATE", parseHeaderTemplate },
	{ "LISTBOXDATA", parseListboxData },
	{ "COMBOBOXDATA", parseComboBoxData },
	{ "SLIDERDATA", parseSliderData },
	{ "RADIOBUTTONDATA", parseRadioButtonData },
	{	"TOOLTIPTEXT", parseTooltipText },
  { "TOOLTIPDELAY", parseTooltipDelay },
	{ "TEXT", parseText },
	{ "TEXTCOLOR", parseTextColor },
	{ "STATICTEXTDATA", parseStaticTextData },
	{ "TEXTENTRYDATA", parseTextEntryData },
	{ "TABCONTROLDATA", parseTabControlData },

	{ "ENABLEDDRAWDATA", parseDrawData },
	{ "DISABLEDDRAWDATA", parseDrawData },
	{ "HILITEDRAWDATA", parseDrawData },
	{ "LISTBOXENABLEDUPBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXENABLEDDOWNBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXENABLEDSLIDERDRAWDATA", parseDrawData },
	{ "LISTBOXDISABLEDUPBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXDISABLEDDOWNBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXDISABLEDSLIDERDRAWDATA", parseDrawData },
	{ "LISTBOXHILITEUPBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXHILITEDOWNBUTTONDRAWDATA", parseDrawData },
	{ "LISTBOXHILITESLIDERDRAWDATA", parseDrawData },
	{ "SLIDERTHUMBENABLEDDRAWDATA", parseDrawData },
	{ "SLIDERTHUMBDISABLEDDRAWDATA", parseDrawData },
	{ "SLIDERTHUMBHILITEDRAWDATA", parseDrawData },

	{ "COMBOBOXDROPDOWNBUTTONENABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXDROPDOWNBUTTONDISABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXDROPDOWNBUTTONHILITEDRAWDATA", parseDrawData },
	{ "COMBOBOXEDITBOXENABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXEDITBOXDISABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXEDITBOXHILITEDRAWDATA", parseDrawData },
	{ "COMBOBOXLISTBOXENABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXLISTBOXDISABLEDDRAWDATA", parseDrawData },
	{ "COMBOBOXLISTBOXHILITEDRAWDATA", parseDrawData },

	{ "IMAGEOFFSET", parseImageOffset },
	{ "TOOLTIP", parseTooltip },

	{ NULL, NULL }
};

// parseWindow ================================================================
/** Parse a WINDOW entry in the script. */
//=============================================================================
static GameWindow *parseWindow( File *inFile, char *buffer )
{
	GameWindowParse *parse;
	GameWindow *window = NULL;
	WinInstanceData instData;
	g_windowScriptCreateRecord.parent = peekWindow();
	char type[64];
	char token[ 256 ];
	char *c;
	void *data = NULL;
	ICoord2D parentSize;
	AsciiString asciibuf;

	//
	// reset our 'static globals' that house the current parsed window callback
	// definitions to empty
	//
	g_windowScriptCreateRecord.winClass = NULL;
	g_windowScriptCreateRecord.system = NULL;
	g_windowScriptCreateRecord.input = NULL;
	g_windowScriptCreateRecord.tooltip = NULL;
	g_windowScriptCreateRecord.draw = NULL;
	g_windowScriptCreateRecord.unknown2c = NULL;
	g_systemCallbackName.clear();
	g_inputCallbackName.clear();
	g_tooltipCallbackName.clear();
	g_drawCallbackName.clear();

	// get the size of the parent, or if no parent present the screen
	if( g_windowScriptCreateRecord.parent )
	{
		g_windowScriptCreateRecord.parent->winGetSize( &parentSize.x, &parentSize.y );
	}  // end if
	else
	{
		parentSize.x = ((ScriptDisplaySlots *)TheDisplay)->getWidth();
		parentSize.y = ((ScriptDisplaySlots *)TheDisplay)->getHeight();
	}  // end else

	// Initialize the instance data to the defaults
	/// @todo need to support enabled/disabled/hilite text colors here
	instData.init();
	instData.m_enabledText.color = defTextColor;
	instData.m_enabledText.borderColor = defTextColor;
	instData.m_disabledText.color = defTextColor;
	instData.m_disabledText.borderColor = defTextColor;
	instData.m_hiliteText.color = defTextColor;
	instData.m_hiliteText.borderColor = defTextColor;

	/// @todo need real font support here
	instData.m_font = defFont;

	//
	// read the first few lines that are required to be first in a 
	// window definition file including position, size, type, and id
	//

	// window type
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );	
	c = NativeScriptCrt::strtok( buffer, seps );
	assert( strcmp( c, "WINDOWTYPE" ) == 0 );
	c = NativeScriptCrt::strtok( NULL, seps );  // get data to right of = sign
	strcpy( type, c );

	//
	// based on the window type get a pointer for any specific data
	// for the gadget controls needed
	//
	data = getDataTemplate( type, NULL );
	
	// position
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );	
	c = NativeScriptCrt::strtok( buffer, seps );
	assert( strcmp( c, "SCREENRECT" ) == 0 );
	if( parseScreenRect( c, buffer, &g_windowScriptCreateRecord.x, &g_windowScriptCreateRecord.y, &g_windowScriptCreateRecord.width, &g_windowScriptCreateRecord.height ) == FALSE )
		goto cleanupAndExit;

	// parse all the field definitions
	while( TRUE ) 
	{

		// get token
		((GoalScriptFileSlots *)inFile)->scanString(asciibuf);

		// parse field
		for( parse = gameWindowFieldList; parse->parse; parse++ ) 
		{

			if (asciibuf.compare(parse->name) == 0)
			{
				
				strcpy( token, asciibuf.str() );

				// eat '='
				((GoalScriptFileSlots *)inFile)->scanString(asciibuf);

				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

				if (parse->parse( token, &instData, buffer, data ) == FALSE ) 
				{
					DEBUG_LOG(( "parseGameObject: Error parsing %s\n", parse->name ));
					goto cleanupAndExit;
				}

				break;
			}

		}  // end for

		if( parse->parse == NULL ) 
		{

			// If it's the END keyword
			if (asciibuf.compare("DATA") == 0)
			{

				// eat '='
				((GoalScriptFileSlots *)inFile)->scanString(asciibuf);

				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

				if( parseData( &data, type, buffer ) == FALSE ) 
				{
					DEBUG_LOG(( "parseGameWindow: Error parsing %s\n", parse->name ));
					goto cleanupAndExit;
				}

			} 
			else if (asciibuf.compare("END") == 0)
			{
				// Check to see if we have a header template, if so, set the font equal to that.
				if(TheHeaderTemplateManager->getFontFromTemplate(instData.m_headerTemplateName))
					instData.m_font = TheHeaderTemplateManager->getFontFromTemplate(instData.m_headerTemplateName);

				// Create a window using the current description
				if( window == NULL )
					{ g_windowScriptCreateRecord.instance = &instData; g_windowScriptCreateRecord.status = instData.getStatus(); window = createWindow(type, instData.m_id, data, (GadgetCreateView *)&g_windowScriptCreateRecord); }

				
				goto cleanupAndExit;

			} 
			else if (asciibuf.compare("CHILD") == 0)
			{

				// Create a window using the current description
				{ g_windowScriptCreateRecord.instance = &instData; g_windowScriptCreateRecord.status = instData.getStatus(); window = createWindow(type, instData.m_id, data, (GadgetCreateView *)&g_windowScriptCreateRecord); }

				if (window == NULL)
					goto cleanupAndExit;

				// Parses the CHILD's window info.
				if( parseChildWindows( window, inFile, buffer ) == FALSE )
				{

					((ScriptChildWindowManagerSlots *)TheWindowManager)->winDestroy( window );
					window = NULL;
					goto cleanupAndExit;

				}  // end if

			} 
			else 
			{

				// Else it is unrecognized so eat associated data
				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

			}

		}  // end if

	}  // end while( TRUE )

cleanupAndExit:

	//
	// this should be true since we should never set the text in
	// display strings in a instance data that is not inside a
	// window ... it's for sanity checking
	//
	// I am commenting this out to get tooltips working, If for
	// some reason we start having displayString problems... CLH
//	assert( instData.m_text == NULL && instData.m_tooltip == NULL );

	return window;

}  // end parseWindow

//=================================================================================================
//=================================================================================================
//=================================================================================================

//-------------------------------------------------------------------------------------------------
/** Parse init for layout file */
//-------------------------------------------------------------------------------------------------
// Defined with the native layout table in GameWindowManagerScript_parseLayoutBlock.cpp.
Bool parseInit(char *, char *, UnsignedInt, WindowLayoutInfo *);

//-------------------------------------------------------------------------------------------------
/** Parse update for layout file */
//-------------------------------------------------------------------------------------------------
// Defined with the native layout table in GameWindowManagerScript_parseLayoutBlock.cpp.
Bool parseUpdate(char *, char *, UnsignedInt, WindowLayoutInfo *);

//-------------------------------------------------------------------------------------------------
/** Parse shutdown for layout file */
//-------------------------------------------------------------------------------------------------
// Defined with the native layout table in GameWindowManagerScript_parseLayoutBlock.cpp.
Bool parseShutdown(char *, char *, UnsignedInt, WindowLayoutInfo *);

static LayoutScriptParse layoutScriptTable[] =
{
	{ "LAYOUTINIT",										parseInit },
	{ "LAYOUTUPDATE",									parseUpdate },
	{ "LAYOUTSHUTDOWN",								parseShutdown },

	{ NULL,															NULL },

};

//-------------------------------------------------------------------------------------------------
/** Parse the layout block which MUST be present in every window file */
//-------------------------------------------------------------------------------------------------
// parseLayoutBlock: defined in GameWindowManagerScript_parseLayoutBlock.cpp (its row's unit).
Bool parseLayoutBlock( File *inFile, char *buffer, UnsignedInt version, WindowLayoutInfo *info );
  // end parseLayoutBlock

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// GameWindowManager::winCreateLayout =========================================
/** Load window(s) from a .wnd definition file and wrap within a
	* new window layout */
//=============================================================================
// Native layout factory is defined with its44B info lifetimes in
// Rva0031763ACtorDtorAssign.cpp.


/** Free up the memory used by static strings.  Normally this memory
is freed by the string destructor but we do it here to make the
memory leak detection code happy.*/
#pragma optimize("s", on)
void GameWindowManager::freeStaticStrings(void)
{
	g_systemCallbackName.clear();
	g_inputCallbackName.clear();
	g_tooltipCallbackName.clear();
	g_drawCallbackName.clear();
}
#pragma optimize("", on)

// ??0WindowLayoutInfo@@ present-unmatched
WindowLayoutInfo::WindowLayoutInfo() :
	version(0),
	init(NULL),
	update(NULL),
	shutdown(NULL),
	initNameString(AsciiString::TheEmptyString),
	updateNameString(AsciiString::TheEmptyString),
	shutdownNameString(AsciiString::TheEmptyString)
{
		windows.clear();
}

// GameWindowManager::winCreateFromScript =====================================
/** Parse through a window .wnd file and create all the windows
	* within it.
	*
	* NOTE: The FIRST window created from the script is returned, this
	* way if you want to know ALL of the windows created from this 
	* layout file you must iterate over info->windows, since the windows will
	* not be at the head of the window list if there is a modal window active.
	*/
//=============================================================================
// This caller imports strchr/sprintf directly; existing parsers retain their thunk declarations.
namespace NativeWindowCrt {
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
}

// The false pooled-erase GameWindow specialization is withdrawn.
// STLport 4.5.3 node creation, kept out of line as in retail.
namespace _STL {
template<> __declspec(noinline)
_List_node<GameWindow*> *list<GameWindow*>::_M_create_node(GameWindow *const &value)
{
    _List_node<GameWindow*> *node = this->_M_node.allocate(1);
    _Construct(&node->_M_data, value);
    return node;
}
}
// Keep the already-rowed STLport assignment and range erase emitted after
// the native caller delegates layout assignment to its 44-byte ABI owner.
namespace _STL {


}
// ABI view of the existing 44-byte constructor/dtor/assign owner.
// Native callbacks prove +4/+8/+C/+10 functions and +14/+18/+1C/+20 names;
// WindowLayoutInfo::load proves the filename at +24. The list payload holds
// window pointers here; the provider's integer-list view has the same four-byte ABI.
// The leading word's purpose and original class spelling remain unestablished.
class Rva0031763A {public:
 Rva0031763A();~Rva0031763A();Rva0031763A &operator=(const Rva0031763A&);
 unsigned version;void *init,*update,*shutdown,*field_10;
 AsciiString initNameString,updateNameString,shutdownNameString,field_20,field_24;
 _STL::list<GameWindow*> windows;
};

// BFME1 9e3be919b10a clean parser lead; target 3177EC..317B35, RET12.
// Keep this in the static stack/default/parser owner. Third argument is the parent;
// inherited status uses bit 0x08000000, and native defaults are APT:None.
GameWindow *GameWindowManager::winCreateFromScript(AsciiString filenameString,Rva0031763A *info,GameWindow *parent) {
 const char *filename=filenameString.str();static char buffer[2048];GameWindow *firstWindow=0,*window;
 char filepath[260]="Window\\";File *inFile;Rva0031763A scriptInfo;AsciiString asciibuf;
 bool inherit=parent ? ((parent->winGetStatus() & 0x8000000)!=0):false;
 memset(windowStack,0,sizeof(windowStack));stackPtr=windowStack;
 defEnabledColor=0;defDisabledColor=0;defBackgroundColor=0;defHiliteColor=0;defSelectedColor=0;defTextColor=0;defFont=0;
 if(parent)*stackPtr++=parent;
 if(NativeWindowCrt::strchr(filename,'\\')==0)NativeWindowCrt::sprintf(filepath,"Window\\%s",filename);else strcpy(filepath,filename);
 inFile=TheFileSystem->openFile(filepath,1,0);if(inFile==0)return 0;
 int version;((GoalScriptFileSlots*)inFile)->read(0,strlen("FILE_VERSION = "));((GoalScriptFileSlots*)inFile)->scanInt(version);((GoalScriptFileSlots*)inFile)->nextLine(0,0);
 if(version>=2) {if(!parseLayoutBlock(inFile,buffer,version,(WindowLayoutInfo*)&scriptInfo))return 0;}
 else {scriptInfo.initNameString="APT:None";scriptInfo.updateNameString="APT:None";scriptInfo.shutdownNameString="APT:None";scriptInfo.field_20="APT:None";}
 while(true) {
 if(!((GoalScriptFileSlots*)inFile)->scanString(asciibuf))break;
 if(asciibuf.compare("END")==0)continue;
 if(asciibuf.compare("ENABLEDCOLOR")==0){if(!parseDefaultColor(&defEnabledColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("DISABLEDCOLOR")==0){if(!parseDefaultColor(&defDisabledColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("HILITECOLOR")==0){if(!parseDefaultColor(&defHiliteColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("SELECTEDCOLOR")==0){if(!parseDefaultColor(&defSelectedColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("TEXTCOLOR")==0){if(!parseDefaultColor(&defTextColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("BACKGROUNDCOLOR")==0){if(!parseDefaultColor(&defBackgroundColor,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("FONT")==0){if(!parseDefaultFont(defFont,inFile,buffer)){((GoalScriptFileSlots*)inFile)->close();inFile=0;return 0;}}
 else if(asciibuf.compare("WINDOW")==0){window=parseWindow(inFile,buffer);if(inherit)window->winSetStatus(0x8000000);if(firstWindow==0)firstWindow=window;scriptInfo.windows.push_back(window);}
 }
 ((GoalScriptFileSlots*)inFile)->close();inFile=0;if(info)*info=scriptInfo;if(parent)popWindow();return firstWindow;
}


// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
