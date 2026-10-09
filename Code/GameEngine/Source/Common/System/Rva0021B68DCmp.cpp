// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// Retail 0x0021B68D (198 bytes): the out-of-line comparator the rowed STLport
// sort family in stlport_sort_rva0021b68d.cpp calls (pinned there from its
// REL32s). Each key is looked up through 0x0040AAF8 (pinned) on the global at
// VA 0x00E02F74; a key that finds nothing sorts last. Entries order by the
// strings at +0x5C, then +0x60 (case-insensitive; a greater one ends the
// test), then by TheGameText's translation of the label at +0x54. The two
// translations are temporaries bound to references, so MSVC packs them into
// the dead argument slots as retail does, and the second has no EH state of
// its own because StringBase::compareNoCase is declared throw().
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

enum Rva0021B68DKey
{
	RVA0021B68D_KEY_INVALID = -1
};

struct Rva0021B68DCmp
{
	bool operator()(const Rva0021B68DKey &a, const Rva0021B68DKey &b) const;
};

class Rva0040AAD5;
extern Rva0040AAD5 *g_00E02F74;

class Rva0040BAD0
{
public:
	Int rva0040AAF8(Int key);
};

struct Rva0021B68DEntry
{
	unsigned char m_pad00[0x54];
	AsciiString m_label;		// +0x54
	unsigned char m_pad58[0x5c - 0x58];
	AsciiString m_first;		// +0x5C
	AsciiString m_second;		// +0x60
};

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
	virtual void reset() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

bool Rva0021B68DCmp::operator()(const Rva0021B68DKey &a, const Rva0021B68DKey &b) const
{
	const Rva0021B68DEntry *entryA = (const Rva0021B68DEntry *)((Rva0040BAD0 *)g_00E02F74)->rva0040AAF8(a);
	const Rva0021B68DEntry *entryB = (const Rva0021B68DEntry *)((Rva0040BAD0 *)g_00E02F74)->rva0040AAF8(b);
	if (entryA == 0)
		return false;
	if (entryB == 0)
		return true;
	if (entryA->m_first.compareNoCase(entryB->m_first) <= 0 && entryA->m_second.compareNoCase(entryB->m_second) <= 0) {
		const UnicodeString &textA = TheGameText->fetch(entryA->m_label);
		const UnicodeString &textB = TheGameText->fetch(entryB->m_label);
		return textA.compareNoCase(textB) < 0;
	}
	return false;
}
