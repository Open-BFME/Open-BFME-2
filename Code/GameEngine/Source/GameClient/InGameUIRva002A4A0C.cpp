// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva002A4A0C@InGameUI@@QAEXVAsciiString@@IPBURva002A1B1DChunk@@111@Z,
// retail 0x002A4A0C..0x002A4A68 (92 bytes, EH, RET 24): the InGameUI method
// two FX-nugget bodies (0x001E0D6A, 0x001E0DB0) call on TheInGameUI with a
// name, a count and four 12-byte chunks. The chunks go to the +0x8D4 holder
// (rowed 0x002A1B1D), then the name and count to the same holder's burst
// record (rowed 0x002A4646, name by value).

#include "ascii_string.h"

struct Rva002A1B1DChunk
{
	int m_words[3];
};

class Rva002A1B1D
{
public:
	void rva002A1B1D(const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4);
};

class Rva002A4646BurstRecord
{
public:
	void rva002A4646(AsciiString name, unsigned int count);
};

class InGameUI
{
public:
	void rva002A4A0C(AsciiString name, unsigned int count, const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4);
private:
	unsigned char m_pad000[0x8D4];
	Rva002A1B1D m_bursts8D4;				// +0x8D4
};

void InGameUI::rva002A4A0C(AsciiString name, unsigned int count, const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4)
{
	m_bursts8D4.rva002A1B1D(p1, p2, p3, p4);
	reinterpret_cast<Rva002A4646BurstRecord *>(&m_bursts8D4)->rva002A4646(name, count);
}
