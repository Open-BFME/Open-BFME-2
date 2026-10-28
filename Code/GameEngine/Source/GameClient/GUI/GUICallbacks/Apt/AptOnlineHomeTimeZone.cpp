// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// platformsdk
//
// ?rva005B977B@OnlineHome@AptOnline@@QAEXXZ @0x005B977B 366B
// Online home screen time-zone refresh, called from the screen constructor
// 0x005B9BBC (AptOnlineHomeConstructor.cpp). Kept in its own unit because the
// callbacks unit (AptOnlineHomeCallbacks.cpp) compiles without /O1 /G7 /EHsc.
// WB twin 0x01585130 (a longer revision of the same routine) translates the
// converted zone name inside each branch; spelling the two translate calls
// that way gives retail's frame homes and argument order (bank 0.96 -> exact).

#include <windows.h>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow;

namespace AptOnline
{
class OnlineHome
{
public:
	void rva005B977B();
	void rva005B95B8();
	void rva005B98E9();
private:
	unsigned char m_pad000[0x60];
	GameWindow *m_motd; // +0x60
};
}

// Native5B977B..5B98E9 RET0;366B. TimeZone172B and512B conversion
// buffer measured from native Win32 arguments. BF1 9cb wholehome has
// same zone abbreviation loop, embedded in a larger player-stat refresh.
// Target resets12 ticker rows and calls the separately rowed PS request.
typedef char HomeZoneSize[sizeof(TIME_ZONE_INFORMATION)==172 ? 1:-1];
class Rva005B9378 { public: void rva005B9378(int,const UnicodeString &); };
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
void rva005BD64D();
// getCharAt(0) is inlined in native; canonical header declares it out of
// line. Shared string header layout proves the data pointer/text+8 view.
static inline unsigned short onlineHomeFirst(const UnicodeString &text)
{
 const unsigned char *data=*reinterpret_cast<const unsigned char *const *>(&text);
 return data ? *reinterpret_cast<const unsigned short *>(data+8):0;
}
void AptOnline::OnlineHome::rva005B977B()
{
 for(int i=0;i<12;++i)
  reinterpret_cast<Rva005B9378 *>(this)->rva005B9378(i,L"-");
 TIME_ZONE_INFORMATION zone;
 unsigned long result=GetTimeZoneInformation(&zone);
 UnicodeString zoneText;
 char buffer[512];
 if(result==0xffffffff) zoneText.format(UnicodeString::TheEmptyString.str());
 else {
  if(result==2) { WideCharToMultiByte(0,0,zone.DaylightName,-1,buffer,512,0,0); zoneText.translate(buffer); }
  else { WideCharToMultiByte(0,0,zone.StandardName,-1,buffer,512,0,0); zoneText.translate(buffer); }
 }
 UnicodeString token,initials;
 while(zoneText.nextToken(&token,L" ")) {
  unsigned short c=onlineHomeFirst(token);
  initials.concat(&c,1);
 }
 g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:TimeZone"),initials,false);
 rva005BD64D();
 rva005B95B8();
}

// stlport
// Retail 0x005B98E9, 642 bytes: the online home screen's message of the day. Each line of the
// GameSpyInfo MOTD (virtual slot 0x10C) is trimmed, an escaped line loses its backslash, a
// "\AARRGGBB" prefix selects the colour (grabHexInt on four byte pairs; otherwise the palette entry 27
// of GameSpyColor, 0x00DB9204), and the line is added to the list box at +0x60. Same flow as BFME 1's
// OnlineHomeMessageOfTheDay.cpp; WorldBuilder 0x015855D0.
#include <string>
// Keep _String_base<unsigned short>::~_String_base inline-only: no call here
// leaves it out of line, and this TU's COMDAT copy is not retail's body.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<unsigned short, allocator<unsigned short> >::~_String_base() { _M_deallocate_block(); }
}
#include <stdlib.h>


// Retail expands getCharAt in place here (movsx from the buffer, null-checked), as LadderDefs.cpp's
// TU does; the out-of-line COMDAT stays with the library.
template<> __declspec(dllimport) __forceinline char StringBase<char>::getCharAt(int index) const throw()
{
	return m_data ? m_data->data[index] : 0;
}

class GameSpyInfoMotd
{
public:
	virtual void s000(); virtual void s004(); virtual void s008(); virtual void s00C();
	virtual void s010(); virtual void s014(); virtual void s018(); virtual void s01C();
	virtual void s020(); virtual void s024(); virtual void s028(); virtual void s02C();
	virtual void s030(); virtual void s034(); virtual void s038(); virtual void s03C();
	virtual void s040(); virtual void s044(); virtual void s048(); virtual void s04C();
	virtual void s050(); virtual void s054(); virtual void s058(); virtual void s05C();
	virtual void s060(); virtual void s064(); virtual void s068(); virtual void s06C();
	virtual void s070(); virtual void s074(); virtual void s078(); virtual void s07C();
	virtual void s080(); virtual void s084(); virtual void s088(); virtual void s08C();
	virtual void s090(); virtual void s094(); virtual void s098(); virtual void s09C();
	virtual void s0A0(); virtual void s0A4(); virtual void s0A8(); virtual void s0AC();
	virtual void s0B0(); virtual void s0B4(); virtual void s0B8(); virtual void s0BC();
	virtual void s0C0(); virtual void s0C4(); virtual void s0C8(); virtual void s0CC();
	virtual void s0D0(); virtual void s0D4(); virtual void s0D8(); virtual void s0DC();
	virtual void s0E0(); virtual void s0E4(); virtual void s0E8(); virtual void s0EC();
	virtual void s0F0(); virtual void s0F4(); virtual void s0F8(); virtual void s0FC();
	virtual void s100(); virtual void s104(); virtual void s108();
	virtual const AsciiString &getMOTD();
};
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern int GameSpyColor[];
void GadgetListBoxReset(GameWindow *);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);
_STL::wstring MultiByteToWideCharSingleLine(const char *);

// The two hex digits are read through a four-character "0xff" template.
namespace CrtIAT { extern "C" __declspec(dllimport) long __cdecl strtol(const char*,char**,int); }
static int __cdecl grabHexInt(const char *s)
{
	char buffer[5] = "0xff";
	buffer[2] = s[0];
	buffer[3] = s[1];
	return CrtIAT::strtol(buffer, 0, 16);
}

namespace AptOnline
{
void OnlineHome::rva005B98E9()
{
	if (m_motd && TheGameSpyInfo)
	{
		GadgetListBoxReset(m_motd);
		AsciiString line;
		UnicodeString text;
		AsciiString motd = ((GameSpyInfoMotd *)TheGameSpyInfo)->getMOTD();
		int color;
		while (motd.nextToken(&line, "\n"))
		{
			if (line.getCharAt(line.getLength() - 1) == '\r')
				line.removeLastChar();	// there is alpha trailing '\r'
			line.trim();
			if (line.isEmpty())
				line = " ";
			color = GameSpyColor[27];
			if (line.startsWith("\\\\"))
				line = line.str() + 1;
			else if (line.startsWith("\\") && line.getLength() > 9)
			{
				// take out the hex value from strings starting as "\ffffffffText"
				unsigned char alpha = grabHexInt(line.str() + 1);
				unsigned char r = grabHexInt(line.str() + 3);
				unsigned char green = grabHexInt(line.str() + 5);
				unsigned char blue = grabHexInt(line.str() + 7);
				color = (alpha << 24) | (r << 16) | (green << 8) | blue;
				line = line.str() + 9;
			}
			text = UnicodeString(MultiByteToWideCharSingleLine(line.str()).c_str());
			GadgetListBoxAddEntryText(m_motd, text, color, -1, -1, true);
			GadgetListBoxSetTopVisibleEntry(m_motd, 0);
		}
	}
}
}
