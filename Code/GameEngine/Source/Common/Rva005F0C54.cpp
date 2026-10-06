// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005F0C54@Rva005F0C54@@QAEXABVUnicodeString@@@Z @0x005F0C54 109B
// __thiscall method over +4 level +8 Outer +0x40 UnicodeString +0x4C shown flag.
// Compares arg vs member via rowed StringBase compare 0x00006A7A then rowed
// Rva005F066CSet 0x005F066C plus rowed StringBase set 0x00037150 then AptCall
// row 0x005FB5E6 with _show plus SetBuildingNameState plus empty fallback.
// Evidence: 1 caller plus prev/next neighbours plus BuildingName Outer shape.
#include "unicode_string.h"

struct Rva005F066CInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005F066COuter
{
	Rva005F066CInner *m_ptr;
};

void __cdecl Rva005F066CSet(int level, Rva005F066COuter *outer, const UnicodeString &text);

class Rva00222A8BTarget;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

extern const char g_Rva0107301CEmptyString[];
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva005F0C54
{
public:
	void rva005F0C54(const UnicodeString &text);
private:
	char m_pad0[4];
	int m_level;
	Rva005F066COuter m_outer;
	char m_pad1[0x34];
	UnicodeString m_name;
	char m_pad2[8];
	bool m_shown;
};

void Rva005F0C54::rva005F0C54(const UnicodeString &text)
{
	if (text.compare(m_name) != 0) {
		Rva005F066CSet(m_level, &m_outer, text);
		m_name.set(text);
	}
	if (!m_shown) {
		const char *mid = m_outer.m_ptr ? m_outer.m_ptr->m_name : g_Rva0107301CEmptyString;
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, mid, "SetBuildingNameState", "_show");
		m_shown = true;
	}
}

class Rva005F0CC1
{
public:
	void rva005F0CC1(const UnicodeString &text);
private:
	char m_pad0[4];
	Rva005F0C54 *m_obj;
};

void Rva005F0CC1::rva005F0CC1(const UnicodeString &text)
{
	return m_obj->rva005F0C54(text);
}
