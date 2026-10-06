// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0025D19E@BfmeStrVM0@@QAEXXZ, retail 0x0025D19E, 103 bytes.
// Field reset of BfmeStrVM0: clears flags at +0x64/+0x10C, and when a timer is
// present runs the predicate-guarded release (rowed rva0025D10F), polls the
// timer slot-7 virtual and drops it; zeroes the +0xC8/+0xCC floats, resets a
// non-empty name at +0xD0 to the exported AsciiString::TheEmptyString
// (0x009E0878, via the pinned operator=), and stamps -1 at +0xE0/+0xE4.
// Evidence: sole caller at 0x0025D6A4 (unclaimed dtor, same this); rowed
// StringBase<char>::isEmpty (AsciiString.cpp) and slot-7 BfmeVM0Timer virtual.
#include "ascii_string.h"


class BfmeVM0Timer
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
};

class BfmeStrVM0
{
public:
	void rva0025D10F();
	void rva0025D19E();
private:
	char m_pad00[0x38];
	BfmeVM0Timer *m_timer;
	char m_pad3C[0x28];
	bool m_b64;
	char m_pad65[0x63];
	float m_fC8;
	float m_fCC;
	AsciiString m_name;
	char m_padD4[0x0c];
	int m_iE0;
	int m_iE4;
	char m_padE8[0x24];
	bool m_b10C;
};

void BfmeStrVM0::rva0025D19E()
{
	m_b10C = false;
	m_b64 = false;
	if (m_timer != 0)
	{
		rva0025D10F();
		m_timer->v7();
		m_timer = 0;
	}
	m_fC8 = 0.0f;
	m_fCC = 0.0f;
	if (!m_name.isEmpty())
		m_name = AsciiString::TheEmptyString;
	m_iE4 = -1;
	m_iE0 = -1;
}
