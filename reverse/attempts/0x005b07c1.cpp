// ?rva005B07C1@Manager@AptCreateAHero@@QAEXHHH@Z
// partial score=0.72 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii -Oy- -GR- -EHsc-
// ?InitGadgets@Manager@AptCreateAHero@@QAEXPADH0@Z @0x005B6967 158B: two-path validated set.
// Unless the third arg is null, strcmp it (imported) against two runtime
// tables; a first-table miss fills a 3-int buffer (9/0x2E/0x2D) for the
// pinned 3-arg callee, stamps +0x8 and runs the pinned helper, while a
// second-table miss fills (0x50/0x14) for the same callee plus the pinned
// 1-arg callee, stamps +0xC and runs the pinned tail body. The middle arg
// is unused. Targets from retail REL32; strcmp via plain C decl reusing
// the existing thunk pin; tables as named externs.
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *a, const char *b);
extern char g_rva005B6967T0[];
extern char g_rva005B6967T1[];

class Rva00407E28
{
public:
	int rva00407E28(int key);
	bool rva00407E53(int key);
	bool rva00407DE0(int key, int value);
private:
	char m_pad[0x14];
	char m_map1[12];
	char m_map2[12];
	char m_pad2[0x38 - 0x14 - 12 - 12];
	int m_flags;
};

class Rva00222A8BTarget
{
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

typedef bool Rva005B07C1Bool;
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
	virtual UnicodeString fetch(const AsciiString &label, Rva005B07C1Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class CreateAHeroHero;
class CreateAHeroManager
{
public:
	const AsciiString &GetBlingNameTag(int blingKey, const CreateAHeroHero *hero, unsigned int value);
};
extern CreateAHeroManager *TheCreateAHeroManager;

struct Rva005B07C1Entry
{
	int key;
	int unk4;
	int minimum;
	int maximum;
	int unk10;
};

struct Rva005B07C1Vector
{
	Rva005B07C1Entry *first;
	Rva005B07C1Entry *last;
	Rva005B07C1Entry *end;
};

struct Rva005B6967Buf
{
	int x;
	int y;
	int z;
};

namespace AptCreateAHero {
class Manager;
}

class AptCreateAHero::Manager
{
public:
	char pad[8];
	char *m_8;
	char *m_C;

	void rva005B6755();
	void rva005B5F2E();
	void InitGadgets(char *a, int unused, char *c);
	void rva005B07C1(int mode, int index, int value);
};

void Rva005B6967F(char *s, int n, int *p);
void Rva005B6967G(char *s);

void AptCreateAHero::Manager::InitGadgets(char *a, int unused, char *c)
{
	if (c == 0)
		return;
	Rva005B6967Buf buf;
	if (strcmp(a, g_rva005B6967T0) == 0) {
		buf.x = 9;
		buf.y = 0x2e;
		buf.z = 0x2d;
		Rva005B6967F(c, 3, &buf.x);
		m_8 = c;
		rva005B6755();
	} else {
		if (strcmp(a, g_rva005B6967T1) != 0)
			return;
		buf.y = 0x50;
		buf.z = 0x14;
		Rva005B6967F(c, 2, &buf.y);
		Rva005B6967G(c);
		m_C = c;
		rva005B5F2E();
	}
}

// ?rva005B07C1@Manager@AptCreateAHero@@QAEXHHH@Z @0x005B07C1 354B.
// Target evidence: three-int thiscall, two 20-byte vectors at +0x174/+0x180,
// per-row signed bounds at +8/+0xC, two map calls on the manager prefix, the
// selected-attribute and point-label strings, and calls to the rowed map,
// string-format, game-text and name-tag methods plus pinned bfmeSetText.
// Identity/layout inference: neighboring manager methods and the constructor
// at 0x005B12C5 support AptCreateAHero::Manager; GetBlingNameTag receives this
// as its hero argument, but that conversion does not establish inheritance.
void AptCreateAHero::Manager::rva005B07C1(int mode, int index, int value)
{
	Rva005B07C1Vector *rows = (Rva005B07C1Vector *)((char *)this + (mode + 31) * 12);
	if ((unsigned int)index >= (unsigned int)(rows->last - rows->first))
		return;
	Rva005B07C1Entry *entry = rows->first + index;
	int oldValue = ((Rva00407E28 *)this)->rva00407E28(entry->key);
	if (value < entry->minimum || value > entry->maximum)
		return;
	if (mode == 1) {
		AsciiString key;
		key.format("APT:MyHeroAppearanceVal_%d", index);
		const AsciiString &name = TheCreateAHeroManager->GetBlingNameTag(entry->key, (const CreateAHeroHero *)this, (unsigned int)value);
		UnicodeString text = TheGameText->fetch(name, (Rva005B07C1Bool *)0);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
	} else if (mode == 0) {
		int points = *(int *)((char *)this + 0x154) + oldValue - value;
		if (points < 0 || points > *(int *)((char *)this + 0x158))
			return;
		*(int *)((char *)this + 0x154) = points;
		UnicodeString text;
		text.format((const unsigned short *)L"%d", points);
		AsciiString key("APT:MyHeroAttribPoints");
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
	}
	((Rva00407E28 *)this)->rva00407DE0(entry->key, value);
}
