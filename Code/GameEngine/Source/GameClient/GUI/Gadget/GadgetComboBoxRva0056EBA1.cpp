// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0056EBA1@Rva0056EBA1@@QAE_NABVUnicodeString@@@Z @0x0056EBA1 47B.
// Chain of just-landed GadgetComboBoxSetText 0x322D63: null member +0xA4 guard
// then SetText with text copy. Retail calls 0x00037050 StringBase copy then
// 0x00322D63 SetText; no callers; honest thiscall wrapper returning Bool.
typedef unsigned short wchar_t;
typedef int Int;

#ifndef NULL
#define NULL 0
#endif

#include "unicode_string.h"


class GameWindow;

void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

class Rva0056EBA1
{
public:
	bool rva0056EBA1(const UnicodeString &text);
	UnicodeString rva0056EB15();
private:
	unsigned char m_pad[0xA4];
	GameWindow *m_combo;
};

bool Rva0056EBA1::rva0056EBA1(const UnicodeString &text)
{
	bool ok = false;
	if (m_combo != NULL)
	{
		GadgetComboBoxSetText(m_combo, text);
		ok = true;
	}
	return ok;
}

UnicodeString Rva0056EBA1::rva0056EB15()
{
	UnicodeString tmp = UnicodeString::TheEmptyString;
	if (m_combo != NULL) {
		tmp = GadgetComboBoxGetText(m_combo);
		tmp.trim();
	}
	return tmp;
}

// ?rva0056EA91@Rva0056EA91@@QAE?AVUnicodeString@@XZ retail 0x0056EA91 132B
// Evidence: empty 0x00A0C898 via StringBase copy 0x00037050; GadgetComboBoxGetText 0x00322D21 then set 0x00037150 and release 0x00036E70; combo at +0xA8; callers 0x0056F4AB 0x00570250; sibling GadgetComboBoxRva0056EBA1
class Rva0056EA91
{
public:
	UnicodeString rva0056EA91();
private:
	unsigned char m_pad[0xA8];
	GameWindow *m_combo;
};

UnicodeString Rva0056EA91::rva0056EA91()
{
	UnicodeString tmp = UnicodeString::TheEmptyString;
	if (m_combo != NULL) {
		tmp = GadgetComboBoxGetText(m_combo);
	}
	return tmp;
}

// ?rva0056EBD0@Rva0056EBD0@@QAE?AVUnicodeString@@XZ retail 0x0056EBD0 132B
// Evidence: empty 0x00A0C898 via 0x00037050; GadgetTextEntryGetText 0x00320AAB then set 0x00037150 release 0x00036E70; combo at +0xAC; sibling 0x0056EA91
class Rva0056EBD0
{
public:
	UnicodeString rva0056EBD0();
private:
	unsigned char m_pad[0xAC];
	GameWindow *m_combo;
};

UnicodeString Rva0056EBD0::rva0056EBD0()
{
	UnicodeString tmp = UnicodeString::TheEmptyString;
	if (m_combo != NULL) {
		tmp = GadgetTextEntryGetText(m_combo);
	}
	return tmp;
}
