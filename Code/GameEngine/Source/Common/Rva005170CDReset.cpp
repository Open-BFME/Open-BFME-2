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
	char m_data[0x18];
	void rva00516F3F();
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
class GameSpyInfoInterface
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
	virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
	virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
	virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
	virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
	virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
	virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67();
	virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
	virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75();
	virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
	virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83();
	virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
	virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91();
	virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
	virtual void d96();
	virtual bool unk184();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class GameTextInterface
{
public:
	virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
	virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
	virtual void e08(); virtual void e09(); virtual void e10(); virtual void e11();
	virtual void e12(); virtual void e13(); virtual void e14();
	virtual UnicodeString fetch(const char *key, int unk);
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
	if (TheGameSpyInfo->unk184())
		return;
	Rva00516E92Enable();
	Rva00437E84(0, TheGameText->fetch("GUI:GSErrorTitle", 0), TheGameText->fetch("GUI:GSDisconReason3", 0));
}
