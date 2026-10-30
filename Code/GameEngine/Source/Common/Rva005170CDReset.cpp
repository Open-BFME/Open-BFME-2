// ?rva005170CD@Rva005170CD@@QAEXXZ @0x005170CD 36B
// cl: /Ireference/shims/bfme2_ascii /MD
// Unlock reset: conditional Rva00437E9C(0) plus clear trailing flag plus tail jmp to rva00516F3F. Evidence: callees 0x00437E9C pin-only 0x00516F3F rowed; offsets 0x298 0x2B0; callers 0x005A3652 0x005A640F 0x005A652D unclaimed; prev 0x00517048 next 0x0051719B.
#include "ascii_string.h"
#include "unicode_string.h"

void __cdecl Rva00437E9C(int value);
void __cdecl Rva00516E92Enable();
void __cdecl Rva00437E84(int type, const UnicodeString &text, const UnicodeString &title);

struct Rva00516F3F
{
	int m_0;
	int m_4;
	int m_8;
	AsciiString m_C;
	AsciiString m_10;
	int m_14;
	void rva00516F3F();
	Rva00516F3F *rva00516F63(const Rva00516F3F &other);
};

struct Rva005170CDInner
{
	Rva00516F3F base;
	int m_18;
};

class Rva005170CD
{
public:
	void rva005170CD();
	void rva005170F1();
private:
	char m_pad0[0x298];
	Rva005170CDInner m_inner;
	char m_pad1[4];
	bool m_2B8;
};

void Rva005170CD::rva005170CD()
{
	if (m_inner.m_18 != 0)
		Rva00437E9C(0);
	Rva005170CDInner *q = &m_inner;
	q->m_18 = 0;
	return q->base.rva00516F3F();
}

// ?rva005170F1@Rva005170CD@@QAEXXZ, retail 0x005170F1, 170 bytes.
// Disconnect error path: gated by TheGameSpyInfo plus two flags plus GameSpy
// slot 0x184, then GameText fetches plus Rva00437E84 plus wide releaseBuffer.
// Evidence: strings GUI:GSDisconReason3 GUI:GSErrorTitle; callees 0x00516E92
// 0x00437E84 0x36E70; externs TheGameSpyInfo TheGameText; caller 0x00518214;
// prev 0x005170CD next 0x0051719B contiguous; __thiscall ret.
class PSPlayerAllStats;

class GameSpyInfoInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual int getLocalProfileID();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void setCachedStats(PSPlayerAllStats stats);
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual bool slot97();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

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
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void Rva005170CD::rva005170F1()
{
	if (TheGameSpyInfo == 0)
		return;
	if (!m_2B8)
		return;
	if (!m_pad0[0x27C])
		return;
	m_2B8 = false;
	if (TheGameSpyInfo->slot97())
		return;
	Rva00516E92Enable();
	Rva00437E84(0, TheGameText->fetch("GUI:GSErrorTitle", 0), TheGameText->fetch("GUI:GSDisconReason3", 0));
}
