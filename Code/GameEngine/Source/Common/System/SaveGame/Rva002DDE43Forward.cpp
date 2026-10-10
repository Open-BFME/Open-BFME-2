// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Oy- /Os
// ?rva002DDE43@GameState@@QAEXABVUnicodeString@@0HH@Z @0x002DDE43 43B
// Leaf forwarding to GameState::saveGame (pinned 0x002DD38D) with its last argument
// zero. The wrapper's fourth argument reaches the saveGame bool slot as the raw
// stack dword (a bool view of the int parameter; no setne normalisation), which the
// size-optimised build keeps as direct memory pushes. Evidence: callers 0x002408F5
// and 0x00435A6F (the latter passes 0 and 1), callees StringBase wide copy and the
// saveGame pin 0x002DD38D; address-derived wrapper name.
// Retail's out-of-line UnicodeString copy is frameless; this TU builds /Oy-
// (frame pointers), which gives the COMDAT an ebp frame and loses the link.
// Compile the UnicodeString inline definitions with frame omission so our
// copy matches the kept retail one.
#pragma optimize("y", on)
#include "unicode_string.h"
#pragma optimize("", on)

class GameState
{
public:
	int saveGame(UnicodeString name, const UnicodeString &text, int save, bool showMessage, int param5);
	void rva002DDE43(const UnicodeString &name, const UnicodeString &text, int save, int confirm);
};

void GameState::rva002DDE43(const UnicodeString &name, const UnicodeString &text, int save, int confirm)
{
	saveGame(name, text, save, *(bool *)&confirm, 0);
}
