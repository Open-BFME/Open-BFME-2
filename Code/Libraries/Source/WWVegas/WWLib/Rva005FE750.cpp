// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva005FE750@@UAE@XZ @0x005FE750 87B via vtable plus StringBase plus Rva members plus wide vector
// Evidence: prev 0x005FE589 and next 0x005FE835 same vector family same flags; callees rowed vector 0x005FE4A3 Rva 0x005242D7 Rva 0x0052413E releaseBuffer 0x00036410; vtable 0x0087A3F4.

#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeContainerRecord005FDEC7
{
	unsigned int word0;
	unsigned int word1;
	UnicodeString text;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva005FE750
{
public:
	virtual ~Rva005FE750();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	int m_24;
	_STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > m_28;
};

Rva005FE750::~Rva005FE750()
{
}
