// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva00382398@@QAE@XZ retail 0x004FDD8B 194 bytes.
// Default ctor over GameSlot base (0x1AC) with int at +0x1AC,
// three AsciiStrings at +0x1B0/+0x1B4/+0x1B8, seven ints +0x1BC..+0x1D4,
// two AsciiStrings at +0x1D8/+0x1DC. Identity from vtable 0x00819424
// shared with copy 0x003830EA and dtor 0x00382398 of the same class.
#include "ascii_string.h"

class GameSlot {
public:
	virtual ~GameSlot();
	unsigned char m_pad04[0x1AC - 4];
	GameSlot();
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
	Rva00382398();
};

Rva00382398::Rva00382398()
	: GameSlot()
	, m_1B0()
	, m_1B4()
	, m_1B8()
	, m_1D8()
	, m_1DC()
{
	{
		GameSlot tmp;
	}
	m_1B0.clear();
	m_1B4.clear();
	m_1C0 = 0;
	m_1C4 = 0;
	m_1C8 = 0;
	m_1CC = 0;
	m_1BC = 0;
	m_1AC = 0;
	m_1B8.clear();
	m_1D4 = -1;
	m_1D0 = -1;
}
