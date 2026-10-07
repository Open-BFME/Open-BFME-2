// ??4Rva000C27B0@@QAEAAV0@ABV0@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHs-c- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??4Rva000C27B0@@QAEAAV0@ABV0@@Z, retail 0x000C27B0 464B.
// Copy-assign for address-derived class Rva000C27B0. Layout mirrors the
// neighbouring Rva000C2980 dtor TU (AsciiString at +0x58/+0x5c/+0x60/+0x70/
// +0x74, five vector<AsciiString> at +0x78/+0x84/+0x90/+0x9c/+0xa8,
// vector<AsciiString> at +0x4c, AudioEventRTS* at +0xdc) with packet-proven
// element types at +0x64/+0xb4/+0xb8/+0xc4/+0xd0. Evidence: unlock lane,
// caller 0x000C8A52 in FUN_004c8914, self-check je, rep movsd 0x13 for
// +0x00..+0x4b, rowed StringBase::set at 0x366F0, rowed vector/list assigns,
// erase plus push_back loop at +0x4c, dword copies at +0xe0..+0xf0, new
// AudioEventRTS at 0x79514 plus assign at 0x9A41B for +0xdc. Identity is
// address-derived (naming: line); class may match Rva000C2980 but keeps its
// own honest name until proven.
#include "ascii_string.h"

struct Pad00 { char d[0x4c]; };

struct Rva000BDBFARecord { char _pad[4]; };
class Rva000BB491 { public: char _pad[4]; };
class Rva000BB4AC { public: char _pad[4]; };
struct Rva000BC20DWords { char _pad[4]; };
struct BfmeStringRecord000B94D2 { char _pad[8]; };
class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &that);
private:
	AsciiString m_first;
	AsciiString m_second;
	int m_unknown8;
	float m_floatC;
	float m_float10;
	float m_float14;
	float m_float18;
	float m_float1C;
	float m_float20;
	unsigned char m_byte24;
	unsigned char m_byte25;
	unsigned char m_byte26;
	char m_pad27;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A> class vector
{
public:
	vector &operator=(const vector &x);
	T *erase(T *first, T *last);
	void push_back(const T &x);
	T *begin() { return m_begin; }
	T *end() { return m_finish; }
	const T *begin() const { return m_begin; }
	const T *end() const { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_begin); }
private:
	T *m_begin;
	T *m_finish;
	T *m_end;
};

template <class T, class A> class list
{
public:
	list &operator=(const list &x);
private:
	void *m_node;
};
}

class Rva000C27B0
{
public:
	Rva000C27B0 &operator=(const Rva000C27B0 &that);
private:
	Pad00 m_pad00;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_4c;
	AsciiString m_58;
	AsciiString m_5c;
	AsciiString m_60;
	_STL::vector<BfmeStringRecord000B94D2, _STL::allocator<BfmeStringRecord000B94D2> > m_64;
	AsciiString m_70;
	AsciiString m_74;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_78;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_84;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_90;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_9c;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_a8;
	_STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> > m_b4;
	_STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> > m_b8;
	_STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> > m_c4;
	_STL::vector<Rva000BC20DWords, _STL::allocator<Rva000BC20DWords> > m_d0;
	AudioEventRTS *m_dc;
	int m_e0;
	int m_e4;
	int m_e8;
	int m_ec;
	int m_f0;
	unsigned char m_f4;
	unsigned char m_f5;
};

Rva000C27B0 &Rva000C27B0::operator=(const Rva000C27B0 &that)
{
	if (this == &that)
		return *this;
	m_pad00 = that.m_pad00;
	m_74 = that.m_74;
	m_58 = that.m_58;
	m_70 = that.m_70;
	m_5c = that.m_5c;
	m_60 = that.m_60;
	m_78 = that.m_78;
	m_b4 = that.m_b4;
	m_b8 = that.m_b8;
	m_c4 = that.m_c4;
	m_f4 = that.m_f4;
	m_84 = that.m_84;
	m_90 = that.m_90;
	m_9c = that.m_9c;
	m_a8 = that.m_a8;
	m_d0 = that.m_d0;
	m_f5 = that.m_f5;
	m_4c.erase(m_4c.begin(), m_4c.end());
	for (int i = 0; i < (int)that.m_4c.size(); ++i)
		m_4c.push_back(that.m_4c.begin()[i]);
	m_e0 = that.m_e0;
	m_e4 = that.m_e4;
	m_e8 = that.m_e8;
	m_ec = that.m_ec;
	m_f0 = that.m_f0;
	m_64 = that.m_64;
	m_dc = 0;
	if (that.m_dc != 0) {
		m_dc = new AudioEventRTS;
		*m_dc = *that.m_dc;
	}
	return *this;
}
