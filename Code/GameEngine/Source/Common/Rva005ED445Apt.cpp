// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005ED445@Rva005ED445@@QAEXABVUnicodeString@@@Z, retail 0x005ED445, 103 bytes.
// APT RegionName setter via level and outer name; true bool.
// Evidence: format APT:_level%u.%s_RegionName via 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C; callers 0x005ED8D1 0x005EDB74; precedent Rva005FDF1CApt.cpp Rva005D2FD0Apt.cpp.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva005ED445Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005ED445Outer
{
	Rva005ED445Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005ED445
{
public:
	void rva005ED445(const UnicodeString &text);
	void rva005ED411();
	void rva005ED4AC(int bonusIndex, const UnicodeString &text);
	void rva005ED516(int suffixIndex, const char *suffix, const UnicodeString &text);
	void rva005ED8D1(const UnicodeString &text);
	void rva005ED8FF(int bonusIndex, const UnicodeString &text);
private:
	int m_pad0;
	int m_level;
	Rva005ED445Outer m_outer;
	char m_pad1C[0x28 - 0x0C];
	UnicodeString m_cached;
	UnicodeString m_bonusCache[8];
};

void Rva005ED445::rva005ED445(const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_outer.m_ptr ? m_outer.m_ptr->m_name : "";
	key.format("APT:_level%u.%s_RegionName", m_level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

void Rva005ED445::rva005ED4AC(int bonusIndex, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_outer.m_ptr ? m_outer.m_ptr->m_name : "";
	key.format("APT:_level%u.%s_RegionBonus%d", m_level, mid, bonusIndex);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

void Rva005ED445::rva005ED516(int suffixIndex, const char *suffix, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_outer.m_ptr ? m_outer.m_ptr->m_name : "";
	key.format("APT:_level%u.%s_%s%d", m_level, mid, suffix, suffixIndex);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

void Rva005ED445::rva005ED8FF(int bonusIndex, const UnicodeString &text)
{
	UnicodeString &slot = m_bonusCache[bonusIndex];
	if (((const StringBase<unsigned short> *)(const void *)&text)->compare(*(const StringBase<unsigned short> *)(const void *)&slot) != 0) {
		rva005ED4AC(bonusIndex, text);
		((StringBase<unsigned short> *)(void *)&slot)->set(*(const StringBase<unsigned short> *)(const void *)&text);
	}
}

void Rva005ED445::rva005ED8D1(const UnicodeString &text)
{
	if (((const StringBase<unsigned short> *)(const void *)&text)->compare(*(const StringBase<unsigned short> *)(const void *)&m_cached) != 0) {
		rva005ED445(text);
		((StringBase<unsigned short> *)(void *)&m_cached)->set(*(const StringBase<unsigned short> *)(const void *)&text);
	}
}

class Rva005ED976
{
public:
	void rva005ED976(const UnicodeString &text);
	void rva005ED5EB();
private:
	int m_pad0;
	Rva005ED445 *m_obj;
};

void Rva005ED976::rva005ED976(const UnicodeString &text)
{
	m_obj->rva005ED8D1(text);
}

void Rva005ED976::rva005ED5EB()
{
	m_obj->rva005ED411();
}
