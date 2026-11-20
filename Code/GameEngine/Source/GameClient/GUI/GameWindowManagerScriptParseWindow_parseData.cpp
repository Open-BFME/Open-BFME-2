// cl: /O1 /Ireference/open-bfme-1/game/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/GameEngine/Source/Common/System /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
//
// ?parseData@@YA_NPAPAXPAD1@Z
// retail 0x0031553A, 644 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// Retail RVA 0x00487F80, 1328 bytes. Port of the Zero Hour parser with
// BFME's shared window record (0x012F253C), File scanString slot +0x24,
// and native StringBase layout. WinInstanceData uses the reference header;
// its accessed offsets are independently witnessed by name_oracle.
// parseData's layout corrections also probe exact. The file statics
// (theSystemString..theDrawString) and createWindow's static helpers live
// in GameWindowManagerScript.cpp, whose initializers retail's table holds.

#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "GameClient/Gadget.h"
#include <string.h>

#include "../../../Include/Common/ScalarTypes.h"


// Ledger names for the two GameWindow calls retail makes on every path
// (ZH winSetWindowId / winGetEditData positions; identities not yet proven).
class Rva00478C90Object { public: Int store( UnsignedInt value ); };
class Gen_004791e0 { public: Int m( void ); };

class Open2479440Record
{
public:
 GameWindow *field00;
 int field04,field08,field0c,field10,field14;
 void *field18,*field1c,*field20,*field24,*field28,*field2c;
 WinInstanceData *m_instData;
};

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva004874A0ManagerView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70();
	virtual GameWindow *s74( Open2479440Record *record );		// ZH winCreate position
	virtual int s78(GameWindow *window); virtual void s7C();
	virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8C();
	virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9C();
	virtual void sA0(); virtual void sA4(); virtual void sA8(); virtual void sAC();
	virtual void sB0(); virtual void sB4(); virtual void sB8(); virtual void sBC();
	virtual void sC0(); virtual void sC4(); virtual void sC8(); virtual void sCC();
	virtual void sD0(); virtual void sD4();
	virtual Int sD8( GameWindow *window, UnsignedInt msg,
		UnsignedInt data1, UnsignedInt data2 );	// ZH winSendInputMsg position
};

class GameTextInterface;
extern GameTextInterface *TheGameText;

class Rva004864E0GameTextView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24();
	virtual UnicodeString s28( const char *label, bool *exists );	// ZH fetch position
};

GameWindow *createGadget( char *type, void *data, Open2479440Record *record, GameWindow *source );








// Native BFME StringBase inlines at this caller.
template<> inline int StringBase<char>::compare(const char *s) const {
 int n = s ? strlen(s) : 0;
 int len = getLength(); const char *text = str();
 int common = len < n ? len : n;
 int c = memcmp(text,s,common); return c ? c : len-n;
}
class File;
class FileScan00487F80 { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual bool scanString(AsciiString &s);
};
class Display00487F80 { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28();
 virtual int getWidth(); virtual int getHeight();
};
extern Display00487F80 *display00487F80;
class HeaderTemplateManager { public: GameFont *getFontFromTemplate(AsciiString name); };
extern HeaderTemplateManager *TheHeaderTemplateManager;


bool parseScreenRect(int*,int*,int*,int*);
bool parseChildWindows(GameWindow*,File*,char*);
struct GameWindowParse { char *name; bool (*parse)(char*,WinInstanceData*,char*,void*); };
extern GameWindowParse gameWindowFieldList[];
static Open2479440Record windowRecord;
static unsigned int defTextColor;
static GameFont *defFont;
enum { WIN_BUFFER_LENGTH = 2048 };
static char *seps = " =;\n\r\t";
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

	  c = strtok( buffer, " \t\n\r" );
    sData.minVal = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    sData.maxVal = atoi(c);

    *data = &sData;

  } 
	else if( !strcmp( type, "SCROLLLISTBOX" ) ) 
	{

    memset( &lData, 0, sizeof( LocalListboxData ) );

	  c = strtok( buffer, " \t\n\r" );
    lData.listLength = atoi(c);

//	  c = strtok( NULL, " \t\n\r" );
//    lData.entryHeight = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoScroll = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoPurge = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.scrollBar = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.multiSelect = atoi(c);

		c = strtok( NULL, " \t\n\r" );
		lData.forceSelect = atoi(c);

    *data = &lData;

  } 
	else if( !strcmp( type, "ENTRYFIELD" ) ) 
	{

    memset( &eData, 0, sizeof( EntryData004850C0 ) );

	  c = strtok( buffer, " \t\n\r" );
    eData.maxTextLen = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
//    if (c)
//      eData.entryWidth = atoi(c);
//    else
//      eData.entryWidth = -1;

		c = strtok( NULL, " \t\n\r" );
		if (c)
		{
			eData.secretText = atoi(c);

			if( eData.secretText != FALSE )
				eData.secretText = TRUE;
		}
		else
			eData.secretText = FALSE;

        eData.field0c = 0;
        c = strtok(NULL, " \t\n\r");
        if (c) {
            if (atoi(c) == 1) eData.field0c |= 0x20;
            if (atoi(c) == 2) eData.field0c |= 0x40;
            if (atoi(c) == 3) eData.field0c |= 0x10;
        }
    *data = &eData;

  } 
	else if( !strcmp( type, "STATICTEXT" ) ) 
	{

	  c = strtok( buffer, " \t\n\r" );
    tData.centered = atoi(c);

		if( tData.centered != FALSE )
			tData.centered = TRUE;

	  c = strtok( NULL, " \t\n\r" );

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

		c = strtok( buffer, " \t\n\r" );
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

}  // end parseWindow

// Emission anchor: parseData is static and its callers are not carried here.
// MSVC gives a static whose address is never taken a register calling
// convention, so it is kept alive by direct calls. Build scaffolding; it
// claims no retail bytes.
// ?parseDataAnchor absent-from-retail
Bool parseDataAnchor(void **data, char *type, char *buffer)
{
	parseData(data, type, buffer);
	return parseData(data, type, buffer);
}
