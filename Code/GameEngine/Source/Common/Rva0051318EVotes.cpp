// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0051318ESet@@YGXHH@Z @0x0051318E 140B: DisconnectScreen VotesReceived update via AsciiString format plus Unicode wide space plus conditional format plus bfmeSetText.
// Evidence: literal DisconnectScreen::VotesReceived%d plus rowed AsciiString format 0x00038150 plus StringBase PBG 0x00037E30 plus UnicodeString format 0x006CB5D0 plus bfmeSetText pin 0x00225301 plus releaseBuffers 0x00036E70 0x00036410; callers 0x004D3C81 0x004D3D20 0x004D414E; donor DisconnectMenuVotes.cpp updateVotes.
// Uses shared ascii header for AsciiString and StringBase; UnicodeString minimal with PBG ctor forwarding to the rowed base.
#include "ascii_string.h"

#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const unsigned short g_Va007C9260[];

void __stdcall Rva0051318ESet(int slot, int votes)
{
	AsciiString key;
	key.format("DisconnectScreen::VotesReceived%d", slot);
	UnicodeString value(L" ");
	if (votes)
		value.format(g_Va007C9260, votes);
	g_bfmeAptWindowManager->bfmeSetText(key, value, false);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")
