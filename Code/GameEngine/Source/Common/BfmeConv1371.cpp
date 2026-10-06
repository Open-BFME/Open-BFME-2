// Open-BFME5 conversions, BFME2 repair: the three string members copy
// through StringBase<char>::set at 0x366F0 (retail's inlined AsciiString
// assignment target, shared with Rva000C3380Copy); the donor's local
// BfmeUniVIA::bfmeSetVIA label names the same bytes.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


struct BfmeElemVIA
{
	AsciiString m_bfme00;
	AsciiString m_bfme04;
	AsciiString m_bfme08;
	char m_bfme0c;
	char m_bfmePad0d[3];
	int m_bfme10;
	char m_bfme14;
	char m_bfmePad15[3];
	int m_bfme18;
};

BfmeElemVIA *__cdecl bfmeCopyVIA(BfmeElemVIA *first, BfmeElemVIA *last, BfmeElemVIA *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int i = n;
		do
		{
			((StringBase<char> *)&dest->m_bfme00)->set(*(const StringBase<char> *)&first->m_bfme00);
			((StringBase<char> *)&dest->m_bfme04)->set(*(const StringBase<char> *)&first->m_bfme04);
			((StringBase<char> *)&dest->m_bfme08)->set(*(const StringBase<char> *)&first->m_bfme08);
			dest->m_bfme0c = first->m_bfme0c;
			dest->m_bfme10 = first->m_bfme10;
			dest->m_bfme14 = first->m_bfme14;
			dest->m_bfme18 = first->m_bfme18;
			++first;
			++dest;
		} while (--i);
	}
	return dest;
}
