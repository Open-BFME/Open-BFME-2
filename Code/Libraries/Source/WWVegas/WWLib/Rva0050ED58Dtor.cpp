// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0050ED58@@QAE@XZ 91B @0x0050ED58: dtor destroying 7x8B array at +0x24 via ??_M then member dtors at +0x14 plus +0x08 plus StringBase release at +0x04 with EH states 2 1 0 -1. Sizes from ??_M pushes (8 7) and member spans; member classes copied from their owner TUs (dtors rowed, declared only here). Evidence: EH prolog plus rowed callees plus callers at 0x0050F185 0x0050F69D 0x0050F6B9.
#include <vector>

#include "ascii_string.h"

class Rva005241B0
{
public:
	~Rva005241B0();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

struct Rva0050ED58Elem
{
	~Rva0050ED58Elem();
	char m_data[8];
};

class Rva0050ED58
{
public:
	~Rva0050ED58();
private:
	char m_pad00[4]; // +0x00
	AsciiString m_str04; // +0x04
	Rva0052413E m_08; // +0x08
	Rva005241B0 m_14; // +0x14
	char m_pad20[4]; // +0x20
	Rva0050ED58Elem m_arr24[7]; // +0x24
};

Rva0050ED58::~Rva0050ED58()
{
}
