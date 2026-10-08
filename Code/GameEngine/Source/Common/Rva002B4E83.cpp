// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002B4E83@Rva002B4E83@@QAEXPAVRva002E0687@@@Z @0x002B4E83 233B.
// Unlock lane; defeat message: if selection locked and local player use GUI:YouHaveBeenDefeated else GUI:PlayerHasBeenDefeated formatted with player name at +0x1c+8 or the empty wide literal, then InGameUI message at 0x4C plus rva0029B16A(&msg 8).
// Callees rowed isSelectionLocked 0x4253A rva002E0687 0x2E0687 set 0x37150 releaseBuffer 0x36E70 format 0x6CB660 copyCtor 0x37050 rva0029B16A 0x29B16A; TheGameText fetch slot 0x3C TheInGameUI VA 0xDFEDF0 empty wide literal VA 0xBBB5C4.
#include "unicode_string.h"

typedef unsigned short WideChar;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

class Rva002E0687
{
public:
	bool rva002E0687() const;
private:
	char m_pad[0x1c];
public:
	void *m_1c;
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void __cdecl message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;

class Rva0029B16A
{
public:
	void rva0029B16A(int a, int b);
};


class Rva002B4E83
{
public:
	void rva002B4E83(Rva002E0687 *p);
};

void Rva002B4E83::rva002B4E83(Rva002E0687 *p)
{
	if (!((BfmeSelectionState *)this)->isSelectionLocked())
		return;
	UnicodeString msg;
	if (p->rva002E0687())
		msg = TheGameText->fetch("GUI:YouHaveBeenDefeated");
	else
	{
		msg = TheGameText->fetch("GUI:PlayerHasBeenDefeated");
		const WideChar *name = (p->m_1c != 0) ? (const WideChar *)((char *)p->m_1c + 8) : (const WideChar *)L"";
		msg.format(&msg, name);
	}
	TheInGameUI->message(msg);
	((Rva0029B16A *)TheInGameUI)->rva0029B16A((int)&msg, 8);
}
