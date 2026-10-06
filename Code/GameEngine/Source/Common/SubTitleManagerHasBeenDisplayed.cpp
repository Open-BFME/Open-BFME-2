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

class Rva0022C4DF
{
public:
	UnicodeString rva0022C4DF() const;
};

class Debug
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24();
	virtual void f25(); virtual void f26();
	virtual void *f27(int a, int b, int c);
};

extern Debug *theDebug;

class LogA
{
public:
	virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
	virtual void g4(); virtual void g5(); virtual void g6(); virtual void g7();
	virtual void g8(); virtual void g9(); virtual void g10(); virtual void g11();
	virtual void g12(); virtual void g13();
	virtual void *g14(const char *s);
};

class LogB
{
public:
	virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
	virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7();
	virtual void h8(); virtual void h9(); virtual void h10(); virtual void h11();
	virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
	virtual void h16(); virtual void h17(); virtual void h18();
	virtual void h19(int x);
};

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
	theDebug->f24();
	LogA *a = (LogA *)theDebug->f27(0, 0, 0);
	LogB *b = (LogB *)a->g14("Index out of range in SubTitleManager::HasBeenDisplayed.");
	b->h19(1);
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
	theDebug->f24();
	LogA *a = (LogA *)theDebug->f27(0, 0, 0);
	LogB *b = (LogB *)a->g14("Index out of range in SubTitleManager::SetDisplayedStats().");
	b->h19(1);
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
	theDebug->f24();
	LogA *a = (LogA *)theDebug->f27(0, 0, 0);
	LogB *b = (LogB *)a->g14("Index out of range in SubTitleManager::GetColor().");
	b->h19(1);
	return 0xffff00ff;
}

UnicodeString SubTitleManager::GetText(int index)
{
	if (index < (int)m_list.size())
		return ((Rva0022C4DF *)m_list[index])->rva0022C4DF();
	_bfme_debugRecordCallsite(1);
	theDebug->f24();
	LogA *a = (LogA *)theDebug->f27(0, 0, 0);
	LogB *b = (LogB *)a->g14("Index out of range in SubTitleManager::GetText().");
	b->h19(1);
	return UnicodeString();
}

void SubTitleManager::rva00046A27()
{
	for (int i = 0; i < (int)m_list.size(); ++i)
		m_list[i]->m_displayed = false;
}
