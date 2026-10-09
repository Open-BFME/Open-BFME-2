// cl: /O1 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /arch:SSE /G7
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "unicode_string.h"
#define UNICODESTRING_H
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
// IMECandidateMainDraw: native FunctionLexicon record VA00DBC998 binds
// the literal at00C028B8 directly to00427858; complete222B ends00427936.
// Based on Open-BFME-1 874e38488c7dcf8cf3343452e8e5371bb3a0e64c
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/IMECandidateMainDraw_Thunk.cpp
// and the EA Generals Zero Hour callback source. Existing BFME2 GUI headers
// supply the measured draw colors and virtual rect slots. The filled rectangle
// uses origin-plus-one temporaries before the end coordinates: preserving
// these values independently of start reproduces native LEA operand order.
void IMECandidateMainDraw(GameWindow *window, WinInstanceData *instData)
{
	ICoord2D origin, size, start, end;
	Color backColor;
	Color backBorder;
	Real borderWidth = 1.0f;

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == 0)
	{
		backColor = window->winGetDisabledColor(0);
		backBorder = window->winGetDisabledBorderColor(0);
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = window->winGetHiliteColor(0);
		backBorder = window->winGetHiliteBorderColor(0);
	}
	else
	{
		backColor = window->winGetEnabledColor(0);
		backBorder = window->winGetEnabledBorderColor(0);
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, borderWidth, start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		Int sx = origin.x + 1, sy = origin.y + 1;
		start.x = sx;
		start.y = sy;
		end.x = sx + size.x - 2;
		end.y = sy + size.y - 2;
		TheWindowManager->winFillRect(backColor, 0.0f, start.x, start.y, end.x, end.y);
	}
}

class DisplayString;
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
// Call-only factory prefix: native create/free slots38/3C, as independently
// used by the already recovered Rva004E5821 consumer. No object is constructed.
class ImeDisplayFactoryPrefix {
public:
 virtual void slot00() = 0;
 virtual void slot04() = 0;
 virtual void slot08() = 0;
 virtual void slot0C() = 0;
 virtual void slot10() = 0;
 virtual void slot14() = 0;
 virtual void slot18() = 0;
 virtual void slot1C() = 0;
 virtual void slot20() = 0;
 virtual void slot24() = 0;
 virtual void slot28() = 0;
 virtual void slot2C() = 0;
 virtual void slot30() = 0;
 virtual void slot34() = 0;
 virtual DisplayString *newDisplayString() = 0;
 virtual void freeDisplayString(DisplayString *) = 0;
};
// Native WindowSystem uses the same nullable four-byte file-static at
// VAE031F8 for create and destroy; the initial native storage is zero.
static DisplayString *Dstring = 0;

// Native FunctionLexicon DBCAB0 binds nameC02690 to427810. All72 bytes
// end427858 with cdecl return; only msg (second callback word) is used.
WindowMsgHandledType IMECandidateWindowSystem(GameWindow *window,UnsignedInt msg,WindowMsgData data1,WindowMsgData data2)
{
 switch(msg) {
  case GWM_CREATE:
   if(Dstring==0) Dstring=reinterpret_cast<ImeDisplayFactoryPrefix *>(TheDisplayStringManager)->newDisplayString();
   break;
  case GWM_DESTROY:
   if(Dstring!=0) {
    reinterpret_cast<ImeDisplayFactoryPrefix *>(TheDisplayStringManager)->freeDisplayString(Dstring);
    Dstring=0;
   }
   break;
  default: return MSG_IGNORED;
 }
 return MSG_HANDLED;
}

// Native TextArea739B independently calls these text and input prefixes.
// Prefixes describe only dispatched slots; no object or vtable is emitted.
// Neither prefix is constructed; window and string value types use the
// existing shared GUI headers.
class ImeCandidateDisplayPrefix {
public:
 virtual void unused00() = 0;
 virtual void setText(UnicodeString);
 virtual void unused08() = 0;
 virtual void unused0C() = 0;
 virtual void unused10() = 0;
 virtual void unused14() = 0;
 virtual void setFont(GameFont *);
 virtual void unused1C() = 0;
 virtual void unused20() = 0;
 virtual void unused24() = 0;
 virtual void setTextColor(Color,Color);
 virtual void unused2C() = 0;
 virtual void unused30() = 0;
 virtual void unused34() = 0;
 virtual void draw(Int,Int,Int,Int);
 virtual void unused3C() = 0;
 virtual Int getWidth(Int=-1);
 virtual void unused44() = 0;
 virtual void unused48() = 0;
 virtual void unused4C() = 0;
 virtual void setClipRegion(IRegion2D *);
};
inline ImeCandidateDisplayPrefix *candidateDisplay(){return reinterpret_cast<ImeCandidateDisplayPrefix *>(Dstring);}
class ImeCandidateInputPrefix {
public:
 virtual void unused00() = 0;
 virtual void unused04() = 0;
 virtual void unused08() = 0;
 virtual void unused0C() = 0;
 virtual void unused10() = 0;
 virtual void unused14() = 0;
 virtual void unused18() = 0;
 virtual void unused1C() = 0;
 virtual void unused20() = 0;
 virtual void unused24() = 0;
 virtual void unused28() = 0;
 virtual void unused2C() = 0;
 virtual void unused30() = 0;
 virtual void unused34() = 0;
 virtual void unused38() = 0;
 virtual void unused3C() = 0;
 virtual void unused40() = 0;
 virtual void unused44() = 0;
 virtual void unused48() = 0;
 virtual void unused4C() = 0;
 virtual void unused50() = 0;
 virtual void unused54() = 0;
 virtual void unused58() = 0;
 virtual void unused5C() = 0;
 virtual Int getIndexBase() = 0;
 virtual Int getCandidateCount() = 0;
 virtual UnicodeString *getCandidate(Int) = 0;
 virtual Int getSelectedCandidateIndex() = 0;
 virtual Int getCandidatePageSize() = 0;
 virtual Int getCandidatePageStart() = 0;
};
extern Int IMECandidateWindowLineSpacing;
// Native FunctionLexicon DBC9A4 pairs nameC0289C with427936. Complete
// native427936..427C19 is739B; native frame FF6CAD56 and pointer-format
// call6CB5D0 replace the BFME1 donor color and by-value format overload.
// Both lifecycle and drawing use this file's Dstring atVAE031F8.
void IMECandidateTextAreaDraw( GameWindow *window, WinInstanceData *instData )
{
	// set up for rendering
	ICoord2D origin, size, start, end;
	Color		textColor,
					textBorder,
					textSelectColor,
					textSelectBorder;
	IRegion2D textRegion;
	Color black = GameMakeColor( 0, 0, 0, 255 );

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get a nice region from the positions
	textRegion.lo.x = origin.x;
	textRegion.lo.y = origin.y;
	textRegion.hi.x = origin.x + size.x;
	textRegion.hi.y = origin.y + size.y;

	// get the right colors for drawing
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == 0 )
	{

		textSelectColor		= window->winGetDisabledTextColor();
		textSelectBorder	= window->winGetDisabledTextBorderColor();
		textColor		= window->winGetDisabledTextColor();
		textBorder	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();
		textSelectColor		= window->winGetHiliteTextColor();
		textSelectBorder	= window->winGetHiliteTextBorderColor();

	}  // end else if, hilited
	else
	{

		textSelectColor		= window->winGetHiliteTextColor();
		textSelectBorder	= window->winGetHiliteTextBorderColor();
		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();

	}  // end else, just enabled

	{
		Real borderWidth = 1.0f;

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( GameMakeColor( 0x6C, 0xAD, 0x56, 0xFF ), borderWidth,
									   start.x, start.y, end.x, end.y );
		TheWindowManager->winFillRect( black, 0,
									   start.x + 1, start.y + 1, end.x - 1, end.y - 1 );
	}

	if ( Dstring == 0 )
	{
		return;
	}

	ImeCandidateInputPrefix *ime = (ImeCandidateInputPrefix*)window->winGetUserData();

	if ( ime == 0 )
	{
		return;
	}

	GameFont *font = window->winGetFont();
	Int height;

	// set the font
	candidateDisplay()->setFont( font );

	// cacl line height
	height = font->height + IMECandidateWindowLineSpacing;

	// set the clip region
	candidateDisplay()->setClipRegion( &textRegion );

	Int first = ime->getCandidatePageStart();
	Int total = ime->getCandidateCount();
	Int pageSize = ime->getCandidatePageSize();
	Int selected = ime->getSelectedCandidateIndex();

	Int count = pageSize;

	if ( count + first > total )
	{
		count = total - first;
	}

	selected = selected - first;
	UnicodeString number;

	// calulate the widest number text
	Int width;
	candidateDisplay()->setText( UnicodeString( L"00:" ) );
	width = candidateDisplay()->getWidth();

	// calc y start pos
	Int y = origin.y;
	Int leftEdge = origin.x + 10 + width;

	for ( Int i = 0; i < count; i++, y += height )
	{
		UnicodeString *candidate = ime->getCandidate( first + i );
		Int tcolor;

		if ( i == selected )
		{
			tcolor = textSelectColor;
		}
		else
		{
			tcolor = textColor;
		}

		// draw number tab first
		number.format( L"%d:", i + ime->getIndexBase() );
		candidateDisplay()->setText( number );
		width = candidateDisplay()->getWidth();
		candidateDisplay()->setTextColor( tcolor, black );
		candidateDisplay()->draw( leftEdge - width, y, 1, 1 );

		// draw candidate
		candidateDisplay()->setText( *candidate );
		candidateDisplay()->draw( leftEdge, y, 1, 1 );
	}
}
