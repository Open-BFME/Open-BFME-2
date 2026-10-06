// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0051C17E@Rva0051C17E@@QAEXH@Z @0x0051C17E 195B: thiscall update via GadgetTextEntryGetText then wide set plus listbox add with winEnable guards; evidence rowed GadgetTextEntryGetText 0x00320AAB wide set 0x00037150 winEnable 0x00313BEC listbox 0x00326BEC copy 0x00037050 release 0x00036E70 caller 0x0051C4B8 globals g_00DD16C4
#include "unicode_string.h"

class GameWindow {
public:
	int winEnable(bool enable);
};

UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *textEntry);
int __cdecl GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);

extern int g_00DD16C4;

struct Rva0051C17EInner {
	char _00[0xA0];
	UnicodeString m_A0;
};

class Rva0051C17E {
public:
	void rva0051C17E(int dummy);
private:
	char _00[0x2A0];
	GameWindow *m_2A0;
	GameWindow *m_2A4;
	Rva0051C17EInner *m_2A8;
	int m_2AC;
};

void Rva0051C17E::rva0051C17E(int dummy)
{
	(void)dummy;
	if (!m_2A8)
		return;
	UnicodeString tmp = GadgetTextEntryGetText(m_2A4);
	UnicodeString &dst = m_2A8->m_A0;
	dst.set(tmp);
	if (m_2A0) {
		m_2A0->winEnable(true);
		if (m_2AC >= 0)
			GadgetListBoxAddEntryText(m_2A0, tmp, g_00DD16C4, m_2AC, 1, true);
	}
	m_2A8 = 0;
	m_2AC = -1;
	if (m_2A0)
		m_2A0->winEnable(true);
}
