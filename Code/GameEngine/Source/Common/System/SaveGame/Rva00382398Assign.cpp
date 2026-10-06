// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003824A5@Rva00382398@@QAEAAV1@ABV1@@Z @0x003824A5 207B: assign twin of copy 0x003830EA over GameSlot base via rowed 0x002DBAB9 plus int at +0x1AC three AsciiStrings +0x1B0/+0x1B4/+0x1B8 seven ints +0x1BC..+0x1D4 two AsciiStrings +0x1D8/+0x1DC return this. Evidence: same layout as Rva00382398Copy.cpp plus Rva00447B58Assign.cpp recipe plus caller 0x00382E9B plus rowed set 0x000366F0.
#include "ascii_string.h"

class GameSlot {
public:
	virtual ~GameSlot();
	unsigned char m_pad04[0x1AC - 4];
	GameSlot &rva002DBAB9(const GameSlot &o);
};

class Rva00382398 : public GameSlot
{
public:
	virtual ~Rva00382398();
	int m_1AC;
	AsciiString m_1B0;
	AsciiString m_1B4;
	AsciiString m_1B8;
	int m_1BC;
	int m_1C0;
	int m_1C4;
	int m_1C8;
	int m_1CC;
	int m_1D0;
	int m_1D4;
	AsciiString m_1D8;
	AsciiString m_1DC;
	Rva00382398 &rva003824A5(const Rva00382398 &o);
};

Rva00382398 &Rva00382398::rva003824A5(const Rva00382398 &o)
{
	GameSlot::rva002DBAB9(o);
	m_1AC = o.m_1AC;
	m_1B0 = o.m_1B0;
	m_1B4 = o.m_1B4;
	m_1B8 = o.m_1B8;
	m_1BC = o.m_1BC;
	m_1C0 = o.m_1C0;
	m_1C4 = o.m_1C4;
	m_1C8 = o.m_1C8;
	m_1CC = o.m_1CC;
	m_1D0 = o.m_1D0;
	m_1D4 = o.m_1D4;
	m_1D8 = o.m_1D8;
	m_1DC = o.m_1DC;
	return *this;
}
