// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??4Rva00382E73@@QAEAAV0@ABV0@@Z @0x00382E73 308B: assign over Rva00381F04 at +0 via rowed 0x00381F04 eight Rva00382398 at +0xDC via just-landed 0x003824A5 AsciiStrings at +0xFDC/+0xFE8/+0xFFC/+0x1000 via rowed set 0x000366F0 plus ints bytes word tail to 0x1020. Evidence: chain caller of 0x003824A5 plus layout from loop 8x0x1E0 plus callers 0x0038589A 0x005A1BFD 0x005A3A78.
#include "ascii_string.h"

struct BfmeSaveElement002295D7
{
	virtual ~BfmeSaveElement002295D7();
	unsigned char m_pad04[0x1AC - 4];
	BfmeSaveElement002295D7 &rva002DBAB9(const BfmeSaveElement002295D7 &o);
};

class Rva00381F04
{
public:
	Rva00381F04 &operator=(const Rva00381F04 &o);
	virtual ~Rva00381F04();
private:
	unsigned char m_pad04[0xDC - 4];
};

class Rva00382398 : public BfmeSaveElement002295D7
{
public:
	virtual ~Rva00382398();
	Rva00382398 &rva003824A5(const Rva00382398 &o);
private:
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
};
// Ensure the declaration above mangles to the rowed honest name.
typedef char Rva00382398AssignCheck[sizeof(Rva00382398) == 0x1E0 ? 1 : -1];

class Rva00382E73
{
public:
	Rva00382E73 &operator=(const Rva00382E73 &o);
private:
	Rva00381F04 m_00;
	Rva00382398 m_DC[8];
	AsciiString m_FDC;
	int m_FE0;
	int m_FE4;
	AsciiString m_FE8;
	unsigned char m_FEC;
	unsigned char m_FED;
	int m_FF0;
	unsigned char m_FF4;
	int m_FF8;
	AsciiString m_FFC;
	AsciiString m_1000;
	int m_1004;
	unsigned short m_1008;
	int m_100C;
	int m_1010;
	int m_1014;
	int m_1018;
	int m_101C;
};

Rva00382E73 &Rva00382E73::operator=(const Rva00382E73 &o)
{
	m_00 = o.m_00;
	for (int i = 0; i < 8; ++i)
		m_DC[i].rva003824A5(o.m_DC[i]);
	m_FDC = o.m_FDC;
	m_FE0 = o.m_FE0;
	m_FE4 = o.m_FE4;
	m_FE8 = o.m_FE8;
	m_FEC = o.m_FEC;
	m_FED = o.m_FED;
	m_FF0 = o.m_FF0;
	m_FF4 = o.m_FF4;
	m_FF8 = o.m_FF8;
	m_FFC = o.m_FFC;
	m_1000 = o.m_1000;
	m_1004 = o.m_1004;
	m_1008 = o.m_1008;
	m_100C = o.m_100C;
	m_1010 = o.m_1010;
	m_1014 = o.m_1014;
	m_1018 = o.m_1018;
	m_101C = o.m_101C;
	return *this;
}
