// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva004E84ABRun@@YAXXZ @ 0x004E84AB (56B):
// Free guarded text-entry refresh. If g_Va00E04478 (rowed as int 3HA in one
// TU so declared int here to mangle the same and cast to pointer for use)
// and its GameWindow at +0x284 are non-null, call rowed
// GadgetTextEntrySetText(window TheEmptyString) constructing the by-value
// UnicodeString arg directly from TheEmptyString (shared header inline copy
// expands to the rowed StringBase copy ctor).

#include "unicode_string.h"

class GameWindow
{
public:
	char m_pad[1];
};

void __cdecl GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

extern int g_Va00E04478;

void Rva004E84ABRun()
{
	if (g_Va00E04478 == 0)
		return;
	if (*(GameWindow **)((char *)(unsigned int)g_Va00E04478 + 0x284) == 0)
		return;
	GadgetTextEntrySetText(*(GameWindow **)((char *)(unsigned int)g_Va00E04478 + 0x284), UnicodeString::TheEmptyString);
}
