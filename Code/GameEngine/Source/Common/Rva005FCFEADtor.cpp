// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva005FCFEA@@UAE@XZ @0x005FCFEA 80B: +0x28 via rowed ~Rva005242D7,
// +0x1c via rowed ~Rva0052413E, base ~Rva005FCF0E (rowed 75B). Both member
// views are vector<AsciiString> and are copied member for member from
// Rva005242D7Chain.cpp / Rva0052413EDtor.cpp (their dtors resolve through
// the ledger). Destruction order in the target (0x28, then 0x1c, then base)
// fixes the declaration order below.
#include <vector>

#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

class Rva005FCF0E
{
public:
	virtual ~Rva005FCF0E();
};

class Rva005FCFEA : public Rva005FCF0E
{
public:
	virtual ~Rva005FCFEA();
private:
	unsigned char m_pad1C[0x1C - 4];
	Rva0052413E m_mem1C;
	Rva005242D7 m_mem28;
};

Rva005FCFEA::~Rva005FCFEA()
{
}
