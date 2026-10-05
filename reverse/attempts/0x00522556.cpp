// ?rva00522556@Rva00522556@@QAEXXZ
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva00522556@Rva00522556@@QAEXXZ, retail 0x00522556, 277 bytes. Leaf GUI
// list fill; callers unclaimed x4; callees rowed (GadgetListBoxReset 0x3247E5,
// SkirmishPreferences::getUserNames 0x43C2D0, StringBase set/copy/compare/
// release, GadgetListBoxAddEntryText 0x326BEC, Rva0043B9F5 0x43B9F5,
// Rva0043DB23 0x43DB23, GadgetListBoxSetSelected 0x324798, list_base dtor
// 0x433BD7); string literal PopupSelectBttnDisable; global
// TheRva00222A8BTarget; vtables none (free function shape with ecx use).
#include "unicode_string.h"
#include <list>

class GameWindow;
class Rva00222A8BTarget;
class SkirmishPreferences;

extern Rva00222A8BTarget *TheRva00222A8BTarget;

void __cdecl GadgetListBoxReset(GameWindow *win);
int __cdecl GadgetListBoxAddEntryText(GameWindow *win, UnicodeString text, int a, int b, int c, bool d);
void __cdecl GadgetListBoxSetSelected(GameWindow *win, int idx);
void __cdecl Rva0043DB23(Rva00222A8BTarget *target, void *a, const char *name);

class SkirmishPreferences
{
public:
	_STL::list<UnicodeString> getUserNames_Rva0043C2D0();
	UnicodeString Rva0043B9F5();
};

class Rva00522556
{
public:
	void rva00522556();
private:
	char m_000[0x274];
	void *m_274;
	char m_278[0x6C4 - 0x278];
	GameWindow *m_6C4;
};

// ?rva00522556@Rva00522556@@QAEXXZ present-unmatched
void Rva00522556::rva00522556()
{
	if (m_6C4 == 0)
		return;
	GadgetListBoxReset(m_6C4);
	_STL::list<UnicodeString> names = ((SkirmishPreferences *)((char *)this + 0x698))->getUserNames_Rva0043C2D0();
	UnicodeString cur;
	int idx = 0;
	int sel = 0;
	_STL::list<UnicodeString>::iterator it = names.begin();
	if (it == names.end())
		goto doDisable;
	do
	{
		cur.set(*it);
		GadgetListBoxAddEntryText(m_6C4, cur, -1, -1, -1, true);
		if (cur.compareNoCase(((SkirmishPreferences *)((char *)this + 0x698))->Rva0043B9F5()) == 0)
			sel = idx;
		++it;
		++idx;
	} while (it != names.end());
	if (idx != 0)
		goto doSet;
doDisable:
	Rva0043DB23(TheRva00222A8BTarget, m_274, "PopupSelectBttnDisable");
doSet:
	GadgetListBoxSetSelected(m_6C4, sel);
}
