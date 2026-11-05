// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?GetArmySummaryName@@YA?AVUnicodeString@@PAVRva00220808@@@Z @0x00220808 131B
// Free cdecl helper returning UnicodeString via AsciiString at +0x64: empty check
// through rowed StringBase<char>::isEmpty 0x00001E2F, else TheGameText slot 0x38
// Ascii fetch plus StringBase<ushort>::set 0x00037150 into a local, then
// StringBase<ushort> copy 0x00037050 into the hidden return with releaseBuffer
// 0x00036E70 cleanup. Evidence: retail call chain isEmpty/fetch/set/copy/release,
// TheGameText VA 0x009FF0BC, callers 0x0031924D/0x0056BB1A forwarding hidden plus
// src, neighbours 0x002207C4/0x0022088B.
#include "ascii_string.h"

#include "unicode_string.h"

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class Rva00220808
{
public:
	char m_pad[0x64];
	AsciiString m_label;
};

UnicodeString __cdecl GetArmySummaryName(Rva00220808 *src)
{
	UnicodeString tmp;
	if (!((const StringBase<char> *)&src->m_label)->isEmpty())
		tmp.set(TheGameText->fetch(src->m_label));
	return tmp;
}
