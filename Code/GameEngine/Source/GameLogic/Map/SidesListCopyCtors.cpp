// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Address-derived 0x0032C19D record view. Retail constructors and assignment
// establish the 4-byte scalar followed by two STLport vector control blocks;
// the original record name and field meaning remain unproven.

#include <vector>

struct Rva0032C0E3Element
{
	char m_body[0x80];
};

class Rva0032C19D
{
public:
	Rva0032C19D();
	~Rva0032C19D();
	Rva0032C19D &operator=(const Rva0032C19D &that);

private:
	int m_value;
	std::vector<Rva0032C0E3Element> m_first;
	std::vector<Rva0032C0E3Element> m_second;
};


Rva0032C19D::Rva0032C19D()
{
}

Rva0032C19D &Rva0032C19D::operator=(const Rva0032C19D &that)
{
	m_value = that.m_value;
	m_first = that.m_first;
	m_second = that.m_second;
	return *this;
}
