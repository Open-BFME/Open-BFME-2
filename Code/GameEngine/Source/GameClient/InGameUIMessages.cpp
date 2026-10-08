// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// InGameUI's on-screen message family: the three ZH formatters (also recovered
// in BFME 1 donor 847fc2a5406da49baed14adf987ff6830204b9d0, InGameUI.cpp), the
// shared addMessageText they feed, three BFME 2 formatters that only post
// while TheGameLogic's multiplayer predicate 0x0023C6FD holds, and the military
// subtitle setup and teardown.
//
// Target facts: the six formatters are InGameUI vftable 0x007FD410 slots 14-19
// (also 0x007C7A88); each is a cdecl variadic member with an __EH_prolog frame,
// an 8192-character wide buffer, vswprintf (0x00BBA5AC) capped at 8191,
// ErrorCode 0xDEAD0002 thrown on failure and addMessageText 0x0029BA58 called
// on the result. Slots 17-19 match ZH's messageColor, message(AsciiString) and
// message(UnicodeString) (MSVC's reversed overload order); slots 14-16 are the
// same three bodies behind the gate, so their names stay address names.
// addMessageText's message ring (6 x 0x10 at +0x5D0), colors (+0x814/+0x818)
// and font triple (+0x82C/+0x830/+0x834) are retail-measured; the ring entry's
// copy assignment is the out-of-line 0x0029A778. Semantics come from ZH.
//
// Slots 22-24 are ZH's militarySubtitle(UnicodeString, Int) 0x0029F530,
// militarySubtitle(const AsciiString&, Int) 0x0029C2F6 and
// removeMilitarySubtitle 0x002A0C87. The 0x48-byte MilitarySubtitleData at
// +0x7F0 and the caption settings at +0x83C..+0x870 are retail-measured; BFME 2
// adds per-line offsets, a word display string and timeGetTime pacing to ZH's
// layout, so the field names past ZH's are descriptive. Retail folded the
// struct's implicit destructor into ~UnicodeString at 0x005B804E.
//
// 0x0029C404 is the subtitle block of ZH's InGameUI::update split into its own
// non-virtual member (sole caller 0x002A169B), so its name is descriptive. It
// paces by timeGetTime deltas capped at 100 ms, holds still while TheShell is
// active (+0x5C), types whole words through the word display string, and plays
// the typing sound held at TheAudio's misc audio +0xBC instead of ZH's
// "MilitarySubtitlesTyping" event; the field name there is descriptive.
//
// Vtable slot 86 (0x0029AD12) draws the subtitle: the block ZH keeps inside
// InGameUI::postDraw, split out like the update step, so its name is
// descriptive. The caption position (+0x84C) scales by TheDisplay's size and
// floors through msvcr71; the typing word trails the last line by up to 30
// pixels and fades in with the time left until the next character. The word
// position is a coordinate pair: retail keeps its unused x slot in the frame.
//
// Vtable slot 1 (0x0029E2DE) is ZH's InGameUI::init. BFME 2 loads the
// definition through IniLoad 0x003397D8 ("InGameUI" plus the block parser
// INI::parseInGameUIDefinition 0x0029A627), applies nine GlobalLanguage font
// overrides (12-byte name/size/bold triples from +0x38; their InGameUI targets
// are retail-measured), and after ZH's tactical view, createControlBar
// 0x0029C23E, createReplayControl 0x0029C269 and `new ControlBar` (0x2B4 B,
// 0x0031E94C) adds a vslot-119 call, a 0x44-byte BannerUI (0x00217211, its
// init and SubsystemInterface::loadIniFilesFromLegend), two singleton getters
// and a zeroed +0x980. createControlBar passes HideControlBar an explicit true.
//
// Vtable slot 108 (0x0029F7EA) is ZH's recreateControlBar as written: window
// lookup through TheWindowManager slot 60, m_idleWorkerWin at +0x978, and both
// deletions run the virtual destructor in place before the global delete.

#include "unicode_string.h"
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../Common/GameLogicObjectLookupView.h"

// The gated label formatter expands isEmpty in place, as retail does here.
template <> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

typedef unsigned short WideChar;
typedef int Color;

#define _DLL
#include <stdarg.h>
__declspec(dllimport) int __cdecl vswprintf(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args);

enum ErrorCode
{
	ERROR_BASE = 0xDEAD0001,
	ERROR_OUT_OF_MEMORY = (ERROR_BASE + 0x0001)
};

struct RGBColor
{
	float red, green, blue;
	int getAsInt() const;
};

class GameFont;

class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void setText( UnicodeString text ) = 0;
	virtual UnicodeString getText() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void reset() = 0;
	virtual void setFont( GameFont *font ) = 0;
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(07) SLOT(08) SLOT(09)
#undef SLOT
	virtual void setColors( Color textColor, Color dropColor ) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void draw( int x, int y, int w, int h ) = 0;
	virtual void getSize( int *width, int *height ) = 0;
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
#undef SLOT
	virtual void clearText() = 0;
	virtual void appendChar( WideChar c ) = 0;
	virtual void appendText( const UnicodeString &text ) = 0;
};

class DisplayStringManager
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;
};
extern DisplayStringManager *TheDisplayStringManager;

class GameTextInterface
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( const AsciiString &label, bool *exists = 0 ) = 0;
};
extern GameTextInterface *TheGameText;

class FontLibrary
{
public:
	GameFont *getFont( const AsciiString *name, float pointSize, bool bold );
};
extern FontLibrary *TheFontLibrary;

struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
};

// Font override offsets are retail-measured from init: ZH's order plus one
// unidentified FontDesc at +0x5C.
class GlobalLanguage
{
public:
	int adjustFontSize( int theFontSize );

	char m_opaque00[ 0x38 ];
	FontDesc m_messageFont;							// +0x38
	FontDesc m_militaryCaptionTitleFont;			// +0x44
	FontDesc m_militaryCaptionFont;					// +0x50
	FontDesc m_unknownFont5C;						// +0x5C
	FontDesc m_superweaponCountdownNormalFont;		// +0x68
	FontDesc m_superweaponCountdownReadyFont;		// +0x74
	FontDesc m_namedTimerCountdownNormalFont;		// +0x80
	FontDesc m_namedTimerCountdownReadyFont;		// +0x8C
	FontDesc m_drawableCaptionFont;					// +0x98
};
extern GlobalLanguage *TheGlobalLanguageData;

extern GameLogic *TheGameLogic;

// TheGameLogic's multiplayer predicate 0x0023C6FD, rowed under this name.
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};
#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) double __cdecl floor( double );

// BaseType.h's inline fld/fistp rounding; retail floors through msvcr71.
__forceinline long fast_float2long_round( float f )
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

__forceinline float fast_float_floor( float f )
{
	return (float)floor( (double)f );
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

struct ICoord2D
{
	int x, y;
};

class View
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03)
	virtual void init();
	SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
	virtual void setWidth( int width );
	SLOT(15)
	virtual void setHeight( int height );
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25)
	SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34)
	SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43)
	SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52)
	SLOT(53) SLOT(54) SLOT(55) SLOT(56)
#undef SLOT
	virtual void setDefaultView( float pitch, float angle, float maxHeight );
};
extern View *TheTacticalView;

class Display
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
#define SLOT(N) virtual void slot##N();
	SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26)
	SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34)
#undef SLOT
	virtual void attachView( View *view );
};
extern Display *TheDisplay;

struct FieldParse;

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void parseInGameUIDefinition( INI *ini );
};
typedef void (*INIBlockParse)( INI *ini );

// inihelp.cpp: loads every INI file the legend lists under the name.
bool IniLoad( const char *name, INIBlockParse parse );

// Deleting a window runs its virtual destructor in place and frees through the
// global operator delete (0x0002FD60).
class GameWindow
{
public:
	virtual ~GameWindow();
	__forceinline void deleteInstance() { ::delete this; }
};
struct WindowLayoutInfo;

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const AsciiString &name );
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
	virtual GameWindow *winCreateFromScript( AsciiString filename, WindowLayoutInfo *info = 0, void *unused = 0 );
#define SLOT(N) virtual void slot##N();
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59)
#undef SLOT
	virtual GameWindow *winGetWindowFromId( GameWindow *window, int id );
};
extern GameWindowManager *TheWindowManager;

extern GameWindow *m_replayWindow;

void HideControlBar( bool hide );

class ControlBar
{
public:
	ControlBar();
	virtual ~ControlBar();
	virtual void init();
private:
	char m_opaque04[ 0x2B4 - 0x4 ];
};
extern ControlBar *TheControlBar;

class BannerUI
{
public:
	BannerUI();
	virtual ~BannerUI();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
private:
	char m_opaque04[ 0x44 - 0x4 ];
};
extern BannerUI *g_00DFE32C;

void *Rva0043CCC2Get();
void *Rva004E4312GetRoute();

// STLport's list base: retail folded list<WindowLayout*>::clear into the rowed
// int instantiation at 0x0023DAA5, so the member view names that one.
namespace _STL
{
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc> class _List_base
	{
	public:
		void clear();
	protected:
		void *_M_node;
	};
}

void Rva00433C18( const UnicodeString &text, bool flag );

void GameGetColorComponents( Color color, unsigned char *red, unsigned char *green, unsigned char *blue, unsigned char *alpha );

class Shell
{
public:
	bool isShellActive() const { return m_isShellActive; }
private:
	char m_opaque00[ 0x5C ];
	bool m_isShellActive;						// +0x5C
};
extern Shell *TheShell;

struct MiscAudio
{
	unsigned char m_unmodelled00[ 0xBC ];
	OpaqueRefElement4 m_subtitleTypingSound;	// +0xBC
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3) AUDIO_SLOT(4)
	AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7) AUDIO_SLOT(8) AUDIO_SLOT(9)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
	virtual unsigned int addAudioEvent( const BfmeAudioEventPrefix136 *event );
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34)
	AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44)
	AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54)
	AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64)
	AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74)
	AUDIO_SLOT(75) AUDIO_SLOT(76) AUDIO_SLOT(77)
	virtual const MiscAudio *getMiscAudio();
#undef AUDIO_SLOT
};
extern AudioManager *TheAudio;

inline Color GameMakeColor( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha )
{
	return ( alpha << 24 ) | ( red << 16 ) | ( green << 8 ) | blue;
}

struct RGBAColorInt
{
	int red, green, blue, alpha;
};

class InGameUI
{
public:
#define SLOT(N) virtual void vslot##N();
	SLOT(00)
	virtual void init();
	SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual void __cdecl rva0029E99F( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl rva0029E656( AsciiString stringManagerLabel, ... );
	virtual void __cdecl rva0029E846( UnicodeString format, ... );
	virtual void __cdecl messageColor( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl message( UnicodeString format, ... );
	virtual void __cdecl message( AsciiString stringManagerLabel, ... );
	virtual void vslot20();
	virtual void vslot21();
	virtual void militarySubtitle( const AsciiString &label, int duration );
	virtual void militarySubtitle( UnicodeString subtitle, int duration );
	virtual void removeMilitarySubtitle();
#define SLOT(N) virtual void vslot##N();
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
	SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
	SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85)
	virtual void drawMilitarySubtitle();
	SLOT(87) SLOT(88) SLOT(89)
	SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95)
	virtual const FieldParse *getFieldParse() const;
	SLOT(97) SLOT(98) SLOT(99)
	SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106) SLOT(107)
	virtual void recreateControlBar();
	virtual void setRva0029B04D( int value );
	virtual void clearRva0029B060();
	SLOT(111) SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117)
#undef SLOT
	virtual View *createView() = 0;
	virtual void vslot119() = 0;

protected:
	void createControlBar();
	void createReplayControl();
	void updateMilitarySubtitle();
	void addMessageText( const UnicodeString &formattedMessage, const RGBColor *rgbColor = 0 );

	struct UIMessage
	{
		UnicodeString fullText;
		DisplayString *displayString;
		unsigned int timestamp;
		Color color;
	};
	enum { MAX_UI_MESSAGES = 6 };

	enum { MAX_SUBTITLE_LINES = 4 };
	struct MilitarySubtitleData
	{
		UnicodeString subtitle;									// +0x00
		unsigned int index;										// +0x04
		DisplayString *displayStrings[ MAX_SUBTITLE_LINES ];	// +0x08
		int lineOffsets[ MAX_SUBTITLE_LINES ];					// +0x18
		DisplayString *wordString;								// +0x28
		unsigned int currentDisplayString;						// +0x2C
		unsigned int lifetime;									// +0x30
		unsigned int nextCharTime;								// +0x34
		unsigned int elapsed;									// +0x38
		unsigned int lastTime;									// +0x3C
		Color color;											// +0x40
		bool finished;											// +0x44
	};

	char m_opaque004[ 0x18 - 0x4 ];
	_STL::_List_base<int, _STL::allocator<int> > m_windowLayouts;	// +0x18
	char m_opaque01C[ 0x5D0 - 0x1C ];
	UIMessage m_uiMessages[ MAX_UI_MESSAGES ];	// +0x5D0
	char m_opaque630[ 0x72C - 0x630 ];
	AsciiString m_superweaponNormalFont;		// +0x72C
	int m_superweaponNormalPointSize;			// +0x730
	bool m_superweaponNormalBold;				// +0x734
	AsciiString m_superweaponReadyFont;			// +0x738
	int m_superweaponReadyPointSize;			// +0x73C
	bool m_superweaponReadyBold;				// +0x740
	char m_opaque744[ 0x77C - 0x744 ];
	AsciiString m_namedTimerNormalFont;			// +0x77C
	int m_namedTimerNormalPointSize;			// +0x780
	bool m_namedTimerNormalBold;				// +0x784
	char m_opaque788[ 0x78C - 0x788 ];
	AsciiString m_namedTimerReadyFont;			// +0x78C
	int m_namedTimerReadyPointSize;				// +0x790
	bool m_namedTimerReadyBold;					// +0x794
	char m_opaque798[ 0x79C - 0x798 ];
	AsciiString m_drawableCaptionFont;			// +0x79C
	int m_drawableCaptionPointSize;				// +0x7A0
	bool m_drawableCaptionBold;					// +0x7A4
	char m_opaque7A8[ 0x7F0 - 0x7A8 ];
	MilitarySubtitleData *m_militarySubtitle;	// +0x7F0
	char m_opaque7F4[ 0x814 - 0x7F4 ];
	Color m_messageColor1;						// +0x814
	Color m_messageColor2;						// +0x818
	char m_opaque81C[ 0x82C - 0x81C ];
	AsciiString m_messageFont;					// +0x82C
	int m_messagePointSize;						// +0x830
	bool m_messageBold;							// +0x834
	char m_opaque838[ 0x83C - 0x838 ];
	RGBAColorInt m_militaryCaptionColor;		// +0x83C
	float m_militaryCaptionPositionX;			// +0x84C
	float m_militaryCaptionPositionY;			// +0x850
	bool m_militaryCaptionCentered;				// +0x854
	AsciiString m_militaryCaptionTitleFont;		// +0x858
	int m_militaryCaptionTitlePointSize;		// +0x85C
	bool m_militaryCaptionTitleBold;			// +0x860
	AsciiString m_militaryCaptionFont;			// +0x864
	int m_militaryCaptionPointSize;				// +0x868
	bool m_militaryCaptionBold;					// +0x86C
	int m_militaryCaptionSpeed;					// +0x870
	char m_opaque874[ 0x978 - 0x874 ];
	GameWindow *m_idleWorkerWin;				// +0x978
	char m_opaque97C[ 0x980 - 0x97C ];
	int m_unknown980;							// +0x980
};
extern InGameUI *TheInGameUI;

void InGameUI::rva0029E656( AsciiString stringManagerLabel, ... )
{
	if( !TheBfmeGlob->bfmeCall939D() )
		return;

	UnicodeString stringManagerString;
	UnicodeString formattedMessage;

	stringManagerString = TheGameText->fetch( stringManagerLabel.str() );
	if( stringManagerString.isEmpty() )
		return;

	va_list args;
	va_start( args, stringManagerLabel );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, stringManagerString.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::message( AsciiString stringManagerLabel, ... )
{
	UnicodeString stringManagerString;
	UnicodeString formattedMessage;

	stringManagerString = TheGameText->fetch( stringManagerLabel.str() );

	va_list args;
	va_start( args, stringManagerLabel );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, stringManagerString.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::rva0029E846( UnicodeString format, ... )
{
	if( TheBfmeGlob->bfmeCall939D() )
	{
		UnicodeString formattedMessage;

		va_list args;
		va_start( args, format );
		WideChar buf[ 8192 ];
		if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
			throw ERROR_OUT_OF_MEMORY;
		formattedMessage.set( buf );
		va_end( args );

		addMessageText( formattedMessage );
	}
}

void InGameUI::message( UnicodeString format, ... )
{
	UnicodeString formattedMessage;

	va_list args;
	va_start( args, format );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::rva0029E99F( const RGBColor *rgbColor, UnicodeString format, ... )
{
	if( TheBfmeGlob->bfmeCall939D() )
	{
		UnicodeString formattedMessage;

		va_list args;
		va_start( args, format );
		WideChar buf[ 8192 ];
		if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
			throw ERROR_OUT_OF_MEMORY;
		formattedMessage.set( buf );
		va_end( args );

		addMessageText( formattedMessage, rgbColor );
	}
}

void InGameUI::messageColor( const RGBColor *rgbColor, UnicodeString format, ... )
{
	UnicodeString formattedMessage;

	va_list args;
	va_start( args, format );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage, rgbColor );
}

void InGameUI::addMessageText( const UnicodeString &formattedMessage, const RGBColor *rgbColor )
{
	int i;
	Color color1 = m_messageColor1;
	Color color2 = m_messageColor2;

	if( rgbColor )
	{
		color1 = rgbColor->getAsInt() | 0xFF000000;
		color2 = rgbColor->getAsInt() | 0xFF000000;
	}

	m_uiMessages[ MAX_UI_MESSAGES - 1 ].fullText.clear();
	if( m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString )
		TheDisplayStringManager->freeDisplayString( m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString );
	m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString = 0;
	m_uiMessages[ MAX_UI_MESSAGES - 1 ].timestamp = 0;

	for( i = MAX_UI_MESSAGES - 1; i >= 1; i-- )
		m_uiMessages[ i ] = m_uiMessages[ i - 1 ];

	m_uiMessages[ 0 ].fullText = formattedMessage;
	m_uiMessages[ 0 ].timestamp = TheGameLogic->getFrame();
	m_uiMessages[ 0 ].displayString = TheDisplayStringManager->newDisplayString();
	m_uiMessages[ 0 ].displayString->setFont( TheFontLibrary->getFont( &m_messageFont,
		TheGlobalLanguageData->adjustFontSize( m_messagePointSize ), m_messageBold ) );
	m_uiMessages[ 0 ].displayString->setText( m_uiMessages[ 0 ].fullText );

	if( m_uiMessages[ 1 ].displayString == 0 || m_uiMessages[ 1 ].color == color2 )
		m_uiMessages[ 0 ].color = color1;
	else
		m_uiMessages[ 0 ].color = color2;
}

void InGameUI::militarySubtitle( const AsciiString &label, int duration )
{
	UnicodeString subtitle = TheGameText->fetch( label );
	militarySubtitle( subtitle, duration );
}

template <typename T>
inline T StringBase<T>::getCharAt( int index ) const throw()
{
	return m_data ? m_data->data[ index ] : 0;
}

// Width of the line of text starting at start, measured on ds.
static int getLineWidth( DisplayString *ds, const UnicodeString *text, int start )
{
	int end = start;
	while( end < text->getLength() && text->getCharAt( end ) != L'\n' )
		end++;
	if( end > start )
	{
		int width, height;
		UnicodeString saved = ds->getText();
		ds->setText( UnicodeString( *text, start, end - start ) );
		ds->getSize( &width, &height );
		ds->setText( saved );
		return width;
	}
	return 0;
}

void InGameUI::updateMilitarySubtitle()
{
	if( !m_militarySubtitle )
		return;

	unsigned int lastTime = m_militarySubtitle->lastTime;
	m_militarySubtitle->lastTime = timeGetTime();
	if( TheShell->isShellActive() )
		return;

	unsigned int delta = m_militarySubtitle->lastTime - lastTime;
	if( delta > 100 )
		delta = 100;
	m_militarySubtitle->elapsed += delta;

	if( m_militarySubtitle->finished )
	{
		if( m_militarySubtitle->elapsed > m_militarySubtitle->lifetime )
		{
			unsigned char r, g, b, a;
			GameGetColorComponents( m_militarySubtitle->color, &r, &g, &b, &a );
			int amount = (int)( delta * 0.1f + 1.0f );
			if( a - amount < 0 )
				removeMilitarySubtitle();
			else
			{
				a -= amount;
				m_militarySubtitle->color = GameMakeColor( r, g, b, a );
			}
		}
	}
	else if( m_militarySubtitle->nextCharTime < m_militarySubtitle->elapsed )
	{
		WideChar ch = m_militarySubtitle->subtitle.getCharAt( m_militarySubtitle->index );
		m_militarySubtitle->displayStrings[ m_militarySubtitle->currentDisplayString ]->appendText( m_militarySubtitle->wordString->getText() );
		m_militarySubtitle->wordString->clearText();
		while( ch == L' ' )
		{
			m_militarySubtitle->displayStrings[ m_militarySubtitle->currentDisplayString ]->appendChar( ch );
			m_militarySubtitle->index++;
			if( m_militarySubtitle->index >= m_militarySubtitle->subtitle.getLength() )
				break;
			ch = m_militarySubtitle->subtitle.getCharAt( m_militarySubtitle->index );
		}

		if( ch == L'\n' )
		{
			m_militarySubtitle->currentDisplayString++;
			if( m_militarySubtitle->currentDisplayString < MAX_SUBTITLE_LINES )
			{
				DisplayString **ds = &m_militarySubtitle->displayStrings[ m_militarySubtitle->currentDisplayString ];
				*ds = TheDisplayStringManager->newDisplayString();
				(*ds)->reset();
				(*ds)->setFont( TheFontLibrary->getFont( &m_militaryCaptionFont,
					TheGlobalLanguageData->adjustFontSize( m_militaryCaptionPointSize ), m_militaryCaptionBold ) );
				m_militarySubtitle->nextCharTime = m_militarySubtitle->elapsed + m_militaryCaptionSpeed;
				if( m_militaryCaptionCentered )
					m_militarySubtitle->lineOffsets[ m_militarySubtitle->currentDisplayString ] = getLineWidth( *ds, &m_militarySubtitle->subtitle, m_militarySubtitle->index + 1 ) / -2;
			}
			else
				m_militarySubtitle->index = m_militarySubtitle->subtitle.getLength();
		}
		else
		{
			m_militarySubtitle->wordString->appendChar( ch );
			static BfmeAudioEventPrefix136 click( TheAudio->getMiscAudio()->m_subtitleTypingSound, 0 );
			TheAudio->addAudioEvent( &click );
			m_militarySubtitle->nextCharTime = m_militarySubtitle->elapsed + m_militaryCaptionSpeed;
		}

		m_militarySubtitle->index++;
		if( m_militarySubtitle->index >= m_militarySubtitle->subtitle.getLength() )
		{
			if( m_militarySubtitle->elapsed + 2000 > m_militarySubtitle->lifetime )
				m_militarySubtitle->lifetime = m_militarySubtitle->elapsed + 2000;
			m_militarySubtitle->finished = true;
		}
	}
}

void InGameUI::drawMilitarySubtitle()
{
	if( !m_militarySubtitle )
		return;

	float progress = 1.0f - (float)( m_militarySubtitle->nextCharTime - m_militarySubtitle->elapsed ) / m_militaryCaptionSpeed;
	ICoord2D pos;
	pos.x = REAL_TO_INT_FLOOR( TheDisplay->getWidth() * m_militaryCaptionPositionX + 0.5f );
	pos.y = REAL_TO_INT_FLOOR( TheDisplay->getHeight() * m_militaryCaptionPositionY + 0.5f );

	unsigned char r, g, b, a;
	GameGetColorComponents( m_militarySubtitle->color, &r, &g, &b, &a );
	Color dropColor = GameMakeColor( 0, 0, 0, a );

	int width = 0;
	int y = pos.y;
	ICoord2D wordPos;
	for( unsigned int i = 0; i <= m_militarySubtitle->currentDisplayString; i++ )
	{
		wordPos.y = y;
		int height;
		m_militarySubtitle->displayStrings[ i ]->getSize( &width, &height );
		m_militarySubtitle->displayStrings[ i ]->setColors( m_militarySubtitle->color, dropColor );
		m_militarySubtitle->displayStrings[ i ]->draw( pos.x + m_militarySubtitle->lineOffsets[ i ], y, 1, 1 );
		y += height;
	}

	wordPos.x = (int)( m_militarySubtitle->lineOffsets[ m_militarySubtitle->currentDisplayString ] + width + ( 1.0f - progress ) * 30.0f + pos.x );
	a = (unsigned char)( a * progress );
	m_militarySubtitle->wordString->setColors( GameMakeColor( r, g, b, a ), GameMakeColor( 0, 0, 0, a ) );
	m_militarySubtitle->wordString->draw( wordPos.x, wordPos.y, 1, 1 );
}

void InGameUI::militarySubtitle( UnicodeString subtitle, int duration )
{
	removeMilitarySubtitle();
	Rva00433C18( subtitle, false );

	if( subtitle.isEmpty() || duration <= 0 )
		return;

	subtitle += L' ';
	m_militarySubtitle = new MilitarySubtitleData;
	m_militarySubtitle->subtitle.set( subtitle );
	m_militarySubtitle->lifetime = duration;
	m_militarySubtitle->elapsed = 0;
	m_militarySubtitle->nextCharTime = 0;
	m_militarySubtitle->lastTime = timeGetTime();
	m_militarySubtitle->index = 0;
	m_militarySubtitle->finished = false;
	for( int i = 1; i < MAX_SUBTITLE_LINES; i++ )
	{
		m_militarySubtitle->displayStrings[ i ] = 0;
		m_militarySubtitle->lineOffsets[ i ] = 0;
	}

	GameFont *font = TheFontLibrary->getFont( &m_militaryCaptionTitleFont,
		TheGlobalLanguageData->adjustFontSize( m_militaryCaptionTitlePointSize ), m_militaryCaptionTitleBold );

	m_militarySubtitle->currentDisplayString = 0;
	m_militarySubtitle->displayStrings[ 0 ] = TheDisplayStringManager->newDisplayString();
	m_militarySubtitle->displayStrings[ 0 ]->reset();
	m_militarySubtitle->displayStrings[ 0 ]->setFont( font );
	if( m_militaryCaptionCentered )
		m_militarySubtitle->lineOffsets[ 0 ] = getLineWidth( m_militarySubtitle->displayStrings[ 0 ], &m_militarySubtitle->subtitle, 0 ) / -2;

	m_militarySubtitle->wordString = TheDisplayStringManager->newDisplayString();
	m_militarySubtitle->wordString->reset();
	m_militarySubtitle->wordString->setFont( font );

	m_militarySubtitle->color = GameMakeColor( m_militaryCaptionColor.red, m_militaryCaptionColor.green,
		m_militaryCaptionColor.blue, m_militaryCaptionColor.alpha );

	if( (float)m_militaryCaptionSpeed < 1.0f )
		m_militaryCaptionSpeed = 1;
}

void InGameUI::removeMilitarySubtitle()
{
	if( !m_militarySubtitle )
		return;

	TheInGameUI->clearRva0029B060();

	for( unsigned int i = 0; i <= m_militarySubtitle->currentDisplayString; i++ )
	{
		TheDisplayStringManager->freeDisplayString( m_militarySubtitle->displayStrings[ i ] );
		m_militarySubtitle->displayStrings[ i ] = 0;
	}
	TheDisplayStringManager->freeDisplayString( m_militarySubtitle->wordString );

	delete m_militarySubtitle;
	m_militarySubtitle = 0;
}

void InGameUI::createControlBar()
{
	TheWindowManager->winCreateFromScript( AsciiString( "ControlBar.wnd" ) );
	HideControlBar( true );
}

void InGameUI::createReplayControl()
{
	m_replayWindow = TheWindowManager->winCreateFromScript( AsciiString( "ReplayControl.wnd" ) );
}

void INI::parseInGameUIDefinition( INI *ini )
{
	if( TheInGameUI )
		ini->initFromINI( TheInGameUI, TheInGameUI->getFieldParse() );
}

// isEmpty was header-defined: MSVC keeps the call out of line (0x00001E2F) but,
// knowing the body, keeps TheGlobalLanguageData in edi across it.
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline bool StringBase<char>::isNotEmpty() const { return !isEmpty(); }

void InGameUI::init()
{
	IniLoad( "InGameUI", INI::parseInGameUIDefinition );

	// override INI values with language localized values
	if( TheGlobalLanguageData )
	{
		if( TheGlobalLanguageData->m_drawableCaptionFont.name.isNotEmpty() )
		{
			m_drawableCaptionFont = TheGlobalLanguageData->m_drawableCaptionFont.name;
			m_drawableCaptionPointSize = TheGlobalLanguageData->m_drawableCaptionFont.size;
			m_drawableCaptionBold = TheGlobalLanguageData->m_drawableCaptionFont.bold;
		}
		if( TheGlobalLanguageData->m_messageFont.name.isNotEmpty() )
		{
			m_messageFont = TheGlobalLanguageData->m_messageFont.name;
			m_messagePointSize = TheGlobalLanguageData->m_messageFont.size;
			m_messageBold = TheGlobalLanguageData->m_messageFont.bold;
		}
		if( TheGlobalLanguageData->m_militaryCaptionTitleFont.name.isNotEmpty() )
		{
			m_militaryCaptionTitleFont = TheGlobalLanguageData->m_militaryCaptionTitleFont.name;
			m_militaryCaptionTitlePointSize = TheGlobalLanguageData->m_militaryCaptionTitleFont.size;
			m_militaryCaptionTitleBold = TheGlobalLanguageData->m_militaryCaptionTitleFont.bold;
		}
		if( TheGlobalLanguageData->m_militaryCaptionFont.name.isNotEmpty() )
		{
			m_militaryCaptionFont = TheGlobalLanguageData->m_militaryCaptionFont.name;
			m_militaryCaptionPointSize = TheGlobalLanguageData->m_militaryCaptionFont.size;
			m_militaryCaptionBold = TheGlobalLanguageData->m_militaryCaptionFont.bold;
		}
		if( TheGlobalLanguageData->m_superweaponCountdownNormalFont.name.isNotEmpty() )
		{
			m_superweaponNormalFont = TheGlobalLanguageData->m_superweaponCountdownNormalFont.name;
			m_superweaponNormalPointSize = TheGlobalLanguageData->m_superweaponCountdownNormalFont.size;
			m_superweaponNormalBold = TheGlobalLanguageData->m_superweaponCountdownNormalFont.bold;
		}
		if( TheGlobalLanguageData->m_superweaponCountdownReadyFont.name.isNotEmpty() )
		{
			m_superweaponReadyFont = TheGlobalLanguageData->m_superweaponCountdownReadyFont.name;
			m_superweaponReadyPointSize = TheGlobalLanguageData->m_superweaponCountdownReadyFont.size;
			m_superweaponReadyBold = TheGlobalLanguageData->m_superweaponCountdownReadyFont.bold;
		}
		if( TheGlobalLanguageData->m_namedTimerCountdownNormalFont.name.isNotEmpty() )
		{
			m_namedTimerNormalFont = TheGlobalLanguageData->m_namedTimerCountdownNormalFont.name;
			m_namedTimerNormalPointSize = TheGlobalLanguageData->m_namedTimerCountdownNormalFont.size;
			m_namedTimerNormalBold = TheGlobalLanguageData->m_namedTimerCountdownNormalFont.bold;
		}
		if( TheGlobalLanguageData->m_namedTimerCountdownReadyFont.name.isNotEmpty() )
		{
			m_namedTimerReadyFont = TheGlobalLanguageData->m_namedTimerCountdownReadyFont.name;
			m_namedTimerReadyPointSize = TheGlobalLanguageData->m_namedTimerCountdownReadyFont.size;
			m_namedTimerReadyBold = TheGlobalLanguageData->m_namedTimerCountdownReadyFont.bold;
		}
	}

	if( TheDisplay )
	{
		// make the tactical display the full screen width and height
		TheTacticalView = createView();
		TheTacticalView->init();
		TheDisplay->attachView( TheTacticalView );

		TheTacticalView->setWidth( TheDisplay->getWidth() );
		// keep the tactical view from rendering underneath the control bar
		TheTacticalView->setHeight( TheDisplay->getHeight() * 0.77f );
	}
	TheTacticalView->setDefaultView( 0.0f, 0.0f, 1.0f );

	createControlBar();
	createReplayControl();

	TheControlBar = new ControlBar;
	TheControlBar->init();

	m_windowLayouts.clear();

	vslot119();

	g_00DFE32C = new BannerUI;
	g_00DFE32C->init();
	g_00DFE32C->loadIniFilesFromLegend();

	Rva0043CCC2Get();
	Rva004E4312GetRoute();

	m_unknown980 = 0;
}

void InGameUI::recreateControlBar()
{
	GameWindow *win = TheWindowManager->winGetWindowFromId( 0, TheNameKeyGenerator->nameToKey( AsciiString( "ControlBar.wnd" ) ) );
	if( win )
		win->deleteInstance();

	m_idleWorkerWin = 0;

	createControlBar();

	if( TheControlBar )
	{
		::delete TheControlBar;
		TheControlBar = new ControlBar;
		TheControlBar->init();
	}
}
