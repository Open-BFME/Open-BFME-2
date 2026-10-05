// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Hero power panel texts. Each builds a UnicodeString through an unrowed
// formatter and hands it to the rowed bfmeSetText. Both formatters
// (0x005B2376, 0x005B2446) return a UnicodeString by value through a hidden
// pointer and are pinned from these REL32 call sites.
//
// ?Rva005B23D7HeroPowersDescription@@YAXPAXHABVAsciiString@@@Z @0x005B23D7 111B
//   APT:HeroPowersDescription with the description text
// ?Rva005B24CDHeroPowerText@@YAXPAXPBDH@Z                      @0x005B24CD 114B
//   APT:%s_%d keyed by the prefix and the 1-based index
// Names are address-derived; the keys are the retail strings.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

UnicodeString __cdecl Rva005B2376Describe(void *power, int unused, const AsciiString &fallback);
UnicodeString __cdecl Rva005B2446Describe(void *power);

void __cdecl Rva005B23D7HeroPowersDescription(void *power, int unused, const AsciiString &fallback)
{
	UnicodeString text = Rva005B2376Describe(power, unused, fallback);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(AsciiString("APT:HeroPowersDescription"), text, true);
}

void __cdecl Rva005B24CDHeroPowerText(void *power, const char *prefix, int index)
{
	AsciiString key;
	key.format("APT:%s_%d", prefix, index + 1);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005B2446Describe(power), false);
}

// ?rva005B9378@Rva005B9378@@QAEXHABVUnicodeString@@@Z @0x005B9378 178B: one
// ticker row. The field text is the game-text label for the row's entry in
// the label table at VA 0x00DD3B90, fetched through TheGameText's
// fetch(const char *, bool *) (slot 0x3C), with L":" appended. It is set under
// APT:TickerField_%d, then the caller's value under APT:TickerValue_%d. Callers
// (0x005B945D and four more) pass this in ecx, which the body never reads.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
extern const char *g_00DD3B90[];

class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
};

void Rva005B9378::rva005B9378(int index, const UnicodeString &value)
{
	AsciiString key;
	key.format("APT:TickerField_%d", index);
	UnicodeString field = TheGameText->fetch(g_00DD3B90[index], 0);
	field.concat(L":");
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, field, false);
	key.format("APT:TickerValue_%d", index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
}

// ?rva00513497@Rva00513497@@QAEXHVUnicodeString@@@Z @0x00513497 193B: the
// disconnect screen's player name. It is set under
// DisconnectScreen::PlayerName%d, or L" " when the name is null or empty
// (inline length test at +4). The slot then goes through the rowed bar update
// 0x00513040 with 0 or, for a real name, the rowed 0x00512CE9 (false) and the
// bar update with 100. Both helpers are rowed as methods of their own
// address-named views of this same object.
class Rva00512CE9
{
public:
	void rva00512CE9(int slot, bool b);
};

class Rva00513040
{
public:
	void rva00513040(int v1, int v2);
};

// StringBase<unsigned short>::isEmpty, inline here as retail expands it.
static inline bool Rva00513497IsEmpty(const UnicodeString &s)
{
	const char *data = *(const char *const *)&s;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class Rva00513497
{
public:
	void rva00513497(int slot, UnicodeString name);
};

void Rva00513497::rva00513497(int slot, UnicodeString name)
{
	AsciiString key;
	key.format("DisconnectScreen::PlayerName%d", slot);
	if (Rva00513497IsEmpty(name))
	{
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, UnicodeString(L" "), false);
		((Rva00513040 *)this)->rva00513040(slot, 0);
	}
	else
	{
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, name, false);
		((Rva00512CE9 *)this)->rva00512CE9(slot, false);
		((Rva00513040 *)this)->rva00513040(slot, 100);
	}
}
