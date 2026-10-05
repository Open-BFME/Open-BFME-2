// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002DAAF2@Rva002DAAF2@@QAE_NABVAsciiString@@HHHH@Z @0x002DAAF2 38B
// Leaf: vtable slot 4 of 0x00803910 (class of Rva002DAB18); calls rowed
// StringBase::isEmpty 0x00001E2F and StringBase::set 0x000366F0; +0x10 member
// set with null-guarded early-out returning bool; caller 0x0009213F.
#include "ascii_string.h"

class Rva002DAAF2
{
public:
	virtual ~Rva002DAAF2();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	bool rva002DAAF2(const AsciiString &s, int a, int b, int c, int d);
private:
	char m_pad04[12];
	AsciiString m_str10;
};

bool Rva002DAAF2::rva002DAAF2(const AsciiString &s, int a, int b, int c, int d)
{
	if (s.isEmpty())
		return false;
	((StringBase<char> *)&m_str10)->set(*(const StringBase<char> *)&s);
	return true;
}
