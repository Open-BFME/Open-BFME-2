// cl: /Ireference/shims/bfme2_ascii /Ob0
// ?Rva006BE270Fill@@YAXPAUBfmeElem60@@0ABU1@@Z 0x006BE270 112B evidence: BfmeVec60::insert caller 0x006BF800 fills range with value; struct layout from GeometryInfoSet BfmeElem60 plus canonical StringBase<char>::set(copy) 0x000366F0; sibling bfmeCopyAA TU flags
#include "ascii_string.h"

#include "../../Include/Common/BfmeCoord60.h"

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoord60 m_10;
	AsciiString m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad[2];
};

void Rva006BE270Fill(BfmeElem60 *first, BfmeElem60 *last, const BfmeElem60 &value)
{
	if (first == last)
		return;
	do
	{
		first->m_00 = value.m_00;
		first->m_04 = value.m_04;
		first->m_08 = value.m_08;
		first->m_0C = value.m_0C;
		first->m_10 = value.m_10;
		((StringBase<char> *)&first->m_1C)->set(*(const StringBase<char> *)&value.m_1C);
		first->m_20 = value.m_20;
		first->m_21 = value.m_21;
		++first;
	} while (first != last);
}
