// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva005AFD89@Rva005AFE86@@UAEXHPBURva005AFD89Param@@@Z, retail 0x005AFD89, 60 bytes.
// Slot 0 of vtable 0x008728B8 (Rva005AFE86 ctor TU): checks id vs +4 and
// listbox +0xC non-null then GadgetListBoxAddEntryText via rowed 0x00326BEC
// with text+color from second param struct, row -1 column -1 overwrite true.
// Evidence: vtable slot 0 refs; callees rowed copyCtor 0x00037050 and
// 0x00326BEC; neighbours Rva005AFE86Ctor // cl /O1 /MD /EHsc.
#include "unicode_string.h"

class GameWindow;
int __cdecl GadgetListBoxAddEntryText(class GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);

struct Rva005AFD89Param
{
	UnicodeString text;
	int color;
};

class Rva005AFE86
{
public:
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p);
private:
	void *m_04;
	int m_08;
	GameWindow *m_0C;
};

void Rva005AFE86::rva005AFD89(int id, const Rva005AFD89Param *p)
{
	if (id != (int)m_04) {
		return;
	}
	if (m_0C == 0) {
		return;
	}
	GadgetListBoxAddEntryText(m_0C, p->text, p->color, -1, -1, true);
}
