// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x00222610, 55B: for each of the 14 slots at +0xF0 (0x28 apart)
// (flag byte at slot +0x24, first flag at +0xF0) whose flag bit 2 is set, run rva00222481 on it and set bit 1; then set
// the byte at +0x311 and tail-call virtual slot 10.

#include "ascii_string.h"

class Rva00062908Host
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	bool rva00222481(int index);
	void rva00222610();

private:
	struct Slot
	{
		void rva00222647(int c, const AsciiString &s4, const AsciiString &s0, int b8);
		AsciiString m_s0;
		AsciiString m_s4;
		int m_8;
		int m_c;
		char m_pad10[0x14];
		unsigned char m_flags;
		char m_tail[3];
	};

	char m_pad04[0xC8];
	Slot m_slots[14];
	char m_pad2fc[0x15];
	bool m_311;
};

void Rva00062908Host::rva00222610()
{
	for (int i = 0; i < 14; ++i)
	{
		if (m_slots[i].m_flags & 2)
		{
			rva00222481(i);
			m_slots[i].m_flags |= 1;
		}
	}
	m_311 = true;
	s10();
}

// ?rva00222647@Slot@Rva00062908Host retail 0x00222647 78B true size to ret.
// Slot assign from 4 args then clears flag bits 2 1 8. Evidence: leaf lane,
// caller 0x002247C2, callees StringBase set rowed, prev/next same Host block.
void Rva00062908Host::Slot::rva00222647(int c, const AsciiString &s4, const AsciiString &s0, int b8)
{
	m_s0.set(s0);
	m_s4.set(s4);
	m_c = c;
	if (m_flags & 2)
		m_flags &= (unsigned char)~2;
	if (m_flags & 1)
		m_flags &= (unsigned char)~1;
	m_8 = b8;
	if (m_flags & 8)
		m_flags &= (unsigned char)~8;
}
