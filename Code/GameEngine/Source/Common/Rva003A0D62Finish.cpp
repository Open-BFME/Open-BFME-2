// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?addUnitInfo@TeamPrototype@@QAEXABVRva0039D769@@@Z @0x003A0D62 166B.
// Evidence: unlock lane; the 0x18-stride array is Rva0039D5A9::m_items[7]
// at +0x130 (m_sum at +0x12c, count at +0xAC -> +0x1D8); StringBase compare
// row 0x0039D769 assign row; total at +0x2D4; max 7.

#include "ascii_string.h"

class Rva0039D769
{
public:
	Rva0039D769 &operator=(const Rva0039D769 &rhs);
	int m00;
	int m04;
	int m08;
	AsciiString m0C;
	AsciiString m10;
	int m14;
};

class Rva0039D5A9
{
public:
	int rva0039D5A9();
	int m_00;
	Rva0039D769 m_items[7];
	int m_countAC;
};

class TeamPrototype
{
public:
	void addUnitInfo(const Rva0039D769 &src);
 void rva003A0E08(const Rva0039D769 &src);
	char m_pad[0x12c];
	Rva0039D5A9 m_sum;
	char m_pad2[0xf8];
	int m_total;
};

void TeamPrototype::addUnitInfo(const Rva0039D769 &src)
{
	int i = 0;
	if (m_sum.m_countAC > 0)
	{
		do {
			if (((const StringBase<char> &)m_sum.m_items[i].m10).compare((const StringBase<char> &)src.m10) == 0 && m_sum.m_items[i].m14 == src.m14)
				goto found;
			++i;
		} while (i < m_sum.m_countAC);
	}
	i = m_sum.m_countAC;
	if (i >= 7)
		return;
	if (m_sum.rva0039D5A9() == 0)
		m_total = src.m00;
	else
		m_total += src.m00;
	m_sum.m_items[i] = src;
	m_sum.m_countAC++;
	return;
found:
	m_sum.m_items[i].m00 += src.m00;
	m_sum.m_items[i].m04 += src.m04;
	m_total += src.m00;
}

// Native003A0E08..003A0E6E and WB00EF2990: find the same name/handle
// record as addUnitInfo, subtract both requested counts and the total.
// AITeamBuilder recruitment calls this with the consumed unit record;
// the outer method name is not exposed by WB, so retain its address.
void TeamPrototype::rva003A0E08(const Rva0039D769 &src) {
 for(int i=0;i<m_sum.m_countAC;++i) {
  if(((const StringBase<char>&)m_sum.m_items[i].m10).compare((const StringBase<char>&)src.m10)==0 && m_sum.m_items[i].m14==src.m14) {
   m_sum.m_items[i].m00-=src.m00;
   m_sum.m_items[i].m04-=src.m04;
   m_total-=src.m00;
   break;
  }
 }
}
