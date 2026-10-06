// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// ?rva000C38F8@Rva000C38F8@@QAEXXZ @0x000C38F8 253B
// Retail clear: memset 0x4c then vector erase 0x4c, string releases 0x58 0x70 0x5c 0x60,
// vector erase 0x78, list clear 0xB4, vector erase 0xB8, release 0x74, vectors 0x84 0x90 0x9C 0xA8,
// vector erase 0xD0, then zeroes E0 F0 DC E4 E8 EC F4 F5.
// Evidence: callees memset 0x6291AE vector erase 0x2CCFC releaseBuffer 0x36410 list clear 0x239D49
// Rva000C1CAE erase 0xC1CAE BfmeStringRecord erase 0x8B4D2, caller 0xC48C6, layout from retail offsets.
#include "ascii_string.h"

extern "C" void *memset(void *dst, int val, unsigned int n);

namespace _STL
{
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end;
	T *erase(T *first, T *last);
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
};
template <class T, class Alloc> class _List_base
{
public:
	void clear();
};
}

struct Rva000C1CAEElement
{
	int _00;
	int _04;
};

struct BfmeStringRecord000B9534
{
	int _00[8];
};

class Rva000C38F8
{
public:
	void rva000C38F8();
private:
	char _00[0x4c];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_4c;
	AsciiString m_58;
	AsciiString m_5c;
	AsciiString m_60;
	char _64[0x0c];
	AsciiString m_70;
	AsciiString m_74;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_78;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_84;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_90;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_9c;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_a8;
	char m_b4[4];
	_STL::vector<Rva000C1CAEElement, _STL::allocator<Rva000C1CAEElement> > m_b8;
	char _c4[0x0c];
	_STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> > m_d0;
	int m_dc;
	int m_e0;
	float m_e4;
	int m_e8;
	float m_ec;
	int m_f0;
	bool m_f4;
	bool m_f5;
};

void Rva000C38F8::rva000C38F8()
{
	memset(this, 0, 0x4c);
	m_4c.clear();
	m_58.clear();
	m_70.clear();
	m_5c.clear();
	m_60.clear();
	m_78.clear();
	((_STL::_List_base<AsciiString, _STL::allocator<AsciiString> > *)((char *)this + 0xb4))->clear();
	m_b8.clear();
	m_74.clear();
	m_f4 = false;
	m_84.clear();
	m_90.clear();
	m_9c.clear();
	m_a8.clear();
	m_d0.clear();
	m_f5 = false;
	m_e0 = 0;
	m_f0 = 0;
	m_dc = 0;
	m_e4 = 0.0f;
	m_e8 = 0xff;
	m_ec = 0.0f;
}
