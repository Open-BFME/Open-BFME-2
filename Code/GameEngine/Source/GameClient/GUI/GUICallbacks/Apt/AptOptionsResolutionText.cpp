// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0051A669@AptOptions@@QAEXXZ
// retail 0x0051A669..0x0051A78E (293 bytes) EH thiscall (this unused).
// The options screen's locked-resolution caption: called on the screen by
// the unrowed 0x0051A78E right after the rowed master-option caption
// 0x005189CF (Rva005189CFText.cpp) which builds the same shape for
// APT:CannotChangeGraphics. The "Resolution" key of a temporary
// OptionPreferences (rowed ctor 0x002E434E and map operator[] 0x002031FB
// pinned dtor 0x002E4272) is read as in InitGadgets
// (AptOptionsInitGadgets.cpp, the function before this one); when it is
// non-empty and sscanf "%d%d" reads both values the caption starts with
// L"(%dx%d) - " (rowed UnicodeString::format 0x006CB5D0); then
// TheGameText's char fetch (vslot 15) of APT:CannotChangeResolution is
// concatenated (rowed 0x00006A2A) and the rowed
// BfmeAptWindowManager::bfmeSetText 0x00225301 on g_bfmeAptWindowManager
// shows it under that label. The method name is address-derived.
#include <map>
#include <stdio.h>

#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// The 0x14-byte UserPreferences layout (vftable then the map at +4 and the
// file name at +0x10) as OptionPreferences_ctor.cpp has it.
class OptionPreferences : public _STL::map<AsciiString, AsciiString>
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

private:
	UnicodeString m_filename; // +0x10
};

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &label, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class AptOptions
{
public:
	void rva0051A669();
};

void AptOptions::rva0051A669()
{
	UnicodeString text;
	AsciiString selectedResolution = OptionPreferences()["Resolution"];
	if (!selectedResolution.isEmpty())
	{
		int xres, yres;
		if (sscanf(selectedResolution.str(), "%d%d", &xres, &yres) == 2)
			text.format(L"(%dx%d) - ", xres, yres);
	}
	text.concat(TheGameText->fetch("APT:CannotChangeResolution"));
	g_bfmeAptWindowManager->bfmeSetText("APT:CannotChangeResolution", text, false);
}
