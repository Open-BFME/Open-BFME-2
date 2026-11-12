// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// GameState::rva002DD282, retail 0x002DD282..0x002DD38D (267 bytes, RET8 with
// hidden UnicodeString return): the first free default save file name for a
// save mode. The format text is L"%d" unless TheGameText fetches
// "GUI:DefaultSaveFileName"; for i = 1..99999998 the name is formatted, joined
// with the mode's save suffix (0x002DBC97) by the concat proxy 0x002DBD80,
// widened by AsciiStringPlusText::operator UnicodeString (0x002DD111) straight
// into the by-value argument of the existence check 0x002DCCFB, and the first
// name that does not exist is returned (L"0" when every name is taken).
// Identity: WorldBuilder twin 0xE6B150 and the sole caller GameState::saveGame
// 0x002DD38D (Rva002DBC97Get.cpp); the method name is address-derived.
// Target facts: literals, callees, the dead mode parameter slot reused for the
// name, EH states read off retail. Passing the proxy to the UnicodeString
// parameter (implicit conversion) builds the argument in place as retail does.
#include "unicode_string.h"

struct AsciiStringPlusText
{
	operator UnicodeString();
	int m_00;
	const char *m_ptr;
	int m_len;
};
struct Rva002DBD80Val : AsciiStringPlusText
{
};
Rva002DBD80Val Rva002DBD80Make(int x, const unsigned short *s);

#include "../../../../Include/Common/Rva002DCCFB.h"

#include "../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../../Include/Common/GameState.h"

UnicodeString GameState::rva002DD282(int mode)
{
	const unsigned short *suffix = (const unsigned short *)rva002DBC97Get(mode);
	UnicodeString formatText((const unsigned short *)L"%d");
	if (TheGameText)
		formatText = TheGameText->fetch("GUI:DefaultSaveFileName");
	for (int i = 1; i < 99999999; ++i)
	{
		UnicodeString leaf;
		leaf.format(&formatText, i);
		if (!((Rva002DCCFB *)this)->rva002DCCFB(Rva002DBD80Make((int)&leaf, suffix)))
			return leaf;
	}
	return UnicodeString((const unsigned short *)L"0");
}
