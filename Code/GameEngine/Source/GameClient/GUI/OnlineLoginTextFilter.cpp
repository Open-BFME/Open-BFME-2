// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 75fe8bad1b2244e6bc97ae83fbfc96e10d1a302d
// game/GameEngine/Source/GameClient/GUI/OnlineLoginTextFilter.cpp
// (bfmeOnlineLoginTextFilter at BFME 1 retail 0x0054CAA0).
//
// ?rva0056E6FF@@YA_NAAVUnicodeString@@HHH@Z retail 0x0056E6FF..0x0056E79E
// (159 bytes cdecl): trims the text to the maximum length (rowed
// StringBase<unsigned short>::removeLastChar 0x000376E0) / drops a trailing
// character that is not a digit (rowed getCharAt 0x00035760 and isEmpty
// 0x00035740 then the msvcr71 iswdigit import) and accepts the remaining
// non-empty text only when the rowed rva0056E6A4 (the adjacent
// OnlineLoginIntegerRange body) finds its value within 0..maximum; otherwise
// the last character is removed and false returned. The third word is unused.
//
// Target facts: the body / call targets / argument slots and the import come
// from retail. Carried from the donor: the OnlineLogin purpose and the
// filter's statement shape (BFME 2 keeps getCharAt and isEmpty as calls where
// BFME 1 inlined them). No caller was found in retail (no rel32 or absolute
// reference) so the original name stays unproven and the function keeps an
// address-qualified name like its rva0056E6A4 neighbour.
#include <ctype.h>
#include "unicode_string.h"

bool rva0056E6A4(const UnicodeString &text, int minimum, int maximum);

bool rva0056E6FF(UnicodeString &text, int maximumLength, int, int maximum)
{
	while (text.getLength() > maximumLength)
		text.removeLastChar();

	if (text.getLength() > 0)
	{
		unsigned short last = text.getCharAt(text.getLength() - 1);
		if (!text.isEmpty() && !iswdigit(last))
			text.removeLastChar();
	}

	if (text.getLength() > 0)
	{
		if (rva0056E6A4(text, 0, maximum))
			return true;
		text.removeLastChar();
	}
	return false;
}
