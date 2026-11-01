// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?OnButtonRenameAccept@AptScoreScreen@@QAEXH@Z @0x0051C17E 195B: thiscall update via GadgetTextEntryGetText then wide set plus listbox add with winEnable guards; evidence rowed GadgetTextEntryGetText 0x00320AAB wide set 0x00037150 winEnable 0x00313BEC listbox 0x00326BEC copy 0x00037050 release 0x00036E70 caller 0x0051C4B8 globals g_00DD16C4
#include "unicode_string.h"

#include "../../../../GameEngine/Include/GameClient/Bfme2GameWindow.h"

UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *textEntry);
int __cdecl GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);

// Retail's own word at RVA 0x009D16C4 (.data, file offset 0x0097D2C4): -1. The
// rowed body below passes it to the listbox adder in place of a row index, so
// the missing object was the constant itself. The ledger's 100-byte bound spans
// the pointer array that follows it in .data, which belongs to retail's next
// object.
// Symbol ?g_00DD16C4@@3HA, transcribed below.
extern int g_00DD16C4 = -1;

struct Rva0051C17EInner {
	char _00[0xA0];
	UnicodeString m_name;
};

class AptScoreScreen
{
public:
	void OnButtonRenameAccept(int dummy);
private:
	char _00[0x2A0];
	GameWindow *m_2A0;
	GameWindow *m_2A4;
	Rva0051C17EInner *m_2A8;
	int m_2AC;
};

void AptScoreScreen::OnButtonRenameAccept(int dummy)
{
	(void)dummy;
	if (!m_2A8)
		return;
	UnicodeString newName = GadgetTextEntryGetText(m_2A4);
	UnicodeString &dst = m_2A8->m_name;
	dst.set(newName);
	if (m_2A0) {
		m_2A0->winEnable(true);
		if (m_2AC >= 0)
			GadgetListBoxAddEntryText(m_2A0, newName, g_00DD16C4, m_2AC, 1, true);
	}
	m_2A8 = 0;
	m_2AC = -1;
	if (m_2A0)
		m_2A0->winEnable(true);
}
