// ?rva005B977B@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.96 date=2026-10-08
// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's online home screen Apt callbacks, bound as member pointers by
// the screen's registration under three spellings of its name
// ("AptOnline::OnlineHome::OnOpened", "AptOnlineHome::InitGadgets",
// "OnlineHome::NumTickerFields"); that binding is their only reference.
// They act on one object, viewed here as the first spelling's class.

#include "unicode_string.h"
#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *window, const unsigned short *operation, const unsigned short *file, const unsigned short *parameters, const unsigned short *directory, int show);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

class GameWindow;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void bfmeMinimizeCurrentThreadWindow();
class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *listBox);
void bfmeGo924A(BfmeKeyLC *listBox, char flag);

// The online home screen instance (Rva005B922FDtor.cpp's g_Va00E06480).
extern int g_Va00E06480;

namespace AptOnline
{
class OnlineHome
{
public:
	void OnOpened(const char *unused);
	void OfficialSite(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void NumTickerFields(int query, char *result, bool skip);

	// Unrowed 0x005B977B (366 bytes) and 0x005B98E9 (refills the message of
	// the day), pinned by address.
	void rva005B977B();
 void rva005B95B8();
	void rva005B98E9();

private:
	unsigned char m_pad00[0x60];
	GameWindow *m_messageOfTheDay; // +0x60
};
}

// Retail 0x005B9B6B, 8 bytes: "AptOnline::OnlineHome::OnOpened".
void AptOnline::OnlineHome::OnOpened(const char *unused)
{
	rva005B977B();
}

// Retail 0x005B930C, 108 bytes: "AptOnline::OnlineHome::OfficialSite" opens
// the localized URL:LotrLadder in Internet Explorer and minimizes the game
// window (AptMpClans::WebSite's pattern).
void AptOnline::OnlineHome::OfficialSite(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:LotrLadder");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}

// Retail 0x005B9B73, 73 bytes: "AptOnlineHome::InitGadgets" keeps the
// "OnlineHome::MessageOfTheDay" list box and fills it.
void AptOnline::OnlineHome::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!g_Va00E06480)
		return;
	if (!window)
		return;
	GadgetListBoxReset(window);
	if (strcmp(name, "OnlineHome::MessageOfTheDay") == 0)
	{
		m_messageOfTheDay = window;
		bfmeGo924A((BfmeKeyLC *)window, 0);
		rva005B98E9();
	}
}

// Retail 0x005B906C, 51 bytes: "OnlineHome::NumTickerFields", an Apt query
// answering 12.
void AptOnline::OnlineHome::NumTickerFields(int query, char *result, bool skip)
{
	if (!skip)
		*result = 0;
	if (query == 0 && !skip)
		_snprintf(result, 0xFF, "%d", 12);
}

// Native5B977B..5B98E9 RET0;366B. TimeZone172B and512B conversion
// buffer measured from native Win32 arguments. BF1 9cb wholehome has
// same zone abbreviation loop, embedded in a larger player-stat refresh.
// Target resets12 ticker rows and calls the separately rowed PS request.
struct HomeSystemTime { unsigned short field[8]; };
struct HomeTimeZone { long bias; unsigned short standardName[32]; HomeSystemTime standardDate;
 long standardBias; unsigned short daylightName[32]; HomeSystemTime daylightDate; long daylightBias; };
typedef char HomeZoneSize[sizeof(HomeTimeZone)==172 ? 1:-1];
extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeZoneInformation(HomeTimeZone *);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned,unsigned long,const unsigned short *,int,char *,int,const char *,int *);
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
 HomeTimeZone zone;
 unsigned long result=GetTimeZoneInformation(&zone);
 UnicodeString zoneText;
 char buffer[512];
 if(result==0xffffffff) zoneText.format(UnicodeString::TheEmptyString.str());
 else {
  if(result==2) WideCharToMultiByte(0,0,zone.daylightName,-1,buffer,512,0,0);
  else WideCharToMultiByte(0,0,zone.standardName,-1,buffer,512,0,0);
  zoneText.translate(buffer);
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
