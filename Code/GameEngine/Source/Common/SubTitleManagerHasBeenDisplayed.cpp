// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?HasBeenDisplayed@SubTitleManager@@QAE_NH@Z retail 0x000468AD 89B.
// Bounds-checked read of the displayed flag at record+0x20 via the pointer
// vector at +0x14: returns the flag when index is in range, else records the
// callsite via rowed _bfme_debugRecordCallsite, logs
// "Index out of range in SubTitleManager::HasBeenDisplayed." through theDebug
// virtuals and returns false. Evidence: string literal plus caller 0x0004807C
// plus neighbour record TUs.
#include <vector>
#include "unicode_string.h"

void __cdecl _bfme_debugRecordCallsite(int x);

#include "../../Include/GameNetwork/Rva0022C4DF.h"

#include "debug.h"

struct SubTitleEntry
{
	char m_pad0[8];
	unsigned int m_color;
	char m_pad1[0x20 - 0x0c];
	bool m_displayed;
};

class SubTitleManager
{
public:
	bool HasBeenDisplayed(int index);
	void SetDisplayedStats(int index);
	unsigned int GetColor(int index);
	UnicodeString GetText(int index);
	void rva00046A27();
private:
	char m_pad[0x14];
	_STL::vector<SubTitleEntry *> m_list;
};

bool SubTitleManager::HasBeenDisplayed(int index)
{
	if (index < (int)m_list.size())
		return m_list[index]->m_displayed;
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::HasBeenDisplayed.").CrashDone(1);
	return false;
}

// ?SetDisplayedStats@SubTitleManager@@QAEXH@Z retail 0x00046973 88B.
// Bounds-checked set of the displayed flag at record+0x20 via the pointer
// vector at +0x14: sets the flag when index is in range, else records the
// callsite and logs "Index out of range in
// SubTitleManager::SetDisplayedStats()." through theDebug virtuals.
// Evidence: string literal plus caller 0x000480D2 plus sibling HasBeenDisplayed.
void SubTitleManager::SetDisplayedStats(int index)
{
	if (index < (int)m_list.size()) {
		m_list[index]->m_displayed = true;
		return;
	}
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::SetDisplayedStats().").CrashDone(1);
}

// ?GetColor@SubTitleManager@@QAEIH@Z retail 0x000469CB 92B.
// Bounds-checked read of the color at record+8 via the pointer vector at
// +0x14: returns the color when index is in range, else records the callsite
// and logs "Index out of range in SubTitleManager::GetColor()." through
// theDebug virtuals and returns 0xffff00ff. Evidence: string literal plus
// caller 0x000480AB plus siblings HasBeenDisplayed/SetDisplayedStats.
unsigned int SubTitleManager::GetColor(int index)
{
	if (index < (int)m_list.size())
		return m_list[index]->m_color;
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::GetColor().").CrashDone(1);
	return 0xffff00ff;
}

UnicodeString SubTitleManager::GetText(int index)
{
	if (index < (int)m_list.size())
		return ((Rva0022C4DF *)m_list[index])->rva0022C4DF();
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::GetText().").CrashDone(1);
	return UnicodeString();
}

void SubTitleManager::rva00046A27()
{
	for (int i = 0; i < (int)m_list.size(); ++i)
		m_list[i]->m_displayed = false;
}
