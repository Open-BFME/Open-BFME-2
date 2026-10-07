// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva005B4BDB@Rva005B4BDB@@QAEXXZ retail 0x005B4BDB 97B
// Evidence: chain lane; callee GadgetTextEntryGetText 0x00320AAB plus trim 0x00037F70 plus rva00407A6A 0x00407A6A plus virtual slot 0x14 plus releaseBuffer 0x00036E70; callers 0x005B4CB7 0x005B4D23; EH prolog with handler code 0x0079F347.
#include "unicode_string.h"
template <> bool StringBase<unsigned short>::isEmpty() const throw();
class GameWindow
{
public:
	unsigned int winGetStyle();
};
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
typedef bool Bool;
class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;
void Rva00437E84(int type, const UnicodeString &text, const UnicodeString &title);
class IMEManager
{
public:
	virtual void m00() = 0;
	virtual void m04() = 0;
	virtual void m08() = 0;
	virtual void m0C() = 0;
	virtual void m10() = 0;
	virtual void m14() = 0;
	virtual void m18() = 0;
	virtual void m1C() = 0;
	virtual void m20() = 0;
	virtual void m24() = 0;
	virtual void m28() = 0;
	virtual void m2C() = 0;
	virtual void m30() = 0;
	virtual void m34() = 0;
	virtual void m38() = 0;
	virtual void m3C() = 0;
	virtual void m40() = 0;
};
extern IMEManager *TheIMEManager;
class Rva00407A6A
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void vslot5();
	bool rva00407A6A(const UnicodeString &arg);
private:
	char m_pad04[4];
public:
	UnicodeString m_wide08;
};
class BfmeKeyLC
{
public:
	void *bfmeFindLC();
};
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *k, unsigned short w);
class Rva005B4BDBOuter
{
public:
	char m_pad[0x27c];
	Rva00407A6A m_inner;
};
class Rva005B4BDB
{
public:
	void rva005B4BDB();
	void rva005B4D20();
	void rva005B4C3C();
	void rva005B4AD9(int arg);
private:
	char m_pad0[4];
	Rva005B4BDBOuter *m_outer04;
	GameWindow *m_window08;
	char m_pad0C;
	bool m_flag0D;
};
void Rva005B4BDB::rva005B4BDB()
{
	UnicodeString tmp = GadgetTextEntryGetText(m_window08);
	tmp.trim();
	m_outer04->m_inner.rva00407A6A(tmp);
	m_outer04->m_inner.vslot5();
}
void Rva005B4BDB::rva005B4D20()
{
	rva005B4BDB();
	if (m_flag0D) {
		TheIMEManager->m40();
		m_flag0D = false;
	}
}
void Rva005B4BDB::rva005B4C3C()
{
	if (m_window08 == 0)
		return;
	GadgetTextEntrySetText(m_window08, m_outer04->m_inner.m_wide08);
	GadgetTextEntrySetMaxChars((BfmeKeyLC *)m_window08, 0x16);
}
// ?rva005B4AD9@Rva005B4BDB@@QAEXH@Z retail 0x005B4AD9 258B
// Evidence: REF constant at 0x005B5035 inside FUN_009b4f6f as handler for
// AptCreateAHero Appearance NamePrompt; [ecx+8] GameWindow matches Rva005B4BDB
// layout; GadgetTextEntryGetText 0x00320AAB plus isEmpty 0x00035740 plus
// TheGameText fetch slot 0x3c plus Rva00437E84 0x00437E84 plus releaseBuffer
// 0x00036E70; strings APT:EnterNameErrorTitle APT:EnterNameError
// LAN:ErrorDuplicateName.
void Rva005B4BDB::rva005B4AD9(int arg)
{
	bool empty = (m_window08 == 0) || GadgetTextEntryGetText(m_window08).isEmpty();
	if (empty) {
		Rva00437E84(0, TheGameText->fetch("APT:EnterNameErrorTitle"), TheGameText->fetch("APT:EnterNameError"));
	} else {
		Rva00437E84(0, TheGameText->fetch("APT:EnterNameErrorTitle"), TheGameText->fetch("LAN:ErrorDuplicateName"));
	}
}
