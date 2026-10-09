// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?method@Rva0054CBEFTarget@@QAEXH@Z retail 0x0054CBEF, 8 B, and
// ??1Rva0057417E@@QAE@XZ retail 0x0057417E, 20 B.
// Target evidence: 0x0054CBEF loads the object at +0x04 and tail-jumps to
// 0x0054C99A with the caller's argument (the pin name its callers use; they
// all call it on AptStrategicMessageBox::s_instance, 0x00A05FAC, the name
// the data ledger carries there). 0x0057417E, the pointee destructor of the
// owning-pointer reset 0x0042C1DF, makes that call with 0 when its byte at
// +0x04 is set (no null test, unlike the 0x005CF9FF siblings). The forwarder
// is noinline so the destructor calls it as retail does. The +0x04 object's
// class and the destructor's owner are address-named.
#include "unicode_string.h"

class Rva0057417E;
class Rva00574192;

class AptStrategicMessageBox
{
private:
	static AptStrategicMessageBox *s_instance;	// 0x00A05FAC
	friend class Rva0057417E;
	friend class Rva00574192;
};

class Rva0054C99AImpl
{
public:
	void rva0054C99A(int arg);			// 0x0054C99A
};

class Rva0054CBEFTarget
{
public:
	__declspec(noinline) void method(int arg);

private:
	void *m_00;
	Rva0054C99AImpl *m_impl;			// +0x04
};

void Rva0054CBEFTarget::method(int arg)
{
	m_impl->rva0054C99A(arg);
}

// 0x0054CBF7, 8 B: the same holder's other forwarder, loading the +0x04
// object and tail-jumping to its rowed transition flush 0x0054CA4A. The
// caller 0x0038076D runs it each update on both message-box singletons
// (g_Va00E032FC and AptStrategicMessageBox::s_instance).
class Rva0054CFB8Target
{
public:
	void rva0054CA4A();				// 0x0054CA4A
};

class Rva0054CBF7Target
{
public:
	void method();

private:
	void *m_00;
	Rva0054CFB8Target *m_impl;			// +0x04
};

void Rva0054CBF7Target::method()
{
	m_impl->rva0054CA4A();
}

class Rva0057417E
{
public:
	~Rva0057417E();

private:
	void *m_00;
	bool m_active;					// +0x04
};

Rva0057417E::~Rva0057417E()
{
	if (m_active)
		((Rva0054CBEFTarget *)(void *)AptStrategicMessageBox::s_instance)->method(0);
}

class AptQuitMenu;
extern AptQuitMenu *TheAptQuitMenu;
struct WaitMessageQuitMenuView
{
	unsigned char unknown000[0x278];
	bool transition;
};

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04)
	TEXT_SLOT(05) TEXT_SLOT(06) TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09)
	TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13) TEXT_SLOT(14)
#undef TEXT_SLOT
	virtual UnicodeString fetch(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Rva0054D2DDTarget
{
public:
	void method(int type, const UnicodeString &title, const UnicodeString &text);
};

// Native574192..574251,191B; WB14CE250 names WaitMessage::Update and
// its literal STRATEGICHUD:WaitMessage identifies the same delayed notice.
// Native and the existing57417E destructor prove time0 and visible4;
// the quit-menu byte278 and message-box singleton are independently named
// by their existing owners. Keep the caller-established address-derived
// method name until its class views can be reconciled together.
class Rva00574192
{
public:
	void rva00574192();
private:
	unsigned long started;
	bool visible;
};

void Rva00574192::rva00574192()
{
	if (!visible) {
		if (!TheAptQuitMenu || ((WaitMessageQuitMenuView *)TheAptQuitMenu)->transition) {
			if (timeGetTime() - started >= 200) {
				UnicodeString text = TheGameText->fetch("STRATEGICHUD:WaitMessage", 0);
				{
					UnicodeString title(L" ");
					((Rva0054D2DDTarget *)AptStrategicMessageBox::s_instance)->method(4, title, text);
				}
				visible = true;
			}
		}
	} else if (TheAptQuitMenu && !((WaitMessageQuitMenuView *)TheAptQuitMenu)->transition) {
		((Rva0054CBEFTarget *)AptStrategicMessageBox::s_instance)->method(0);
		visible = false;
	}
}
