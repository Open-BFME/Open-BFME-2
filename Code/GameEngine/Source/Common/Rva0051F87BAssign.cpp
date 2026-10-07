// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??4Rva0051F87B@@QAEAAV0@ABV0@@Z @0x0051F972 111B
// operator= for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4 via rowed StringBase@G set 0x00037150, int at +8, AsciiString at +0xC
// via rowed StringBase@D set 0x000366F0, int at +0x10, Rva0051F6DF at +0x14
// via rowed 0x0051F6DF, vector<Rva0051F7ADRecord> at +0x20 via rowed 0x0051F7AD,
// three vector<Rva0026F4F4Element> at +0x2C/+0x38/+0x44 via rowed 0x0026F4F4.
// Evidence: same layout as rowed copy 0x0051F87B and default ctor 0x0051FAFC;
// callers in stlport_asciistring_record_bodies and StlSweepW5Rva0051FC54;
// add edi 0x44 tail matches copy ctor.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

class Rva0051F6DF
{
public:
	Rva0051F6DF &operator=(const Rva0051F6DF &other);
private:
	char m_data[12];
};

struct Rva0051F7ADRecord
{
	char bytes[12];
};

struct Rva0026F4F4Element
{
	unsigned words[1];
};

class Rva0051F87B
{
public:
	virtual ~Rva0051F87B();
	Rva0051F87B &operator=(const Rva0051F87B &other);
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	Rva0051F6DF m_14;
	_STL::vector<Rva0051F7ADRecord, _STL::allocator<Rva0051F7ADRecord> > m_20;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_2C;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_38;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_44;
};

Rva0051F87B &Rva0051F87B::operator=(const Rva0051F87B &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_20 = other.m_20;
	m_2C = other.m_2C;
	m_38 = other.m_38;
	m_44 = other.m_44;
	return *this;
}
