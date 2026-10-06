// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?rva000C32D9@Rva000C32D9@@QAEXIVAsciiString@@@Z @0x000C32D9 98B: vector<AsciiString> resize via erase vs _M_fill_insert. Evidence: caller 0x000C3AB3 grows to esi+1 with EmptyString then sets element; retail erases start+n..finish when n<size else fill_insert finish n-size value plus releaseBuffer of by-value AsciiString.
#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	AsciiString *erase(AsciiString *first, AsciiString *last);
	void _M_fill_insert(AsciiString *pos, unsigned int n, const AsciiString &x);
};
}

class Rva000C32D9
{
	AsciiString *m_begin;
	AsciiString *m_finish;
	AsciiString *m_end_of_storage;
public:
	void rva000C32D9(unsigned int n, AsciiString x);
};

void Rva000C32D9::rva000C32D9(unsigned int n, AsciiString x)
{
	if (n < (unsigned int)(m_finish - m_begin))
		((_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)this)->erase(m_begin + n, m_finish);
	else {
		unsigned int need = n - (unsigned int)(m_finish - m_begin);
		((_STL::vector<AsciiString, _STL::allocator<AsciiString> > *)this)->_M_fill_insert(m_finish, need, x);
	}
}
