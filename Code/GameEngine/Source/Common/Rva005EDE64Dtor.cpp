// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"

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
	char m_pad[16];
};

struct BfmeStringRecord005ED5F3;

namespace _STL
{
	template<class T> class allocator;
	template<class T, class Allocator> class vector;

	template<> class vector<BfmeStringRecord005ED5F3,
		allocator<BfmeStringRecord005ED5F3> >
	{
	public:
		~vector();
	private:
		BfmeStringRecord005ED5F3 *m_start;
		BfmeStringRecord005ED5F3 *m_finish;
		BfmeStringRecord005ED5F3 *m_endOfStorage;
	};
}

class Rva005EDE64
{
public:
	~Rva005EDE64();
private:
	char m_pad00[8];
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	UnicodeString m_28;
	UnicodeString m_2C[6];
	_STL::vector<BfmeStringRecord005ED5F3,
		_STL::allocator<BfmeStringRecord005ED5F3> > m_44;
};

Rva005EDE64::~Rva005EDE64()
{
}
