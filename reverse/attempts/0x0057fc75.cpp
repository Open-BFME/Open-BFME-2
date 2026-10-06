// ?rva0057FC75@Rva0057F2DE@@QAE_NIII@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0057FC75@Rva0057F2DE@@QAE_NIII@Z @0x0057FC75 234B: MpGameSetup +0x190 clan panel message handler dispatching 0x4015 list selection and 0x4026 combo text via rowed Gadget helpers plus just-landed AptMpClans 0x0057FA1C.
// Evidence: calls 0x0057FA1C row plus rowed GadgetComboBoxGetText 0x00322D21 GadgetListBoxGetSelected 0x00324773 GadgetListBoxGetText 0x00327074 plus wide copy ctor 0x00037050 plus releaseBuffer 0x00036E70 plus caller 0x00442D30 plus prev 0x0057FA1C same +0xA0 +0xA4 +0xA8.
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow;

UnicodeString __cdecl GadgetComboBoxGetText(GameWindow *comboBox);
void __cdecl GadgetListBoxGetSelected(GameWindow *listBox, int *sel);
UnicodeString __cdecl GadgetListBoxGetText(GameWindow *listBox, int index, int flag);

class AptMpClans
{
public:
	void rva0057FA1C(UnicodeString name);
};

class Rva0057F2DE
{
public:
	bool rva0057FC75(unsigned int msg, unsigned int data1, unsigned int data2);

private:
	unsigned char m_pad000[0xA0];
	GameWindow *m_clanName;
	GameWindow *m_clanPlayers;
	unsigned char m_flagA8;
	unsigned char m_padA9[0xAC - 0xA9];
	AsciiString m_clan;
};

// ?rva0057FC75@Rva0057F2DE@@QAE_NIII@Z present-unmatched
bool Rva0057F2DE::rva0057FC75(unsigned int msg, unsigned int data1, unsigned int data2)
{
	GameWindow *window = (GameWindow *)data1;
	(void)data2;
	if (!m_flagA8)
		return false;
	switch (msg)
	{
	case 0x4015:
		if (window == m_clanPlayers)
		{
			int sel = 0;
			GadgetListBoxGetSelected(window, &sel);
			if (sel < 0)
				return true;
			UnicodeString item = GadgetListBoxGetText(window, sel, 1);
			((AptMpClans *)this)->rva0057FA1C(item);
			return true;
		}
		break;
	case 0x4026:
		if (window == m_clanName)
		{
			UnicodeString combo = GadgetComboBoxGetText(window);
			((AptMpClans *)this)->rva0057FA1C(combo);
			return true;
		}
		return window == m_clanPlayers;
	}
	if (window == m_clanName)
		return true;
	return window == m_clanPlayers;
}
