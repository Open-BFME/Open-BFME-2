// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva00382398@@QAE@ABV0@@Z, retail 0x003830EA, 257 bytes.
// Copy ctor over BfmeSaveElement002295D7 base (0x1AC) with int at +0x1AC,
// three AsciiStrings at +0x1B0/+0x1B4/+0x1B8, seven ints +0x1BC..+0x1D4,
// two AsciiStrings at +0x1D8/+0x1DC. Identity from vtable 0xC19424,
// rowed base copy 0x002295D7, rowed StringBase copy 0x000365F0 and rowed
// dtor 0x00382398 of the same class.
#include "ascii_string.h"

struct BfmeSaveElement002295D7
{
	virtual ~BfmeSaveElement002295D7();
	unsigned char m_pad04[0x1AC - 4];
	BfmeSaveElement002295D7(const BfmeSaveElement002295D7 &other);
};

class Rva00382398 : public BfmeSaveElement002295D7
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
	Rva00382398(const Rva00382398 &other);
};

Rva00382398::Rva00382398(const Rva00382398 &other)
	: BfmeSaveElement002295D7(other)
	, m_1AC(other.m_1AC)
	, m_1B0(other.m_1B0)
	, m_1B4(other.m_1B4)
	, m_1B8(other.m_1B8)
	, m_1BC(other.m_1BC)
	, m_1C0(other.m_1C0)
	, m_1C4(other.m_1C4)
	, m_1C8(other.m_1C8)
	, m_1CC(other.m_1CC)
	, m_1D0(other.m_1D0)
	, m_1D4(other.m_1D4)
	, m_1D8(other.m_1D8)
	, m_1DC(other.m_1DC)
{
}
