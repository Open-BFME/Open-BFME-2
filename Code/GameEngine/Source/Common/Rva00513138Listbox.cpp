// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00513138@Rva00513138@@QAEXVUnicodeString@@@Z @0x00513138 86B: listbox wrapper passing this+0x27c with incoming UnicodeString by value plus global color plus -1 -1 true.
// Evidence: rowed StringBase<G> copy 0x00037050 plus GadgetListBoxAddEntryText 0x00326BEC plus releaseBuffer 0x00036E70 with EH_prolog handler 0x00794F68; caller 0x004D10D0; neighbours 0x00512CE9 0x00513813.
// Private wide StringBase/UnicodeString copied from GadgetListBoxAddEntryText.cpp to inline copy/dtor to the rowed workers.

#include "unicode_string.h"


class GameWindow;
extern int g_00DD1488;
// g_00DD1488: matched references place it at VA 0xdd1488 (retail .data initial value -65536).
int g_00DD1488 = -65536;
int GadgetListBoxAddEntryText(class GameWindow *listbox, class UnicodeString text, int color, int row, int column, bool overwrite);

class Rva00513138
{
public:
	void rva00513138(class UnicodeString text);
private:
	char m_pad00[0x27C];
	class GameWindow *m_listbox;
};

void Rva00513138::rva00513138(class UnicodeString text)
{
	GadgetListBoxAddEntryText(m_listbox, text, g_00DD1488, -1, -1, true);
}
