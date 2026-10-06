// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00463235@Rva00463235@@QAE?AVAsciiString@@PAVThing@@@Z, retail 0x00463235, 92 bytes.
// Search the passenger-bone list at moduleData+0x48 for the first node whose
// 116-bit KindOf mask (node+0x08) passes Thing::isKindOfMulti against
// g_009FEFA4, or the first node when the filter is null; return that node's
// AsciiString at node+0x24, else AsciiString("ARROW_").
// Evidence: BFME1 donor OpenContain::getPassengerBoneName (OpenContainGetPassengerBoneName.cpp,
// retail 0x002228E0) is the same body with the same list walk; BFME2 lays the
// bone list at module data +0x48 and the name at node+0x24. The by-value
// AsciiString return is the ABI the dead 4-byte return object (push ecx;
// and dword ptr [ebp-4],0) proves; the banked pointer-out form omitted it.
// Callee 0x0030AD7D isKindOfMulti rowed; 0x0037BA0/0x00365F0 StringBase ctors rowed.
#include "ascii_string.h"

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

class Thing
{
public:
	bool isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const;
};

class BfmeFixedStorage0004543D
{
public:
	char m_data[28];
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

struct Rva00463235Node
{
	Rva00463235Node *m_next;
	char m_pad04[4];
	BitFlags<116> m_flags08;
	char m_pad18[12];
	AsciiString m_str24;
};

struct Rva00463235List
{
	char m_pad00[0x48];
	Rva00463235Node *m_head;
};

class Rva00463235
{
public:
	AsciiString rva00463235(Thing *filter);
	char m_pad00[4];
	Rva00463235List *m_list;
};

AsciiString Rva00463235::rva00463235(Thing *filter)
{
	Rva00463235List *list = m_list;
	Rva00463235Node *cur = list->m_head->m_next;
	if (cur == list->m_head)
		return AsciiString("ARROW_");
	for (; cur != list->m_head; cur = cur->m_next) {
		if (filter == 0)
			return cur->m_str24;
		if (filter->isKindOfMulti(cur->m_flags08, (const BitFlags<116> &)g_defaultStorage009FEFA4))
			return cur->m_str24;
	}
	return AsciiString("ARROW_");
}
