// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00583202Set@@YGXH@Z @0x00583202 206B
// File-transfer loading time setter: clamps a seconds count at zero, splits
// minutes/seconds, formats via TheGameText "MapTransfer:Timeout" fetch into a
// stack buffer, then bfmeSetText with key "APT:FileTransferLoadingTime".
// Evidence: callers 0x0044C621 0x0044C820 pass one int ret4; fetch slot 0x3C
// on 0x9FF0BC; swprintf IAT msvcr71.dll; bfmeSetText pin 0x00225301;
// releaseBuffer 0x00036410 ansi 0x00036E70 wide; StringBase ctors 0x00037BA0
// ansi 0x00037E30 wide; wide empty fallback VA 0x00BBB5C4.
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
class AsciiString;

#include "ascii_string.h"

#include "unicode_string.h"


class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

extern "C" __declspec(dllimport) int __cdecl swprintf(wchar_t *buffer, const wchar_t *format, ...);

void __stdcall Rva00583202Set(int totalSeconds)
{
	if (totalSeconds < 0)
		totalSeconds = 0;
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds - minutes * 60;
	wchar_t buf[260];
	swprintf(buf, TheGameText->fetch("MapTransfer:Timeout", 0).str(), minutes, seconds);
	UnicodeString value(buf);
	AsciiString key("APT:FileTransferLoadingTime");
	g_bfmeAptWindowManager->bfmeSetText(key, value, false);
}
